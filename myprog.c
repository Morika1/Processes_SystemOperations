#include "myprog.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>


#define MAXSIZE 100


int globalAnswer = 0;


void handler(int sigaction)
{
    wait(NULL);
    printf("The number of all prime numbers is: %d\n",globalAnswer);
    exit(1);
}
int main(int argc, char *argv[])
{
    int totalCount = 0;
    struct sigaction sigAction;
    sigAction.sa_handler = handler;
    sigAction.sa_flags = SA_INTERRUPT;
    if(sigaction(SIGINT, &sigAction, NULL)==-1)
    {
        perror("sigaction failed");
        exit(1);
    }
    int thePipe[2];

    while (1)
    {   
       if(pipe(thePipe)<0) 
       {
          perror("pipe failed");
          exit(1);
       }
        int pid = fork();    
if(pid<0){
    perror("fork failed");
    exit(1);
}

        if (pid == 0)
         // child pro
        {       
            char num1[MAXSIZE];
            char num2[MAXSIZE];
            if(dup2(thePipe[1], STDOUT_FILENO)<0){ 
                perror("dup2 failed");
                exit(1);
            };
            close(thePipe[1]);
            read(thePipe[0], num1, sizeof(num1));
            read(thePipe[0], num2, sizeof(num2));               
            close(thePipe[0]); 
            char *args[] = {"./prime", num1, num2, NULL};
            execvp(args[0], args);
            return 0;
        }
        else
        {
            //parent pro   
            char readNum1[MAXSIZE];
            char readNum2[MAXSIZE];      
            scanf("%s", readNum1);
            scanf("%s", readNum2);
            write(thePipe[1], readNum1, MAXSIZE);
            write(thePipe[1], readNum2, MAXSIZE);
            close(thePipe[1]);
            wait(NULL);
            read(thePipe[0],&totalCount,sizeof(int));
            close(thePipe[0]);

            if(feof(stdin))
            break;

            printf("Num of prime numbers in range %s - %s : %d\n",readNum1,readNum2,totalCount);
            globalAnswer+=totalCount;
            totalCount= 0;
            
        }

    }
     printf("The number of all prime numbers is: %d\n",globalAnswer);
    close(thePipe[1]); 

    return 0;
}