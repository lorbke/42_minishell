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

# path to your minishell
minishell = "../../minishell"

def execute_minishell(command, minishell=minishell):
    command = f'echo "{command}" | {minishell}'
    process = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    process.stdout.flush()
    stdout, stderr = process.communicate()
    process.terminate()
    # should check if stderr is not empty
    if stderr.decode() != "":
        return stderr.decode()
    else:
        return stdout.decode()

def execute_bash(command):
    command = f'echo "{command}" | bash'
    process = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    process.stdout.flush()
    stdout, stderr = process.communicate()
    process.terminate()
    # should check if stderr is not empty
    if stderr.decode() != "":
        return stderr.decode()
    else:
        return stdout.decode()

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

def print_result(minishell_result, bash_result, j):
    matcher = difflib.SequenceMatcher(None, minishell_result, bash_result)
    ratio = matcher.ratio()
    if ratio == 1:
        print(colored("OK ", "green"), end="")
    elif ratio > 0.8:
        print(colored("OK ", "yellow"), end="")
    else:
        print(colored("KO ", "red"), end="")
    if j % 5 == 0:
        print()

def open_files():
    # clear outfile
    with open("../test/output.txt", "w") as c:
        pass
    infile = open("../test/input.txt", "r")
    outfile = open("../test/output.txt", "a")
    return infile, outfile

menu = [
    {
        "type": "list",
        "name": "menu",
        "message": "Choose a mode",
        "choices": [
            "Mandatory",
            "Bonus",
            "All",
        ]
    }
]

def test():
    print(shinimell)
    # execute cases based on answer
    answers = prompt(menu)
     # open files
    infile, outfile = open_files()
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
            minishell_result = execute_minishell(command)
            bash_result = execute_bash(command)
            output_to_outfile(outfile, minishell_result, bash_result)
            print_result(minishell_result, bash_result, j)

test()
