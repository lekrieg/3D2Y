#include "MenuScene.h"

#include "PlayScene.h"
#include "../managers/AudioManager.h"
#include "../imgui/imgui-SFML.h"
#include "SFML/Graphics/Text.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Keyboard.hpp"

void core::MenuScene::Init(const std::string& configPath)
{
	if (!m_gameApplication->GetAudioManager()->IsMusicPlaying())
	{
		m_gameApplication->GetAudioManager()->PlayMusic("MainMusic");
	}

	RegisterAction(sf::Keyboard::Key::W, "GO_UP");
	RegisterAction(sf::Keyboard::Key::S, "GO_DOWN");
	RegisterAction(sf::Keyboard::Key::D, "PLAY");
	RegisterAction(sf::Keyboard::Key::Escape, "QUIT");

	m_menuStrings.emplace_back("Assignment 4");
	m_menuStrings.emplace_back("Test level");

	m_menuTitleText.setFont(m_gameApplication->GetAssets().GetFont("elementalis"));
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
		m_levelList.emplace_back(sf::Text(m_gameApplication->GetAssets().GetFont("elementalis"), m_menuStrings[i], 24.0f));
		m_levelList.at(i - 1).setFillColor(sf::Color::Green);
		m_levelList.at(i - 1).setPosition(sf::Vector2<float>(20.0f, yOffsetPos));


		//if (m_gameApplication->GetGameManager().clearedLevels.at(i - 1))
		//{
		//	cleared = "CLEARED";
		//	c = sf::Color::Green;
		//}
		//else
		//{
		//	cleared = "UNCLEARED";
		//	c = sf::Color::Red;
		//}

		yOffsetPos += 30.0f;
	}
}

void core::MenuScene::Update(float deltaTime)
{
}

void core::MenuScene::Render()
{
	if (!m_paused)
	{
		m_gameApplication->GetWindow().clear(sf::Color::Black);
	}
	else
	{
		m_gameApplication->GetWindow().clear(sf::Color(104, 104, 104));
	}

	m_gameApplication->GetWindow().draw(m_menuTitleText);
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

		m_gameApplication->GetWindow().draw(m_levelList.at(i));
	}

	ImGui::SFML::Render(m_gameApplication->GetWindow());

	m_gameApplication->GetWindow().display();
}

void core::MenuScene::OnEnd()
{
	m_gameApplication->Quit();
}

void core::MenuScene::ExecuteAction(const core::Action& action)
{
	if (action.State() == core::ActionState::Start)
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
			std::string levelPath = "scenes/scene" + std::to_string(m_menuIndex) + ".txt";
			m_gameApplication->GetGameManager().sceneIndex = m_menuIndex;
			m_gameApplication->ChangeScene("PLAY", std::make_shared<core::PlayScene>(m_gameApplication, levelPath, m_gameApplication->GetAssets().GetFont("elementalis")));
		}
		else if (action.Name() == "QUIT")
		{
			OnEnd();
		}
	}
}
