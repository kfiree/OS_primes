#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include <time.h>
#include <stdbool.h>

pthread_mutex_t lock;
long sum = 0, primeCtr = 0;
int numbersNum;
int rndSeed;
int cpuSize;
long sumArray[8]={0};
long primeCtrArray[8]={0};
int* randomsArray;

void* checkPrime(int num, int threadId){
    if(num == 2 || num == 3){
        primeCtrArray[threadId]++;
        sumArray[threadId] += num;
        // printf("21\n");
        // pthread_mutex_lock(&lock);
        // sum += num;
        // primeCtr++;
        // pthread_mutex_unlock(&lock);
    }
    if(num%6 == 1 || num%6 == 5){
        //run from 2 to sqrt(num)
        int i;
        int root = (int)sqrt((double)num);
        for(i=2; i<=root; i++){
            //Check if divisible.
            if(num%i == 0){
                return 0;
            }
        }
        // pthread_mutex_lock(&lock);
        // sum += num;
        // primeCtr++;
        // pthread_mutex_unlock(&lock);
        // printf("41\n");
        primeCtrArray[threadId]++;
        sumArray[threadId] += num;
        return 0;
    }
    else{
        return 0;
    }
}

void * generateAndCheck(int threadId)
{
    // printf("53\n");
    int *randoms = randomsArray;

    int chunkSize = (numbersNum+cpuSize -1)/cpuSize;
    int from = threadId*chunkSize;
    int to; 

    if(from + chunkSize > numbersNum)
        to = numbersNum;
    else
        to = from + chunkSize;

    // printf("threadId := %d, cpuSize := %d, chunkSize := %d, to:= %d, from := %d\n", threadId, cpuSize, chunkSize, to, from);
    
    for(int i = from; i < to; i++){
        // printf("%d) %d coolcoolcool \n", i, *(randoms + i));
        checkPrime(*(randoms + i), threadId);
    }
}

int main(int argc, char *argv[])
{
    if(argc != 3) {
        printf("Too few arguments ");
        printf("USAGE: ./primeCalc <prime pivot> <num of random numbers>");
        exit(0);
    }

    
    rndSeed = atoi(argv[1]);
    numbersNum = atoi(argv[2]);

    srand(rndSeed);

    // cpu number
     cpuSize = 2*get_nprocs_conf();
    //cpuSize = atoi(argv[3]);

    // printf("      === random numbers ===         \n");
    // randoms

    randomsArray = (long*) malloc(sizeof(long)*numbersNum);

    for(int i = 0; i<numbersNum; i++){
        randomsArray[i] = rand();
        // printf("%d) %d \n", i, randomsArray[i]);
    }
    // printf("      === random numbers ===         \n");
    // randomsArray = &randomsArray;
    
    // threads
    pthread_t threads[cpuSize];

    // create threads
    for(int i=0; i<cpuSize; i++){
        if(pthread_create(threads + i, NULL, &generateAndCheck, i) != 0){
            perror("Failed to create thread.");
        }
    }

    //Joining the thread in a different loop to make parallelism.
    for(int i=0; i<cpuSize; i++){
        if(pthread_join(threads[i], NULL) != 0){
            perror("Failed to join thread.");
        }
    }


    for(int i=0;i<cpuSize;i++){
        sum+=sumArray[i];
        primeCtr+=primeCtrArray[i];
    }

    printf("\033[0;31m%ld",sum);

    printf("\033[0;32m,");

    printf("\033[0;33m%ld\033[0;34m",primeCtr);
    // printf("%ld,%ld \n",sum , primeCtr);

    return 0;
}
