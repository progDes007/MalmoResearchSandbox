#pragma once

#include "agent_global.h"

class AGENT_EXPORT Agent
{
public:
	Agent();
	virtual ~Agent();

private:
	struct Impl;
	std::unique_ptr<Impl> m_impl;
};
