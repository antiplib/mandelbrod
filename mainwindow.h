//
// Created by Владислав Отвагин on 14.09.2024.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include "qlabel.h"
#include <QPushButton>
#include <QGraphicsRectItem>
#include "Label.h"
#include <QToolBar>
#include <QKeyEvent>
QT_BEGIN_NAMESPACE
namespace Ui { class mainwindow; }
QT_END_NAMESPACE

class mainwindow : public QMainWindow {
Q_OBJECT

public:
    explicit mainwindow(QWidget *parent = nullptr);
    ~mainwindow() override;
    void back();
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void draw(QPointF x, QPointF y);
    void hd();
    void sh();
   // void keyPressEvent(QKeyEvent* event) override;
    void press();
private:
 QLabel *settings_icon;
    QPushButton *settings;
    QLabel* set;
    QToolBar *red, *green, *blue, *alpha;

    Ui::mainwindow *ui;
    double del = 250;
    bool is_activated = 0;
    int x_beg, y_beg;
    int x_last, y_last;
    QPushButton * close;
    Label *rect;
    QGraphicsRectItem *rect_item;
    QGraphicsView* view;
    QGraphicsScene* scene;
protected:

};


#endif //MAINWINDOW_H
