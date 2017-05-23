#pragma once
#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>

class Camera {
public:
	Camera();
	Camera(float width, float height);
	float* getProjection();
	void setPos(float x, float y);
	void setScale(float zoom);
private:
	static const glm::mat4 iMat;
	glm::mat4 view, projection, translation, negTranslation, scaling;
};

#endif