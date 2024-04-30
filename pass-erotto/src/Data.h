#pragma once
#include "StateMachine.h"
#include <SFML\Graphics.hpp>

#include <ini.h>

namespace Data
{
	static const std::string WINDOW_TITLE = "Pass-erotto";
	static const unsigned int WINDOW_WIDTH = 400;
	static const unsigned int WINDOW_HEIGTH = 600;
	static const sf::Uint32 WINDOW_STYLE = sf::Style::Close;
	static const unsigned int WINDOW_FPSLIMIT = 60;
	static const bool WINDOW_VSYNC = false;

	static const std::string DATAFILE_NAME = "data";
	inline mINI::INIFile DATAFILE(DATAFILE_NAME);

	static const sf::Color WINDOW_BACKGROUND(70, 100, 170);
	inline sf::Font* WINDOW_FONT = NULL;

	inline sf::RenderWindow* g_Window = NULL;
	inline StateMachine g_Machine;

	void INIT();
};