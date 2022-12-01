#!/usr/bin/python3
# -*- coding: utf-8 -*-
import time
import sys
import pywintypes, win32pipe, win32file


class Pipe():
    def __init__(self):
        self.pipe = None
        self.name = None

    def create(self, name):
        self.name = name
        self.pipe = win32pipe.CreateNamedPipe(
        r'\\.\pipe\\' + name,
        win32pipe.PIPE_ACCESS_DUPLEX,
        win32pipe.PIPE_TYPE_MESSAGE | win32pipe.PIPE_READMODE_MESSAGE | win32pipe.PIPE_WAIT,
        1, 65536, 65536,
        0,
        None)
    
    def connect(self, name):
        self.name = name
        self.pipe = win32file.CreateFile(
            r'\\.\pipe\\' + name,
            win32file.GENERIC_READ | win32file.GENERIC_WRITE,
            0,
            None,
            win32file.OPEN_EXISTING,
            0,
            None
        )
        res = win32pipe.SetNamedPipeHandleState(self.pipe, win32pipe.PIPE_READMODE_MESSAGE, None, None)

    def write(self, data):
        win32file.WriteFile(self.pipe, data)
        
    def read(self):
        try:
            win32pipe.ConnectNamedPipe(self.pipe, None)
            _, data = win32file.ReadFile(self.pipe, 64*1024)
            return data
        
        except pywintypes.error as e:
            #print(e)
            pass
            #if(e.args[0] == 109):
            #    win32pipe.DisconnectNamedPipe(self.pipe)
            #    win32file.CloseHandle(self.pipe)
        return None
        
                
    def close(self):
        win32file.CloseHandle(self.pipe)
    
    def reinit(self):
        self.close()
        self.create(self.name)

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
