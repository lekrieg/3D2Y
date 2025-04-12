#ifndef EDITOR_APPLICATION_H
#define EDITOR_APPLICATION_H

#include "Application.h"
#include "Assets.h"
#include "Scene.h"
#include "scenes/EditorScene.h"

#include <memory>

namespace editor
{
	class Scene;

	class EditorApplication : public abyss::Application
	{
		private:

			std::shared_ptr<editor::EditorScene> m_scene;

		public:

			EditorApplication(const std::string &configPath, const std::string &assetsPath)
			{
				Init(configPath, assetsPath);
			}

			~EditorApplication();

			void Run() override;
			void Quit() override;
			bool IsRunning() override;
			abyss::Assets &GetAssets() override;
			sf::RenderWindow &GetWindow() override;
			const float DeltaTime() const override;

		protected:

			void Init(const std::string &configPath, const std::string &assetsPath) override;
			void Update() override;

			void UserInputSystem() override;
	};
}

#endif // !EDITOR_APPLICATION_H
