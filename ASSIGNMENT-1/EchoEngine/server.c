/*
 * server.c: Server program
 *           to demonstrate interprocess commnuication
 *           with System V message queues
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define SERVER_KEY_PATHNAME "/tmp/mqueue_server_key"
#define PROJECT_ID 'M'
#define QUEUE_PERMISSIONS 0660
#define BUF_SIZE 2

struct message_text {
    int qid;
    char buf;
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

    if ((msg_queue_key = ftok (SERVER_KEY_PATHNAME, PROJECT_ID)) == -1) {
        perror ("ftok");
        exit (1);
    }

    if ((qid = msgget (msg_queue_key, IPC_CREAT | QUEUE_PERMISSIONS)) == -1) {
        perror ("msgget");
        exit (1);
    }

    printf ("Server: Hello, World! QID: (%d)\n", qid);

    while (1) {
        // read an incoming message
        if (msgrcv (qid, &message, sizeof (struct message_text), 0, 0) == -1) {
            perror ("msgrcv");
            exit (1);
        }


        int client_qid = message.message_text.qid;

        printf ("Server: (%d) message received from client: (%d)\n", qid, client_qid);

        // process message
        char ch = message.message_text.buf;

        // check if it's an alphabet
        if (isalpha(ch)){
            if (isupper(ch))
                ch  = tolower(ch);
            else
                ch = toupper(ch);
        }

        // update the buffer
        message.message_text.buf = ch;

        // int length = strlen (message.message_text.buf);
        // char buf [20];
        // sprintf (buf, " %d", length);
        // strcat (message.message_text.buf, buf);

        message.message_text.qid = qid;

        // send reply message to client
        if (msgsnd (client_qid, &message, sizeof (struct message_text), 0) == -1) {  
            perror ("msgget");
            exit (1);
        }

        printf ("Server: (%d) response sent to client: (%d)\n", qid, client_qid);
    }
}