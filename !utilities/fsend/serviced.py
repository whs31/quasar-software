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
import sys

if(os.name == 'posix'):
    import pipe_posix as pipe
else:
    import pipe_windows as pipe

FIFO_IN = 'fsend.pipe.in'
FIFO_OUT = 'fsend.pipe.out'
LOCKFILE = "fsend.lock"

class Sender(threading.Thread):
    def __init__(self, parent):
        super().__init__()

        logging.info('Сервис запущен ({})'.format(os.getpid()))
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
        pipeIn = pipe.Pipe()
        pipeIn.create(FIFO_IN)
        
        pipeOut = pipe.Pipe()
        pipeOut.create(FIFO_OUT)

        while(self.parent.running):
            d = pipeIn.read()
            if(d == None):
                pipeIn.reinit()
                continue
            elif(d == b'\x00status'):
                self.status(pipeOut)
                continue
            elif(d == b'\x00stop'):
                logging.info('Сервис остановлен ({})'.format(os.getpid()))
                os._exit(0)
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
        logging.info('Объем файла: {} байт'.format(filesize) )
        
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
        s = 'На очереди {} файл(ов)'.format(len(self.fileList))
        p.write(s.encode())
        logging.info(s)

class serviced():

    def __init__(self, args):
        self.args = args
        self.running = True
        
        
    def daemonize(self):
        try:
            pid = os.fork()
            if pid > 0:
                sys.exit(0)
        except OSError as err:
            logging.error('Ошибка запуска в фоновом режиме: {0}\n'.format(err))
            sys.exit(1)
        
        #os.chdir('/')
        os.setsid()
        os.umask(0)

        try:
            pid = os.fork()
            if pid > 0:
                sys.exit(0)
        except OSError as err:
            logging.error('Ошибка запуска в фоновом режиме: {0}\n'.format(err))
            sys.exit(1)

        sys.stdout.flush()
        sys.stderr.flush()
        si = open(os.devnull, 'r')
        so = open(os.devnull, 'w')
        se = open(os.devnull, 'w')
        os.dup2(si.fileno(), sys.stdin.fileno())
        os.dup2(so.fileno(), sys.stdout.fileno())
        os.dup2(se.fileno(), sys.stderr.fileno())

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
        
    def sendToService(self, cmd):
        p = pipe.Pipe()
        p.connect(FIFO_IN)
        p.write(cmd.encode())
        p.close()
        
    def readFromService(self):
        p = pipe.Pipe()
        p.connect(FIFO_OUT)
        d = p.read()
        p.close()
        
        return d.decode('utf-8')

    def append(self, adr, fn):
        
        cmd = '{}\n{}'.format(adr, fn)

        if(not self.active()):
            
            if(self.args.d):
                self.daemonize()
            
            sender = Sender(self)
            sender.start()
            if(fn):
                sender.fileList.append(cmd)
                sender.sem.release()
            
            sender.readCommand()
        else:                
            self.sendToService(cmd)
            
    def extra(self, args):
        if(self.args.k):
            self.sendToService('\0stop')
            return True
        if(self.args.s):
            self.status()
            return True
        
        return False
            
    def status(self):
        if(self.active()):
                self.sendToService('\0status')
                print(self.readFromService())
        else:
            logging.info('Сервис не активен')
        



