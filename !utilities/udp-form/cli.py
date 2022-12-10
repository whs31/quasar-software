#!/usr/bin/python
# -*- coding: utf-8 -*-
import socket


'''

// Original C# algorithm
//http://www.ccontrolsys.com/w/How_to_Compute_the_Modbus_RTU_Message_CRC
UInt16 ModRTU_CRC(byte[] buf, int len)
{
  UInt16 crc = 0xFFFF;

  for (int pos = 0; pos < len; pos++) {
    crc ^= (UInt16)buf[pos];

    for (int i = 8; i != 0; i--) {
      if ((crc & 0x0001) != 0) {
        crc >>= 1;
        crc ^= 0xA001;
      }
      else
        crc >>= 1;
    }
  }
  // Помните, что младший и старший байты поменяны местами, используйте соответственно (или переворачивайте)
  return crc;
}
'''

def crc16(data):
    crc = 0xFFFF
    
    for d in data:
        crc ^= d
        
        for i in range(8, 0, -1):
            if ((crc & 0x0001) != 0):
                crc >>= 1
                crc ^= 0xA001
            else:
                crc >>= 1
    
    return '{:02x}'.format(crc)
        
    

mess_id = '0001'
mess_cmd = '$9922'

mess_len = '{:02x}'.format(len(mess_cmd))

message = ':{}|{}|{}|'.format(mess_id, mess_len, mess_cmd)
message += crc16(message.encode())
message += '\n'

print(message)


client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
addr = ("127.0.0.1", 9845)
client_socket.sendto(message.encode(), addr)

try:
    data, server = client_socket.recvfrom(1024)
    print(f'{data}')
except socket.timeout:
    print('REQUEST TIMED OUT')
