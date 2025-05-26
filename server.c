#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define MY_SOCK_PATH "/home/andrew/Desktop/ls2/ex2/mysock"

int find_mo(int*, int);

int main() 
{
    // fork


    struct sockaddr_un my_addr;
    int sock, client_sock;
    int a;

    sock = socket(AF_UNIX, SOCK_STREAM, 0);

    memset(&my_addr, 0, sizeof(struct sockaddr_un));
    my_addr.sun_family = AF_UNIX;
    strncpy(my_addr.sun_path, MY_SOCK_PATH, sizeof(my_addr.sun_path) - 1);



    int* buffer = malloc(100*sizeof(int));
    int cnt = 0;
    int i,res;
    

    while (1) {
        int client_sock = accept(sock, NULL, NULL);
        if (client_sock == -1) 
        {
            perror("accept");
            continue;  
        }
    
        printf("Client connected.\n");
     
    
        ssize_t bytes = read(client_sock, &a, sizeof(int));
    
        if (bytes == sizeof(int)) 
        {
            printf("read %d\n", a);
    
            if (a != 0) {
                buffer[cnt++] = a;
            } else {
                if (cnt == 0) {
                    printf("No numbers received before 0.\n");
                    continue;
                }
    
                res = find_mo(buffer, cnt);
                write(client_sock, &res, sizeof(int));
    
                if (res > 20) 
                {
                    write(client_sock, "Ok", sizeof("Ok"));
                }
                else
                {
                    write(client_sock, "Not Ok", sizeof("Not Ok")); 
                }
    
                cnt = 0;  
            }
    
        } 
        else if (bytes == 0) 
        {
            printf("Client disconnected.\n");
            break;
        } 
    }


    close(client_sock);
    close(sock);
    unlink(MY_SOCK_PATH);
    return 0;
}



int find_mo(int* buffer, int size)
{
    int i, sum=0;

    for(i = 0; i < size; i++)
    {
        sum += buffer[i];
    }

    int res = sum/size;

    return(res);
}