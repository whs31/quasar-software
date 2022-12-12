#!/usr/bin/python
# -*- coding: utf-8 -*-

import time
from decimal import *
import socket
import struct
from datetime import datetime
import threading
import math

class NavThread(threading.Thread):
    def __init__(self, t=True):
        threading.Thread.__init__(self)
        self.testMode = t
        self.lat = 0.0
        self.lon = 0.0
        self.elv = 0.0
        self.speed = 0.0
        self.running = True
 
 
        
        

    def run(self):
        print ("Поток телеметрии запущен") 
        if(self.testMode):
            print ("(!)Телеметрия в тестовом режиме") 
            self.test()
            
        else:
            #self.work()
            print ("Телеметрия в рабочем режиме") 
            self.work_local()
            #print ("Телеметрия в рабочем режиме") 
        
    def test(self):
        reverseGraph = False
        
        self.lat = 60.0-0.1413
        self.lon = 30.0
        self.elv = 300.0
        self.speed = 50.0
        
        
        #60.1415
        while(1):
            lt = self.lat
            ln = self.lon
            if(reverseGraph == False and self.lat>=60.1413):
                reverseGraph = True
            if(reverseGraph == True and self.lat<=60.0-0.1413):
                reverseGraph = False
                
            if(reverseGraph == False and self.lat<=60.1413):
                self.lon = -math.sin((self.lat-60)*math.sqrt(1-50*(self.lat-60)**2))+30
                self.lat += 0.0001
            if (reverseGraph == True and self.lat>=60.0-0.1413):
                self.lon = 0.5*math.sin((self.lat-60)*math.sqrt(1-50*(self.lat-60)**2))+30
                self.lat -= 0.0001
            #self.lon = -math.sin((self.lat-60)*math.sqrt(1-50*(self.lat-60)*(self.lat-60)))+30
            #self.lat += 0.005
            self.speed = (3.6*115120*math.sqrt((self.lat-lt)**2+(self.lon-ln)**2))/(0.5) 
            self.elv += 0.1
            
            time.sleep(0.05)
        
        
            
    def work(self):
        import GPTelemetry_pb2
        MCAST_GRP = '229.10.12.90'
        MCAST_PORT = 31290


        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
        sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        sock.bind((MCAST_GRP, MCAST_PORT))
        mreq = struct.pack("4sl", socket.inet_aton(MCAST_GRP), socket.INADDR_ANY)

        sock.setsockopt(socket.IPPROTO_IP, socket.IP_ADD_MEMBERSHIP, mreq)

        tel = GPTelemetry_pb2.Telemetry()

        while(self.running):
            try:
                data, addr = sock.recvfrom(1024)
            except (socket.error, e):
                print ("Exception", e) 
                   
            p_magic = struct.unpack("BBB", data[0:3])
            p_len = int(struct.unpack("B", data[3])[0] )
            p_crc_proto = struct.unpack("B", data[4])
            p_crc_header = struct.unpack("B", data[5])
            
            #p_data = struct.unpack("s", data[6:6+p_len])
            p_data = data[6:6+p_len];
            
            
            tel.ParseFromString(p_data);
            
            unix_time = int(tel.unix_time) + (3*60*60)
            self.speed = tel.gps_speed
            air_speed = tel.air_speed
            self.lat = tel.lat
            self.lon = tel.lon
            self.elv = tel.alt_gps
            dir = tel.gps_course
            fix = 99
            sats = 777
            #print self.lat, self.lon

            date_str = datetime.utcfromtimestamp(unix_time).strftime('%Y-%m-%dT%H:%M:%S')
            

        sock.close()
        
    def work_local(self):
        import time
        import serial
        from micropyGPS import MicropyGPS

        gps = MicropyGPS(location_formatting='dd')
        ttyname = '/dev/ttyACM0'        
        try:
            com = serial.Serial(ttyname, timeout=1.0)
        except serial.SerialException:
            print('could not connect to %s' % ttyname)
            exit(-1)
            #continue
            
        while(self.running):
            for x in com.read(128):
                if(gps.update(x) != None):
                    self.speed = gps.speed[2]
                    self.lat = gps.latitude[0]
                    self.lon = gps.longitude[0]
                    self.elv = gps.altitude
                    dir = gps.course
                    fix = gps.fix_type
                    sats = gps.satellites_in_use
                    day = gps.date[0]
                    mon = gps.date[1]
                    year = gps.date[2]
                    hour = gps.timestamp[0]
                    min = gps.timestamp[1]
                    sec = gps.timestamp[2] 
        com.close()
        
        
    def stop(self):
        self.running = False 

