#include <kernel.h>

/**
 *@param stdin descriptor of input device
 *@param stdout descriptor of output device
 *@param stderr descriptor of error device
 *@param args array of arguments
 *@return OK for success, SYSERR for syntax error
 **/
command xsh_parrot(ushort stdin, ushort stdout, ushort stderr,ushort nargs, char *args[])
{       if(nargs==1 || nargs>2){
                fprintf(stdout,"Invalid number of commands\n");
                fprintf(stdout, "Useage:\n");
                fprintf( stdout,"    parrot <word/character>\n");

        }else{
        fprintf(stdout, "%s\n",args[1]);
        }
        return OK;
}

