#include "philosopher.h"

void* routine() 
{
    printf("Hello from threads\n");
    sleep(3);
    printf("Ending thread\n");
}