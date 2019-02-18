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

    my_message.message_type = 1;
    my_message.message_text.qid = myqid;

    printf ("Client (%d) Please type a file name ", myqid);
    
    while(fgets(my_message.message_text.filename, FILE_NAME_LENGTH, stdin)){

        int length = strlen (my_message.message_text.filename);
       
        if (my_message.message_text.filename [length - 1] == '\n')
            my_message.message_text.filename [length - 1] = '\0';

        // send message to server
        if (msgsnd (server_qid, &my_message, sizeof (struct message_text), 0) == -1) {
                perror ("client: msgsnd");
                exit (1);
        }else{
            printf("Client: (%d) sent request to server: (%d)\n", myqid, server_qid);
        }

        // read response from server
        if (msgrcv (myqid, &return_message, sizeof (struct message_text), 0, 0) == -1) {
                perror ("client: msgrcv");
                exit (1);
        }else{

            printf ("Client: (%d) received response from server: (%d)\n", myqid, server_qid);  

        }


        if (strcmp(FILE_NOT_EXISTS, return_message.message_text.contents) == 0)
            printf("%s\n\n", return_message.message_text.contents);
        else
            printf ("Client (%d): The contents of the file %s are \n%s\n\n", myqid, return_message.message_text.filename, return_message.message_text.contents);

        printf ("Client (%d) Please type a file name ", myqid);

    }

    if (msgctl (myqid, IPC_RMID, NULL) == -1) {
            perror ("client: msgctl");
            exit (1);
    }

    printf ("Client (%d): bye\n", myqid);

    exit (0);
    // while (fgets (my_message.message_text.buf, 198, stdin)) {
    //     // remove newline from string
    //     int length = strlen (my_message.message_text.buf);
    //     if (my_message.message_text.buf [length - 1] == '\n')
    //        my_message.message_text.buf [length - 1] = '\0';

    //     // send message to server
    //     if (msgsnd (server_qid, &my_message, sizeof (struct message_text), 0) == -1) {
    //         perror ("client: msgsnd");
    //         exit (1);
    //     }

    //     // read response from server
    //     if (msgrcv (myqid, &return_message, sizeof (struct message_text), 0, 0) == -1) {
    //         perror ("client: msgrcv");
    //         exit (1);
    //     }

    //     // process return message from server
    //     printf ("Message received from server: %s\n\n", return_message.message_text.buf);  

    //     printf ("Please type a message: ");
    // }
    // remove message queue
    
}