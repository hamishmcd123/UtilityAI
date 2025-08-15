#include "agent.hpp"
#include "raylib.h"
#include "util.hpp"
#include <string>

void Agent::update(float dtime)
{
	m_hunger += 0.03f * dtime;
	m_hunger = clamp01(m_hunger);

	m_energy -= 0.02f * dtime;
	m_energy = clamp01(m_energy);

	m_fun -= 0.02f * dtime;
	m_fun = clamp01(m_fun);

	m_clean -= 0.01f * dtime;
	m_clean = clamp01(m_clean);

	m_utilAI.update(this, dtime);
	m_pathAgent.update(dtime);
}

void Agent::draw()
{
	m_pathAgent.draw();
}

void Agent::drawBars(int x, int y)
{
	UtilityAI* utilai = &m_utilAI;
	
	if (utilai->getCurrentBehaviour()) {
		switch (utilai->getCurrentBehaviour()->name) {

		case(BEHAVIOUR_NAME::eat):
			DrawText("EAT", x, y - 40, 20, RED);
			break;

		case(BEHAVIOUR_NAME::wash):
			DrawText("WASH", x, y - 40, 20, BLUE);
			break;

		case(BEHAVIOUR_NAME::sleep):
			DrawText("SLEEP", x, y - 40, 20, YELLOW);
			break;

		case(BEHAVIOUR_NAME::play): 
			DrawText("PLAY", x, y - 40, 20, GREEN);
			break;

		default:
			DrawText("ERROR", x, y - 40, 20, RED);
		}
	}

	DrawRectangleLines(x, y - 10, 420, 160, BLACK);

	DrawRectangle(x, y, (int)((1 - m_hunger) * 300), 20, RED);
	DrawText("Hunger", x + 320, y, 15, BLACK);

	DrawRectangle(x, y + 40, (int)(m_energy * 300), 20, YELLOW);
	DrawText("Energy", x + 320, y + 40, 15, BLACK);

	DrawRectangle(x, y + 80, (int)(m_clean * 300), 20, BLUE);
	DrawText("Hygiene", x + 320, y + 80, 15, BLACK);

	DrawRectangle(x, y + 120, (int)(m_fun * 300), 20, GREEN);
	DrawText("Fun", x + 320, y + 120, 15, BLACK);
	
	DrawText((std::string("Action Timer: ") + std::to_string(m_actionTimer)).c_str(), x, y - 60, 10, BLACK);
}

UtilityAI* Agent::getUtilAI()
{
	return &m_utilAI;
}

PathAgent* Agent::getPathAgent()
{
	return &m_pathAgent;
}
