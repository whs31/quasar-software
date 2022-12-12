import sys
sys.path.append('./../')
import deconstruct as c
import io

defaults = {'port':4559, 'timeFromHost':True, 'log':False}

STRUCT_CRC_MRLS_TELEMETRY = 12597
RUAVP_MARKER = 0xFE53

crcCore = STRUCT_CRC_MRLS_TELEMETRY.to_bytes(2, 'little')

class mrls_telemetry_t(c.Struct):
    
    __byte_order__ = c.ByteOrder.NATIVE
    __type_width__ = c.TypeWidth.STANDARD
    
    lat: c.double
    lon: c.double
    ts: c.uint64
    altitude_abs: c.float
    altitude_gps: c.float
    ax: c.float
    ay: c.float
    az: c.float
    gx: c.float
    gy: c.float
    gz: c.float
    pitch: c.float
    roll: c.float
    vx: c.float
    vy: c.float
    vz: c.float
    yaw: c.float
    time_nanosecond: c.int32
    marker_gps: c.uint32
    time_year: c.uint16
    reserved: c.uint8
    time_day: c.uint8
    time_hour: c.uint8
    time_minute: c.uint8
    time_month: c.uint8
    time_second: c.uint8


class ruavp_header_t(c.Struct):
    
    __byte_order__ = c.ByteOrder.NATIVE
    __type_width__ = c.TypeWidth.STANDARD

    marker: c.uint16
    size: c.uint8
    source: c.uint8
    destination: c.uint8
    structure_id: c.uint8
    flags: c.uint16
    
    
class ruavp_control_t(c.Struct):
    
    __byte_order__ = c.ByteOrder.NATIVE
    __type_width__ = c.TypeWidth.STANDARD

    sid: c.uint16
    counter: c.uint32
    crc16: c.uint16


def crc16(data):
    
    def ruavp_crc_acc_buf(pcrc, buf):

        pcrc = int(pcrc)
        for p in buf:
            tmp = p ^ (pcrc & 0xff);
            tmp ^= (tmp << 4) & 0xff;
            pcrc = (pcrc >> 8) ^ (tmp << 8) ^ (tmp << 3) ^ (tmp >> 4) 
        
        return pcrc & 0xFFFF;

    c = 0xFFFF
    c = ruavp_crc_acc_buf(c, data)
    c = ruavp_crc_acc_buf(c, crcCore)
    
    return c

def run(parent, cfg):
    import socket
    from datetime import datetime
    
    print('VT45 mode')
    
    mrls_telemetry = mrls_telemetry_t()
    ruavp_header = ruavp_header_t()
    ruavp_control = ruavp_control_t()
    
    sizeOfPack = ruavp_header.sizeof + mrls_telemetry.sizeof + ruavp_control.sizeof    
    
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    
    
    if(cfg['log']):
        logFile = open('log/vt45-{}.log'.format(str(datetime.now())), 'wb')
    
    
    sock.bind( ('', cfg['port'] ) )
    timeFromHost = cfg['timeFromHost']
    while(parent.running):
        
        data, addr = sock.recvfrom(1024)
        
        if( len(data) != sizeOfPack):
            continue
        
        data = io.BytesIO(data)
        
        ruavp_header.from_bytes( data.read(ruavp_header.sizeof) )
        
        if(ruavp_header.marker != RUAVP_MARKER):
            continue
        
        
        mrls_telemetry.from_bytes( data.read(mrls_telemetry.sizeof) )
        ruavp_control.from_bytes( data.read(ruavp_control.sizeof) )
        
        if( crc16(data.getbuffer()[:-2]) != ruavp_control.crc16):
            continue
        
        #patent.updated = False
        parent.gpx.speed = mrls_telemetry.vy * 3.6
        parent.gpx.lat = mrls_telemetry.lat
        parent.gpx.lon = mrls_telemetry.lon
        parent.gpx.elv = mrls_telemetry.altitude_gps
        parent.gpx.direct = mrls_telemetry.yaw * (180.0/3.1415926535)
        parent.gpx.fix = 1
        parent.gpx.sats = 1
        
        
        if(timeFromHost):
            d = datetime.now()
            
            parent.gpx.day = d.day
            parent.gpx.mon = d.month
            parent.gpx.year = d.year
            parent.gpx.hour = d.hour
            parent.gpx.minutes = d.minute
            parent.gpx.sec = d.second + (d.microsecond/1000000)
        else:
            parent.gpx.day = mrls_telemetry.time_day
            parent.gpx.mon = mrls_telemetry.time_month
            parent.gpx.year = mrls_telemetry.time_year
            parent.gpx.hour = mrls_telemetry.time_hour
            parent.gpx.minutes = mrls_telemetry.time_minute
            parent.gpx.sec = mrls_telemetry.time_second + mrls_telemetry.time_nanosecond/1000000000
        
        if(cfg['log']):
            logFile.write(data.getbuffer())
        
    
    if(cfg['log']):
        logFile.close()
    sock.close()
