/*
 * client.c: Client program
 *           to demonstrate interprocess commnuication
 *           with System V message queues
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>

#define SERVER_KEY_PATHNAME "/tmp/mqueue_server_key"
#define PROJECT_ID 'M'
#define BUF_SIZE 1000
#define FILE_NAME_LENGTH 30
#define FILE_NOT_EXISTS "File doesn't exists"
#define NUM_FILES 100
#define DB_PATH "./db/"

struct message_text {
    int qid;
    char filename [FILE_NAME_LENGTH];
    char contents [BUF_SIZE];
};

struct message {
    long message_type;
    struct message_text message_text;
};

int main (int argc, char **argv){

    key_t server_queue_key;
    clock_t start, end, start_per_req;

    double total_elapsed_time,  avg_response_time = 0.0;

    int server_qid, myqid;
    struct message my_message, return_message;


    // create an array of strings that will contain the file names
    char db[NUM_FILES][FILE_NAME_LENGTH];

    // to store current directory in currentPath

    DIR *dr;
    struct dirent *de; // pointer for directory entry
    struct stat buf;

    
    // Open Current Directory
    if ((dr = opendir(DB_PATH)) == NULL){
        printf("Could not open database directory\n");
        return errno;
    }


    // add filnames of the DB in a C-Array
    int i=0;
    while ((de = readdir(dr)) != NULL){
        
        /*Skips . and ..*/
        if(strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0)
             continue;
        
        char fullPath[FILENAME_MAX] = "";
        
        strcat(fullPath, DB_PATH);
        strcat(fullPath, de->d_name);

        if (stat(fullPath, &buf) == -1){
            perror("stat");
            return errno;
        }


        if (S_ISREG(buf.st_mode)){
            // only append to the list when it's a regular file
            strcpy(db[i], fullPath);
            i++;
        }
    }

    closedir(dr);

    
    // create my client queue for receiving messages from server
    if ((myqid = msgget (IPC_PRIVATE, 0660)) == -1) {
        perror ("msgget: myqid");
        exit (1);
    }

    if ((server_queue_key = ftok (SERVER_KEY_PATHNAME, PROJECT_ID)) == -1) {
        perror ("ftok");
        exit (1);
    }

    if ((server_qid = msgget (server_queue_key, 0)) == -1) {
        perror ("msgget: server_qid");
        exit (1);
    }

    my_message.message_type = 1;
    my_message.message_text.qid = myqid;

    i = 0;

    // start timer starts
    start = clock();

    while(i<NUM_FILES){

        strcpy(my_message.message_text.filename, db[i]);

        int length = strlen (my_message.message_text.filename);
       
        if (my_message.message_text.filename [length - 1] == '\n')
            my_message.message_text.filename [length - 1] = '\0';

        start_per_req = clock();
        // send message to server
       
        if (msgsnd (server_qid, &my_message, sizeof (struct message_text), 0) == -1) {
                perror ("client: msgsnd");
                exit (1);
        }else{
            printf("Client: (%d) requested %s from server: (%d)\n", myqid, my_message.message_text.filename, server_qid);
        }

        // read response from server
        if (msgrcv (myqid, &return_message, sizeof (struct message_text), 0, 0) == -1) {
                perror ("client: msgrcv");
                exit (1);
        }else{

            avg_response_time += ((double) (clock() - start_per_req)) / (CLOCKS_PER_SEC /1000);

            printf ("Client: (%d) received response from server: (%d)\n", myqid, server_qid);  

        }


        if (strcmp(FILE_NOT_EXISTS, return_message.message_text.contents) == 0)
            printf("%s\n\n", return_message.message_text.contents);
        else
            printf ("Client (%d): The contents of the file %s are \n%s\n\n", myqid, return_message.message_text.filename, return_message.message_text.contents);


        i++;
        
    }

    end = clock();
    // remove the message queue
    if (msgctl (myqid, IPC_RMID, NULL) == -1) {
            perror ("client: msgctl");
            exit (1);
    }

    total_elapsed_time = ((double) (end-start)) / (CLOCKS_PER_SEC/ 1000);
    avg_response_time /= NUM_FILES;
    
    printf ("Client (%d) finsished %d file requests in %.3f milliseconds\n", myqid, NUM_FILES, total_elapsed_time);
    printf ("Average Response time: %.5f milliseconds\n\n", avg_response_time);
    
    exit (0);
}