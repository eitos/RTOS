#include <inttypes.h>

#include "mutex.hpp"
#include "OS.hpp"
#include "task.hpp"
#include "EiTOSConfig.hpp"
#include "port/port.hpp"

uint8_t MutexUsed = 0;
uint8_t MutexTaken[MAX_MUTEX] = {false};

mutex::mutex() {
    MutexUsed++;
    this->nr = MutexUsed;
}

static inline void unlockTasksByMutex(uint8_t mutexNr) {
    for (uint8_t i = 0; i < TaskQueue.size(); i++) {
        if ( TaskQueue[i].blockingMutexNr == mutexNr ) {
            TaskStruct_t taskRemoved = TaskQueue[i];
            taskRemoved.blockingMutexNr = 0;
            TaskQueue.remove(i);
            TaskQueue.push(taskRemoved);
        }
    }
}

void mutex::give() {
    if ( MutexTaken[this->nr] == false )
        return;
    MutexTaken[this->nr] = false;
    unlockTasksByMutex(this->nr);
    TriggerSysTick();
}

static inline void lockTaskByMutex(uint8_t mutexNr) {
    ActrualRunningTaskStruct.blockingMutexNr = mutexNr;
}

void mutex::take() {
    if ( MutexTaken[this->nr] == false ) {
        MutexTaken[this->nr] = true;
    } else {
        lockTaskByMutex(this->nr);
        TriggerSysTick();
    }
}

bool mutex::take(uint32_t timeout) {
    return false;  // TODO(GG PR): timer.
}
