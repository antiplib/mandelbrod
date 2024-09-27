//
// Created by Владислав Отвагин on 14.09.2024.
//

#ifndef COMPLEX_H
#define COMPLEX_H



class complex {
public:
    complex();
    complex(double x, double y);
    complex(complex &a);
    complex(complex &&a);
    ~complex();

    double get_x();
    double get_y();

    complex operator+(const complex&a);
    complex operator*(const complex&a);
    complex operator-(const complex&a);
    complex &operator=(const complex &a);

    bool operator==(const complex &a);

    complex operator-() ;

    friend void swap(complex &a, complex &b);
    friend double abs(complex &a);

private:
    double x, y;

};





#endif //COMPLEX_H
