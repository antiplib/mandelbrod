//
// Created by Владислав Отвагин on 17.09.2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_begin.h" resolved

#include "begin.h"
#include "ui_begin.h"
#include <QPushButton>

#include "jullian.h"
#include "mainwindow.h"

begin::begin(QWidget *parent) :
    QWidget(parent), ui(new Ui::begin) {
    this->resize(450, 300);
    ui->setupUi(this);
    QPushButton *jullian = new QPushButton(this);
    QPushButton *mandelbrod = new QPushButton(this);
    jullian->setText("jullian");
    mandelbrod->setText("Mandelbrod");
    jullian->setGeometry(QRect(75, 100, 100, 100));
    mandelbrod->setGeometry(QRect(225, 100, 100, 100));
    // connect(jullian, QPushButton::clicked, this, &begin::jullian);
    connect(mandelbrod, &QPushButton::clicked, this, &begin::mandelbrod);
    connect(jullian, &QPushButton::clicked, this, &begin::jullian);


}

void begin::mandelbrod() {
    auto m = new mainwindow(this);
    this->hide();
    m->show();
}

void begin::jullian() {
    auto m = new ::jullian(this);
    this->hide();
    m->show();
}

begin::~begin() {
    delete ui;
}
