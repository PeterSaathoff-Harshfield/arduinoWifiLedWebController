#!/usr/bin/env python3.7

import glob
import time
import re
import sys
import os
import json

minify = False

filename = ""

if len(sys.argv) > 1:
    filename = sys.argv[1]
else:
    print(f"usage: filename.html")
    sys.exit(0)

run = False
if len(sys.argv) > 2:
    run = sys.argv[2] == "run"

print(f"html2c {filename}", end='')
print("")

def process(filename, outfile):
    try:

        f = open(filename, "r")
        text = f.read()
        out = f"char {base}[] = \""
        lastspace = False
        for c in text:
            #print(f"c {c}")
            if minify:
                if c == ' ' or c == '\r' or c == '\n' or c == '\t':
                    if lastspace == False:
                        out = out + " "
                    lastspace = True
                    pass
                elif c == '\"':
                    out = out + "\\\""
                    lastspace = False
                else:
                    out = out + c
                    lastspace = False
            else:
                if c == '\r':
                    pass
                elif c == '\n':
                    out = out + "\\r\\n\"\r\n\""
                elif c == '\"':
                    out = out + "\\\""
                else:
                    out = out + c
                pass
        out = out + "\";\r\n"
        #print(f"out: {out}")
        print(f"Input length: {len(text)}  Output length: {len(out)}")

        o = open(outfile, "w")
        o.write(out)
        print(f"Wrote output: {outfile}")
    except FileNotFoundError:
        print(f"File not found: {filename}")
        sys.exit(0)
    except SystemExit:
        pass
    except:
        print(f"Error: {sys.exc_info()[0]}")
        sys.exit(0)

dot = filename.find(".html")
if dot == -1:
    print(f"usage: filename.html")
    sys.exit(0)
base = filename[0:dot]
outfile = filename[0:dot] + ".c"

if run:
    while True:
        desttime = 0
        srctime = os.path.getmtime(filename)
        if os.path.exists(outfile):
            desttime = os.path.getmtime(outfile)
        #print(f"srctime {srctime}")
        #print(f"desttime {desttime}")
        if srctime > desttime:
            process(filename, outfile)
        time.sleep(1)
else:
    process(filename, outfile)
