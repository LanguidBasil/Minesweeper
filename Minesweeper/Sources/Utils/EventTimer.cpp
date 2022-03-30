#include "EventTimer.h"
#include <thread>

namespace Utils
{
	EventTimerArgs::EventTimerArgs(milliseconds delayBetweenEvents, milliseconds totalPassedTime)
		: DelayBetweenEvents(delayBetweenEvents), TotalPassedTime(totalPassedTime) {}



	EventTimer::EventTimer(milliseconds delayBetweenEvents)
		: Event(),
		ThreadIsActive(true),
		Thread(&EventTimer::StartTimer, this),
		DelayBetweenEvents(delayBetweenEvents),
		Start(std::chrono::high_resolution_clock::now())
	{}

	EventTimer::~EventTimer()
	{
		ThreadIsActive = false;
		Thread.detach();
	}

	milliseconds EventTimer::GetTotalPassedTime()
	{
		return std::chrono::duration_cast<milliseconds>(std::chrono::high_resolution_clock::now() - Start);
	}

	void EventTimer::StartTimer()
	{
		while (ThreadIsActive)
		{
			std::this_thread::sleep_for(DelayBetweenEvents);
			Event.Fire(EventTimerArgs(DelayBetweenEvents, GetTotalPassedTime()));
		}
	}
}