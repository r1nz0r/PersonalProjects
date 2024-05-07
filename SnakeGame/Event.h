#pragma once
#include <functional>
#include <vector>

template <typename... Args>
class Event
{
public:
	using EventHandler = std::function<void(Args...)>;
	void Subscribe(EventHandler handler);
	void Unsubscribe(EventHandler handler);
	void Notify(Args... args);// Notify all listeners
	Event<>& operator+=(EventHandler handler);// Call Subscribe()
	Event<>& operator-=(EventHandler handler);// Call Unsubscribe()
	void operator()(Args... args);// Call Notify()

private:
	std::vector<EventHandler> _handlers;
};

template<typename ...Args>
inline void Event<Args...>::Subscribe(EventHandler handler)
{
	_handlers.push_back(handler);
}

template<typename ...Args>
inline void Event<Args...>::Unsubscribe(EventHandler handler)
{
	_handlers.erase(std::remove(_handlers.begin(), _handlers.end(), handler), _handlers.end());
}

template<typename ...Args>
inline void Event<Args...>::Notify(Args... args)
{
	for (const auto& handler : _handlers)
	{
		handler(std::forward<Args>(args)...);
	}
}

template<typename ...Args>
Event<>& Event<Args...>::operator+=(EventHandler handler)
{
	Subscribe(handler);
	return *this;
}

template<typename ...Args>
Event<>& Event<Args...>::operator-=(EventHandler handler)
{
	Unsubscribe(handler);
	return *this;
}

template<typename ...Args>
void Event<Args...>::operator()(Args... args)
{
	Notify(std::forward<Args>(args)...);
}