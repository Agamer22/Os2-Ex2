#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

void print_one(sem_t []);
void print_two(sem_t []);
void print_three(sem_t []);


int main( int argc , char *argv[] )
{
    pthread_t thread1 , thread2 , thread3 ;
    sem_t sem1 , sem2 , sem3 ;
    sem_init(&sem1,1,0);
    sem_init(&sem2,1,0);
    sem_init(&sem3,1,0);
    sem_t *array;
    array = malloc (3*sizeof(sem_t));
    array[0] = sem1;
    array[1] = sem2;
    array[2] = sem3;

    pthread_create(&thread1,NULL,(void*)print_one,array);
    
    pthread_create(&thread2,NULL,(void*)print_two,array);
    
    pthread_create(&thread3,NULL,(void*)print_three,array);
    
    sem_post(&array[0]);

    sleep(5);

    

    free(array);

    return(0) ;
}


void print_one(sem_t array[])
{

    while(1)
    {
        sem_wait(&array[0]);
        printf("<one>\n");
        sem_post(&array[1]);
        sleep(1);
    }
}

void print_two(sem_t array[])
{
 
    while(1)
    {
        sem_wait(&array[1]);
        printf("<two>\n");
        sem_post(&array[2]);   
        sleep(1);
    }
}

void print_three(sem_t array[])
{

    while(1)
    {
        sem_wait(&array[2]);
        printf("<three>\n");
        sem_post(&array[0]);
        sleep(1);
    }
}