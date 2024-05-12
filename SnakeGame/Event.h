#pragma once
#include <functional>
#include <vector>


/**
* @brief Класс для реализации системы событий, позволяющей подписываться, отписываться и уведомлять обработчики событий.
*
* @tparam Args Аргументы, которые передаются обработчикам событий.
*/
template <typename... Args>
class Event
{
public:
	/**
	* @brief Деструктор, который автоматически очищает обработчики.
	*/
	~Event();

	/**
	* @brief Тип функции, представляющей обработчик события.
	*/
	using EventHandler = std::function<void(Args...)>;

	/**
	* @brief Подписывает новый обработчик на событие.
	* @param handler Функция-обработчик, которая будет вызвана при срабатывании события.
	*/
	void Subscribe(EventHandler handler);

	/**
	* @brief Отписывает обработчик от события.
	* @param handler Функция-обработчик, которая больше не должна вызываться.
	*/
	void Unsubscribe(EventHandler handler);

	/**
	* @brief Уведомляет все подписанные обработчики о событии.
	* @param args Аргументы, передаваемые в обработчики.
	*/
	void Notify(Args... args);// Notify all listeners

	/**
	* @brief Оператор добавления обработчика (перегрузка +=).
	* @param handler Функция-обработчик для добавления.
	* @return Ссылка на текущий объект `Event`.
	*/
	Event<>& operator+=(EventHandler handler);// Call Subscribe()

	/**
	* @brief Оператор удаления обработчика (перегрузка -=).
	* @param handler Функция-обработчик для удаления.
	* @return Ссылка на текущий объект `Event`.
	*/
	Event<>& operator-=(EventHandler handler);// Call Unsubscribe()
	void operator()(Args... args);// Call Notify()

private:
	/**
	* @brief Хранилище всех подписанных обработчиков событий.
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