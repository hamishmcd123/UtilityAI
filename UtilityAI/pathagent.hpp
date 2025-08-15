#pragma once
#include "pathfinding.hpp"

class PathAgent {
public:
	Node* m_currentNode;
	float m_speed;
	int m_currentIndex;
	std::vector<Node*> m_path;
	glm::vec2 m_position;
	float m_radius;
	int m_xoffset = 300;
	int m_yoffset = 50;
	void update(float dtime);
	void goToNode(Node* node);
	void draw();
	void setNode(Node* node);
	void setSpeed(float speed);
	void setRadius(float radius);
};