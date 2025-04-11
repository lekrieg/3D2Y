#include "MenuScene.h"

#include "SFML/Graphics/Text.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Keyboard.hpp"

void game::MenuScene::Init(const std::string &configPath)
{
	// if (!m_application->GetAudioManager()->IsMusicPlaying())
	// {
	// 	m_application->GetAudioManager()->PlayMusic("MainMusic");
	// }

	RegisterAction(sf::Keyboard::Key::W, "GO_UP");
	RegisterAction(sf::Keyboard::Key::S, "GO_DOWN");
	RegisterAction(sf::Keyboard::Key::D, "PLAY");
	RegisterAction(sf::Keyboard::Key::Escape, "QUIT");

	m_menuStrings.emplace_back("Assignment 4");
	m_menuStrings.emplace_back("Test level");

	m_menuTitleText.setFont(m_application->GetAssets().GetFont("elementalis"));
	m_menuTitleText.setFillColor(sf::Color::White);
	m_menuTitleText.setCharacterSize(32.0f);
	m_menuTitleText.setString(m_menuStrings[0]);
	m_menuTitleText.setPosition(sf::Vector2<float>(20.0f, 20.0f));

	float yOffsetPos = 100.0f;
	float xOffsetPos = 50.0f;
	std::string cleared = "";
	sf::Color c;
	for (int i = 1; i <= m_menuStrings.size() - 1; i++)
	{
		m_levelList.emplace_back(sf::Text(m_application->GetAssets().GetFont("elementalis"), m_menuStrings[i], 24.0f));
		m_levelList.at(i - 1).setFillColor(sf::Color::Green);
		m_levelList.at(i - 1).setPosition(sf::Vector2<float>(20.0f, yOffsetPos));

		// if (m_application->GetGameManager().clearedLevels.at(i - 1))
		//{
		//	cleared = "CLEARED";
		//	c = sf::Color::Green;
		// }
		// else
		//{
		//	cleared = "UNCLEARED";
		//	c = sf::Color::Red;
		// }

		yOffsetPos += 30.0f;
	}
}

void game::MenuScene::Update(float deltaTime)
{
}

void game::MenuScene::Render()
{
	if (!m_paused)
	{
		m_application->GetWindow().clear(sf::Color::Black);
	}
	else
	{
		m_application->GetWindow().clear(sf::Color(104, 104, 104));
	}

	m_application->GetWindow().draw(m_menuTitleText);
	for (int i = 0; i < m_levelList.size(); i++)
	{
		if (i == m_menuIndex)
		{
			m_levelList.at(i).setFillColor(sf::Color(104, 104, 150));
		}
		else
		{
			m_levelList.at(i).setFillColor(sf::Color::White);
		}

		m_application->GetWindow().draw(m_levelList.at(i));
	}

	m_application->GetWindow().display();
}

void game::MenuScene::OnEnd()
{
	m_application->Quit();
}

void game::MenuScene::ExecuteAction(const abyss::Action &action)
{
	if (action.State() == abyss::ActionState::Start)
	{
		if (action.Name() == "GO_DOWN")
		{
			m_menuIndex++;
			if (m_menuIndex > m_levelList.size() - 1)
			{
				m_menuIndex = 0;
			}
		}
		else if (action.Name() == "GO_UP")
		{
			m_menuIndex--;
			if (m_menuIndex < 0)
			{
				m_menuIndex = m_levelList.size() - 1;
			}
		}
		else if (action.Name() == "PLAY")
		{
			// std::string levelPath = "scenes/scene" + std::to_string(m_menuIndex) + ".txt";
			// m_application->GetGameManager().sceneIndex = m_menuIndex;
			// m_application->ChangeScene("PLAY", std::make_shared<game::PlayScene>(m_application, levelPath,
			// m_application->GetAssets().GetFont("elementalis")));
		}
		else if (action.Name() == "QUIT")
		{
			OnEnd();
		}
	}
}
