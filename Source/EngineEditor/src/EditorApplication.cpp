#include "EditorApplication.h"

#include "Action.h"
#include "Enums.h"
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

	m_scene = std::make_shared<editor::EditorScene>(this, "", GetAssets().GetFonts()["Default"]);

	if (!ImGui::SFML::Init(m_window))
	{
		ABYSS_ERROR("ImGui SFML initialization problem!");
		return;
	}

	ConfigImGuiStyle();
}

editor::EditorApplication::~EditorApplication()
{
	ImGui::SFML::Shutdown();
}

void editor::EditorApplication::Run()
{
	while (IsRunning())
	{
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

	ImGui::SFML::Update(m_window, clockTime);

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
				abyss::Action(m_scene->GetActionMap().at(keyPressed->code), abyss::enums::ActionState::Start));
		}
		else if (keyReleased)
		{
			if (m_scene->GetActionMap().find(keyReleased->code) == m_scene->GetActionMap().end())
			{
				continue;
			}

			m_scene->ExecuteAction(
				abyss::Action(m_scene->GetActionMap().at(keyReleased->code), abyss::enums::ActionState::End));
		}

		// TODO: try to block user input when focus on imgui
		if (!ImGui::GetIO().WantCaptureMouse)
		{
			sf::Vector2i foo = sf::Mouse::getPosition(m_window);
			abyss::math::Vec2<int> mousePosition(foo.x, foo.y);

			if (mousePressed)
			{
				const abyss::enums::ActionState actionState = abyss::enums::ActionState::Start;

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
				const abyss::enums::ActionState actionState = abyss::enums::ActionState::End;

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
				m_scene->ExecuteAction(abyss::Action("MOUSE_MOVE", abyss::enums::ActionState::Start, abyss::math::Vec2<int>(mouseMoved->position.x, mouseMoved->position.y)));
			}

			if (mouseWheelScrolled)
			{
				m_scene->ExecuteAction(abyss::Action(
					"ZOOM", abyss::enums::ActionState::Start,
					abyss::math::Vec2<int>(mouseWheelScrolled->position.x, mouseWheelScrolled->position.y),
					mouseWheelScrolled->delta));
			}
		}
	}
}

void editor::EditorApplication::ConfigImGuiStyle()
{
	ImGuiStyle* style = &ImGui::GetStyle();
	ImVec4* colors = style->Colors;

	// Base colors for a pleasant and modern dark theme with dark accents
	colors[ImGuiCol_Text] = ImVec4(0.92f, 0.93f, 0.94f, 1.00f);                  // Light grey text for readability
	colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.52f, 0.54f, 1.00f);          // Subtle grey for disabled text
	colors[ImGuiCol_WindowBg] = ImVec4(0.14f, 0.14f, 0.16f, 1.00f);              // Dark background with a hint of blue
	colors[ImGuiCol_ChildBg] = ImVec4(0.16f, 0.16f, 0.18f, 1.00f);               // Slightly lighter for child elements
	colors[ImGuiCol_PopupBg] = ImVec4(0.18f, 0.18f, 0.20f, 1.00f);               // Popup background
	colors[ImGuiCol_Border] = ImVec4(0.28f, 0.29f, 0.30f, 0.60f);                // Soft border color
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);          // No border shadow
	colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.22f, 0.24f, 1.00f);               // Frame background
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.22f, 0.24f, 0.26f, 1.00f);        // Frame hover effect
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.24f, 0.26f, 0.28f, 1.00f);         // Active frame background
	colors[ImGuiCol_TitleBg] = ImVec4(0.14f, 0.14f, 0.16f, 1.00f);               // Title background
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.16f, 0.16f, 0.18f, 1.00f);         // Active title background
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.14f, 0.14f, 0.16f, 1.00f);      // Collapsed title background
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.20f, 0.20f, 0.22f, 1.00f);             // Menu bar background
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.16f, 0.16f, 0.18f, 1.00f);           // Scrollbar background
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.24f, 0.26f, 0.28f, 1.00f);         // Dark accent for scrollbar grab
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.28f, 0.30f, 0.32f, 1.00f);  // Scrollbar grab hover
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.32f, 0.34f, 0.36f, 1.00f);   // Scrollbar grab active
	colors[ImGuiCol_CheckMark] = ImVec4(0.46f, 0.56f, 0.66f, 1.00f);             // Dark blue checkmark
	colors[ImGuiCol_SliderGrab] = ImVec4(0.36f, 0.46f, 0.56f, 1.00f);            // Dark blue slider grab
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.40f, 0.50f, 0.60f, 1.00f);      // Active slider grab
	colors[ImGuiCol_Button] = ImVec4(0.24f, 0.34f, 0.44f, 1.00f);                // Dark blue button
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.28f, 0.38f, 0.48f, 1.00f);         // Button hover effect
	colors[ImGuiCol_ButtonActive] = ImVec4(0.32f, 0.42f, 0.52f, 1.00f);          // Active button
	colors[ImGuiCol_Header] = ImVec4(0.24f, 0.34f, 0.44f, 1.00f);                // Header color similar to button
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.28f, 0.38f, 0.48f, 1.00f);         // Header hover effect
	colors[ImGuiCol_HeaderActive] = ImVec4(0.32f, 0.42f, 0.52f, 1.00f);          // Active header
	colors[ImGuiCol_Separator] = ImVec4(0.28f, 0.29f, 0.30f, 1.00f);             // Separator color
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.46f, 0.56f, 0.66f, 1.00f);      // Hover effect for separator
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.46f, 0.56f, 0.66f, 1.00f);       // Active separator
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.36f, 0.46f, 0.56f, 1.00f);            // Resize grip
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.40f, 0.50f, 0.60f, 1.00f);     // Hover effect for resize grip
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.44f, 0.54f, 0.64f, 1.00f);      // Active resize grip
	colors[ImGuiCol_Tab] = ImVec4(0.20f, 0.22f, 0.24f, 1.00f);                   // Inactive tab
	colors[ImGuiCol_TabHovered] = ImVec4(0.28f, 0.38f, 0.48f, 1.00f);            // Hover effect for tab
	colors[ImGuiCol_TabActive] = ImVec4(0.24f, 0.34f, 0.44f, 1.00f);             // Active tab color
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.20f, 0.22f, 0.24f, 1.00f);          // Unfocused tab
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.24f, 0.34f, 0.44f, 1.00f);    // Active but unfocused tab
	colors[ImGuiCol_PlotLines] = ImVec4(0.46f, 0.56f, 0.66f, 1.00f);             // Plot lines
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.46f, 0.56f, 0.66f, 1.00f);      // Hover effect for plot lines
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.36f, 0.46f, 0.56f, 1.00f);         // Histogram color
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.40f, 0.50f, 0.60f, 1.00f);  // Hover effect for histogram
	colors[ImGuiCol_TableHeaderBg] = ImVec4(0.20f, 0.22f, 0.24f, 1.00f);         // Table header background
	colors[ImGuiCol_TableBorderStrong] = ImVec4(0.28f, 0.29f, 0.30f, 1.00f);     // Strong border for tables
	colors[ImGuiCol_TableBorderLight] = ImVec4(0.24f, 0.25f, 0.26f, 1.00f);      // Light border for tables
	colors[ImGuiCol_TableRowBg] = ImVec4(0.20f, 0.22f, 0.24f, 1.00f);            // Table row background
	colors[ImGuiCol_TableRowBgAlt] = ImVec4(0.22f, 0.24f, 0.26f, 1.00f);         // Alternate row background
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.24f, 0.34f, 0.44f, 0.35f);        // Selected text background
	colors[ImGuiCol_DragDropTarget] = ImVec4(0.46f, 0.56f, 0.66f, 0.90f);        // Drag and drop target
	colors[ImGuiCol_NavHighlight] = ImVec4(0.46f, 0.56f, 0.66f, 1.00f);          // Navigation highlight
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f); // Windowing highlight
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);     // Dim background for windowing
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);      // Dim background for modal windows

	// Style adjustments
	style->WindowPadding = ImVec2(8.00f, 8.00f);
	style->FramePadding = ImVec2(5.00f, 2.00f);
	style->CellPadding = ImVec2(6.00f, 6.00f);
	style->ItemSpacing = ImVec2(6.00f, 6.00f);
	style->ItemInnerSpacing = ImVec2(6.00f, 6.00f);
	style->TouchExtraPadding = ImVec2(0.00f, 0.00f);
	style->IndentSpacing = 25;
	style->ScrollbarSize = 11;
	style->GrabMinSize = 10;
	style->WindowBorderSize = 1;
	style->ChildBorderSize = 1;
	style->PopupBorderSize = 1;
	style->FrameBorderSize = 1;
	style->TabBorderSize = 1;
	style->WindowRounding = 7;
	style->ChildRounding = 4;
	style->FrameRounding = 3;
	style->PopupRounding = 4;
	style->ScrollbarRounding = 9;
	style->GrabRounding = 3;
	style->LogSliderDeadzone = 4;
	style->TabRounding = 4;
}
