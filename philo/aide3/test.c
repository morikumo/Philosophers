#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "philosopher.h"

int main(int argc, char **argv)
{
    (void) argc;
    (void) argv;
    pthread_t p1;
    pthread_t p2;

	if (argc > 6 || argc < 5)
	{
		printf("wrong argument\n");
		return (1);
	}
    if (check_arg(argv) == 1)
        return (1);
    if (pthread_create(&p1, NULL, &routine, NULL) != 0) 
        return (2);
    if (pthread_create(&p2, NULL, &routine, NULL) != 0) 
        return (3);
    if (pthread_join(p1, NULL) != 0)
        return (4);
    if (pthread_join(p2, NULL) != 0)
        return (5);
    return (0);
}