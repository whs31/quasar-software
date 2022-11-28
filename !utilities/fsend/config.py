#!/usr/bin/python
# -*- coding: utf-8 -*-
import os


            
def read(cfg, defaults=None):
    
    cfgDir = './cfg/'

    if(not os.path.exists(cfgDir)):
        os.makedirs(cfgDir)
        
    
    retDict = {}
    path = '{}/{}.cfg'.format(cfgDir, cfg)
    
    if(not os.path.isfile(path)):
        print('Creating config file {}'.format(path) )
        
        configFile = open(path, 'w')
        if(defaults):
            for key, value in defaults.items() :
                configFile.write('{} = {}\n'.format(key, repr(value) ))
        configFile.close()
        
    configFile = open(path)
    exec(configFile.read(), globals(), retDict)
    configFile.close()
    
    return retDict
        
