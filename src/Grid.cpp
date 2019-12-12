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

Grid::Grid(std::vector<std::shared_ptr<Point>> &points) : points(points) {}

std::pair<std::shared_ptr<Point>, std::shared_ptr<Point>> Grid::findClosestPair()
{
    std::sort(points.begin(), points.end(), sortPointsX);
    // auto leftSide = std::vector<std::shared_ptr<Point>>(points.begin(), (points.size() / 2) + points.begin());
    // auto rightSide = std::vector<std::shared_ptr<Point>>((points.size() / 2) + points.begin(), points.end());

    // std::cout << "left side" << std::endl;
    // for (auto &coord : leftSide)
    // {
    //     std::cout << "x: " << coord->position.first << std::endl;
    //     std::cout << "y: " << coord->position.second << std::endl;
    // }

    // std::cout << "right side" << std::endl;
    // for (auto &coord : rightSide)
    // {
    //     std::cout << "x: " << coord->position.first << std::endl;
    //     std::cout << "y: " << coord->position.second << std::endl;
    // }

    // std::cout << "\nLeft side:" << std::endl;
    // auto leftSideClosestPair = bruteForceFindClosestPair(leftSide);

    // std::cout << "\nRight side:" << std::endl;
    // auto rightSideClosestPair = bruteForceFindClosestPair(rightSide);

    auto closestPair = bruteForceFindClosestPair(points);

    std::cout << "Final closest pair: " << std::endl;
    std::cout << "x: " << closestPair.first->position.first << "\ty: " << closestPair.first->position.second << std::endl;
    std::cout << "x: " << closestPair.second->position.second << "\ty: " << closestPair.second->position.second << std::endl;
    return closestPair;
    // auto leftSideDistance = calcDistance(leftSideClosestPair.first, leftSideClosestPair.second);
    // auto rightSideDistance = calcDistance(rightSideClosestPair.first, rightSideClosestPair.second);

    // if (leftSideDistance <= rightSideDistance)
    // {
    //     std::cout << "Left side had closest pair, which is:" << std::endl;
    //     std::cout << "x: " << leftSideClosestPair.first->position.first << "\ty: " << leftSideClosestPair.first->position.second << std::endl;
    //     std::cout << "x: " << leftSideClosestPair.second->position.second << "\ty: " << leftSideClosestPair.second->position.second << std::endl;
    //     return leftSideClosestPair;
    // }
    // else
    // {
    //     std::cout << "Right side had closest pair, which is:" << std::endl;
    //     std::cout << "x: " << rightSideClosestPair.first->position.first << "\ty: " << rightSideClosestPair.first->position.second << std::endl;
    //     std::cout << "x: " << rightSideClosestPair.second->position.second << "\ty: " << rightSideClosestPair.second->position.second << std::endl;
    //     return rightSideClosestPair;
    // }
}

std::pair<std::shared_ptr<Point>, std::shared_ptr<Point>> Grid::bruteForceFindClosestPair(std::vector<std::shared_ptr<Point>> coords)
{
    auto p1 = std::shared_ptr<Point>();
    auto p2 = std::shared_ptr<Point>();
    std::pair<std::shared_ptr<Point>, std::shared_ptr<Point>> left;
    std::pair<std::shared_ptr<Point>, std::shared_ptr<Point>> right;

    auto min = 1000.0;

    if (coords.size() <= 3)
    {
        for (auto x = coords.begin(); x != coords.end(); x++)
        {
            for (auto y = x + 1; y != coords.end(); y++)
            {
                if (calcDistance(*x, *y) < min)
                {
                    min = calcDistance(*x, *y);
                    p1 = *x;
                    p2 = *y;
                }
            }
        }
        std::cout << p1->position.first << "\t" << p1->position.second << std::endl;
        std::cout << p2->position.first << "\t" << p2->position.second << std::endl;
        return std::pair<std::shared_ptr<Point>, std::shared_ptr<Point>>(p1, p2);
    }
    else
    {

        //recursive call
        auto middle = coords.begin() + (coords.size() / 2);
        auto leftSide = std::vector<std::shared_ptr<Point>>(coords.begin(), middle);
        auto rightSide = std::vector<std::shared_ptr<Point>>(middle, coords.end());
        left = bruteForceFindClosestPair(leftSide);
        right = bruteForceFindClosestPair(rightSide);
    }

    // for (auto x = coords.begin(); x != coords.end(); x++)
    // {
    //     for (auto y = x + 1; y != coords.end(); y++)
    //     {
    //         if (calcDistance(*x, *y) < min)
    //         {
    //             min = std::min(min, calcDistance(*x, *y));
    //             p1 = *x;
    //             p2 = *y;
    //         }
    //     }
    // }

    if (calcDistance(left.first, left.second) <= calcDistance(right.first, right.second))
    {
        std::cout << "\nClosest Pairs..." << std::endl;
        std::cout << "\tPoint 1: \n\t\tx: " << left.first->position.first << "\ty: " << left.first->position.second << std::endl;
        std::cout << "\tPoint 2: \n\t\tx: " << left.second->position.second << "\ty: " << left.second->position.second << std::endl;
        std::cout << "Distance:\t" << calcDistance(left.first, left.second) << std::endl;
        return left;
    }
    else
    {
        std::cout << "\nClosest Pairs..." << std::endl;
        std::cout << "\tPoint 1: \n\t\tx: " << right.first->position.first << "\ty: " << right.first->position.second << std::endl;
        std::cout << "\tPoint 2: \n\t\tx: " << right.second->position.second << "\ty: " << right.second->position.second << std::endl;
                std::cout << "Distance:\t" << calcDistance(right.first, right.second) << std::endl;
        return right;
    }

    // return std::pair<std::shared_ptr<Point>, std::shared_ptr<Point>>(p1, p2);
}

double Grid::calcDistance(std::shared_ptr<Point> a, std::shared_ptr<Point> b)
{
    auto x1 = a->position.first;
    auto x2 = b->position.first;
    auto y1 = a->position.second;
    auto y2 = b->position.second;
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}