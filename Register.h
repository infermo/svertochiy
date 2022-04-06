#pragma once

#include "Bit.h"

struct Register {
    Register(unsigned char c = 0);

    Register &operator=(const Register &b);
    Register &operator=(const Bit &b);

    Bit _bit;
};

