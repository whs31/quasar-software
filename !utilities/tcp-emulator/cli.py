#!/usr/bin/python
# -*- coding: utf-8 -*-
import socket
import sys
import time

chunk_size = 1024
fileName = 'example.jpg'
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_address = ('localhost', 10000)

sock.connect(server_address)

sock.send(fileName + '\n')

f = open(fileName, 'rb')

for chunk in iter(lambda: f.read(chunk_size), b''):
    sock.send(chunk)
    
    # Имитация медленного канала
    time.sleep(0.02)


print('Sending done')
sock.shutdown(socket.SHUT_WR)
f.close()
sock.close()
