#include "mainwindow.h"
#include <QApplication>

QMap<QString, double> ratesUSD;

void requestFinished(QNetworkReply*);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    // Request data
    QNetworkAccessManager nm;
    QObject::connect(&nm, &QNetworkAccessManager::finished, requestFinished);
    nm.get(QNetworkRequest(QStringLiteral("http://openexchangerates.org/api/latest.json?app_id=22b4523fa2774ffcbd8348d92bcd279f")));

    return a.exec();
}

void requestFinished(QNetworkReply* rep)
{
    if (rep->error() == QNetworkReply::NoError)
    {
        QByteArray rawdata = rep->readAll();
        QString currenciesList = QString::fromUtf8(rawdata);

        // Fill map
        for(QString::size_type i = 197; ratesUSD.size() != 170; i += 7)
        {
            QString currency, rateUSD;
            currency.clear();
            rateUSD.clear();
            for(QString::size_type j = 0; j < 3; ++j)
                currency += currenciesList[i + j];
            i += 6;
            for(;currenciesList[i] != ","; ++i)
                rateUSD += currenciesList[i];
            ratesUSD.insert(currency, rateUSD.toDouble());
        }
    }
    else
        qDebug() << "Request failed: " << rep->errorString();

    rep->deleteLater();
}
