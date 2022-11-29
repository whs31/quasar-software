#!/usr/bin/python
# -*- coding: utf-8 -*-
import socket
import sys

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_address = ('localhost', 10000)
sock.bind(server_address)

sock.listen(1)

print('Waiting for a connection')
connection, client_address = sock.accept()

#f = open('out.jpg', 'wb')

head = True

f = None

data = connection.recv(1024)

p = data.find(b'\0')
print(len(data))
fn = data[:p]
print(fn)
f = open('out-'+str(fn.decode('utf-8')), 'wb')
data = data[p+1:]

head = False

while(1):
    data = connection.recv(1024)
    
    if not data:
        break
    
    f.write(data)


f.close()
sock.close()
