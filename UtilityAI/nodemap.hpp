#pragma once
#include "pathfinding.hpp"
#include <vector>
#include <string>
#include "pathagent.hpp"

class NodeMap {
public:
	NodeMap(int height, int width) : m_width(width), m_height(height) {}
	int m_width;
	int m_height;
	Node** m_nodes;
	Node* getNode(int x, int y);
	void setNode(int x, int y, NODE_TYPE type);
	void draw();
	~NodeMap();
	Node* getClosestNode(glm::vec2 worldPos);
	void initialise();
	void resetNodes();
	PathAgent* pa;
	static std::vector<Node*> DijkstrasSearch(Node* startNode, Node* endNode);
};