//
// Created by Владислав Отвагин on 16.09.2024.
//
#pragma once
#ifndef LABEL_H
#define LABEL_H
#include <QLabel>
#include <QObject>
#include <QMouseEvent>

class Label : public QLabel {
Q_OBJECT
public:
  explicit Label(QWidget *parent = nullptr) : QLabel(parent) {};
 ~Label() {};
  void mousePressEvent(QMouseEvent *event) override{
      QLabel::mousePressEvent(event);
      emit clicked();
  }
  signals:
    void clicked();
};



#endif //LABEL_H
