#ifndef _SCREENSHOT_
#define _SCREENSHOT_

#include <stdlib.h>

/**
 * Get a screenshot and save it to a memory buffer
 * this will allocate a memory buffer and set the pointer
 * this will set the size of the buffer in bytes
 * returns -1 if an error occured
 */
extern int screenshot_util(size_t *, char **);

#endif