#!/usr/bin/env python3.7

import glob
import time
import re
import sys
import os
import json

minify = False
progmem = False
run = False
filename = ""

def usage():
    print(f"usage: -r -p -m filename.html")
    print(f"    -r  run continuously")
    print(f"    -p  put strings in PROGMEM")
    print(f"    -m  minify")
    sys.exit(0)

args = sys.argv[1:]
for arg in args:
    #print(f"arg: {arg}")
    if arg[0] == '-' and len(arg) > 1:
        if arg[1] == 'r':
            run = True
        if arg[1] == 'p':
            progmem = True
        if arg[1] == 'm':
            minify = True
    else:
        if filename == "":
            filename = arg
        else:
            print(f"too many arguments")
            usage()

print(f"html2c {filename}", end='')
print("")

def process(files, outfile, includefile):
    out = f"#include <avr/pgmspace.h>\r\n\r\n"
    iout = f"#include <avr/pgmspace.h>\r\n\r\n"

    print(f"files: {files}")
    for filename in files:
        dot = filename.find(".html")
        base = filename[0:dot]
        out = out + f"const char {base}[] {'' if progmem == False else 'PROGMEM '}= \""
        iout = iout + f"extern const char {base}[]{'' if progmem == False else ' PROGMEM'};\r\n"
        sout = ""
        try:
            f = open(filename, "r")
            text = f.read()
            lastspace = False
            for c in text:
                #print(f"c {c}")
                if minify:
                    #if c == ' ' or c == '\r' or c == '\n' or c == '\t':
                    if c == ' ' or c == '\t':
                        if lastspace == False:
                            sout = sout + " "
                        lastspace = True
                        pass
                    elif c == '\n':
                        #sout = sout + "\\r\\n\"\r\n\""
                        sout = sout + "\\n"
                    elif c == '\"':
                        sout = sout + "\\\""
                        lastspace = False
                    else:
                        sout = sout + c
                        lastspace = False
                else:
                    if c == '\r':
                        pass
                    elif c == '\n':
                        #sout = sout + "\\r\\n\"\r\n\""
                        sout = sout + "\\n\\\r\n"
                    elif c == '\"':
                        sout = sout + "\\\""
                    else:
                        sout = sout + c
                    pass
            sout = sout + "\";\r\n\r\n"
            #print(f"sout: {sout}")
            print(f"{filename}\tInput length: {len(text)}  Output length: {len(sout)}")
            out = out + sout

        except FileNotFoundError:
            print(f"File not found: {filename}")
            sys.exit(0)
        except SystemExit:
            pass
        except:
            print(f"Error: {sys.exc_info()[0]}")
            sys.exit(0)
    o = open(outfile, "w")
    o.write(out)
    oi = open(includefile, "w")
    oi.write(iout)
    print(f"Wrote output: {outfile}")

#dot = filename.find(".html")
#if dot == -1:
#    print(f"error, html2c needs an html file.")
#    usage()
#base = filename[0:dot]
#outfile = filename[0:dot] + ".c"
outfile = "chtml.c"
includefile = "chtml.h"

if run:
    while True:
        srctime = 0
        desttime = 0

        if os.path.exists(outfile):
            desttime = os.path.getmtime(outfile)
        files = glob.glob(f"*.html")
        #print("html files: ", files)
        update = False
        for file in files:
            if os.path.exists(file):
                srctime = os.path.getmtime(file)
                if srctime > desttime:
                    update = True

#        if os.path.exists(filename):
#            srctime = os.path.getmtime(filename)
#        if os.path.exists(outfile):
#            desttime = os.path.getmtime(outfile)
        #print(f"srctime {srctime}")
        #print(f"desttime {desttime}")
#        if srctime > desttime:
        if len(files) > 0 and update:
            process(files, outfile, includefile)
        time.sleep(1)
else:
    files = glob.glob(f"*.html")
    process(files, outfile, includefile)
