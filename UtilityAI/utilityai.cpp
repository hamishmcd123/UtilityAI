#include "utilityai.hpp"
#include "agent.hpp"

void UtilityAI::update(Agent* agent, float dtime)
{
	float bestEval = 0; 
	Behaviour* newBehaviour = nullptr;

	if (agent->getPathAgent()->m_path.empty()) {
		agent->getPathAgent()->goToNode(m_currentBehaviour->m_recoverNode);
	}

	for (Behaviour* b : m_behaviours) {
		float eval = b->evaluate(agent);

		if (eval > bestEval) {
			bestEval = eval;
			newBehaviour = b;
		}
	}

	float actionTimer = agent->m_actionTimer;

	if (newBehaviour != nullptr && newBehaviour != m_currentBehaviour && actionTimer > 3.0f) {
		if (m_currentBehaviour) {
			m_currentBehaviour->exit(agent);
			m_currentBehaviour = newBehaviour;
			m_currentBehaviour->enter(agent);
		}
	}
	m_currentBehaviour->update(agent, dtime);
}

UtilityAI::~UtilityAI()
{
	for (Behaviour* b : m_behaviours) {
		delete b;
	}
}

void UtilityAI::addBehaviour(Behaviour* behaviour)
{
	if (m_behaviours.empty()) {
		m_currentBehaviour = behaviour;
	}

	m_behaviours.push_back(behaviour);
}

Behaviour* UtilityAI::getCurrentBehaviour()
{
	return m_currentBehaviour;
}
