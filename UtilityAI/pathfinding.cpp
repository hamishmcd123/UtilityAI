#include "pathfinding.hpp"

void Node::connectTo(Node* other, float cost)
{
	connections.push_back(Edge(other, cost));
}
