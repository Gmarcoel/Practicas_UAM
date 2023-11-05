# Base de operaciones (BO), donde los jefazos de la UREJ controlan 
# todos los elementos del sistema, y diseñan las operaciones. 
# Solo existe una BO en toda la red.
# Estaciones de tierra (ET), que constituyen los elementos básicos de la red.
import socket
import os
from _thread import *
import time
import sys
import json
import auxMethods
import random
import string
import terminal
import threading



# Estación terrestre (ET)
class Base():
    ets={} # Dictionary of ets format ets[id] = {"socket":socket, "ip":ip, "port":port}
    drones={} # Dictionary of drones format drones[id] = socket

    public_key = None
    private_key = None
    # Constructor
    def __init__(self, host='127.0.0.1', port=auxMethods.port):

        # Create the interface
        self.boApp = terminal.BoApp()
        app_thread = threading.Thread(target=self.boApp.run)
        app_thread.start()
        self.stop_event = threading.Event() # Event to stop the threads

        # Create RSA public and private keys
        self.public_key, self.private_key = auxMethods.generate_keys()

        # Create the socket to listen for connections
        self.bo_socket = socket.socket()
        self.host = host
        self.port = port
        while True:
            try:
                self.bo_socket.bind((host, self.port))
                break
            except socket.error as e:
                self.port+=1
        
        # Save bo in secret file
        with open('.bo.txt', 'w') as f:
            f.write(self.host+':'+str(self.port))
            f.close()
        
        self.bo_socket.listen(10)
        
        # Wait until interface is ready
        time.sleep(0.05)
        self.boApp.updateInfo("[INFO]   BO created\n\thost: "+self.host+"\n\tPort: "+str(self.port))
        

    # ------------------------------LISTEN SOCKETS------------------------------
    # Listen for new connections
    def listen(self):
        while not self.stop_event.is_set(): # Stop event to stop the thread from "exit" command
            # Accept connection
            Client, address = self.bo_socket.accept()
            msg = Client.recv(1024).decode('utf-8')
            msg = json.loads(msg)

            # Check if the connection is a drone or an et
            if msg['type'] == 'create':
                if msg['element']=='drone':
                    prefix="DR-"
                    existing = self.drones.keys()
                elif msg['element']=='et':
                    prefix="ET-"
                    existing = self.ets.keys()
                result = msg['id']
                while result in existing or result == "BO" or ' ' in result:
                    # Define the length of the random portion of the string
                    random_len = 4
                    # Generate a random string of uppercase letters and digits
                    random_chars = ''.join(random.choices(string.ascii_uppercase + string.digits, k=random_len))
                    # Combine the random string with the fixed prefix "DR"
                    result = prefix + random_chars

                # If drone add to drones list, send id, and start listening to it
                if msg['element']=='drone':
                    self.drones[result]= {"socket":Client, "public_key":msg['public_key']}
                    Client.send(str.encode('{"type":"id", "id":"'+result+'", "public_key":"'+self.public_key+'"}'))
                    self.boApp.updateInfo( "[OK]     Connected to drone ("+result+") at "+ address[0] + ':' + str(address[1]))
                    threading.Thread(target=self.listen_drone, args=(self.drones[result]['socket'], result)).start()
                # If et add to ets dictionary, send id and start listening to it
                elif msg['element']=='et':
                    self.ets[result]= {"socket":Client, "ip":msg['ip'], "port":msg['port'], "public_key":msg['public_key']}
                    Client.send(str.encode('{"type":"id", "id":"'+result+'", "public_key":"'+self.public_key+'"}'))
                    self.boApp.updateInfo( "[OK]     Connected to ET ("+result+") at "+ address[0] + ':' + str(address[1]))
                    threading.Thread(target=self.listen_et, args=(self.ets[result]['socket'], result)).start()

    # Listen for messages from drones
    def listen_drone(self, connection, droneId):
        while not self.stop_event.is_set(): # Stop event to stop the thread from "exit" command
            msg = auxMethods.listen_socket(connection)
            if msg != None:
                if msg['type'] == 'link':
                    # Check if the destiny ET exists in the BO database
                    if msg['id'] in list(self.ets.keys()):
                        # If it exist we reespond accepting the connection and sending the ip and port for the drone to connect
                        et = self.ets[msg['id']]
                        auxMethods.sendMessage(connection, '{"type":"response","connection": true, "ip":"'+et['ip']+'", "port":"'+str(et['port'])+ '", "public_key":"' + et['public_key'] + '"}')
                    else:
                        # If the ET is not in the database we respond with a failed connection
                        auxMethods.sendMessage(connection, '{"type":"response","connection": false}')

            
            else:
                if not self.stop_event.is_set():
                    self.boApp.updateInfo("[INFO]   Drone disconnected")
                break

    # Listen for messages from ets
    def listen_et(self, connection, etId):
        flag = False
        while not self.stop_event.is_set(): # Stop event to stop the thread from "exit" command
            msg = auxMethods.listen_socket(connection, self.private_key, self.ets[etId]['public_key'])
            if msg != None:
                if msg['type'] == 'unlink':

                    # Delete the et from the database
                    for et in self.ets:
                        if self.ets[et]["socket"] == connection:
                            del self.ets[et]
                            self.boApp.updateInfo("[INFO]   Et " + et + " disconnected")
                            # auxMethods.sendMessage(connection, '{"type":"response","connection": true}', self.private_key, self.ets[et]["public_key"])
                            flag = True
                            return
                            break
                
                # Link to send msg between ets
                if msg['type'] == 'link':
                    # Check if the destiny ET exists in the BO database
                    if msg['id'] in list(self.ets.keys()):
                        # If it exist we reespond accepting the connection and sending the ip and port for the drone to connect
                        et = self.ets[msg['id']]
                        auxMethods.sendMessage(connection, '{"type":"response","connection": true, "ip":"'+et['ip']+'", "port":"'+str(et['port'])+'", "public_key":"' + et['public_key'] + '"}')                        

                    else:
                        # If the ET is not in the database we respond with a failed connection
                        auxMethods.sendMessage(connection, '{"type":"response","connection": false}')
                
                # Receive message from ET
                if msg['type'] == 'sm':
                    # Show message in the interface
                    self.boApp.updateInfo("[INFO]   Message from ET "+ msg['id'] +": " + msg['msg'])

                elif msg['type'] == 'sf':
                    # 
                    self.boApp.updateInfo("[INFO]   ET "+etId+" is sending a file called: "+msg['n'])
                    # If directory does not exist, create it
                    if not os.path.exists('BO_downloads'):
                        os.makedirs('BO_downloads')
                    # Open file to write
                    file = open('BO_downloads/'+msg['n'], 'w')
                    # Recieve file

                    data = ""
                    i=0
                    while i<msg['c']:
                        res = auxMethods.listen_socket(connection, self.private_key, self.ets[etId]["public_key"])
                        if res == None:
                            auxMethods.sendMessage(connection, '{"type":"response","msg":"Chunk not received"}', self.private_key, self.ets[etId]["public_key"])
                            continue
                        auxMethods.sendMessage(connection, '{"type":"response","msg":"Chunk received"}', self.private_key, self.ets[etId]["public_key"])
                        
                        if res['type'] == "c":
                            data = data + res['d'][2:-1]
                            i+=1

                    file.write(data)
                    file.close()
                    self.boApp.updateInfo("[INFO]   Downloaded file "+msg['n']+" sent by "+etId)
                
                else:
                    auxMethods.sendMessage(connection, '{"type":"response", "msg":"incorrect command"}', self.private_key, self.ets[etId]["public_key"])
            
            else:
                if not self.stop_event.is_set() and not flag:
                    self.boApp.updateInfo("[INFO]   Et disconnected")
                    for et in self.ets:
                        if self.ets[et]["socket"] == connection:
                            del self.ets[et]
                            break
                break
    
    # ------------------------------COMMAND RECIEVER------------------------------
    # Main loop checking for commands
    def commands(self):
        while True:

            if self.boApp.command!="":

                # Parse command and args
                command = self.boApp.command.split(" ")


                #Case command is EXIT
                if command[0] == "exit":
                    self.exit_command() 

                # Case command is HELP
                # TODO añadir comandos q faltan
                elif command[0] == "help":
                    self.boApp.updateInfo("[INFO]   Possible commands: fly <et_id>, land <et_id>, exit")

                # Case command is FLY
                elif command[0] == "fly":
                    if len(command) != 2:
                        self.boApp.updateInfo("[INFO]   Drone no especificado. Uso: fly <drone_id>")
                    else:
                        self.fly(command[1])

                # Case command is LAND
                elif command[0] == "land":
                    if len(command) != 2:
                        self.boApp.updateInfo("[INFO]   Drone no especificado. Uso: land <drone_id>")
                    else:
                        self.land(command[1])
                    
                # Case command is SEND_MSG/FILE
                elif command[0] == "send":
                    # Case command is SEND_MSG
                    if command[1] == "msg":
                        if command[2] in list(self.ets.keys()):
                            self.send_msg(command[2], ' '.join(command[3:]))
                        else:
                            self.boApp.updateInfo("[ERROR]  Et no encontrado")
                    # Case command is SEND_FILE
                    elif command[1] == "file":
                        if command[2] in list(self.ets.keys()):
                            self.send_file(command[2], command[3])
                        else:
                            self.boApp.updateInfo("[ERROR]  Et no encontrado")
                        # self.send_file(command[2], command[3])

                # Case command is GET_STATUS
                elif command[0] == "status":
                    self.get_status()

                # TODO Case command is SHUTDOWN
                elif command[0] == "shutdown":
                    self.shutdown()
                    break

                # Case command is not recognised
                else:
                    self.boApp.updateInfo("[ERROR]    Comando no reconocido")

                # Reset the command variable
                self.boApp.command=""

    # Assigns a valid ID to the entrant conection and handles it
    def assign_id(self, Client, msg):

        # Checks if the message type is CREATE
        if msg['type'] == 'create':

            # Checks the element we are about to create and sets the list of existings and the prefix according
            if msg['element']=='drone':
                prefix="DR-"
                existing = self.drones
            elif msg['element']=='et':
                prefix="ET-"
                existing = self.ets.keys()

            # We get the proposed ID 
            result = msg['id']

            # We check if it is valid and not taken and in case it is not we generate a new one until it is valid
            while result in existing:
                random_len = 4
                random_chars = ''.join(random.choices(string.ascii_uppercase + string.digits, k=random_len))
                result = prefix + random_chars

            # Check again for the type of element
            if msg['element']=='drone':
                # In case it is a drone element we send the final ID and start a thread to handle future events for the drone
                self.drones[result] = {"socket":Client, "public_key":msg['public_key']}
                auxMethods.sendMessage(Client, '{"type":"id", "id":"'+result+'"}')
                start_new_thread(self.listen_drone, (Client,))
            
            elif msg['element']=='et':                
                # In case it is a ET element we send the final ID, store the ET on our database and throw a new thread to handle ET events
                self.ets[result]= {"socket":Client, "ip":msg['ip'], "port":msg['port'],"public_key":msg['public_key']}
                auxMethods.sendMessage(Client, '{"type":"id", "id":"'+result+'"}')
                
    def send_msg(self, et_id, content):

        # Check if the ET is in the database
        if et_id not in self.ets.keys():
            self.boApp.updateInfo("[ERROR]    No existe la estación: "+str(et_id))
            return
        
        # Send the message to the ET
        auxMethods.sendMessage(self.ets[et_id]["socket"], '{"type":"send_msg", "msg":"'+content+'"}', self.private_key, self.ets[et_id]["public_key"])


    # Mensaje SEND_FILE: envia fichero a otra ET.
    def send_file(self, et_id, file_path):
        
        # Check if ET is linked to the BO
        if et_id not in self.ets.keys():
            self.boApp.updateInfo("[ERROR]    Esta estación no está conectada a la bo. Usar comando 'link' desde la ET")
            return

        et_socket = self.ets[et_id]["socket"]
        
        try:
            with open(file_path, "r") as f:
                file_content = f.read()
        except Exception as e:
            self.boApp.updateInfo("[ERROR]    No se ha podido leer el fichero")
            return
        file_name = file_path.split("/")[-1]
        file_content = str.encode(file_content, encoding='utf-8')
        file_chunks = [file_content[i:i+32] for i in range(0, len(file_content), 32)]
        chunk_id=0
        msg = '{"type": "send_file", "file_name":"'+ file_name +'", "chunks": '+str(len(file_chunks))+'} '
        try:
            auxMethods.sendMessage(et_socket, msg, self.private_key, self.ets[et_id]["public_key"])
        except Exception as e:
            self.boApp.updateInfo("[ERROR]    "+e)
            return

        while chunk_id < len(file_chunks):
            msg = '{"type": "chunk", "data": "'+str(file_chunks[chunk_id])+'"} '
            res = auxMethods.sendRequest(et_socket, msg)
            if res["type"]=="response" and res["msg"]=="Chunk received":
                chunk_id+=1
            self.boApp.updateInfo(msg)

        auxMethods.sendMessage(et_socket, msg, self.private_key, self.ets[et_id]["public_key"])


    def fly(self, drone_id):
        for et in self.ets.keys():
            res = auxMethods.sendRequest(self.ets[et]["socket"], '{"type":"fly", "drone_id":"'+drone_id+'"}', self.private_key, self.ets[et]["public_key"])
            if res["type"] == "Success":
                self.boApp.updateInfo("El drone con id: "+drone_id+" conectado a la ET: "+et+" esta volando")
                return
        self.boApp.updateInfo("El drone con id: "+drone_id+" no se ha encontrado en ninguna ET activa")

    def land(self, drone_id):
        for et in self.ets.keys():
            res = auxMethods.sendRequest(self.ets[et]["socket"], '{"type":"land", "drone_id":"'+drone_id+'"}', self.private_key, self.ets[et]["public_key"])
            if res["type"] == "Success":
                self.boApp.updateInfo("El drone con id: "+drone_id+" conectado a la ET: "+et+" esta en tierra")
                return
        self.boApp.updateInfo("El drone con id: "+drone_id+" no se ha encontrado en ninguna ET activa")

    def get_status(self):
        status_msg = []
        for et in self.ets.keys():
            status_msg.append("----- "+et+" - Connected")
            msg = '{"type":"get_status"}'
            res = None
            
            auxMethods.sendMessage(self.ets[et]["socket"], msg, self.private_key, self.ets[et]["public_key"])
            time.sleep(0.1)
            while res == None:
                res = auxMethods.listen_socket(self.ets[et]["socket"], self.private_key, self.ets[et]["public_key"])
                self.boApp.updateInfo(res)
            # get chunks from res
            chuncks = res["chunks"]
            chunk_id = 0
            while chunk_id < chuncks:
                # Listen for the chunk
                msg = None
                while msg == None:
                    msg = auxMethods.listen_socket(self.ets[et]["socket"], self.private_key, self.ets[et]["public_key"])
                self.boApp.updateInfo(msg)
                auxMethods.sendMessage(self.ets[et]["socket"], '{"type":"response", "msg":"Chunk received"}', self.private_key, self.ets[et]["public_key"])
                if msg["type"] == "chunk":
                    status_msg.append(msg["data"])
                    chunk_id+=1
            # res = auxMethods.sendRequest(self.ets[et]["socket"], msg, self.private_key, self.ets[et]["public_key"])
            # for drone in res.keys():
            #     status_msg.append("- "+drone+" - "+res[drone])
        self.boApp.updateStatus(status_msg)


    def exit_command(self):
        self.stop_event.set()                       # Stop threads
        self.bo_socket.shutdown(socket.SHUT_RD)     # Stop listening
        # Stop listening all drones
        for drone in self.drones:
            try:
                self.drones[drone]['socket'].shutdown(socket.SHUT_RD)
            except:
                pass
        # Stop listening all ets
        for et in self.ets:
            if self.ets[et]["socket"] != None:
                self.ets[et]["socket"].shutdown(socket.SHUT_RD)
        self.bo_socket.close()                      # Close socket
        self.boApp.die()                            # Close interface
        os.system('clear')                          # Clear terminal
        print("\n\n\n\t\tPress any button to return to terminal")
        sys.exit(0)     

    def shutdown(self):
        for et in self.ets.keys():
            auxMethods.sendMessage(self.ets[et]["socket"], '{"type":"shutdown"}', self.private_key, self.ets[et]["public_key"])
        

        self.exit_command()

    # ------------------------------MAIN PROGRAM------------------------------
# Main function that creates an ET and starts recieving
def main():
    bo = Base()
    threading.Thread(target=bo.listen).start()
    bo.commands()


if __name__ == "__main__":
    main()
