#include <kernel.h>
#include <stdio.h>
#include <string.h>

/**
 *  *@param stdin descriptor of input device
 *   *@param stdout descriptor of output device
 *    *@param stderr descriptor of error device
 *     *@param args array of arguments
 *      *@return OK for success, SYSERR for syntax error
 *       **/

int findNumofChar(char *buff, char find, int len);
int check(char *buff, int len);

command xsh_palan(ushort stdin, ushort stdout, ushort stderr,ushort nargs, char *args[])
{       if(nargs==1 || nargs>2){
                fprintf(stdout,"Invalid number of commands\n");
                fprintf(stdout, "Useage:\n");
                fprintf( stdout,"    palan <word/character>\n");

        }else{
        	int length = strlen(args[1]);
		if(check(args[1], length)==1){
			fprintf(stdout, "yes :)\n");
		}else {
			fprintf(stdout,"no :(\n");
		}
		
        }
        return OK;
}

int check(char *buff, int len)
{
  int i ,isOddFlag =0;

  for(i = 0; i<len; ++i){
    if(findNumofChar(buff, buff[i], len) %2 ==1){
      if (isOddFlag==1){
        return 0;
      }
      isOddFlag =1;
    }

  }
  return 1;
}

int findNumofChar(char *buff, char find, int len)
{
  int i, count =0;

  for(i =0; i<len; ++i){
    if (buff[i]==find){
      count++;
    }
  }
  return count;
}
