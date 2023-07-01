#!/usr/bin/python
# -*- coding: utf-8 -*-
import socket
from queue import Queue
import threading
import io

class _Stop:
    pass

class Sender(threading.Thread):
    def __init__(self, addr, max_pack_len):
        super().__init__()
        addr, port = addr.split(':')
        self.max_pack_len = max_pack_len
        self._STOP = _Stop()
        self.addr = ( addr, int(port) )
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) 
        self.queue = Queue()
        super().start()        
    def run(self):
        while True:
            data = self.queue.get()
            if(data == self._STOP):
                break

            packages = io.BytesIO(data)
            while True:
                pack = packages.read(self.max_pack_len)
                if(pack == b''):
                    break
                self.sock.sendto(pack, self.addr)

    def stop(self):
        self.queue.put(self._STOP)

    def put(self, data):
        self.queue.put(data)
