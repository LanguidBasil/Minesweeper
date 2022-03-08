#pragma once
#include "EventSystem.h"

#include <chrono>
#include <thread>

using milliseconds = std::chrono::milliseconds;

namespace Utils
{
	struct EventTimerArgs : EventSystem::EventArgs
	{
		EventTimerArgs(milliseconds delayBetweenEvents, milliseconds totalPassedTime);

		milliseconds DelayBetweenEvents;
		milliseconds TotalPassedTime;
	};

	class EventTimer
	{
	public:
		EventSystem::Event<EventTimerArgs> Event;
		milliseconds DelayBetweenEvents;

		explicit EventTimer(milliseconds delayBetweenEvents);
		~EventTimer();

		milliseconds GetTotalPassedTime();

	private:
		std::thread Thread;
		std::chrono::high_resolution_clock::time_point Start;

		void StartTimer();
	};
}