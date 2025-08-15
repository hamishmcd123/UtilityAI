#pragma once
#include "pathfinding.hpp"
class Agent;

enum class BEHAVIOUR_NAME {
	eat,
	wash,
	sleep,
	play
};

class Behaviour {
public:
	virtual void update(Agent* agent, float dtime) = 0;
	virtual void exit(Agent* agent) {}
	virtual void enter(Agent* agent) {}
	virtual float evaluate(Agent* agent) { return 0.0f; }
	BEHAVIOUR_NAME name;
	Node* m_recoverNode;
	
};

class EatBehaviour : public Behaviour {
public:

	EatBehaviour(Node* recoverNode) {
		name = BEHAVIOUR_NAME::eat;
		m_recoverNode = recoverNode;
	}
	
	void enter(Agent* agent) override;
	float evaluate(Agent* agent) override;
	void update(Agent* agent, float dtime) override;
};

class SleepBehaviour : public Behaviour {
public:
	SleepBehaviour(Node* recoverNode) {
		name = BEHAVIOUR_NAME::sleep; 
		m_recoverNode = recoverNode;
	}

	void enter(Agent* agent) override;
	float evaluate(Agent* agent) override;
	void update(Agent* agent, float dtime) override;
};

class WashBehaviour : public Behaviour {
public:
	WashBehaviour(Node* recoverNode) {
		name = BEHAVIOUR_NAME::wash;
		m_recoverNode = recoverNode;
	}

	void enter(Agent* agent) override;
	float evaluate(Agent* agent) override;
	void update(Agent* agent, float dtime) override;

};

class PlayBehaviour : public Behaviour {
public:
	PlayBehaviour(Node* recoverNode) {
		name = BEHAVIOUR_NAME::play;
		m_recoverNode = recoverNode;
	}

	void enter(Agent* agent) override;
	float evaluate(Agent* agent) override;
	void update(Agent* agent, float dtime) override;
};