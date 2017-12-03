#include "stdafx.h"
#include "Agent.h"

#include <qtcore/qjsondocument.h>
#include <qtcore/qjsonobject.h>

struct Agent::Impl
{
	// This stores the general agent information.
	// Can be accessed only from the worker thread.
	AgentStatsInfo m_privateAgentStats;
};

/////////////////////////////////////////////////////////
Agent::Agent()
	: m_impl(new Impl)
{
	
}

Agent::~Agent()
{
}

void Agent::update(malmo::AgentHost & agentHost, malmo::WorldState & worldState, double timeElapsed)
{
	if (worldState.number_of_observations_since_last_state > 0)
	{
		for (auto observation : worldState.observations)
		{
			// PArse the json
			QJsonDocument doc =	QJsonDocument::fromJson(QByteArray(observation->text.c_str()));
			bool isObject = doc.isObject();
			assert(isObject); // TODO: what todo with arrays?
			QJsonObject object = doc.object();
			// Loop through object keys
			for (auto it = object.begin(); it != object.end(); ++it)
			{
				observeJson(it.key(), it.value());
			}
		}
	}
}

bool Agent::observeJson(const QString & key, QJsonValueRef value)
{
	if (key == "IsAlive")
	{
		m_impl->m_privateAgentStats.m_isAlive = value.toBool();
	}
	else if (key == "XPos")
	{
		m_impl->m_privateAgentStats.m_position[0] = value.toDouble();
	}
	else if (key == "YPos")
	{
		m_impl->m_privateAgentStats.m_position[1] = value.toDouble();
	}
	else if (key == "ZPos")
	{
		m_impl->m_privateAgentStats.m_position[2] = value.toDouble();
	}
	else if (key == "Yaw")
	{
		m_impl->m_privateAgentStats.m_yaw = value.toDouble();
	}
	else if (key == "Pitch")
	{
		m_impl->m_privateAgentStats.m_pitch = value.toDouble();
	}
	return false;
}