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
    std::pair<std::shared_ptr<Point>,std::shared_ptr<Point>> findClosestPair();
    std::pair<std::shared_ptr<Point>, std::shared_ptr<Point>> slowFindClosestPair();
    double calcDistance(std::shared_ptr<Point> a, std::shared_ptr<Point> b);

    private:
        std::pair<std::shared_ptr<Point>, std::shared_ptr<Point>> findClosestPairRecurs(std::vector<std::shared_ptr<Point>> & coords);
        std::vector<std::shared_ptr<Point>> findCenterStrip(double minDistance);
        std::pair<std::shared_ptr<Point>, std::shared_ptr<Point>> findMinDistStrip(std::vector<std::shared_ptr<Point>> & strip);
        std::pair<std::shared_ptr<Point>, std::shared_ptr<Point>> bruteForce(std::vector<std::shared_ptr<Point>> & coordinates);


        double minDistFromCenterLine;
};

#endif // !GRID_HPP