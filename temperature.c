#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#define KEY 1000 /key for the shm/
#define LOWER_TEMP_BOUND 0
#define UPPER_TEMP_BOUND 100.00

int main()
{
    int shm_id;
    int i=0;
    float temperature;
    float *p=0;

    printf("Shm:Start of temperature of writer process\n");

    //request shared memory of size 2x integer size
    shm_id = shmget(KEY,2*sizeof(int),IPC_CREAT|0660); //excess give to the
    process at this shared memory
    if(shm_id == -1){ //shared memory not created
    perror("shmat:");
    exit(1);
    }
    p=(float*)shmat(shm_id,NULL,0);

    while(1)
{
    sleep(5);
    temperature = LOWER_TEMP_BOUND+(float)(UPPER_TEMP_BOUND*rand()/(RAND_MAX+
    1.0));//start writing
    p[i]=temperature;
    printf("The temperature is %.2f\n",p[i]);
}
}