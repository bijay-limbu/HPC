#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>
#include <mpi.h>

/******************************************************************************
  Demonstrates how to crack an encrypted password using a simple
  "brute force" algorithm. Works on passwords that consist only of 2 uppercase
  letters and a 2 digit integer. Your personalised data set is included in the
  code. 

  Compile with:
    mpicc -o 3_3_3_4digits 3_3_3_4digits.c -lcrypt

  If you want to analyse the results then use the redirection operator to send
  output to a file that you can view using an editor or the less utility:

    mpirun -n 3 ./3_3_3_4digits

  Dr Kevan Buckley, University of Wolverhampton, 2018
******************************************************************************/
int n_passwords = 4;

char *passwords_enc[] = {
  "$6$KB$Xm83SegrEKMkyFz7IJqlWwmLqh5ag4ed4w6d0sUN/OOiZW4noNfk9Rl0c.8ALHPuoxd6LAVGSjiVINpHt0uBS.",
  "$6$KB$Xm83SegrEKMkyFz7IJqlWwmLqh5ag4ed4w6d0sUN/OOiZW4noNfk9Rl0c.8ALHPuoxd6LAVGSjiVINpHt0uBS.",
  "$6$KB$hluVAAIEgKB8XhdM7nPT.EswCee0LBQ3V2yBZcHkSAH37OCe.RI8Qdb/Wzg7KuJKaC9MWoduZKwy7vT02R4zj0",
  "$6$KB$IeYUz/kWAq2K.J0SBEq1l7/LyBc8IyCDUKe.Ym/Ric1noYWKyiNQHxb2o1uJoOSrpbo.rowc.GdcbvxIs96Tp1"



};

/**
 Required by lack of standard function in C.   
*/

void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}

void function_1(char *salt_and_encrypted){
  int S,A,J;    
  char salt[7];
  char plain[7];
  char *enc;
  int count = 0;

  substr(salt, salt_and_encrypted, 0, 6);

  for(S='A';S<='M'; S++){
    for(A='A'; A<='Z'; A++){
      for(J=0; J<=99; J++){
        for(int K=0; K<=99; K++){
	printf("Instance 1:");
        sprintf(plain, "%c%c%02d%02d", S,A,J,K); 
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          printf("#%-8d%s %s\n", count, plain, enc);
        } 
	else {
	printf("%-8d%s %s\n", count, plain, enc);
	}
      }
    }
  }
}
  printf("%d solutions explored\n", count);
}

void function_2(char *salt_and_encrypted){
  int H,R,E;
  char salt[7];
  char plain[7];
  char *enc;
  int count = 0;

  substr(salt, salt_and_encrypted, 0, 6);

  for(H='N';H<='Z'; H++){
    for(R='A'; R<='Z'; R++){
      for(E=0; E<=99; E++){
        for(int F=0; F<=99; F++){
	printf("Instance 2:");
        sprintf(plain, "%c%c%02d%02d", H,R,E,F); 
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          printf("#%-8d%s %s\n", count, plain, enc);
        }
        else{
        printf("%-8d%s %s\n", count, plain, enc);
        }
      }
    }
  }
}
  printf("%d solutions explored\n", count);
}





void function_3(char *salt_and_encrypted){
  int G,H,I;    
  char salt[7];
  char plain[7];
  char *enc;
  int count = 0;

  substr(salt, salt_and_encrypted, 0, 6);

  for(G='A';G<='M'; G++){
    for(H='A'; H<='Z'; H++){
      for(I=0; I<=99; I++){
        for(int J=0; J<=99; J++){
	printf("Instance 3:");
        sprintf(plain, "%c%c%02d%02d", G,H,I,J); 
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          printf("#%-8d%s %s\n", count, plain, enc);
        } 
	else {
	printf("%-8d%s %s\n", count, plain, enc);
	}
      }
    }
  }
}
  printf("%d solutions explored\n", count);
}
int time_difference(struct timespec *start, struct timespec *finish, 
                    long long int *difference) {
  long long int ds =  finish->tv_sec - start->tv_sec; 
  long long int dn =  finish->tv_nsec - start->tv_nsec; 

  if(dn < 0 ) {
    ds--;
    dn += 1000000000; 
  } 
  *difference = ds * 1000000000 + dn;
  return !(*difference > 0);
}

int main() {

  struct timespec start, finish;   
  long long int time_elapsed;

  clock_gettime(CLOCK_MONOTONIC, &start);

  int size, rank;
  int i;

  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if(size != 3){
    if (rank ==0){
	printf("this program needs to run on exactly 3 process to run\n ");
	}
}else{
 if(rank == 0){

	int x;
	MPI_Send(&x, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
	MPI_Send(&x, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);

}else if(rank==1){
 int number;
 MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
  for(i=0; i<n_passwords; i<i++){
    function_1(passwords_enc[i]);
   }
  } else if{
    int number;
    MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	for(i=0; i<n_passwords; i<i++){
          function_2(passwords_enc[i]);
   }
}
else {
    int number;
    MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	for(i=0; i<n_passwords; i<i++){
          function_3(passwords_enc[i]);
   }

}

  }

 MPI_Finalize();
  clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &time_elapsed);
  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed, 
         (time_elapsed/1.0e9)); 


  return 0;
}
