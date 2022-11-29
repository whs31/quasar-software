import threading
import os
import errno
import time
import psutil
import pipe
import time
import socket

FIFO = 'fsend.pipe'
LOCKFILE = "fsend.lock"

class Sender(threading.Thread):
    def __init__(self, parent):
        super().__init__()

        print('Запуск сервиса')
        self.fileList = []
        self.parent = parent
        lockfile = open(LOCKFILE, "w")
        lockfile.write( str(os.getpid()) )
        lockfile.close()
        
        self.sem = threading.Semaphore(value=0) 

    def run(self):
        while(self.parent.running):
            self.sem.acquire()
            fileName = self.fileList.pop(0)
            self.sendFile(fileName)
            
    def readCommand(self):
        p = pipe.Pipe()
        p.create(FIFO)

        while(self.parent.running):
            d = p.read()
            if(d == None):
                p.reinit()
                continue
            self.fileList.append(d)
            self.sem.release()
            print(d)
            
    def sendFile(self, fileName):
        chunk_size = 1024
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.settimeout(5)
        ip = 'localhost'
        port = 10000
        server_address = (ip, port)
        
        print('Подключение {}:{}'.format(ip, port))
        try:
            sock.connect(server_address)
        except socket.error as err:
            print(err)
            return

        try:
            filesize = os.path.getsize(fileName)
            f = open(fileName, 'rb')
        except:
            print('Ошибка: файла {} не существует'.format(fileName))
            return
        
        print('Передача файла: {}'.format(fileName))
        print(filesize, 'байт')
        
        fileinfo = ("m1_x1.jpg" + '\0').encode() + filesize.to_bytes(4, byteorder='little')
        sock.send(fileinfo)
        
        for chunk in iter(lambda: f.read(chunk_size), b''):
            
            try:
                sock.send(chunk)
            except socket.error as err:
                print(err)
                return
            # Имитация медленного канала
            time.sleep(0.01)
            
        print('Передача завершена')
        sock.shutdown(socket.SHUT_WR)
        f.close()
        sock.close()


class serviced():

    def __init__(self):
        self.running = True

    def active(self):

        pid = None
        try:
            lockfile = open(LOCKFILE, "r")
            pid = lockfile.read()
            lockfile.close()
        except:
            pass

        if(pid == None):
            return False
        pid = int(pid)
        print('PID:', pid)

        return psutil.pid_exists(pid)

    def command(self, cmd):

        if(not self.active()):
            sender = Sender(self)
            sender.start()
            sender.readCommand()
        else:
            p = pipe.Pipe()
            p.connect(FIFO)
            p.write(cmd.encode())
            p.close()



