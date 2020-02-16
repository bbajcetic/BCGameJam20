#include "custom.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void wait(long seconds, long microseconds)
{
    struct timespec reqDelay = { seconds, microseconds * 1000};
    nanosleep(&reqDelay, (struct timespec*) NULL);
}

