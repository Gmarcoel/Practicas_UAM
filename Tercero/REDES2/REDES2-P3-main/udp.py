from mimetypes import init
import socket
import sys
from appJar import gui
from PIL import Image, ImageTk
import cv2
from buffer import BufferCircular
import flujo
import time

class Udp():
    send_ip = None
    send_port = None
    fps = 60
    BufferCircular = None
    vc = None
    num_ord = 0
    res = ""

    #init
    def __init__(self, fps, vc, res):
        self.fps = fps
        self.vc = vc
        self.num_ord=0
        self.res = res
        self.BufferCircular = BufferCircular(fps)


    def listen(self, ip, port):

        # Create a UDP socket
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        # Bind the socket to the port
        server_address = (ip, port)
        s.bind(server_address)

        while True:
            data, address = s.recvfrom(65536)
            cabecera = data.split(b'#', 4) # Criminal detenganlo
            img = flujo.descomprimir(cabecera[4])

            cv2_im = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
            img_tk = ImageTk.PhotoImage(Image.fromarray(cv2_im))
            #enviar el frame al buffer circular
            dic = {'ord': int(cabecera[0].decode()), 'time': float(cabecera[1].decode()), 'res': str(cabecera[2].decode()).split("x"), 'fps':int(cabecera[3].decode()), 'img': img_tk}
            self.BufferCircular.insertar(dic)
            #photo = ImageTk.PhotoImage(Image.open("imgs/webcam.gif"))

    def rend(self):
        while True:
            while self.send_ip and self.send_port:
                if self.BufferCircular.vacio() == True: 
                    continue
                
                if time.time() - self.BufferCircular.getTime() <= 2:
                    continue
                d=self.BufferCircular.extraer()
                img = d['img']
                self.vc.app.setImageData("videoInternet", img, fmt='PhotoImage')
                self.vc.app.setImageSize("videoInternet", d['res'][0], d['res'][1])
                self.vc.app.setStatusbar("FPS: "+str(d['fps']), 0)
                self.vc.app.setStatusbar("Delay: "+str(time.time() - d['time']), 1)



    def send(self,data):
        if not self.send_ip or not self.send_port:
            return
        # Create socket for server
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        address = (self.send_ip, int(self.send_port))
        # Let's send data through UDP protocol
        # BUFSIZE = 4024
        # msg = data
        # while msg:
        #     bytes_sent = s.sendto(msg[:BUFSIZE], address)
        #     msg = msg[bytes_sent:]
        msg = data
        self.num_ord+=1
        cabecera=str(self.num_ord)+"#"+str(time.time())+"#"+str(self.res)+"#"+str(self.fps)+"#"
        msg = cabecera.encode('utf-8')+msg
        s.sendto(msg, address)
        s.close()

