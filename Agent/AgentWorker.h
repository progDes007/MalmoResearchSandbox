#pragma once

#include "AsyncWorker.h"
#include "Agent.h"

#include <AgentHost.h>
#include <ClientPool.h>

class AGENT_EXPORT AgentWorker : public AsyncWorker
{
public:
	AgentWorker(std::unique_ptr<malmo::MissionSpec>  missionSpec,
		std::unique_ptr<Agent> agent);
	~AgentWorker();
protected:
	/// implementation of job done by worker in async 
	virtual void  doJob();
private:
	std::unique_ptr<Agent> m_agent;
	std::unique_ptr<malmo::MissionSpec> m_missionSpec;
};