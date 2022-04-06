#pragma once

#include <RegisterSet.h>
#include <Summator.h>

class Decoder {
public:
    struct Settings {
        struct {
            const unsigned char *buffer;
            unsigned int len;
        } input;
        Summator::DescrList sumDescrList;
        unsigned int regsNum;
        //unsigned int depth;
    };

    Decoder(const Settings &settings);

    unsigned int GetDecodedLen();
    void Decode(unsigned char *out);

private:
    using Segment = QList<Bit>; //Segment блок битов равный количеству сумматоров
    using SegmentList = QList<Segment>;

    int GetWeight(RegisterSet, Bit, const Segment&);

    const Settings _settings;
};
