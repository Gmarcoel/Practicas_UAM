import socket

class Discovery:
    socket = None
    HOST = 'vega.ii.uam.es'  # The server's hostname or IP address
    PORT = 8000                       # The port used by the server
    buf = ""

    def __init__ (self):
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.connect((self.HOST,  self.PORT))

    """
    Función REGISTER
    Objetivo: Registrar a un usuario en el sistema. También sirve para cambiar el nick de un usuario existente.
    Comando: REGISTER nick ip_address port password protocol
    Posibles respuestas/errores:
        OK WELCOME nick ts : El registro o actualización del nick se ha realizado correctamente. ts contiene el nuevo instante de registro (en formato UNIX)
        NOK WRONG_PASS : El nick es válido, pero la contraseña proporcionada es errónea

    """
    def register(self, nick, ip, port, password, supports):
        msg = "REGISTER " + nick + " " + ip + " " + str(port) +" "+ str(password) +" "+ supports
        



        # If not connected, connect to the server
        if not self.socket:
            self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.socket.connect((self.HOST,  self.PORT))
        
        # Send petition to server
        self.socket.sendall(bytes(msg, 'utf-8'))

        # Response from server
        data = self.socket.recv(1024)
        data = data.decode('utf-8')
        data = data.split(' ')

        # Response from server
        if data and data[0]=='OK':
            print("OK WELCOME " + data[2] + data[3])
            return data
        else:
            print("NOK WRONG_PASS")
            return None


    """
    Función QUERY
    Objetivo: Permite obtener la dirección IP y puerto de un usuario conociendo su nick
    Comando: QUERY name
    Posibles respuestas/errores:
        OK USER_FOUND nick ip_address port protocols : Devuelve información sobre el usuario.protocols contiene todos los protocolos soportados por ese cliente, separados por '#'.
        NOK USER_UNKNOWN
    """
    def query(self, name):
        if name == None:
            return

        msg = "QUERY "+ name
        


        # If not connected, connect to the server
        if not self.socket:
            self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.socket.connect((self.HOST,  self.PORT))
        
        # Send petition to server
        self.socket.sendall(bytes(msg, 'utf-8'))
        
        # Response from server
        data = self.socket.recv(1024)
        data = data.decode('utf-8')
        data = data.split(' ')

        # Response from server
        if data and data[0] == 'OK':
            #print("OK USER_FOUND " + data.nick + data.ip + data.port + data.protocols)
            return [data[3], data[4]]
        else:
            print("NOK USER_UNKNOWN")
            return None

    """
    Función LIST_USERS
    Objetivo: Listar todos los usuarios registrados en el sistema
    Comando: LIST_USERS
    Posibles respuestas/errores:
        OK USERS_LIST user1#user2#...#usern# : Devuelve una lista de los usuarios registrados en el sistema, mostrando para cada uno la información devuelta por el comando QUERY, separados por el símbolo '#'
        NOK USER_UNKNOWN
    """
    def list_users(self):
        msg = "LIST_USERS"
        


        # If not connected, connect to the server
        if not self.socket:
            self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.socket.connect((self.HOST,  self.PORT))
        
    

        try:
            self.socket.send(bytes(msg, 'utf-8'))
            msg = self.socket.recv(1024)
            msg = msg.decode('utf-8')
        except Exception as e:
            print("Error de conexion: ", e)
            return None
        if msg == None:
            print('Error al recibir el mensaje')
            return
        d = []
        users = msg.split("#")
        user = users[0].split(" ")
        if user[0] != "OK":
            print("Error al recibir el mensaje")
            return
        while len(users)-1 < int(user[2]):
            msg=msg+self.socket.recv(1024).decode('utf-8')
            users = msg.split('#')
            user = users[0].split(" ")

        size = int(user[2])
        if size > 0:
            nick = user[3]
            ip = user[4]
            port = user[5]
            d.append([nick, ip, port])
            
        if size < 2:
            return d
        
        for i in range(1, size - 1):
            user = users[i].split(" ")
            nick = user[0]
            ip = user[1]
            port = user[2]
            d.append([nick, ip, port])
        
        return d

    """
    Función QUIT
    Objetivo: Señalizar el cierre de la conexión con el servidor
    Comando: QUIT
    Posibles respuestas/errores:
        BYE
    """
    def quit(self):
        msg = "QUIT"
        
        # If not connected, connect to the server
        if not self.socket:
            self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.socket.connect((self.HOST,  self.PORT))
        
        # Send petition to server
        self.socket.sendall(bytes(msg, 'utf-8'))
        
        # Response from server
        data = self.socket.recv(1024)
        data = data.decode('utf-8')
        # Response from server
        print('Received', data)
        print("BYE")
        self.socket.close()
        return data
        