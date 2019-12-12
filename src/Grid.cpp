#include "Grid.hpp"
#include <algorithm>
#include <cmath>
#include <limits>
#include <chrono>
using Clock = std::chrono::high_resolution_clock;
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

    auto closestPair = bruteForceFindClosestPair(points);
    // auto minLRdistance = calcDistance(closestPair.first, closestPair.second);
    

    // auto centerStrip = findCenterStrip(minDistFromCenterLine);
    // auto minCenterDistancePoints = findMinDistStrip(centerStrip);
    // auto minCenterStripDistance = calcDistance(minCenterDistancePoints.first, minCenterDistancePoints.second);

    // std::cout << "min left right distance:\t" << minLRdistance << std::endl;
    // std::cout << "center strip distance:  \t" << minCenterStripDistance << std::endl;

    // if (minCenterStripDistance < minLRdistance)
    // {
    //     std::cout << "Closest pair: (from centerline)" << std::endl;
    //     std::cout << "x: " << minCenterDistancePoints.first->position.first << "\ty: " << minCenterDistancePoints.first->position.second << std::endl;
    //     std::cout << "x: " << minCenterDistancePoints.second->position.first << "\ty: " << minCenterDistancePoints.second->position.second << std::endl;
    //     std::cout << "Min distance:\t" << calcDistance(closestPair.first, closestPair.second) << std::endl;
    //     return minCenterDistancePoints;
    // }
    std::cout << "Closest pair: " << std::endl;
    std::cout << "x: " << closestPair.first->position.first << "\ty: " << closestPair.first->position.second << std::endl;
    std::cout << "x: " << closestPair.second->position.first << "\ty: " << closestPair.second->position.second << std::endl;
    std::cout << "Min distance:\t" << calcDistance(closestPair.first, closestPair.second) << std::endl;
    return closestPair;
}

std::pair<std::shared_ptr<Point>, std::shared_ptr<Point>> Grid::bruteForceFindClosestPair(std::vector<std::shared_ptr<Point>> &coords)
{

    std::pair<std::shared_ptr<Point>, std::shared_ptr<Point>> left;
    std::pair<std::shared_ptr<Point>, std::shared_ptr<Point>> right;

    if (coords.size() <= 3)
    {
        auto min = std::numeric_limits<double>::max();
        auto p1 = std::shared_ptr<Point>();
        auto p2 = std::shared_ptr<Point>();
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
        return std::pair<std::shared_ptr<Point>, std::shared_ptr<Point>>(p1, p2);
    }

        //recursive call
        auto middle = coords.begin() + (coords.size() / 2);
        auto leftSide = std::vector<std::shared_ptr<Point>>(coords.begin(), middle);
        auto rightSide = std::vector<std::shared_ptr<Point>>(middle, coords.end());

        left = bruteForceFindClosestPair(leftSide);
        right = bruteForceFindClosestPair(rightSide);

    auto leftSideMinDistance = calcDistance(left.first, left.second);
    auto rightSideMinDistance = calcDistance(right.first, right.second);

    minDistFromCenterLine = std::min(leftSideMinDistance, rightSideMinDistance);

    auto strip = std::vector<std::shared_ptr<Point>>();
    auto midPoint = coords[(coords.size() / 2)];
    for (auto point: coords) {
        if(abs(point->position.first - midPoint->position.first) < minDistFromCenterLine) {
            strip.push_back(point);
        }
    }
    // auto centerStrip = findCenterStrip(minDistFromCenterLine);

    auto closestCenterPair = findMinDistStrip(strip);
    auto centerPairDist = calcDistance(closestCenterPair.first, closestCenterPair.second);

    if(centerPairDist < leftSideMinDistance && centerPairDist < rightSideMinDistance) {
        return closestCenterPair;
    }
    else if (leftSideMinDistance < rightSideMinDistance) {
        return left;
    }
    else {
        return right;
    }

    // return std::pair<std::shared_ptr<Point>, std::shared_ptr<Point>>(p1, p2);
}

std::vector<std::shared_ptr<Point>> Grid::findCenterStrip(double minDistance)
{

    auto strip = std::vector<std::shared_ptr<Point>>();
    auto end = points.back();
    auto beg = points.front();

    //get middle value of range
    auto centerLine = beg->position.first + ((end->position.first - beg->position.first) / 2);
    auto center = points[points.size()/2]->position.first;
    // auto middle = points.begin() + (points.size() / 2);
    for (auto point : points)
    {
        // if (point->position.first < center + minDistance && point->position.first > center - minDistance)
        if(point->position.first > minDistance - center && point->position.first < minDistance + center)
        {
            strip.push_back(point);
        }
    }

    return strip;
}

std::pair<std::shared_ptr<Point>, std::shared_ptr<Point>> Grid::findMinDistStrip(std::vector<std::shared_ptr<Point>> &strip)
{

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

std::pair<std::shared_ptr<Point>, std::shared_ptr<Point>> Grid::slowFindClosestPair()
{
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
    std::cout << "Min distance:\t" << calcDistance(p1, p2) << std::endl;
    return std::pair<std::shared_ptr<Point>, std::shared_ptr<Point>>(p1, p2);
}