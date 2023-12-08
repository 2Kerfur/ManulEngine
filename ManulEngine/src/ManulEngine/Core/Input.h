#pragma once

#include "KeyCodes.h"
#include "MouseCodes.h"
#include "Math/Math.h"

namespace ManulEngine {

	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static Vector2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}