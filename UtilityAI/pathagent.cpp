#include "pathagent.hpp"
#include "nodemap.hpp"
#include "raylib.h"

void PathAgent::update(float dtime)
{
	if (m_path.empty()) {
		return;
	}

	Node* nextNode = m_path[m_currentIndex];

	glm::vec2 vecToTarget = nextNode->position - m_position;

	float distanceToTarget = glm::length(vecToTarget);

	float toMove = distanceToTarget - m_speed * dtime;

	if (toMove > 0) {
		m_position += m_speed * dtime * glm::normalize(vecToTarget);
	}
	else {
		if (++m_currentIndex >= m_path.size()) {
			m_position = nextNode->position;
			m_path.clear();
			m_currentIndex = 0;
			setNode(nextNode);
		}
		else {
			nextNode = m_path[m_currentIndex];
			vecToTarget = nextNode->position - m_position;
			m_position += -1 * toMove * glm::normalize(vecToTarget);
			setNode(nextNode);
		}
	}
}

void PathAgent::goToNode(Node* node)
{
	m_path = NodeMap::DijkstrasSearch(m_currentNode, node);
	m_currentIndex = 0;
}

void PathAgent::draw()
{
	DrawCircle(static_cast<int>(m_position.x + m_xoffset), static_cast<int>(m_position.y + m_yoffset), m_radius, BLACK);

}

void PathAgent::setNode(Node* node)
{
	m_currentNode = node;
}

void PathAgent::setSpeed(float speed)
{
	m_speed = speed;
}

void PathAgent::setRadius(float radius)
{
	m_radius = radius;
}