#pragma once
#include "utilityai.hpp"
#include "pathagent.hpp"

class Agent {
public:
	float m_hunger;
	float m_fun; 
	float m_clean; 
	float m_energy;
	Agent() {
		m_hunger = 0.1f;
		m_fun = 1.0f;
		m_clean = 1.0f;
		m_energy = 1.0f;
	}
	void update(float dtime);
	void draw();
	void drawBars(int x, int y);
	UtilityAI* getUtilAI();
	float m_actionTimer;
	PathAgent* getPathAgent();

private:
	UtilityAI m_utilAI;
	PathAgent m_pathAgent;


};