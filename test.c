#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void main()
{
    int pid1,pid2,pid3,pid4,pid5;
pid1= fork();
if (pid1 !=0)
{
    pid2= fork();
    pid3= fork();
}
else
{
    pid4= fork();
    if (pid4== 0)
    {
        pid5= fork();
    }
}
}
