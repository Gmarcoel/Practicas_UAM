'''
    arp.py
    Implementación del protocolo ARP y funciones auxiliares que permiten realizar resoluciones de direcciones IP.
    Autor: Javier Ramos <javier.ramos@uam.es>
    2019 EPS-UAM
'''



from ethernet import *
import logging
import socket
import struct
import fcntl
import time
from threading import Lock
from expiringdict import ExpiringDict

#Semáforo global 
globalLock =Lock()
#Dirección de difusión (Broadcast)
broadcastAddr = bytes([0xFF]*6)
#Cabecera ARP común a peticiones y respuestas. Específica para la combinación Ethernet/IP
ARPHeader = bytes([0x00,0x01,0x08,0x00,0x06,0x04])
#longitud (en bytes) de la cabecera común ARP
ARP_HLEN = 6

#Variable que alamacenará que dirección IP se está intentando resolver
requestedIP = None
#Variable que alamacenará que dirección MAC resuelta o None si no se ha podido obtener
resolvedMAC = None
#Variable que alamacenará True mientras estemos esperando una respuesta ARP
awaitingResponse = False

#Variable para proteger la caché
cacheLock = Lock()
#Caché de ARP. Es un diccionario similar al estándar de Python solo que eliminará las entradas a los 10 segundos
cache = ExpiringDict(max_len=100, max_age_seconds=10)



def getIP(interface:str) -> int:
    '''
        Nombre: getIP
        Descripción: Esta función obtiene la dirección IP asociada a una interfaz. Esta funció NO debe ser modificada
        Argumentos:
            -interface: nombre de la interfaz
        Retorno: Entero de 32 bits con la dirección IP de la interfaz
    '''
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    ip = fcntl.ioctl(
        s.fileno(),
        0x8915,  # SIOCGIFADDR
        struct.pack('256s', (interface[:15].encode('utf-8')))
    )[20:24]
    s.close()
    return struct.unpack('!I',ip)[0]

def printCache()->None:
    '''
        Nombre: printCache
        Descripción: Esta función imprime la caché ARP
        Argumentos: Ninguno
        Retorno: Ninguno
    '''
    print('{:>12}\t\t{:>12}'.format('IP','MAC'))
    with cacheLock:
        for k in cache:
            if k in cache:
                print ('{:>12}\t\t{:>12}'.format(socket.inet_ntoa(struct.pack('!I',k)),':'.join(['{:02X}'.format(b) for b in cache[k]])))



def processARPRequest(data:bytes,MAC:bytes)->None:
    '''
        Nombre: processARPRequest
        Decripción: Esta función procesa una petición ARP. Esta función debe realizar, al menos, las siguientes tareas:
            -Extraer la MAC origen contenida en la petición ARP
            -Si la MAC origen de la trama ARP no es la misma que la recibida del nivel Ethernet retornar
            -Extraer la IP origen contenida en la petición ARP
            -Extraer la IP destino contenida en la petición ARP
            -Comprobar si la IP destino de la petición ARP es la propia IP:
                -Si no es la propia IP retornar
                -Si es la propia IP:
                    -Construir una respuesta ARP llamando a createARPReply (descripción más adelante)
                    -Enviar la respuesta ARP usando el nivel Ethernet (sendEthernetFrame)
        Argumentos:
            -data: bytearray con el contenido de la trama ARP (después de la cabecera común)
            -MAC: dirección MAC origen extraída por el nivel Ethernet
        Retorno: Ninguno
    '''
    #-Extraer la MAC origen contenida en la petición ARP
    MACOrigenPeticion=data[8:14]
    #-Si la MAC origen de la trama ARP no es la misma que la recibida del nivel Ethernet retornar
    if MAC!=MACOrigenPeticion:
        return
    #-Extraer la IP origen contenida en la petición ARP
    IPOrigenPeticion=data[14:18]
    #-Extraer la IP destino contenida en la petición ARP
    IPDestinoPeticion=data[24:28]
    #-Comprobar si la IP destino de la petición ARP es la propia IP:
    if IPDestinoPeticion!=myIP:
        #-Si no es la propia IP retornar
        return
    #-Si es la propia IP:
    else:
        #-Construir una respuesta ARP llamando a createARPReply (descripción más adelante)
        createARPReply(IPOrigenPeticion)
        #-Enviar la respuesta ARP usando el nivel Ethernet (sendEthernetFrame)
        sendEthernetFrame(data, len(data), 0x0806, MAC)
    return


def processARPReply(data:bytes,MAC:bytes)->None:
    '''
        Nombre: processARPReply
        Decripción: Esta función procesa una respuesta ARP. Esta función debe realizar, al menos, las siguientes tareas:
            -Extraer la MAC origen contenida en la petición ARP
            -Si la MAC origen de la trama ARP no es la misma que la recibida del nivel Ethernet retornar
            -Extraer la IP origen contenida en la petición ARP
            -Extraer la MAC destino contenida en la petición ARP
            -Extraer la IP destino contenida en la petición ARP
            -Comprobar si la IP destino de la petición ARP es la propia IP:
                -Si no es la propia IP retornar
                -Si es la propia IP:
                    -Comprobar si la IP origen se corresponde con la solicitada (requestedIP). Si no se corresponde retornar
                    -Copiar la MAC origen a la variable global resolvedMAC
                    -Añadir a la caché ARP la asociación MAC/IP.
                    -Cambiar el valor de la variable awaitingResponse a False
                    -Cambiar el valor de la variable requestedIP a None
        Las variables globales (requestedIP, awaitingResponse y resolvedMAC) son accedidas concurrentemente por la función ARPResolution y deben ser protegidas mediante un Lock.
        Argumentos:
            -data: bytearray con el contenido de la trama ARP (después de la cabecera común)
            -MAC: dirección MAC origen extraída por el nivel Ethernet
        Retorno: Ninguno
    '''
    global requestedIP,resolvedMAC,awaitingResponse,cache


    #-Extraer la MAC origen contenida en la petición ARP
    MACOrigenPeticion=data[8:14]
    #-Si la MAC origen de la trama ARP no es la misma que la recibida del nivel Ethernet retornar
    if MAC!=MACOrigenPeticion:
        return
    #-Extraer la IP origen contenida en la petición ARP
    IPOrigenPeticion=data[14:18]
    #-Extraer la MAC destino contenida en la petición ARP
    MACDestinoPeticion=data[18:24]
    #-Extraer la IP destino contenida en la petición ARP
    IPDestinoPeticion=data[24:28]
    #-Comprobar si la IP destino de la petición ARP es la propia IP:
    if IPDestinoPeticion!=myIP:
        #-Si no es la propia IP retornar
        return
    #-Si es la propia IP:
    else:
        #-Comprobar si la IP origen se corresponde con la solicitada (requestedIP). Si no se corresponde retornar
        if IPOrigenPeticion!=requestedIP:
            return
        #-Copiar la MAC origen a la variable global resolvedMAC
        resolvedMAC=MACOrigenPeticion
        #-Añadir a la caché ARP la asociación MAC/IP.
        cache.append(resolvedMAC,requestedIP)
        #-Cambiar el valor de la variable awaitingResponse a False
        awaitingResponse=False
        #-Cambiar el valor de la variable requestedIP a None
        requestedIP=None
    return
        



def createARPRequest(ip:int) -> bytes:
    '''
        Nombre: createARPRequest
        Descripción: Esta función construye una petición ARP y devuelve la trama con el contenido.
        Argumentos: 
            -ip: dirección a resolver 
        Retorno: Bytes con el contenido de la trama de petición ARP
    '''
    global myMAC,myIP
    frame = bytes()

    

    # Cabecera ARP
    # Hardware Type (2 Bytes): Indica el tipo de direcciones de nivel de enlace. En el caso de direcciones Ethernet este valor es 0x0001.
    hw = (0x0001).to_bytes(2,"big")
    # Protocol Type (2 Bytes): Indica el tipo de direcciones de nivel de red. En el caso de direcciones IP este valor es 0x0800.
    protocol = (0x0800).to_bytes(2,"big")
    # Hardware Size (1 Byte): Tamaño (en bytes) de las direcciones de nivel de enlace. En el caso de Ethernet este campo debe valer 6.
    hw_size = (6).to_bytes(1,"big")
    # Protocol Size (1 Byte): Tamaño (en bytes) de las direcciones de nivel de red. En el caso de IP este campo debe valer 4.
    protocol_size = (4).to_bytes(1,"big")
    # Opcode (2 Bytes): Indicador de operación ARP. Si el paquete ARP es una petición (Request) este campo vale 0x0001 mientras que si es una respuesta (Reply) este campo vale 0x0002.
    opcode = (0x0001).to_bytes(2,"big")
    # Sender Eth (6 Bytes): Dirección Ethernet del emisor del paquete ARP.
    etho = myMAC
    # Sender IP (4 Bytes): Dirección IP del emisor del paquete ARP.
    ipo = (myIP).to_bytes(4,"big")
    # Target Eth (6 bytes): Dirección Ethernet del receptor del paquete ARP. Si el Opcode del paquete es 1 este valor será la dirección nula (6 bytes a 0) ya que no se conoce cuál es la dirección Ethernet.
    ethdest = broadcastAddr
    # Target IP (4 Bytes): Dirección IP del receptor del paquete ARP.
    ipdest = (ip).to_bytes(4,"big")

    arp = hw + protocol + hw_size + protocol_size + opcode + etho + ipo + ethdest + ipdest

    # Cabecera ethernet
    # eth = ethdest + etho + hw

    # Trama
    frame = arp # + (0).to_bytes(18,"big")
    return frame


    
def createARPReply(IP:int ,MAC:bytes) -> bytes:
    '''
        Nombre: createARPReply
        Descripción: Esta función construye una respuesta ARP y devuelve la trama con el contenido.
        Argumentos: 
            -IP: dirección IP a la que contestar
            -MAC: dirección MAC a la que contestar
        Retorno: Bytes con el contenido de la trama de petición ARP
    '''
    global myMAC,myIP
    frame = bytearray()

    # Cabecera ARP

    # Hardware Type (2 Bytes): Indica el tipo de direcciones de nivel de enlace. En el caso de direcciones Ethernet este valor es 0x0001.
    hw = (0x0001).to_bytes(2,"big")
    # Protocol Type (2 Bytes): Indica el tipo de direcciones de nivel de red. En el caso de direcciones IP este valor es 0x0800.
    protocol = (0x0800).to_bytes(2,"big")
    # Hardware Size (1 Byte): Tamaño (en bytes) de las direcciones de nivel de enlace. En el caso de Ethernet este campo debe valer 6.
    hw_size = (6).to_bytes(1,"big")
    # Protocol Size (1 Byte): Tamaño (en bytes) de las direcciones de nivel de red. En el caso de IP este campo debe valer 4.
    protocol_size = (4).to_bytes(1,"big")
    # Opcode (2 Bytes): Indicador de operación ARP. Si el paquete ARP es una petición (Request) este campo vale 0x0001 mientras que si es una respuesta (Reply) este campo vale 0x0002.
    opcode = (0x0002).to_bytes(2,"big")
    # Sender Eth (6 Bytes): Dirección Ethernet del emisor del paquete ARP.
    etho = myMAC
    # Sender IP (4 Bytes): Dirección IP del emisor del paquete ARP.
    ipo = (myIP).to_bytes(4,"big")
    # Target Eth (6 bytes): Dirección Ethernet del receptor del paquete ARP. Si el Opcode del paquete es 1 este valor será la dirección nula (6 bytes a 0) ya que no se conoce cuál es la dirección Ethernet.
    ethdest = (MAC).to_bytes(6,"big")
    # Target IP (4 Bytes): Dirección IP del receptor del paquete ARP.
    ipdest = (IP).to_bytes(4,"big")

    arp = hw + protocol + hw_size + protocol_size + opcode + etho + ipo + ethdest + ipdest
    # eth = ethdest + etho + hw
    frame = arp # + (0).to_bytes(18,"big")



    return frame
    


def process_arp_frame(us:ctypes.c_void_p,header:pcap_pkthdr,data:bytes,srcMac:bytes) -> None:
    '''
        Nombre: process_arp_frame
        Descripción: Esta función procesa las tramas ARP. 
            Se ejecutará por cada trama Ethenet que se reciba con Ethertype 0x0806 (si ha sido registrada en initARP). 
            Esta función debe realizar, al menos, las siguientes tareas:
                -Extraer la cabecera común de ARP (6 primeros bytes) y comprobar que es correcta
                -Extraer el campo opcode
                -Si opcode es 0x0001 (Request) llamar a processARPRequest (ver descripción más adelante)
                -Si opcode es 0x0002 (Reply) llamar a processARPReply (ver descripción más adelante)
                -Si es otro opcode retornar de la función
                -En caso de que no exista retornar
        Argumentos:
            -us: Datos de usuario pasados desde la llamada de pcap_loop. En nuestro caso será None
            -header: cabecera pcap_pktheader
            -data: array de bytes con el contenido de la trama ARP
            -srcMac: MAC origen de la trama Ethernet que se ha recibido
        Retorno: Ninguno
    '''

    # Extraer la cabecera común de ARP (6 primeros bytes) y comprobar que es correcta
    if header != data[:6]:
        return 
    # Extraer el campo opcode
    opcode = data[6:8]
    # Si opcode es 0x0001 (Request) llamar a processARPRequest (ver descripción más adelante)
    if opcode == 0x0001:
        processARPRequest(data, srcMAC)
    # Si opcode es 0x0002 (Reply) llamar a processARPReply (ver descripción más adelante)
    elif opcode == 0x0002:
        processARPReply(data, srcMAC)
    # Si es otro opcode retornar de la función
    else:
        return
    # En caso de que no exista retornar
    return
    
  

        



def initARP(interface:str) -> int:
    '''
        Nombre: initARP
        Descripción: Esta función construirá inicializará el nivel ARP. Esta función debe realizar, al menos, las siguientes tareas:
            -Registrar la función del callback process_arp_frame con el Ethertype 0x0806
            -Obtener y almacenar la dirección MAC e IP asociadas a la interfaz especificada
            -Realizar una petición ARP gratuita y comprobar si la IP propia ya está asignada. En caso positivo se debe devolver error.
            -Marcar la variable de nivel ARP inicializado a True
    '''
    global myIP,myMAC,arpInitialized
    # Registrar la función del callback process_arp_frame con el Ethertype 0x0806
    # registerCallback(callback_func: Callable[[ctypes.c_void_p,pcap_pkthdr,bytes],None], ethertype:int)
        # us: Datos de usuario pasados desde la llamada de pcap_loop. En nuestro caso será None
        # header: cabecera pcap_pktheader
        # data: array de bytes con el contenido de la trama ARP
        # srcMac: MAC origen de la trama Ethernet que se ha recibido
    registerCallback(process_arp_frame, 0x0806)
    # Obtener y almacenar la dirección MAC e IP asociadas a la interfaz especificada
    myMAC = getHwAddr(interface)
    myIP = getIP(interface)
    # Realizar una petición ARP gratuita y comprobar si la IP propia ya está asignada. En caso positivo se debe devolver error.
    if ARPResolution(myIP) != None: return -1 # Devolver error si ip ya está asignada a otro
    # Marcar la variable de nivel ARP inicializado a True
    arpInitialized = True

def ARPResolution(ip:int) -> bytes:
    '''
        Nombre: ARPResolution
        Descripción: Esta función intenta realizar una resolución ARP para una IP dada y devuelve la dirección MAC asociada a dicha IP 
            o None en caso de que no haya recibido respuesta. Esta función debe realizar, al menos, las siguientes tareas:
                -Comprobar si la IP solicitada existe en la caché:
                -Si está en caché devolver la información de la caché
                -Si no está en la caché:
                    -Construir una petición ARP llamando a la función createARPRequest (descripción más adelante)
                    -Enviar dicha petición
                    -Comprobar si se ha recibido respuesta o no:
                        -Si no se ha recibido respuesta reenviar la petición hasta un máximo de 3 veces. Si no se recibe respuesta devolver None
                        -Si se ha recibido respuesta devolver la dirección MAC
            Esta función necesitará comunicarse con el la función de recepción (para comprobar si hay respuesta y la respuesta en sí) mediante 3 variables globales:
                -awaitingResponse: indica si está True que se espera respuesta. Si está a False quiere decir que se ha recibido respuesta
                -requestedIP: contiene la IP por la que se está preguntando
                -resolvedMAC: contiene la dirección MAC resuelta (en caso de que awaitingResponse) sea False.
            Como estas variables globales se leen y escriben concurrentemente deben ser protegidas con un Lock
    '''
    global requestedIP,awaitingResponse,resolvedMAC
    # Comprobar si la IP solicitada existe en la caché:
    # cache = ExpiringDict(max_len=100, max_age_seconds=10)
    if ip in cache:
    # Si está en caché devolver la información de la caché
        return cache.get(ip)
    # Si no está en la caché:
    else:
        # Variables globales
        requestedIP = ip
        
        # Construir una petición ARP llamando a la función createARPRequest (descripción más adelante)
        trama = createARPRequest(ip)
        # Enviar dicha petición
        # Comprobar si se ha recibido respuesta o no:
        i = 0
        awaitingResponse = True
        while i < 3:
            sendEthernetFrame(trama,len(trama),0x0806,broadcastAddr)
            if awaitingResponse == False:
                return resolvedMAC
                # Si no se ha recibido respuesta reenviar la petición hasta un máximo de 3 veces. Si no se recibe respuesta devolver None
            i+= 1
        return None
        # Si se ha recibido respuesta devolver la dirección MAC
