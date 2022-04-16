#pragma once

#ifndef IObserver_H
#define IObserver_H

class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void UpdateEvent();
};

#endif