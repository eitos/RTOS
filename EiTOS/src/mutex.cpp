#include <inttypes.h>

#include "mutex.hpp"
#include "task.hpp"
#include "EiTOSConfig.hpp"
#include "port/port.hpp"

uint8_t MutexUsed = 0;
uint8_t MutexTaken[MAX_MUTEX] = {false};

mutex::mutex() {
    MutexUsed++;
    this->nr = MutexUsed;
}

void mutex::give() {
    if ( MutexTaken[this->nr] == false )
        return;
    MutexTaken[this->nr] = false;
    for (uint8_t i = 0; i < TaskQueue.size(); i++) {
        if ( TaskQueue[i].blockingMutexNr == this->nr ) {
            TaskStruct_t taskRemoved = TaskQueue[i];
            taskRemoved.blockingMutexNr = 0;
            TaskQueue.remove(i);
            TaskQueue.push(taskRemoved);
        }
    }
    TriggerSysTick();
}

void mutex::take() {
    MutexTaken[this->nr] = true;
    TaskStruct_t task = TaskQueue.front();
    TaskQueue.pop();
    task.blockingMutexNr = this->nr;
    TaskQueue.push(task);
    TriggerSysTick();
}

bool mutex::take(uint32_t timeout) {
}
