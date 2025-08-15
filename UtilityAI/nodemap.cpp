#include "nodemap.hpp"
#include "raylib.h"
#include <algorithm>
#include <queue>
#include <unordered_set>
#include "pathagent.hpp"

Node* NodeMap::getNode(int x, int y)
{
	return m_nodes[x + m_width * y];
}

void NodeMap::setNode(int x, int y, NODE_TYPE type)
{
	Node* node = getNode(x, y);
	node->type = type;
}

void NodeMap::draw()
{
	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width; x++) {
			Node* node = getNode(x, y);
			switch (node->type) {

			case(NODE_TYPE::empty):
				DrawRectangleLines(pa->m_xoffset + x * 32, pa->m_yoffset + y * 32, 32, 32, BLACK);
				break;
			
			case(NODE_TYPE::eat):
				DrawRectangle(pa->m_xoffset + x * 32, pa->m_yoffset + y * 32, 32, 32, RED);
				break;
			case(NODE_TYPE::sleep):
				DrawRectangle(pa->m_xoffset + x * 32, pa->m_yoffset + y * 32, 32, 32, YELLOW);
				break;

			case(NODE_TYPE::wash):
				DrawRectangle(pa->m_xoffset + x * 32, pa->m_yoffset + y * 32, 32, 32, BLUE);
				break;

			case(NODE_TYPE::play):
				DrawRectangle(pa->m_xoffset + x * 32, pa->m_yoffset + y * 32, 32, 32, GREEN);
				break;

			default:
				DrawRectangleLines(pa->m_xoffset + x * 32, pa->m_yoffset + y * 32, 32, 32, BLACK);
				break;
			}
		}
	}
}
NodeMap::~NodeMap()
{
		if (m_nodes != nullptr) {
			for (int i = 0; i < m_width * m_height; i++) {
				delete m_nodes[i];
			}
		}
		delete[] m_nodes;
}

Node* NodeMap::getClosestNode(glm::vec2 worldPos)
{
	int i = (int)((worldPos.x - pa->m_xoffset) / 32);
	if (i < 0 || i >= m_width) return nullptr;

	int j = (int)((worldPos.y - pa->m_yoffset) / 32);
	if (j < 0 || j >= m_height) return nullptr;

	return getNode(i, j);
}

void NodeMap::initialise()
{
	m_nodes = new Node * [m_width * m_height];
	

	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width; x++) {
			m_nodes[x + m_width * y] = new Node((x + 0.5f) * 32, (y + 0.5f) * 32);
		}
	}
	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width; x++) {
			Node* node = getNode(x, y);
			if (node) {
				// See if there is a node to our west. Return nullptr if we are on the 
				// first node horizontally.

				Node* nodeWest = x == 0 ? nullptr : getNode(x - 1, y);
				if (nodeWest) {
					// Assuming a weight of 1 for now.
					node->connectTo(nodeWest, 1);
					nodeWest->connectTo(node, 1);
				}

				Node* nodeSouth = y == 0 ? nullptr : getNode(x, y - 1);
				if (nodeSouth) {
					node->connectTo(nodeSouth, 1);
					nodeSouth->connectTo(node, 1);
				}
			}
		}
	}
}

void NodeMap::resetNodes()
{
	
}

std::vector<Node*> NodeMap::DijkstrasSearch(Node* startNode, Node* endNode)
{
	if (startNode == nullptr || endNode == nullptr) {
		return {};
	}

	// Empty path if startNode = endNode
	if (startNode == endNode) {
		return {};
	}

	startNode->gScore = 0;
	startNode->previous = nullptr;

	// Create a comparison functor 
	struct Compare {
		bool operator()(Node* a, Node* b) {
			return a->gScore > b->gScore;
		}
	};

	// Create our open and closed list (priority queue custom comparison object)
	std::priority_queue<Node*, std::vector<Node*>, Compare> openList;
	std::unordered_set<Node*> openSet;
	std::unordered_set<Node*> closedList;

	openList.push(startNode);
	openSet.insert(startNode);

	while (!openList.empty()) {
		Node* currentNode = openList.top();

		if (currentNode == endNode) {
			break;
		}

		openList.pop();
		openSet.erase(currentNode);
		closedList.insert(currentNode);

		for (auto& c : currentNode->connections) {
			if (closedList.find(c.target) == closedList.end()) {
				float gScore = c.cost + currentNode->gScore;

				// If the target is not in the open list.
				if (openSet.find(c.target) == openSet.end()) {
					c.target->gScore = gScore;
					c.target->previous = currentNode;
					openList.push(c.target);
					openSet.insert(c.target);
				}
				else if (gScore < c.target->gScore) {
					c.target->gScore = gScore;
					c.target->previous = currentNode;
					// To update priority queue.
					openList.push(c.target);
				}
			}
		}
	}

	std::vector<Node*> path;
	Node* currentNode = endNode;

	if (endNode->previous == nullptr) {
		return {};
	}

	while (currentNode != nullptr) {
		path.push_back(currentNode);
		currentNode = currentNode->previous;
	}
	std::reverse(path.begin(), path.end());

	return path;
}
