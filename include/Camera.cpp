#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "Camera.hpp"

using namespace glm;

const mat4 Camera::iMat = mat4(1.0f);

Camera::Camera() {
	projection = ortho(-1.0f, 1.0f, -1.0f, 1.0f);
	translation = translate(iMat, vec3(0.0f));
	negTranslation = translate(iMat, vec3(0.0f));
	scaling = scale(iMat, vec3(1.0f));

	view = projection * translation * scaling;
}

Camera::Camera(float width, float height) {
	projection = ortho(-width / 2.0f, width / 2.0f, -height / 2.0f, height / 2.0f);
	translation = translate(iMat, vec3(0.0f, 0.0f, 0.0f));
	negTranslation = translate(iMat, vec3(0.0f));
	scaling = scale(iMat, vec3(1.0f));

	view = projection *translation * scaling;
}

mat4 Camera::getView() {
	return view;
}

void Camera::setPos(float x, float y) {
	translation = translate(iMat, vec3(x, y, 0.0f));
	negTranslation = translate(iMat, vec3(-x, -y, 0.0f));
	view = projection * negTranslation * scaling * translation;
}

void Camera::setScale(float zoom) {
	scaling = scale(iMat, vec3(zoom, zoom, 1.0f));
	view = projection * translation * scaling;
}