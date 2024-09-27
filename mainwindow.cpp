//
// Created by Владислав Отвагин on 14.09.2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_mainwindow.h" resolved
#pragma GCC optimize("Ofast,unroll-loops,mfma,mavx,mavx2")
#pragma once

#pragma GCC target("avx,avx2,fma")
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("vpt")
#pragma GCC optimize("rename-registers")
#pragma GCC optimize("move-loop-invariants")
#pragma GCC optimize("unswitch-loops")
#pragma GCC optimize(3)
#pragma GCC optimize("O3")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#include "mainwindow.h"
#include "cmake-build-debug/mondelbrod_autogen/include/ui_mainwindow.h"
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
#include <QKeyEvent>

std::vector <std::vector <std::vector <complex>>> prev;
std::vector <std::vector <complex>> matrix;
std::vector <std::vector <QGraphicsLineItem*>> mat;
std::vector <std::pair<std::pair <double, double>, std::pair <double, double>>> cords;


int steps = 100;
int okurki = 4;

QColor get_color(complex &a) {
    int iterations = 0;
    complex b(0, 0);
    while(abs(b) <= okurki) {
        iterations++;
        b = b*b+a;
        if(iterations == 200)
            return Qt::black;
    }
    return QColor::fromRgb((iterations*10)%256, (iterations * 10)%256, (iterations * 10)%256); ;
}

QColor get_color_new(complex &a, double x, double y) {
    int iterations = 0;
    complex b(x, y);
    while(abs(b) <= okurki) {
        iterations++;
        b = b*b+a;
        if(iterations == steps)
            return Qt::black;
    }
    return QColor::fromRgb((iterations*10 )%256, (iterations * 10)%256, (iterations * 10)%256); ;
}


mainwindow::mainwindow(QWidget *parent):
    QMainWindow(parent), ui(new Ui::mainwindow) {
     QCoreApplication::instance()->installEventFilter(this);
     setMouseTracking(true);
    ui->setupUi(this);
    this->resize(1020, 760);
    view = new QGraphicsView(this);
     rect = new Label(this);

    scene = new QGraphicsScene(view);
    QPixmap pixmap;
    //pixmap.setBrush(fromRgb(0, 255, 50, 50));
    QPushButton *back = new QPushButton(this);
    back->setGeometry(10, 10, 50,30);
    back->setText("Back");
    back->setStyleSheet("QPushButton {"
    "background-color: rgba(200, 50, 50, 200);"
     "border-radius: 10px;"
     "}");



    rect->setStyleSheet("background-color: rgba(50, 50, 200, 100);");
    rect->setGeometry(QRect(0, 0, 0, 0));
    view->setGeometry(QRect(10, 50, 1000, 700));
    view->setScene(scene);
    view->setDisabled(true);
    scene->setSceneRect(0, 0, 1000, 700);
    matrix.resize(1000, std::vector <complex>(700));
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
            matrix[j][i] = a;
        }
    }
     cords.push_back({{-3, 3.5},{2, -3.50}});
    mat.resize(1000, std::vector <QGraphicsLineItem*>(700));
     //rect_item = new QGraphicsRectItem();

     QColor color(200, 0, 255, 100);
     QBrush brush(color);
    //rect_item->setBrush(brush);
    connect(back, &QPushButton::clicked, this,  &mainwindow::back);


    for(int j = 0; j < 1000; ++j) {
        for(int i = 0; i < 700; ++i) {
            QGraphicsLineItem* line = new QGraphicsLineItem;
            line->setLine(j, i, j, i);
            mat[j][i] = line;
            QPen pen;
            pen.setColor(get_color(matrix[j][i]));
            line->setPen(pen);
            scene->addItem(line);
        }
    }
}

mainwindow::~mainwindow() {
    delete ui;
}

void mainwindow::keyPressEvent(QKeyEvent *event) {

    if(event->key() == Qt::Key_Space && prev.size() >= 1) {
        scene->clear();

        while(prev.size() != 1){
        steps = 200;
            prev.pop_back();

         }
         matrix = prev[0];

         for(int j = 0; j < 1000; ++j) {
         for(int i = 0; i < 700; ++i) {
             QGraphicsLineItem* line = new QGraphicsLineItem;
             line->setLine(j, i, j, i);
             mat[j][i] = line;
             QPen pen;
             pen.setColor(get_color_new(matrix[j][i], 0, 0));
             line->setPen(pen);
             scene->addItem(line);
             scene->update();
         }
     }
    }

}

void mainwindow::back() {
    if(prev.size() == 0)
        return;
    scene->clear();
    steps/=1.5;
    matrix= prev[prev.size() - 1];
    prev.pop_back();
    for(int j = 0; j < 1000; ++j) {
        for(int i = 0; i < 700; ++i) {
            QGraphicsLineItem* line = new QGraphicsLineItem;
            line->setLine(j, i, j, i);
            mat[j][i] = line;
            QPen pen;
            pen.setColor(get_color(matrix[j][i]));
            line->setPen(pen);
            scene->addItem(line);
        }
    }
    scene->update();
}


void mainwindow::mousePressEvent(QMouseEvent *event)
 {
 if(event->button() == Qt::LeftButton && !is_activated) {
     is_activated = 1;
if(event->x() <10 || event->y() <= 50) {
    is_activated = 0;
    return;
}
         x_beg = (int)event->x() ;
         y_beg = (int)event->y() ;

     rect->setGeometry(QRect(x_beg, y_beg, 10, 10));
     scene->update();

     rect->raise();
     rect->show();
     this->update();
    }
 }

void mainwindow::mouseMoveEvent(QMouseEvent *event) {
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

void mainwindow::draw(QPointF o, QPointF t) {
     prev.push_back(matrix);
     matrix.clear();
     scene->clear();
     matrix.resize(1000, std::vector <complex>(700));
    double plus_x = (t.x() - o.x()) /1000;
     for(double j = 0; j < 1000; ++j) {
         double plus_y = (t.y() - o.y()) /700;
         for(double i = 0; i < 700; ++i) {
             double x, y;
             x = o.x() + plus_x*j;
             y = o.y() + plus_y*i;

             complex a(x,y);
             matrix[j][i] = a;
         }
     }
     mat.resize(1000, std::vector <QGraphicsLineItem*>(700));
     //rect_item = new QGraphicsRectItem();

     QColor color(200, 0, 255, 100);
     QBrush brush(color);
     //rect_item->setBrush(brush);

     for(int j = 0; j < 1000; ++j) {
         for(int i = 0; i < 700; ++i) {
             QGraphicsLineItem* line = new QGraphicsLineItem;
             line->setLine(j, i, j, i);
             mat[j][i] = line;
             QPen pen;
             pen.setColor(get_color_new(matrix[j][i], -0, 0));
             line->setPen(pen);
             scene->addItem(line);
         }
     }
 }

 void mainwindow::mouseReleaseEvent(QMouseEvent *event) {
    if(!is_activated) {
        return;
    }
    is_activated = 0;
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
     //x-=10;
     y_beg-=50;
     x_beg-=10;
    if((y - y_beg >= 0) && (x - x_beg >= 0)) {
            x_last = x;
            y_last =   y_beg + (x - x_beg)* 7 / 10;
        } else if((y - y_beg <= 0 )&&( x - x_beg <= 0)) {
            x_last = x;
            y_last =  y_beg + (x_beg - x) * 7 / 10;
        } else if((y - y_beg <= 0 ) && (x - x_beg >= 0)) {
            x_last = x;
            y_last = y_beg + (x_beg-x) * 7 / 10;
        } else if((y - y_beg >= 0) &&( x - x_beg <= 0)) {
            x_last = x;
            y_last = y_beg + (x_beg - x) * 7 / 10;
        }


     double x1, x2, y1, y2;
    x1 = x_beg  ;
    y1 = y_beg ;
    x2 = x_last ;
    y2 = y_last;
    double xx1 = std::min(x1, x2);
    double xx2 = std::max(x1, x2);
    double yy1 = std::max(y1, y2);
    double yy2 = std::1min(y1, y2);
    x1 = xx1;
    y1 = yy1;
    x2 = xx2;
    y2 = yy2;

    QPointF o(matrix[(int) x1][(int)y1].get_x(), matrix[(int) x1][(int)y1].get_y());
    QPointF t(matrix[(int) x2][(int)y2].get_x(), matrix[(int) x2][(int)y2].get_y());
    cords.push_back({{x1, y1}, {x2, y2}});
    steps*=1.5;
    draw(o, t);
 }