//
// Created by Владислав Отвагин on 14.09.2024.
//

#include "complex.h"
#include <utility>

complex::complex() = default;

complex::complex(double x, double y) {
    this->x = x;
    this->y = y;
}

complex::complex(complex&& a) {
    this->x = std::exchange(a.x, x);
    this->y = std::exchange(a.y, y);
}

complex::complex(complex &a) {
    this->x = a.x;
    this->y = a.y;
}

complex::~complex() = default;

double complex::get_x() {
    return this->x;
}

double complex::get_y() {
    return this->y;
}

complex complex::operator*(const complex &first) {
    complex copy(0, 0);
    copy.x = first.x*x - first.y*y;
    copy.y = first.x*y + first.y*x;
    return copy;
}

complex complex::operator+(const complex &a) {
    complex c(this->x + a.x, this->y + a.y);
    return c;
}

complex complex::operator-(const complex &a) {
    complex c(this->x - a.x, this->y - a.y);
    return c;
}

complex &complex::operator=(const complex &a) {
    this->x = a.x;
    this->y = a.y;
    return *this;
}

bool complex::operator==(const complex &a) {
    return (((this->x == a.x) && (this->y == a.y)) ? true : false);
}


complex complex::operator-() {
    complex c(-this->x, -this->y);
    return c;
}


void swap(complex &a, complex &b) {
    complex t = std::move(a);
    a = std::move(b);
    b = std::move(t);
}

double abs(complex &a) {
    double c(a.get_x()*a.get_x() + a.get_y()*a.get_y());
    return c;
}
