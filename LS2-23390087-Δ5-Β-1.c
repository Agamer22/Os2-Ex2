/*
Εργαστήριο ΛΣ 2 / Άσκηση 2 / Ερώτημα 1
Ονοματεπώνυμο: ΤΖΑΝΗΣ ΑΝΔΡΕΑΣ
ΑΜ: 23390087
Τρόπος μεταγλώττισης: gcc LS2-23390087-Δ5-Β-1.c
*/



#include <complex.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct
{
    int start;
    int end;
    int *max;
    int my_max;
    int number;
    int *Array;
}data_max;

void find_max (data_max*);


int main( int argc, char* argv[] )
{
    int *X , *buffer;
    int size_of_X , i , j , n_threads , found , max ;
    pthread_t *T;
    data_max *S;

    printf("Please type the size of the array:");
    scanf("%d",&size_of_X);
    printf("\n");

    X = malloc (size_of_X*sizeof(int)); 
    buffer = malloc (size_of_X*sizeof(int));
    for ( i=0; i<size_of_X; i++)
    {
        printf("Please type No%d element of the array: ",i);
        scanf("%d",&X[i]);
    }

    j=0;
    for( i=1; i<=size_of_X; i++)
    {
        if( size_of_X % i == 0)
        {
            buffer[j] = i;
            j++;
        }
    }

    printf("How many threads do you want to find the max element?\n");
    printf("Options: ");
    for ( i=0; i<j; i++ )
    {
        printf("%d ",buffer[i]);
    }
    printf("\n");

    found = 0;

    while( found != 1 )
    {
        scanf("%d",&n_threads);
        for( i=0; i<j; i++)
        {
            if( buffer[i] == n_threads )
            {
                found = 1;
                break;
                
            }
        }   
        
        if( found != 1)
        {
            printf("Please pick one of the options\n");
        }
             
    }
    
    printf("\n");
    free (buffer);    
    

    T = malloc (n_threads * sizeof(pthread_t));     //Thread array
    S = malloc (n_threads*sizeof(data_max));        //Struct array
    max = X[0];                                          //Init of max

    for( i=0; i<n_threads; i++ )
    {
        if ( i==0 )
        {
            S[i].start = 0;
            S[i].end = (size_of_X / n_threads) -1;
            S[i].max = &max;
            S[i].number = 1;
            S[i].Array = X;
        }
        else if ( i>0)
        {
            S[i].start = S[i-1].start + ((size_of_X / n_threads));
            S[i].end = S[i-1].end + ((size_of_X / n_threads));
            S[i].max = &max;
            S[i].number = i+1;
            S[i].Array = X;
        }
        //printf("Created Thread\n");
        pthread_create(&T[i], NULL , (void*) &find_max , &S[i]);
        pthread_join(T[i], NULL);
    }

    printf("\nSo the total max is:%d\n\n", max);


    free (T);
    free (S);
    free (X);
    return (0);
}



void find_max(data_max* Data)
{
    printf("Thread No%d  Start:%d  End:%d\n", Data->number , Data->start , Data->end);
    int i;
    Data->my_max = Data->Array[Data->start];
    for ( i=Data->start+1; i<Data->end; i++)
    {
        if( Data->Array[i] > Data->my_max )
        {
            Data->my_max = Data->Array[i];
        }
    }
    printf("    I found local_max = %d\n\n",Data->my_max);
    if( Data->my_max > *Data->max )
    {
        *Data->max = Data->my_max;
    }
}
