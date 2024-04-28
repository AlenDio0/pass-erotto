#pragma once
#include "StateMachine.h"
#include <SFML\Graphics.hpp>

namespace Data
{
	//TO DO: ini parser
	static const std::string WINDOW_TITLE = "Pass-erotto";
	static const unsigned int WINDOW_WIDTH = 200;
	static const unsigned int WINDOW_HEIGTH = 800;
	static const sf::Uint32 WINDOW_STYLE = sf::Style::Close;
	static const unsigned int WINDOW_FPSLIMIT = 60;
	static const bool WINDOW_VSYNC = false;

	static sf::RenderWindow* s_Window = NULL;
	static StateMachine s_Machine;

	void INIT();
};