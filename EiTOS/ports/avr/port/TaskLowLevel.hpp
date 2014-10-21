#ifndef __TASK_LOW_LEVEL_HPP__
#define __TASK_LOW_LEVEL_HPP__

#include <inttypes.h>

typedef void ( * TaskHandler_t )();

typedef struct {
	uint8_t* StackStart;
} TaskLowLevel_t;


#endif
