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

    

    auto centerStrip = findCenterStrip(minDistFromCenterLine);
    auto minCenterDistancePoints = findMinDistStrip(centerStrip);
    auto minCenterStripDistance = calcDistance(minCenterDistancePoints.first, minCenterDistancePoints.second);


    if (minCenterStripDistance < calcDistance(closestPair.first, closestPair.second))
    {
        std::cout << "Closest pair: " << std::endl;
        std::cout << "x: " << minCenterDistancePoints.first->position.first << "\ty: " << minCenterDistancePoints.first->position.second << std::endl;
        std::cout << "x: " << minCenterDistancePoints.second->position.first << "\ty: " << minCenterDistancePoints.second->position.second << std::endl;
        return minCenterDistancePoints;
    }
    std::cout << "Closest pair: " << std::endl;
    std::cout << "x: " << closestPair.first->position.first << "\ty: " << closestPair.first->position.second << std::endl;
    std::cout << "x: " << closestPair.second->position.first << "\ty: " << closestPair.second->position.second << std::endl;
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
        // auto timeBegin = Clock::now();
        // auto timeEnd = Clock::now();
        // auto divAndConquerTime = std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeBegin).count();

        // std::cout << divAndConquerTime << std::endl;
    }

    auto leftSideMinDistance = calcDistance(left.first, left.second);
    auto rightSideMinDistance = calcDistance(right.first, right.second);

    minDistFromCenterLine = std::min(leftSideMinDistance, rightSideMinDistance);

    // auto centerStrip = findCenterStrip(minDistFromCenterLine);
    // auto minCenterDistancePoints = findMinDistStrip(centerStrip);
    // auto minCenterStripDistance = calcDistance(minCenterDistancePoints.first, minCenterDistancePoints.second);
    // // auto minCenterPointDist = calcDistance(centerStrip);

    // if(minCenterStripDistance < minDistFromCenterLine) {
    //     // std::cout << "from center line" << std::endl;
    //     // std::cout << "Distance:\t" << calcDistance(minCenterDistancePoints.first, minCenterDistancePoints.second) << std::endl;
    //     return minCenterDistancePoints;
    // } else if
    if (leftSideMinDistance < rightSideMinDistance)
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

std::vector<std::shared_ptr<Point>> Grid::findCenterStrip(double minDistance)
{

    auto strip = std::vector<std::shared_ptr<Point>>();
    auto end = points.back();
    auto beg = points.front();

    //get middle value of range
    auto centerLine = beg->position.first + ((end->position.first - beg->position.first) / 2);

    // auto middle = points.begin() + (points.size() / 2);
    for (auto point : points)
    {
        if (abs(point->position.first) < centerLine + minDistance && abs(point->position.first) > centerLine - minDistance)
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

    return std::pair<std::shared_ptr<Point>, std::shared_ptr<Point>>(p1, p2);
}