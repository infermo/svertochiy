#include <Summator.h>

Summator::Summator(const QList<const Register*> &rl) :
    _rl(rl)
{
}
Summator::Summator(const Summator &b) {
    *this = b; //Входной сумматор
}
Bit Summator::GetSum() const {
    auto len = _rl.size();

    Bit ret(0);

    for(int i = 0; i < len; ++i) {
        ret = ret + _rl[i]->_bit;
    }

    return ret;
}
Summator& Summator::operator=(const Summator &b) {
    _rl.clear();
    for(int i = 0; i < b._rl.size(); ++i) {
        _rl << b._rl[i];
    }

    return *this;
}
