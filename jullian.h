//
// Created by Владислав Отвагин on 17.09.2024.
//

#ifndef JULLIAN_H
#define JULLIAN_H
#include <QObject>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include "qlabel.h"
#include <QGraphicsRectItem>
#include "Label.h"
#include <QWidget>
class jullian : public QMainWindow{
Q_OBJECT
public:
    explicit jullian(QWidget *parent = nullptr);
    ~jullian() override;
    void back();
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void draw(QPointF x, QPointF y);
    // void keyPressEvent(QKeyEvent* event) override;
    void press();
private:
    double del = 250;
    bool is_activated = 0;
    int x_beg, y_beg;
    int x_last, y_last;
    Label *rect;
    QGraphicsRectItem *rect_item;
    QGraphicsView* view;
    QGraphicsScene* scene;
protected:
};



#endif //JULLIAN_H
