#include	"../includes/Graph.hpp"
#include	<vector>

std::string Graph::getLineGraph(size_t y) const {
	// Calcule la largeur nécessaire pour afficher les indices
	int width = 1;
    size_t maxX = (int)getSize().getX();
	if ((int)maxX < (int)getSize().getY())
		maxX = (int)getSize().getY();
	while (maxX >= 10){
		maxX /= 10;
		width++;
	}

	std::string line;
	// Initialise la ligne avec des "-" suivis d'un espace
	for (size_t x = 0; x <= getSize().getX(); x++)
		line += std::string(width, '-') + " ";

	for (size_t i = 0; i < _list.size(); i++){
		Vector2 vec = _list[i];
		if ((int)vec.getY() == (int)(_size.getY() - y)){
			int pos = (int)(vec.getX()) * (width + 1);
			for (int k = 0; k < width; k++)
				line[pos + k] = 'X';
		}
	}
	return line;
}

static std::string intToStringWithSpace(size_t n, int width) {
	std::string s;
	if (n == 0)
		s = "0";
	else {
		while (n){
			char digit = 48 + (n % 10);
			s = digit + s;
			n /= 10;
		}
	}

	// Ajoute taille max espace
	while (static_cast<int>(s.length()) < width)
		s = " " + s;
	return s;
}

Graph::Graph(Vector2 size): _size(size), _list(){
	//std::cout << "Graph created with size of " << size << "and null Vector2" << std::endl;
};

Graph::~Graph(){
	//for (size_t i = 0; i < _list.size(); i++)
    //	delete _list[i];
	//std::cout << "Graph deleted" << std::endl;
};

void	Graph::addVector(Vector2 v){
	if (v.getX() < 0 || v.getX() > getSize().getX() || v.getY() < 0 || v.getY() > getSize().getY()) {
		std::cout << "Vector is out of bounds and will not be added." << std::endl;
		return;
	}
	_list.push_back(v);
	//std::cout << "Graph addVector" << v << " !" << std::endl;
};

std::vector<Vector2>	Graph::getVector() const{
	return _list;
};

Vector2	Graph::getSize() const{
	return _size;
};

void Graph::printMap() const {
    std::vector<std::string> toPrint;

    // largeur max
    int width = 1;
    size_t maxX = (int)getSize().getX();
	if ((int)maxX < (int)getSize().getY())
		maxX = (int)getSize().getY();
	while (maxX >= 10){
		maxX /= 10;
		width++;
	}

    // avant chanques colonnes
    std::string strFinal = "&" + std::string(width + 1, ' ') + std::string (width, ' ');
    for (size_t i = 0; i <= getSize().getX(); i++) {
        std::string indexStr = intToStringWithSpace(i, width);
		std::cout << indexStr << std::endl;
        strFinal += indexStr + " ";
		std::cout << strFinal << std::endl;
    }

    // lignes
    for (size_t y = 0; y <= getSize().getY(); y++) {
        std::string line = "&" + std::string(width, ' ');
        std::string yIndexStr = intToStringWithSpace(getSize().getY() - y, width);
        line += yIndexStr + " " + getLineGraph(y);
        toPrint.push_back(line);
    }
    toPrint.push_back(strFinal);

	std::cout << std::endl << "Graph printMap" << std::endl;
    for (size_t i = 0; i < toPrint.size(); i++) 
        std::cout << toPrint[i] << std::endl;
};
