from socket import *

serverSocket = socket(AF_INET, SOCK_DGRAM)

serverSocket.bind(('', 12000))

i = 0
while True:
    message, address = serverSocket.recvfrom(10240)
    f = open("pack/{}".format(i), 'wb')
    f.write(message)
    f.close()
    i+=1
