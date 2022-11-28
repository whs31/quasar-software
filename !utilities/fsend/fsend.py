#!/usr/bin/python3
# -*- coding: utf-8 -*-
import os
import sys
import config
import serviced
import time

def main(cmd):
    defaults = {'daemonize': False}
    cfg = config.read('main', defaults)
    s = serviced.serviced()
    s.command(cmd)



if __name__ == "__main__":
    cmd = ''
    if(len(sys.argv) == 1):
        cmd = 'status'
    else:
        #print(sys.argv)
        #cmd = ' '.join( map(str, sys.argv[1:]) )
        for c in sys.argv[1:]:
            cmd += "{}".format(c)
    main(cmd)
