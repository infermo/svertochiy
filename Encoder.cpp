#include <Encoder.h>
#include <CoderHelper.h>

#include <string.h>

Encoder::Encoder(const Settings &settings) :
    _settings(settings)
{
}
unsigned int Encoder::GetEncodedLen() {
    unsigned int sumsNum = _settings.sumDescrList.size();
    unsigned int regsNum = _settings.regsNum;

    unsigned int inputByteNum = strlen(_settings.inputText);
    unsigned int inputBitNum = inputByteNum * 8;
    unsigned int outputBitNum = sumsNum * (inputBitNum + regsNum - 1);

    unsigned int outputByteNum = (outputBitNum / 8) + ( (outputBitNum % 8) ? 1 : 0 );

    return outputByteNum + 1;
}
void Encoder::Encode(unsigned char *bufferOut) {
    unsigned int sumsNum = _settings.sumDescrList.size();
    unsigned int regsNum = _settings.regsNum;

    unsigned int inputByteNum = strlen(_settings.inputText);
    unsigned int inputBitNum = inputByteNum * 8;
    unsigned int outputBitNum = sumsNum * (inputBitNum + regsNum - 1);

    *bufferOut = 8 - (outputBitNum % 8);
    bufferOut++;

    RegisterSet rs(_settings.regsNum); // Регистры

    QList<Summator> summs;
    for(int i = 0; i < _settings.sumDescrList.size(); ++i) { // Сумматоры
        auto descr = _settings.sumDescrList[i];

        QList<const Register*> rl;

        for(int j = 0; j < descr.size(); ++j) {
            auto pos = descr[j];
            rl << &(rs[pos]);
        }

        summs << Summator(rl);
    }

    unsigned int byteBufferCounter = 0;
    for(unsigned i = 0; i < strlen(_settings.inputText); i++) { // Кодирование
        unsigned char buf = _settings.inputText[i];

        for (unsigned j = 0; j < 8; j++){
            unsigned char bit = buf & 0b01;

            rs.PushBit(bit);

            for(int k = 0; k < summs.size(); ++k) {
                auto s = summs[k].GetSum();
                CoderHelper::PushBit(&bufferOut, &byteBufferCounter, s.val);
            }

            buf = buf >> 1;
        }
    }

    for(unsigned i = 0; i < (_settings.regsNum - 1); ++i) { //Заполнение нулями
        rs.PushBit(0);

        for(int k = 0; k < summs.size(); ++k) {
            auto s = summs[k].GetSum();
            CoderHelper::PushBit(&bufferOut, &byteBufferCounter, s.val);
        }
    }
}
