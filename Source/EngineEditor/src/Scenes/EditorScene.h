// #ifndef GAME_APPLICATION_H
// #define GAME_APPLICATION_H

// #include "FileData.h"
// #include "SFML/Window/Event.hpp"
// #include "SFML/Window/Keyboard.hpp"
// #include "Assets.h"
// #include "Scene.h"
// #include "managers/AudioManager.h"
// #include "managers/GameManager.h"

// #include <memory>

// namespace game
// {
// 	class Scene;
// 	class AudioManager;

// 	class GameApplication
// 	{
// 			game::GameManager m_gameManager;
// 			game::AudioManager *m_audioManager; // TODO: think in a better way to make this stuff

// 			std::map<std::string, std::shared_ptr<abyss::Scene>> m_scenes;
// 			sf::RenderWindow m_window;
// 			abyss::Assets m_assets;
// 			std::string m_currentScene;
// 			int m_simulationSpeed = 1;
// 			bool m_running = true;

// 			// DeltaTime stuff
// 			sf::Time FIXED_FRAME_TIME = sf::seconds(1 / 60.0f);
// 			sf::Time timeSinceLastUpdate = sf::Time::Zero;
// 			sf::Clock clock;

// 		public:

// 			GameApplication(const std::string &configPath, const std::string &assetsPath)
// 			{
// 				Init(configPath, assetsPath);
// 			}

// 			~GameApplication();

// 			void Run();
// 			void Quit();
// 			bool IsRunning();
// 			game::AudioManager *GetAudioManager();
// 			abyss::Assets &GetAssets();
// 			sf::RenderWindow &GetWindow();
// 			game::GameManager &GetGameManager();
// 			const float DeltaTime() const;

// 			void ChangeScene(const std::string &sceneName, std::shared_ptr<abyss::Scene> scene,
// 							 bool endCurrentScene = false);

// 		private:

// 			void Init(const std::string &configPath, const std::string &assetsPath);
// 			void Update();

// 			std::shared_ptr<abyss::Scene> GetCurrentScene();

// 			void UserInputSystem();
// 	};
// }

// #endif // !GAME_APPLICATION_H
