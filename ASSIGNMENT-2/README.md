# Socket programming
Implement a client-server architecture using TCP sockets. Experiment with multiple clients and observe how it changes the server response time.
There are 2 parts we need to solve for this assignment:
1. Implement an EchoEngine server that changes the case of the character requested by the client. The details can be found [here](https://github.com/thedatamonk/RTOS/blob/master/ASSIGNMENT-2/SocketEchoEngine/README.md).
2. Implement a DatabaseEngine server that returns the contents of the file requested by the client. The details can be found [here](https://github.com/thedatamonk/RTOS/blob/master/ASSIGNMENT-2/SocketDatabaseEngine/README.md).

## Running the code
- Clone the repository
```
$ git clone https://github.com/thedatamonk/RTOS.git
```
### Setting up EchoEngine server
- Navigate to the `SocketEchoEngine` directory.
```
$ cd RTOS/ASSIGNMENT-2/SocketEchoEngine
```
- Compile the client and server source codes using `make`. The executables will be created and stored in the current working directory. This can be changed in the `MakeFile`.
```
$ make
```
- Run the executables by executing the `run.sh` shell script. 
It takes **2** mandatory arguments. The first argument is an integer (between 1-5 (both inclusive)) which is the number of parallel clients.
And the second argument takes in the IP address of the machine on which the server is running. 
In this case, the server and the clients run on same machine. So, for both of them the IP addresses will be same.
To find your machine's IP address, open Terminal and type the following command.
```
$ hostname -I
```
For instance, to run **2** clients, run the shell in the following way:
```
$ sh run.sh 2 <your_ip_address>
```
- Each client and the server will be run in a separate terminal. The log outputs of the clients' terminals will not visible in the terminal
but will be instead stored in the output log files. All log files are stored systematically as they follow a standard file naming system. 
All log file paths are of the form: `./logs/NUM_OF_PARALLEL_CLIENTS/client_{CLIENT_NUMBER}.txt`. 

### Setting up DatabaseEngine server
- Navigate to the `SocketDatabaseEngine` directory.
```
$ cd RTOS/ASSIGNMENT-2/SocketDatabaseEngine
```
- Create a dummy database by running `init_db.py` file. By default, this will create **10** `.txt` files in the `./db/` directory. Each file will contain a single line of text in the following format: `Hello! This is FILE_NAME.txt || RANDOM_STRING_OF_FIXED_LENGTH`. The number of files to create can be passed as a command-line argument. For instance, to create 100 files:
```
$ python init_db.py 100
```
- Compile the client and server source codes using `make`. The executables will be created and stored in the current working directory. This can be changed in the `MakeFile`.
```
$ make
```
- Run the executables by executing the `run.sh` shell script. 
It takes **2** mandatory arguments. The first argument is an integer (between 1-5 (both inclusive)) which is the number of parallel clients.
And the second argument takes in the IP address of the machine on which the server is running. 
In this case, the server and the clients run on same machine. So, for both of them the IP addresses will be same.
To find your machine's IP address, open Terminal and type the following command.
```
$ hostname -I
```
For instance, to run **2** clients, run the shell in the following way:
```
$ sh run.sh 2 <your_ip_address>
```
- Each client and the server will be run in a separate terminal. The log outputs of the clients' terminals will not visible in the terminal
but will be instead stored in the output log files. All log files are stored systematically as they follow a standard file naming system. 
All log file paths are of the form: `./logs/NUM_OF_PARALLEL_CLIENTS/client_{CLIENT_NUMBER}.txt`. 
### Issues:
1. When running the `run.sh` script, it might happen that the number of clients actually running may differ from the intended number. For instance, you want to run 3 clients but it may open only 2 terminals or even 1. I haven't figured out the solution for this yet. But if you try a few more times, you will be able to run the intended number of clients.
2. Sometimes, it may also show *"server is waiting.."* message. But you will be able to run it successfully if you try a few more times. 

## References
The client and server code is adapted from this [blog](http://www.theinsanetechie.in/2014/01/tcp-in-c-one-server-and-multiple-clients.html).



