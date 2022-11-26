#!/usr/bin/python
# -*- coding: utf-8 -*-

import socket
import navthread
import sys
import os
import struct
import time
import subprocess
import json

#для рабочей консоли на windows
###from colorama import just_fix_windows_console
###just_fix_windows_console()
#------------------------------


localIP     = "127.0.0.1"
localPort   = 25564
bufferSize  = 1024

UDPServerSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)
UDPServerSocket.bind((localIP, localPort))



ts = time.localtime()
start_time = time.strftime("%H:%M:%S", ts)
print("Сервер UDP работает на адресе "+localIP+":"+str(localPort)+" и ожидает приема данных                   ( " +start_time+" )")

nt = navthread.NavThread(True)
nt.start()
while(1):

    try:
        bytesAddressPair = UDPServerSocket.recvfrom(bufferSize)
    except KeyboardInterrupt:
        #nt.exit()
        UDPServerSocket.close()
        os.kill(0, 9)

    message = bytesAddressPair[0]
    address = bytesAddressPair[1]
    messageStr = str(message, 'utf-8')
    if(message == b'$JSON'):
        data_dict = {}
        data_dict['Latitude'] = nt.lat
        data_dict['Longitude'] = nt.lon
        data_dict['Speed'] = nt.speed
        data_dict['Elevation'] = nt.elv
        data_dict['Sats'] = 3
    
        json_data = json.dumps(data_dict)
        data = b'$JSON' + json_data.encode()
        
        print("[REMOTE] Передача телеметрии                                                            ( "" )",end='\r')
        print("\033[F")
        UDPServerSocket.sendto(data, address)
    if(messageStr == "$form-SAR-image"):
        UDPServerSocket.sendto(str.encode("$>>Формирование РЛИ#"), address)
        print ("\n[REMOTE] Получена команда на формирование РЛИ") 
        p1 = subprocess.Popen(['python3', r'./start.py'])
        p1.wait()
