#include	"../includes/Graph.hpp"
#include	<vector>

Graph::Graph(size_t size, std::vector<Vector2*> list) : _size(size), _list(list){
	//std::cout << "Graph created with size of " << size << "and " << std::endl;
};

Graph::Graph(size_t size): _size(size), _list(){
	//std::cout << "Graph created with size of " << size << "and null Vector2" << std::endl;
};

Graph::~Graph(){
	//for (size_t i = 0; i < _list.size(); i++)
    //	delete _list[i];
	//std::cout << "Graph deleted" << std::endl;
};

void	Graph::addVector(Vector2 *v){
	_list.push_back(v);
	//std::cout << "Graph addVector" << v << " !" << std::endl;
};

std::vector<Vector2*>	Graph::getVector() const{
	return _list;
};

//std::vector<std::string>	Graph::getTabl() const{
//	return _toPrint;
//};

size_t	Graph::getSize() const{
	return _size;
};

bool	Graph::pointVector(size_t y) const{
	for (size_t i = 0; i < _list.size(); i++){
		if (getSize() - _list[i]->getY() == y)
			return true;
	}
	return false;
};

//std::string Graph::getLineGraph(size_t y) const{
//	std::string str;

//	for(size_t i = 0; i <= getSize(); i++)
//		str += "- ";

//	size_t index;
//	for(index = 0; index <= getSize(); index++){
//		for(size_t i = 0; i < _list.size(); i++){
//			Vector2 *test = _list[i];
			
//			if( test->getX() == (getSize() - y) && test->getY() == index ){
//				str[index * 2] = 'X';
//			}
//		}
//	}
//	return str;
//};
std::string Graph::getLineGraph(size_t y) const {
	// Calcule la largeur nécessaire pour afficher les indices
	int width = 1;
	size_t maxSize = getSize();
	while (maxSize >= 10) {
		maxSize /= 10;
		width++;
	}

	std::string str;
	// Initialise la ligne avec des "-" suivis d'un espace
	for (size_t x = 0; x <= getSize(); x++)
		str += std::string(width, '-') + " ";

	// Place les "X" aux bonnes positions
	for (size_t x = 0; x <= getSize(); x++) {
		for (size_t i = 0; i < _list.size(); i++) {
			int vecX = static_cast<int>(_list[i]->getX());
			int vecY = static_cast<int>(_list[i]->getY());

			if (vecX == static_cast<int>(x) && vecY == static_cast<int>(getSize() - y)) {
				for (int k = 0; k < width; k++)
					str[x * (width + 1) + k] = 'X';
			}
		}
	}
	return str;
}

static std::string intToString(size_t n, int width) {
	std::string s;
	if (n == 0)
		s = "0";
	else {
		while (n) {
			s = char('0' + (n % 10)) + s;
			n /= 10;
		}
	}
	// Ajoute des espaces devant pour atteindre la largeur souhaitée
	while (static_cast<int>(s.length()) < width)
		s = " " + s;
	return s;
}

void Graph::printMap() const {
    std::vector<std::string> toPrint;

    // Calcule la largeur nécessaire pour afficher les indices
    int width = 1;
    size_t maxSize = getSize();
    while (maxSize >= 10) {
        maxSize /= 10;
        width++;
    }

    // En-tête : affiche les indices des colonnes
    std::string strFinal = "&" + std::string(width + 1, ' ') + std::string (width, ' ');
    for (size_t i = 0; i <= getSize(); i++) {
        std::string indexStr = intToString(i, width);
        strFinal += indexStr + " ";
    }

    // Lignes du tableau
    for (size_t y = 0; y <= getSize(); y++) {
        std::string line = "&" + std::string(width, ' ');
        std::string yIndexStr = intToString(getSize() - y, width);
        line += yIndexStr + " " + getLineGraph(y);
        toPrint.push_back(line);
    }
    toPrint.push_back(strFinal);

    // Affichage
    for (size_t i = 0; i < toPrint.size(); i++) 
        std::cout << toPrint[i] << std::endl;
};

void Graph::saveAsPPM(const std::string& filename, int scale) const {
    // Taille de l'image (en pixels)
    const unsigned width = (getSize() + 1) * scale;
    const unsigned height = (getSize() + 1) * scale;

    // Crée une image vide (3 canaux : RGB)
    std::vector<unsigned char> image;
    image.resize(width * height * 3, 255); // Fond blanc par défaut

    // Dessine la grille et les points
    for (unsigned y = 0; y < height; y++) {
        for (unsigned x = 0; x < width; x++) {
            unsigned i = 3 * width * y + 3 * x; // Index du pixel

            // Dessine les lignes de la grille
            if (x % scale == 0 || y % scale == 0)
                image[i] = image[i + 1] = image[i + 2] = 200; // Gris clair pour les lignes

            // Dessine les points (vecteurs)
            size_t gridX = x / scale;
            size_t gridY = getSize() - (y / scale);
            for (size_t vecIdx = 0; vecIdx < _list.size(); vecIdx++) {
                int vecX = static_cast<int>(_list[vecIdx]->getX());
                int vecY = static_cast<int>(_list[vecIdx]->getY());

                if (vecX == static_cast<int>(gridX) && vecY == static_cast<int>(gridY)) {
                    image[i] = 255;     // Rouge
                    image[i + 1] = 0;
                    image[i + 2] = 0;
                }
            }
        }
    }

    // Écriture du fichier PPM
    std::ofstream ofs(filename.c_str(), std::ios::binary);
    if (!ofs) {
        std::cerr << "Erreur : impossible d'ouvrir le fichier " << filename << std::endl;
        return;
    }

    // En-tête du fichier PPM
    ofs << "P6\n" << width << " " << height << "\n255\n";
    ofs.write(reinterpret_cast<const char*>(&image[0]), image.size());
}
//void	Graph::printMap() const{
//	std::vector<std::string> toPrint;
//	std::string strFinal = "&   ";

//	for (size_t i = 0; i <= getSize(); i++)
//		strFinal +=  intToString(i) + " ";
	
//	for (size_t y = 0; y <= getSize(); y++){
//		toPrint.push_back(("& " + intToString((getSize() - y))) + " " + getLineGraph(y));
//		if(y == getSize()){
//			toPrint.push_back(strFinal);
//			break;
//		}
//	}
	
//	for (size_t i = 0; i < toPrint.size(); i++)
//		std::cout << toPrint[i] << std::endl;
//};
