#pragma once

#include "AsyncWorker.h"
#include "Agent.h"


class AGENT_EXPORT AgentWorker : public AsyncWorker
{
public:
	AgentWorker();
	~AgentWorker();
protected:
	/// implementation of job done by worker in async 
	virtual void  doJob();
};