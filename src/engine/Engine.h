#pragma once
#ifndef ENGINE_CLASS_H
#define ENGINE_CLASS_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <memory>

#include <engine/Metrics.h>
#include <window/Window.h>

#include <components/Camera.h>
#include <components/Light.h>
#include <components/Model.h>

typedef std::unique_ptr<Window> WindowPtr;
// Camera is shared with Window
typedef std::shared_ptr<Camera> CameraSharedPtr;
typedef std::unique_ptr<Light> LightPtr;
typedef std::unique_ptr<Model> ModelPtr;

class Engine {
private:
	double lastTime;
	Metric metric;

	WindowPtr window;
	CameraSharedPtr camera;
	LightPtr light;
	ModelPtr model;
public:
	Engine();
	~Engine();

	Engine(Engine& other);
	Engine& operator=(Engine& other);

	void Start();

private:
	double getTime();
	void Run();
	void Update(double thisTime, double delta);
	void Render(double delta);
};

#endif // !ENGINE_CLASS_H

