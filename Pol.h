#pragma once
#include <vector>
#include <iostream>
#include <glm/glm.hpp>


struct Vertex {
	glm::vec2 v;
};

struct Edges {
	glm::vec2 first;
	glm::vec2 second;
	char orientation;
};

class Pol {

public:
	std::vector <Edges> edge;
	std::vector <Vertex> vertex;
	float len;
	Pol();
	Pol(std::vector<Vertex> v, float l);
	void construct();
	char find_orient(glm::vec2 a, glm::vec2 b);
};
