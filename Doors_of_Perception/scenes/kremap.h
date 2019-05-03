#pragma once

#include "engine.h"

class Kremap : public Scene {
public:

	Kremap() = default;
	~Kremap() override = default;

	void Load() override;

	void UnLoad();

	void Update(const double& dt) override;
	void Render() override;
};
