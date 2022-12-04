defaults = {'baud':'115200', 'ttyname':'/dev/ttyUSB0'}


def run(parent, cfg):
    import serial
    from micropyGPS import MicropyGPS
    import time
    
    com = None
    baud  = cfg['baud']
    
    ttyname = cfg['ttyname']
    
    gps = MicropyGPS(location_formatting='dd')
    
    while(parent.running):
        
        com = None
    
        print('Try to connect to {} ({})...'.format(ttyname, baud))
        while(com == None):
            try:
                com = serial.Serial(port=ttyname, baudrate=baud)
            except serial.SerialException:
                time.sleep(2)
            
        print('OK')


        try:
            com.write( b"PUBX,40,GLL,0,0,0,0\r\n");
            com.write( b"PUBX,40,VTG,0,0,0,0\r\n");
            com.write( b"PUBX,40,GSV,0,0,0,0\r\n");
            
            com.write( b"PUBX,40,RMC,1,1,1,0*46\r\n");
            
            com.write( b"\xB5\x62\x06\x08\x06\x00\xC8\x00\x01\x00\x01\x00\xDE\x6A");
            com.write( b"\xB5\x62\x06\x00\x01\x00\x01\x08\x22");
        except serial.SerialException:
            com.close()
            pass
            
        
        print('Running')
        
        while(parent.running):
            
            try:
                buf = com.read(128)
            except serial.SerialException:
                print('Serial lost...')
                break

            for x in buf:
                if gps.update(x) is not None:
                    if(parent.gpx.sec != gps.timestamp[2]):
                        parent.gpx.speed = gps.speed[2]
                        parent.gpx.lat = gps.latitude[0]
                        parent.gpx.lon = gps.longitude[0]
                        parent.gpx.elv = gps.altitude
                        parent.gpx.direct = gps.course
                        parent.gpx.fix = gps.fix_type
                        parent.gpx.sats = gps.satellites_in_use
                        parent.gpx.day = gps.date[0]
                        parent.gpx.mon = gps.date[1]
                        parent.gpx.year = gps.date[2]
                        parent.gpx.hour = gps.timestamp[0]
                        parent.gpx.minutes = gps.timestamp[1]
                        parent.gpx.sec = gps.timestamp[2] 

        
        com.close()
