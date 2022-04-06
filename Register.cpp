#include <Register.h>

Register::Register(unsigned char c) :
    _bit(c)
{

}
Register& Register::operator =(const Register &b) { // Регистр = регистр
    this->_bit = b._bit;
    return *this;
}
Register& Register::operator=(const Bit &b) { // Регистр = бит
    this->_bit = b;
    return *this;
}
