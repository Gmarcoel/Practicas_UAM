import re
from rest import *
from crypto import *
import os


def upload(file, dest_id):
    # Upload a file
    print("Solicitado envio de fichero a SecureBox")

    # Check if file exists
    if not os.path.exists(file):
        print("Error: El fichero no existe")
        return
    # Encript file
    if not enc_sign(file, dest_id):
        print("Error al encriptar el fichero")
        return
    

    print("-> Subiendo fichero a servidor...", end="")
    response = files_upload("encrypted_files/" + os.path.basename(file), dest_id)
    if response.status_code == requests.codes.ok:
        print("OK")
        print("Subida realizada correctamente, ID del fichero: "+response.json().get("file_id"))
    else:
        print("ERROR")
        print("\tError al subir el fichero")
        print(response.text)
    
    # Delete encrypted_files folder
    print("-> Borrando carpeta 'encrypted_files'...", end="")
    os.system("rm -rf encrypted_files")
    print("OK")

def list_files():
    print("Solicitado lista de archivos en SecureBox...", end="")
    # List all user files
    response = files_list()
    if response.status_code != requests.codes.ok:
        print("ERROR")
        print("\tError al listar los archivos")
        return

    print("OK")
    print(response)
    # print(response.text)
    fl = response.json().get("files_list")
    i = 1
    for r in fl:
        print("["+str(i)+"] "+r['fileName']+", ID: "+r['fileID'])
        i += 1
    print("Total de archivos: "+ str(response.json().get("num_files")))

def download(file_id, source_id):
    # Download a file
    print("Descargando fichero de SecureBox...", end="")
    response = files_download(file_id)

    # If download is successful, save file
    if response.status_code == requests.codes.ok:
        print("OK")
        print("-> "+response.headers.get("Content-length")+" bytes descargados correctamente")

        #get file name
        file_name = response.headers.get("Content-Disposition").split("filename=")[1]
        file_name = file_name[1:len(file_name)-1]
        # Decrypt file and save it
        v = dec_verify(file_name, response.content, source_id, False)
        if v:
            print("-> Fichero '" + file_name + "' descargado y verificado correctamente")
        
    
    # If download is not successful, print error
    else:
        print("ERROR")
        print("\tError al descargar el fichero")
    
    # print(response.text)

def delete_file(id):
    # Delete a file
    response = file_delete(id)
    print(response)
    print(response.text)
