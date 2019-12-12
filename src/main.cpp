// #include "Point.hpp"
#include "Grid.hpp"
#include <iostream>
#include <memory>

using coords = std::pair<double, double>;
int main() {

    // auto x = coords(3, 1);
    auto a = std::make_shared<Point>(coords(3, 1));
    auto b = std::make_shared<Point>(coords(7, 1.5));
    auto e = std::make_shared<Point>(coords(3, 2));
    auto c = std::make_shared<Point>(coords(12, 1));
    auto d = std::make_shared<Point>(coords(8, 1));

    // auto points = std::vector<std::shared_ptr<Point>>(4);
    // points.push(a);
    std::vector<std::shared_ptr<Point>> points = {a, b, c, d, e};
    // points.push_back(a);
    // points.push_back(b);
    // points.push_back(c);
    // points.push_back(d);
    auto grid = std::make_unique<Grid>(points);
    auto z = grid->findClosestPair();
    // std::cout << "x: "<< a->position.first << std::endl;
    // std::cout << "y: "<< a->position.second << std:: endl;
}