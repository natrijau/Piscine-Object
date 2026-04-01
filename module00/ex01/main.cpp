#include	"includes/Vector2.hpp"
#include	"includes/Graph.hpp"
#include 	<iostream>

static bool inputFailed() {
	if (std::cin.eof()) {
		std::cout << "\nEOF detected (Ctrl+D), exiting..." << std::endl;
		return true;
	}
	std::cin.clear();
	std::cin.ignore(10000, '\n');
	return false;
};

static bool initGraph(){

	std::cout << "Creat new Graph" << std::endl;
	std::cout << "Choose the size of you Graph ( > 0 and < Max.size_t)" << std::endl;
	size_t size;

	while (!(std::cin >> size)) {
		if (inputFailed())
			return false;
		std::cout << "Invalid size, try again: ";
		continue;
	}
	std::cout << "You graph !!" << std::endl;
	Graph graph(size);
	graph.printMap();
	graph.saveAsPPM("graph.png", size);

	std::cout << "Now choose points (x, y)" << std::endl;
	float x;
	float y;
	char yes = 'y';

	while(yes == 'y'){
		std::cout << "x: ";
		if (!(std::cin >> x)) {
			if (inputFailed())
				return false;
			std::cout << "Invalid input!" << std::endl;
			continue;
		}

		std::cout << "y: ";
		if (!(std::cin >> y)) {
			if (inputFailed())
				return false;			
			std::cout << "Invalid input!" << std::endl;
			continue;
		}

		if (x < 0 || y < 0 || x > size || y > size) {
			std::cout << "Invalid point (out of graph)" << std::endl;
			continue;
		}

		graph.addVector(new Vector2(x, y));
		graph.saveAsPPM("graph.png", size);
		graph.printMap();
		std::cout << "Add another point? (y/n): ";
		if (!(std::cin >> yes)) 
			if (inputFailed())
				return false;
	}
	return false;
};

int main(){

	bool needVector = true;
	while(needVector){
		needVector = initGraph();
	}
	return (0);
}
