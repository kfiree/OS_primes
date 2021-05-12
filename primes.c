#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include <time.h>
#include <stdbool.h>
#include "counter.h"
#include "primes.h"
#define OUTPUT 1

counter_t sum;
pthread_mutex_t  rndLock;
counter_t numCtr;
counter_t primeCtr;
int numbersNum;
int rndSeed;
// long sum = 0;
	
bool checkPrime(int random)
{
  // int n = inc_counter(&primessearch);
  int halfOfn = random / 2;
  for (int i=2; i<=halfOfn; i++){
    if (random % i == 0)
    {
      // printf("%ld --- not prime number", random);
      return false;
    }
  }

  // printf("%ld ----  prime number", random);
  inc_sum(&sum, random);
  inc_counter(&primeCtr);

  return true;
// #if OUTPUT

//       switch (threadid)
//       {
//         case 1:
//           printf("\033[0;31m%d,",random);
//           break;
//         case 2:
//           printf("\033[0;32m%d,",random);
//           break;
//         case 3:
//           printf("\033[0;33m%d,",random);
//           break;
//         case 4:
//           printf("\033[0;34m%d,",random);
//           break;
//         case 5:
//           printf("\033[0;35m%d,",random);
//           break;
//         case 6:
//           printf("\033[0;36m%d,",random);
//           break;
//         case 7:
//           printf("\033[1;32m%d,",random);
//           break;
//         case 8:
//           printf("\033[1;34m%d,",random);
//       }

// #endif
}

void * generateAndCheck()
{
  // int i = 1;
  while (inc_counter(&numCtr) <= numbersNum)
  { 
      //init random generator
      // pthread_mutex_lock(&rndLock);
      // int rnd = rand();
      // pthread_mutex_unlock(&rndLock);

      checkPrime(rand());

  }  
  return NULL;
}

int main(int argc, char *argv[])
{
  //set threads
  pthread_t p1, p2, p3, p4, p5, p6, p7, p8;

  //init strucuts
  init_counter(&sum);
  init_counter(&numCtr);

  

	if(argc != 3) {
	    printf("Too few arguments ");
	    printf("USAGE: ./primeCalc <prime pivot> <num of random numbers>");
            exit(0);
  }

	rndSeed = atoi(argv[1]);
	numbersNum = atoi(argv[2]);

  srand(rndSeed);
 
	// long primeCounter = 0;

  pthread_create(&p1, NULL, (void *) generateAndCheck, 1);  // CREATE PRIME GENERATOR THREAD 1
  pthread_create(&p2, NULL, (void *) generateAndCheck, 2);  // CREATE PRIME GENERATOR THREAD 2
  pthread_create(&p3, NULL, (void *) generateAndCheck, 3);  // CREATE PRIME GENERATOR THREAD 3
  pthread_create(&p4, NULL, (void *) generateAndCheck, 4);  // CREATE PRIME GENERATOR THREAD 4
  pthread_create(&p5, NULL, (void *) generateAndCheck, 5);  // CREATE PRIME GENERATOR THREAD 5
  pthread_create(&p6, NULL, (void *) generateAndCheck, 6);  // CREATE PRIME GENERATOR THREAD 6
  pthread_create(&p7, NULL, (void *) generateAndCheck, 7);  // CREATE PRIME GENERATOR THREAD 7
  pthread_create(&p8, NULL, (void *) generateAndCheck, 8);  // CREATE PRIME GENERATOR THREAD 8

  pthread_join(p1, NULL);
  pthread_join(p2, NULL);
  pthread_join(p3, NULL);
  pthread_join(p4, NULL);
  pthread_join(p5, NULL);
  pthread_join(p6, NULL);
  pthread_join(p7, NULL);
  pthread_join(p8, NULL);

  printf("%ld,%ld \n",get_counter(&sum) , get_counter(&primeCtr));

  return 0;
}
