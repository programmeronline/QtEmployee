#ifndef PIN_H
#define PIN_H
#include <QString>

class Pin
{
public:
    QString pin;
    int retryCounter;
public:
    Pin(QString pinValue, int retry);
    bool verifyPin(QString enteredPin);
    bool changePin(QString oldPin,QString newPin);
    QString getPin() const;
    void setPin(QString value);
};

#endif // PIN_H
