#include "mainwindow.h"
#include "ui_mainwindow.h"

extern QMap<QString, double> ratesUSD;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

// How else?
void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    if(comboBoxFilled)
        return;
    comboBoxFilled = true;
    for(auto i = ratesUSD.begin(); i != ratesUSD.end(); ++i)
    {
        ui->comboBox->addItem(i.key());
        ui->comboBox_2->addItem(i.key());
    }
}
