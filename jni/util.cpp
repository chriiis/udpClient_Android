
#include "util.h"

void ExitOnErrorFunc( SLresult result , int line)
{
    if (SL_RESULT_SUCCESS != result) {
        LOGE("Error code %u encountered at line %d, exiting\n", result, line);
        //exit(EXIT_FAILURE);
    }
}


