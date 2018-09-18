#include <kernel.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NFRAME 10
#define NSLOT 2
//hyperperiod = 20

/**
 *  *  *@param stdin descriptor of input device
 *   *   *@param stdout descriptor of output device
 *    *    *@param stderr descriptor of error device
 *     *     *@param args array of arguments
 *      *      *@return OK for success, SYSERR for syntax error
 *       *       **/
int hp=20;

void task1(void);
void task2(void);
void task3(void);
void task4(void);
void task5(void);
void burn(void);

void (*ttable1[NFRAME][NSLOT])(void);
void (*ttable2[NFRAME][NSLOT])(void);


command xsh_schedule(ushort stdin, ushort stdout, ushort stderr,ushort nargs, char *args[])
{       if(nargs==1 || nargs>2){
                fprintf(stdout,"\n\033[1;31mInvalid number of commands\n");
                fprintf(stdout, "Useage:\n");
                fprintf( stdout,"    schedule <1 or 2> or sch <1 or 2>\033[0;39m\n");

        }else{

		int frame, slot;
		
		if(strcmp(args[1],"1")==0){
			fprintf(stdout, "\n\033[1;33m	Hyperperiod: 12\n");
                	fprintf(stdout, "	Frame size: %d\n", NSLOT);
                	fprintf(stdout, "	Total Frames to complete 1 Hyperperiod: 6\033[0;39m\n\n");
			
			while (1) {
                                fprintf(stdout,"\n\033[33mStarting a new hyperperiod \033[39m\n");
                                for (frame=0; frame <6; frame++){
                                        fprintf (stdout,"\n\033[33mStarting a new frame \033[39m\n");
                                        for (slot=0; slot<NSLOT; slot++){
                                                (*ttable1[frame][slot])();
                                        }
                                }
                        }


		} else if (strcmp(args[1],"2")==0){
			fprintf(stdout, "\n\033[1;33m	Hyperperiod: %d\n", hp);
                	fprintf(stdout, "	Frame size: %d\n", NSLOT);
                	fprintf(stdout, "	Total Frames to complete 1 Hyperperiod: %d\033[0;39m\n", NFRAME);

			while (1) {
				fprintf(stdout,"\n\033[33mStarting a new hyperperiod \033[39m\n");
				for (frame=0; frame <NFRAME; frame++){
        				fprintf (stdout,"\n\033[33mStarting a new frame \033[39m\n");
        				for (slot=0; slot<NSLOT; slot++){
          					(*ttable2[frame][slot])();
        				}
      				}
				fprintf(stdout,"\033[0;39m");
  			}
		} else {
			fprintf(stdout, "\n\033[1;31m33Useage:\n");
                	fprintf( stdout,"    schedule <1 or 2> or sch <1 or 2>\033[0;39m\n");
		}
        }
        return OK;
}

void task1() {
  printf("Task 1 in the house!\n");
  sleep(2000);
}


void task2() {
  printf("Task 2 in the house!\n");
  sleep(2000);
}

void task3() {
  printf("Task 3 in the house!\n");
  sleep(2000);
}

void task4() {
  printf("Task 4   here homie!\n");
  sleep(2000);
}


void burn() {
printf ("BURN!!\n");
}

void (*ttable1[NFRAME][NSLOT])(void) = {
{task3, task2},
{task1, task1},
{task2, burn},
{task1, task1},
{task1, task1},
{task1, task1}
};

void (*ttable2[NFRAME][NSLOT])(void) = {
{task1, task3},
{task2, burn},
{task4, task4},
{task1, burn},
{task2, burn},
{task1, burn},
{task2, burn},
{task1, burn},
{task2, burn},
{task1, burn}
};

