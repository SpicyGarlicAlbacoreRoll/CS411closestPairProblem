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
    std::pair<std::shared_ptr<Point>, std::shared_ptr<Point>> slowFindClosestPair();

    private:
        std::pair<std::shared_ptr<Point>, std::shared_ptr<Point>> bruteForceFindClosestPair(std::vector<std::shared_ptr<Point>> & coords);
        std::vector<std::shared_ptr<Point>> findCenterStrip(double minDistance);
        std::pair<std::shared_ptr<Point>, std::shared_ptr<Point>> findMinDistStrip(std::vector<std::shared_ptr<Point>> & strip);
        double calcDistance(std::shared_ptr<Point> a, std::shared_ptr<Point> b);

        double minDistFromCenterLine;
};

#endif // !GRID_HPP