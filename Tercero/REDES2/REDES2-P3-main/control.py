import socket

class Control:
    IP = ""
    PORT = ""

    socket = None
    socket_recibir = None

    def __init__(self, IP, PORT):
        # self.IP = IP
        # self.PORT = PORT

        # Creamos el socket para recibir llamadas
        self.socket_recibir = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket_recibir.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        # self.socket.connect((self.IP, self.PORT))
        self.socket_recibir.bind(('', PORT))
        self.socket_recibir.listen(5)

    """
    Comando CALLING

    Objetivo: Señalizar que un nodo quiere establecer una videollamada con otro
    Sintaxis: CALLING nick srcUDPport, donde srcUDPport es el puerto UDP en el que el llamante desea recibir el video del llamado.
    Posibles respuestas/errores:

        CALL_ACCEPTED nick dstUDPport, donde dstUDPport es donde el llamado recibirá el video
        CALL_DENIED nick 
        CALL_BUSY, el llamado está en una llamada y no puede recibir la comunicación. 
    """
    def calling(self, nick, ip, port, srcUDPport):
        command = "CALLING " + nick + " " + str(srcUDPport)
        
        # Create a tcp socket
        if self.socket:
            self.socket.close()
            self.socket = None
        self.IP = ip
        self.PORT = port
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.connect((ip, int(port)))

        self.socket.send(bytes(command, 'utf-8'))
        return

    """
    Comando CALL_HOLD
    Objetivo: Señalizar que se desea pausar temporalmente una llamada, sin cortarla.
    Sintaxis: CALL_HOLD nick
    Posibles respuestas/errores: Ninguno
    """
    def call_hold(self, nick):
        command = "CALL_HOLD " + nick

        # Call the server
        if self.socket:
            self.socket.close()
            self.socket = None
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.connect((self.IP, int(self.PORT)))
        self.socket.send(bytes(command, 'utf-8'))

        self.close_socket()

        
        # No response
        return

    """
    Comando CALL_RESUME 
    Objetivo: Señalizar que se desea reanudar una llamada anteriormente pausada.
    Sintaxis: CALL_RESUME nick
    Posibles respuestas/errores: Ninguno
    """
    def call_resume(self, nick):
        command = "CALL_RESUME " + nick

        if self.socket:
            self.socket.close()
            self.socket = None
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.connect((self.IP, int(self.PORT)))
        
        self.socket.send(bytes(command, 'utf-8'))

        # No response
        return
        
    """
    Comando CALL_END
    Objetivo: Señalizar que se desea finalizar una llamada.
    Sintaxis: CALL_END nick
    Posibles respuestas/errores: Ninguno
    """
    def call_end(self, nick):
        command = "CALL_END " + nick


        if self.socket:
            self.socket.close()
            self.socket = None
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.connect((self.IP, int(self.PORT)))
        self.socket.send(bytes(command, 'utf-8'))

        self.close_socket()

        # No response
        return
        
    """
    Comando ACCEPT_CALL
    WIP
    """
    def accept_call(self, nick, ip, port, dstUDPport):
        command = "ACCEPT_CALL " + nick + " " + str(dstUDPport)

        # Create a tcp socket
        if self.socket:
            self.socket.close()
            self.socket = None
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        # print("Respondemos a ", ip, int(port))
        self.socket.connect((ip, int(port)))
        self.socket.send(bytes(command, 'utf-8'))

        # No response
        return

    # Funcion que espera la recepcion de llamadas TCP de otros usuarios
    def recibir(self):        
            # Receive data from client
            conn, address = self.socket_recibir.accept()
            with conn:
                # print(f"Connected by {address}")
                data = conn.recv(1024).decode('utf-8')
            
                # Split data
                data = data.split(" ")
                
                # Check the command
                """""""""
                if data[0] == "CALLING":
                    # Accept the call
                    self.accept_call(data[1], data[2])
                if data[0] == "CALL_HOLD":
                    # Hold the call
                    self.call_hold(data[1])
                if data[0] == "CALL_RESUME":
                    # Resume the call
                    self.call_resume(data[1])
                if data[0] == "CALL_END":
                    # End the call
                    self.call_end(data[1])
                if data[0] == "CALL_BUSY":
                    # Busy the call
                    self.call_busy(data[1])
                if data[0] == "CALL_ACCEPTED":
                    # Accept the call
                    self.call_accepted(data[1], data[2])
                if data[0] == "CALL_DENIED":
                    # Deny the call
                    self.call_denied(data[1])
                """
                return data
    


    """
    Comando CALL_DENIED
    WIP
    """
    def call_denied(self, nick, ip, port):
        command = "CALL_DENIED " + nick
        # Create a tcp socket
        if self.socket:
            self.socket.close()
            self.socket = None
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.connect((ip, int(port)))
        self.socket.send(bytes(command, 'utf-8'))


        self.socket.close()
        self.socket = None
        # No response
        return


    """
    Comando CALL_BUSY
    WIP
    """
    def call_busy(self, ip, port):
        command = "CALL_BUSY " 
        # Create a tcp socket
        if self.socket:
            self.socket.close()
            self.socket = None
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.connect((ip, int(port)))
        self.socket.send(bytes(command, 'utf-8'))


        self.socket.close()
        self.socket = None
        # No response
        return



    def close_socket(self):
        if self.socket:
            self.socket.close()
            self.socket = None