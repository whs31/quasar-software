import socket
import time
import support.vt45 as vt45

RUAVP_MARKER = 0xFE53

mrls_telemetry = vt45.mrls_telemetry_t()
ruavp_header = vt45.ruavp_header_t()
ruavp_control = vt45.ruavp_control_t()

server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)

server.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)

server.settimeout(0.2)

f = open('nav_dump2.bin', 'rb')
data = f.read()

while True:
    '''
    message = b''
    
    mrls_telemetry.lat += 0.1
    message += ruavp_header.to_bytes()
    message += mrls_telemetry.to_bytes()
    message += ruavp_control.to_bytes()
    
    server.sendto(message, ('<broadcast>', 4559))
    '''
    
    server.sendto(data, ('<broadcast>', 4559))
    print("message sent!")
    time.sleep(1)
