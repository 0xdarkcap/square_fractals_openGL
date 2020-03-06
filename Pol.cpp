#include "Pol.h"

Pol::Pol() {
	Vertex ver[4];
	ver[0].v = { 1,1 };
	vertex.push_back(ver[0]);
	ver[1].v = { 1, -1 };
	vertex.push_back(ver[1]);
	ver[2].v = { -1, -1 };
	vertex.push_back(ver[2]);
	ver[3].v = { -1, 1 };
	vertex.push_back(ver[3]);
	len = 2.0;
	std::cout << vertex.size() << std::endl;
	construct();
}

Pol::Pol(std::vector<Vertex> v, float l) {
	vertex = v;
	len = l;
	construct();
	std::cout << edge.size() << " " << vertex.size() << std::endl;
}

void Pol::construct() {
	std::vector<Vertex>::iterator i;
	for (i = vertex.begin(); i != vertex.end() - 1; ++i)
	{
		Vertex first = *i;
		Vertex second = *(i + 1);
		Edges temp;
		temp.first = first.v;
		temp.second = second.v;
		temp.orientation = find_orient(first.v, second.v);
		edge.push_back(temp);
	}
	Edges temp;
	temp.first = (vertex.back()).v;
	temp.second = (vertex.front()).v;
	temp.orientation = find_orient((vertex.back()).v, (vertex.front()).v);
	edge.push_back(temp);
}

char Pol::find_orient(glm::vec2 a, glm::vec2 b) {
	if (a.x == b.x && a.y > b.y) return 'a';
	else if (a.y == b.y && a.x > b.x) return 'b';
	else if (a.x == b.x && a.y < b.y) return 'c';
	else return 'd';
}