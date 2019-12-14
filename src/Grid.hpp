#ifndef GRID_HPP
#define GRID_HPP 

#include "Point.hpp"
#include <iostream>
#include <vector>
#include <memory>



class Grid {
    public:

		// ctor
		Grid(std::vector<std::shared_ptr<Point>> & points);

		// public member functions
		std::pair<std::shared_ptr<Point>,std::shared_ptr<Point>> findClosestPair();
		std::pair<std::shared_ptr<Point>, std::shared_ptr<Point>> slowFindClosestPair();
		double calcDistance(std::shared_ptr<Point> a, std::shared_ptr<Point> b);
		void printStats(std::pair<std::shared_ptr<Point>, std::shared_ptr<Point>> & closestPair);
    private:
		
		// private helper functions
		std::pair<std::shared_ptr<Point>, std::shared_ptr<Point>> findClosestPairRecurse(std::vector<std::shared_ptr<Point>>& coords);
		std::pair<std::shared_ptr<Point>, std::shared_ptr<Point>> bruteForce(std::vector<std::shared_ptr<Point>>& coordinates);

		//private data members
		std::vector<std::shared_ptr<Point>> points;
};

#endif // !GRID_HPP