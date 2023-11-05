import socket
import json
import os
import time
import rsa
import hashlib
from Cryptodome.Cipher import AES
from Cryptodome.Random import get_random_bytes
from Cryptodome.PublicKey import RSA
from Cryptodome.Hash import SHA256
from Cryptodome.Util import Padding
from Cryptodome.Cipher import PKCS1_OAEP
from Cryptodome.Signature import pkcs1_15

port=2728
ip='127.0.0.1'

et_initial_port=2100

green = '\033[1;32m'
blue = '\033[1;36m'
default = '\033[1;m'
yellow = '\033[1;33m'
red = '\033[1;31m'
grey = '\033[1;30m'

info = grey + "[INFO] " + default
ok = green +  "[OK]   " + default
error = red + "[ERROR]" + default


def droneStatusMsg(bat, state):
    col = default
    if bat == 100:
        col = blue
    elif bat > 50:
        col = green
    elif bat > 10:
        col = yellow
    else:
        col = red
    if state == "flying":
        status = ("[ON AIR]")
    elif state =="returning":
        status = ("[RETURNING TO BASE] (LOW BATTERY)")
    elif state =="charging":
        status = ("[CHARGING]")
    else:
        status = ("[GROUNDED]")
    return ("Status: "+status+"\t|\tBattery: " + str(bat)+ "     ")


# Imprime la pantalla de los drones
def renderEtScreen(drones):
    for droneId in drones:
        print("Drone:\t"+droneId)
        print("\t"+droneStatusMsg(drones[droneId]["battery"], drones[droneId]["state"]))


# Conecta a la BO
def connectToBO(id, public_key, element_ip=None, element_port=None):
    global ip, port
    # If .bo.txt exists, read the ip and port from it
    if os.path.isfile(".bo.txt"):
        with open(".bo.txt", "r") as f:
            ip, port = f.read().split(":")
            port = int(port)
            f.close()

    try:
        #Create and assign BO socket
        bo_socket = socket.socket()
        bo_socket.settimeout(3)
        bo_socket.connect((ip, port))

        #Send a petition to the BO to create elemnt with the ID we input
        if element_ip == None and element_port == None:
            message = '{"type": "create", "element":"drone", "id":"' + id + '", "public_key":"' + public_key +'"} '
        else:
            message = '{"type": "create", "element":"et", "id":"' + id + '", "public_key":"' + public_key + '", "ip":"' + element_ip + '", "port":"'+str(element_port)+'"} '
        #Recieve response of the ID assignation from the BO
        res = sendRequest(bo_socket, message)
        final_id = res['id']
        bo_public_key = res['public_key']
        return [bo_socket, final_id, bo_public_key]
    except Exception as e:
        return [None, "", ""]


# Desconecta el elemento del BO
def disconnectFromBO(bo_socket, drone, send_private_key=None, rec_public_key=None):
    try:
        if drone:
            message = '{"type": "unlink", "element":"drone"} '
        else:
            message = '{"type": "unlink", "element":"et"} '
        if send_private_key != None:
            res =sendMessage(bo_socket, message, send_private_key, rec_public_key)
        else:
            res = sendMessage(bo_socket, message)
        bo_socket.close()
        return res
    except Exception as e:
        return None

# Envia un mensaje al socket y espera la respuesta
def sendRequest(target_socket, msg, send_private_key=None, rec_public_key=None):
    try:
        # Si se han pasado las claves, ciframos el mensaje
        if send_private_key != None:
            sendMessage(target_socket, msg, send_private_key, rec_public_key)
        else:
            sendMessage(target_socket, msg)
        res = target_socket.recv(1024)
        # Si se han pasado las claves, desciframos el mensaje
        if send_private_key != None:
            res = decode_message(res, send_private_key, rec_public_key)
        else:
            res = res.decode('utf-8')
        res = json.loads(res)
        return res
    except Exception as e:
        return None

# Envia un mensaje al socket
def sendMessage(target_socket, msg, send_private_key=None, rec_public_key=None):
    # Si se han pasado las claves, ciframos el mensaje
    if send_private_key != None and rec_public_key != None:
        msg = encode_message(msg, send_private_key, rec_public_key)
    else:
        msg = str.encode(msg)
    target_socket.send(msg)

# Recibe un mensaje del socket y lo decodifica
def listen_socket(target_socket, rec_private_key=None, send_public_key=None):
    try:
        res = target_socket.recv(1024)
        # Si se han pasado las claves, desciframos el mensaje
        if rec_private_key != None and send_public_key != None:
            res = decode_message(res, rec_private_key, send_public_key)
        else:
            res = res.decode('utf-8')
        res = json.loads(res)
        return res
    except Exception as e:
        return None
    
# Asigna un puerto libre al socket
def assignPorts(target_socket, host, initialPort):
    port=initialPort
    while True:
        try:
            target_socket.bind((host, port))
            break
        except socket.error as e:
            port+=1
    return port

import signal

# No está en uso
def force_port():
    # get the PID of the process using the port
    output = os.popen(f"lsof -i :{port}").read()
    lines = output.split('\n')
    pid_line = lines[1]
    pid = int(pid_line.split()[1])

    # send a SIGTERM signal to the process to terminate it
    os.kill(pid, signal.SIGTERM)

# Generador clave pública y privada
def generate_keys():
    # Generate RSA key pair
    public_key, private_key = rsa.newkeys(512)


    # Convert the keys to string format
    public_key_str = public_key.save_pkcs1().decode('utf-8')
    public_key_str = public_key_str.split('\n')[1:-2]
    public_key_str = ''.join(public_key_str)

    private_key_str = private_key.save_pkcs1().decode('utf-8')
    private_key_str = private_key_str.split('\n')[1:-2]
    private_key_str = ''.join(private_key_str)

    return (public_key_str, private_key_str)

def key_format(key, public):
    if public:
        key = '-----BEGIN RSA PUBLIC KEY-----\n' + key + '\n-----END RSA PUBLIC KEY-----'
    else:
        key = '-----BEGIN RSA PRIVATE KEY-----\n' + key + '\n-----END RSA PRIVATE KEY-----'
    
    key = key.encode('utf-8')
    if public:
        # key = RSA.import_key(key)
        key = rsa.PublicKey.load_pkcs1(key)
    else:
        # key = RSA.import_key(key)
        key = rsa.PrivateKey.load_pkcs1(key)
    
    return key

# Generador de clave simétrica AES
def generate_aes_key():
    return get_random_bytes(32)

def encode_message(message, send_private_key, rec_public_key):
    # To bytes
    send_private_key   = key_format(send_private_key, False)
    rec_public_key     = key_format(rec_public_key, True)
    mensaje_descifrado = str.encode(message)

    # Create random iv
    # iv = get_random_bytes(16)

    # Firma digital 64
    # cifrador_firma = pkcs1_15.new(send_private_key)
    # firma_digital      = cifrador_firma.sign(SHA256.new(mensaje_descifrado))

    

    # Clave simétrica 32
    # clave_simetrica    = generate_aes_key()
    # cifrador_simetrico = AES.new(clave_simetrica, AES.MODE_CBC, iv)
    # mensaje_cifrado    = cifrador_simetrico.encrypt(Padding.pad(mensaje_descifrado + firma_digital, AES.block_size))

    # Sobre digital
    # cifrador_asimetrico = PKCS1_OAEP.new(rec_public_key)
    # sobre_digital       = cifrador_asimetrico.encrypt(clave_simetrica)
    # concatenacion       = iv + sobre_digital + mensaje_cifrado
    # concatenacion       = iv + mensaje_cifrado
    # print(len(concatenacion))
    

    return rsa.encrypt(mensaje_descifrado, rec_public_key)



def decode_message(message, rec_private_key, send_public_key):
    # To bytes
    rec_private_key = key_format(rec_private_key, False)
    send_public_key = key_format(send_public_key, True)

    # Chipeando
    # iv = message[0:16]
    # sobre_digital = message[16:48]
    # mensaje_cifrado = message[48:]

    # Descifrar clave simétrica
    # clave_simetrica = 
    # descifrador_asimetrico = PKCS1_OAEP.new(rec_private_key)
    # clave_simetrica = descifrador_asimetrico.decrypt(sobre_digital)
    
    # Descifrar mensaje
    # descifrador_simetrico    = AES.new(clave_simetrica, AES.MODE_CBC, iv)
    # mensaje_descifrado_firma = descifrador_simetrico.decrypt(mensaje_cifrado)
    # mensaje_descifrado_firma = Padding.unpad(mensaje_descifrado_firma, AES.block_size)
    # mensaje_descifrado       = mensaje_descifrado_firma[:-256]
    # firma_digital            = mensaje_descifrado_firma[-256:]


    # Verifica firma digital
    # mensaje_hash = SHA256.new(mensaje_descifrado)
    # descifrador_firma = pkcs1_15.new(send_public_key)
    # descifrador_firma.verify(mensaje_hash, firma_digital)

    mensaje_descifrado = rsa.decrypt(message, rec_private_key)
    mensaje_descifrado = mensaje_descifrado.decode('utf-8')
    return mensaje_descifrado
    
    """
    # To bytes
    send_private_key = key_format(send_private_key, False)
    
    rec_public_key   = key_format(rec_public_key, True)
    # Save in file
    
    message = str.encode(message)

    # Generamos la clave simétrica
    sim_key = generate_aes_key()

    # Ciframos el mensaje con la clave simétrica
    cipher = AES.new(sim_key, AES.MODE_EAX)
    mensaje_cifrado, tag = cipher.encrypt_and_digest(message)

    # Ciframos la clave simétrica con la clave pública RSA
    clave_simetrica_cifrada = rsa.encrypt(sim_key, rec_public_key)

    # Save in file
    with open('clave_simetrica_cifrada.txt', 'wb') as f:
        f.write(clave_simetrica_cifrada)
        f.close()

    # Creamos un hash del mensaje original
    hash_message = hashlib.sha256(message).digest()

    # Firmamos el hash del mensaje con la clave privada RSA
    firma_digital = rsa.sign(hash_message, send_private_key, 'SHA-256')

    # Creamos un sello digital que incluye el mensaje cifrado, el tag y la clave simétrica cifrada
    # print("AAAAAAAAAAAAAAAAA", len(mensaje_cifrado), len(tag), len(clave_simetrica_cifrada), len(firma_digital))
    sello_digital = mensaje_cifrado + tag + clave_simetrica_cifrada

    # Enviamos el sello digital y la firma digital junto con el mensaje cifrado
    mensaje_enviado = sello_digital + firma_digital
    return mensaje_enviado
    """
    """
    # To bytes
    rec_private_key = key_format(rec_private_key, False)
    send_public_key = key_format(send_public_key, True)
    
    # Separamos el sello digital y la firma digital del mensaje recibido en x, 16, 64, 64
    mensaje_cifrado = message[:-144]
    tag = message[-144:128]
    clave_simetrica_cifrada = message[-128:-64]
    firma_digital_recibida = message[-64:]

    # Save message in file
    with open('message.txt', 'wb') as f:
        f.write(message)
        f.close()


    # Desciframos la clave simétrica con la clave privada RSA
    clave_simetrica_descifrada = rsa.decrypt(clave_simetrica_cifrada, rec_private_key)
    print("Clave simétrica descifrada: ", str(clave_simetrica_descifrada))
    print("2")

    # Desciframos el mensaje con la clave simétrica
    cipher = AES.new(clave_simetrica_descifrada, AES.MODE_EAX)
    print("2.5")
    mensaje_descifrado = None
    mensaje_descifrado = cipher.decrypt(mensaje_cifrado)
    # mensaje_descifrado = cipher.decrypt_and_verify(mensaje_cifrado, tag, mensaje_descifrado)

    print("3")

    # Creamos un hash del mensaje descifrado
    # hash_mensaje_descifrado = hashlib.sha256(mensaje_descifrado).digest()

    print("4")

    # Verificamos la firma digital con la clave pública RSA
    # rsa.verify(mensaje_descifrado, firma_digital_recibida, send_public_key)

    print("5")
    # To normal string
    # Decode
    res = mensaje_descifrado.decode('utf-8')
    print(str(res))
    return res
    """