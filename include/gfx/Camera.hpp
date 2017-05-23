#ifndef CAMERA_HPP
#define CAMERA_HPP

class Camera {
public:
	typedef glm::mat4 mat4;
	Camera();
	Camera(float width, float height);
	mat4 getView();
	float* getProjection();
	void setPos(float x, float y);
	void setScale(float zoom);
private:
	static const mat4 iMat;
	mat4 view, projection, translation, negTranslation, scaling;
};

#endif