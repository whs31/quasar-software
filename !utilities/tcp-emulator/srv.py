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

while(1):
    data = connection.recv(1024)
    
    if(head):
        
        p = data.find(b'\n')
        if(p > -1):
            fn = data[:p]
            f = open('out-'+str(fn), 'wb')
            data = data[p+1:]
            print(data)
            head = False
            
        else:
            # Значит, вместо заголовка пришла какая-то херня
            # Нужно придумать исключение
            pass
    
    if(f):
        f.write(data)
    
    
    if not data:
        break


f.close()
sock.close()
