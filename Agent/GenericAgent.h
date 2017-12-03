#pragma once
#include "Agent.h"


/// GenericAgent class - is agent that plays survival game
class AGENT_EXPORT GenericAgent : public Agent
{
public:
	GenericAgent();
	virtual ~GenericAgent();

	// Function for update
	virtual void update(malmo::AgentHost & agentHost, malmo::WorldState & worldState, double timeElapsed);
protected:
	virtual bool observeJson(const QString & key, QJsonValueRef value);
private:
	
	struct Impl;
	std::unique_ptr<Impl> m_impl;
};
