#!/usr/bin/python
# -*- coding: utf-8 -*-

import socket
import sys
import os
import struct
import config
import json
import time
from decimal import *
from datetime import datetime
import threading
import deconstruct as c

class gpx_t(c.Struct):
    
    __byte_order__ = c.ByteOrder.NATIVE
    __type_width__ = c.TypeWidth.STANDARD

    head: c.uint32
    speed: c.float
    lat: c.double
    lon: c.double
    elv: c.float
    direct: c.float
    fix: c.uint8
    sats: c.uint16
    day: c.uint8
    mon: c.uint8
    year: c.uint16
    hour: c.uint8
    minutes: c.uint8
    sec: c.float

class NavHandler(threading.Thread):
    def __init__(self, mode):
        threading.Thread.__init__(self)
        self.mode = mode   
        
        self.gpx = gpx_t()     
        self.running = True
        

    def run(self):
        
        if(self.mode == 'test'):
            import support.test as worker
        elif(self.mode == 'nmea_serial'):
            import support.nmea_serial as worker
        elif(self.mode == 'vt45'):
            import support.vt45 as worker
        else:
            print('Error: have no mode ({})'.format(self.mode))
            return
            
        cfg = config.read(self.mode, worker.defaults)
        
        worker.run(self, cfg)
        
            
    def stop(self):
        self.running = False 




if __name__ == "__main__":
    defaults = {'ip':'192.168.1.47', 'port':9955, 'profile':'vt45'}

    cfg = config.read('main', defaults)

    localIP     = cfg['ip']
    localPort   = cfg['port']
    bufferSize  = 1024

    UDPServerSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)
    UDPServerSocket.bind((localIP, localPort))

    print("UDP server up and listening")

    nt = NavHandler(cfg['profile'])
    nt.start()
    
    print('Data format: ' + nt.gpx.format_string)

    while(nt.running):

        try:
            bytesAddressPair = UDPServerSocket.recvfrom(bufferSize)
        except KeyboardInterrupt:
            nt.stop()
            continue
            #os.kill(0, 9)

        message = bytesAddressPair[0]
        address = bytesAddressPair[1]
        
        if(message == b'$BIN'):
            nt.gpx.head = int.from_bytes(message, byteorder='big')
            print(nt.gpx)
            data = nt.gpx.to_bytes()
        elif(message == b'$JSON'):
            data_dict = {}

            data_dict['Latitude'] = nt.lat
            data_dict['Longitude'] = nt.lon
            data_dict['Speed'] = nt.speed
            data_dict['Elevation'] = nt.direct
            data_dict['Sats'] = nt.sats
        
            json_data = json.dumps(data_dict)
            data = b'$JSON' + json_data
        
        UDPServerSocket.sendto(data, address)

UDPServerSocket.close()
