'''
    practica1.py
    Muestra el tiempo de llegada de los primeros 50 paquetes a la interfaz especificada
    como argumento y los vuelca a traza nueva con tiempo actual

    Autor: Javier Ramos <javier.ramos@uam.es>
    2020 EPS-UAM
'''

from ctypes import sizeof
from rc1_pcap import *
import sys
import binascii
import signal
import argparse
from argparse import RawTextHelpFormatter
import time
import logging

from datetime import datetime, timedelta # jeje salu3

ETH_FRAME_MAX = 1514
PROMISC = 1
NO_PROMISC = 0
TO_MS = 10
num_paquete = 0
TIME_OFFSET = 30*60
GNBYTES = 0

def signal_handler(nsignal,frame):
	logging.info('Control C pulsado')
	if handle:
		pcap_breakloop(handle)

		
# Función procesadora de paquetes
def procesa_paquete(us,header,data):
	global num_paquete, pdumper
	logging.info('Nuevo paquete de {} bytes capturado en el timestamp UNIX {}.{}'.format(header.len,header.ts.tv_sec,header.ts.tv_sec))
	num_paquete += 1
	hexData = str(data[:GNBYTES].hex())
	output=""
	#TODO imprimir los N primeros byte
	for i in range(GNBYTES):
		output += str(hexData[i])+str(hexData[i+1])+" "
		i+=1

	print(output)
	#Escribir el tráfico al fichero de captura con el offset temporal
	if pdumper is not None:
		pcap_dump(pdumper, header,data)
	return

	# cada paquete capturado/analizado en hexadecimal con 2 dígitos por Byte (y separando cada Byte por espacios en blanco). 
	

if __name__ == "__main__":
	global pdumper,args,handle
	parser = argparse.ArgumentParser(description='Captura tráfico de una interfaz ( o lee de fichero) y muestra la longitud y timestamp de los 50 primeros paquetes',
	formatter_class=RawTextHelpFormatter)
	parser.add_argument('--file', dest='tracefile', default=False,help='Fichero pcap a abrir')
	parser.add_argument('--itf', dest='interface', default=False,help='Interfaz a abrir')
	parser.add_argument('--nbytes', dest='nbytes', type=int, default=14,help='Número de bytes a mostrar por paquete')
	parser.add_argument('--debug', dest='debug', default=False, action='store_true',help='Activar Debug messages')
	args = parser.parse_args()
	print(args)
	if args.debug:
		logging.basicConfig(level = logging.DEBUG, format = '[%(asctime)s %(levelname)s]\t%(message)s')
	else:
		logging.basicConfig(level = logging.INFO, format = '[%(asctime)s %(levelname)s]\t%(message)s')

	signal.signal(signal.SIGINT, signal_handler)

	errbuf = bytearray()
	handle = None
	pdumper = None
	GNBYTES = args.nbytes 
	# Caso sin argumentos
	if args.tracefile is False and args.interface is False:
		logging.error('No se ha especificado interfaz ni fichero')
		parser.print_help()
		sys.exit(-1)

	# Ir a opcion --itf
	elif args.tracefile is False:
		#TODO abrir la interfaz especificada para captura o la trazaW
		handle=pcap_open_live(str(args.interface), -1, NO_PROMISC, TO_MS, errbuf)
		#TODO abrir un dumper para volcar el tráfico (si se ha especificado interfaz) 
		descr = pcap_open_dead(DLT_EN10MB, ETH_FRAME_MAX)
		pdumper = pcap_dump_open(descr, 'captura.'+str(args.interface)+'.'+ str(datetime.now()+timedelta(minutes=30)) +'.pcap')
		
	# Ir a opcion --file
	elif args.interface is False:
		line_count = 0
		handle = pcap_open_offline(args.tracefile, errbuf)
		if handle is None:
			print("Error al abrir el archivo .pcap")


	# Procesamiento de la traza/interfaz
	ret = pcap_loop(handle,-1,procesa_paquete, None)
	if ret == -1:
		logging.error('Error al capturar un paquete')
	elif ret == -2:
		logging.debug('pcap_breakloop() llamado')
	elif ret == 0:
		logging.debug('No mas paquetes o limite superado')
	logging.info('{} paquetes procesados'.format(num_paquete))
	#TODO si se ha creado un dumper cerrarlo
	if pdumper is not None:
		pcap_close(descr)
		pcap_dump_close(pdumper)
	