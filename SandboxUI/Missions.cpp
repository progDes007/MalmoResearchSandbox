#include "Internal.h"
#include "Missions.h"
#include <Agent/GenericAgent.h>
#include <QFile.h>

std::unique_ptr<AgentWorker> Missions::createMission1()
{
	// Open the xml
	QFile file("Resources\\mission1.xml");
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	QString qxml(file.readAll());
	std::string xml = qxml.toStdString();
	// Define mission
	std::unique_ptr<malmo::MissionSpec> my_mission(new malmo::MissionSpec(xml, true));
	std::unique_ptr<Agent> agent(new GenericAgent());
	std::unique_ptr<AgentWorker> res (new AgentWorker(std::move(my_mission), std::move(agent)));
	return res;
}