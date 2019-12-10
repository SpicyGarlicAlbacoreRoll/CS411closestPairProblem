#ifndef POINT_HPP
#define POINT_HPP
#include <iostream>

class Point {
    public:
        Point(std::pair<double, double> position);
        Point();
        std::pair<double, double> position;
};

#endif // !POINT_HPP
