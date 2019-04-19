#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Request data
    nm = new QNetworkAccessManager(this);
    QUrl url("http://openexchangerates.org/api/latest.json?app_id=22b4523fa2774ffcbd8348d92bcd279f");
    QNetworkRequest request(url);
    QNetworkReply *reply = nm->get(request);
    connect(reply, SIGNAL(finished()), this, SLOT(requestFinished()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    // Convert to USD firstly by divine, then to necessary currency by multiple
    double faceValue = ui->lineEdit->text().toDouble() / ratesUSD.value(ui->comboBox->currentText()) *  ratesUSD.value(ui->comboBox_2->currentText());
    ui->lineEdit_2->setText(QString::number(faceValue));
}

void MainWindow::requestFinished()
{
    QNetworkReply *rep = qobject_cast<QNetworkReply*>(sender());
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

        // Fill ComboBox
        for(auto i = ratesUSD.begin(); i != ratesUSD.end(); ++i)
        {
            ui->comboBox->addItem(i.key());
            ui->comboBox_2->addItem(i.key());
        }
    }
    else
        qDebug() << "Request failed: " << rep->errorString();

    rep->deleteLater();
}
