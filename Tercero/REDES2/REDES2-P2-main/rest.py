import requests
from Crypto.PublicKey import RSA
token='bC824fd9DEFAB3c7'

def user_register(name, email, key):
    url = "http://vega.ii.uam.es:8080/api/users/register"
    data = {'nombre': name, 'email': email, 'publicKey': key}
    headers = {'Authorization' : 'Bearer '+token} # 'Content-type': 'application/json', 

    response = requests.post(url, json=data, headers=headers)

    return response

def user_search(id):
    url = "http://vega.ii.uam.es:8080/api/users/search"

    data = {'data_search': id}
    
    headers = {'Authorization' : 'Bearer '+token} 
    response = requests.post(url, json=data, headers=headers)

    return response

def user_get_public_key(id):
    # print("-> Recuperando clave pública de ID "+id+"...", end="")
    url = "http://vega.ii.uam.es:8080/api/users/getPublicKey"
    data = {'userID': id}
    headers = {'Authorization' : 'Bearer '+token}
    response = requests.post(url, json=data, headers=headers)
    """    
    if response.status_code == requests.codes.ok:
        print("OK")
        return RSA.import_key(response.json().get('publicKey'))
    else:
        print("Error al recuperar clave pública")
        print(response.text)
        return None
        """
    #check if the response is ok
    if response.status_code == requests.codes.ok and RSA.import_key(response.json().get('publicKey')) is not None:
         return RSA.import_key(response.json().get('publicKey'))
    else:
        print("ERROR")
        print("\tError al recuperar clave pública")
        print(response.text)
        return None

def user_delete(id):
    url = "http://vega.ii.uam.es:8080/api/users/delete"
    data = {'userID': id}
    headers = {'Authorization' : 'Bearer '+token}
    response = requests.post(url, json=data, headers=headers)

    return response

def files_upload(f, dest_id):
    url = "http://vega.ii.uam.es:8080/api/files/upload"
    headers = {'Authorization' : 'Bearer ' + token}
    response = requests.post(url, files={'ufile': open(f, 'rb')}, headers=headers)
    return response

def files_download(id):
    url = "http://vega.ii.uam.es:8080/api/files/download"
    data = {'file_id': id}
    headers = {'Authorization' : 'Bearer ' + token}
    response = requests.post(url, json=data, headers=headers)

    return response

def files_list():
    url = "http://vega.ii.uam.es:8080/api/files/list"
    data = {}
    headers = {'Authorization' : 'Bearer '+token}
    response = requests.post(url, json=data, headers=headers)

    return response

def file_delete(id):
    url = "http://vega.ii.uam.es:8080/api/files/delete"
    data = {'file_id': id}
    headers = {'Authorization' : 'Bearer '+token}
    response = requests.post(url, json=data, headers=headers)

    return response
