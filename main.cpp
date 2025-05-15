#include <iostream>
#include "scheduler.h"


int main(){

    Scheduler shed(24, 8, 1);
    shed.green_execution();
    return 0;
}