# Estaciones de tierra (ET), que constituyen los elementos básicos de la red.
import socket
import os
import time
import json
import auxMethods
import terminal
import threading
import sys
import base64

# Estación terrestre (ET)
class Station():
    bo_socket = None
    drone_socket = None
    etApp = None
    drones = {}
    host = '127.0.0.1'
    port = auxMethods.et_initial_port
    public_key = None
    private_key = None
    bo_public_key = None

    # Constructor for ET
    def __init__(self, id, host='127.0.0.1', port=auxMethods.et_initial_port):
        # Run the interface for the ET
        self.etApp = terminal.EtApp()
        app_thread = threading.Thread(target=self.etApp.run)
        app_thread.start()
        self.stop_event = threading.Event() # Event to stop the threads
        self.id = id

        # Create RSA public and private keys
        self.public_key, self.private_key = auxMethods.generate_keys()

        #Create the sockets for the drones
        self.drone_socket = socket.socket()

        # Check port availability and if not available try different port
        self.port = auxMethods.assignPorts(self.drone_socket, self.host, self.port)
        self.drone_socket.listen(10)

        time.sleep(0.2)
        self.etApp.updateInfo("[INFO]   ET creada con ip: "+self.host+"\n\tpuerto: "+str(self.port))
        self.etApp.updateInfo("[INFO]   La id aún no esta asignada por la BO")
        self.etApp.updateInfo("[INFO]   Usa el comando link para conectar con la BO")

        self.drone_socket.listen(10)
        listen_thread = threading.Thread(target=self.listen_elements)
        listen_thread.start()


    # ------------------------------DRONE SOCKETS HANDLER------------------------------
    # Checks for the entry connections and assigns a thread to handle them
    def listen_elements(self):
        while not self.stop_event.is_set():
            try:
                # Accept new petition to connect with the drones socket
                Client, address = self.drone_socket.accept()
                # Wait for first message of connection identifier
                msg = auxMethods.listen_socket(Client)

                # If drone, save in drone dictionary and start thread to handle the connection
                if msg['element'] == 'drone':
                    self.drones[msg['id']] = {"Client":Client, "battery":100, "state":"UNKNOWN", "public_key":msg['public_key']}
                    auxMethods.sendMessage(Client, '{"type":"response","connection": true}') # , self.private_key, msg['public_key'])
                    threading.Thread(target=self.drone_connection, args=(Client, msg['id'])).start()
                    self.etApp.updateInfo("[OK]     Drone "+msg['id']+" conectado")
                
                # If et, start thread to handle the connection
                elif msg['element'] == 'et':
                    auxMethods.sendMessage(Client, '{"type":"response","connection": true}')
                    self.etApp.updateInfo('[OK]     Conectado a et: ' + address[0] + ':' + str(address[1]))
                    threading.Thread(target=self.et_connection, args=(Client, msg['id'],msg['public_key'])).start()

            except Exception as e:
                self.etApp.updateInfo("[ERROR]  Fallo en escucha"+str(e))
                self.drone_socket.close()
                break

    # ------------------------------DRONE CONNECTIONS HANDLER------------------------------
    # Handles the connection with the drone and its petitions
    def drone_connection(self, connection, droneId):
        while not self.stop_event.is_set():
            # Wait for the connection to recieve a petition
            res = auxMethods.listen_socket(connection, self.private_key, self.drones[droneId]['public_key'])
            if res!=None:
                
                # If the type of the petition is a disconnect of the drone handle it and stop waiting to recieve
                if res['type'] == 'disconnect':
                    # TODO implementar disconnect
                    self.disconnectFromDrone(res['id'] )
                    break

                # If the type of the petition is a response from the drone just print it
                elif res['type'] == 'response':
                    pass
                    # self.etApp.updateInfo(res['msg'])

                # If the message type is a telemetry save the states to our database and show the new status of the drones
                elif res['type'] == 'telemetry':
                    self.drones[droneId]["state"]=res["s"]
                    self.drones[droneId]["battery"]=res["b"]
                    message = "Dr " + str(droneId) + ", Bat: " + str(res["b"])+ ", St: " + str(res["s"])
                    self.etApp.updateStatus(droneId, message)
            # If something fails during the recieve the connection will fail and the drone will get disconnected
            else:
                self.etApp.updateInfo("[ERROR]  Connection with drone "+droneId+" failed: Drone disconnected")
                connection.close()
                break

    def et_connection(self, connection, etId, et_public_key):
        res = auxMethods.listen_socket(connection, self.private_key, et_public_key)
        if res!=None:

            if res['type'] == 'send_msg':
                self.etApp.updateInfo("[INFO]   ET "+etId+" says: "+res['msg'])
            
            elif res['type'] == 'sf':
                # 
                self.etApp.updateInfo("[INFO]   ET "+etId+" envia archivo llamado: "+res['n'])
                # If directory does not exist, create it
                if not os.path.exists(self.id+'_downloads'):
                    os.makedirs(self.id+'_downloads')
                # Open file to write
                file = open(self.id+'_downloads/'+res['n'], 'w')
                # Recieve file

                data = ""
                i=0
                while i<res['c']:
                    msg = None
                    while msg == None:
                        msg = auxMethods.listen_socket(connection, self.private_key, et_public_key)
                    auxMethods.sendMessage(connection, '{"type":"response","msg":"Chunk received"}', self.private_key, et_public_key)
                    if msg['type'] == "c":#  and num == i:
                        data = data + msg['d'][2:-1]
                        i+=1
                file.write(data)
                file.close()
                self.etApp.updateInfo("[INFO]   Descargado "+res['n']+" enviado por "+etId)

        else:
            self.etApp.updateInfo("[ERROR]  Connection with ET "+etId+" failed") 
        connection.close()

    def bo_connection(self):
        while not self.stop_event.is_set(): 
            res = auxMethods.listen_socket(self.bo_socket, self.private_key, self.bo_public_key)
            if res!=None:
                if res['type'] == 'fly':
                    if res['drone_id'] in self.drones.keys():
                        self.fly(res['drone_id'])
                        auxMethods.sendMessage(self.bo_socket, '{"type":"Success"}', self.private_key, self.bo_public_key)
                        self.etApp.updateInfo("[INFO]   BO ordered a fly command to drone: "+res['drone_id'])
                    else:
                        auxMethods.sendMessage(self.bo_socket, '{"type":404}', self.private_key, self.bo_public_key)

                if res['type'] == 'land':
                    if res['drone_id'] in self.drones.keys():
                        self.land(res['drone_id'])
                        auxMethods.sendMessage(self.bo_socket, '{"type":"Success"}', self.private_key, self.bo_public_key)
                        self.etApp.updateInfo("[INFO]   BO ordered a land command to drone: "+res['drone_id'])

                    else:
                        auxMethods.sendMessage(self.bo_socket, '{"type":404}', self.private_key, self.bo_public_key)
                
                elif res['type'] == 'send_msg':
                    self.etApp.updateInfo("[INFO]   BO says: "+res['msg'])

                elif res['type'] == 'send_file':
                    self.etApp.updateInfo("[INFO]   BO is sending a file called: "+res['file_name'])
                    # If directory does not exist, create it
                    if not os.path.exists('sent_files'):
                        os.makedirs('sent_files')
                    # Open file to write
                    file = open('sent_files/'+res['file_name'], 'w')
                    # Recieve file

                    msg = res
                    data = ""
                    i=0
                    while i<res['chunks']:
                        msg = auxMethods.listen_socket(self.bo_socket)
                        auxMethods.sendMessage(self.bo_socket, '{"type":"response", "msg":"Chunk received"}')
                        
                        # self.etApp.updateInfo(str(msg))
                        if msg['type'] == "chunk":
                            data = data + msg['data'][2:-1]
                            i+=1
                    # final = final + "'"
                    # final = base64.b64decode(final)
                    # self.etApp.updateInfo(str(final))
                    file.write(data)
                    file.close()
                    self.etApp.updateInfo("[INFO]   Downloaded file "+res['file_name']+" sent by BO")

                elif res['type'] == 'get_status':
                    # auxMethods.sendMessage(self.bo_socket, json.dumps(self.etApp.getStatus()), self.private_key, self.bo_public_key)
                    status = json.dumps(self.etApp.getStatus())
                    # Trocear status en chunks de 16 caracteres
                    chunks = [status[i:i+16] for i in range(0, len(status), 16)]
                    # Enviar numero de chunks
                    auxMethods.sendMessage(self.bo_socket, '{"type":"status", "chunks":'+str(len(chunks))+'}', self.private_key, self.bo_public_key)
                    # Enviar chunks
                    chunk_id = 0
                    while chunk_id < len(chunks):
                        auxMethods.sendMessage(self.bo_socket, '{"type":"chunk", "data":"'+chunks[chunk_id]+'"}', self.private_key, self.bo_public_key)
                        res = auxMethods.listen_socket(self.bo_socket, self.private_key, self.bo_public_key)
                        if res == None:
                            continue
                        if res['type'] == 'response':
                            chunk_id += 1
                        
                    self.etApp.updateInfo("[INFO]   Status sent to BO")


                elif res['type'] == 'shutdown':
                    for drone in self.drones.keys():
                        auxMethods.sendMessage(self.drones[drone]["Client"], '{"type":"shutdown"}', self.private_key, self.drones[drone]['public_key'])
                        self.etApp.updateInfo("[INFO]   Shutting down drone : "+drone)
                    self.etApp.updateInfo("[INFO]   ET is shutting down")
                    self.exit()

                else: 
                    auxMethods.sendMessage(self.bo_socket, '{"type":"response", "msg":"incorrect command"}', self.private_key, self.bo_public_key)
            else:
                pass
                # self.etApp.updateInfo("[ERROR]  Connection with BO failed "+str(res))
    # ------------------------------COMMAND RECIEVER------------------------------

    # Main loop checking for commands
    def commands(self):
        while True:

            if self.etApp.command!="":
                # Parse command and args
                command = self.etApp.command.split(" ")

                #Case command is EXIT
                if command[0] == "exit":
                    self.exit()

                #Case command is HELP
                elif command[0] == "help":
                    self.etApp.updateInfo("[HELP]   Posibles comandos: link, fly <et_id>, land <et_id>, exit")

                #Case command is FLY
                elif command[0] == "fly":
                    if len(command) != 2:
                        self.etApp.updateInfo("[HELP]   Drone no especificado. Uso: fly <drone_id>")
                    else:
                        if command[1] not in self.drones.keys():
                            self.etApp.updateInfo("[ERROR]  El drone "+command[1]+" no esta conectado a la ET")
                        else:
                            self.fly(command[1])

                #Case command is LAND
                elif command[0] == "land":
                    if len(command) != 2:
                        self.etApp.updateInfo("[HELP]   Drone no especificado. Uso: land <drone_id>")
                    else:
                        if command[1] not in self.drones.keys():
                            self.etApp.updateInfo("[ERROR]  El drone "+command[1]+" no esta conectado a la ET")
                        else:
                            self.land(command[1])

                # TODO Case command is LINK
                elif command[0] == "link":
                    self.link()

                # Case command is UNLINK
                elif command[0] == "unlink":
                    self.unlink()
                
                # Case command is SEND_MSG/FILE
                # TODO pasar a solo un comando
                elif command[0] == "send":
                    # Case command is SEND_MSG
                    if command[1] == "msg":
                        if len(command) >= 4:
                            self.send_msg(command[2], ' '.join(command[3:]))
                        else:
                            self.etApp.updateInfo("[HELP]   ET no especificada. Uso: send msg <et_id> <msg>")
                    # Case command is SEND_FILE
                    elif command[1] == "file":
                        if len(command) == 4:
                            self.send_file(command[2], command[3])
                        else:
                            self.etApp.updateInfo("[HELP]   ET no especificada. Uso: send file <et_id> <file_path>")

                # TODO Case command is DISCONNECT
                elif command[0] == "disconnect":
                    if len(command) == 2:
                        if command[1] not in self.drones.keys():
                            self.etApp.updateInfo("[ERROR]  El drone "+command[1]+" no esta conectado a la ET")
                        else:
                            self.disconnect(command[1])
                    else:
                        self.etApp.updateInfo("[HELP]   ET no especificada. Uso: disconnect <drone_id>")

                # Case command is not recognised
                else:
                    self.etApp.updateInfo("[ERROR]  Comando no reconocido")

                # Reset the command variable
                self.etApp.command=""

    def exit(self):
        self.stop_event.set()                       # Stop threads
        try:
            self.bo_socket.shutdown(socket.SHUT_RD)     # Stop listening
        except:
            pass
        # Stop listening all drones
        for drone in self.drones:
            self.disconnect(drone)
            self.drones[drone]["Client"].close()
        try:
            self.drone_socket.shutdown(socket.SHUT_RD)
        except:
            pass
        try:
            self.bo_socket.close()                      
        except:
            pass
        self.etApp.die()                            # Close interface
        os.system('clear')                          # Clear terminal
        print("\n\n\n\t\tPress any button to return to terminal")
        sys.exit(0) 

    # ------------------------------COMMAND HANDLER------------------------------

    # ---------para et y bo---------
    # Link ET and BO
    def link(self):

        if self.bo_socket!=None:
            self.etApp.updateInfo( "[INFO]   ET ya conectada con la BO")
            return

        # Connect ET to the BO
        self.etApp.updateInfo( "[INFO]   Conectando con la BO...")
        self.bo_socket, self.id, self.bo_public_key = auxMethods.connectToBO(self.id, self.public_key, self.host, self.port)
        if self.bo_socket == None:
            self.etApp.updateInfo("[ERROR]  La BO no se encuentra activa")
            return

        self.etApp.updateInfo( "[OK]     ET enlazado a BO con id "+ str(self.id))
        self.etApp.update_name(self.id)
        bo_thread = threading.Thread(target=self.bo_connection)
        bo_thread.start()


    # Unlinks ET and BO
    def unlink(self):

        if self.bo_socket==None:
            self.etApp.updateInfo( "[INFO]   La ET aun no esta conectada a la BO.")
            return
        # Disconnect all drones
        for drone in self.drones:
            self.disconnect(drone)
        # Disconnect ET from BO
        auxMethods.disconnectFromBO(self.bo_socket, False, self.private_key, self.bo_public_key)
        self.bo_socket = None
        self.bo_public_key = None
        self.etApp.updateInfo("[OK]     ET desconectado de BO")
        self.etApp.update_name("")

    def send_msg(self, et_id, content):

        # Check if ET is linked to the BO
        if not self.bo_socket:
            self.etApp.updateInfo("[ERROR]  Esta estación no está conectada a la bo. Usar comando 'link'")
            return
        
        # If ET is BO, send message to the BO
        if et_id == "BO":
            msg = '{"type": "sm", "id": "'+self.id+'", "msg": "'+content+'"} '
            res = auxMethods.sendMessage(self.bo_socket, msg, self.private_key, self.bo_public_key)
            return
        

        # Ask BO for ET ip and port
        msg = '{"type": "link", "element":"et", "id":"' + et_id + '"} '
        while not self.stop_event.is_set():
            auxMethods.sendMessage(self.bo_socket, msg, self.private_key, self.bo_public_key)
            res = auxMethods.listen_socket(self.bo_socket)
            if res == None:
                continue
                # self.etApp.updateInfo("[ERROR]    No se ha podido conectar a la bo")
                # return
            if 'connection' in res:
                break

        
        if res['connection'] != True:
            self.etApp.updateInfo("[ERROR]  No se ha podido conectar a la bo")
            return


        et_ip = res["ip"]
        et_port = res["port"]
        et_public_key = res["public_key"]


        # Send connect message to ET
        msg = '{"type": "connect", "element":"et", "id":"' + self.id + '","public_key":"' + self.public_key + '"} '
        
        et_socket = socket.socket()
        et_socket.connect((et_ip, int(et_port)))
        res = auxMethods.sendRequest(et_socket, msg)

        

        if res == None:
            self.etApp.updateInfo("[ERROR]    No se ha podido conectar a la estación: "+str(et_id))
            et_socket.close()
            return
        
        
        # Send send_msg message to ET
        msg = '{"type": "send_msg", "msg":"' + content + '"} '
        res = auxMethods.sendMessage(et_socket, msg, self.private_key, et_public_key)
        self.etApp.updateInfo("[OK]     Mensaje enviado con exito a ET: "+str(et_id))
        et_socket.close()

    # Mensaje SEND_FILE: envia fichero a otra ET o a la BO.
    def send_file(self, et_id, file_path):
        
        # Check if ET is linked to the BO
        if not self.bo_socket:
            self.etApp.updateInfo("[ERROR]    Esta estación no está conectada a la bo. Usar comando 'link'")
            return
        

        # Open file
        try:
            with open(file_path, "r") as f:
                file_content = f.read()
        except Exception as e:
            self.etApp.updateInfo("[ERROR]    No se ha podido leer el fichero")
            return
        file_name = file_path.split("/")[-1]
        file_content = str.encode(file_content, encoding='utf-8')
        file_chunks = [file_content[i:i+16] for i in range(0, len(file_content), 16)]
        chunk_id=0


        # If ET is BO, send message to the BO
        if et_id == "BO":
            
            msg = '{"type": "sf", "n":"'+ file_name +'", "c": '+str(len(file_chunks))+'} '
            auxMethods.sendMessage(self.bo_socket, msg, self.private_key, self.bo_public_key)
            time.sleep(0.1)
            while chunk_id < len(file_chunks):
                msg = '{"type":"c","n":' + str(chunk_id) + ',"d":"'+str(file_chunks[chunk_id])+'"} '
                auxMethods.sendMessage(self.bo_socket, msg, self.private_key, self.bo_public_key)
                res = auxMethods.listen_socket(self.bo_socket, self.private_key, self.bo_public_key)
                if res == None:
                    continue
                if res["type"]=="response" and res["msg"]=="Chunk received":
                    chunk_id+=1
            return 

        else:
            # Ask BO for ET ip and port
            msg = '{"type": "link", "element":"et", "id":"' + et_id + '"} '
            while not self.stop_event.is_set():
                auxMethods.sendMessage(self.bo_socket, msg, self.private_key, self.bo_public_key)
                res = auxMethods.listen_socket(self.bo_socket)
                if res == None:
                    continue
                    # self.etApp.updateInfo("[ERROR]    No se ha podido conectar a la bo")
                    # return
                if 'connection' in res:
                    break

            
            if res['connection'] != True:
                self.etApp.updateInfo("[ERROR]  No se ha podido conectar a la bo")
                return


            et_ip = res["ip"]
            et_port = res["port"]
            et_public_key = res["public_key"]

            # Send connect message to ET
            msg = '{"type": "connect","element":"et","id":"' + self.id + '","public_key":"' + self.public_key + '"} '
            et_socket = socket.socket()
            et_socket.connect((et_ip, int(et_port)))
            res = auxMethods.sendRequest(et_socket, msg)
            if res == None:
                self.etApp.updateInfo("[ERROR]    No se ha podido conectar a la estación: "+str(et_id))
                et_socket.close()
                return
            

            msg = '{"type": "sf", "n":"'+ file_name +'", "c": '+str(len(file_chunks))+'} '
            auxMethods.sendMessage(et_socket, msg, self.private_key, et_public_key)
            time.sleep(0.1)
            while chunk_id < len(file_chunks):
                msg = '{"type":"c","n":' + str(chunk_id) + ',"d":"'+str(file_chunks[chunk_id])+'"} '
                auxMethods.sendMessage(et_socket, msg, self.private_key, et_public_key)
                res = auxMethods.listen_socket(et_socket, self.private_key, et_public_key)
                if res == None:
                    continue
                if res["type"]=="response" and res["msg"]=="Chunk received":
                    chunk_id+=1
            
            self.etApp.updateInfo("[OK]     Archivo "+file_name+" enviado con exito a ET: "+str(et_id))

            et_socket.close()
        

    # ---------para drones---------
    #   Mensaje FLY: ordena al drone que alce el vuelo e inicie la búsqueda de enanitos cautivos.
    def fly(self, drone_id):

        try:
            self.etApp.updateInfo("[INFO]   Drone "+drone_id+" volando")
            msg = '{"type": "fly"}'
            auxMethods.sendMessage(self.drones[drone_id]["Client"], msg, self.private_key, self.drones[drone_id]['public_key'])

        except Exception as e:
            self.drone_socket.close()
    
    #   Mensaje LAND: ordena a un drone concreto para que finalice el vuelo y se pose de forma segura en el suelo tan pronto como le sea posible.
    def land(self, drone_id):
        
        try:
            self.etApp.updateInfo("[INFO]   Drone "+drone_id+" aterrizando")
            msg = '{"type": "land"}'
            auxMethods.sendMessage(self.drones[drone_id]["Client"], msg, self.private_key, self.drones[drone_id]['public_key'])

        except Exception as e:
            self.drone_socket.close()
    
        pass

    def disconnect(self, droneId):

        try:
            msg = '{"type": "disconnect"}'
            res = auxMethods.sendMessage(self.drones[droneId]["Client"], msg, self.private_key, self.drones[droneId]['public_key'])
            if res["type"]=="disconnect":
                self.disconnectFromDrone(droneId)
                del self.drones[droneId]

        except Exception as e:
            self.drone_socket.close()

    def disconnectFromDrone(self, droneId):
        self.etApp.updateInfo("[INFO]   Drone "+droneId+" desconectado")
        self.etApp.removeDroneStatus(droneId)
        del self.drones[droneId]


    # ------------------------------MAIN PROGRAM------------------------------
# Main function that creates an ET and starts recieving
def main():
    et_name = 'ET-01'
    if len(sys.argv)>1:
        et_name = sys.argv[1]
    et = Station(et_name) 
    et.commands()


if __name__ == "__main__":
    main()
