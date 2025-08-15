#pragma once 
#include "behaviour.hpp"
#include <vector>

class UtilityAI : public Behaviour {
public:
	void update(Agent* agent, float dtime) override;
	~UtilityAI();
	void addBehaviour(Behaviour* behaviour);
	Behaviour* getCurrentBehaviour();

private:
	std::vector<Behaviour*> m_behaviours;
	Behaviour* m_currentBehaviour;
};