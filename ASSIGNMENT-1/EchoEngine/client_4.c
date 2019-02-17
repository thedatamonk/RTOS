/*
 * client.c: Client program
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

struct message_text {
    int qid;
    char buf;  // 1 extra for the null character
};

struct message {
    long message_type;
    struct message_text message_text;
};

int main (int argc, char **argv)
{
    key_t server_queue_key;
    int server_qid, myqid;
    struct message my_message, return_message;

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

    my_message.message_type = 4;
    my_message.message_text.qid = myqid;

    printf ("Client: (%d) Please type a message: ", myqid);

    
    
    // my_message.message_text.buf = getchar();

    while (my_message.message_text.buf = getchar()) {
        // remove newline from string
        // int length = strlen (my_message.message_text.buf);
        // printf("Length of the input string is %d\n", length);
        // if (my_message.message_text.buf [length - 1] == '\n')
           // my_message.message_text.buf [length - 1] = '\0';
        // printf("The character read is %c", my_message.message_text.buf);
        // send message to server
        // fflush(stdin);

        if (msgsnd (server_qid, &my_message, sizeof (struct message_text), 0) == -1) {
            perror ("client: msgsnd");
            exit (1);
        }

        // read response from server
        if (msgrcv (myqid, &return_message, sizeof (struct message_text), 0, 0) == -1) {
            perror ("client: msgrcv");
            exit (1);
        }

        // process return message from server
        printf ("Client: (%d) message received from server: (%d): %c\n\n", myqid, server_qid, return_message.message_text.buf);  

        printf ("Client: (%d) Please type a message: ", myqid);

        while (getchar() != '\n');
        

    }
    // remove message queue
    if (msgctl (myqid, IPC_RMID, NULL) == -1) {
            perror ("client: msgctl");
            exit (1);
    }

    printf ("Client: bye\n");

    exit (0);
}