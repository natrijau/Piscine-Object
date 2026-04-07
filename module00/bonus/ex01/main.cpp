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

static float readCoordinate(const std::string& prompt, size_t maxValue) {
	float value;
	std::string input;

	while (true) {
		std::cout << prompt;

		if (!std::getline(std::cin >> std::ws, input))
			throw std::runtime_error("Input failed.");
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

static	std::pair<Vector2, Vector2> addPair(Graph &graph) {

	float startX = readCoordinate("startX: ", graph.getSize());
	float startY = readCoordinate("startY: ", graph.getSize());

	float endX = readCoordinate("endX: ", graph.getSize());
	float endY = readCoordinate("endY: ", graph.getSize());

	Vector2 start = Vector2(startX, startY);
	Vector2 end = Vector2(endX, endY);

	return std::pair<Vector2, Vector2>(start, end);
};

static void lineRequest(Graph &graph){
	char yes = 'y';

	while(true) {
		std::cout << "Add line [ startPoint(x,y), endPoint(x,y) ] ? (y/n): ";
		std::cin >> yes;

		if (yes != 'y' && yes != 'n') {
			std::cout << "Invalid input, expected 'y' or 'n'." << std::endl;
			continue;
		}

		yes = tolower(yes);
		if(yes == 'y'){
			//// je veux free dans le cas ou CTR+C est tapé pendant la saisie des coordonnées
			if (inputFailed())
				return;
			std::pair<Vector2, Vector2> line = addPair(graph);
			graph.addLine(line.first, line.second);
			//graph.saveAsPPM("graph.png", graph.getSize());
			graph.printMap();
		}
		else
			break;
	};
};

static void pointRequest(Graph &graph) {
	char yes = 'y';
	while (true) {
		std::cout << "Enter point(x,y)? (y/n): ";
		std::cin >> yes;

		if (inputFailed())
			return;

		yes = std::tolower(yes);
		if (yes != 'y' && yes != 'n'){
			std::cout << "Invalid input, expected 'y' or 'n'." << std::endl;
			continue;
		}

		if (yes == 'y'){
			std::cin.ignore(10000, '\n');
			float x = readCoordinate("X: ", graph.getSize());
			float y = readCoordinate("Y: ", graph.getSize());

			Vector2 point = Vector2(x, y);
			graph.addVector(point);
			//graph.saveAsPPM("graph.png", graph.getSize());
			//graph.printMap();
		}
		else
			break;
	}
};

void fileRequest(Graph &graph) {
	char yes = 'y';
	while (true) {
		std::cout << "Load points from file? (y/n): ";
		std::cin >> yes;

		if (inputFailed())
			return;

		yes = std::tolower(yes);
		if (yes != 'y' && yes != 'n') {
			std::cout << "Invalid input, expected 'y' or 'n'." << std::endl;
			continue;
		}

		if (yes == 'y') {
			std::string filename;
			std::cout << "Enter filename: ";
			std::cin >> filename;

			if (inputFailed())
				return;
			if (filename.empty()) {
				std::cout << "Filename cannot be empty." << std::endl;
				continue;
			}
			if (filename.size() < 4 || filename.substr(filename.size() - 4) != ".txt") {
				std::cout << "Invalid file format! Please enter a .txt file." << std::endl;
				continue;
			}
			try {
				graph.loadFile(filename);
				graph.saveAsPPM("graph.png", graph.getSize());
				graph.printMap();
			} catch (const std::exception& e) {
				std::cerr << "Error loading file: " << e.what() << std::endl;
			}
		}
		else
			break;
	}
};

static void initGraph(){

	std::cout << "Creat new Graph" << std::endl;
	size_t size;
	char yes = 'y';

	while (true){
		std::cout << "Enter size of graph (> 0 && < 150): ";
		std::cin >> size;

		if (inputFailed())
			return;

		if (size == 0) {
			std::cout << "Invalid input! Size must be greater than 0." << std::endl;
			continue;
		}
		if (size > 150) {
			std::cout << "Size too large! Please enter a value less than or equal to 150." << std::endl;
			continue;
		}
		break;
	}

	Graph graph(size);

	while (true){
		pointRequest(graph);
		lineRequest(graph);
		fileRequest(graph);

		std::cout << "Do you want exit? (y/n): ";
		std::cin >> yes;

		if (inputFailed())
			return;

		yes = std::tolower(yes);

		if (yes == 'y')
			break;
		else if (yes != 'n') {
			std::cout << "Invalid input, expected 'y' or 'n'." << std::endl;
			continue;
		}
	}
};

int main(){

	try {
		initGraph();
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
	return (0);
}
