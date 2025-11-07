#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPixmap>
#include <QPushButton>

double num_first;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Подключение цифровых кнопок
    connect(ui->pushButton_0,SIGNAL(clicked()),this,SLOT(digit_numbers()));
    connect(ui->pushButton_1,SIGNAL(clicked()),this,SLOT(digit_numbers()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(digit_numbers()));
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(digit_numbers()));
    connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(digit_numbers()));
    connect(ui->pushButton_5,SIGNAL(clicked()),this,SLOT(digit_numbers()));
    connect(ui->pushButton_6,SIGNAL(clicked()),this,SLOT(digit_numbers()));
    connect(ui->pushButton_7,SIGNAL(clicked()),this,SLOT(digit_numbers()));
    connect(ui->pushButton_8,SIGNAL(clicked()),this,SLOT(digit_numbers()));
    connect(ui->pushButton_9,SIGNAL(clicked()),this,SLOT(digit_numbers()));

    // Подключение унарных операций
    connect(ui->pushButton_plmin,SIGNAL(clicked()),this,SLOT(operations()));
    connect(ui->pushButton_procent,SIGNAL(clicked()),this,SLOT(operations()));

    // Подключение математических операций
    connect(ui->pushButton_minus,SIGNAL(clicked()),this,SLOT(math_operations()));
    connect(ui->pushButton_plus,SIGNAL(clicked()),this,SLOT(math_operations()));
    connect(ui->pushButton_delit,SIGNAL(clicked()),this,SLOT(math_operations()));
    connect(ui->pushButton_umonozh,SIGNAL(clicked()),this,SLOT(math_operations()));

    // Делаем кнопки операций проверяемыми
    ui->pushButton_delit->setCheckable(true);
    ui->pushButton_minus->setCheckable(true);
    ui->pushButton_plus->setCheckable(true);
    ui->pushButton_umonozh->setCheckable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digit_numbers() {
    QPushButton *button = (QPushButton *)sender();

    // Если на экране "0" или результат предыдущей операции, очищаем его
    if (ui->label->text() == "0" || ui->label->text() == "Error") {
        ui->label->setText(button->text());
    } else {
        ui->label->setText(ui->label->text() + button->text());
    }
}

void MainWindow::on_pushButton_dot_clicked()
{
    if(!(ui->label->text().contains('.')) && ui->label->text() != "")
        ui->label->setText(ui->label->text() + ".");
}

void MainWindow::operations() {
    QPushButton *button = (QPushButton *)sender();

    double all_numbers;
    QString new_label;

    if(button->text() == "+/-") {
        all_numbers = (ui->label->text()).toDouble();
        all_numbers = all_numbers * -1;
        new_label = QString::number(all_numbers, 'g', 15);
        ui->label->setText(new_label);
    } else if(button->text() == "%") {
        num_first = ui->label->text().toDouble();
        ui->label->setText("");
        // Устанавливаем флаг, что ожидаем ввод процента
        ui->pushButton_procent->setCheckable(true);
    }
}

// ИСПРАВЛЕНО: правильное имя слота
void MainWindow::on_pushButton_ac_clicked()
{
    // Сброс всего калькулятора
    ui->label->setText("0");
    num_first = 0;

    // Сброс всех проверяемых кнопок
    ui->pushButton_plus->setChecked(false);
    ui->pushButton_minus->setChecked(false);
    ui->pushButton_umonozh->setChecked(false);
    ui->pushButton_delit->setChecked(false);
}

void MainWindow::math_operations()
{
    QPushButton *button = (QPushButton *)sender();

    // Сбрасываем предыдущую операцию
    ui->pushButton_plus->setChecked(false);
    ui->pushButton_minus->setChecked(false);
    ui->pushButton_umonozh->setChecked(false);
    ui->pushButton_delit->setChecked(false);

    num_first = ui->label->text().toDouble();
    ui->label->setText("");
    button->setChecked(true);
}

void MainWindow::on_pushButton_ravno_clicked()
{
    double labelNumber, num_second;
    QString new_label;

    // Проверяем, что есть второе число
    if (ui->label->text().isEmpty()) {
        return;
    }

    num_second = ui->label->text().toDouble();

    if(ui->pushButton_plus->isChecked()) {
        labelNumber = num_first + num_second;
        new_label = QString::number(labelNumber, 'g', 15);
        ui->label->setText(new_label);
        ui->pushButton_plus->setChecked(false);
    } else if(ui->pushButton_minus->isChecked())  {
        labelNumber = num_first - num_second;
        new_label = QString::number(labelNumber, 'g', 15);
        ui->label->setText(new_label);
        ui->pushButton_minus->setChecked(false);
    } else if(ui->pushButton_umonozh->isChecked()) {
        labelNumber = num_first * num_second;
        new_label = QString::number(labelNumber, 'g', 15);
        ui->label->setText(new_label);
        ui->pushButton_umonozh->setChecked(false);
    } else if(ui->pushButton_delit->isChecked())  {
        if (num_second == 0) {
            ui->label->setText("Error"); // Более информативное сообщение
        } else {
            labelNumber = num_first / num_second;
            new_label = QString::number(labelNumber, 'g', 15);
            ui->label->setText(new_label);
        }
        ui->pushButton_delit->setChecked(false);
    } else if(ui->pushButton_procent->isChecked()) {
        // Вычисление процента: num_first * (num_second / 100)
        labelNumber = num_first * (num_second / 100.0);
        new_label = QString::number(labelNumber, 'g', 15);
        ui->label->setText(new_label);
        ui->pushButton_procent->setChecked(false);
    }

    // Сбрасываем первое число после вычисления
    num_first = 0;
}



