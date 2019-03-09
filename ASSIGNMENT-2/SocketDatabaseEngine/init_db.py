import glob
import random
import os
import sys
import string
from pathlib import Path


DB_DIR = "./db/"
NUM_FILES = 10
STRING_LENGTH = 20


if len(sys.argv) > 1:
	NUM_FILES = int(sys.argv[1])


# create the directory if doesn't already exists

if not os.path.exists(DB_DIR):
	os.makedirs(DB_DIR)

# create files in the directory

for i in range(1, NUM_FILES+1):
	# create a new file
	file_path = os.path.join(DB_DIR, "file_{0}.txt".format(i))
	

	Path(file_path).touch()
	print ("{0} created".format(file_path))

	with open(file_path, "w") as file:

		str_message = ''.join(random.choice(string.ascii_uppercase + string.digits) for _ in range(STRING_LENGTH))
		file.write("Hello! This is {0} ||".format(os.path.basename(file_path)) + " " + str_message + "\n")
		print ("Message written to {0}\n".format(file_path))


