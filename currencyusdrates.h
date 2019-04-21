#ifndef CURRENCYUSDRATES_H
#define CURRENCYUSDRATES_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
// Object contains rates of currencies based on USD.
class CurrencyUSDRates : public QObject
{
    Q_OBJECT

public:
    CurrencyUSDRates();
    QMap<QString, double>::key_iterator begin() const { return ratesMap.keyBegin(); }
    QMap<QString, double>::key_iterator end() const { return ratesMap.keyEnd(); }
    const QMap<QString, double>& getData() const
    {
        return ratesMap;
    }
    double getRate(QString currency)
    {
        return ratesMap.value(currency);
    }

public slots:
    void recieveData();
signals:
    void dataRecieved();

private:
    QNetworkAccessManager *nm;
    QMap<QString, double> ratesMap; // Key - currency. Value - rate to USD.
};

#endif // CURRENCYUSDRATES_H
