// #include "Point.hpp"
#include "Grid.hpp"
#include <iostream>
#include <memory>
#include <random>
#include <chrono>
using Clock=std::chrono::high_resolution_clock;
using coords = std::pair<double, double>;

struct
{
    bool operator()(const std::shared_ptr<Point> &a, const std::shared_ptr<Point> &b)
    {
        return a->position.first < b->position.first;
    }
} sortPoints;

std::vector<std::shared_ptr<Point>> generateRandomPoints(int min, int max, int size) {
    // std::default_random_engine generator;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(min, max);
    // std::uniform_real_distribution<double> distribution(double, double);

    auto randPoints = std::vector<std::shared_ptr<Point>>(size);
    for(int i = 0; i < size; i++ ) {
        auto xPos = dis(gen);
        auto yPos = dis(gen);
        auto pos = std::make_shared<Point>(coords(xPos, yPos));
        randPoints[i] = pos;

    }

    return randPoints;
}

int main() {

    int max = 150;
    int min = -max;
    int size = 1000;

    std::cout << "creating points...\n" << std::endl;
    auto randPoints = generateRandomPoints(min, max, size);


    std::cout << "Finding the closest pair out of " << size << " points..." << std::endl;
    std::sort(randPoints.begin(), randPoints.end(), sortPoints);

    auto grid = std::make_unique<Grid>(randPoints);

    std::cout << "With divide and conquer solution" << std::endl;
    auto timeBegin = Clock::now();
    auto z = grid->findClosestPair();
    auto timeEnd = Clock::now();

    auto divAndConquerTime = std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeBegin).count();

    std::cout << "Divide and Conquer Time:\n" << divAndConquerTime << " milliseconds\n" << std::endl;

    auto gridBruteForce = std::make_unique<Grid>(randPoints);

    std::cout << "Finding the closest pair out of " << size << " points..." << std::endl;
    std::cout << "With brute force (for reference)" << std::endl;
    timeBegin = Clock::now();
    auto y = gridBruteForce->slowFindClosestPair();
    timeEnd = Clock::now();

    auto bruteForceTime = std::chrono::duration_cast<std::chrono::seconds>(timeEnd - timeBegin).count();


    std::cout << "Brute Force Time:\n" << bruteForceTime << " seconds...\n" << std::endl;
    // std::cout << "x: "<< a->position.first << std::endl;
    // std::cout << "y: "<< a->position.second << std:: endl;
}

