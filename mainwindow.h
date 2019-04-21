#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "currencyusdrates.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void fillComboBox(); // Fills combo boxes with currencies
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    CurrencyUSDRates usdRates;
};

#endif // MAINWINDOW_H
