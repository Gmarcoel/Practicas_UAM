from email import message
from unicodedata import digit
from rest import *
import Crypto
from Crypto.Hash import SHA256
from Crypto.PublicKey import RSA
from Crypto.Random import get_random_bytes
from Crypto.Cipher import AES, PKCS1_OAEP
from Crypto.Util.Padding import pad, unpad
from Crypto.Signature import pkcs1_15
import os

def encrypt_file(message, dest_id, is_file):

    
    # If done separately, encrypt the file
    if is_file:
        with open(message, 'rb') as f:
            message = f.read()
    

    # Create random iv
    iv = get_random_bytes(16)

    # Encrypt the concatenation
    symmetric_key = get_random_bytes(32)
    symmetric_key_aes = AES.new(symmetric_key, AES.MODE_CBC, iv)
    encrypted_message = symmetric_key_aes.encrypt(pad(message, AES.block_size))
    
    # Get the public key
    print("-> Recuperando clave pública de ID " + dest_id + "...", end="")
    public_key = user_get_public_key(dest_id)
    if not public_key:
        return None
    print("OK")

    # Encrypt the symmetric key with the public key of the receiver
    print("-> Cifrando fichero...", end="")
    public_key_rsa = PKCS1_OAEP.new(public_key)
    digital_envelope = public_key_rsa.encrypt(symmetric_key)
    print("OK")

    # Print length in bytes of iv, digital envelope and encrypted message
    print("-> Longitud del IV: " + str(len(iv)) + " bytes")
    print("-> Longitud de la firma digital: " + str(len(digital_envelope)) + " bytes")
    print("-> Longitud del mensaje cifrado: " + str(len(encrypted_message)) + " bytes")

    # Concatenate digital envelope and encrypted message
    concatenation = iv + digital_envelope + encrypted_message
    return concatenation
    


def sign_file(fi):
    print("-> Firmando fichero...", end="")
    with open(fi, 'rb') as f:
        message = f.read()
    
    
    # If file error occurs, return error
    if message == b'':
        print("ERROR")
        print("\tError al firmar el fichero")
        return
        
    hashed_message = SHA256.new(message)
    
    # Get the emisor's private key
    private_key = RSA.import_key(open('private.pem').read())
    # private_key = open('private.pem').read()


    # Encrypt the hash_message
    private_key_rsa = pkcs1_15.new(private_key)
    # Sign hash_message
    digital_sign = private_key_rsa.sign(hashed_message)

    # digital_sign = private_key_rsa.sign(hashed_message)

    # Concatenate message and digital signature
    concatenation = message + digital_sign
    print("OK")

    # Print length in bytes of message and digital signature
    print("-> Longitud del mensaje: " + str(len(message)) + " bytes")
    print("-> Longitud de la firma digital: " + str(len(digital_sign)) + " bytes")


    return concatenation


def enc_sign(f, dest_id):

    # Sign
    firma_digital = sign_file(f)

    # Encrypt
    firma_digital_enc = encrypt_file(firma_digital, dest_id, False)
    if not firma_digital_enc:
        return None

    #create folder encrypted_files if it doesn't exist
    if not os.path.exists('encrypted_files'):
        os.makedirs("encrypted_files")
    
    # Remove the name of f before /
    name = f.split('/')[-1]

    # Download
    with open("encrypted_files/"+ name, 'wb') as f:
        f.write(firma_digital_enc)
        f.close()

    return firma_digital_enc

    

def decrypt_file(message, user_id, is_file):
    print("-> Descifrando fichero...", end="")

    if is_file:
        with open(message, 'rb') as f:
            message = f.read()
    
    # Get the iv
    iv = message[0:16]

    # Get the digital envelope
    digital_envelope = message[16:272]

    # Get the encrypted message
    encrypted_message = message[272:]

    # Get the private key
    private_key = RSA.import_key(open('private.pem').read())

    # Decrypt the digital envelope
    private_key_rsa = PKCS1_OAEP.new(private_key)
    symmetric_key = private_key_rsa.decrypt(digital_envelope)
    

    # Decrypt the message
    symmetric_key_aes = AES.new(symmetric_key, AES.MODE_CBC, iv)
    message_and_signature = symmetric_key_aes.decrypt(encrypted_message)
    # decrypted_message = unpad(symmetric_key_aes.decrypt(encrypted_message), AES.block_size)
    print("OK")
    return message_and_signature






def verify_sign(message_and_sign, user_id, is_file):
    print("-> Verificando firma...", end="")

    # If done separately, decrypt the file
    if is_file:
        with open(message, 'rb') as f:
            message_and_sign = f.read()
    
    # Unpad message and sign
    message_and_sign = unpad(message_and_sign, AES.block_size)

    # Get the message
    message = message_and_sign[0:-256]

    # Get the digital signature
    digital_sign = message_and_sign[-256:]

    # Get the public key
    public_key = user_get_public_key(user_id)
    if not public_key:
        return None


    # Get the hash of the message
    hashed_message = SHA256.new(message)

    # Verify the digital signature
    public_key_rsa = pkcs1_15.new(public_key)
    try:
        public_key_rsa.verify(hashed_message, digital_sign)
    except ValueError:
        print("ERROR")
        print("\tError al verificar la firma")
        return None

    print("OK")
    return message


def dec_verify(fname, f, user_id, is_file):
    # Decrypt
    message_and_signature = decrypt_file(f, user_id, is_file)
    if not message_and_signature:
        print("Error al descifrar el fichero")
        return None

    # Verify
    message = verify_sign(message_and_signature, user_id, False)
    if not message:
        print("Error al verificar la firma")
        return None
    
    
    with open(fname, 'wb') as f:
        f.write(message)
        f.close()
    
    return message

