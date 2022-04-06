#pragma once

#include <RegisterSet.h>
#include <Summator.h>

class Encoder {
public:

    struct Settings {
        const char *inputText;
        Summator::DescrList sumDescrList; // Список связей
        unsigned int regsNum;
    };

    Encoder(const Settings &settings);

    unsigned int GetEncodedLen();
    void Encode(unsigned char *out);

private:
    const Settings _settings;
};
