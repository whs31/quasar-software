#!/usr/bin/python3
# -*- coding: utf-8 -*-
import time
import sys
import os


class Pipe():
    def __init__(self):
        self.pipe = None
        self.name = None

    def create(self, name):
        self.name = name
        
        try:
            os.remove(name)
        except:
            pass
        os.mkfifo(name)
        
        self.pipe = os.open(name, os.O_CREAT | os.O_RDWR)

    
    def connect(self, name):
        self.name = name
        self.pipe = os.open(name, os.O_RDWR)

    def write(self, data):
        os.write(self.pipe, data)
        
    def read(self):
        return os.read(self.pipe, 1024)
        
                
    def close(self):
        os.close(self.pipe)
        
    
    def reinit(self):
        pass

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print("need s or c as argument")
    elif sys.argv[1] == "s":
        #pipe_server()
        p = Pipe();
        p.create('Foo')
        while(1):
            d = p.read()
            if(d == None):
                p.reinit()
            else:
                print( d )
    elif sys.argv[1] == "c":
        #pipe_client()
        p = Pipe();
        p.connect('Foo')
        while(1):
            print( p.write(b'some data') )
            #time.sleep(1)
    else:
        print(f"no can do: {sys.argv[1]}")
