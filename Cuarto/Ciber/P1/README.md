# CIBER_P1
## Sistema de comunicación para la UREJ (Unidad de Rescate de Enanitos de Jardín)

### Instalación de dependencias
Para poder usar el programa, todo ordenador de la UREJ involucrado en eluso de estas herramientas tiene que instalar ciertas libreriías de las que hacen uso los programas. Para ello ejecutar en la terminal el siguiente comando (A ser posible en un enviroment de Python propio para este proyecto):
> `pip install -r requirements.txt`

Este comando instalará lo necesario para poder continuar.

### Guia del sistema:

El sistema de comunicaciones se basa en tres archivos .py distintos que deberán ser ejecutados cada uno en su respectivo componente.
- [Base de operaciones (BO)](./bo.py): Programa que se deberá ejecutar en la única base de operaciones y solo tendran acceso a el los jefes centrales de la UREJ. La aplicación permite controlar todos los elementos del sistema, y diseñar las operaciones de rescate.
- [Estación de tierra (ET)](./et.py): Programa que represanta las unidades básicas de la red. Permite la comunicación y da capacidad de control de sus drones (aunque mas limitada) a los jefes de cada zona de la UREJ.
- [Drones (DR)](./drone.py): Programa que corre dentro de un propio drone y le permite ejecutar las funciones basicas que se le pidan. 

Por otro lado tenemos dos archivos auxiliares:
- [auxMethods](./auxMethods.py): Toda la funcionalidad reusable por varios componentes de envio de mensajes, encriptación de los mensajes, conexión con la BO, etc...
- [terminal](./terminal.py): Contiene todas las clases diferentes de la Terminal User Interface (TUI) y sus metodos para poder manejarlas.


Todas las aplicaciones forman parte de una red que permite la comunicación entre ellas. Para obtener más información consultar la [implementación](https://git.eps.uam.es/ciber/2023/2471/09/practica1/-/wikis/Implementaci%C3%B3n-sistema) de la misma tanto pinchando el link o visitando la Wiki.

### Guía de uso:


**Uso de la interfaz**

Al ejecutar cada una de las aplicaciones se generará una interfaz. Esta interfaz requiere de una terminal con unas medidas mínimas, así que si a la hora de abrir el programa no se genera dicha interfaz, pruebese a volver a ejeutarlo aumentando previamente el tamaño.

La interfaz muestra algo parecido a lo siguiente:

__ Status _________________________________________________________________

|__________________________________________________________________________|

__ Info ___________________________________________________________________

|__________________________________________________________________________|

__ Terminal _______________________________________________________________

|__________________________________________________________________________|

Y cada sección muestra lo siguiente: 

| Seccion | Contenido |
| ------ | ------ |
|Status|Muestra el estatus del sistema que se esta ejecutando. En caso del drone solo mostrara su propio status, en caso de la ET, los status de los drones a los que esta conectada y en caso de la BO, para no saturar la red, solo se muestra el estado de todos los drones cuando se ejecuta el comando GET_STATUS |
|Info|Seccion en la que se muestran los últimos mensajes de información relevantes o errores|
|Terminal|Input para poder enviar comandos a la aplicación que estamos ejecutando. Mas abajo estan explicados todos los comandos posibles en cada aplicación. *IMPORTANTE: todos los comandos son case sensitive y deben estar en minusculas*|


**Aplicación Base de operaciones (BO)**

Esta aplicación debe ser ejecutada en la única base de operaciones de la UREJ situada en [40°26′07″N 3°43′11″O](https://geohack.toolforge.org/geohack.php?language=es&pagename=Cuartel_General_del_Ej%C3%A9rcito_del_Aire_y_del_Espacio&params=40.435377777778_N_-3.7198611111111_E_type:landmark). Por motivos de seguridad y confidencialidad, el uso de esta herramienta queda restringido exclusivamente al Jefe de la UREJ, Oscar Delgado, de conformidad con las políticas y procedimientos de la organización. La aplicación proporciona control sobre toda la red.

<ins>Guia de comandos:</ins>

| Comando | Descripción |
| ------ | ------ |
|`send msg <id> <msg>`| Envia una cadena de texto (msg) a una ET indicada por el id |
|`send file <id> <route>`| Envia un archivo a una ET indicada por el id |
|`fly <drone_id>`| Manda volar a un drone especificado por la id. Para ello, contacta con todas las ET para que en caso de que alguna tenga ese drone conectado, le mande un mensaje para que vuele |
|`land <drone_id>`| Misma metodologia que el comando FLY pero en este caso para hacer que un drone aterrice |
|`status`| Muestra en la box de Status de la terminal el estado de todas las ET y sus drones |
|`shutdown`|Provoca que todas las ET ordenen a sus drones asociados que aterricen inmediatamente y, luego, los desconecta |

**Aplicación Estación de tierra (ET)**

Esta aplicación se ejecutara 
en todas las [bases del ejercito del aire que dispongan de un departamento de UREJ](https://upload.wikimedia.org/wikipedia/commons/thumb/1/13/Bases_A%C3%A9reas_del_Ej%C3%A9rcito_del_Aire_de_Espa%C3%B1a2.svg/1024px-Bases_A%C3%A9reas_del_Ej%C3%A9rcito_del_Aire_de_Espa%C3%B1a2.svg.png) y solo sera usada por el equipo de UREJ. Permite la gestion de los drones conectados y la comunicación con el resto de la red.

<ins>Guia de comandos:</ins>

| Comando | Descripción |
| ------ | ------ |
|`send msg <id> <msg>`| Envia una cadena de texto (msg) a una ET indicada por el id. En caso que el id sea "BO" el mensaje será transmitido a la base de operaciones |
|`send file <id> <route>`| Envia un archivo a una ET indicada por el id. En caso que el id sea "BO" el archivo será transmitido a la base de operaciones  |
|`fly <drone_id>`| Manda volar a un drone especificado por la id. Para ello, contacta con todas las ET para que en caso de que alguna tenga ese drone conectado, le mande un mensaje para que vuele |
|`land <drone_id>`| Misma metodologia que el comando FLY pero en este caso para hacer que un drone aterrice |
|`link`| Conecta la ET a la base de operaciones |
|`unlink`| Desconecta la ET de la base de operaciones |
|`disconnect`| Desconecta un drone especifico de la ET |

**Aplicación Drones (DR)**

Esta aplicación se ejecutara en el drone. Una vez el drone sea comprado por la UREJ, será enviado a la Base de Operaciones. Ahi se ejecutaran las tareas de asignación de id del drone al ejecutarse la aplicación por primera vez y se linkeará el drone desde la BO a todas las estaciones de tierra donde se prevee el uso de ese drone. Una vez ese proceso se termina, el drone es enviado de la Base de operaciones a la Estación de Tierra para que los trabajadores de la UREJ de esa estación puedan comenzar a darlke uso tras conectarlo. Al ser conectado a una ET el drone empezará a mandar mensajes de telemetria haciendo a la ET conocedora de su estado en todo momento menos en el caso que el drone este totalmente cargado y en la base donde entrara en el standby mode y dejará de enviar telemetría hasta que su estado cambie (esto se hace para no saturar la red con información redundante). El drone también dispone de una batería la cual se agota tras un minuto de vuelo. En cuanto la batería llega a un 20% se inicia el protocolo de regreso a base y en cuanto el drone esta en base comienza a cargar hasta alcanzar la maxima capacidad de batería.

<ins>Guia de comandos:</ins>

| Comando | Descripción |
| ------ | ------ |
|`link <et_id>`| Pregunta a la BO por la et que tenga un id concreto y la BO devuelve al drone la ip y puerto done encontrarla para poder almacenarla en su lista de opsibles ET para conexión |
|`unlink <et_id>`| Elimina una ET de la lista de ET disponibles para conexión para el drone |
|`connect <et_id>`| Inicia una conexión entre una et indicada por el id y el drone. Da control del drone a una ET especifica que debe estar previamente en la lista de ET disponibles para conexion |
|`disconnect`| Cierra la conexión vigente con la ET |

Para leer la memoria de este proyecto por favor visita la [Wiki](https://git.eps.uam.es/ciber/2023/2471/09/practica1/-/wikis/Implementaci%C3%B3n-sistema).
