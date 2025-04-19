#include "EditorApplication.h"

#include "Action.h"
#include "ActionState.h"
#include "Logger.h"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Mouse.hpp"
#include "SFML/Window/VideoMode.hpp"
#include "imgui/imgui-SFML.h"
#include "imgui/imgui.h"
#include "math/Vectors.h"
#include "scenes/EditorScene.h"
#include <optional>

void editor::EditorApplication::Init(const std::string &configPath, const std::string &assetsPath)
{
	m_assets.LoadFromFile(assetsPath);

	m_window.create(sf::VideoMode(sf::Vector2u(1024, 768)), "Level Editor", sf::Style::Titlebar | sf::Style::Close);

	m_scene = std::make_shared<editor::EditorScene>(this, "", GetAssets().GetFont("elementalis"));

	if (!ImGui::SFML::Init(m_window))
	{
		ABYSS_ERROR("ImGui SFML initialization problem!");
	}
}

editor::EditorApplication::~EditorApplication()
{
	ImGui::SFML::Shutdown();
}

void editor::EditorApplication::Run()
{
	while (IsRunning())
	{
		ImGui::SFML::Update(m_window, FIXED_FRAME_TIME);

		Update();
	}
}

void editor::EditorApplication::Update()
{
	sf::Time clockTime = clock.restart();
	timeSinceLastUpdate += clockTime;

	while (timeSinceLastUpdate > FIXED_FRAME_TIME)
	{
		timeSinceLastUpdate -= FIXED_FRAME_TIME;

		UserInputSystem();
		m_scene->Update(DeltaTime());
	}

	m_scene->EntityInfoGui();
	m_scene->AssetManagerGui();
	m_scene->SceneManagerGui();
	m_scene->InspectorGui();

	m_scene->Render();
}

void editor::EditorApplication::Quit()
{
	m_running = false;
}

bool editor::EditorApplication::IsRunning()
{
	return m_running && m_window.isOpen();
}

abyss::Assets &editor::EditorApplication::GetAssets()
{
	return m_assets;
}

sf::RenderWindow &editor::EditorApplication::GetWindow()
{
	return m_window;
}

const float editor::EditorApplication::DeltaTime() const
{
	return FIXED_FRAME_TIME.asSeconds();
}

void editor::EditorApplication::UserInputSystem()
{
	while (const std::optional event = m_window.pollEvent())
	{
		ImGui::SFML::ProcessEvent(m_window, *event);

		const auto *keyPressed = event->getIf<sf::Event::KeyPressed>();
		const auto *keyReleased = event->getIf<sf::Event::KeyReleased>();
		const auto *mousePressed = event->getIf<sf::Event::MouseButtonPressed>();
		const auto *mouseReleased = event->getIf<sf::Event::MouseButtonReleased>();
		const auto *mouseMoved = event->getIf<sf::Event::MouseMoved>();
		const auto *mouseWheelScrolled = event->getIf<sf::Event::MouseWheelScrolled>();

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
			if (m_scene->GetActionMap().find(keyPressed->code) == m_scene->GetActionMap().end())
			{
				continue;
			}

			m_scene->ExecuteAction(
				abyss::Action(m_scene->GetActionMap().at(keyPressed->code), abyss::ActionState::Start));
		}
		else if (keyReleased)
		{
			if (m_scene->GetActionMap().find(keyReleased->code) == m_scene->GetActionMap().end())
			{
				continue;
			}

			m_scene->ExecuteAction(
				abyss::Action(m_scene->GetActionMap().at(keyReleased->code), abyss::ActionState::End));
		}

		if (!ImGui::GetIO().WantCaptureMouse)
		{
			sf::Vector2i foo = sf::Mouse::getPosition(m_window);
			abyss::math::Vec2<int> mousePosition(foo.x, foo.y);

			if (mousePressed)
			{
				const abyss::ActionState actionState = abyss::ActionState::Start;

				switch (mousePressed->button)
				{
					case sf::Mouse::Button::Left:
					{
						m_scene->ExecuteAction(abyss::Action("LEFT_CLICK", actionState, mousePosition));
						break;
					};
					case sf::Mouse::Button::Right:
					{
						m_scene->ExecuteAction(abyss::Action("RIGHT_CLICK", actionState, mousePosition));
						break;
					};
					case sf::Mouse::Button::Middle:
					{
						m_scene->ExecuteAction(abyss::Action("MIDDLE_CLICK", actionState, mousePosition));
						break;
					};
					default:
						break;
				}
			}

			if (mouseReleased)
			{
				const abyss::ActionState actionState = abyss::ActionState::End;

				switch (mouseReleased->button)
				{
					case sf::Mouse::Button::Left:
					{
						m_scene->ExecuteAction(abyss::Action("LEFT_CLICK", actionState, mousePosition));
						break;
					};
					case sf::Mouse::Button::Right:
					{
						m_scene->ExecuteAction(abyss::Action("RIGHT_CLICK", actionState, mousePosition));
						break;
					};
					case sf::Mouse::Button::Middle:
					{
						m_scene->ExecuteAction(abyss::Action("MIDDLE_CLICK", actionState, mousePosition));
						break;
					};
					default:
						break;
				}
			}

			if (mouseMoved)
			{
				m_scene->ExecuteAction(abyss::Action("MOUSE_MOVE", abyss::ActionState::Start, abyss::math::Vec2<int>(mouseMoved->position.x, mouseMoved->position.y)));
			}

			if (mouseWheelScrolled)
			{
				m_scene->ExecuteAction(abyss::Action(
					"ZOOM", abyss::ActionState::Start,
					abyss::math::Vec2<int>(mouseWheelScrolled->position.x, mouseWheelScrolled->position.y),
					mouseWheelScrolled->delta));
			}
		}
	}
}
