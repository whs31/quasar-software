#!/usr/bin/python
# -*- coding: utf-8 -*-

import socket
import navthread
import sys
import os
import struct
import time
import subprocess

#для рабочей консоли на windows
from colorama import just_fix_windows_console
just_fix_windows_console()
#------------------------------


localIP     = "127.0.0.1"
localPort   = 25565
bufferSize  = 1024

TCPServerSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_STREAM)
TCPServerSocket.bind((localIP, localPort))
TCPServerSocket.listen()


ts = time.localtime()
start_time = time.strftime("%H:%M:%S", ts)
print("Сервер TCP-IP работает на адресе "+localIP+":"+str(localPort)+" и ожидает приема данных                ( " +start_time+" )")

nt = navthread.NavThread(True)
nt.start()

conn, addr = TCPServerSocket.accept()
with conn:
    print (f"Подключено к {addr}")
    while(1):
        try:
            bytesAddressPair = conn.recv(bufferSize)
        except KeyboardInterrupt:
            #nt.exit()
            UDPServerSocket.close()
            os.kill(0, 9)

        message = bytesAddressPair
        #address = bytesAddressPair[1]
        messageStr = str(message, 'utf-8') 
        #print ('Recv:', message) 
        data = str.encode("$"+str(nt.lat)+"@"+str(nt.lon)+"@"+str(nt.speed)+"@"+str(nt.elv)+"#")
        #data = struct.pack('ddff', nt.lat, nt.lon, nt.speed, nt.elv)
        if(messageStr == "$request"):
            conn.sendall(data) 
            t = time.localtime() 
            current_time = time.strftime("%H:%M:%S", t)
        
            print("[REMOTE] Передача телеметрии                                                            ( "+current_time+" )",end='\r')
            print("\033[F")
        if(messageStr == "$form-SAR-image"):
            conn.sendall(str.encode("$>>Формирование РЛИ...#"))
            print ("\n[REMOTE] Получена команда на формирование РЛИ") 
            p1 = subprocess.Popen(['python', r'./start.py'])
            p1.wait()
