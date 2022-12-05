#!/usr/bin/python
# -*- coding: utf-8 -*-
import socket
import sys
import os
import struct
import time
import argparse
from decimal import *

#Разбор аргументов
parser = argparse.ArgumentParser(description='Регистрация навигационных данных')
parser.add_argument('-f', type=str, default='out.gpx', help='Имя файла выходных данных (по умолчанию: out.gpx)')
parser.add_argument('-t', type=int, default=3, help='Время записи (по умолчанию: 3 секунды)')
parser.add_argument('-d', type=str, default='192.168.1.47:9955', help='Устройство (по умолчанию: 192.168.1.47:9955)')
args = parser.parse_args()
args = parser.parse_args()

gpxfn = args.f
timedur = args.t
ttyname = args.d



(adr, port) = ttyname.split(':')
bufferSize  = 1024

UDPServerSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)
UDPServerSocket.settimeout(3)

address = (adr, int(port))

gpxfile = open(gpxfn, 'w')
gpxfile.write("<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n<gpx version=\"1.1\"><metadata></metadata><trk><trkseg>\n")

start = time.time()
while (time.time() - start) < timedur:
	
    UDPServerSocket.sendto(b'$BIN', address)

    bytesAddressPair = UDPServerSocket.recvfrom(bufferSize)
    message = bytesAddressPair[0]
    address = bytesAddressPair[1]

    (head, speed, lat, lon, elv, direct, fix, sats, day, mon, year, hour, minutes, sec) = struct.unpack('=1L1f1d1d1f1f1B1H1B1B1H1B1B1f', message)

    
    string = "<trkpt lat=\"%f\" lon=\"%f\">\n\
  <ele>%f</ele>\n\
  <time>%d-%d-%dT%02d:%02d:%.1fZ</time>\n\
  <speed>%f</speed>\n\
  <direction>%f</direction>\n\
  <fix>%d</fix>\n\
  <sats>%d</sats>\n\
</trkpt>\n" % (lat, lon, elv, int(year), int(mon), int(day), int(hour), int(minutes), sec, speed, direct, fix, sats)
    gpxfile.write(string)
    
    
    #print(string)
    time.sleep(0.2)

gpxfile.write("</trkseg></trk></gpx>\n")		
gpxfile.close()
