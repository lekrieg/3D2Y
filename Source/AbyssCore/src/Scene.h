#ifndef SCENE_H
#define SCENE_H

#include "Action.h"
#include "EntityManager.h"

#include "../GameApplication.h"
#include "SFML/Window/Keyboard.hpp"

namespace core
{
	class GameApplication;

	class Scene
	{
	protected:

		GameApplication* m_gameApplication;
		EntityManager m_entityManager;
		std::shared_ptr<core::Entity> m_selectedEntity;
		std::map<sf::Keyboard::Key, std::string> m_actionMap;
		bool m_paused = false;
		bool m_hasEnded = false;
		bool m_isEntityInfoOpen = false;
		bool m_isAssetManagerOpen = false;
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

		Scene(GameApplication* gameApplication = nullptr) : m_gameApplication(gameApplication)
		{

		}

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

		void EntityInfoGui();
		void AssetManagerGui();
	};
}

#endif // !SCENE_H
