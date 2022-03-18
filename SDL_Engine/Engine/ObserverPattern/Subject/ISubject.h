#pragma once

#ifndef ISubject_H
#define ISubject_H

#include <vector>
#include <algorithm>
#include "../Observer/IObserver.h"

class ISubject {
public:
    virtual void Subscribe(IObserver* newSubscriber);
    virtual void Unsubscribe(IObserver* subscriber);
    virtual void Notify();
};

#endif