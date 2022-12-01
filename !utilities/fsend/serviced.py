#!/usr/bin/python3
# -*- coding: utf-8 -*-
import threading
import os
import errno
import time
import psutil
import time
import socket
import logging

if(os.name == 'posix'):
    import pipe_posix as pipe
else:
    import pipe_windows as pipe

FIFO = 'fsend.pipe'
LOCKFILE = "fsend.lock"

class Sender(threading.Thread):
    def __init__(self, parent):
        super().__init__()

        logging.info('Сервис запущен')
        self.fileList = []
        self.parent = parent
        lockfile = open(LOCKFILE, "w")
        lockfile.write( str(os.getpid()) )
        lockfile.close()
        
        self.sem = threading.Semaphore(value=0) 

    def run(self):
        while(self.parent.running):
            self.sem.acquire()
            tmp = self.fileList.pop(0)
            address, fileName = tmp.split('\n')
            self.sendFile(address, fileName)
            
    def readCommand(self):
        p = pipe.Pipe()
        p.create(FIFO)

        while(self.parent.running):
            d = p.read()
            if(d == None):
                p.reinit()
                continue
            
            if(d == b'\x00status'):
                self.status(p)
                continue
            
            self.fileList.append(d.decode("utf-8") )
            self.sem.release()
            
    def sendFile(self, address, fileName):
        chunk_size = 1024
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.settimeout(5)
        ip, port = address.split(':')
        server_address = (ip, int(port))
        
        logging.info('Подключение {}:{}'.format(ip, port))
        try:
            sock.connect(server_address)
        except socket.error as err:
            logging.error(err)
            return

        try:
            filesize = os.path.getsize(fileName)
            
            f = open(fileName, 'rb')
        except:
            logging.error('Ошибка: файла {} не существует'.format(fileName))
            return
        
        logging.info('Передача файла: {}'.format(fileName))
        logging.info(filesize, 'байт')
        
        fileinfo = (os.path.basename(fileName).encode() + b'\0') + filesize.to_bytes(4, byteorder='little')
        sock.send(fileinfo)
        
        for chunk in iter(lambda: f.read(chunk_size), b''):
            
            try:
                sock.send(chunk)
            except socket.error as err:
                logging.error(err)
                return
            
        logging.info('Передача завершена')
        sock.shutdown(socket.SHUT_WR)
        f.close()
        sock.close()
        
    def status(self, p):
        s = b'STATUS'
        #p.write(s)
        logging.info(s)

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

        return psutil.pid_exists(pid)

    def append(self, adr, fn):
        
        cmd = '{}\n{}'.format(adr, fn)

        if(not self.active()):
            sender = Sender(self)
            sender.start()
            if(fn):
                sender.fileList.append(cmd)
                sender.sem.release()
            
            sender.readCommand()
        else:
            p = pipe.Pipe()
            p.connect(FIFO)
            p.write(cmd.encode())
            p.close()
            
    def status(self):
        if(self.active()):
                p = pipe.Pipe()
                p.connect(FIFO)
                p.write(b'\x00status')
                p.close()
        else:
            logging.info('Сервис не активен')
        



