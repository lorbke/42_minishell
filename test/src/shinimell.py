# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_minishell.py                                  :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/20 18:11:54 by fyuzhyk           #+#    #+#              #
#    Updated: 2023/02/20 18:58:43 by fyuzhyk          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Modules
import difflib
import subprocess
from termcolor import colored
from InquirerPy import prompt

# Local modules
from print import pepe, shinimell

#1. make re before running this script
#2. exit status
#3. expansion (wildcards if bonus)
#4. output alignment
#5. useful information, regarding where to find the test e.g (like tjensen)
#6. menu where ppl (I) can choose between builtins, expansions, expansion with wildcard, or both
#7. We can try to make the tester completely interactive, by allowing people to input their own commands
# which are then executed by bash and the minishell, comparing output and exit status
# it also should be easy to add new test cases, or files

# Global Variables
# path to your minishell
minishell = "../../minishell"
# path to infile
infile_path = "../test_cases/input.txt"
# path to outfile
outfile_path = "../test_output/output.txt"

# Modes
# 1. variable expansion
expansion = "../modes/expansion.txt"
# 2. builtins
builtins = "../test_cases/input.txt"


def execute_minishell(command, minishell=minishell):
    command = f'echo "{command}" | {minishell}'
    process = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    process.stdout.flush()
    stdout, stderr = process.communicate()
    process.terminate()
    # should check if stderr is not empty
    if stderr.decode() != "":
        return stderr.decode(), 1
    else:
        return stdout.decode(), 0

def execute_bash(command):
    command = f'echo "{command}" | bash'
    process = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    process.stdout.flush()
    stdout, stderr = process.communicate()
    process.terminate()
    # should check if stderr is not empty
    if stderr.decode() != "":
        # format stderr
        return stderr.decode(), 1
    else:
        return stdout.decode(), 0

def format_stderr(stderr):
    if stderr != "":
        stderr = stderr.split("")

def print_builtin_name(line, infile, outfile):
    print("\n")
    while line != "" and line != "\n":
        print(line)
        outfile.write(line)
        line = infile.readline()
    outfile.write("\n")

def init_command(line, infile, command):
    while line != "" and line != "\n":
        command += line
        command += "\n"
        line = infile.readline()
    return command

def output_to_outfile(outfile, minishell_result, bash_result):
    outfile.write("\n")
    outfile.write(f"minishell output: \n{minishell_result}\n")
    outfile.write(f"bash      output: \n{bash_result}\n")
    outfile.write("\n")
    outfile.write("---------------------------------------------\n")
    outfile.write("\n")

def print_result(minishell_result, bash_result, m_err, b_err):
    if m_err == 1 and b_err == 1:
        matcher = difflib.SequenceMatcher(None, minishell_result, bash_result)
        ratio = matcher.ratio()
        if ratio > 0.7:
            print(colored("GUD ", "green"), end="")
        else:
            print(colored("BAD ", "red"), end="")
    else:
        if minishell_result == bash_result:
            print(colored("GUD ", "green"), end="")
        else:
            print(colored("BAD ", "red"), end="")

def open_files(file_path):
    # clear outfile
    with open(f"{outfile_path}", "w") as c:
        pass
    infile = open(f"{file_path}", "r")
    outfile = open(f"{outfile_path}", "a")
    return infile, outfile

menu = [
    {
        "type": "list",
        "name": "menu",
        "message": "Choose a mode",
        "choices": [
            "Builtins",
            "Expansion",
        ]
    }
]

def test():
    print(shinimell)
    # execute cases based on answer
    mode = prompt(menu)
    # open files
    if mode["menu"] == "Builtins":
        infile, outfile = open_files(builtins)
    elif mode["menu"] == "Expansion":
        infile, outfile = open_files(expansion)
    # exection loop
    i = 1
    j = 0
    while True:
        command = ""
        line = infile.readline()
        if line == "":
            print("\n")
            break
        elif line[0] == "/":
            print_builtin_name(line, infile, outfile)
            j = 0
        else:
            # init command
            command = init_command(line, infile, command)
            print(colored(f"Case #{i}: ", "blue"), end="")
            outfile.write(f"Case #{i}: \n")
            outfile.write("\n")
            outfile.write(f"{command}")
            i += 1
            j += 1
            minishell_result, m_err = execute_minishell(command)
            bash_result, b_err = execute_bash(command)
            output_to_outfile(outfile, minishell_result, bash_result)
            print_result(minishell_result, bash_result, m_err, b_err)
            if j % 5 == 0:
                print()

test()