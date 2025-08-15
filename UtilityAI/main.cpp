#include "raylib.h"
#include <iostream>
#include "util.hpp"
#include "agent.hpp"
#include "behaviour.hpp"
#include "nodemap.hpp"
#include <ctime>

int main() {
	SetTargetFPS(120);
	
	srand((unsigned int)time(0));

	NodeMap map(15, 15);
	map.initialise();

	Node* eatNode = map.getNode(3, 3);
	map.setNode(3, 3, NODE_TYPE::eat);

	Node* sleepNode = map.getNode(12, 13);
	map.setNode(12, 13, NODE_TYPE::sleep);

	Node* washNode = map.getNode(8, 8);
	map.setNode(8, 8, NODE_TYPE::wash);

	Node* playNode = map.getNode(5, 10);
	map.setNode(5, 10, NODE_TYPE::play);

	Node* start = map.getNode(2, 2);
	Node* end = nullptr;

	std::vector<Node*> path = NodeMap::DijkstrasSearch(start, end);
	
	Agent test;

	PathAgent* testPathAgent = test.getPathAgent();
	testPathAgent->setNode(start);
	testPathAgent->m_position = start->position;
	testPathAgent->setSpeed(128);
	testPathAgent->setRadius(10);

	EatBehaviour* eatBehaviour = new EatBehaviour(eatNode);
	SleepBehaviour* sleepBehaviour = new SleepBehaviour(sleepNode);
	WashBehaviour* washBehaviour = new WashBehaviour(washNode); 
	PlayBehaviour* playBehaviour = new PlayBehaviour(playNode);

	test.getUtilAI()->addBehaviour(eatBehaviour);
	test.getUtilAI()->addBehaviour(sleepBehaviour);
	test.getUtilAI()->addBehaviour(washBehaviour);
	test.getUtilAI()->addBehaviour(playBehaviour);

	map.pa = testPathAgent;

	InitWindow(1280, 720, "UtilityAI");
	while (!WindowShouldClose()) {
		float dtime = GetFrameTime();
		BeginDrawing();
		ClearBackground(RAYWHITE);
		EndDrawing();
		test.drawBars(20, 550);
		test.update(dtime);
		map.draw();
		test.draw();
	}
	CloseWindow();
	return 0;
}