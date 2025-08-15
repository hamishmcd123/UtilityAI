#pragma once
#include <glm/glm.hpp>
#include <vector>
struct Node;

enum class NODE_TYPE {
	play,
	wash,
	eat,
	sleep,
	empty
};

struct Edge {
	Edge() { target = nullptr; cost = 0; }
	Edge(Node* _target, float _cost) : target(_target), cost(_cost) {}
	Node* target;
	float cost;
};

struct Node {
	glm::vec2 position;
	std::vector<Edge> connections;
	float gScore;
	Node* previous;
	NODE_TYPE type;
	Node(float xpos, float ypos) : position(glm::vec2(xpos, ypos)) { previous = nullptr; gScore = FLT_MAX; type = NODE_TYPE::empty; }
	void connectTo(Node* other, float cost);
};