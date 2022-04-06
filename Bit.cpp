#include <Bit.h>

Bit::Bit(unsigned char i) :
    val(i)
{

}
Bit& Bit::operator =(unsigned int b)
{
    this->val = b;
    return *this;
}
Bit Bit::operator +(const Bit &b) const
{
    return this->val + b.val;
}

bool Bit::operator ==(const Bit &b) const {
    return (this->val == b.val);
}
bool Bit::operator !=(const Bit &b) const {
    return (this->val != b.val);
}
