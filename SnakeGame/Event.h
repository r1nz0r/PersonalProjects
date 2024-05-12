#pragma once
#include <functional>
#include <vector>


/**
* @brief ����� ��� ���������� ������� �������, ����������� �������������, ������������ � ���������� ����������� �������.
*
* @tparam Args ���������, ������� ���������� ������������ �������.
*/
template <typename... Args>
class Event
{
public:
	/**
	* @brief ����������, ������� ������������� ������� �����������.
	*/
	~Event();

	/**
	* @brief ��� �������, �������������� ���������� �������.
	*/
	using EventHandler = std::function<void(Args...)>;

	/**
	* @brief ����������� ����� ���������� �� �������.
	* @param handler �������-����������, ������� ����� ������� ��� ������������ �������.
	*/
	void Subscribe(EventHandler handler);

	/**
	* @brief ���������� ���������� �� �������.
	* @param handler �������-����������, ������� ������ �� ������ ����������.
	*/
	void Unsubscribe(EventHandler handler);

	/**
	* @brief ���������� ��� ����������� ����������� � �������.
	* @param args ���������, ������������ � �����������.
	*/
	void Notify(Args... args);// Notify all listeners

	/**
	* @brief �������� ���������� ����������� (���������� +=).
	* @param handler �������-���������� ��� ����������.
	* @return ������ �� ������� ������ `Event`.
	*/
	Event<>& operator+=(EventHandler handler);// Call Subscribe()

	/**
	* @brief �������� �������� ����������� (���������� -=).
	* @param handler �������-���������� ��� ��������.
	* @return ������ �� ������� ������ `Event`.
	*/
	Event<>& operator-=(EventHandler handler);// Call Unsubscribe()
	void operator()(Args... args);// Call Notify()

private:
	/**
	* @brief ��������� ���� ����������� ������������ �������.
	*/
	std::vector<EventHandler> _handlers;
};



template<typename ...Args>
inline Event<Args...>::~Event()
{
	_handlers.clear();
}

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