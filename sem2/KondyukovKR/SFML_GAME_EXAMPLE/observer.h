#pragma once

#include <vector>

// Интерфейс наблюдателя
class Observer {
public:
    virtual ~Observer() = default;
    virtual void update() = 0;
};

// Интерфейс наблюдаемого объекта (Model)
class Observable {
public:
    void addObserver(Observer* observer) {
        _observers.push_back(observer);
    }

    void removeObserver(Observer* observer) {
        _observers.erase(
            std::remove(_observers.begin(), _observers.end(), observer),
            _observers.end()
        );
    }

    void notifyObservers() {
        for (Observer* obs : _observers)
            obs->update();
    }

private:
    std::vector<Observer*> _observers;
};