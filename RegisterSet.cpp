#include "RegisterSet.h"

#include <string.h>

RegisterSet::RegisterSet(int len) :
    _len(len)
{
    _rs = new Register[_len];
}
RegisterSet::RegisterSet(const RegisterSet &a) :
    _len(a._len)
{
    _rs = new Register[_len];
    memcpy(_rs, a._rs, sizeof(Register) * _len);
}
RegisterSet::~RegisterSet() {
    delete[] _rs;
}
void RegisterSet::PushBit(const Bit &b) {
    Shift();
    _rs[0] = b;
}
Register& RegisterSet::operator[] (unsigned int i) {
    return _rs[i];
}
int RegisterSet::GetLen() const {
    return _len;
}
void RegisterSet::Shift() {
    for(int i = (_len - 1); i >= 1; --i) {
        _rs[i] = _rs[i -1];
    }

    _rs[0] = Bit(0);
}
