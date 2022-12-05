#!/usr/bin/python3
# -*- coding: utf-8 -*-
import os
import sys
import config
import serviced
import argparse
import logging

def main():
    defaults = {'daemonize': False, 'address': '127.0.0.1:10000'}
    
    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        handlers=[
            logging.FileHandler("fsend.log"),
            logging.StreamHandler()
        ]
    )
    
    
    cfg = config.read('main', defaults)
    
    
    parser = argparse.ArgumentParser(description='Сервис для передачи файлов')
    parser.add_argument('-f', type=str, default=None, help='Имя файла')
    parser.add_argument('-a', type=str, default=cfg['address'], help='Адрес сервера для приема')
    parser.add_argument('-s', help='Статус', action='store_true')
    parser.add_argument('-d', default=cfg['daemonize'], help='Запуск в фоновом режиме', action='store_true')
    parser.add_argument('-k', help='Остановка процесса в фоновом режиме', action='store_true')
    
    args = parser.parse_args()
    
    s = serviced.serviced(args)
    
    if(not s.extra(args)):
        s.append(args.a, args.f)



if __name__ == "__main__":

    os.chdir(os.path.dirname(os.path.abspath(__file__)))
    main()
