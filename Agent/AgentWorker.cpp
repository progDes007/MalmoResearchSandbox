#include "stdafx.h"
#include "AgentWorker.h"


#include <AgentHost.h>
#include <ClientPool.h>

AgentWorker::AgentWorker()
{
}

AgentWorker::~AgentWorker()
{
}

void AgentWorker::doJob()
{
	malmo::AgentHost agentHost;

	malmo::MissionSpec my_mission;
	my_mission.timeLimitInSeconds(10);
	my_mission.requestVideo(320, 240);
	my_mission.rewardForReachingPosition(19.5f, 0.0f, 19.5f, 100.0f, 1.1f);

	malmo::MissionRecordSpec my_mission_record("./saved_data.tgz");
	my_mission_record.recordCommands();
	my_mission_record.recordMP4(20, 400000);
	my_mission_record.recordRewards();
	my_mission_record.recordObservations();


	agentHost.startMission(my_mission, my_mission_record);
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));

	malmo::WorldState world_state;

	do {
		if (isCancelled()) return;
		agentHost.sendCommand("move 1");
		{
			std::ostringstream oss;
			oss << "turn " << rand() / float(RAND_MAX);
			agentHost.sendCommand(oss.str());
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		world_state = agentHost.getWorldState();
		std::cout << "video,observations,rewards received: "
			<< world_state.number_of_video_frames_since_last_state << ","
			<< world_state.number_of_observations_since_last_state << ","
			<< world_state.number_of_rewards_since_last_state << std::endl;
		for (boost::shared_ptr<malmo::TimestampedReward> reward : world_state.rewards)
			std::cout << "Summed reward: " << reward->getValue() << std::endl;
		for (boost::shared_ptr<malmo::TimestampedString> error : world_state.errors)
			std::cout << "Error: " << error->text << std::endl;
	} while (world_state.is_mission_running);
}