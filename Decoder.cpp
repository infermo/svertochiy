#include "Decoder.h"

#include <CoderHelper.h>

#include <string.h>

Decoder::Decoder(const Settings &settings) :
    _settings(settings) // Копируются settings
{

}
unsigned int Decoder::GetDecodedLen() {
    const unsigned int encodedBytesNum = _settings.input.len - 1;
    const unsigned int decodedBytesNum = encodedBytesNum / _settings.sumDescrList.size();

    return decodedBytesNum + 1;
}
int Decoder::GetWeight(RegisterSet rs, Bit b, const Segment &seg) {
    rs.PushBit(b);

    QList<Summator> summs; //Список сумматоров
    for(int i = 0; i < _settings.sumDescrList.size(); ++i) {
        auto descr = _settings.sumDescrList[i];

        QList<const Register*> rl;

        for(int j = 0; j < descr.size(); ++j) {
            auto pos = descr[j];
            rl << &(rs[pos]);
        }

        summs << Summator(rl);
    }

    Segment curSeg;

    for(int k = 0; k < summs.size(); ++k) {
        auto s = summs[k].GetSum(); // Выход сумматора
        curSeg << s;
    }

    int weight = 0;
    for(int i = 0; i < curSeg.size(); ++i) {
        if(curSeg[i] != seg[i]) {
            ++weight;
        }
    }

    return weight;
}
void Decoder::Decode(unsigned char *out) {
    unsigned int extraBits = *_settings.input.buffer;

    memset(out, 0x00, GetDecodedLen());
    SegmentList sl;

    unsigned int sumsNum = _settings.sumDescrList.size();
    unsigned int counter = 0;
    unsigned int extraSegments = extraBits / sumsNum;

    Segment currentSegment;

    for(unsigned int i = 1; i < _settings.input.len; ++i) { // Из массива входных байт создается список сегментов
        auto byte = _settings.input.buffer[i];
        for(int j = 0; j < 8; ++j) {
            currentSegment << Bit(byte & 0x01);
            byte = byte >> 1;
            ++counter;

            if(counter == sumsNum) {
                sl << currentSegment;
                currentSegment.clear();
                counter = 0;
            }
        }
    }

    while(extraSegments--) {
        sl.pop_back();
    }

    RegisterSet rs(_settings.regsNum);

    counter = 0;
    auto maxSl = sl.size() - _settings.regsNum + 1;
    for(unsigned int i = 0; i < maxSl; ++i) {
        auto w0 = GetWeight(rs, 0, sl[i]);
        auto w1 = GetWeight(rs, 1, sl[i]);

        char bit = (w0 <= w1) ? 0 : 1;
        rs.PushBit(bit);
        CoderHelper::PushBit(&out, &counter, bit);
    }
}
