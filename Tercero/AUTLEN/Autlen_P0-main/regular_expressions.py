"""
Esta es la expresion regular para el ejercicio 0, que se facilita
a modo de ejemplo:
"""
RE0 = "[a-zA-Z]+"

"""
Completa a continuacion las expresiones regulares para los
ejercicios 1-5:
"""
RE1 = "[\w]+.py"
RE2 = "(-?[\d]*\.[\d]*)|(-?[1-9][\d]*)|-?0"
RE3 = "[a-z]+\.[a-z]+@(estudiante\.)?uam.es"
RE4 = "([\w ]*\([\w ]*\)[\w ]*)+"
RE5 = "([\w ]*\(("+RE4+"|[\w])*\)?[\w ]*)+" 

   
"""
Recuerda que puedes usar el fichero prueba.py para probar tus
expresiones regulares.
"""

""" 
EJERCICIO 6:
Incluye a continuacion, dentro de esta cadena, tu respuesta 
al ejercicio 6.

Discute por qué no es posible crear una expresión regular que reconozca todas las
secuencias de paréntesis bien anidadas sin límite de profundidad.

No es posible crear una expresión regular que reconozca todas las secuencias de paréntesis bien anidadas sin límite de profundidad ya que
cada nivel de anidación se tiene que añadir una nueva condicion a la expresion manualmente por lo que siempre va a haber un número finito de anidaciones. Esto se debe a que no
hay manera de guardar el número de paréntesis abierto para que se cierren la misma cantidad.

"""
