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

int isPalindrome(char buff[], int length);

command xsh_palindrome(ushort stdin, ushort stdout, ushort stderr,ushort nargs, char *args[])
{       if(nargs==1 || nargs>2){
                fprintf(stdout,"Invalid number of commands\n");
                fprintf(stdout, "Useage:\n");
                fprintf( stdout,"    palindrome <word/character>\n");

        }else{
		int strLen = strlen(args[1]);
		if(isPalindrome(args[1],strLen-1)==1){
			fprintf(stdout, "yes\n");
		} else {
			fprintf(stdout, "no\n");
		}
	
        }
        return OK;
}

int isPalindrome(char buff[], int length)
{
	int j=0;
	int returnInt=0;
	
	while(length>j){
		if(buff[j++] != buff[length--]){
			//not palindrome
			return returnInt;
		}
	
	}
	returnInt=1;
	return returnInt;

}



