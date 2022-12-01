#!/usr/bin/python
# -*- coding: utf-8 -*-
import os
import logging

            
def read(cfg, defaults=None):
    
    cfgDir = './cfg/'

    if(not os.path.exists(cfgDir)):
        os.makedirs(cfgDir)
        
    
    retDict = {}
    path = '{}/{}.cfg'.format(cfgDir, cfg)
    
    if(not os.path.isfile(path)):
        logging.info('Creating config file {}'.format(path) )
        
        configFile = open(path, 'w')
        if(defaults):
            for key, value in defaults.items() :
                configFile.write('{} = {}\n'.format(key, repr(value) ))
        configFile.close()
        
    configFile = open(path)
    exec(configFile.read(), globals(), retDict)
    configFile.close()
    
    if(defaults):
        diff = list(set(defaults.keys()) - set(retDict.keys()))
        if(len(diff) > 0):
            
            configFile = open(path, 'w')
            for key in diff:
                retDict[key] = defaults[key]
                
            for key, value in retDict.items() :
                configFile.write('{} = {}\n'.format(key, repr(value) ))
            configFile.close()
    
    return retDict
        
