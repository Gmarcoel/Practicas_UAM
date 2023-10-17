#!/bin/bash


for i in P1-base P1-ejb-servidor-remoto P1-ejb-cliente-remoto P1-ws; do
cd $i
ant unsetup-db 
bash script_despliegue.sh
cd -
done

