// #include "Point.hpp"
#include "Grid.hpp"
#include <iostream>
#include <memory>
#include <random>
#include <chrono>
using Clock=std::chrono::high_resolution_clock;
using coords = std::pair<double, double>;

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

    
    // auto x = coords(3, 1);
    auto r = std::make_shared<Point>(coords(1, 1));
    auto a = std::make_shared<Point>(coords(3, 1));
    auto u = std::make_shared<Point>(coords(7.3, 1.25));
    auto p = std::make_shared<Point>(coords(7.4, 1.25));
    auto b = std::make_shared<Point>(coords(7.6, 1.25));
    auto e = std::make_shared<Point>(coords(3, 2));
    auto c = std::make_shared<Point>(coords(12, 1));
    auto d = std::make_shared<Point>(coords(8, 1));

    // auto points = std::vector<std::shared_ptr<Point>>(4);
    // points.push(a);
    std::vector<std::shared_ptr<Point>> points = {a, b, c, d, e, p, r, u};

    int max = 100;
    int min = -max;
    int size = 200;

    auto randPoints = generateRandomPoints(min, max, size);
    // points.push_back(a);
    // points.push_back(b);
    // points.push_back(c);
    // points.push_back(d);
    // auto grid = std::make_unique<Grid>(points);
    auto grid = std::make_unique<Grid>(randPoints);

    auto timeBegin = Clock::now();
    auto z = grid->findClosestPair();
    auto timeEnd = Clock::now();

    auto divAndConquerTime = std::chrono::duration_cast<std::chrono::nanoseconds>(timeEnd - timeBegin).count();

    auto gridBruteForce = std::make_unique<Grid>(randPoints);

    timeBegin = Clock::now();
    auto y = gridBruteForce->slowFindClosestPair();
    timeEnd = Clock::now();

    auto bruteForceTime = std::chrono::duration_cast<std::chrono::nanoseconds>(timeEnd - timeBegin).count();

    std::cout << "Divide and Conquer Time:\n" << divAndConquerTime << std::endl;
    std::cout << "Brute Force Time:\n" << bruteForceTime << std::endl;
    // std::cout << "x: "<< a->position.first << std::endl;
    // std::cout << "y: "<< a->position.second << std:: endl;
}

