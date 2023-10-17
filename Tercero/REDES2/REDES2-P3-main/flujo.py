import numpy as np
import cv2


def comprimir(img):
    # Compresión JPG al 50% de resolución (se puede variar)
    encode_param = [cv2.IMWRITE_JPEG_QUALITY,50]
    result,encimg = cv2.imencode('.jpg',img,encode_param)
    if result == False: print('Error al codificar imagen')
    encimg = encimg.tostring()
    """msg = orde+"#"+time.time()+"#"+res+"#"+self.fps)
    msg = msg.encode() + encimg.tostring()
    orde += 1"""
    return encimg

# Los datos "encimg" ya están listos para su envío por la red
# enviar(encimg)

def descomprimir(encimg):
    img = cv2.imdecode(np.frombuffer(encimg,np.uint8),1)
    return img

#  sudo sysctl -w net.inet.udp.maxdgram=65535