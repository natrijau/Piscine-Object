#ifndef	__GRAPH_HPP__
#define	__GRAPH_HPP__

#include	<vector>
#include	<map>
#include	<iostream>
#include	<sstream>
#include	"./Vector2.hpp"

// Ajoute l'inclusion pour LodePNG
//#include "lodepng.h"
#include <fstream> // Pour écrire dans un fichier

class Graph {
	private:
		size_t _size;
		std::vector<Vector2> _list;
		std::vector<std::pair<Vector2, Vector2> >	_lines;

	public:
		Graph(size_t size, std::vector<Vector2> list);
		Graph(size_t size);
		~Graph();

		void	addVector(Vector2);
		void	addLine(Vector2 start, Vector2 end);

		std::vector<Vector2>	getVector() const;
		size_t	getSize() const;

		void	loadFile(const std::string& filename);
		std::string getLineGraph(size_t y) const;
		bool	pointVector(size_t y) const;
		void	printMap() const;

		void 	saveAsPPM(const std::string& filename, size_t scale) const;
};

std::ostream& operator<<(std::ostream& os, const Graph& graph);

#endif
