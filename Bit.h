#pragma once

struct Bit {
    unsigned char val : 1;
    unsigned : 31;

    Bit(unsigned char i = 0);

    Bit &operator=(unsigned int b);
    Bit operator+(const Bit &b) const;
    bool operator ==(const Bit &b) const;
    bool operator !=(const Bit &b) const;
};

