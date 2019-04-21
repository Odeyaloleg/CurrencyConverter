#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&usdRates, &CurrencyUSDRates::dataRecieved, this, &MainWindow::fillComboBox);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fillComboBox()
{
    for(auto i: usdRates)
    {
        ui->comboBox->addItem(i);
        ui->comboBox_2->addItem(i);
    }
}

void MainWindow::on_pushButton_clicked()
{
    // Convert to USD firstly by divine, then to necessary currency by multiple
    double faceValue = ui->lineEdit->text().toDouble() / usdRates.getRate(ui->comboBox->currentText()) *  usdRates.getRate(ui->comboBox_2->currentText());
    ui->lineEdit_2->setText(QString::number(faceValue));
}
