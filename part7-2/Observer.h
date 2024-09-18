#pragma once

#include <unordered_set>
#include <functional>
#include <map>

enum class EventType
{
    Temperature,
    Pressure,
    Humidity,
    WindSpeed,
    WindDirection
};

/*
Шаблонный интерфейс IObserver. Его должен реализовывать класс,
желающий получать уведомления от соответствующего IObservable
Параметром шаблона является тип аргумента,
передаваемого Наблюдателю в метод Update
*/
template <typename T>
class IObserver
{
public:
	virtual void Update(T const& data, EventType eventType) = 0;
	virtual ~IObserver() = default;
};

/*
Шаблонный интерфейс IObservable. Позволяет подписаться и отписаться на оповещения,
а также инициировать рассылку уведомлений зарегистрированным наблюдателям.
*/
template <typename T>
class IObservable
{
public:
	virtual ~IObservable() = default;

    [[maybe_unused]] virtual void RegisterObserver(IObserver<T> & observer, EventType eventType, int priority) = 0;
    [[maybe_unused]] virtual void RegisterObserver(IObserver<T> & observer, EventType eventType) = 0;
	virtual void NotifyObservers(EventType eventType) = 0;
	virtual void RemoveObserver(IObserver<T> & observer, EventType eventType) = 0;

};

// Реализация интерфейса IObservable
template <class T>
class CObservable : public IObservable<T>
{
public:
    typedef IObserver<T> ObserverType;

    void RegisterObserver(ObserverType& observer, EventType eventType, int priority) override
    {
        if (!m_observers.contains(eventType))
        {
            m_observers.insert({eventType, {}});
        }
        if (!m_observers.at(eventType).contains(priority))
        {
            m_observers.at(eventType).insert({priority, {}});
        }

        m_observers.at(eventType).at(priority).insert(&observer);
    }

    void RegisterObserver(ObserverType& observer, EventType eventType) override
    {
        if (!m_observers.contains(eventType))
        {
            m_observers.insert({eventType, {}});
        }
        if (!m_observers.at(eventType).contains(5))
        {
            m_observers.at(eventType).insert({5, {}});
        }
        m_observers.at(eventType).at(5).insert(&observer);
    }

    void NotifyObservers(EventType eventType) override
    {
        T data = GetChangedData();
        auto observersCopy = m_observers; // #2
        for (auto& [priority, observers] : m_observers[eventType])
        {
            for (auto& observer : observers)
            {
                observer->Update(data, eventType);
            }
        }
    }

    void RemoveObserver(ObserverType& observer, EventType eventType) override
    {
        for (auto& [priority, observers] : m_observers[eventType])
        {
            if (observers.erase(&observer))
            {
                return;
            }
        }
    }
protected:
	// Классы-наследники должны перегрузить данный метод,
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData() const = 0;

private:
    std::map<EventType, std::map<int, std::unordered_set<ObserverType*>>> m_observers;
};
