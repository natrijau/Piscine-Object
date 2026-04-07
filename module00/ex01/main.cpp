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

static float validateFloatInput(const std::string& prompt){
	float value;
	std::string input;

	while(true){
		std::cout << prompt;
		std::getline(std::cin >> std::ws, input);
		if (std::cin.eof()) {
			std::cout << "\nEOF detected (Ctrl+D), exiting..." << std::endl;
			return -1;
		}

		std::istringstream iss(input);
		char c;
		if (!(iss >> value) || iss.get(c)) {
			std::cout << "Invalid input! Please enter a valid number." << std::endl;
			continue;
		}

		if (value < 0.01f|| value > 150.0f){
			std::cout << "Invalid input! Value must be between 0.01 and 150." << std::endl;
			continue;
		}
		break;
	}
	return value;
};


static float readCoordinate(const std::string& prompt, size_t maxValue) {
	float value;
	std::string input;

	while (true) {
		std::cout << prompt;

		if (!std::getline(std::cin >> std::ws, input)){
			if (inputFailed())
				return false;
			continue;
		}
		std::istringstream iss(input);
		if (!(iss >> value) || !iss.eof()) {
            std::cout << "Invalid input! Please enter an integer." << std::endl;
            continue;
        }

		if (value < 0 || value > static_cast<int>(maxValue)){
			std::cout << "Invalid input! Value must be between 0 and " << maxValue << "." << std::endl;
			continue;
		}
		break;
	};

	return value;
}

static bool	pointRequest(Graph &graph) {
	std::string yes = "y";
	std::string input;
	while (true) {
		std::cout << std::endl << "Enter point(x,y)? (y/n): ";
		if (!std::getline(std::cin >> std::ws, input)){
			if (inputFailed())
				return false;
			continue;
		}
		std::istringstream iss(input);

		if (!(iss >> yes) || !iss.eof()) {
            std::cout << "Invalid input! Please enter y or n." << std::endl;
            continue;
        }

		yes[0] = std::tolower(yes[0]);
		if (yes != "y" && yes != "n"){
			std::cout << "Invalid input, expected 'y' or 'n'." << std::endl;
			continue;
		}

		if (yes == "y"){
			float x = readCoordinate("X: ", graph.getSize().getX());
			float y = readCoordinate("Y: ", graph.getSize().getY());

			Vector2 point = Vector2(x, y);
			graph.addVector(point);
			graph.printMap();
		}
		else
			return false;
	}
	return true;
};

static bool initGraph(){

	std::cout << "Creat new Graph" << std::endl;
	std::cout << "Choose the size of you Graph ( > 0 and < 150)\nFormat vector(width,height) :" << std::endl;

	float width = validateFloatInput("Width: ");
	if (width < 0)
		return false;
	
	float height = validateFloatInput("Height: ");
	if (height < 0)
		return false;

    Vector2 size(width, height);
    Graph graph(size);

    graph.printMap();

	std::string input;
	std::string yes = "y";
	while(true){
		if(!pointRequest(graph))
			return false;
		
		std::cout << std::endl << "Do you want exit? (y/n): ";
		if (!std::getline(std::cin >> std::ws, input)){
			if (inputFailed())
				return false;
			continue;
		}
		std::istringstream iss(input);
		if (!(iss >> yes) || !iss.eof()) {
            std::cout << "Invalid input! Please enter y or n." << std::endl;
            continue;
        }
		yes[0] = std::tolower(yes[0]);

		if (yes == "y")
			break;
		else if (yes != "n") {
			std::cout << "Invalid input, expected 'y' or 'n'." << std::endl;
			continue;
		}
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
