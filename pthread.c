#define LOWER_PRESURE_BOUND -50 
#define UPPER_PRESURE_BOUND 500.0 

#define LOWER_TEMP_BOUND 0 
#define UPPER_TEMP_BOUND 100.0 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>



void *temperature() 
{ 
int *temperature = (int*)malloc(sizeof(int)); 
temperature[0] = LOWER_TEMP_BOUND + (int)(UPPER_TEMP_BOUND*rand()/(RAND_MAX+1.0)); 


return (void*)temperature; 
} 


void *pressure() 
{ 
int *pressure = (int*)malloc(sizeof(int)); 
pressure[0] = LOWER_PRESURE_BOUND + (int)(UPPER_PRESURE_BOUND*rand()/(RAND_MAX+1.0)); 


return (void*)pressure; 
} 

void *combine() 
{ 

int *combine = (int*)malloc(sizeof(int)); 

pthread_t thread_ID1, thread_ID2; 
void *exitstatus1, *exitstatus2; 
int *temperature_result, *pressure_result; 

pthread_create(&thread_ID1, NULL, temperature, &temperature_result); 
pthread_create(&thread_ID2, NULL, pressure, &pressure_result); 

pthread_join(thread_ID1, &exitstatus1); 
pthread_join(thread_ID2, &exitstatus2); 
 


printf("This is thread 3\n"); 
temperature_result = (int *)exitstatus1; 
printf("\nTemperature - Result Return = %d\n",*temperature_result); 
printf("\nTemperature address\t\t\t %p\n", &temperature_result); 
printf("\nTemperature pointed\t\t\t %p\n", temperature_result); 

pressure_result = (int *)exitstatus2; 
printf("\nPressure - Result Return = %d\n",*pressure_result);
printf("\nPressure address\t\t\t %p\n", &pressure_result); 
printf("\nPressure pointed\t\t\t %p\n", pressure_result); 


free(exitstatus1); 
free(exitstatus2); 
printf("\nEnd of Thread 3\n"); 
printf("\n---------------------------\n\n"); 


return (void*)combine; 
} 

void main(void) 
{ 

while (1)
{
    
printf("This Text Is From Main\n");

pthread_t thread_ID3; 
void *exitstatus3; 
int *combine_result;


pthread_create(&thread_ID3, NULL, combine, &combine_result); 
pthread_join(thread_ID3, &exitstatus3); 

sleep(4);

free(exitstatus3); 



}

}   
