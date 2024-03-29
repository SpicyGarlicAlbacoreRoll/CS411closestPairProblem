#include "Grid.hpp"
#include <algorithm>
#include <cmath>
#include <limits>
using std::pair;
using std::abs;
using std::shared_ptr;
using std::vector;

Grid::Grid(vector<shared_ptr<Point>> &points) : points(points) {}

pair<shared_ptr<Point>, shared_ptr<Point>> Grid::findClosestPair()
{
	return findClosestPairRecurse(points);   
}

pair<shared_ptr<Point>, shared_ptr<Point>> Grid::findClosestPairRecurse(vector<shared_ptr<Point>> &coords)
{

    if (coords.size() <= 3)
    {
        auto min = std::numeric_limits<double>::max();
        auto p1 = shared_ptr<Point>();
        auto p2 = shared_ptr<Point>();
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
        return pair<shared_ptr<Point>, shared_ptr<Point>>(p1, p2);
    }

	// Gets ranges for first and second halves of the points
    auto middle = coords.begin() + (coords.size() / 2);
    auto leftSide = vector<shared_ptr<Point>>(coords.begin(), middle);
    auto rightSide = vector<shared_ptr<Point>>(middle, coords.end());

    // recursive call returing the closest pair on the left and right numbers
    auto left = findClosestPairRecurse(leftSide);
    auto right = findClosestPairRecurse(rightSide);

    auto leftSideMinDistance = calcDistance(left.first, left.second);
    auto rightSideMinDistance = calcDistance(right.first, right.second);

    // The distance from our center line that will be the cut off point
    // for points to include in our center strip.
    auto minDistFromCenterLine = std::min(leftSideMinDistance, rightSideMinDistance);

    // Will contain the points that are closer to the center line than the length
    // of our minimum distance calculated above
    auto strip = vector<shared_ptr<Point>>();
    auto midPoint = coords[(coords.size() / 2)];
    for (auto point : coords)
    {
        if (abs(point->position.first - midPoint->position.first) < minDistFromCenterLine)
        {
            strip.push_back(point);
        }
    }

    //If our strip is only a single point, return either the left or right side
    if (strip.size() < 2)
    {
        if (leftSideMinDistance < rightSideMinDistance)
        {
            return left;
        }
        else
        {
            return right;
        }
    }
    
    // Brute force find closest pair along center strip
    auto closestCenterPair = bruteForce(strip);

    // The distance between the closest pair of points
    auto centerPairDist = calcDistance(closestCenterPair.first, closestCenterPair.second);

    // if the closest points we found in the center strip are closer
    // than the one we found on either side recursively, we return that pair.
    // Otherwise we return the shortest of the left or the right
    if (centerPairDist < minDistFromCenterLine)
    {
        return closestCenterPair;
    }
    else if (leftSideMinDistance < rightSideMinDistance)
    {
        return left;
    }
    else
    {
        return right;
    }
}

// Helper function for determining the distance between 2-Dimensional points
double Grid::calcDistance(shared_ptr<Point> a, shared_ptr<Point> b)
{
    auto x1 = a->position.first;
    auto x2 = b->position.first;
    auto y1 = a->position.second;
    auto y2 = b->position.second;

    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

// brute force function for finding the closest pair of points
pair<shared_ptr<Point>, shared_ptr<Point>> Grid::bruteForce(vector<shared_ptr<Point>> &coordinates)
{

    auto p1 = shared_ptr<Point>();
    auto p2 = shared_ptr<Point>();

    auto min = std::numeric_limits<double>::max();

    for (auto x = coordinates.begin(); x != coordinates.end(); x++)
    {
        for (auto y = x + 1; y != coordinates.end(); y++)
        {
            if (calcDistance(*x, *y) < min)
            {
                min = calcDistance(*x, *y);
                p1 = *x;
                p2 = *y;
            }
        }
    }

    return pair<shared_ptr<Point>, shared_ptr<Point>>(p1, p2);
}

// The brute force solution to finding the closests pair
pair<shared_ptr<Point>, shared_ptr<Point>> Grid::slowFindClosestPair()
{
    auto closestPair = bruteForce(points);
    return closestPair;
}

void Grid::printStats(std::pair<std::shared_ptr<Point>, std::shared_ptr<Point>> & closestPair) {
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "\t" << "Closest pair: " << std::endl << std::endl;
	std::cout << "\t\t" << "x: " << closestPair.first->position.first << "\ty: " << closestPair.first->position.second << std::endl;
	std::cout << "\t\t" << "x: " << closestPair.second->position.first << "\ty: " << closestPair.second->position.second << std::endl << std::endl;
	std::cout << "\t" << "Distance apart:\n\n\t\t" << calcDistance(closestPair.first, closestPair.second) << std::endl << std::endl;
}