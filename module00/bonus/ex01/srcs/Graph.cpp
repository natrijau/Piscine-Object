#include	"../includes/Graph.hpp"
#include	<vector>

static bool validateValue(int x, int y, int maxSize) {
	if (x > maxSize || y > maxSize) {
		std::cout << "Invalid input! Value must be between 0 and " << maxSize << "." << std::endl;
		return false;
	}
	if (x < 0 || y < 0) {
		std::cout << "Invalid input! Value must be between 0 and " << maxSize << "." << std::endl;
		return false;
	}	
	return true;
};

Graph::Graph(size_t size, std::vector<Vector2> list) : _size(size), _list(list){
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

void	Graph::addVector(Vector2 v){
	_list.push_back(v);
	//std::cout << "Graph addVector" << v << " !" << std::endl;
};

void Graph::addLine(Vector2 start, Vector2 end)
{
    int x0 = static_cast<int>(start.getX());
    int y0 = static_cast<int>(start.getY());
    int x1 = static_cast<int>(end.getX());
    int y1 = static_cast<int>(end.getY());

    std::cout << "\n================= NOUVELLE LIGNE =================\n";

    std::cout << "Départ  : (" << x0 << ", " << y0 << ")\n";
    std::cout << "Arrivée : (" << x1 << ", " << y1 << ")\n";

    int dx = x1 - x0;
    if (dx < 0) dx = -dx;

    int dy = y1 - y0;
    if (dy < 0) dy = -dy;

    std::cout << "\n--- Distances ---\n";
    std::cout << "dx = " << dx << " | dy = " << dy << "\n";

    int stepX = (x0 < x1) ? 1 : (x0 > x1 ? -1 : 0);
    int stepY = (y0 < y1) ? 1 : (y0 > y1 ? -1 : 0);

    std::cout << "\n--- Directions ---\n";
    std::cout << "stepX = " << stepX << " | stepY = " << stepY << "\n";

    // erreur Bresenham classique
    int error = dx - dy;

    std::cout << "\n--- Initialisation ---\n";
    std::cout << "Erreur initiale = dx - dy = " << error << "\n";

    int step = 0;

    while (true)
    {
		if (x0 == x1 && y0 == y1)
        {
        	_list.push_back(Vector2(x0, y0));
			std::cout << "Arrivée atteinte.\n";
            break;
        }
		std::cout << "\n----------------------------------------\n";
		std::cout << "Étape " << step++ << "\n";
        std::cout << "Point ajouté : (" << x0 << ", " << y0 << ")\n";
        _list.push_back(Vector2(x0, y0));
        int e2 = error;


        // Y
		if (e2 < dx)
        {
            std::cout << "\n\t[Déplacement en Y]\n";
			std::cout << "\tCondition: " << e2 << " > " << -dx << " ✔\n\t-dx represente la distance restante en X, si e2 est plus grand que -dx\n\tcela signifie que nous sommes plus proches de la ligne que de la case suivante en X, donc on avance en Y\n";

            std::cout << "\terror = " << error << " + " << dx;
            error += dx;
            std::cout << " -> " << error << "\n";

            std::cout << "\ty0 = " << y0 << " + (" << stepY << ")";
            y0 += stepY;
            std::cout << " -> " << y0 << "\n";
        }

		// X
        if (e2 > -dy){
            std::cout << "\n\t[Déplacement en X]\n";
			std::cout << "\tCondition: " << e2 << " > " << -dy << " ✔\n\t-dy represente la distance restante en Y, si e2 est plus grand que -dy\n\tcela signifie que nous sommes plus proches de la ligne que de la case suivante en Y, donc on avance en X\n";
            std::cout << "\terror = " << error << " - " << dy;
            error -= dy;
            std::cout << " -> " << error << "\n";

            std::cout << "\tx0 = " << x0 << " + (" << stepX << ")";
            x0 += stepX;
            std::cout << " -> " << x0 << "\n";
        }

	}

    std::cout << "\n============= FIN =================\n";
}

std::vector<Vector2>	Graph::getVector() const{
	return _list;
};


size_t	Graph::getSize() const{
	return _size;
};

bool	Graph::pointVector(size_t y) const{
	for (size_t i = 0; i < _list.size(); i++){
		if (getSize() - _list[i].getY() == y)
			return true;
	}
	return false;
};

void	Graph::loadFile(const std::string& filename){
	std::ifstream file(("./files/" + filename).c_str());
	if (!file.is_open())
		throw	std::runtime_error("Cant open file");

	std::string line;
	std::vector<Vector2> tmpList;
	while(std::getline(file, line)){
		float x, y;
		std::istringstream iss(line);
		if (iss >> x >> y){
			if (!validateValue(static_cast<int>(x), static_cast<int>(y), static_cast<int>(getSize())))
				throw std::runtime_error("Invalid coordinate in file. Coordinates must be between 0 and max .");
			tmpList.push_back(Vector2(x, y));
		}
		else
			throw std::runtime_error("Invalid file format. Each line must contain two numbers.");
	};
	_list.insert(_list.end(), tmpList.begin(), tmpList.end());

	// le format du fichier doit etre :
	// x y
	file.close();
};

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
			int vecX = static_cast<int>(_list[i].getX());
			int vecY = static_cast<int>(_list[i].getY());

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

void Graph::saveAsPPM(const std::string& filename, size_t scale) const {
	if( scale < 10 )
		scale = 10;

	size_t width = (getSize() + 1) * scale;
	size_t height = (getSize() + 1) * scale;

	std::cout << "width=" << width << ", height=" << height << ", scale=" << scale << std::endl;

	std::cout << "On creer une map pour les vector2 qui constituent la ligne " << std::endl;
	// map des element de _list pour eviter de faire une boucle dans le vector2 pour chaque pixel, teste et tres lent!  surtout pour les grandes tailles de graph (100 et +) 

	std::vector<unsigned char> image(width * height * 3, 255);
	std::map<std::pair<int,int>, bool> pointsMap;
	size_t idx;
	for ( idx = 0; idx < _list.size(); ++idx) {
		int x = _list[idx].getX();
		int y = _list[idx].getY();
		pointsMap[std::make_pair(x, y)] = true;
	}

	std::cout << "Drqwing points in the image..." << std::endl;
	for (size_t y = 0; y < height; ++y) {
		for (size_t x = 0; x < width; ++x) {
			size_t i = (y * width + x) * 3;
			if (pointsMap.find(std::make_pair(x / scale, getSize() - (y / scale))) != pointsMap.end()) {
				image[i] = 255;
				image[i + 1] = 0;
				image[i + 2] = 0;
			}
		}
	}

	// Écriture du fichier PPM
	std::ofstream ofs(filename.c_str(), std::ios::binary);
	if (!ofs) {
		std::cerr << "Error: Could not open file " << filename << std::endl;
		return;
	}

	ofs << "P6\n" << width << " " << height << "\n255\n";
	ofs.write(reinterpret_cast<const char*>(&image[0]), image.size());
};
