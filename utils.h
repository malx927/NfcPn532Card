#ifndef UTILS_H
#define UTILS_H
#include <QByteArray>
#include <QDate>

QByteArray intToByte1(int i)
{
    QByteArray abyte0;
    abyte0.resize(1);
    abyte0[0] = static_cast<char>(0x000000ff & i);
    return abyte0;
}

QByteArray intToByte4(uint i)
{
    QByteArray abyte0;
    abyte0.resize(4);
    abyte0[0] = static_cast<char>((0xff000000 & i) >> 24);
    abyte0[1] = static_cast<char>((0x00ff0000 & i) >> 16);
    abyte0[2] = static_cast<char>((0x0000ff00 & i) >> 8);
    abyte0[3] = static_cast<char>(0x000000ff & i);
    return abyte0;
}

QByteArray date2byte(QDate date)
{
    int year = date.year();
    int mon = date.month();
    int day = date.day();
    int high_year = year/100;
    int low_year = year%100;
    QByteArray arr;
    arr.append(intToByte1(high_year));
    arr.append(intToByte1(low_year));
    arr.append(intToByte1(mon));
    arr.append(intToByte1(day));
    return arr;

}

#endif // UTILS_H
