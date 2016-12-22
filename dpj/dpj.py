#!/usr/bin/python3.5
# -*- coding: utf-8 -*-
import os
import sys
args_1 = sys.argv[1]
os.rename(args_1,"test.c")
os.system("sdcc test.c << packihx > test.hex |  hex2bin test.hex | sudo stcflash test.bin") 
