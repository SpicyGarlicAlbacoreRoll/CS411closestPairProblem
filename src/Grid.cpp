#include "Grid.hpp"
#include <algorithm>
#include <cmath>

struct
{
    bool operator()(const std::shared_ptr<Point> &a, const std::shared_ptr<Point> &b)
    {
        return a->position.first < b->position.first;
    }
} sortPointsX;

struct
{
    bool operator()(const std::shared_ptr<Point> &a, const std::shared_ptr<Point> &b)
    {
        return a->position.second < b->position.second;
    }
} sortPointsY;

Grid::Grid(std::vector<std::shared_ptr<Point>> & points) : points(points) {}

Point Grid::findClosestPair()
{
    std::sort(points.begin(), points.end(), sortPointsX);
    auto leftSide = std::vector<std::shared_ptr<Point>>(points.begin(), (points.size() / 2) + points.begin());
    auto rightSide = std::vector<std::shared_ptr<Point>>((points.size() / 2) + points.begin(), points.end());


    std::cout << "left side" << std::endl;
    for(auto &coord : leftSide)
    {
        std::cout << "x: " << coord->position.first  << std::endl;
        std::cout << "y: " << coord->position.second  << std::endl;
    }

        std::cout << "right side" << std::endl;
        for(auto &coord : rightSide)
    {
        std::cout << "x: " << coord->position.first  << std::endl;
        std::cout << "y: " << coord->position.second  << std::endl;
    }

    std::cout << "\nLeft side:" << std::endl;
    auto leftSideClosestPair = bruteForceFindClosestPair(leftSide);

    std::cout << "\nRight side:" << std::endl;
    auto rightSideClosestPair = bruteForceFindClosestPair(rightSide);

    return *leftSide[0];

}

std::pair<std::shared_ptr<Point>, std::shared_ptr<Point>> Grid::bruteForceFindClosestPair(std::vector<std::shared_ptr<Point>> coords) {
    auto p1 = std::shared_ptr<Point>();
    auto p2 = std::shared_ptr<Point>();

    auto min = 1000.0;
    for(auto x = coords.begin(); x != coords.end(); x++)
    {
        for(auto y = x + 1; y != coords.end(); y++) {
            if(calcDistance(*x, *y) < min){
                min = std::min(min, calcDistance(*x, *y));
                p1 = *x;
                p2 = *y;
            }
        }
    }
    std::cout << "\nClosest Pairs..." << std::endl;
    std::cout << "\tPoint 1: \n\t\tx: " << p1->position.first << "\ty: " << p1->position.second << std::endl;
    std::cout << "\tPoint 2: \n\t\tx: " << p2->position.first << "\ty: " << p2->position.second << std::endl;
    return std::pair<std::shared_ptr<Point>, std::shared_ptr<Point>>(p1, p2);
}

double Grid::calcDistance(std::shared_ptr<Point> a, std::shared_ptr<Point> b) {
    auto x1 = a->position.first;
    auto x2 = b->position.first;
    auto y1 = a->position.second;
    auto y2 = b->position.second;
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}