#ifndef	__GRAPH_HPP__
#define	__GRAPH_HPP__

#include	<vector>
#include	<iostream>
#include	<sstream>
#include	"./Vector2.hpp"

// Ajoute l'inclusion pour LodePNG
//#include "lodepng.h"
#include <fstream> // Pour écrire dans un fichier

class Graph {
	private:
		Vector2 _size;
		std::vector<Vector2> _list;

		std::string getLineGraph(size_t y) const;
	public:
		Graph(Vector2 size);
		~Graph();

		void	addVector(Vector2);

		std::vector<Vector2>	getVector() const;
		Vector2	getSize() const;

		void	printMap() const;
};

//std::ostream& operator<<(std::ostream& os, const Graph& graph);

#endif
