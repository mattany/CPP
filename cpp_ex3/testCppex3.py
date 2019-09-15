import subprocess
import sys
import os

USAGE_MESSAGE = b'Usage: SpamDetector <database path> <message path> <threshold>\n'
SPAM_MESSAGE = b'SPAM\n'
NOT_SPAM_MESSAGE = b'NOT_SPAM\n'
INVALID_INPUT_MESSAGE = b'Invalid input\n'
EMPTY = b''
CUR_PATH = os.path.dirname(os.path.abspath(__file__))


def compileFile():
	# os.system('g++ ./SpamDetector.cpp HashMap.hpp -o ./SpamDetector')
	os.system('g++ -Wextra -Wall -Wvla -g -std=c++14 -lm ./SpamDetector.cpp ./HashMap.hpp -o ./SpamDetector')


# looking for a db file which doesn't exist
def db_file_not_exist():
	proc = subprocess.Popen(
		["./SpamDetector", "asfafsa", "text.txt", "20"],
		stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	stdout, stderr = proc.communicate()

	if stdout == EMPTY and stderr == INVALID_INPUT_MESSAGE:
		print("passed test db_file_not_exist")
	else:
		print("failed test db_file_not_exist")


# trying to run with invalid number of arguments
def invalid_num_of_args():
	proc = subprocess.Popen(
		["./SpamDetector", "text.txt", "20"],
		stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	stdout, stderr = proc.communicate()

	if stdout == EMPTY and stderr == USAGE_MESSAGE:
		print("passed test invalid_num_of_args")
	else:
		print("failed test invalid_num_of_args")


# missing number first line
def db_bad1():
	proc = subprocess.Popen(
		["./SpamDetector", "db-bad1", "text.txt", "1"],
		stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	stdout, stderr = proc.communicate()

	if stdout == EMPTY and stderr == INVALID_INPUT_MESSAGE:
		print("passed test db_bad1")
	else:
		print("failed test db_bad1")


# missing number other line
def db_bad2():
	proc = subprocess.Popen(
		["./SpamDetector", "db-bad2.txt", "text.txt", "1"],
		stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	stdout, stderr = proc.communicate()

	if stdout == EMPTY and stderr == INVALID_INPUT_MESSAGE:
		print("passed test db_bad2")
	else:
		print("failed test db_bad2")


# missing , char in one line
def db_bad3():
	proc = subprocess.Popen(
		["./SpamDetector", "db-bad3.txt", "text.txt", "1"],
		stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	stdout, stderr = proc.communicate()

	if stdout == EMPTY and stderr == INVALID_INPUT_MESSAGE:
		print("passed test db_bad3")
	else:
		print("failed test db_bad3")


# missing bad expression in one line
def db_bad4():
	proc = subprocess.Popen(
		["./SpamDetector", "db-bad4.txt", "text.txt", "1"],
		stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	stdout, stderr = proc.communicate()

	if stdout == EMPTY and stderr == INVALID_INPUT_MESSAGE:
		print("passed test db_bad4")
	else:
		print("failed test db_bad4")


# an empty line in the middle of the db
def db_bad5():
	proc = subprocess.Popen(
		["./SpamDetector", "db-bad5.txt", "text.txt", "1"],
		stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	stdout, stderr = proc.communicate()

	if stdout == EMPTY and stderr == INVALID_INPUT_MESSAGE:
		print("passed test db_bad5")
	else:
		print("failed test db_bad5")


# a space before number
def db_bad6():
	proc = subprocess.Popen(
		["./SpamDetector", "db-bad6.txt", "text.txt", "1"],
		stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	stdout, stderr = proc.communicate()

	if stdout == EMPTY and stderr == INVALID_INPUT_MESSAGE:
		print("passed test db_bad6")
	else:
		print("failed test db_bad6")


# a space after number
def db_bad7():
	proc = subprocess.Popen(
		["./SpamDetector", "db-bad7.txt", "text.txt", "1"],
		stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	stdout, stderr = proc.communicate()

	if stdout == EMPTY and stderr == INVALID_INPUT_MESSAGE:
		print("passed test db_bad7")
	else:
		print("failed test db_bad7")


# bad number of columns (3 columns)
def db_bad8():
	proc = subprocess.Popen(
		["./SpamDetector", "db-bad8.txt", "text.txt", "1"],
		stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	stdout, stderr = proc.communicate()

	if stdout == EMPTY and stderr == INVALID_INPUT_MESSAGE:
		print("passed test db_bad8")
	else:
		print("failed test db_bad8")


# negative score for expression
def db_bad9():
	proc = subprocess.Popen(
		["./SpamDetector", "db-bad9.txt", "text.txt", "1"],
		stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	stdout, stderr = proc.communicate()

	if stdout == EMPTY and stderr == INVALID_INPUT_MESSAGE:
		print("passed test db_bad9")
	else:
		print("failed test db_bad9")


# empty line in the beginning of file
def db_bad10():
	proc = subprocess.Popen(
		["./SpamDetector", "db-bad10.txt", "text.txt", "1"],
		stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	stdout, stderr = proc.communicate()

	if stdout == EMPTY and stderr == INVALID_INPUT_MESSAGE:
		print("passed test db_bad10")
	else:
		print("failed test db_bad10")


# num is invalid (float number)
def db_bad11():
	proc = subprocess.Popen(
		["./SpamDetector", "db-bad11.txt", "text.txt", "1"],
		stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	stdout, stderr = proc.communicate()

	if stdout == EMPTY and stderr == INVALID_INPUT_MESSAGE:
		print("passed test db_bad11")
	else:
		print("failed test db_bad11")


# looking for a text file which doesn't exist
def text_file_not_exist():
	proc = subprocess.Popen(
		["./SpamDetector", "database1.txt", "safasfaf", "20"],
		stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	stdout, stderr = proc.communicate()

	if stdout == EMPTY and stderr == INVALID_INPUT_MESSAGE:
		print("passed test text_file_not_exist")
	else:
		print("failed test text_file_not_exist")


# threshold is not a num
def bad_threshold1():
	proc = subprocess.Popen(
		["./SpamDetector", "database1.txt", "text.txt", "asf"],
		stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	stdout, stderr = proc.communicate()

	if stdout == EMPTY and stderr == INVALID_INPUT_MESSAGE:
		print("passed test bad_threshold1")
	else:
		print("failed test bad_threshold1")


# threshold is not bigger than 0
def bad_threshold2():
	proc = subprocess.Popen(
		["./SpamDetector", "database1.txt", "text.txt", "0"],
		stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	stdout, stderr = proc.communicate()

	if stdout == EMPTY and stderr == INVALID_INPUT_MESSAGE:
		print("passed test bad_threshold2")
	else:
		print("failed test bad_threshold2")


# threshold is not int
def bad_threshold3():
	proc = subprocess.Popen(
		["./SpamDetector", "database1.txt", "text.txt", "2.2"],
		stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	stdout, stderr = proc.communicate()

	if stdout == EMPTY and stderr == INVALID_INPUT_MESSAGE:
		print("passed test bad_threshold3")
	else:
		print("failed test bad_threshold3")


# mail1 has score of 20
def good_input1():
	proc = subprocess.Popen(
		["./SpamDetector", "database1.txt", "mail1.txt", "21"],
		stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	stdout, stderr = proc.communicate()

	if stdout == NOT_SPAM_MESSAGE and stderr == EMPTY:
		print("passed test good_input1")
	else:
		print("failed test good_input1")


# mail1 has score of 20
def good_input2():
	proc = subprocess.Popen(
		["./SpamDetector", "database1.txt", "mail1.txt", "20"],
		stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	stdout, stderr = proc.communicate()

	if stdout == SPAM_MESSAGE and stderr == EMPTY:
		print("passed test good_input2")
	else:
		print("failed test good_input2")


# mail2 has score of 0
def good_input3():
	proc = subprocess.Popen(
		["./SpamDetector", "database2.txt", "mail2.txt", "1"],
		stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	stdout, stderr = proc.communicate()

	if stdout == NOT_SPAM_MESSAGE and stderr == EMPTY:
		print("passed test good_input3")
	else:
		print("failed test good_input3")


# mail3 has score of 30
def good_input4():
	proc = subprocess.Popen(
		["./SpamDetector", "database3.txt", "mail3.txt", "30"],
		stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	stdout, stderr = proc.communicate()

	if stdout == SPAM_MESSAGE and stderr == EMPTY:
		print("passed test good_input4")
	else:
		print("failed test good_input4")


# mail3 has score of 30
def good_input5():
	proc = subprocess.Popen(
		["./SpamDetector", "database3.txt", "mail3.txt", "31"],
		stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	stdout, stderr = proc.communicate()

	if stdout == NOT_SPAM_MESSAGE and stderr == EMPTY:
		print("passed test good_input5")
	else:
		print("failed test good_input5")


# mail4 has the expression but with a line break (shouldn't be counted)
def good_input6():
	proc = subprocess.Popen(
		["./SpamDetector", "database4.txt", "mail4.txt", "2"],
		stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	stdout, stderr = proc.communicate()

	if stdout == NOT_SPAM_MESSAGE and stderr == EMPTY:
		print("passed test good_input6")
	else:
		print("failed test good_input6")


# mail5 is empty and therefore not spam
def good_input7():
	proc = subprocess.Popen(
		["./SpamDetector", "database5.txt", "mail5.txt", "2"],
		stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	stdout, stderr = proc.communicate()

	if stdout == NOT_SPAM_MESSAGE and stderr == EMPTY:
		print("passed test good_input7")
	else:
		print("failed test good_input7")


# mail6 has two expressions which overlap partially and gets a score of 15
def good_input8():
	proc = subprocess.Popen(
		["./SpamDetector", "database6.txt", "mail6.txt", "15"],
		stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	stdout, stderr = proc.communicate()

	if stdout == SPAM_MESSAGE and stderr == EMPTY:
		print("passed test good_input8")
	else:
		print("failed test good_input8")


# mail6 has two expressions which overlap partially and gets a score of 15
def good_input9():
	proc = subprocess.Popen(
		["./SpamDetector", "database6.txt", "mail6.txt", "16"],
		stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	stdout, stderr = proc.communicate()

	if stdout == NOT_SPAM_MESSAGE and stderr == EMPTY:
		print("passed test good_input9")
	else:
		print("failed test good_input9")


# mail7 is mixing small and capital letters which exist in words in DB. score of 15
def good_input10():
	proc = subprocess.Popen(
		["./SpamDetector", "database7.txt", "mail7.txt", "15"],
		stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	stdout, stderr = proc.communicate()

	if stdout == SPAM_MESSAGE and stderr == EMPTY:
		print("passed test good_input10")
	else:
		print("failed test good_input10")


# mail7 is mixing small and capital letters which exist in words in DB. score of 15
def good_input11():
	proc = subprocess.Popen(
		["./SpamDetector", "database7.txt", "mail7.txt", "16"],
		stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	stdout, stderr = proc.communicate()

	if stdout == NOT_SPAM_MESSAGE and stderr == EMPTY:
		print("passed test good_input11")
	else:
		print("failed test good_input11")


# mail8 is a normal text but its DB is empty and therefore the message is not a spam
def good_input12():
	proc = subprocess.Popen(
		["./SpamDetector", "database8.txt", "mail8.txt", "1"],
		stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	stdout, stderr = proc.communicate()

	if stdout == NOT_SPAM_MESSAGE and stderr == EMPTY:
		print("passed test good_input12")
	else:
		print("failed test good_input12")


if __name__ == "__main__":
	compileFile()

	invalid_num_of_args()

	db_file_not_exist()
	db_bad1()
	db_bad2()
	db_bad3()
	db_bad4()
	db_bad5()
	db_bad6()
	db_bad7()
	db_bad8()
	db_bad9()
	db_bad10()
	db_bad11()
	bad_threshold1()
	bad_threshold2()

	text_file_not_exist()

	good_input1()
	good_input2()
	good_input3()
	good_input4()
	good_input5()
	good_input6()
	good_input7()
	good_input8()
	good_input9()
	good_input10()
	good_input11()
	good_input12()
