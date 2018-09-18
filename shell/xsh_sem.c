#include <kernel.h>
#include <stdio.h>
#include <stdlib.h>
#include <proc.h>
#include <semaphore.h>
#include <string.h>

/**
 *  *  *@param stdin descriptor of input device
 *   *   *@param stdout descriptor of output device
 *    *    *@param stderr descriptor of error device
 *     *     *@param args array of arguments
 *      *      *@return OK for success, SYSERR for syntax error
 *       *       **/
int counter;



semaphore sem1;

semaphore sync1_2;
semaphore sync2_3;
semaphore sync3_1;

void process1(void);
void process2(void);
void process3(void);

void processSync1(void);
void processSync2(void);
void processSync3(void);

command xsh_sem(ushort stdin, ushort stdout, ushort stderr,ushort nargs, char *args[])
{       if(nargs==1 || nargs>2){
	fprintf(stdout,"\n\033[0;31mInvalid number of commands\n");
                fprintf(stdout, "Useage:\n");
                fprintf( stdout,"    sem <1 or 2> or sem < sync or muex>\033[0;39m\n");

        }else{
		counter=0;

		if(strcmp(args[1],"2")==0 || strcmp(args[1],"muex")==0){

		fprintf(stdout, "\n\033[36mInitial counter value: %d\033[39m\n", counter);
		sem1= newsem(1);

		ready(create((void*)process1, INITSTK, INITPRIO, "PROCESS1",2,0,NULL), RESCHED_NO);
		ready(create((void*)process2, INITSTK, INITPRIO, "PROCESS2",2,0,NULL), RESCHED_NO);
		ready(create((void*)process3, INITSTK, INITPRIO, "PROCESS3",2,0,NULL), RESCHED_NO);
		
		}else if(strcmp(args[1],"1")==0 || strcmp(args[1],"sync")==0){

		sync1_2=newsem(0);
		sync2_3=newsem(0);
		sync3_1=newsem(0);

		fprintf(stdout, "\n\033[36mInitial counter value: %d\033[39m\n", counter);
		
		ready(create((void*)processSync1, 0, 0, "PROCESSSync1",2,0,NULL), RESCHED_NO);
                ready(create((void*)processSync2, 0, 0, "PROCESSSync2",2,0,NULL), RESCHED_NO);
                ready(create((void*)processSync3, 0, 0, "PROCESSSync3",2,0,NULL), RESCHED_NO);
		signal(sync3_1);
		
		} else {

		fprintf(stdout, "\n\033[0;31mUseage:\n");
                fprintf( stdout,"    sem <1 or 2> or sem < sync or muex>\033[0;39m\n");

		}



        }
        return OK;
}

/**below are the processes for semaphore Mutual exclusion**/
void process1()
{
	while(1){
		sleep(rand()%1000);
		wait(sem1);
		counter++;
		printf("Process 1 updates counter: %d\n", counter);
		signal(sem1);
	}
}

void process2()
{
        while(1){
                sleep(rand()%1000);
                wait(sem1);
                counter++;
		printf("Process 2 updates counter: %d\n", counter);
                signal(sem1);
        }

}

void process3()
{
        while(1){
                sleep(rand()%1000);
                wait(sem1);
                counter++;
		printf("Process 3 updates counter: %d\n", counter);
                signal(sem1);
        }

}

/*below are the processes for semaphore synchronization*/
void processSync1()
{
        while(1){
                sleep(rand()%1000);
                wait(sync3_1);
                counter++;
                //fprintf(stdout, "Process 1 updates counter: %d\n", counter);
		printf("Process 1 updates counter: %d\n", counter);
                signal(sync1_2);
        }
}

void processSync2()
{
        while(1){
                sleep(rand()%1000);
                wait(sync1_2);
                counter++;
                //fprintf(stdout, "Process 2 updates counter: %d\n", counter);
		printf("Process 2 updates counter: %d\n", counter);
                signal(sync2_3);
        }

}

void processSync3()
{
        while(1){
                sleep(rand()%1000);
                wait(sync2_3);
                counter++;
                //fprintf(stdout, "Process 3 updates counter: %d\n", counter);
		printf("Process 3 updates counter: %d\n\n", counter);
                signal(sync3_1);
        }

}
