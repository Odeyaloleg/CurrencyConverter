#include "currencyusdrates.h"

CurrencyUSDRates::CurrencyUSDRates()
{
    // Request data
    nm = new QNetworkAccessManager();
    QUrl url("http://openexchangerates.org/api/latest.json?app_id=22b4523fa2774ffcbd8348d92bcd279f");
    QNetworkRequest request(url);
    QNetworkReply *reply = nm->get(request);
    connect(reply, &QNetworkReply::finished, this, &CurrencyUSDRates::recieveData);
}

void CurrencyUSDRates::recieveData()
{
    QNetworkReply *rep = qobject_cast<QNetworkReply*>(sender());
    if (rep->error() == QNetworkReply::NoError)
    {
        QByteArray rawdata = rep->readAll();
        QString currenciesData = QString::fromUtf8(rawdata);

        // Fill map
        QString currency, rateUSD;
        for(QString::size_type i = 197; ratesMap.size() != 170; i += 7)
        {
            currency.clear();
            rateUSD.clear();
            for(QString::size_type j = 0; j < 3; ++j)
                currency += currenciesData[i + j];
            i += 6;
            for(;currenciesData[i] != ","; ++i)
                rateUSD += currenciesData[i];
            ratesMap.insert(currency, rateUSD.toDouble());
        }

        emit dataRecieved();
    }
    else
        qDebug() << "Request failed: " << rep->errorString();

    rep->deleteLater();
}
