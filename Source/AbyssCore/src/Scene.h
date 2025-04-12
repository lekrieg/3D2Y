#ifndef SCENE_H
#define SCENE_H

#include "Action.h"
#include "EntityManager.h"

#include "Application.h"
#include "SFML/Window/Keyboard.hpp"

namespace abyss
{
	class Application;

	class Scene
	{
	protected:

		Application* m_application;
		EntityManager m_entityManager;
		std::map<sf::Keyboard::Key, std::string> m_actionMap;
		bool m_paused = false;
		bool m_hasEnded = false;
		float m_deltaTime = 0.0f;

		virtual void OnEnd() = 0;

		void SetPaused(bool paused)
		{
			m_paused = paused;
		}

		virtual void Init(const std::string& levelPath) = 0;

	public:
		Scene()
		{

		}

		Scene(Application* application = nullptr) : m_application(application)
		{

		}

		~Scene() = default;

		virtual void Update(float deltaTime) = 0;
		virtual void ExecuteAction(const Action& action) = 0;
		virtual void Render() = 0;

		void RegisterAction(sf::Keyboard::Key inputKey, const std::string& actionName)
		{
			m_actionMap[inputKey] = actionName;
		}

		int Width() const;

		int Height() const;

		bool HasEnded() const
		{
			return m_hasEnded;
		}

		const std::map<sf::Keyboard::Key, std::string>& GetActionMap() const
		{
			return m_actionMap;
		}

		void DrawLine(sf::Vector2f p1, sf::Vector2f p2);
	};
}

#endif // !SCENE_H
