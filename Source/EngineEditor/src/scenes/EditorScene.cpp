#include "EditorScene.h"
#include "Action.h"

#include "Entity.h"
#include "EntityTag.h"
#include "components/Anim.h"
#include "components/BoundingBox.h"
#include "components/FollowPlayer.h"
#include "components/Gravity.h"
#include "components/Input.h"
#include "components/Jump.h"
#include "components/Lifespan.h"
#include "components/Patrol.h"
#include "components/State.h"
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
	RegisterAction(sf::Keyboard::Key::Escape, "CANCEL");
	RegisterAction(sf::Keyboard::Key::T, "TOGGLE_TEXTURE");
	RegisterAction(sf::Keyboard::Key::C, "TOGGLE_COLLISION");
	RegisterAction(sf::Keyboard::Key::G, "TOGGLE_GRID");
	RegisterAction(sf::Keyboard::Key::Y, "TOGGLE_CAMERA_TYPE");
	RegisterAction(sf::Keyboard::Key::A, "TO_LEFT");
	RegisterAction(sf::Keyboard::Key::D, "TO_RIGHT");
	RegisterAction(sf::Keyboard::Key::W, "TO_UP");
	RegisterAction(sf::Keyboard::Key::S, "TO_DOWN");
	RegisterAction(sf::Keyboard::Key::LControl, "CONTROL");
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

	// TODO: Check how to better reset the manager
	m_entityManager = abyss::EntityManager();

	m_componentManager = ComponentManager();
	m_componentManager.RegisterComponent<abyss::components::Transform>();
	m_componentManager.RegisterComponent<abyss::components::BoundingBox>();
	m_componentManager.RegisterComponent<abyss::components::Input>();
	m_componentManager.RegisterComponent<abyss::components::Lifespan>();
	m_componentManager.RegisterComponent<abyss::components::Anim>();
	m_componentManager.RegisterComponent<abyss::components::Gravity>();
	m_componentManager.RegisterComponent<abyss::components::State>();
	m_componentManager.RegisterComponent<abyss::components::Patrol>();
	m_componentManager.RegisterComponent<abyss::components::FollowPlayer>();
	m_componentManager.RegisterComponent<abyss::components::Jump>();

	std::shared_ptr<abyss::Entity> player = m_entityManager.AddEntity(abyss::EntityTag::Player);
	m_componentManager.AddComponent(player->Id(),
									abyss::components::Anim(m_application->GetAssets().GetAnimation("Down"), true));
	m_componentManager.AddComponent(player->Id(), abyss::components::Transform(sf::Vector2f(512, 300)));

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
	if (m_componentManager.HasComponent<abyss::components::Anim>(entity->Id()))
	{
		auto &spriteSize = m_componentManager.GetComponent<abyss::components::Anim>(entity->Id()).animation.GetSize();
		return {(gridX * m_gridSize.x) + (spriteSize.x / 2.0f),
							Height() - ((gridY * m_gridSize.y) + (spriteSize.y / 2.0f))};
	}

	return {};
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
			if (!m_componentManager.HasComponent<abyss::components::Transform>(e->Id()) ||
				!m_componentManager.HasComponent<abyss::components::Anim>(e->Id()))
			{
				assert("No component registered!");
				continue;
			}

			auto &transform = m_componentManager.GetComponent<abyss::components::Transform>(e->Id());

			// TODO: check if I can get the sprite and dont waste the calls to GetSprite
			auto &animation = m_componentManager.GetComponent<abyss::components::Anim>(e->Id());
			animation.animation.SetRotation(transform.angle);
			animation.animation.SetPosition(sf::Vector2<float>(transform.pos.x, transform.pos.y));
			animation.animation.SetScale(sf::Vector2<float>(transform.scale.x, transform.scale.y));

			m_application->GetWindow().draw(animation.animation.GetSprite());
		}

		if (m_drawCollision)
		{
			if (!m_componentManager.HasComponent<abyss::components::Transform>(e->Id()) ||
				!m_componentManager.HasComponent<abyss::components::BoundingBox>(e->Id()))
			{
				assert("No component registered!");
				continue;
			}

			auto &boundingBox = m_componentManager.GetComponent<abyss::components::BoundingBox>(e->Id());
			auto &transform = m_componentManager.GetComponent<abyss::components::Transform>(e->Id());

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
		if (m_componentManager.HasComponent<abyss::components::Anim>(e->Id()))
		{
			m_componentManager.GetComponent<abyss::components::Anim>(e->Id()).animation.Update();

			if (!m_componentManager.GetComponent<abyss::components::Anim>(e->Id()).repeat)
			{
				e->Destroy();
				m_componentManager.EntityDestroyed(e->Id());
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
		else if (action.Name() == "CONTROL")
		{
			m_leftControl = true;
		}

		if (m_leftControl && action.Name() == "TOGGLE_INSPECTOR")
		{
			m_isInspectorOpen = !m_isInspectorOpen;
		}
		else if (m_leftControl && action.Name() == "TOGGLE_SCENE_MANAGER")
		{
			m_isSceneManagerOpen = !m_isSceneManagerOpen;
		}
		else if (m_leftControl && action.Name() == "TOGGLE_ASSET_MANAGER")
		{
			m_isAssetManagerOpen = !m_isAssetManagerOpen;
		}

		sf::Vector2f worldPos =
			m_application->GetWindow().mapPixelToCoords(sf::Vector2i(action.Pos().x, action.Pos().y));

		if (m_draggingEntity && action.Name() == "CANCEL")
		{
			if (m_draggingEntity && !m_entityCreation)
			{
				if (m_componentManager.HasComponent<abyss::components::Transform>(m_dragEntity->Id()))
				{
					m_componentManager.GetComponent<abyss::components::Transform>(m_dragEntity->Id()).pos = {m_originalEntityPos.x, m_originalEntityPos.y};
				}
			}
			else if (m_entityCreation)
			{
				m_componentManager.EntityDestroyed(m_dragEntity->Id());
				m_dragEntity->Destroy();
			}

			m_dragEntity = {};
			m_draggingEntity = false;
			m_entityCreation = false;
		}

		if (action.Name() == "LEFT_CLICK")
		{
			if (m_draggingEntity && !m_entityCreation)
			{
				m_dragEntity = {};
				m_draggingEntity = false;
			}
			else if (m_draggingEntity && m_entityCreation)
			{
				m_dragEntity = {};
				m_dragEntity = CreateEntity(m_cloningEntity, m_lastEntityToCreate.c_str());
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
						if (m_physics.IsInside(abyss::math::Vec2<float>(worldPos.x, worldPos.y), e,
											   &m_componentManager))
						{
							m_dragEntity = e;
							m_draggingEntity = true;

							if (m_componentManager.HasComponent<abyss::components::Transform>(m_dragEntity->Id()))
							{
								auto t = m_componentManager.GetComponent<abyss::components::Transform>(m_dragEntity->Id());
								m_originalEntityPos = abyss::math::Vec2<float>(t.pos.x, t.pos.y);
							}

							break;
						}
					}
				}
			}
		}
		else if (action.Name() == "RIGHT_CLICK")
		{
			if (m_entityCreation)
			{
				return;
			}

			m_selectedEntity = {};
			for (auto e : m_entityManager.GetEntities())
			{
				if (m_physics.IsInside(abyss::math::Vec2<float>(worldPos.x, worldPos.y), e, &m_componentManager))
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

				m_componentManager.GetComponent<abyss::components::Transform>(m_dragEntity->Id()).pos = worldPos;
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

		if (action.Name() == "CONTROL")
		{
			m_leftControl = false;
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

void editor::EditorScene::DeleteEntity(const std::shared_ptr<abyss::Entity>& entity)
{
	m_componentManager.EntityDestroyed(entity->Id());
	entity->Destroy();
}

void editor::EditorScene::EntityInfoGui()
{
	if (m_draggingEntity || m_entityCreation || !m_selectedEntity || !m_isEntityInfoOpen)
	{
		return;
	}

	ImGui::Begin("Entity Info", &m_isEntityInfoOpen);
	if (ImGui::Button("C", ImVec2(25, 25)))
	{
		m_dragEntity = CreateEntity(true);
		m_draggingEntity = true;
		m_entityCreation = true;
		m_cloningEntity = true;
		m_isEntityInfoOpen = false;

		m_lastEntityToCreate = {};
	}

	ImGui::SameLine();

	if (ImGui::Button("D", ImVec2(25, 25)))
	{
		DeleteEntity(m_selectedEntity);
		m_selectedEntity = {};

		m_isEntityInfoOpen = false;

		ImGui::End();
		return;

	}

	if (ImGui::Button("Add component", ImVec2(100, 25)))
	{
		ImGui::OpenPopup("my_add_component_popup");
	}
	if (ImGui::BeginPopup("my_add_component_popup"))
	{
		const char *names[] = { "Transform", "Anim", "Bounding box" };

		for (int i = 0; i < IM_ARRAYSIZE(names); i++)
			if (ImGui::Selectable(names[i]))
			{
				InsertGuiToDraw(i);
			}

		ImGui::EndPopup();
	}

	// button to clone the entity
	// option to change the tag
	// option to change the entity name (this will show at the top, the name will be used on the inspector stuff to
	// filter and so on)
	// list of components added
	// button to add more components

	// TODO: add component to the entity
	// TODO: find a way to reset the function pointers so every entity has its own info
	// for(auto& f : m_guiPointers)
	// {
	//    (this->*f)();
	// }
	//
	if (m_componentManager.HasComponent<abyss::components::Transform>(m_selectedEntity->Id()))
	{
		TransformCompGui();
	}
	if (m_componentManager.HasComponent<abyss::components::Anim>(m_selectedEntity->Id()))
	{
		AnimCompGui();
	}
	if (m_componentManager.HasComponent<abyss::components::BoundingBox>(m_selectedEntity->Id()))
	{
		BoundingBoxCompGui();
	}

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
						m_lastEntityToCreate = a.first;
						m_dragEntity = CreateEntity(false, m_lastEntityToCreate.c_str());

						m_draggingEntity = true;
						m_entityCreation = true;
						m_cloningEntity = false;
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

std::shared_ptr<abyss::Entity> editor::EditorScene::CreateEntity(const bool clone, const char* animName)
{
	auto entity = m_entityManager.AddEntity(abyss::EntityTag::Default);

	if (clone)
	{
		if (m_componentManager.HasComponent<abyss::components::Anim>(m_selectedEntity->Id()))
		{
			auto a = m_componentManager.GetComponent<abyss::components::Anim>(m_selectedEntity->Id());
			m_componentManager.AddComponent(entity->Id(), abyss::components::Anim(abyss::Animation(a.animation.GetName(), a.animation.GetSprite().getTexture(), a.animation.GetFrameCount(), a.animation.speed), a.repeat));
		}

		if (m_componentManager.HasComponent<abyss::components::Transform>(m_selectedEntity->Id()))
		{
			const auto t = m_componentManager.GetComponent<abyss::components::Transform>(m_selectedEntity->Id());
			m_componentManager.AddComponent(entity->Id(), abyss::components::Transform(t.pos, t.velocity, t.scale, t.angle));
		}

		if (m_componentManager.HasComponent<abyss::components::BoundingBox>(m_selectedEntity->Id()))
		{
			const auto bb = m_componentManager.GetComponent<abyss::components::BoundingBox>(m_selectedEntity->Id());
			m_componentManager.AddComponent(entity->Id(), abyss::components::BoundingBox(bb.size, bb.isTrigger, bb.blockMove, bb.blockVision));
		}
	}
	else
	{
		m_componentManager.AddComponent<abyss::components::Anim>(
			entity->Id(),
			abyss::components::Anim(m_application->GetAssets().GetAnimation(std::string(animName)), true));
		m_componentManager.AddComponent<abyss::components::Transform>(
			entity->Id(), abyss::components::Transform(
				sf::Vector2f(m_application->GetWindow().getView().getCenter().x,
				             m_application->GetWindow().getView().getCenter().y)));
	}

	return entity;
}

void editor::EditorScene::TransformCompGui()
{
	if (ImGui::CollapsingHeader("Transform"))
	{
		auto &transform = m_componentManager.GetComponent<abyss::components::Transform>(m_selectedEntity->Id());
		auto &animation = m_componentManager.GetComponent<abyss::components::Anim>(m_selectedEntity->Id());

		float pos[2] = { transform.pos.x, transform.pos.y };
		ImGui::InputFloat2("t_pos", pos);
		transform.pos.x = pos[0];
		transform.pos.y = pos[1];

		float scale[2] = { transform.scale.x, transform.scale.y };
		ImGui::InputFloat2("t_scale", scale);
		transform.scale.x = scale[0];
		transform.scale.y = scale[1];

		ImGui::InputFloat("t_angle", &transform.angle);
	}
}

void editor::EditorScene::AnimCompGui()
{
	if (ImGui::CollapsingHeader("Anim"))
	{
		auto &animation = m_componentManager.GetComponent<abyss::components::Anim>(m_selectedEntity->Id());
		ImGui::InputInt("Speed", &animation.animation.speed);
	}
}

void editor::EditorScene::BoundingBoxCompGui()
{
	if (ImGui::CollapsingHeader("Bounding box"))
	{
		if (ImGui::Button("Remove", ImVec2(100, 25)))
		{
			m_componentManager.RemoveComponent<abyss::components::BoundingBox>(m_selectedEntity->Id());
			return;
		}

		auto &bb = m_componentManager.GetComponent<abyss::components::BoundingBox>(m_selectedEntity->Id());

		float pos[2] = { bb.size.x, bb.size.y };
		ImGui::InputFloat2("bb_position", pos);
		bb.size.x = pos[0];
		bb.size.y = pos[1];
		bb.halfSize = sf::Vector2f(bb.size / 2.0f);

		ImGui::Checkbox("Is trigger", &bb.isTrigger);
		ImGui::Checkbox("Block movement", &bb.blockMove);
		ImGui::SameLine();
		ImGui::Checkbox("Block vision", &bb.blockVision);
	}
}

void editor::EditorScene::InsertGuiToDraw(int index)
{
	switch (index)
	{
		case 0:
			if (!m_componentManager.HasComponent<abyss::components::Transform>(m_selectedEntity->Id()))
			{
				m_componentManager.AddComponent<abyss::components::Transform>(
					m_selectedEntity->Id(), abyss::components::Transform(sf::Vector2f()));
			}
			break;
		case 1:
			if (!m_componentManager.HasComponent<abyss::components::Anim>(m_selectedEntity->Id()))
			{
				m_componentManager.AddComponent<abyss::components::Anim>(
					m_selectedEntity->Id(),
					abyss::components::Anim(m_application->GetAssets().GetAnimation("Down"), true));
			}
			break;
		case 2:
			if (!m_componentManager.HasComponent<abyss::components::BoundingBox>(m_selectedEntity->Id()))
			{
				ABYSS_INFO("Entrei aqui o/");
				m_componentManager.AddComponent<abyss::components::BoundingBox>(
					m_selectedEntity->Id(), abyss::components::BoundingBox(sf::Vector2f(), false));
			}
			break;
	}
}
