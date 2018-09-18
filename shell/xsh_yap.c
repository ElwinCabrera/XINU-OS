#include <kernel.h>
#include <stdio.h>
#include <string.h>
#include <shell.h>
#include <stdlib.h>


#define USERNUM 10

/**
 *  *  *@param stdin descriptor of input device
 *   *   *@param stdout descriptor of output device
 *    *    *@param stderr descriptor of error device
 *     *     *@param args array of arguments
 *      *      *@return OK for success, SYSERR for syntax error
 *       *       **/

typedef struct  {
	unsigned short int uID;
	char *userName;
	char *pass;
} USERS;

USERS users[USERNUM];
int currUsers=0;

char *userNames[USERNUM];
char *pass[USERNUM];


local chat (ushort, ushort, char *);
void initialize(void);
void addUser(char *, char *);
int checkUser(char *);
int validate(char *, char *);
void listUsers(void);
int isFull(void);

command xsh_yap(ushort stdin, ushort stdout, ushort stderr,ushort nargs, char *args[])
{       if(nargs>2){
                fprintf(stdout,"\033[31mInvalid number of commands\n");
                fprintf(stdout, "Useage:\n");
                fprintf( stdout,"    yap or chat\033[39m\n");

        }else{
		char userN[20], pass[20], ch;
		int loggedin = 0, i;
		//int i;
		/*for(i=0; i<USERNUM; ++i){
			users[i].userName=NULL;
			users[i].pass=NULL;
			users[i].uID=NULL;
		}*/
		

		//char admin []= "admin";
		//char adminPass[] ="admin";
		//strncpy(u.userName,admin, sizeof(admin));
		//strncpy(u.pass, adminPass, sizeof(adminPass));
		//u.uID=0;
		//addUser2(users,u,&currUsers);
		initialize();

				fprintf(stdout,"\033[1;33m	Test users:\n");
                                fprintf(stdout,"        username:user1, password:user1\n");
                                fprintf(stdout,"        username:user2, password:user1\033[0;39m\n");


		do {
                	// Retrieve username and password from user
                	fprintf (stdout, "\nUsername: ");
                	read(stdin,  userN, 20);
                        
                	fprintf (stdout, "Password: ");
			/*for(i=0; i<5; ++i){
				ch = getc(stdin);
				pass[i]=ch;
				ch = '*';
				printf("%c", ch);
			}*/
                	read(stdin,  pass, 20);


                 	//Check to see if the login was successfull
                	if ( (strncmp(userN, "user1",5) == 0 && strncmp(pass, "user1",5) == 0 ) ||
                         (strncmp(userN, "user2",5) == 0   && strncmp(pass, "user2",5) == 0 ) )
                	{
                         	//Greet the user and proceed to the chat room
                        	userN[20] = '\0';
                        	fprintf(stdout,"\n\n\033[1;33m	Welcome to XINU chat, %s\n", userN);
				fprintf(stdout,"	Type /a to add a user (admin only)\n");
				fprintf(stdout,"	Type /r to remove a user(admin only)\n");
				fprintf(stdout,"	Type /l to list all registerd users\n");
				fprintf(stdout,"	Type /q to quit.\033[0;39m\n\n");
                        	loggedin = 1;
                	}else{
                         	//Continue prompting for a login if unsuccessful login
                        	fprintf (stdout, "\nIncorrect username or password. ");
                        	fprintf (stdout, "Please try again!\n");
                	}

        	} while (loggedin == 0);


		if(stdin== TTY0){
			chat (TTY0,TTY1, userN);
		}else if(stdin ==TTY1){
			chat(TTY1,TTY0, userN);

		}
		

        }
        return OK;
}

int isFull()
{
	if(currUsers < USERNUM){
		return 0;
	} 
	return 1;
}
void initialize()
{
		userNames[0]="admin";
		pass[0]="admin";
		userNames[1]="user1";
		pass[1]="user1";
		userNames[2]="user2";
		pass[2]="user2";
		

		currUsers += 3;

}

void addUser(char *name, char *pass)
{

	/*if(currUsers < USERNUM){
		userNames[currUsers]=name;
		pass[currUsers]=pass;
		currUsers += 1;
	}*/

}
void listUsers()
{
	int i; 
	for(i=0; i<USERNUM; ++i){
		printf("user %d is: %s\n",i,userNames[i]);
	}

}

int validate(char *name, char *pass)
{
	int i;
	for(i= 0; i<USERNUM; ++i){
		if(strcmp(name,users[i].userName)==0 &&
		   strcmp(pass,users[i].pass)==0){
			return 1;
		}
	}
	return 0;

}


int checkUser(char *name)
{
	int i;
	for(i =0; i<USERNUM; ++i){
		if(strcmp(name,users[i].userName)==0){
			return 1;
		}
		
	}
	return 0;

}

local chat (ushort in, ushort out, char *name) {

        // Define local variables
        char msg[140], userN[20], pass[20];
        int i, quit = 0;

        // Continue chat room until the user exits
        while (quit == 0) {

                // Clear the message buffer
                for (i=0; i<140; i++) {
                        msg[i] = '\0';
                }

                // Take in the user message to send
                printf("> ");
                read(in, msg, 140);

		if(strncmp(msg,"/a",2)==0){ // if user wants to add a new user
			if(strcmp(name, "admin")==0){
				printf ("\nEnter new nsername: ");
                        	read(in,  userN, 20);

                        	printf ("Enter new user password: ");
                        	read(in,  pass, 20);
			
				if(isFull()==0){
				//addUser(userN, pass);
				} else {
					printf("Maximum number of users registerd, ask admin to remove a user\n");
				}
				if(validate(userN,pass)==1){
					printf("%s added successfully!\n");
				
				}else{
					printf("An error occured, unable to add user at this time.\n");
				}
			}else{
				printf("Access Denied (only admin can add/remove users)");
			}

		}else if (strncmp(msg, "/r",2)==0){ //user wants to remove
			
		}else if (strncmp(msg, "/l",2)==0){ //user wants to list current users
			listUsers();
			
		}else if ( strncmp(msg, "/q", 2) == 0) { // if user wants to quit
			char quitmsg[10];
			fprintf(in, "\nAre you sure you want to quit?[yes/no]\n");
			read(in, quitmsg,10);
			if(strncmp(quitmsg,"yes",3)==0 ||strncmp(quitmsg,"y",1)==0){
				quit=1;
				//strcpy(msg, "\n**HAS LEFT THE CHAT **\n");
				write(out, "User has left",13);
			}
                       
                }

                 //Send out the chat message
                fprintf(out, "\033[36m" "> %s:  \033[0m", name);
                write(out, msg, strlen(msg));

        }

        return OK;
}

