#include "GameApplication.h"

#include "ActionState.h"
#include "Logger.h"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Mouse.hpp"
#include "SFML/Window/VideoMode.hpp"
#include "scenes/PlayScene.h"
#include "managers/AudioManager.h"
#include <optional>

void game::GameApplication::Init(const std::string &configPath, const std::string &assetsPath)
{
	m_audioManager = new game::AudioManager(this);

	// TODO: checar se e possivel substituir isso pelo resource manager do livro
	// TODO: read config file and fill the config things(windows size and etc)
	m_assets.LoadFromFile(assetsPath);

	m_window.create(sf::VideoMode(sf::Vector2u(800, 600)), "Assignment 3", sf::Style::Titlebar | sf::Style::Close);

	// TODO: add an option on settings to allow user limit this / activate VSync
	// m_window.setFramerateLimit(60);

	// ChangeScene("MENU", std::make_shared<scene::MenuScene>(this)); -> TODO: finish the menu level
	// ChangeScene("MENU", std::make_shared<game::MenuScene>(this));
	ChangeScene("PLAY",
				std::make_shared<game::PlayScene>(this, "scenes/testScene.txt", GetAssets().GetFont("elementalis")));
}

game::GameApplication::~GameApplication()
{
	delete m_audioManager;
}

void game::GameApplication::Run()
{
	// TODO: Check if this run is really necessary, I could just use update...
	while (IsRunning())
	{
		Update();
	}
}

void game::GameApplication::Update()
{
	sf::Time clockTime = clock.restart();
	timeSinceLastUpdate += clockTime;

	while (timeSinceLastUpdate > FIXED_FRAME_TIME)
	{
		timeSinceLastUpdate -= FIXED_FRAME_TIME;

		UserInputSystem();
		m_scenes[m_currentScene]->Update(DeltaTime());
	}

	m_scenes[m_currentScene]->Render();
}

void game::GameApplication::Quit()
{
	// TODO: check later if I am in a level

	m_running = false;
}

bool game::GameApplication::IsRunning()
{
	return m_running && m_window.isOpen();
}

game::AudioManager *game::GameApplication::GetAudioManager()
{
	return m_audioManager;
}

abyss::Assets &game::GameApplication::GetAssets()
{
	return m_assets;
}

sf::RenderWindow &game::GameApplication::GetWindow()
{
	return m_window;
}

game::GameManager &game::GameApplication::GetGameManager()
{
	return m_gameManager;
}

const float game::GameApplication::DeltaTime() const
{
	return FIXED_FRAME_TIME.asSeconds();
}

void game::GameApplication::ChangeScene(const std::string &sceneName, std::shared_ptr<abyss::Scene> scene,
										bool endCurrentScene)
{
	// TODO: transform this in a helper method that I can call to reset the view
	sf::View view = GetWindow().getView();
	view.setCenter(sf::Vector2<float>(GetWindow().getSize().x / 2.0f, GetWindow().getSize().y / 2.0f));
	GetWindow().setView(view);

	m_scenes[sceneName] = scene;
	// TODO: reset the old scene
	m_currentScene = sceneName;
}

std::shared_ptr<abyss::Scene> game::GameApplication::GetCurrentScene()
{
	return m_scenes[m_currentScene];
}

void game::GameApplication::UserInputSystem()
{
	while (const std::optional event = m_window.pollEvent())
	{
		const auto *keyPressed = event->getIf<sf::Event::KeyPressed>();
		const auto *keyReleased = event->getIf<sf::Event::KeyReleased>();
		const auto *mousePressed = event->getIf<sf::Event::MouseButtonPressed>();
		const auto *mouseReleased = event->getIf<sf::Event::MouseButtonReleased>();

		if (event->is<sf::Event::Closed>())
		{
			Quit();
		}

		/*if (event.type == sf::Event::Resized)
		{
			m_window.setView(sf::View(sf::FloatRect(0.f, 0.f, m_window.getView().getViewport().width,
		m_window.getView().getViewport().height)));
		}*/
		if (const auto *resized = event->getIf<sf::Event::Resized>())
		{
			sf::FloatRect view(sf::Rect(sf::Vector2<int>(0, 0), sf::Vector2<int>(resized->size.x, resized->size.y)));
			m_window.setView(sf::View(view));
		}

		if (keyPressed)
		{
			if (keyPressed->code == sf::Keyboard::Key::X)
			{
				std::cout << "screenshot save to" << "test.png" << std::endl;
				sf::Texture texture;
				if (!texture.resize(sf::Vector2u(m_window.getSize().x, m_window.getSize().y)))
				{
					ABYSS_ERROR("Texture resing problem!");
				}

				texture.update(m_window);

				if (texture.copyToImage().saveToFile("test.png"))
				{
					ABYSS_INFO("Screenshot saved to test.png");
				}
			}
		}

		if (keyPressed)
		{
			if (GetCurrentScene()->GetActionMap().find(keyPressed->code) == GetCurrentScene()->GetActionMap().end())
			{
				continue;
			}

			GetCurrentScene()->ExecuteAction(
				abyss::Action(GetCurrentScene()->GetActionMap().at(keyPressed->code), abyss::ActionState::Start));
		}
		else if (keyReleased)
		{
			if (GetCurrentScene()->GetActionMap().find(keyReleased->code) == GetCurrentScene()->GetActionMap().end())
			{
				continue;
			}

			GetCurrentScene()->ExecuteAction(
				abyss::Action(GetCurrentScene()->GetActionMap().at(keyReleased->code), abyss::ActionState::End));
		}

		if (mousePressed)
		{
			const abyss::ActionState actionState = abyss::ActionState::Start;

			sf::Vector2i foo = sf::Mouse::getPosition(m_window);
			// window().mapPixelToCoords(action.pos());

			abyss::math::Vec2<int> mousePosition(foo.x, foo.y);
			switch (mousePressed->button)
			{
				case sf::Mouse::Button::Left:
				{
					GetCurrentScene()->ExecuteAction(abyss::Action("LEFT_CLICK", actionState, mousePosition));
					break;
				};
				case sf::Mouse::Button::Right:
				{
					GetCurrentScene()->ExecuteAction(abyss::Action("RIGHT_CLICK", actionState, mousePosition));
					break;
				};
				case sf::Mouse::Button::Middle:
				{
					GetCurrentScene()->ExecuteAction(abyss::Action("MIDDLE_CLICK", actionState, mousePosition));
					break;
				};
				default:
					break;
			}
		}

		if (mouseReleased)
		{
			const abyss::ActionState actionState = abyss::ActionState::End;

			sf::Vector2i foo = sf::Mouse::getPosition(m_window);
			// window().mapPixelToCoords(action.pos());

			abyss::math::Vec2<int> mousePosition(foo.x, foo.y);
			switch (mouseReleased->button)
			{
				case sf::Mouse::Button::Left:
				{
					GetCurrentScene()->ExecuteAction(abyss::Action("LEFT_CLICK", actionState, mousePosition));
					break;
				};
				case sf::Mouse::Button::Right:
				{
					GetCurrentScene()->ExecuteAction(abyss::Action("RIGHT_CLICK", actionState, mousePosition));
					break;
				};
				case sf::Mouse::Button::Middle:
				{
					GetCurrentScene()->ExecuteAction(abyss::Action("MIDDLE_CLICK", actionState, mousePosition));
					break;
				};
				default:
					break;
			}
		}
	}
}
