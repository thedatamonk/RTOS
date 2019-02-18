/*
 * server.c: Server program
 *           to demonstrate interprocess commnuication
 *           with System V message queues
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define SERVER_KEY_PATHNAME "/tmp/mqueue_server_key"
#define PROJECT_ID 'M'
#define QUEUE_PERMISSIONS 0660
#define BUF_SIZE 1000
#define FILE_NAME_LENGTH 30
#define FILE_NOT_EXISTS "File doesn't exists"

struct message_text {
    int qid;
    char filename [FILE_NAME_LENGTH];
    char contents [BUF_SIZE];
};

struct message {
    long message_type;
    struct message_text message_text;
};

int main (int argc, char **argv)
{
    key_t msg_queue_key;
    int qid;
    struct message message;
    FILE * f_ptr;

    if ((msg_queue_key = ftok (SERVER_KEY_PATHNAME, PROJECT_ID)) == -1) {
        perror ("ftok");
        exit (1);
    }

    if ((qid = msgget (msg_queue_key, IPC_CREAT | QUEUE_PERMISSIONS)) == -1) {
        perror ("msgget");
        exit (1);
    }

    printf ("Server (%d): Hello, World!\n", qid);

    while (1) {
        // read an incoming message
        int client_qid;
        
        if (msgrcv (qid, &message, sizeof (struct message_text), 0, 0) == -1) {
            perror ("msgrcv");
            exit (1);
        }else{
            client_qid = message.message_text.qid;

            printf ("Server: (%d) received request from client: (%d)\n", qid, client_qid);

        }

        // process message
        // read the file name


        if ((f_ptr = fopen(message.message_text.filename, "r")) == NULL){
            // file doesn't exists
            strcpy(message.message_text.contents, FILE_NOT_EXISTS);
        }else{

            fscanf(f_ptr,"%[^\n]", message.message_text.contents);
        }


        message.message_text.qid = qid;

        // send reply message to client
        if (msgsnd (client_qid, &message, sizeof (struct message_text), 0) == -1) {  
            perror ("msgget");
            exit (1);
        }else{
            printf ("Server: (%d) response sent to client: (%d)\n", qid, client_qid);    
        }

    }
}