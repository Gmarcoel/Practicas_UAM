# Practica2

**Ejecución del código:**

`python3 client.py --help`

Una vez ejecutado aparecerán las opciones posibles:


| Opción | Descripción |
| ------ | ------ |
| --create_id nombre email [alias] | Crea una nueva identidad (par de claves pública y privada) para un usuario con nombre y correo email, y la registra en SecureBox, para que pueda ser encontrada por otros usuarios. alias es una cadena identificativa opcional. |
| --search_id cadena | Busca un usuario cuyo nombre o correo electrónico contenga cadena en el repositorio de identidades de SecureBox, y devuelve su ID. |
| --delete_id id | Borra la identidad con ID id registrada en el sistema. Obviamente, sólo se pueden borrar aquellas identidades creadas por el usuario que realiza la llamada. |
| --upload fichero | Envia un fichero a otro usuario, cuyo ID es especificado con la opción --dest_id. Por defecto, el archivo se subirá a SecureBox firmado y cifrado con las claves adecuadas para que pueda ser recuperado y verificado por el destinatario. |
| --source_id id | ID del emisor del fichero |
| --dest_id id | ID del receptor del fichero. |
| --list_files | Lista todos los ficheros pertenecientes al usuario |
| --download id_fichero | Recupera un fichero con ID id_fichero del sistema (este ID se genera en la llamada a upload, y debe ser comunicado al receptor). Tras ser descargado, debe ser verificada la firma y, después, descifrado el contenido. |
| --delete_file id_fichero | Borra un fichero del sistema |
| --encrypt fichero | Cifra un fichero, de forma que puede ser descifrado por otro usuario, cuyo ID es especificado con la opción --dest_id. |
| --sign fichero | Firma un fichero. |
| --enc_sign fichero | Cifra y firma un fichero, combinando funcionalmente las dos opciones anteriores |
| --decrypt | Descifra un fichero previamente cifrado y firmado |
| --dec_verify | Descifra y verifica un fichero. |

Posteriormente se ejecuta el comand inicial con la opción deseada y el programa devolverá el resultado de la ejecución.

**Datos importantes:**

**NIA** : 420594

**Token** : bC824fd9DEFAB3c7

La **private key** se encuentra en el archivo _'private.pem'_





Para saber más sobre el programa visita la [Wiki](https://git.eps.uam.es/redes2/2022/2391/04/practica2/-/wikis/Pr%C3%A1ctica-2-Seguridad-y-criptograf%C3%ADa).

