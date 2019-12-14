// #include "Point.hpp"
#include "Grid.hpp"
#include <iostream>
#include <memory>
#include <algorithm>
#include <random>
#include <chrono>

using Clock=std::chrono::high_resolution_clock;
using coords = std::pair<double, double>;

// struct used for sorting points by x coordinates
struct
{
    bool operator()(const std::shared_ptr<Point> &a, const std::shared_ptr<Point> &b)
    {
        return a->position.first < b->position.first;
    }
} sortPoints;


// Generates random points for data sets
std::vector<std::shared_ptr<Point>> generateRandomPoints(int min, int max, int size) {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(min, max);

    auto randPoints = std::vector<std::shared_ptr<Point>>(size);

	// Creates randomly placed point

    for(auto i = 0; i != randPoints.size(); i++ ) {
        randPoints[i] = std::make_shared<Point>(coords(dis(gen), dis(gen)));
    }

    return randPoints;
} // generateRandomPoints(int min, int max, int size)


int main() {

	// Values for randomly gerneated vector to be intialized with
    int maxValue = 10000;
    int minValue = -maxValue;
    int size = 5000;

    std::cout << "creating points...\n" << std::endl;
    auto randPoints = generateRandomPoints(minValue, maxValue, size);
    
    //Pre-sorting data before passing off to two different closest pair solutions
    std::sort(randPoints.begin(), randPoints.end(), sortPoints);


    std::cout << "Finding the closest pair out of " << size << " points..." << std::endl;
	std::cout << std::endl << "******************************************************************" << std::endl;


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Grid used for finding closest pair via divide and conquer solution
    auto grid = std::make_unique<Grid>(randPoints);

    std::cout << "With divide and conquer solution" << std::endl;
    auto timeBegin = Clock::now();
    auto closestPair = grid->findClosestPair();
    auto timeEnd = Clock::now();
   auto divAndConquerTime = std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeBegin).count();

    grid->printStats(closestPair);
    std::cout << "\t" << "Divide and Conquer Time:\n\n\t\t" << divAndConquerTime << " milliseconds\n" << std::endl;
    std::cout << "******************************************************************" << std::endl;



	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Grid used for finding closest pair via brute force solution
    auto gridBruteForce = std::make_unique<Grid>(randPoints);

    std::cout << "With brute force (for reference)" << std::endl;
    timeBegin = Clock::now();
    closestPair = gridBruteForce->slowFindClosestPair();
    timeEnd = Clock::now();
    auto bruteForceTime = std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeBegin).count();
    
	gridBruteForce->printStats(closestPair);
    std::cout << "\t" <<  "Brute Force Time:\n\n\t\t" << bruteForceTime << " milliseconds\n" << std::endl;
    std::cout << "******************************************************************" << std::endl;
    std::cout << std::endl;


    return 0;
} // main()