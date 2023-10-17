from rest import *
import json
from Crypto.PublicKey import RSA

def create_id(name, email):
    print("Generando par de claves RSA de 2048 bits...", end="")
    key = RSA.generate(2048)
    public_key = key.publickey().export_key()
    print("OK")
    file_out = open("private.pem", "wb")
    file_out.write(key.exportKey("PEM"))
    file_out.close()
    # decode the public key
    public_key = public_key.decode('utf-8')

    response = user_register(name, email, public_key)
    if response.status_code == requests.codes.ok:
        print("Identidad con ID#"+ response.json().get("userID") +" creada correctamente")
    else:
        print("Error al crear identidad")
        print(response.text)
    

def search_id(id):
    print("Buscando usuario '" + id + "' en el servidor...", end="")
    # If name is an email, search by email. Otherwise, search by name.
    response = user_search(id)
    if response.status_code == requests.codes.ok:
        print("OK")
        print(str(len(response.json()))+" usuarios encontrados: ")
        i = 1
        for r in response.json():
            print("["+str(i)+"] "+r['nombre']+", "+r['email']+", ID: "+r['userID'])
            i += 1
    else:
        print("Error al buscar el usuario")
        print(response.text)
    

    
def delete_id(id):
    # Delente user with id given
    print("Solicitando borrado de la identidad "+id+"...", end="")
    response = user_delete(id)
    if response.status_code == requests.codes.ok:
        print("OK")
        print("Identidad con ID "+ response.json().get("userID") +"borrada correctamente")
    else:
        print("ERROR")
        print("\tError al borrar la identidad")
        print(response.text)