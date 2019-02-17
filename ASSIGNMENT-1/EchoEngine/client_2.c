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

#define SERVER_KEY_PATHNAME "/tmp/mqueue_server_key"
#define PROJECT_ID 'M'
#define CHAR_LOW 33
#define CHAR_HIGH 126
#define ITERS 10000000


struct message_text {
    int qid;
    char buf;  // 1 extra for the null character
};

struct message {
    long message_type;
    struct message_text message_text;
};

int main (int argc, char **argv){
    
    key_t server_queue_key;
    clock_t start, end, start_per_req;

    double total_elapsed_time, avg_response_time=0.0;

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

    my_message.message_type = 2;
    my_message.message_text.qid = myqid;

    // printf ("Client: (%d) Please type a message: ", myqid);

    
    // start the  loop
    long t_step = 0;
    char char_message;

    start = clock();   // timer starts


    while(t_step < ITERS){
        char_message = (rand() % (CHAR_HIGH - CHAR_LOW + 1)) + CHAR_LOW; 
        
        my_message.message_text.buf = char_message;

        start_per_req = clock();
        
        if (msgsnd (server_qid, &my_message, sizeof (struct message_text), 0) == -1) {
            perror ("client: msgsnd");
            exit (1);
        }else{
            printf("Client: (%d) sent message to server: (%d): %c\n", myqid, server_qid, char_message);
        } 

        if (msgrcv (myqid, &return_message, sizeof (struct message_text), 0, 0) == -1) {
            perror ("client: msgrcv");
            exit (1);
        }

        avg_response_time +=  ((double)(clock()-start_per_req) / (CLOCKS_PER_SEC / 1000));


         // process return message from server
        printf ("Client: (%d) message received from server: (%d): %c\n", myqid, server_qid, return_message.message_text.buf);  


        t_step++;


    }

    end = clock();
    

    if (msgctl (myqid, IPC_RMID, NULL) == -1) {
            perror ("client: msgctl");
            exit (1);
    }

    total_elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    avg_response_time /= ITERS;

    printf ("Client (%d) finished %d requests in %.2f seconds\n", myqid, ITERS, total_elapsed_time);
    printf ("Average Response time: %f milliseconds\n\n", avg_response_time);
    exit (0);

    // my_message.message_text.buf = getchar();

    // while (my_message.message_text.buf = getchar()) {
    //     // remove newline from string
    //     // int length = strlen (my_message.message_text.buf);
    //     // printf("Length of the input string is %d\n", length);
    //     // if (my_message.message_text.buf [length - 1] == '\n')
    //        // my_message.message_text.buf [length - 1] = '\0';
    //     // printf("The character read is %c", my_message.message_text.buf);
    //     // send message to server
    //     // fflush(stdin);

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
    //     printf ("Client: (%d) message received from server: (%d): %c\n\n", myqid, server_qid, return_message.message_text.buf);  

    //     printf ("Client: (%d) Please type a message: ", myqid);

    //     while (getchar() != '\n');
        

    // }
    // remove message queue
    

}