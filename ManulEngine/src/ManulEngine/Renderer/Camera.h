#pragma once
#include "glm/glm.hpp"
class Camera
{
public:
	void Create();
private:
	glm::vec3 cameraPos;
	glm::vec3 up;
	glm::vec3 cameraRight;

	glm::vec3 cameraTarget;
	glm::vec3 cameraDirection;
	glm::vec3 cameraUp;
};