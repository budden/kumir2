#!/usr/bin/python2
# coding=UTF-8

import sys
import os.path
import os
import subprocess
import inspect
import threading
import json

# Assume this file located in ${KUMIR_DIR}/testing/scripts
KUMIR_DIR = os.path.abspath(inspect.getfile(inspect.currentframe())+os.path.sep+".."+os.path.sep+".."+os.path.sep+"..")

# Check if kumir dir is specified in commandline
for arg in sys.argv:
    if arg.startswith("--kumirdir="):
        KUMIR_DIR = arg[len("--kumirdir="):]


TIMEOUT = 30
for arg in sys.argv:
    if arg.startswith("--timeout="):
        TIMEOUT = int(arg[len("--timeout="):])

SYSTEMENCODING = "UTF-8"
if os.name=="nt":
    SYSTEMENCODING = "CP1251"
for arg in sys.argv:
    if arg.startswith("--encoding="):
        KUMIR_DIR = arg[len("--encoding="):]

class CompileError:
    """
    line: line number (start from 1)
    pos: error position start in line (start from 1)
    length: error length in line
    """
    def __init__(self, err_string):
        "Creates error from error string"
        lexems = err_string.split(":", 5)
        self.line = int(lexems[2])
        linepos = lexems[3].split("-")
        self.pos = int(linepos[0])
        self.length = int(linepos[1])
        self.text = unicode(lexems[4], SYSTEMENCODING)

    def __str__(self):
        return json.dumps({
                "line": self.line,
                "pos": self.pos,
                "length": self.length,
                "text": self.text
            }, ensure_ascii=False).encode(SYSTEMENCODING)

def __binary_path(util):
    "Returns absolute file path to execuable"
    res = KUMIR_DIR+os.path.sep+"bin"+os.path.sep+util
    if os.name=="nt":
        res += ".exe"
    return res

def __run_util(args):
    "Starts a process and returns what process returns"
    proc = subprocess.Popen(args, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    out, err = proc.communicate()
    err = err.strip()
    if len(err)>0:
        errors = err.split("\n")
    else:
        errors = []
    return out, errors

class __TimeableProcess:
    def __init__(self):
        self.proc = None
        self.out, self.err = None, None
        self.indata = None
        self.args = None
    def __thread_run(self):
        self.proc = subprocess.Popen(self.args, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        self.out, self.err = self.proc.communicate(self.indata)
    def start(self, args, indata):
        self.args = args
        self.indata = indata
        thread = threading.Thread(target=self.__thread_run)
        thread.start()
        thread.join(TIMEOUT)
        if thread.is_alive():
            self.proc.kill()
            thread.join()
        return self.out, self.err

def __run_program(args, indata):
    "Starts a process, passes indata and returns when process returns or timeout"
    tp = __TimeableProcess()
    return tp.start(args, indata)
    

def compile_to_bytecode(kumfile):
    "Compiles a kumir program file into kumir bytecode file"
    out, errors = __run_util([__binary_path("kumir2-bc"), kumfile])
    return map(lambda x: CompileError(x), errors)

def compile_to_native(kumfile):
    "Compiles a kumir program file into native execuable file"
    out, errors = __run_util([__binary_path("kumir2-cc"), kumfile])
    return map(lambda x: CompileError(x), errors)

def run_bytecode(kodfile, indata):
    "Evaluates kumir bytecode and returns output, then input"
    return __run_program([__binary_path("kumir2-run"), kodfile], indata)

def print_usage_and_exit(errcode):
    sys.stderr.write("""Usage:
    %s [--kumirdir=KUMIR_DIR] bc FILENAME.kum
or:
    %s [--kumirdir=KUMIR_DIR] cc FILENAME.kum
or:
    %s [--kumirdir=KUMIR_DIR] [--timeout=TIMEOUT] run FILENAME.kum [OUTFILE.txt] [INFILE.txt]
""" % ( sys.argv[0], sys.argv[0], sys.argv[0]) )
    sys.exit(errcode)

if __name__=="__main__":
    mode = None
    filename = None
    outfile = None
    infile = None
    for arg in sys.argv:
        if mode==None and arg=="bc":
            mode = "bc"
        elif mode==None and arg=="cc":
            mode = "cc"
        elif mode==None and arg=="run":
            mode = "run"
        elif mode!=None and filename==None:
            filename = arg
        elif mode!=None and filename!=None and outfile==None:
            outfile = arg
        elif mode!=None and filename!=None and outfile!=None and infile==None:
            infile = arg
    if mode is None:
        print_usage_and_exit(127)
    elif mode=="bc":
        errs = compile_to_bytecode(filename)
        for err in errs:
            sys.stderr.write(str(err)+"\n")
    elif mode=="cc":
        errs = compile_to_native(filename)
        for err in errs:
            sys.stderr.write(str(err)+"\n")
    elif mode=="run":
        indata = None
        if infile:
            f = open(infile, 'r')
            indata = f.read()
            f.close()
        out, err = run_bytecode(filename, indata)
        if err and len(err.strip())>0:
            sys.stderr.write(err.strip()+"\n")
        if out and outfile:
            f = open(outfile, 'w')
            f.write(out)
            f.close()
        elif out:
            sys.stdout.write(out)
        
