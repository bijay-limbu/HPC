#include <stdio.h>
#include <cuda_runtime_api.h>
#include <time.h>

/****************************************************************************
 * An experiment with cuda kernel invocation parameters. 2x3x4 threads on  
 * one block should yield 24 kernel invocations.
 *
 * Compile with:
 *   nvcc -o 2_1_a_2d 2_1_a_2digit.cu
 *
 * Dr Kevan Buckley, University of Wolverhampton, January 2018
 *****************************************************************************/
__device__ int is_a_match(char *attempt){
char password1[] ="AA11";
char password2[] ="BB22";
char password3[] ="CC33";
char password4[] ="DD44";

char *a = attempt;
char *b = attempt;
char *c = attempt;
char *d = attempt;
char *pass1 = password1;
char *pass2 = password2;
char *pass3 = password3;
char *pass4 = password4;

 while(*a ==*pass1){
  if(*a == '\0')
 {
 printf("password:%s\n", password1);
 break;
 }
  a++;
  pass1++;
  }
 while(*b ==*pass2){
  if(*b == '\0')
 {
 printf("password:%s\n", password2);
 break;
  }
 b++;
 pass2++;
 }
 while(*c ==*pass3){
  if(*c == '\0')
{
printf("password:%s\n", password3);
break;
}
c++;
pass3++;
}
while(*d ==*pass4){
  if(*d == '\0')
{
printf("password: %s\n",password4);
return 1;
}
d++;
pass4++;
}
return 0;
}

__global__ void kernel(){
char i1, i2;

char password[7];
password[6] ='\0';

int i = blockIdx.x +65;
int j = threadIdx.x+65;
char firstMatch =i;
char secondMatch =j;

password[0] =firstMatch;
password[1] =secondMatch;
for(i1='0'; i1<='9'; i1++){
for(i2='0'; i2<='9'; i2++){

password[2] =i1;
password[3] =i2;

if(is_a_match(password)){
}
else{
//printf("tried: %s\n",password);
}
     }
    }
  }


int time_difference(struct timespec *start, struct timespec *finish,long long int *difference) {
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

  kernel<<<26,26>>>();
cudaThreadSynchronize();
 

 clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &time_elapsed);
  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed,
         (time_elapsed/1.0e9));
return 0;
}
