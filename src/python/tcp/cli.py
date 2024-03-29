#!/usr/bin/python
# -*- coding: utf-8 -*-
import socket
import sys
import time
import os

chunk_size = 1024
fileName = 'm4-13-12-2022_21-19-14.jpg'
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_address = ('127.0.0.1', 10000)

sock.connect(server_address)

filesize = os.path.getsize(fileName)

print(filesize)
fileinfo = (fileName + '\n').encode() + filesize.to_bytes(4, byteorder='little')

print(fileinfo)

sock.send(fileinfo)

f = open(fileName, 'rb')

for chunk in iter(lambda: f.read(chunk_size), b''):
    sock.send(chunk)
    
    # Имитация медленного канала
    time.sleep(0.015)
print('Sending done')
sock.shutdown(socket.SHUT_WR)
f.close()
sock.close()
