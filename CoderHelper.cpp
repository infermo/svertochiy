#include "CoderHelper.h"

void CoderHelper::PushBit(unsigned char **outBytePtr, unsigned int *counter, const char &bit) {
    (**outBytePtr) = ((**outBytePtr) >> 1);
    (**outBytePtr) = (**outBytePtr) | (bit << 7);
    (*counter)++;

    if((*counter) == 8) {
        (*outBytePtr)++;
        (*counter) = 0;
    }
}
