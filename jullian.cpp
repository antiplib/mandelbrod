//
// Created by Владислав Отвагин on 17.09.2024.
//

//
// Created by Владислав Отвагин on 14.09.2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_mainwindow.h" resolved

#include <QGraphicsView>
#include <QGraphicsScene>
#include <vector>
#include <QGraphicsLineItem>
#include "complex.h"
#include <QMouseEvent>
#include <QCursor>
#include <QGraphicsSceneMouseEvent>
#include <QLabel>
#include <QPushButton>
#include <QToolBar>
#include "jullian.h"
std::vector <std::vector <std::vector <complex>>> prevv;
std::vector <std::vector <complex>> matrixx;
// std::vector <std::vector <QGraphicsLineItem*>> mat;
std::vector <std::pair<std::pair <double, double>, std::pair <double, double>>> coords;


int step = 100;
int okurk = 4;

QColor gets_color(complex &a) {
    int iterations = 0;
    complex b(0, 0);
    while(abs(b) <= okurk) {
        iterations++;
        complex c(1, 0);
        b = b*b+c;
        if(iterations == 200)
            return Qt::black;
    }
    return QColor::fromRgb((iterations*10)%256, (iterations * 10)%256, (iterations * 10)%256); ;
}

QColor gets_color_new(complex &a, double x, double y) {
    int iterations = 0;
    complex b(x, y);
    while(abs(b) <= okurk) {
        iterations++;
        b = b*b*b*b*b-a;
        if(iterations == step)
            return Qt::black;
    }
    return QColor::fromRgb((iterations*10 )%256, (iterations * 10)%256, (iterations * 10)%256); ;
}


jullian::jullian(QWidget *parent):
    QMainWindow(parent) {
     QCoreApplication::instance()->installEventFilter(this);
     setMouseTracking(true);
    this->resize(1020, 760);
    view = new QGraphicsView(this);
     rect = new Label(this);

    scene = new QGraphicsScene(view);
    QPixmap pixmap;
    //pixmap.setBrush(fromRgb(0, 255, 50, 50));
    QPushButton *back = new QPushButton(this);
    back->setGeometry(10, 10, 50,30);
    back->setText("Back");
    rect->setStyleSheet("background-color: rgba(50, 50, 200, 100);");
    rect->setGeometry(QRect(0, 0, 0, 0));
    view->setGeometry(QRect(10, 50, 1000, 700));
    view->setScene(scene);
    view->setDisabled(true);
    scene->setSceneRect(0, 0, 1000, 700);
    matrixx.resize(1000, std::vector <complex>(700));
    for(double j = 0; j < 1000; ++j) {
        for(double i = 0; i < 700; ++i) {
            double x, y;
            if(j <= 500) {
                x =  -(500-j)/del;
            } else {
                x = -(-j + 500.0)/del;
            }
            if(i <= 350) {
                y = (350 - i)/del;
            } else {
                y = (-i + 350 )/del;
            }
            // x = j / 200.0;
            // y = i / 200.0;
            complex a(x,y);
            matrixx[j][i] = a;
        }
    }
     coords.push_back({{-3, 3.5},{2, -3.50}});
     //rect_item = new QGraphicsRectItem();

     QColor color(200, 0, 255, 100);
     QBrush brush(color);
    //rect_item->setBrush(brush);
    connect(back, &QPushButton::clicked, this,  &jullian::back);
    for(int j = 0; j < 1000; ++j) {
        for(int i = 0; i < 700; ++i) {
            QGraphicsLineItem* line = new QGraphicsLineItem;
            line->setLine(j, i, j, i);
            QPen pen;
            pen.setColor(gets_color(matrixx[j][i]));
            line->setPen(pen);
            scene->addItem(line);
        }
    }
}

jullian::~jullian() {
}


void jullian::back() {
    if(prevv.size() == 0)
        return;
    scene->clear();
    step/=2;
    matrixx= prevv[prevv.size() - 1];
    prevv.pop_back();
    for(int j = 0; j < 1000; ++j) {
        for(int i = 0; i < 700; ++i) {
            QGraphicsLineItem* line = new QGraphicsLineItem;
            line->setLine(j, i, j, i);
            QPen pen;
            pen.setColor(gets_color(matrixx[j][i]));
            line->setPen(pen);
            scene->addItem(line);
        }
    }
    scene->update();
}


void jullian::mousePressEvent(QMouseEvent *event)
 {
 if(event->button() == Qt::LeftButton && !is_activated) {
     is_activated = 1;

         x_beg = (int)event->x() ;
         y_beg = (int)event->y() ;

     rect->setGeometry(QRect(x_beg, y_beg, 10, 10));
     scene->update();

     rect->raise();
     rect->show();
     this->update();
    }
 }

void jullian::mouseMoveEvent(QMouseEvent *event) {
    if (is_activated) {
        int x = event->x() ;
        int y = event->y();
        x_last = x;
        y_last = y;
        if((y - y_beg >= 0) && (x - x_beg >= 0)) {
            x_last = x;
            y_last =   y_beg + (x - x_beg)* 7 / 10;
        } else if((y - y_beg <= 0 )&&( x - x_beg <= 0)) {
            x_last = x;
            y_last =  y_beg - (x_beg - x) * 7 / 10;
        } else if((y - y_beg <= 0 ) && (x - x_beg >= 0)) {
            x_last = x;
            y_last = y_beg + (x_beg-x) * 7 / 10;
        } else if((y - y_beg >= 0) &&( x - x_beg <= 0)) {
            x_last = x;
            y_last = y_beg + (x_beg - x) * 7 / 10;
        }
        x = x_last;
        y = y_last;
        rect->setGeometry(QRect(std::min(x_beg, x), std::min(y_beg, y),
            abs(x - x_beg), abs(y - y_beg)));
        this->update();
         rect->raise();
        rect->show();
    }

 }

void jullian::draw(QPointF o, QPointF t) {
     prevv.push_back(matrixx);
     matrixx.clear();
     scene->clear();
     matrixx.resize(1000, std::vector <complex>(700));
    double plus_x = (t.x() - o.x()) /1000;
     for(double j = 0; j < 1000; ++j) {
         double plus_y = (t.y() - o.y()) /700;
         for(double i = 0; i < 700; ++i) {
             double x, y;
             x = o.x() + plus_x*j;
             y = o.y() + plus_y*i;

             complex a(x,y);
             matrixx[j][i] = a;
         }
     }
     //rect_item = new QGraphicsRectItem();

     QColor color(200, 0, 255, 100);
     QBrush brush(color);
     //rect_item->setBrush(brush);

     for(int j = 0; j < 1000; ++j) {
         for(int i = 0; i < 700; ++i) {
             QGraphicsLineItem* line = new QGraphicsLineItem;
             line->setLine(j, i, j, i);
             QPen pen;
             pen.setColor(gets_color_new(matrixx[j][i], -0, 0));
             line->setPen(pen);
             scene->addItem(line);
         }
     }
 }

 void jullian::mouseReleaseEvent(QMouseEvent *event) {
     int x = event->x() ;
     int y = event->y();
    if(x == x_beg && y == y_beg) {
        x = x_beg+10;
        y = y_beg+7;
    }
     rect->setGeometry(0, 0, 0, 0);
     is_activated = 0;
     this->update();
     rect->raise();
     x_last =  x - 10;
    x-=10;
    if((y - y_beg >= 0) && (x - x_beg >= 0)) {
        x_last = x;
        y_last =   y_beg + (x - x_beg)* 7 / 10;
    } else if((y - y_beg <= 0 )&&( x - x_beg <= 0)) {
        x_last = x;
        y_last =  y_beg - (x_beg - x) * 7 / 10;
    } else if((y - y_beg <= 0 ) && (x - x_beg >= 0)) {
        x_last = x;
        y_last = y_beg + (x_beg-x) * 7 / 10;
    } else if((y - y_beg >= 0) &&( x - x_beg <= 0)) {
        x_last = x;
        y_last = y_beg + (x_beg - x) * 7 / 10;
    }
    y_last-=50;
     double x1, x2, y1, y2;
    x1 = x_beg  - 10;
    y1 = y_beg  - 50;
    x2 = x_last ;
    y2 = y_last;
    x1 = std::min(x1, x2);
    x2 = std::max(x1, x2);
    y1 = std::min(y1, y2);
    y2 = std::max(y1, y2);
    QPointF o(matrixx[(int) x1][(int)y1].get_x(), matrixx[(int) x1][(int)y1].get_y());
    QPointF t(matrixx[(int) x2][(int)y2].get_x(), matrixx[(int) x2][(int)y2].get_y());
    coords.push_back({{x1, y1}, {x2, y2}});
    step*=2;
    draw(o, t);
 }