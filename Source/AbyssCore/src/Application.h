#ifndef APPLICATION_H
#define APPLICATION_H

#include "Assets.h"

namespace abyss
{
	class Scene;

	class Application
	{
	   protected:
			sf::RenderWindow m_window;
			abyss::Assets m_assets;
			std::string m_currentScene;
			int m_simulationSpeed = 1;
			bool m_running = true;

			// DeltaTime stuff
			sf::Time FIXED_FRAME_TIME = sf::seconds(1 / 60.0f);
			sf::Time timeSinceLastUpdate = sf::Time::Zero;
			sf::Clock clock;

		public:

		    Application() = default;
		    virtual ~Application() = default;
			virtual void Run() = 0;
			virtual void Quit() = 0;
			virtual bool IsRunning() = 0;
			virtual abyss::Assets &GetAssets() = 0;
			virtual sf::RenderWindow &GetWindow() = 0;
			virtual const float DeltaTime() const = 0;

			virtual void ChangeScene(const std::string &sceneName, std::shared_ptr<abyss::Scene> scene,
							 bool endCurrentScene = false) { };

		protected:
			virtual void Init(const std::string &configPath, const std::string &assetsPath) = 0;
			virtual void Update() = 0;
			virtual void UserInputSystem() = 0;

			virtual std::shared_ptr<abyss::Scene> GetCurrentScene() { return nullptr; };
	};
}

#endif // !APPLICATION_H
