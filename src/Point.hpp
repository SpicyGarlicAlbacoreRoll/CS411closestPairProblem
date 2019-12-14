#ifndef POINT_HPP
#define POINT_HPP
#include <iostream>

class Point {
    public:
        Point(std::pair<double, double> position);
        Point();
        std::pair<double, double> position;
		bool operator == (const std::shared_ptr<Point> lhs) const {
			return (lhs->position.first == this->position.first && lhs->position.second == this->position.second);
		}
};

#endif // !POINT_HPP
