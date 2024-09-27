//
// Created by Владислав Отвагин on 17.09.2024.
//

#ifndef BEGIN_H
#define BEGIN_H

#include <QWidget>
#include "mainwindow.h"
QT_BEGIN_NAMESPACE
namespace Ui { class begin; }
QT_END_NAMESPACE

class begin : public QWidget {
Q_OBJECT

public:
    explicit begin(QWidget *parent = nullptr);
    ~begin() override;
    void mandelbrod();
    void jullian();
private:
    Ui::begin *ui;
};


#endif //BEGIN_H
