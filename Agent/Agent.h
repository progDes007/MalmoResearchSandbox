#pragma once

#include "agent_global.h"
#include <AgentHost.h>
#include <ClientPool.h>

class QJsonValueRef;

class AGENT_EXPORT Agent
{
public:
	// Describes the general agent info.
	struct AgentStatsInfo
	{
		bool m_isAlive;
		Vector3d m_position;
		double m_yaw;
		double m_pitch;

		AgentStatsInfo()
			: m_isAlive (true), m_position{ 0.0, 0.0, 0.0 }, m_yaw(0.0), m_pitch(0.0)
		{}
	};
public:
	Agent();
	virtual ~Agent();

	// Function for update
	virtual void update(malmo::AgentHost & agentHost, malmo::WorldState & worldState, double timeElapsed);
protected:
	// Function for reading the observations. Function is virtual. Subcalsses can
	// implement their own handling. Function returns true if the observation is handled
	virtual bool observeJson(const QString & key, QJsonValueRef value);
private:

	

	struct Impl;
	std::unique_ptr<Impl> m_impl;
};
