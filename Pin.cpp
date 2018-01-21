#include <QString>
#include <string>
#include <Pin.h>
#include <QMessageBox>
#include <mainwindow.h>
QString Pin::getPin() const
{
    return pin;
}

void Pin::setPin(QString value)
{
    this->pin = value;
}

Pin::Pin(QString pinValue, int retryCount)
{
    this->pin = pinValue;
    this->retryCounter  = retryCount;
}

bool Pin::verifyPin(QString pinToCompare)
{
    if(this->pin == pinToCompare)
    {
        if(this->retryCounter != RETRY_COUNT)
            this->retryCounter =RETRY_COUNT;
        return true;
    }
    else
    {
        this->retryCounter--;
        QMessageBox::information(0,QString("Error Window"),"Pin verification failed!");
        return false;
    }
}

bool Pin::changePin(QString oldPin,QString newPin)
{
    if(this->verifyPin(oldPin))
    {
        this->setPin(newPin);
        return true;
    }
    return false;
}
