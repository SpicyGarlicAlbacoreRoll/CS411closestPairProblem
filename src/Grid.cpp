#include "Grid.hpp"
#include <algorithm>
#include <cmath>
#include <limits>

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

    std::cout << "Closest pair: " << std::endl;
    std::cout << "x: " << closestPair.first->position.first << "\ty: " << closestPair.first->position.second << std::endl;
    std::cout << "x: " << closestPair.second->position.first << "\ty: " << closestPair.second->position.second << std::endl;
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

    auto min = std::numeric_limits<double>::max();

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
        // std::cout << p1->position.first << "\t" << p1->position.second << std::endl;
        // std::cout << p2->position.first << "\t" << p2->position.second << std::endl;
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

    auto leftSideMinDistance = calcDistance(left.first, left.second);
    auto rightSideMinDistance = calcDistance(right.first, right.second);

    auto minDistFromCenterLine = std::min(leftSideMinDistance, rightSideMinDistance);

    auto centerStrip = findCenterStrip(minDistFromCenterLine);
    auto minCenterDistancePoints = findMinDistStrip(centerStrip);
    auto minCenterStripDistance = calcDistance(minCenterDistancePoints.first, minCenterDistancePoints.second);
    // auto minCenterPointDist = calcDistance(centerStrip);

    if(minCenterStripDistance < minDistFromCenterLine) {
        // std::cout << "from center line" << std::endl;
        // std::cout << "Distance:\t" << calcDistance(minCenterDistancePoints.first, minCenterDistancePoints.second) << std::endl;
        return minCenterDistancePoints;
    } else if (leftSideMinDistance < rightSideMinDistance)
    {
        // std::cout << "\nClosest Pairs..." << std::endl;
        // std::cout << "\tPoint 1: \n\t\tx: " << left.first->position.first << "\ty: " << left.first->position.second << std::endl;
        // std::cout << "\tPoint 2: \n\t\tx: " << left.second->position.second << "\ty: " << left.second->position.second << std::endl;
        // std::cout << "Distance:\t" << calcDistance(left.first, left.second) << std::endl;
        return left;
    }
    else
    {
        // std::cout << "\nClosest Pairs..." << std::endl;
        // std::cout << "\tPoint 1: \n\t\tx: " << right.first->position.first << "\ty: " << right.first->position.second << std::endl;
        // std::cout << "\tPoint 2: \n\t\tx: " << right.second->position.second << "\ty: " << right.second->position.second << std::endl;
                // std::cout << "Distance:\t" << calcDistance(right.first, right.second) << std::endl;
        return right;
    }

    // return std::pair<std::shared_ptr<Point>, std::shared_ptr<Point>>(p1, p2);
}


std::vector<std::shared_ptr<Point>> Grid::findCenterStrip(double minDistance) {
    auto strip = std::vector<std::shared_ptr<Point>>();
    auto end = points.back();
    auto beg = points.front();

    //get middle value of range
    auto numericCenter = beg->position.first + ((end->position.first - beg->position.first) / 2);

    auto center = (points[points.size() / 2]);
    auto centerX = center->position.first;
    auto centerY = center->position.second;
    // auto middle = points.begin() + (points.size() / 2);
    for(auto point : points)
    {
        // if(abs(point->position.first - minDistance) < (points[points.size() / 2]->position.first)) {

        if(abs(point->position.first) < numericCenter + minDistance && abs(point->position.first) > numericCenter - minDistance ) {
            strip.push_back(point);
        }
    }

    // std::cout << "center line:" << std::endl;
    // std::cout << "\tx: " << numericCenter << std::endl;
    // for(auto point : strip)
    // {
    //     std::cout << point->position.first << std::endl;
    // }

    // std::sort(strip.begin(), strip.end(), sortPointsY);
    // for(auto point : strip)
    // {
    //     std::cout << point->position.first << std::endl;
    // }
    return points;

}

std::pair<std::shared_ptr<Point>, std::shared_ptr<Point>> Grid::findMinDistStrip(std::vector<std::shared_ptr<Point>> strip) {

        auto min = std::numeric_limits<double>::max();
        auto p1 = std::shared_ptr<Point>();
        auto p2 = std::shared_ptr<Point>();
        
        for (auto x = strip.begin(); x != strip.end(); x++)
        {
            for (auto y = x + 1; y != strip.end(); y++)
            {
                if (calcDistance(*x, *y) < min)
                {
                    min = calcDistance(*x, *y);
                    p1 = *x;
                    p2 = *y;
                }
            }
        }

        // std::cout << p1->position.first << "\t" << p1->position.second << std::endl;
        // std::cout << p2->position.first << "\t" << p2->position.second << std::endl;
        return std::pair<std::shared_ptr<Point>, std::shared_ptr<Point>>(p1, p2);
}

double Grid::calcDistance(std::shared_ptr<Point> a, std::shared_ptr<Point> b)
{
    auto x1 = a->position.first;
    auto x2 = b->position.first;
    auto y1 = a->position.second;
    auto y2 = b->position.second;
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}




std::pair<std::shared_ptr<Point>, std::shared_ptr<Point>> Grid::slowFindClosestPair() {
    std::sort(points.begin(), points.end(), sortPointsX);
      auto p1 = std::shared_ptr<Point>();
    auto p2 = std::shared_ptr<Point>();
    std::pair<std::shared_ptr<Point>, std::shared_ptr<Point>> left;
    std::pair<std::shared_ptr<Point>, std::shared_ptr<Point>> right;

    auto min = std::numeric_limits<double>::max();

        for (auto x = points.begin(); x != points.end(); x++)
        {
            for (auto y = x + 1; y != points.end(); y++)
            {
                if (calcDistance(*x, *y) < min)
                {
                    min = calcDistance(*x, *y);
                    p1 = *x;
                    p2 = *y;
                }
            }
        }
        // std::cout << p1->position.first << "\t" << p1->position.second << std::endl;
        // std::cout << p2->position.first << "\t" << p2->position.second << std::endl;

        std::cout << "Closest pair: " << std::endl;
        std::cout << "x: " << p1->position.first << "\ty: " << p1->position.second << std::endl;
        std::cout << "x: " << p2->position.first << "\ty: " << p2->position.second << std::endl;

        return std::pair<std::shared_ptr<Point>, std::shared_ptr<Point>>(p1, p2);
}