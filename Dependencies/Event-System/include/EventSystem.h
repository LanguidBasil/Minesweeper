#pragma once

#include <vector>
#include <functional>
#include <type_traits>

namespace EventSystem
{
	struct EventArgs {};

	template <typename Args>
	class Event
	{
	public:
		explicit Event()
			: Subscribed(std::vector<std::function<void(Args)>>())
		{
			static_assert(std::is_base_of<EventArgs, Args>::value, "Invalid type, Args have to be derived from EventArgs");
		}

		explicit Event(const Event&) = delete;
		~Event() {}

		void Fire(const Args& args)
		{
			for (auto& func : Subscribed)
				func(args);
		}

		void Add(std::function<void(Args)> func)
		{
			Subscribed.push_back(func);
		}

		void Remove(std::function<void(Args)> func)
		{
			for (auto it = Subscribed.begin(); it != Subscribed.end(); it++)
			{
				const auto& current = it->target<void()>();
				const auto& target = func.target<void()>();

				if (current == target)
				{
					Subscribed.erase(it);
					return;
				}
			}
		}

		void RemoveAll()
		{
			Subscribed.clear();
		}

		void operator += (std::function<void(Args)> func)
		{
			Add(func);
		}

		void operator -= (std::function<void(Args)> func)
		{
			Remove(func);
		}

	private:
		std::vector<std::function<void(Args)>> Subscribed;
	};
}