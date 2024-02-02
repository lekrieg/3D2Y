#include "Application.h"

void Application::Resize(int width, int height)
{

}

bool Application::Initialize()
{
	bool result = false;

	abyss::render::RenderParams params;

	params.name = "SunRise";
	params.colorBits = 24;
	params.depthBits = 16;
	params.stencilBits = 8;
	params.isFullscreen = false;
	params.height = 600;
	params.width = 600;
	params.maxCacheBytes = 2000;
	params.maxCacheIndices = 2000;

	if(render.Initialize(&params) != ABYSS_RESULT::ABYSS_SUCCESS)
	{
		return false;
	}

	// TODO: Limpa a tela com uma cor nova
	// TODO: Ativa shader
	// TODO: Ativa textura
	// TODO: Carrega a mesh de teste
	// TODO: Seta os filtros que vao ser usados na textura
	// TODO: Carrega a textura
	// TODO: Cria e seta o shader

	return true;
}

void Application::Update()
{
	// TODO: Pega entrada do usuario
}

void Application::Render()
{
	render.EndRendering();
	// TODO: limpa a tela
	// TODO: seta a view e rotaciona a matrix da camera
	// TODO: aplica o shader
	// TODO: aplica a textura
	// TODO: renderiza os modelos
}

void Application::Shutdown()
{
	render.Shutdown();
}

bool Application::ShouldCloseWindow()
{
	return render.ShouldCloseWindow();
}