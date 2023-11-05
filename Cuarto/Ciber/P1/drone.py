# Drones (DR), utilizados para detectar a los enanitos cautivos, 
# y poder diseñar un plan de rescate. Debido a su rango de comunicaciones, 
# sólo pueden conectarse a una estación de tierra.
import socket
import time
import json
import math
import auxMethods
import os
import npyscreen
import terminal
import sys
import threading

class Drone():
    bo_socket = None
    et_socket = None
    droneApp = None
    et_links = {}
    et_public_key = None
    state = "landed"
    battery = 100
    public_key = None
    private_key = None
    bo_public_key = None

    # Constructor for Drone
    def __init__(self, id):
        #Start the interface
        self.droneApp = terminal.DroneApp()
        threading.Thread(target=self.droneApp.run).start()

        # Create RSA public and private keys
        self.public_key, self.private_key = auxMethods.generate_keys()

        # Connect drone to BO
        self.droneApp.updateInfo("[INFO]    Para obtener una ID el drone debe conectarse a la BO")
        self.droneApp.updateInfo("[INFO]    Conectando con la BO...")
        self.bo_socket, self.id, self.bo_public_key = auxMethods.connectToBO(id, self.public_key)
        time.sleep(0.1)
        if self.bo_socket == None:
            self.droneApp.updateInfo("[ERROR]   No se ha encontrado la BO")
            self.droneApp.updateInfo("[INFO]    Saliendo de la aplicación")
            time.sleep(3)
            self.droneApp.die()
            os.system('clear')
            print("\n\n\n\t\tPress any button to return to terminal")
            # TODO que esto cierre totalmente la interfaz
            sys.exit(1)

        else:
            self.droneApp.updateInfo( "[OK]      Drone creado con id "+ str(self.id))
            self.droneApp.update_name(self.id)

        self.stop_event = threading.Event() # Event to stop the threads


    # ------------------------------COMMAND RECIEVER------------------------------
    # Main loop checking for commands
    def commands(self):
        while not self.stop_event.is_set():
            if self.droneApp.command!="":
                # Parse command and args
                command = self.droneApp.command.split(" ")

                #Case command is EXIT
                if command[0] == "exit":
                    self.exit_command()         
                
                #Case command is LINK
                elif command[0] == "link":
                    if len(command) == 2:
                        self.link(command[1])
                    else:
                        self.droneApp.updateInfo("[HELP]    No se ha especificado la estación a enlazar, use: link <et_id>")

                #Case command is LINK
                elif command[0] == "unlink":
                    if len(command) == 2:
                        if command[1] in self.et_links.keys():
                            if self.et_public_key == self.et_links[command[1]][2]:
                                self.droneApp.updateInfo("[ERROR]    Desconecte previamente el drone y la et "+command[1])
                            else:
                                del self.et_links[command[1]]
                                self.droneApp.updateInfo("[OK]      El drone se ha desvinculado de la et : "+command[1])
                        else:
                            self.droneApp.updateInfo("[INFO]    El drone no esta vinculado a una ET con la id : "+command[1])
                    else:
                        self.droneApp.updateInfo("[HELP]    No se ha especificado la estación a enlazar, use: link <et_id>")


                #Case command is CONNECT
                elif command[0] == "connect":
                    if len(command) == 2:
                        if command[1] not in self.et_links.keys():
                            self.droneApp.updateInfo("[ERROR]   No se ha enlazado con la estación: "+command[1])
                        self.connect(command[1])
                    else:
                        self.droneApp.updateInfo("[HELP]    No se ha especificado la estación a conectar, use: connect <et_id>")
                        
                #Case command is DISCONNECT
                elif command[0] == "disconnect":
                    self.disconnect()
                    
                        
                # Case command is HELP
                elif command[0] == "help":
                    # Show information on how to use the drone interface
                    self.droneApp.updateInfo("[HELP]    Comandos posibles: link <et_id>, connect <et_id>, disconnect, exit")
                
                # Case command is not recognised
                else:
                    self.droneApp.updateInfo("[ERROR]   Comando no reconocido")

                # Reset the command variable
                self.droneApp.command=""

    # ------------------------------COMMAND HANDLER------------------------------
    # Chequea la existencia de una ET y la añade a la lista et_links
    def link(self, et_id):
        # Comprobar si la estación está en la lista de enlaces
        if et_id in self.et_links:
            self.droneApp.updateInfo("[INFO]    Ya está conectado a la estación "+et_id)
            # TODO comprobar que sigue existiendo la estación
            return
        
        # Preguntar a BO por la IP y puerto de la estación
        msg = '{"type": "link", "element":"et", "id":"' + et_id + '"} '
        res = auxMethods.sendRequest(self.bo_socket, msg)

        if res != None:
            if res["connection"] == True:
                # Si la estación existe, guardamos los datos en la lista de links
                self.et_links[et_id] = (res["ip"], int(res["port"]), res["public_key"])
                self.droneApp.updateInfo("[OK]      Link a la estación: "+str(et_id))
            
            else:
                self.droneApp.updateInfo("[ERROR]   No se ha podido enlazar a la estación: "+str(et_id))

        else:
            self.droneApp.updateInfo("[ERROR]   La estación: "+str(et_id) + " no existe")
            return

    # Conecta el socket de comunicacion conla ET del drone
    def connect(self, et_id):
        if self.et_socket!=None:
            self.droneApp.updateInfo("[ERROR]   El drone ya esta conectado a una estacion. ")
            return 
        # Comprobar si la estación está en la lista de enlaces
        if et_id not in self.et_links:
            self.droneApp.updateInfo("[ERROR]   No se ha podido conectar a la estación: "+str(et_id))
            return
        
        # Create socket for ET communication
        self.et_socket = socket.socket()
        
        try:
            # Conectamos socket ET con las direcciones de ET obtenidas de et_links
            self.et_socket.connect((self.et_links[et_id][0], self.et_links[et_id][1]))

        except Exception as e:
            self.droneApp.updateInfo("[ERROR]   Connect exception: "+str(et_id))
            self.et_socket = None
            return
        
        # Enviamos msg de conectar a ET
        msg= '{"type": "connect", "element":"drone", "id":"' + self.id + '", "public_key":"' + self.public_key + '"} '
        res = auxMethods.sendRequest(self.et_socket, msg)
        if res != None:
            if res["connection"] == True:
                self.et_public_key = self.et_links[et_id][2]
                # Lanzamos un hilo que escuche de ET
                threading.Thread(target=self.listen_et).start()
                # Lanzamos un hilo que envie la telemetry a la ET
                threading.Thread(target=self.telemetry).start()
                self.droneApp.updateInfo("[OK]      Conectado con la estacion : "+str(et_id))
            else:
                self.droneApp.updateInfo("[ERROR]    No se ha podido conectar a la estación: "+str(et_id))
        
    # Desconecta el drone de la ET a la que esta conectada
    def disconnect(self):
        if self.et_socket:
            self.state = "landed"
            self.droneApp.updateStatus(auxMethods.droneStatusMsg(self.battery, self.state))
            auxMethods.sendMessage(self.et_socket, '{"type":"disconnect", "id":"'+self.id+'"}', self.private_key, self.et_public_key)
            self.et_socket.close()
            self.et_socket = None
            self.et_public_key = None
            self.droneApp.updateInfo("[INFO]    Desconectado de la estación")
        else:
            self.droneApp.updateInfo("[INFO]      No hay ninguna estación conectada")

    # ------------------------------ET HANDLER------------------------------
    # Listens to the messages comming from the ET and process them
    def listen_et(self):
        while not self.stop_event.is_set():

            if self.et_socket==None:
                break

            if self.et_socket.fileno() == -1:
                continue
            
            # Listen to the socket until response or disconection
            res = auxMethods.listen_socket(self.et_socket, self.private_key, self.et_public_key)
            if res != None:
                if 'type' in res:

                    # Fly command
                    if res['type'] == 'fly':
                        self.fly()

                    # Land command
                    elif res['type'] == 'land':
                        self.land()

                    # Disconnect command
                    elif res['type'] == 'disconnect':
                        self.disconnect()

                    # Shutdown command
                    elif res['type'] == 'shutdown':
                        self.shutdown()

                    else:
                        auxMethods.sendMessage(self.et_socket, '{"type":"response", "msg":"command not recognized"}', self.private_key, self.et_public_key)
            else:
                self.et_socket = None
                self.droneApp.updateInfo("[INFO]     Conexion con la estacion cerrada")
                break

    # Send periodical message to the ET indicating the state of the drone
    def telemetry(self):
        try:
            while not self.stop_event.is_set():
                if self.et_socket!=None:
                    # Send a message to the ET containing the telemetry
                    msg = '{"type": "telemetry", "s":"' + self.state + '","b":'+ str(math.ceil(self.battery)) + '}'
                    auxMethods.sendMessage(self.et_socket, msg, self.private_key, self.et_public_key)
                    self.droneApp.updateStatus(auxMethods.droneStatusMsg(self.battery, self.state))
                    
                    # Update battery 

                    # If drone is flying or returning to base, discharge at a rate of 100% in a minute
                    if self.state=="flying" or self.state == "returning":
                        # TODO volver a incorporar el rate correcto (abajo)
                        #self.battery-=100/60
                        self.battery-=10
                        if self.battery<=0:
                            self.battery=0
                            self.state="landed"
                        elif self.battery<=20:
                            self.state = "returning"

                    # If drone is at the base and not fully charge charge the drone
                    elif self.battery<100:
                        # TODO cambiar la rate de carga?
                        self.battery+=20
                        self.state="charging"

                    # If drone is at base and fully charged, enter Standby Mode
                    else:
                        self.battery=100                    
                        self.droneApp.updateInfo("[INFO]    Drone en base cargado al 100%")
                        self.droneApp.updateInfo("[INFO]    Modo Standby activado")

                        # Set state to landed and send one last telemetry
                        self.state="landed"
                        msg = '{"type": "telemetry", "s":"' + self.state + '","b":'+ str(math.ceil(self.battery)) + '}'
                        auxMethods.sendMessage(self.et_socket, msg, self.private_key, self.et_public_key)

                        # Stop sending telemetry to ET while in Standby Mode
                        while self.state == "landed":
                            pass
                else:
                    break
                # Wait to seecond lapse between telemetries
                time.sleep(2)

        except Exception as e:
            self.droneApp.updateInfo("Telemetry exception: "+str(e))
            self.et_socket.close()
    
    # ------------------------------DRONE HANDLER------------------------------
    # Function that makes a drone fly
    def fly(self):
        # We set the state to flying 
        self.state = "flying"
        self.droneApp.updateInfo('[INFO]    Volando por orden de ET ' + self.id)
        msg = '{"type": "response", "msg":"Drone flying"}'
        auxMethods.sendMessage(self.et_socket, msg, self.private_key, self.et_public_key)

    def land(self):
        self.state = "landed"
        self.droneApp.updateInfo('[INFO]   Aterrizando por orden de ET ' + self.id)
        # msg = '{"type": "response", "msg":"Drone with id: '+str(self.id)+' landed"}'
        msg = '{"type": "response", "msg":"Drone with id: landed"}'
        auxMethods.sendMessage(self.et_socket, msg, self.private_key, self.et_public_key)


    def exit_command(self):
        self.stop_event.set()                       # Stop threads
        if self.et_socket != None:
            self.et_socket.shutdown(socket.SHUT_RD)
            self.et_socket.close()                      # Close socket
        self.bo_socket.close()                      # Close socket
        self.droneApp.die()                            # Close interface
        os.system('clear')                          # Clear terminal
        print("\n\n\n\t\tPress any button to return to terminal")
        sys.exit(0)      

    def shutdown(self):
        self.state = "landed"
        self.droneApp.updateInfo('Landing drone: ' + self.id + "    ( ╥﹏╥)")
        self.exit_command()


# Main function that creates a drone and starts recieving
def main():
    drone_name = 'DR-01'
    if len(sys.argv)>1:
        drone_name = sys.argv[1]
    drone = Drone(drone_name)
    drone.commands()


if __name__ == "__main__":
    main()




