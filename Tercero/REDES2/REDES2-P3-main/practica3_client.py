# import the library
from appJar import gui
from PIL import Image, ImageTk
import numpy as np
import cv2
from flujo import comprimir, descomprimir
import threading
import udp
import discovery
import control
import socket

from control import Control

# La ip y puerto propio las dejo como globales un poco chapucero a ver si cambiamos
ip = None
puerto_ds = None
puerto_llamadas = None
puerto_udp = None
username = None

class VideoClient(object):
	discovery = None 
	control = None
	udp = None

	def __init__(self, window_size):
		# Añadimos discovery y control
		self.discovery = discovery.Discovery()
		self.udp = udp.Udp(60, self, "640x520")
		self.udp.vc=self

		# Creamos una variable que contenga el GUI principal
		self.app = gui("Redes2 - P2P", window_size)
		self.app.setGuiPadding(10,10)

		# Preparación del interfaz
		self.app.addLabel("title", "Cliente Multimedia P2P - Redes2 ")
		self.app.addImage("videoLocal", "imgs/loading.gif")
		#self.app.addImage("videoOnline", "imgs/webcam.gif")

		# Registramos la función de captura de video
		# Esta misma función también sirve para enviar un vídeo
		self.cap = cv2.VideoCapture(0) # 0 es la webcam
		#set poll time to have a frequency of 20 times per second
		self.app.setPollTime(60)
		self.app.registerEvent(self.capturaVideo)

		# Añadir los botones
		# self.app.addButtons(["Conectar", "Colgar", "Usuarios", "Salir"], self.buttonsCallback)
		self.app.addButtons(["Conectar", "Usuarios", "Salir"], self.buttonsCallback)
		

		# Barra de estado
		# Debe actualizarse con información útil sobre la llamada (duración, FPS, etc...)
		self.app.addStatusbar(fields=2)

		self.app.startSubWindow("Usuarios", modal=False)
		u = self.discovery.list_users()
		self.app.setFont(10)
		self.app.addListBox("list", u)
		"""for user in u:
			s="Nick: "+ str(user[0]) + "	IP: " +str(user[1]) + "	Port: " + str(user[2])+"\n"
			self.app.addLabel(s, s)"""
		

		self.app.stopSubWindow()

		self.app.startSubWindow("Llamada", modal=False)
		self.app.setFont(10)
		self.app.addImage("videoInternet", "imgs/loading.gif")
		self.app.addButtons(["Pausar", "Colgar", "Reanudar"], self.botones_llamada)
		self.app.stopSubWindow()


	def add_control(self, ip, port):
		self.control = control.Control(ip,port)


	def start(self):
		# Register
		vc.register_page()
		self.app.go()

	# Función que captura el frame a mostrar en cada momento
	def capturaVideo(self):
		
		# Capturamos un frame de la cámara o del vídeo
		ret, frame = self.cap.read()
		frame = cv2.resize(frame, (640,480))
		cv2_im = cv2.cvtColor(frame,cv2.COLOR_BGR2RGB)
		img_tk = ImageTk.PhotoImage(Image.fromarray(cv2_im))	    

		# Lo mostramos en el GUI
		self.app.setImageData("videoLocal", img_tk, fmt = 'PhotoImage')

		#if con una bandera que si estoy en llamada envio la frame por el socket 

		# Aquí tendría que el código que envia el frame a la red
		encimg = comprimir(frame)

		# Los datos "encimg" ya están listos para su envío por la red
		self.udp.send(encimg)


	# Establece la resolución de la imagen capturada
	def setImageResolution(self, resolution):		
		# Se establece la resolución de captura de la webcam
		# Puede añadirse algún valor superior si la cámara lo permite
		# pero no modificar estos
		if resolution == "LOW":
			self.cap.set(cv2.CAP_PROP_FRAME_WIDTH, 160) 
			self.cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 120) 
		elif resolution == "MEDIUM":
			self.cap.set(cv2.CAP_PROP_FRAME_WIDTH, 320) 
			self.cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 240) 
		elif resolution == "HIGH":
			self.cap.set(cv2.CAP_PROP_FRAME_WIDTH, 640) 
			self.cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)
				
	# Función que gestiona los callbacks de los botones
	def buttonsCallback(self, button):
		global puerto_udp, username

		if button == "Salir":
	    	# Salimos de la aplicación
			self.discovery.quit()
			self.app.stop()
			# exit program

		elif button == "Conectar":
	    	# Entrada del nick del usuario a conectar    
			nick = self.app.textBox("Conexión", 
	        	"Introduce el nick del usuario a buscar")
			connect_ip, connect_port = self.discovery.query(nick)
			self.control.calling(username, connect_ip, connect_port, puerto_udp)
			# Crear un pop up que pone llamando
			self.app.infoBox("Llamando a ", nick)
		elif button == "Usuarios":
			self.app.showSubWindow("Usuarios")


			"""
			# Entrada del nick del usuario a conectar    
			u = self.discovery.list_users()
			# Crear una tabla con los usuarios y sus datos en la subwindow
			s=""
			for user in u:
				s += str( "Nick: "+ str(user[0]) + "	IP: " +str(user[1]) + "	Port: " + str(user[2])+"\n")


			self.app.infoBox("Usuarios", s)
			"""
			
	def recibir_llamadas(self):
		while True:
			data = self.control.recibir()
			if data:
				if data[0] == "CALLING":
					# command = "CALLING " + nick + " " + srcUDPport
					nick = data[1]
					srcUDPport = data[2]
					# Crear una yesNo box para aceptar o rechazar la llamada
					c=self.app.yesNoBox("Llamada de", nick)
					connect_ip, connect_port = self.discovery.query(nick)
					# Si se acepta la llamada
					if c:
						p = data[2]
						# Crear una subwindow para mostrar el video de la llamada
						self.control.accept_call(username, connect_ip, connect_port, puerto_udp)
						self.app.showSubWindow("Llamada")
						# Mandar video
						self.udp.send_ip = connect_ip
						self.udp.send_port = p


						
					else:
						# Si no se acepta la llamada
						self.control.call_denied(username, connect_ip, connect_port)
				
				if data[0] == "ACCEPT_CALL":
					nick = data[1]
					p = data[2]
					# command = "CALL_ACCEPTED " + nick + " " + dstUDPport
					# Hacer que se abra la ventana de llamada
					self.app.showSubWindow("Llamada")
					# Mandar video
					connect_ip, connect_port = self.discovery.query(nick)
					self.udp.send_ip = connect_ip
					self.udp.send_port = p

				if data[0] == "CALL_DENIED":
					# command = "CALL_DENIED " + nick
					# Crear un pop up de llamada denegada
					self.app.infoBox("Denegada", "Llamada denegada por "+data[1])
					self.control.close_socket()

				if data[0] == "CALL_BUSY":
					# command = "CALL_BUSY"
					# Crear un pop up de llamada ocupada
					self.app.infoBox("Ocupado", "Llamada ocupada")
					self.control.close_socket()
				
				if data[0] == "CALL_HOLD":
					self.udp.send_ip = None

				if data[0] == "CALL_END":
					self.app.infoBox("Finalizada", "Llamada finalizada con "+data[1])
					self.udp.send_ip = None
					self.udp.send_port = None
					self.control.close_socket()
					self.app.hideSubWindow("Llamada")
				
				if data[0] == "CALL_RESUME":
					self.udp.send_ip = self.control.IP


	
	def botones_llamada(self, button):
		if button == 'Pausar':
			self.udp.send_ip = None
			# self.udp.send_port = None
			
		if button == 'Colgar':
			self.udp.send_ip = None
			self.udp.send_port = None
			self.control.call_end(username)
			self.app.hideSubWindow("Llamada")
		if button == 'Reanudar':
			self.udp.send_ip = self.control.IP
			self.control.call_resume(username)
	


	def register_page(self):


		# create a GUI variable called app
		self.app.startSubWindow("Registro", modal=True, blocking=True)


		self.app.addLabelEntry("Username")
		self.app.addLabelSecretEntry("Password")

		# link the buttons to the function called press
		self.app.addButtons(["Submit", "Cancel"], self.register_buttons)

		self.app.setFocus("Username")

		self.app.stopSubWindow()
		self.app.showSubWindow("Registro")
	# handle button events
	def register_buttons(self, button):
		global ip, puerto_ds, username
		if button == "Cancel":
			self.app.stop()
		else:
			usr = self.app.getEntry("Username")
			pwd = self.app.getEntry("Password")
			self.discovery.register(usr, ip,puerto_ds, pwd, "V0")
			username = usr
			#close the subwindow
			self.app.hideSubWindow("Registro")

					
if __name__ == '__main__':
	vc = VideoClient("640x520")
	# Crear aquí los threads de lectura, de recepción y,
	# en general, todo el código de inicialización que sea necesario

	# Obtenemos nuestra propia ip
	# h_name = socket.gethostname()
	# ip = socket.gethostbyname(h_name)
	s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	s.connect(("8.8.8.8",  80))
	ip = s.getsockname()[0]
	s.close()

	# Obtenemos un puerto de escucha
	puerto_ds = 20012
	puerto_llamadas = 20012
	puerto_udp = 8002
	# Creamos control del video client
	vc.add_control(ip, puerto_llamadas)
	
	# Crear thread de lectura
	thread_lectura = threading.Thread(target=vc.udp.listen, args=(ip, puerto_udp))
	thread_lectura.start()

	# Crear thread de recepción
	thread_recepcion = threading.Thread(target=vc.recibir_llamadas, args=())
	thread_recepcion.start()

	
	thread_buff = threading.Thread(target=vc.udp.rend, args=())
	thread_buff.daemon = True
	thread_buff.start()


	# Lanza el bucle principal del GUI
	# El control ya NO vuelve de esta función, por lo que todas las
	# acciones deberán ser gestionadas desde callbacks y threads
	vc.start()