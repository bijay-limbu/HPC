#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>

/*
  Compile with:
    cc -o CrackAZ99-With-Data CrackAZ99-With-Data.c -lcrypt

    
 */
int total_passwords = 4;

char *encrypted_passwords[] = {
  "$6$KB$fyo99S0gm72R/M2MTWbQnTj.Vyw0ewZaAy55Pu8EOiEoX0GC4AUTuMfvuamABMtr37/oIcXza1XOguA/vLAmG.",
  "$6$KB$H8RIsbCyr2r7L1lklCPKY0tLK9k5WudNWpxkNbx2bCBRHCsI3qyVRY.0nrovdkDLDJRsogQE9mA3OqcIafVsV0",
  "$6$KB$fpZDw2bDkmDJqQTwQLByx39LhurTAIQmFCNYU1t8EGX4gw9qwDQrkRMvNq1yf/lFPjAckzqc5K12bMGhybRBB.",
  "$6$KB$OpOIZac00sMBfYemANRTO3lKNZCFLegKAMakI3i2fk78/vZgo01X5mdG/1R1K0Ohs0V1AuxfOK7KY.th3dInb0"
};



void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}

9840247477

void pass_crack(char *salt_and_encrypted){
  int b, i,j ;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space for \0
  char plain[7];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password
  int count = 0;   // The number of combinations explored so far

  substr(salt, salt_and_encrypted, 0, 6);

  for(b='A'; b<='Z'; b++){
    for(i='A'; i<='Z'; i++){
      for(j=0; j<=99; j++){
        sprintf(plain, "%c%c%02d", b, i, j); 
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          printf("#%-8d%s %s 1\n", count, plain, enc);
        } else {
          printf(" %-8d%s %s 2 \n", count, plain, enc);
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
struct timespec start, finish;   
  long long int difference;
  int account =0;
  clock_gettime(CLOCK_MONOTONIC, &start);

  
  for(i=0;i<total_passwords;i<i++) {
    pass_crack(encrypted_passwords[i]);
  }

  clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &difference);
  printf("run lasted %9.5lfs\n", difference/1000000000.0); 

  return 0;
}
