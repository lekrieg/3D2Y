#ifndef SCENE_H
#define SCENE_H

#include "Action.h"
#include "EntityManager.h"
#include "Logger.h"
#include "serialization/Serializer.h"

#include "Application.h"
#include "SFML/Window/Keyboard.hpp"
#include <fstream>

namespace abyss
{
	class Application;

	class Scene
	{
		protected:

			Application *m_application;
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

			virtual void Init(const std::string &levelPath) = 0;

		public:

			Scene()
			{
			}

			Scene(Application *application = nullptr) : m_application(application)
			{
			}

			~Scene() = default;

			virtual void Update(float deltaTime) = 0;
			virtual void ExecuteAction(const Action &action) = 0;
			virtual void Render() = 0;

			void RegisterAction(sf::Keyboard::Key inputKey, const std::string &actionName)
			{
				m_actionMap[inputKey] = actionName;
			}

			int Width() const;

			int Height() const;

			bool HasEnded() const
			{
				return m_hasEnded;
			}

			const std::map<sf::Keyboard::Key, std::string> &GetActionMap() const
			{
				return m_actionMap;
			}

			void DrawLine(sf::Vector2f p1, sf::Vector2f p2);

			inline void Serialize(const std::string &path)
			{
				YAML::Emitter emitter;
				emitter << YAML::BeginMap;
				abyss::serializer::Serializer(&m_entityManager).serialize(emitter);
				emitter << YAML::EndMap;

				std::ofstream filepath(path);
				filepath << emitter.c_str();
			}

			inline bool Deserialize(const std::string &path)
			{
				YAML::Node root;
				try
				{
					root = YAML::LoadFile(path);
				}
				catch (YAML::ParserException e)
				{
					ABYSS_ERROR("Failed to deserialize scene!");
					return false;
				}

				if (auto entities = root["entities"])
				{
					abyss::serializer::Serializer(&m_entityManager).Deserialize(entities);
					return true;
				}

				return false;
			}
	};
}

#endif // !SCENE_H
