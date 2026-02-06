#include "counter.h"

volatile unsigned long counter = 0;

void incrementCounter() {
    counter++;
}
