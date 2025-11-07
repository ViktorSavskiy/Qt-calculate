#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "secondwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;

private slots:
    void digit_numbers();
    void operations();
    void on_pushButton_dot_clicked();
    void on_pushButton_ac_clicked();
    void on_pushButton_ravno_clicked();
    void math_operations();
};
#endif // MAINWINDOW_H
