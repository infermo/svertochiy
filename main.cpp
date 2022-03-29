#include <iostream>

using namespace std;




struct Bit {
    char val       : 1;
    char           : 7;

    Bit(unsigned int i) : val(i) {}

    Bit& operator = (int b) {
        this->val = b;
        return *this;
    }

    Bit operator + (const Bit &b) const {
        return this->val + b.val;
    }
};

struct Register {
    Register(char c = 0) : _bit(c == 0 ? 0 : 1) {}

    Bit _bit;

    Register *_next = nullptr;
    Register *_prev = nullptr;

    Register& operator = (const Register &b) {
        this->_bit = b._bit;
        return *this;
    }
    Register& operator = (const Bit &b) {
        this->_bit = b;
        return *this;
    }
};

Register* GenerateRegisterList(unsigned int num) {
    if(0 == num) {
        return nullptr;
    }

    auto first = new Register();
    auto ptr = first;

    for(unsigned int i = 1; i < num; ++i) {
        ptr->_next = new Register();
        ptr->_next->_prev = ptr;
        ptr = ptr->_next;
    }

    return first;
}


Register* FindLast(Register *reg) {
    if(nullptr == reg) {
        return nullptr;
    }

    while(nullptr != reg->_next) {
        reg = reg->_next;
    }

    return reg;
}

//void ShiftRegistersValue(Register *first) {
//    if(nullptr == first) {
//        return;
//    }

//    auto reg = FindLast(first);

//    while(nullptr != reg->_prev) {
//        *reg = *(reg->_prev);
//        reg = reg->_prev;
//    }

//    reg->_bit = 0;
//}

struct RegisterSimple {
    RegisterSimple(char c = 0) : _bit(c == 0 ? 0 : 1) {}

    char _bit    : 1;
    char         : 7;

    RegisterSimple& operator = (const RegisterSimple &b) {
        this->_bit = b._bit;
        return *this;
    }
};


void ShiftRegistersSimpleValue(RegisterSimple *reg, unsigned int len) {
    if(nullptr == reg) {
        return;
    }
    if(0 == len) {
        return;
    }

    for(int i = (len-1); i >= 1; --i) {
        reg[i] = reg[i-1];
    }

    reg[0]._bit = 0;
}

struct Summator {
    Summator(RegisterSimple *a, RegisterSimple *b) : _a(a), _b(b) {}

    Bit GetSum() {
        return _a->_bit + _b->_bit;
    }

    RegisterSimple *_a = nullptr;
    RegisterSimple *_b = nullptr;
};

int main() {
    char strin[] = "Input text";

    char buf = strin[0];

    char bit1 = buf & 0x01;
    buf = buf >> 1;

    char bit2 = buf & 0x01;

    char sum1_2 = bit1 ^ bit2;

    const unsigned int regsNum = 3;

    auto regs = GenerateRegisterList(regsNum);

    RegisterSimple regsSimple[regsNum];

    Summator sum1{&regsSimple[0], &regsSimple[1]};
    Summator sum2{&regsSimple[0], &regsSimple[2]};

    regs[0] = Bit(bit1);

    sum1.GetSum();
    sum2.GetSum();

    printf("%d",bit1);

    ShiftRegistersSimpleValue(regsSimple, regsNum);

    return 0;
}
