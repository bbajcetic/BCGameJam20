#include "custom.h"
#include "constants.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <cmath>

void wait(long seconds, long microseconds)
{
    struct timespec reqDelay = { seconds, microseconds * 1000};
    nanosleep(&reqDelay, (struct timespec*) NULL);
}

float findAngle(float adjacent, float opposite) {
    float rad;
    if (adjacent == 0) {
        rad = (opposite >= 0) ? PI/2.0 : 3.0*PI/2.0;
    }
    else {
        rad = atan(opposite/adjacent);
        if (adjacent >= 0 and opposite < 0) {
            rad = rad + 2.0*PI; /* to make angle between 0-360 */
        }
        else if (adjacent < 0) {
            rad = rad + PI;
        }
    }
    return rad;
}