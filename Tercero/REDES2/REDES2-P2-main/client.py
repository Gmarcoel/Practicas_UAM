import json
import argparse
import crypto
from users import *
from files import *




def main():
    parser = argparse.ArgumentParser(description='Process server orders.') 
    parser.add_argument('--create_id',
                        help='Crea una nueva identidad (par de claves pública y privada) para un usuario con \
                        nombre y correo email, y la registra en SecureBox, para que pueda ser encontrada por\
                        otros usuarios. alias es una cadena identificativa opcional.',
                        nargs=2, 
                        metavar=('Nombre', 'Email'))

    parser.add_argument('--search_id',
                        help='Busca un usuario cuyo nombre o correo electrónico contenga cadena en el repositorio\
                        de identidades de SecureBox, y devuelve su ID.',
                        metavar='Nombre/Email')

    parser.add_argument('--delete_id', help='Borra la identidad con ID id registrada en el sistema. Obviamente, sólo se pueden\
                        borrar aquellas identidades creadas por el usuario que realiza la llamada.', 
                        metavar='id')

    parser.add_argument('--upload',
                        help='Envia un fichero a otro usuario, cuyo ID es especificado con la opción --dest_id. Por\
                        defecto, el archivo se subirá a SecureBox firmado y cifrado con las claves adecuadas\
                        para que pueda ser recuperado y verificado por el destinatario.',
                        metavar='fichero')


    parser.add_argument('--source_id', 
                        help='ID del emisor del fichero.', 
                        metavar='id_emisor')

    parser.add_argument('--dest_id', 
                        help='ID del receptor del fichero.', 
                        metavar='id_receptor')

    parser.add_argument('--list_files', 
                        action='store_true', 
                        help='Lista todos los ficheros pertenecientes al usuario')

    parser.add_argument('--download', 
                        help='Recupera un fichero con ID id_fichero del sistema (este ID se genera en la llamada a\
                        upload, y debe ser comunicado al receptor). Tras ser descargado, debe ser\
                        verificada la firma y, después, descifrado el contenido.',
                        metavar='id_fichero')

    parser.add_argument('--delete_file', 
                        help='Borra un fichero del sistema.', 
                        metavar='id_fichero')

    parser.add_argument('--encrypt',
                        help='Cifra un fichero, de forma que puede ser descifrado por otro usuario, cuyo ID es\
                        especificado con la opción --dest_id.',
                        metavar='fichero')

    parser.add_argument('--sign', 
                        help='Firma un fichero.', 
                        metavar='fichero')

    parser.add_argument('--enc_sign', 
                        help='Cifra y firma un fichero, combinando funcionalmente las dos opciones anteriores.', 
                        metavar='fichero')

    parser.add_argument('--decrypt', 
                        help='Descifra un fichero', 
                        metavar='fichero')
    
    parser.add_argument('--dec_verify',
                        help='Descifra y verifica un fichero.',
                        metavar='fichero')


    args = parser.parse_args()

    if args.create_id:
        create_id(args.create_id[0], args.create_id[1])

    if args.search_id:
        search_id(args.search_id)

    if args.delete_id:
        delete_id(args.delete_id)
    
    if args.upload:
        if args.dest_id:
            upload(args.upload, args.dest_id)
        else:
            print("--dest_id es obligatorio")
    
    if args.list_files:
        list_files()
    
    if args.download:
        if args.source_id:
            download(args.download, args.source_id)
        else:
            print("--source_id es obligatorio")
    
    if args.delete_file:
        delete_file(args.delete_file)
        
    if args.encrypt:
        if args.dest_id:
            encrypt_file(args.encrypt, args.dest_id, True)
        else:
            print("--dest_id es obligatorio")

    if args.sign:
        sign_file(args.sign)

    if args.enc_sign:
        if args.dest_id:
            enc_sign(args.enc_sign, args.dest_id)
        else:
            print("--dest_id es obligatorio")

    if args.decrypt:   
        decrypt_file(args.decrypt)
    
    if args.dec_verify:
        if args.dest_id:
            dec_verify(args.dec_verify, args.dec_verify, args.dest_id, True)
        else:
            print("--dest_id es obligatorio")






if __name__ == '__main__':
    main()
