#ifndef APPLICATION_H
#define APPLICATION_H

#include "Rendering/Render.h"
#include "Rendering/RenderParams.h"

class Application
{
public:
	// Rendering System.
	abyss::render::OpenGLRenderer render;

	// Main model object.
	// abyss::ModelData model;

	// Decals.
	// abyss::ABYSS_TEXTURE texture;

	// Shader.
	// abyss::ShaderHandle shader;

	// Shader parameters.
	// abyss::ParameterHandle mvpParam;
	// abyss::ParameterHandle decalParam;

	// Scene rotations.
	// int xRot = 0, oldXRot = 0;
	// int yRot = 0, oldYRot = 0;

	void Resize(int width, int height);
	bool Initialize();
	void Update();
	void Render();
	void Shutdown();
	bool ShouldCloseWindow();
};

#endif