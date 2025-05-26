/*
Εργαστήριο ΛΣ 2 / Άσκηση 2 / Ερώτημα 2 / 2023-24
Ονοματεπώνυμο: ΤΖΑΝΗΣ ΑΝΔΡΕΑΣ
ΑΜ: 23390087
Τρόπος μεταγλώττισης: gcc LS2-23390087-Δ5-Β-3b.c
*/


#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>     
#include <sys/un.h>       
#include <unistd.h> 


#define MY_SOCK_PATH "/home/andrew/Desktop/ls2/ex2/mysock"
struct sockaddr_un my_addr;


int main(int argc, char **argv)
{
    printf("Please don't start a sequence with the number 0\n");


    int sock = socket(AF_UNIX , SOCK_STREAM, 0);
    
    memset(&my_addr, 0, sizeof(struct sockaddr_un));
    my_addr.sun_family = AF_UNIX;
    strncpy(my_addr.sun_path, MY_SOCK_PATH, sizeof(my_addr.sun_path) - 1);

    if (connect(sock, (struct sockaddr *) &my_addr, sizeof(struct sockaddr_un)) == -1) {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    printf("Client Side\n");
    printf("To end sequence type 0\n");
    printf("To exit type -1\n");


    int a = 0, mo;
    char *buffer = malloc(100 * sizeof(char));

while (a != -1)
{
    printf("Please type the next number\n");
    scanf("%d", &a);
    write(sock, &a, sizeof(int));

    if (a == 0)
    {
        read(sock, &mo, sizeof(int));
        printf("The mo of the numbers is %d\n", mo);

        
        
            memset(buffer, 0, 100);
            ssize_t bytes = read(sock, buffer, 100);
            if (bytes > 0)
            {
                printf("Output: %s\n", buffer);
            }
    }
}

    

    close(sock);
        
    return(0);
}


//TODO free buffer here and on the server
