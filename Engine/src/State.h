#pragma once

class State
{
public:
	State();
	virtual ~State();

	virtual void pollEvent() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
};