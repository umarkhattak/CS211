#!/usr/bin/python

import os, sys, glob, time, subprocess, signal
import popen2
import time

hwName = 'hw6'
programs = ['first']

# if a program has single liner input and output, we put all test cases in single file. Otherwise, we have a file for test and associated file with results
formats = {'first':'file'}

weight = {'first':1}

total = {'first':100}

runtime = {'first':2050}

test_cases_directory = ""

class ExperimentError(Exception):
    def __init__(self, command, output):
        self.command = command
        limit = 10000
        if(len(output) > limit):
          self.output = output[:limit/2] + "\n\n...TRUNCATED...\n\n" + output[-limit/2:]
        else:
          self.output = output
    def __str__(self):
        return "ExperimentError:" + `self.command`

def run_command(command_string, input_string="", max_lines=0,
                timeout=20, verbose=False, echo=False, throw_exception=True,
                return_valgrind_output=False, user_program=False):
    if echo:
        print "executing:", command_string
    obj = popen2.Popen4(command_string)
    output = ""
    valgrind_output = ""
    obj.tochild.write(input_string)
    obj.tochild.close()
    valgrind_prefix = "==%d==" % obj.pid
    maxSleep = timeout
    if user_program: #program may have an infinite loop
        while maxSleep>0:
            time.sleep(0.25)
            maxSleep-=1
            if obj.poll()!=-1:
                break
        if maxSleep==0 and obj.poll()==-1:
            os.kill(obj.pid, signal.SIGKILL)
            print command_string, " taking longer than expected. Killed."
            return ""
    line = obj.fromchild.readline()
    while (line):
        if verbose == 1:
            print line,
        if line.startswith(valgrind_prefix):
            valgrind_output += line
        output += line
        line = obj.fromchild.readline()
    exit_status = obj.wait()
    if(max_lines != 0):
        lines = output.split("\n")
        output = string.join(lines[-max_lines:], "\n")
    if throw_exception and exit_status != 0:
        raise ExperimentError(command_string, output)

    if return_valgrind_output:
        return valgrind_output
    else:
        return output

def compare_string_file(ref_file, test_string, show_difference=False):
    test_list=test_string.split("\n")
    fd = open(ref_file)
    i=0
    flag=True
    for line in fd:
        if i<len(test_list):
            if line.strip()!=test_list[i].strip():
                flag=False
        elif len(line.strip())>0:
            print "Output missing: ", line
            flag=False
        i+=1

    fd.close()
    while(i<len(test_list)):
        if len(test_list[i].strip())==0:
            i+=1
            continue
        print "Extra output: ", test_list[i]
        i+=1
        flag=False
    return flag

def compare_string(ref, test):
    ref = ref.strip()
    test = test.strip()

    if(ref==test):
        return True
    if(ref==test.lower()):
        print "%s and %s are in different case. Please print your output in correct case."%(ref, test)
    return False


def make_executable(dirname):
    if os.path.isfile('Makefile') or os.path.isfile('makefile'):
        run_command("make clean", verbose=False)
        run_command("make", verbose=True)
    else:
        print "No Makefile found in", dirname
        print "Please submit a Makefile to receive full grade."
        run_command("gcc -o %s *.c *.h"%(dirname), verbose=False)


def file_grade(dirname):
    print "Grading file", dirname
    score = 0
    try:
        make_executable(dirname)
    except Exception as e:
        print "An exception occured trying to execute %s"%(dirname)
        print(e)
	print "Score is ", score
        return

    if not os.path.isfile(dirname):
        print "Executable %s missing. Please check the compilation output."%(dirname)
	print "Score is ", score
        return

    output = "output"
    input = "input"
    input_dir = test_cases_directory + dirname  + "/" + input
    output_dir = test_cases_directory + dirname  + "/" + output

    for testfile in sorted(os.listdir(input_dir)):
        if os.path.isdir(testfile) or not testfile.startswith("trace"):
            continue
        for resultfile in sorted(os.listdir(output_dir)):

            if resultfile.startswith("one") and  (not testfile[len(resultfile)-4] == "1"):
                continue
            elif resultfile.startswith("two") and (not testfile[len(resultfile)-4] == "2"):
                continue
            elif resultfile.startswith("thr") and (not testfile[len(resultfile)-4] == "3"):
                continue
            elif resultfile.startswith("fou") and (not testfile[len(resultfile)-4] == "4"):
                continue
            else:
                print ""

            paramsets = [ "128 assoc:4 lru 4",
                          "128 assoc:4 fifo 4",
                          "32 direct lru 4",
                          "32 direct fifo 4" ]
            index = int(resultfile[len(resultfile)-5])

            try:
                run_command("./%s %s %s > %s"%(dirname, paramsets[index - 1], input_dir + "/" + testfile,resultfile), timeout=runtime[dirname], user_program=True, echo=True)
            except Exception as e:
                print "An exception occurred while executing %s %s"%(dirname, testfile)
                print(e)
                print "score is ", score

            command = "diff " + output_dir + "/" +resultfile + " " + resultfile + " >/dev/null"
            if os.system(command)==0:
                print resultfile + " is correct"
                score = score + 3.125
            else:
                print resultfile + " is not correct"

    print "Your score is " , score

def single_grade(dirname):
    # not needed for this assignment
    pass

def global_grade(dirname):
    for prog in programs:
        if prog in formats and formats[prog]=='line':
            single_grade(prog)
        elif prog in formats and formats[prog]=='file':
            file_grade(prog)

if __name__ == '__main__':
    tarmode = False # by default check the directory

    test_cases_directory = os.getcwd() + "/testcases/"
    if len(sys.argv)>1:
        if sys.argv[1].strip().endswith("tar"):
            tarmode=True

    if tarmode:
        prevdir = os.getcwd()
	print "dir is ", prevdir
        if not os.path.exists("%s.tar" % hwName):
            print "Expecting %s.tar in current directory. Current directory is %s"%(hwName, prevdir)
            print "Please make sure you created %s.tar in the right directory" % hwName
            sys.exit(1)
        if os.path.exists("obj_temp"):
            print "Deleting the directory obj_temp."
            run_command("rm -rf obj_temp", verbose=False)
        run_command("mkdir obj_temp", verbose=False)
        os.chdir("obj_temp")
        run_command("tar -xvf ../%s.tar" % hwName)
        if os.path.isdir(hwName):
            os.chdir(hwName)
            global_grade(hwName)
        else:
            print "There is no directory named %s in %s.tar." % (hwName, hwName)
            print "Please check your tar file."
        os.chdir(prevdir)
    else:
        if not os.path.isdir(hwName):
            print "%s is not present in this directory." % hwName
            sys.exit(1)
        else:
	    if os.path.exists("obj_temp"):
            	run_command("rm -rf obj_temp", verbose=False)
            run_command("mkdir obj_temp", verbose=False)
            os.chdir("obj_temp")
            run_command("cp -r ../%s ." % hwName)
            if os.path.isdir(hwName):
                os.chdir(hwName)
   	        print "Grading the content of %s." % hwName

            global_grade(hwName)
