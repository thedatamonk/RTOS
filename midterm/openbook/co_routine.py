def print_name(prefix):
	print("Searching prefix:{}".format(prefix))

	try:
		while True:
			name = (yield)
			if prefix in name:
				print (name)


	except GeneratorExit:
		print ("Closing coroutine!!")


def main():
	handle = print_name("Dear")
	handle.__next__()
	handle.send("Mahesh")
	handle.send("Dear Mahesh")
	handle.send("Dear Anand")
	handle.send("Dr Anand")
	handle.close()

if __name__ == '__main__':
	main()