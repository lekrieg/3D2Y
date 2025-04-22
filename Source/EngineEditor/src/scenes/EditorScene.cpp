#include "EditorScene.h"

#include "Action.h"

#include "Entity.h"
#include "EntityTag.h"
#include "components/Anim.h"
#include "components/Transform.h"

#include "Logger.h"

#include "../imgui/imgui-SFML.h"
#include "../imgui/imgui.h"
#include "SFML/Graphics/View.hpp"
#include "SFML/System/Angle.hpp"
#include "SFML/System/Vector2.hpp"
#include "math/Vectors.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <filesystem>
#include <math.h>
#include <memory>
#include <string>

void editor::EditorScene::Update(float deltaTime)
{
	m_entityManager.Update();

	if (!m_paused)
	{
		// CameraSystem();
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
	RegisterAction(sf::Keyboard::Key::Num1, "TOGGLE_INSPECTOR");
	RegisterAction(sf::Keyboard::Key::Num2, "TOGGLE_ASSET_MANAGER");
	RegisterAction(sf::Keyboard::Key::Num3, "TOGGLE_SCENE_MANAGER");

	m_gridText.setCharacterSize(8);
	m_gridText.setFont(m_application->GetAssets().GetFont("elementalis"));

	m_fileDialog.SetTitle("File dialog");
	m_fileDialog.SetTypeFilters({ ".yaml" });

	LoadLevel(levelPath);
}

void editor::EditorScene::LoadLevel(const std::string &fileName)
{
	ABYSS_INFO("Info...");
	ABYSS_WARNING("Warning...");
	ABYSS_ERROR("Error...");

	// TODO: terminar de serializar e deserializar os componentes
	// dessa forma sempre que der load, os itens sao redesanhados na cena corretamente

	// TODO: Check how to better reset the manager
	m_entityManager = abyss::EntityManager();

	std::shared_ptr<abyss::Entity> player = m_entityManager.AddEntity(abyss::EntityTag::Player);
	player->AddComponent<abyss::components::Anim>(m_application->GetAssets().GetAnimation("Down"), true);
	player->AddComponent<abyss::components::Transform>(sf::Vector2f(512, 300));

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
	view.setCenter(sf::Vector2f(m_midPointX, m_midPointY));

	m_application->GetWindow().setView(view);
}

void editor::EditorScene::OnEnd()
{
}

void editor::EditorScene::ExecuteAction(const abyss::Action &action)
{
	if (!m_allowInput)
	{
		return;
	}

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
		else if (action.Name() == "TOGGLE_ASSET_MANAGER")
		{
			m_isAssetManagerOpen = !m_isAssetManagerOpen;
		}
		else if (action.Name() == "TOGGLE_INSPECTOR")
		{
			m_isInspectorOpen = !m_isInspectorOpen;
		}
		else if (action.Name() == "TOGGLE_SCENE_MANAGER")
		{
			m_isSceneManagerOpen = !m_isSceneManagerOpen;
		}

		sf::Vector2f worldPos =
			m_application->GetWindow().mapPixelToCoords(sf::Vector2i(action.Pos().x, action.Pos().y));

		if (action.Name() == "LEFT_CLICK")
		{
			if (m_draggingEntity)
			{
				m_dragEntity = {};
				m_draggingEntity = false;
			}
			else
			{
				m_leftClick = true;
				m_oldPos = abyss::math::Vec2<float>(action.Pos().x, action.Pos().y);

				if (!m_dragEntity)
				{
					m_dragEntity = {};
					for (auto e : m_entityManager.GetEntities())
					{
						if (m_physics.IsInside(abyss::math::Vec2<float>(worldPos.x, worldPos.y), e))
						{
							m_dragEntity = e;
							m_draggingEntity = true;
							break;
						}
					}
				}
			}
		}
		else if (action.Name() == "RIGHT_CLICK")
		{
			m_selectedEntity = {};
			for (auto e : m_entityManager.GetEntities())
			{
				if (m_physics.IsInside(abyss::math::Vec2<float>(worldPos.x, worldPos.y), e))
				{
					m_isEntityInfoOpen = true;
					m_selectedEntity = e;
					break;
				}
			}
		}

		if (action.Name() == "MOUSE_MOVE")
		{
			if (m_leftClick)
			{
				abyss::math::Vec2<float> newPos = abyss::math::Vec2<float>(action.Pos().x, action.Pos().y);
				abyss::math::Vec2<float> deltaPos = m_oldPos - newPos;

				sf::View view = m_application->GetWindow().getView();
				view.move(sf::Vector2f(deltaPos.x, deltaPos.y));
				m_application->GetWindow().setView(view);

				m_oldPos = newPos;
			}

			if (m_dragEntity)
			{
				if (m_snapToGrid)
				{
					worldPos.x = std::floor(worldPos.x / 16) * 16 + 8;
					worldPos.y = std::floor(worldPos.y / 16) * 16 + 8;
				}

				m_dragEntity->GetComponent<abyss::components::Transform>().pos = worldPos;
			}
		}
		else if (action.Name() == "ZOOM")
		{
			if (action.ScrollWheelDelta() <= -1)
			{
				actualZoom = std::min(2.0f, actualZoom + 0.1f);
			}
			else if (action.ScrollWheelDelta() >= 1)
			{
				actualZoom = std::max(0.5f, actualZoom - 0.1f);
			}

			accumulatedZoom *= actualZoom;
			sf::View view = m_application->GetWindow().getView();
			view.setSize(m_application->GetWindow().getDefaultView().getSize());
			view.zoom(actualZoom);
			m_application->GetWindow().setView(view);

		sf:;
			sf::Vector2f newPos =
				m_application->GetWindow().mapPixelToCoords(sf::Vector2i(action.Pos().x, action.Pos().y));
			sf::Vector2f deltaPos = worldPos - newPos;
			view.move(deltaPos);
			m_application->GetWindow().setView(view);
		}
	}
	else if (action.State() == abyss::ActionState::End)
	{
		if (action.Name() == "LEFT_CLICK")
		{
			m_leftClick = false;
		}
	}
}

void editor::EditorScene::DrawGrid()
{
	sf::View view = m_application->GetWindow().getView();
	float leftX = view.getCenter().x - Width();
	float rightX = view.getCenter().x + Width();
	float nextGridX = leftX - std::fmod(leftX, m_gridSize.x);

	float topY = view.getCenter().y - Height();
	float bottomY = view.getCenter().y + Height();
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
		// for (float x = nextGridX; x < rightX; x += m_gridSize.x)
		// {
		// 	int xCell = static_cast<int>(std::floor(x / m_gridSize.x));
		// 	int yCell = static_cast<int>(std::floor(y / m_gridSize.y));

		// 	m_gridText.setString("(" + std::to_string(xCell) + "," + std::to_string(yCell) + ")");
		// 	m_gridText.setPosition(sf::Vector2<float>(x + 3, y + 2));
		// 	m_application->GetWindow().draw(m_gridText);
		// }
	}
}

void editor::EditorScene::EntityInfoGui()
{
	if (!m_selectedEntity || !m_isEntityInfoOpen)
	{
		return;
	}

	ImGui::Begin("Entity Info", &m_isEntityInfoOpen);

	ImGui::End();
}

void editor::EditorScene::AssetManagerGui()
{
	if (!m_isAssetManagerOpen)
	{
		return;
	}

	ImGui::Begin("Asset Manager", &m_isAssetManagerOpen);
	ImGuiTabBarFlags tabBarFlags = ImGuiTabBarFlags_None;
	if (ImGui::BeginTabBar("GameTabBar", tabBarFlags))
	{
		if (ImGui::BeginTabItem("Systems"))
		{
			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Assets"))
		{
			ImGui::Checkbox("Snap to grid", &m_snapToGrid);
			if (ImGui::BeginTable("TableTest", 5))
			{
				for (auto &a : m_application->GetAssets().GetAnimations())
				{
					if (ImGui::ImageButton(a.first.c_str(), a.second.GetSprite(), sf::Vector2f(32, 32)))
					{
						m_dragEntity = m_entityManager.AddEntity(abyss::EntityTag::Default);
						m_dragEntity->AddComponent<abyss::components::Anim>(
							m_application->GetAssets().GetAnimation(a.first.c_str()), true);
						m_dragEntity->AddComponent<abyss::components::Transform>(
							sf::Vector2f(m_application->GetWindow().getView().getCenter().x,
										 m_application->GetWindow().getView().getCenter().y));

						m_draggingEntity = true;
					}
					ImGui::TableNextColumn();
				}

				ImGui::EndTable();
			}
			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}
	ImGui::End();

	// TODO: tab Actions
	// This one will show and let you do some actions, like pause, toggle texture and etc
}

void editor::EditorScene::SceneManagerGui()
{
	if (!m_isSceneManagerOpen)
	{
		return;
	}

	ImGui::Begin("Scene Manager", &m_isSceneManagerOpen, ImGuiWindowFlags_NoResize);

	// Scene: Name
	ImGui::Text("Scene: %s", m_sceneName.c_str());

	ImGui::Spacing();

	// New
	if (ImGui::Button("New", ImVec2(100, 25)))
	{
		m_sceneName = "Default";
		m_entityManager.Clear();
	}

	ImGui::SameLine();

	// Save
	if (ImGui::Button("Save", ImVec2(100, 25)))
	{
		m_allowInput = false;
		m_fileDialog.SetFlagOptions(0 | ImGuiFileBrowserFlags_CloseOnEsc | ImGuiFileBrowserFlags_EnterNewFilename |
									ImGuiFileBrowserFlags_CreateNewDir);
		m_dialogState = FileDialogState::Save;
		m_fileDialog.Open();
	}

	ImGui::SameLine();

	// Load
	if (ImGui::Button("Load", ImVec2(100, 25)))
	{
		m_allowInput = false;
		m_fileDialog.SetFlagOptions(0 | ImGuiFileBrowserFlags_CloseOnEsc);
		m_dialogState = FileDialogState::Load;
		m_fileDialog.Open();
	}

	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();

	static ImGuiComboFlags flags = 0;
	std::vector<std::filesystem::path> fileList;

	for (auto const &dirEntry : std::filesystem::directory_iterator(std::filesystem::canonical(m_levelsPathFolder)))
	{
		if (dirEntry.path().string().find(".yaml") != std::string::npos)
		{
			fileList.push_back(dirEntry.path());
		}
	}

	static int item_selected_idx = 0;

	const char *combo_preview_value = fileList[item_selected_idx].filename().c_str();
	if (ImGui::BeginCombo("Level list", combo_preview_value, flags))
	{
		for (int n = 0; n < fileList.size(); n++)
		{
			const bool is_selected = (item_selected_idx == n);
			if (ImGui::Selectable(fileList[n].filename().c_str(), is_selected))
				item_selected_idx = n;

			// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}

	ImGui::Spacing();

	if (ImGui::Button("Reload", ImVec2(100, 25)))
	{
		m_sceneName = fileList[item_selected_idx].filename();
		Deserialize(fileList[item_selected_idx]);
	}

	ImGui::SameLine();

	ImGui::Text("%s", fileList[item_selected_idx].filename().c_str());

	ImGui::End();

	m_fileDialog.Display();

	if (m_fileDialog.HasSelected())
	{
		m_allowInput = true;
		std::string path = m_fileDialog.GetSelected().string();
		m_sceneName = m_fileDialog.GetSelected().filename();

		switch (m_dialogState)
		{
			case FileDialogState::Save:
				m_levelPath = path.empty() ? "DefaultName.yaml" : path;
				if (m_levelPath.find(".yaml") == std::string::npos)
				{
					m_levelPath.append(".yaml");
				}
				Serialize(m_levelPath);
				break;
			case FileDialogState::Load:
				Deserialize(path);
				break;
		}

		m_fileDialog.ClearSelected();
	}
	else if (!m_allowInput && !m_fileDialog.IsOpened())
	{
		m_allowInput = true;
	}
}

void editor::EditorScene::InspectorGui()
{
	if (!m_isInspectorOpen)
	{
		return;
	}

	ImGui::Begin("Inspector", &m_isInspectorOpen);

	ImGui::End();
}
