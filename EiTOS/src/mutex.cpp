#include "mutex.hpp"
#include "task"

uint8_t MutexUsed = 0;

mutex::mutex() {
    MutexUsed++;
    this->nr = MutexUsed;
}

void mutex::give() {
    for (uint8_t i = 0; i < TaskQueue->size(); i++) {
        if ( TaskQueue[i].blockingMutexNr == this->nr ) {
            // TODO(rexina): problem z usuwaniem z listy
        }
    }
}

void mutex::take() {
}

void mutex::take(uint32_t timeout) {
}
