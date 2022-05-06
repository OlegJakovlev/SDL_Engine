#pragma once

#ifndef AudioConfigurator_H
#define AudioConfigurator_H

#include "../Configurator.h"
#include "../../Locator/AudioLocator/AudioLocator.h"
#include "../../Service/Audio/PCAudio/PCAudio.h"

class AudioConfigurator : public Configurator {
public:
	explicit AudioConfigurator(const std::string& configPath);
	~AudioConfigurator();

	virtual void LoadConfiguration() override;
};

#endif