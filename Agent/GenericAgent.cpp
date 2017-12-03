#include "stdafx.h"
#include "GenericAgent.h"

#include <qtcore/qjsonobject.h>
#include <qtcore/qjsonarray.h>

const int GRID_OBSERVATION_MIN_X = -1;
const int GRID_OBSERVATION_MAX_X = 1;
const int GRID_OBSERVATION_MIN_Y = -1;
const int GRID_OBSERVATION_MAX_Y = 1;
const int GRID_OBSERVATION_MIN_Z = -1;
const int GRID_OBSERVATION_MAX_Z = 1;
const int GRID_OBSERVATION_SIZE_X = GRID_OBSERVATION_MAX_X - GRID_OBSERVATION_MIN_X + 1;
const int GRID_OBSERVATION_SIZE_Y = GRID_OBSERVATION_MAX_Y - GRID_OBSERVATION_MIN_Y + 1;
const int GRID_OBSERVATION_SIZE_Z = GRID_OBSERVATION_MAX_Z - GRID_OBSERVATION_MIN_Z + 1;
const int GRID_OBSERVATION_ARRAY_SIZE = GRID_OBSERVATION_SIZE_X * GRID_OBSERVATION_SIZE_Y * GRID_OBSERVATION_SIZE_Z;


struct GenericAgent::Impl
{
};

/////////////////////////////////////////////////////////
GenericAgent::GenericAgent()
	: m_impl(new Impl)
{

}

GenericAgent::~GenericAgent()
{
}

void GenericAgent::update(malmo::AgentHost & agentHost, malmo::WorldState & worldState, double timeElapsed)
{
	Agent::update(agentHost, worldState, timeElapsed);
	agentHost.sendCommand("move 1");
	{
		std::ostringstream oss;
		oss << "turn " << rand() / float(RAND_MAX);
		agentHost.sendCommand(oss.str());
	}
}

bool GenericAgent::observeJson(const QString & key, QJsonValueRef value)
{
	if (key == "grid_observation")
	{
		assert(value.isArray());
		QJsonArray ar = value.toArray();
		int arraySize = ar.size();
		if (arraySize == GRID_OBSERVATION_ARRAY_SIZE)
		{
			// Loop through array.
			int i = 0; // Array index
			for (int y = GRID_OBSERVATION_MIN_X; y <= GRID_OBSERVATION_MAX_X; ++y)
			{
				for (int z = GRID_OBSERVATION_MIN_Z; z <= GRID_OBSERVATION_MAX_Z; ++z)
				{
					for (int x = GRID_OBSERVATION_MIN_X; x <= GRID_OBSERVATION_MAX_X; ++x)
					{
						QString s = ar[i].toString();

						++i;
					}
				}
			}
		}
		else std::cout << "Error: incorrect array size for grid observation" << std::endl;
		return true;
	}
	else return Agent::observeJson(key, value);
}