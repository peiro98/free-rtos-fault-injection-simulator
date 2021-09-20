#include <FreeRTOS.h>
#include <task.h>

#include <stdio.h>

#include "simulator.h"

int mustEnd = 0;

void *injectorFunction(void *arg)
{
    thData_t *data = (thData_t *)arg;

    DEBUG_PRINT("Requested injection address: %p\n", data->address);
    DEBUG_PRINT("Requested injection time: %lu\n", data->injTime);
    DEBUG_PRINT("Requested injection offset byte: %lu\n", data->offsetByte);
    DEBUG_PRINT("Requested injection offset bit: %lu\n", data->offsetBit);

    // printf("already %lu", ulGetRunTimeCounterValue());
    #ifdef POSIX
    sleepNanoseconds(data->injTime - ulGetRunTimeCounterValue());
    #else
    injectorWait ();
    #endif

    unsigned long currentTime = ulGetRunTimeCounterValue();

    DEBUG_PRINT("Performing the injection at time %lu...\n", currentTime);
    printf("Injection delay:\t%d\n", (signed) currentTime - (signed) data->injTime);
    *((char *)data->address + data->offsetByte) ^= (1 << data->offsetBit);
    DEBUG_PRINT("Injection completed\n");

    DEBUG_PRINT("Waiting the execution timeout\n");
    sleepNanoseconds(data->timeoutNs - currentTime);

    DEBUG_PRINT("The execution timeout expired\n");
    vPortGenerateSimulatedInterrupt( 5 );
    vTaskEndScheduler();

    // vTaskEndScheduler should NOT return
    DEBUG_PRINT("injectorFunction is executing past vTaskEndScheduler!!!\n");

    return NULL;
}