#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    // I assume that P0 is main
    pid_t P1 , P2 , P3 , P4 , P5 , P6;
    pid_t pid2 , pid3, whofinished;

    int pype[2];
    pipe(pype);
    char buffer[100];

    int status;
    int exit_code;

    // Making The processes
    printf("\nP0   PID:%d  PPID:%d\n"  , getpid() , getppid());
    P1 = fork();

    if( P1 == 0 )
    {
        P3 = fork();
        pid3 = P3;
        if( P3 == 0 )
        {
            printf("\nP3   PID:%d  PPID:%d\n"  , getpid() , getppid());
            close(pype[0]);    //close read
            write(pype[1],"Hello from your child",21);
            close(pype[1]);
            exit(0);
        }

        P4 = fork();
        if( P4 == 0 )
        {
            printf("\nP4   PID:%d  PPID:%d\n"  , getpid() , getppid());
            exit(0);
        }

        printf("\nP1   PID:%d  PPID:%d\n"  , getpid() , getppid());
        waitpid(pid3,0,0);
        close(pype[1]);
        read(pype[0],buffer,100);
        printf("\nP1 received this message from P3: %s \n" , buffer);
        
        
        waitpid(P4, &status, 0);  

        exit_code = WEXITSTATUS(status);
        printf("\nP4 finished with exit code: %d\n", exit_code);


        exit(0);
    }

    P2 = fork();
    pid2 = P2;
    if( P2 == 0 )
    {
        P5 = fork();
        if( P5 == 0 )
        {
            printf("\nP5   PID:%d  PPID:%d\n"  , getpid() , getppid());
            exit(0);
        }

        P6 = fork();
        if( P6 == 0 )
        {
            printf("\nP6   PID:%d  PPID:%d\n"  , getpid() , getppid());
            exit(0);
        }

        printf("\nP2   PID:%d  PPID:%d\n"  , getpid() , getppid());
        whofinished = wait(NULL);
        printf("The child with pid:%d finished first\n",whofinished);
        


        int n,i;
        pid_t Px;
        printf("\nHow many extra children do you want P2 to have:\n");
        scanf("");
        scanf("%d",&n);

        for( i=0; i<n; i++ )
        {
            Px = fork();
            if ( Px == 0)
            {
                printf("P_%d    PID:%d  PPID%d\n",i,getpid(),getppid());
                exit(0);
            }
        }



        exit(0);
    }

    printf("\nWaiting for P2 to finish \n");
    waitpid(pid2, 0 , 0);
    printf("\nP2 is finished\n");
    printf("\n");



    execlp( "ps", "ps", NULL);
    
    return(0);
}