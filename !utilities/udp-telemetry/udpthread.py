#!/usr/bin/python
# -*- coding: utf-8 -*-

import socket
import navthread
import sys
import os
import struct

localIP     = "192.168.1.1"
localPort   = 9846
bufferSize  = 1024

UDPServerSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)
UDPServerSocket.bind((localIP, localPort))

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
    data = b'$TEST' 
    UDPServerSocket.sendto(data, address)
