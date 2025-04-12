#include "EditorScene.h"

#include "Action.h"

#include "components/Anim.h"
#include "components/Transform.h"

#include "Logger.h"

#include "../imgui/imgui-SFML.h"
#include "SFML/Graphics/View.hpp"
#include "SFML/System/Angle.hpp"
#include "SFML/System/Vector2.hpp"
#include <cmath>
#include <cstdlib>
#include <math.h>
#include <string>

void editor::EditorScene::Update(float deltaTime)
{
	m_entityManager.Update();

	if (!m_paused)
	{
		CameraSystem();
	}

	AnimationSystem();
}

void editor::EditorScene::Init(const std::string &levelPath)
{
	RegisterAction(sf::Keyboard::Key::P, "PAUSE");
	RegisterAction(sf::Keyboard::Key::Escape, "QUIT");
	RegisterAction(sf::Keyboard::Key::T, "TOGGLE_TEXTURE");
	RegisterAction(sf::Keyboard::Key::C, "TOGGLE_COLLISION");
	RegisterAction(sf::Keyboard::Key::G, "TOGGLE_GRID");
	RegisterAction(sf::Keyboard::Key::Y, "TOGGLE_CAMERA_TYPE");
	RegisterAction(sf::Keyboard::Key::A, "TO_LEFT");
	RegisterAction(sf::Keyboard::Key::D, "TO_RIGHT");
	RegisterAction(sf::Keyboard::Key::W, "TO_UP");
	RegisterAction(sf::Keyboard::Key::S, "TO_DOWN");
	RegisterAction(sf::Keyboard::Key::Num1, "TOGGLE_ASSET_MANAGER");

	LoadLevel(levelPath);
}

void editor::EditorScene::LoadLevel(const std::string &fileName)
{
	ABYSS_INFO("Info...");
	ABYSS_WARNING("Warning...");
	ABYSS_ERROR("Error...");

	// TODO: Check how to better reset the manager
	m_entityManager = abyss::EntityManager();

	// std::ifstream ifs(fileName, std::ifstream::in);

	// std::string itemType;
	// while (ifs.good())
	// {
	// 	ifs >> itemType;
	// 	if (itemType.compare("Player") == 0)
	// 	{
	// 		ifs >> m_playerInfo.gridLocation.x >> m_playerInfo.gridLocation.y >> m_playerInfo.boundingBoxSize.x >>
	// 			m_playerInfo.boundingBoxSize.y >> m_playerInfo.speed.x >> m_playerInfo.speed.y >>
	// 			m_playerInfo.maxSpeed >> m_playerInfo.gravity >> m_playerInfo.bulletAnimation;
	// 	}
	// }
}

sf::Vector2f editor::EditorScene::GridToMidPixel(float gridX, float gridY, std::shared_ptr<abyss::Entity> entity)
{
	auto &spriteSize = entity->GetComponent<abyss::components::Anim>().animation.GetSize();
	return sf::Vector2f((gridX * m_gridSize.x) + (spriteSize.x / 2.0f),
						Height() - ((gridY * m_gridSize.y) + (spriteSize.y / 2.0f)));
}

void editor::EditorScene::Render()
{
	if (!m_paused)
	{
		m_application->GetWindow().clear(sf::Color::Black);
	}
	else
	{
		m_application->GetWindow().clear(sf::Color(104, 104, 104));
	}

	for (auto e : m_entityManager.GetEntities())
	{
		if (m_drawTextures)
		{
			auto &transform = e->GetComponent<abyss::components::Transform>();
			if (e->HasComponent<abyss::components::Anim>())
			{
				// TODO: check if I can get the sprite and dont waste the calls to GetSprite
				auto &animation = e->GetComponent<abyss::components::Anim>();
				animation.animation.GetSprite().setRotation(sf::degrees(transform.angle));
				animation.animation.GetSprite().setPosition(sf::Vector2<float>(transform.pos.x, transform.pos.y));
				animation.animation.GetSprite().setScale(sf::Vector2<float>(transform.scale.x, transform.scale.y));

				m_application->GetWindow().draw(animation.animation.GetSprite());
			}
		}

		if (m_drawCollision)
		{
			if (e->HasComponent<abyss::components::BoundingBox>())
			{
				auto &boundingBox = e->GetComponent<abyss::components::BoundingBox>();
				auto &transform = e->GetComponent<abyss::components::Transform>();

				sf::RectangleShape rect;
				rect.setSize(sf::Vector2f(boundingBox.size.x - 1, boundingBox.size.y - 1));
				rect.setOrigin(sf::Vector2f(boundingBox.halfSize.x, boundingBox.halfSize.y));
				rect.setPosition(sf::Vector2<float>(transform.pos.x, transform.pos.y));
				rect.setFillColor(sf::Color(0, 0, 0, 0));
				rect.setOutlineColor(sf::Color(255, 255, 255, 255));
				rect.setOutlineThickness(1);
				m_application->GetWindow().draw(rect);
			}
		}
	}

	if (m_drawGrid)
	{
		DrawGrid();
	}

	ImGui::SFML::Render(m_application->GetWindow());

	m_application->GetWindow().display();
}

void editor::EditorScene::AnimationSystem()
{
	for (auto e : m_entityManager.GetEntities())
	{
		if (e->HasComponent<abyss::components::Anim>())
		{
			e->GetComponent<abyss::components::Anim>().animation.Update();

			if (!e->GetComponent<abyss::components::Anim>().repeat)
			{
				e->Destroy();
			}
		}
	}
}

void editor::EditorScene::CameraSystem()
{
	sf::View view = m_application->GetWindow().getView();

	// view.setCenter();

	m_application->GetWindow().setView(view);
}

void editor::EditorScene::OnEnd()
{
}

void editor::EditorScene::ExecuteAction(const abyss::Action &action)
{
	if (action.State() == abyss::ActionState::Start)
	{
		if (action.Name() == "TOGGLE_TEXTURE")
		{
			m_drawTextures = !m_drawTextures;
		}
		else if (action.Name() == "TOGGLE_COLLISION")
		{
			m_drawCollision = !m_drawCollision;
		}
		else if (action.Name() == "TOGGLE_GRID")
		{
			m_drawGrid = !m_drawGrid;
		}
		else if (action.Name() == "TOGGLE_CAMERA_TYPE")
		{
			m_follow = !m_follow;
		}
		else if (action.Name() == "PAUSE")
		{
			SetPaused(!m_paused);
		}
		else if (action.Name() == "QUIT")
		{
			OnEnd();
		}
		else if (action.Name() == "LEFT_CLICK")
		{
			// m_selectedEntity = {};
			// sf::Vector2f worldPos =
			// 	m_application->GetWindow().mapPixelToCoords(sf::Vector2i(action.Pos().x, action.Pos().y));

			// for (auto e : m_entityManager.GetEntities())
			// {
			// 	if (m_physics.IsInside(abyss::math::Vec2<float>(worldPos.x, worldPos.y), e))
			// 	{
			// 		m_isEntityInfoOpen = true;
			// 		m_selectedEntity = e;
			// 		break;
			// 	}
			// }
		}
		else if (action.Name() == "TOGGLE_ASSET_MANAGER")
		{
			// m_isAssetManagerOpen = !m_isAssetManagerOpen;
		}
	}
	else if (action.State() == abyss::ActionState::End)
	{
	}
}

void editor::EditorScene::DrawGrid()
{
	float leftX = m_midPointX - Width();
	float rightX = m_midPointX + Width();
	float nextGridX = leftX - std::fmod(leftX, m_gridSize.x);

	float topY = m_midPointY - Height();
	float bottomY = m_midPointY + Height();
	float nextGridY = topY - std::fmod(topY, m_gridSize.y);

	// draw Y lines
	for (float x = nextGridX; x < rightX; x += m_gridSize.x)
	{
		DrawLine(sf::Vector2f(x, topY), sf::Vector2f(x, bottomY));
	}

	// draw X lines
	for (float y = nextGridY; y < bottomY; y += m_gridSize.y)
	{
		DrawLine(sf::Vector2f(leftX, y), sf::Vector2f(rightX, y));

		// draw text inside grid
		for (float x = nextGridX; x < rightX; x += m_gridSize.x)
		{
			int xCell = static_cast<int>(std::floor(x / m_gridSize.x));
			int yCell = static_cast<int>(std::floor(y / m_gridSize.y));

			m_gridText.setString("(" + std::to_string(xCell) + "," + std::to_string(yCell) + ")");
			m_gridText.setPosition(sf::Vector2<float>(x + 3, y + 2));
			m_application->GetWindow().draw(m_gridText);
		}
	}
}

void editor::EditorScene::EntityInfoGui()
{
 //   	if (!m_selectedEntity || !m_isEntityInfoOpen)
	// {
	//    return;
	// }

 //    ImGui::Begin("Entity Info", &m_isEntityInfoOpen);

	// ImGui::End();
}

void editor::EditorScene::AssetManagerGui()
{
 //   	if (!m_isAssetManagerOpen)
	// {
	//     return;
	// }

 //    ImGui::Begin("Asset Manager", &m_isAssetManagerOpen);
	// ImGuiTabBarFlags tabBarFlags = ImGuiTabBarFlags_None;
	// if (ImGui::BeginTabBar("GameTabBar", tabBarFlags))
	// {
	// 	if (ImGui::BeginTabItem("Systems"))
	// 	{
	// 		ImGui::EndTabItem();
	// 	}

	// 	if (ImGui::BeginTabItem("Assets"))
	// 	{
	// 		if (ImGui::BeginTable("TableTest", 5))
	// 		{
	// 			for (auto &a : m_gameApplication->GetAssets().GetAnimations())
	// 			{
	// 				ImGui::ImageButton(a.first.c_str(), a.second.GetSprite(), a.second.GetSize());
	// 				ImGui::TableNextColumn();
	// 			}

	// 			ImGui::EndTable();
	// 		}
	// 		ImGui::EndTabItem();
	// 	}
	// 	ImGui::EndTabBar();
	// }
	// ImGui::End();

	// TODO: tab Actions
	// This one will show and let you do some actions, like pause, toggle texture and etc
}
