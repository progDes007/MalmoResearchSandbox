#include "stdafx.h"
#include "AgentWorker.h"

#include <qtcore/qelapsedtimer.h>


AgentWorker::AgentWorker(std::unique_ptr<malmo::MissionSpec> missionSpec,
	std::unique_ptr<Agent> agent)
	: m_agent(std::move(agent)), m_missionSpec(std::move(missionSpec))
{
}

AgentWorker::~AgentWorker()
{
}

void AgentWorker::doJob()
{
	try
	{
		malmo::AgentHost agentHost;

		malmo::MissionRecordSpec my_mission_record("./saved_data.tgz");
		my_mission_record.recordCommands();
		my_mission_record.recordMP4(20, 400000);
		my_mission_record.recordRewards();
		my_mission_record.recordObservations();

		std::cout << "Starting mission" << std::endl;
		int startAttempts = 5;
		while (true){
			try
			{
				agentHost.startMission(*m_missionSpec, my_mission_record);
				break; // No excpetion = success
			}
			catch (...)
			{
				startAttempts--;
				if (startAttempts > 0) 
					std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Try again in 1 second
				else throw; // All attempts failed.
				if (isCancelled()) return;
			}
		}
		malmo::WorldState world_state;

		// Loop until mission not starts
		world_state = agentHost.getWorldState();
		while (!world_state.has_mission_begun)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			world_state = agentHost.getWorldState();
		}
		std::cout << "Mission started" << std::endl;

		QElapsedTimer timer;
		timer.start();

		do {

			if (isCancelled()) return;
			world_state = agentHost.getWorldState();
			
			m_agent->update(agentHost, world_state, timer.elapsed() / 1000.0);
			timer.restart();
			
		/*	std::cout << "video,observations,rewards received: "
				<< world_state.number_of_video_frames_since_last_state << ","
				<< world_state.number_of_observations_since_last_state << ","
				<< world_state.number_of_rewards_since_last_state << std::endl;
			for (boost::shared_ptr<malmo::TimestampedReward> reward : world_state.rewards)
				std::cout << "Summed reward: " << reward->getValue() << std::endl;
			for (boost::shared_ptr<malmo::TimestampedString> error : world_state.errors)
				std::cout << "Error: " << error->text << std::endl;*/
		} while (world_state.is_mission_running);
		std::cout << "Mission ended" << std::endl;
	}
	catch (std::exception & e)
	{
		std::cout << "AgentWorker::doJob() exception: " << e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "AgentWorker::doJob() unknowne exception: " << std::endl;
	}
}