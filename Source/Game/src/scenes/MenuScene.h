#ifndef MENU_SCENE_H
#define MENU_SCENE_H

#include "Scene.h"

#include <SFML/Graphics/Text.hpp>
#include <string>
#include <vector>

namespace game
{
	class MenuScene : public abyss::Scene
	{
			std::string m_title;
			std::vector<std::string> m_menuStrings;
			std::vector<std::string> m_levelPaths;
			sf::Text m_menuTitleText;
			std::vector<sf::Text> m_levelList;
			int m_menuIndex = 0;

		protected:

			void Init(const std::string &configPath) override;
			void OnEnd() override;

		public:

			MenuScene(abyss::Application *gameApplication = nullptr) :
				abyss::Scene(gameApplication),
				m_menuTitleText(m_application->GetAssets().GetFont("elementalis"))
			{
				Init("");
			}

			void Update(float deltaTime) override;
			void Render() override;
			void ExecuteAction(const abyss::Action &action) override;
	};
}

#endif // !MENU_SCENE_H
