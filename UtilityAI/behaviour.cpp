#include "behaviour.hpp"
#include "agent.hpp"
#include "util.hpp"
#include "raylib.h"
#include <string>

void EatBehaviour::enter(Agent* agent)
{
	agent->m_actionTimer = 0.0f;
	agent->getPathAgent()->goToNode(m_recoverNode);
}

float EatBehaviour::evaluate(Agent* agent)
{
	float hungerEval = smoothStep01(agent->m_hunger) * (0.8 + 0.2 * smoothStep01(agent->m_energy));
	DrawText("Hunger Eval:", 10, 40, 10, BLACK);
	DrawText(std::to_string(hungerEval).c_str(), 80, 40, 10, BLACK);

	if (agent->m_hunger > 0.9) {
		return std::max(hungerEval, 0.95f);
	}
	else {
		return hungerEval;
	}
}

void EatBehaviour::update(Agent* agent, float dtime)
{
	if (glm::distance(agent->getPathAgent()->m_position, m_recoverNode->position) < 1.0f) {
		agent->m_hunger -= 0.8f * dtime;
		agent->m_energy += 0.05f * dtime;
		agent->m_clean -= 0.02f * dtime;
		agent->m_actionTimer += dtime;
	}

}

void SleepBehaviour::enter(Agent* agent)
{
	agent->getPathAgent()->goToNode(m_recoverNode);
	agent->m_actionTimer = 0.0f;
}

float SleepBehaviour::evaluate(Agent* agent)
{
	float sleepEval = smoothStep01(1 - agent->m_energy) * (0.8 + 0.2 * smoothStep01(1 - agent->m_hunger));
	DrawText("Sleep Eval:", 10, 20, 10, BLACK);
	DrawText(std::to_string(sleepEval).c_str(), 80, 20, 10, BLACK);
	if (agent->m_energy < 0.1) {
		return 1.0f;
	}
	else {
		return sleepEval;
	}
}

void SleepBehaviour::update(Agent* agent, float dtime)
{
	if (glm::distance(agent->getPathAgent()->m_position, m_recoverNode->position) < 1.0f) {
		agent->m_energy += 0.7f * dtime;
		agent->m_fun -= 0.05f * dtime;
		agent->m_actionTimer += dtime;
	}
}

void WashBehaviour::enter(Agent* agent)
{
	agent->m_actionTimer = 0.0f;
	agent->getPathAgent()->goToNode(m_recoverNode);
}

float WashBehaviour::evaluate(Agent* agent)
{
	float washEval = smoothStep01(1 - agent->m_clean);
	DrawText("Wash Eval:", 10, 30, 10, BLACK);
	DrawText(std::to_string(washEval).c_str(), 80, 30, 10, BLACK);
	
	return washEval;
}

void WashBehaviour::update(Agent* agent, float dtime)
{
	if (glm::distance(agent->getPathAgent()->m_position, m_recoverNode->position) < 1.0f) {
		agent->m_clean += 0.5f * dtime;
		agent->m_actionTimer += dtime;
	}
}

void PlayBehaviour::enter(Agent* agent)
{
	agent->getPathAgent()->goToNode(m_recoverNode);
	agent->m_actionTimer = 0.0f;
}

float PlayBehaviour::evaluate(Agent* agent)
{
	float playEval = smoothStep01(1 - agent->m_fun) * (0.7 + 0.3 * smoothStep01(agent->m_energy));
	DrawText("Play Eval", 10, 50, 10, BLACK);
	DrawText(std::to_string(playEval).c_str(), 80, 50, 10, BLACK);
	return playEval;
	
}

void PlayBehaviour::update(Agent* agent, float dtime)
{

	if (glm::distance(agent->getPathAgent()->m_position, m_recoverNode->position) < 1.0f) {
		agent->m_fun += 0.15f * dtime;
		agent->m_energy -= 0.1f * dtime;
		agent->m_hunger += 0.01f * dtime;
		agent->m_actionTimer += dtime;
	}
}
