#pragma once

class State
{
public:
	State() = default;
	virtual ~State() = default;

	virtual void pollEvent() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
};