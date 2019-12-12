#ifndef GRID_HPP
#define GRID_HPP 

#include "Point.hpp"
#include <iostream>
#include <vector>
#include <memory>

class Grid {
    public:
        Grid(std::vector<std::shared_ptr<Point>> & points);

    std::vector<std::shared_ptr<Point>> points;
    size_t gridSize;
    std::pair<std::shared_ptr<Point>,std::shared_ptr<Point>> findClosestPair();

    private:
        std::pair<std::shared_ptr<Point>, std::shared_ptr<Point>> bruteForceFindClosestPair(std::vector<std::shared_ptr<Point>> coords);
        double calcDistance(std::shared_ptr<Point> a, std::shared_ptr<Point> b);
};

#endif // !GRID_HPP