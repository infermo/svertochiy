#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QRegExp"


#include <Encoder.h>
#include <Decoder.h>

static Summator::DescrList GetDesrcList(const QString &str) {
    Summator::DescrList descrList;
    QRegExp groupRx("(\\{[\\d\\,]+\\})");
    auto sumDescrText = str;

    int offset = 0;
    while(-1 != (offset = groupRx.indexIn(sumDescrText, offset))) {
        offset += groupRx.matchedLength();
        auto curSumText = groupRx.cap(1);
        Summator::Descr descr;

        QRegExp sumRx("(\\d+)");
        int curOffset = 0;
        while(-1 != (curOffset = sumRx.indexIn(curSumText, curOffset))) {
            descr << sumRx.cap(1).toUInt();
            curOffset += sumRx.matchedLength();
        }

        if(descr.size() == 0) {
            return Summator::DescrList();
        }

        descrList << descr;
    }

    if(descrList.size() == 0) {
        return Summator::DescrList();
    }

    return descrList;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_encodeButton_clicked() {
    auto plainText = ui->plainEdit->text().toUtf8();

    Summator::DescrList descrList = GetDesrcList(ui->descripInput->text());
    if(descrList.size() == 0) {
        ui->plainLabel->setText("error");
        return;
    }

    Encoder::Settings encSettings = {
        plainText.data(),
        descrList,
        ui->registerIntput->text().toUInt()
    };

    Encoder enc(encSettings);

    auto encBufferSize = enc.GetEncodedLen();
    QByteArray encoded(encBufferSize, '\0');

    enc.Encode((unsigned char*)encoded.data());

    QString text;
    for(int i = 0; i < encoded.size(); ++i) {
        unsigned char byte = encoded[i];
        for(int j = 0; j < 8; ++j) {
            text += (byte & 0x01) ? "1" : "0";
            byte = byte >> 1;
        }
        text += " ";
    }

    ui->encodedEdit->setText(text.trimmed());
}

void MainWindow::on_decodeButton_clicked() {
    auto encodedBinText = ui->encodedEdit->text();
    auto bytesList = encodedBinText.split(" ");

    QByteArray encodedText;
    for(auto &byteText : bytesList) {
        if(byteText.size() != 8) {
            ui->plainLabel->setText("error");
            return;
        }

        unsigned char byte = 0;

        for(int i = 0; i < 8; ++i) {
            byte = byte >> 1;
            byte |= (byteText[i] == "1" ? 1 : 0) << 7;
        }

        encodedText += (char)byte;
    }

    Summator::DescrList descrList = GetDesrcList(ui->descripInput->text());
    if(descrList.size() == 0) {
        ui->plainLabel->setText("error");
        return;
    }

    Decoder::Settings decSettings = {
        {
            (unsigned char*)encodedText.data(),
            (unsigned int)encodedText.size()
        },
        descrList,
        ui->registerIntput->text().toUInt()
    };

    Decoder dec(decSettings);

    auto decBufferSize = dec.GetDecodedLen();
    QByteArray decoded(decBufferSize, '\0');

    dec.Decode((unsigned char*)decoded.data());

    ui->plainLabel->setText(decoded);
}

