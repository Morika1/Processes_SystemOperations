#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prime.h"

void howManyPrimeNumbers(int min, int max)
{
    int counter = 0;
    for (int i = min; i <= max; i++)
    {
        if (checkIfPrimeNum(i) == 1)
            counter++;
    }
    printf("count: %d\n",counter);
    if (write(STDOUT_FILENO, &counter, sizeof(int)) < 0)
        perror("write() failed");
    exit(1);
}

int checkIfPrimeNum(int numberToCheck)
{
    if ( numberToCheck == 2)
        return 1;
    if(numberToCheck==1)
        return -1;
    for (int i = numberToCheck - 1; i > 1; i--)
    {
        if (numberToCheck % i == 0)
            return -1;
    }
    return 1;
}



int main(int argc, char* argv[])
{
	if (argc != 3) {
			printf("Usage: prime <min> <max>");
			return 0;
		}

		int min = atoi(argv[1]);
		int max = atoi(argv[2]);

		howManyPrimeNumbers(min, max);

    

}

