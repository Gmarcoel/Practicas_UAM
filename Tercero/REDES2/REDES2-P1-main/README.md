# Redes2_P1

**Compilación y ejecución del código:**

1. Añadir carpeta media con el contenido proporcionado en moodle
2. Ejecutar make desde la carpeta principal (_Redes2_P1_) para compilar los archivos y generar el ejecutable
>Usuario:~/DEsktop/Redes2_P1$ make
3. Mover el archivo servidor.conf a la carpeta _etc/systemd/system/_ cambiando los parámetros User, ExecStart y WorkingDirectory por aquellos pertinentes 

| Parametro | Definición |
| ------ | ------ |
| User | Usuario desde el cual se quiere ejecutar |
| ExecStart | Ruta local al archivo ejecutable (server en nuestro caso) |
| WorkingDirectory | Ruta local al directorio donde se encuentra nuestro código |
4. Correr el servidor con el comando:
>`sudo systemctl start server`
5. Parar la ejecución del servidor con el comando:
>`sudo systemctl stop server`


**Para entender más sobre el código leer la [memoria](https://git.eps.uam.es/redes2/2022/2391/04/redes2_p1/-/wikis/Memoria)**
