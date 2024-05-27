#pragma once
#include "Data.h"

#include "TextButton.h"

namespace Style
{
	enum CharSize : uint32_t
	{
		Small = 20u,
		Medium = 30u,
		Large = 38u,
	};

	const unsigned int WINDOW_AXIS = Data::WINDOW_WIDTH / 2;
	const unsigned int WINDOW_OFFSET = 10;
}
