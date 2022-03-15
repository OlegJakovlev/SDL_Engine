#pragma once

#ifndef InputController_H
#define InputController_H

#include <utility>
#include <map>
#include <string>
#include <iostream>

class InputController {
private:
    //std::multimap<std::string, MyKeys> Binds;

public:
    InputController();
    virtual ~InputController();
    bool isActionActive(const std::string& actionName) const;
};

#endif