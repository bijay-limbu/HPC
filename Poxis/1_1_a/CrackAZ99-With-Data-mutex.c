#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>
#include <pthread.h> 
#include <unistd.h> 
  
/******************************************************************************
  Demonstrates how to crack an encrypted password using a simple
  "brute force" algorithm. Works on passwords that consist only of 2 uppercase
  letters and a 2 digit integer. Your personalised data set is included in the
  code. 

  Compile with:
    cc -o CrackAZ99-With-Data-mutex CrackAZ99-With-Data-mutex.c -lcrypt

  If you want to analyse the results then use the redirection operator to send
  output to a file that you can view using an editor or the less utility:

    ./CrackAZ99-With-Data > results.txt

  Dr Kevan Buckley, University of Wolverhampton, 2018
******************************************************************************/
int n_passwords = 4;
pthread_mutex_t lock;
char *encrypted_passwords[] = {
  "$6$KB$fyo99S0gm72R/M2MTWbQnTj.Vyw0ewZaAy55Pu8EOiEoX0GC4AUTuMfvuamABMtr37/oIcXza1XOguA/vLAmG.",
  "$6$KB$H8RIsbCyr2r7L1lklCPKY0tLK9k5WudNWpxkNbx2bCBRHCsI3qyVRY.0nrovdkDLDJRsogQE9mA3OqcIafVsV0",
  "$6$KB$fpZDw2bDkmDJqQTwQLByx39LhurTAIQmFCNYU1t8EGX4gw9qwDQrkRMvNq1yf/lFPjAckzqc5K12bMGhybRBB.",
  "$6$KB$OpOIZac00sMBfYemANRTO3lKNZCFLegKAMakI3i2fk78/vZgo01X5mdG/1R1K0Ohs0V1AuxfOK7KY.th3dInb0"
};

/**
 Required by lack of standard function in C.   
*/

void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}

/**
 This function can crack the kind of password explained above. All combinations
 that are tried are displayed and when the password is found, #, is put at the 
 start of the line. Note that one of the most time consuming operations that 
 it performs is the output of intermediate results, so performance experiments 
 for this kind of program should not include this. i.e. comment out the printfs.
*/

void crack(char *salt_and_encrypted){
  int x, y, z;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space for \0
  char plain[7];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password
  int count = 0;   // The number of combinations explored so far

  substr(salt, salt_and_encrypted, 0, 6);
    pthread_mutex_lock(&lock); 
  for(x='A'; x<='Z'; x++){
    for(y='A'; y<='Z'; y++){
      for(z=0; z<=99; z++){
        sprintf(plain, "%c%c%02d", x, y, z); 
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          printf("#%-8d%s %s 1 \n", count, plain, enc);
        } else {
          printf(" %-8d%s %s  2 \n", count, plain, enc);
pthread_mutex_unlock(&lock); 
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
int main(int argc, char *argv[]){

 int i;
int error; 

if (pthread_mutex_init(&lock, NULL) != 0) { 
        printf("\n mutex init has failed\n"); 
        return 1; 
    } 
  
    
 
struct timespec start, finish;   
  long long int difference;
  int account =0;
  clock_gettime(CLOCK_MONOTONIC, &start);

  
  for(i=0;i<n_passwords;i<i++) {
    crack(encrypted_passwords[i]);
  }



  clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &difference);
  printf("run lasted %9.5lfs\n", difference/1000000000.0); 
pthread_mutex_destroy(&lock); 
  return 0;
}
