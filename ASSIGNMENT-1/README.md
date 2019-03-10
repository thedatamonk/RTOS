# Message Queue
Implement a client-server architecture using message queues. Experiment with multiple clients and observe how it changes the server response time.
There are 2 parts we need to solve for this assignment:
1. Implement an EchoEngine server that changes the case of the character requested by the client. The details can be found [here](https://github.com/thedatamonk/RTOS/blob/master/ASSIGNMENT-1/EchoEngine/README.md).
2. Implement a DatabaseEngine server that returns the contents of the file requested by the client. The details can be found [here](https://github.com/thedatamonk/RTOS/blob/master/ASSIGNMENT-1/DatabaseEngine/README.md).

## Running the code
- Clone the repository
```
$ git clone https://github.com/thedatamonk/RTOS.git
```
### Setting up EchoEngine server
- Navigate to the `EchoEngine` directory.
```
$ cd RTOS/ASSIGNMENT-1/EchoEngine
```
- Create a file in the `/tmp/mqueue_server_key` using `touch` command. This file will be used to create the unique key to access the message queue.
```
$ touch /tmp/mqueue_server_key
```
- Compile the client and server source codes using `make`. The executables will be created and stored in the current working directory. This can be changed in the `MakeFile`.
```
$ make
```
- Run the executables by executing the `run.sh` shell script. It takes **1** mandatory argument which is the number of parallel clients **(between 1-5 (both inclusive))**. For instance, to run **2** clients, run the shell in the following way:
```
$ sh run.sh 2
```
- Each client and the server will be run in a separate terminal. The log outputs of the clients' terminals will be stored in the `./logs/NUM_OF_PARALLEL_CLIENTS/client_{CLIENT_NUMBER}.txt`. 
**Disclaimer:** The output log files can be huge (100MB+) by default. You can avoid this by decreasing the value of `ITERS` macro in each client source code. In the end of each client log file, is the average response time in milliseconds for that client.

### Setting up DatabaseEngine server
- Navigate to the `DatabaseEngine` directory.
```
$ cd RTOS/ASSIGNMENT-1/DatabaseEngine
```
- Create a file in the `/tmp/mqueue_server_key` using `touch` command. This file will be used to create the unique key to access the message queue.
```
$ touch /tmp/mqueue_server_key
```
- Create a dummy database by running `init_db.py` file. By default, this will create **10** `.txt` files in the `./db/` directory. Each file will contain a single line of text in the following format: `Hello! This is FILE_NAME.txt || RANDOM_STRING_OF_FIXED_LENGTH`. The number of files to create can be passed as a command-line argument. For instance, to create 100 files:
```
$ python init_db.py 100
```
- Compile the client and server source codes using `make`. The executables will be created and stored in the current working directory. This can be changed in the `MakeFile`.
```
$ make
```
- Run the executables by executing the `run.sh` shell script. It takes **1** mandatory argument which is the number of parallel clients **(between 1-5 (both inclusive))**. For instance, to run **2** clients, run the shell in the following way:
```
$ sh run.sh 2
```
- Each client and the server will be run in a separate terminal. The log outputs of the clients' terminals will be stored in the `./logs/NUM_OF_PARALLEL_CLIENTS/client_{CLIENT_NUMBER}.txt`. In the end of each client log file, is the average response time in milliseconds for that client.
## References
The client and server code is adapted from this [blog](https://www.softprayog.in/programming/interprocess-communication-using-system-v-message-queues-in-linux).



