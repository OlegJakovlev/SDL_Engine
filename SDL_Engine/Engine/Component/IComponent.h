#pragma once

#ifndef IComponent_H
#define IComponent_H

class IComponent {
public:
    virtual void Update();
    virtual void Render();
    virtual IComponent* GetComponent();
};

#endif
