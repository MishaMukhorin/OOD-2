﻿#pragma once

#include <unordered_set>
#include <functional>
#include <map>

const int DEFAULT_PRIORITY = 5;

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
	virtual void Update(T const& data) = 0;
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

    [[maybe_unused]] void RegisterObserver(IObserver<T> & observer, int priority = 5)
    {
        RegisterObserverImpl(observer, priority);
    }
    virtual void NotifyObservers() = 0;
    virtual void RemoveObserver(IObserver<T> & observer) = 0;
protected:
    
    [[maybe_unused]] virtual void RegisterObserverImpl(IObserver<T> & observer, int priority) = 0;
// todo done non virtual interface
};

// Реализация интерфейса IObservable
template <class T>
class CObservable : public IObservable<T>
{
public:
    typedef IObserver<T> ObserverType;

    void RegisterObserverImpl(ObserverType& observer, int priority) override
    {
        if (!m_observers.contains(priority))
        {
            m_observers.insert({priority, {}});
        }
        m_observers.at(priority).insert(&observer);
    }

    void NotifyObservers() override
    {
        T data = GetChangedData();
        auto observersCopy = m_observers; // #2
        for (auto it = observersCopy.rbegin(); it != observersCopy.rend(); ++it)
        {
            for (auto& observer : it->second)
            {
                observer->Update(data);
            }
        }
    }

    void RemoveObserver(ObserverType& observer) override
    {
        for (auto& [priority, observers] : m_observers)
        {
            if (observers.erase(&observer) > 0)
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
    //сделать быстрое удаление
    std::map<int, std::unordered_set<ObserverType*>> m_observers;
};
