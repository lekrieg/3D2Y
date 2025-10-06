#include "PlayScene.h"

#include "Action.h"
#include "Assets.h"
#include "Physics.h"

#include "components/Anim.h"
#include "components/Input.h"
#include "components/Jump.h"
#include "components/State.h"
#include "components/Transform.h"

#include "Logger.h"

#include "SFML/Graphics/View.hpp"
#include "SFML/System/Angle.hpp"
#include "SFML/System/Vector2.hpp"
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <string>

#include "components/FollowPlayer.h"
#include "components/Gravity.h"
#include "components/Lifespan.h"
#include "components/Patrol.h"
#include "serialization/Serializer.h"
#include "yaml-cpp/exceptions.h"
#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/parse.h"

void game::PlayScene::Update(float deltaTime)
{
	m_entityManager.Update();

	if (!m_paused)
	{
		MovementSystem();
		CollisionSystem();
		CameraSystem();
	}

	AnimationSystem();
}

void game::PlayScene::Init(const std::string &levelPath)
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

	m_gridText.setCharacterSize(12);
	m_gridText.setFont(m_application->GetAssets().GetFonts()[0]);

	LoadLevel(levelPath);

	FillInfos();
}

void game::PlayScene::LoadLevel(const std::string &fileName)
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

	Deserialize("scenes/scene1.yaml");

	// update one time so the vectors are updated
	m_entityManager.Update();

	SpawnPlayer();

	// should position the entity with the grid x,y read from the file
	// brick->AddComponent<Transform>(GridX, GridY, brick);
}

sf::Vector2f game::PlayScene::GridToMidPixel(float gridX, float gridY, std::shared_ptr<abyss::Entity> entity)
{
	/* TODO: must return a vector2 indicating where the center position of the entity should be
	 * you must use the entity animation size to position it correctly
	 * the size of the grid width and height is stored in m_gridSize.x and m_gridSize.y
	 * the bottom left corner of th animation should be with the bottom left of the grid cell
	 */

	auto &spriteSize = m_componentManager.GetComponent<abyss::components::Anim>(entity->Id()).animation.GetAnimation()->frames[0];
	return sf::Vector2f((gridX * m_gridSize.x) + (spriteSize->size.x / 2.0f),
						Height() - ((gridY * m_gridSize.y) + (spriteSize->size.x / 2.0f)));
}

void game::PlayScene::Render()
{
	if (!m_paused)
	{
		m_application->GetWindow().clear(sf::Color::Black);
	}
	else
	{
		m_application->GetWindow().clear(sf::Color(104, 104, 104));
	}

	// auto& playerPos = m_player->GetComponent<abyss::components::Transform>().pos;
	// float windowCenterX = std::max(m_application->GetWindow().getSize().x / 2.0f, playerPos.x);
	// sf::View view = m_application->GetWindow().getView();
	// view.setCenter(sf::Vector2<float>(windowCenterX, m_application->GetWindow().getSize().y -
	// view.getCenter().y)); m_application->GetWindow().setView(view);

	for (auto e : m_entityManager.GetEntities())
	{
		if (m_drawTextures)
		{
			auto &transform = m_componentManager.GetComponent<abyss::components::Transform>(e->Id());
			if (m_componentManager.HasComponent<abyss::components::Anim>(e->Id()))
			{
				// TODO: check if I can get the sprite and dont waste the calls to GetSprite
				auto &animation = m_componentManager.GetComponent<abyss::components::Anim>(e->Id());
				animation.animation.GetSprite().setRotation(sf::degrees(transform.angle));
				animation.animation.GetSprite().setPosition(sf::Vector2<float>(transform.pos.x, transform.pos.y));
				animation.animation.GetSprite().setScale(sf::Vector2<float>(transform.scale.x, transform.scale.y));

				m_application->GetWindow().draw(animation.animation.GetSprite());
			}
		}

		if (m_drawCollision)
		{
			if (m_componentManager.HasComponent<abyss::components::BoundingBox>(e->Id()))
			{
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
	}

	// room rx, ry
	// tile tx, ty
	// I need to do a vector2 that will track the room number (I will increment and decrement according with
	// the direction I go)
	// this will be multiplied by h and w of the window
	// the rest of the math is basically the same

	if (m_drawGrid)
	{
		DrawGrid();
	}

	sf::CircleShape circ;
	circ.setFillColor(sf::Color::Red);
	circ.setRadius(2.f);
	// circ.setPosition(m_componentManager.GetComponent<abyss::components::Anim>(m_player->Id()).animation.GetSprite().getPosition());
	m_application->GetWindow().draw(circ);

	// sf::Vertex v[] =
	//{
	//	sf::Vertex((m_player->GetComponent<components::Transform>().pos))
	// };

	// m_application->GetWindow().draw(v, 50, sf::Points);

	m_application->GetWindow().display();
}

// TODO: Re-implement the jump and check physics
// TODO: Implement the maxmimum player speed in both x and y directions

void game::PlayScene::MovementSystem()
{
	auto &playerTransform = m_componentManager.GetComponent<abyss::components::Transform>(m_player->Id());
	// auto& playerJump = m_player->GetComponent<components::Jump>();
	sf::Vector2f playerVelocity;

	if (m_componentManager.HasComponent<abyss::components::Input>(m_player->Id()))
	{
		auto &playerInput = m_componentManager.GetComponent<abyss::components::Input>(m_player->Id());

		if (playerInput.left)
		{
			// TODO: add a file with the entity configurations
			playerVelocity.x -= m_playerInfo.speed;

			m_componentManager.GetComponent<abyss::components::Anim>(m_player->Id()).animation.SetAnimation("WalkLeft");
		}
		else if (playerInput.right)
		{
			playerVelocity.x += m_playerInfo.speed;

			m_componentManager.GetComponent<abyss::components::Anim>(m_player->Id()).animation.SetAnimation("WalkRight");
		}

		if (playerInput.down)
		{
			playerVelocity.y += m_playerInfo.speed;

			m_componentManager.GetComponent<abyss::components::Anim>(m_player->Id()).animation.SetAnimation("WalkDown");
		}

		if (playerInput.up)
		{
			playerVelocity.y -= m_playerInfo.speed;

			m_componentManager.GetComponent<abyss::components::Anim>(m_player->Id()).animation.SetAnimation("WalkUp");
		}
	}

	playerTransform.velocity = playerVelocity;

	for (auto e : m_entityManager.GetEntities())
	{
		auto& entityTransform = m_componentManager.GetComponent<abyss::components::Transform>(e->Id());

		entityTransform.previousPos = entityTransform.pos;
		entityTransform.pos += entityTransform.velocity * m_application->DeltaTime();
	}
}

void game::PlayScene::EnemySpawnerSystem()
{
}

void game::PlayScene::CollisionSystem()
{
	/*
	 * SFML (0,0) pos is on  the top-left corner
	 * this means jumping will have a negative y and gravity will have a positive y
	 * also, something below something else will have a y value greater than it
	 * also, something above something else will have a y value less than it
	 *
	 * TODO: implement bullet / tile collision
	 * destroy the tile if it has brick collision
	 */

	if (!m_componentManager.HasComponent<abyss::components::Transform>(m_player->Id()))
	{
		ABYSS_WARNING("Player dont have transform comp!");
		return;
	}
	if (!m_componentManager.HasComponent<abyss::components::BoundingBox>(m_player->Id()))
	{
		ABYSS_WARNING("Player dont have BB comp!");
		return;
	}

	auto &playerTransform = m_componentManager.GetComponent<abyss::components::Transform>(m_player->Id());
	auto &playerBB = m_componentManager.GetComponent<abyss::components::BoundingBox>(m_player->Id());

	for (const auto& e: m_entityManager.GetEntities())
	{
		if (m_componentManager.HasComponent<abyss::components::BoundingBox>(e->Id()))
		{
			sf::Vector2f overlap = m_physics.GetOverlap(m_player, e, &m_componentManager);
			if (overlap.x > 0 && overlap.y > 0)
			{
				auto &eTransform = m_componentManager.GetComponent<abyss::components::Transform>(e->Id());
				auto &eBB = m_componentManager.GetComponent<abyss::components::BoundingBox>(e->Id());

				sf::Vector2f previousOverlap = m_physics.GetPreviousOverlap(m_player, e, &m_componentManager);
				if (!m_componentManager.GetComponent<abyss::components::BoundingBox>(e->Id()).isTrigger)
				{
					if (previousOverlap.y > 0)
					{
						if ((playerTransform.pos.x + playerBB.halfSize.x) < (eTransform.pos.x + eBB.halfSize.x))
						{
							playerTransform.pos.x -= overlap.x;
						}
						else if ((playerTransform.pos.x + playerBB.halfSize.x) > (eTransform.pos.x + eBB.halfSize.x))
						{
							playerTransform.pos.x += overlap.x;
						}
					}
					else if (previousOverlap.x > 0)
					{
						if ((playerTransform.pos.y + playerBB.halfSize.y) < (eTransform.pos.y + eBB.halfSize.y))
						{
							playerTransform.pos.y -= overlap.y;
						}
						else if ((playerTransform.pos.y + playerBB.halfSize.y) > (eTransform.pos.y + eBB.halfSize.y))
						{
							playerTransform.pos.y += overlap.y;
						}
					}
				}
			}

			// else
			// {
			// 	if (e->Tag() == abyss::enums::EntityTag::Dangerous)
			// 	{
			// 		if (playerTransform.pos.y + 0.2f > eTransform.pos.y)
			// 		{
			// 			if (playerTransform.pos.x < eTransform.pos.x - 50.0f ||
			// 				eTransform.pos.x + 50.0f < playerTransform.pos.x)
			// 			{
			// 				continue;
			// 			}
			//
			// 			OnEnd();
			// 		}
			// 	}
			// 	else if (e->Tag() == abyss::enums::EntityTag::Default)
			// 	{
			// 		if (playerTransform.pos.y + 0.2f > eTransform.pos.y)
			// 		{
			// 			if (playerTransform.pos.x < eTransform.pos.x - 50.0f ||
			// 				eTransform.pos.x + 50.0f < playerTransform.pos.x)
			// 			{
			// 				continue;
			// 			}
			//
			// 			// int index = m_application->GetGameManager().sceneIndex;
			// 			// m_application->GetGameManager().clearedLevels[index] = true;
			//
			// 			OnEnd();
			// 		}
			// 	}
		}
	}
}

void game::PlayScene::AnimationSystem()
{
	// auto &playerInput = m_componentManager.GetComponent<abyss::components::Input>(m_player->Id());
	//
	// if (m_componentManager.GetComponent<abyss::components::Anim>(m_player->Id()).animation.GetAnimation()->name !=
	// 		"WalkLeft")
	// {
	// 	auto &s = m_application->GetAssets().GetSprites()[274];
	// 	m_componentManager.AddComponent<abyss::components::Anim>(m_player->Id(),
	// 															 abyss::components::Anim(
	// 																 abyss::CustomSprite(
	// 																	 s, m_application->GetAssets().GetTextures()
	// 																	 [s.path]), true));
	// }

	// if (m_componentManager.GetComponent<abyss::components::State>(m_player->Id()).state == "WalkLeft")
	// {
	// 	if (m_componentManager.GetComponent<abyss::components::Anim>(m_player->Id()).animation.GetAnimation()->name !=
	// 	    "WalkLeft")
	// 	{
	// 		auto &s = m_application->GetAssets().GetSprites()[274];
	// 		m_componentManager.AddComponent<abyss::components::Anim>(m_player->Id(),
	// 		                                                         abyss::components::Anim(
	// 			                                                         abyss::CustomSprite(
	// 				                                                         s, m_application->GetAssets().GetTextures()
	// 				                                                         [s.path]), true));
	// 	}
	//
	// 	/*auto& playerTransform = m_player->GetComponent<components::Transform>();
	// 	if (playerInput.left)
	// 	{
	// 		playerTransform.scale.x = -1;
	// 	}
	// 	else if (playerInput.right)
	// 	{
	// 		playerTransform.scale.x = 1;
	// 	}*/
	// }
	// else if (m_player->GetComponent<abyss::components::State>().state == "Up")
	// {
	// 	if (m_player->GetComponent<abyss::components::Anim>().animation.GetName() != "Up")
	// 	{
	// 		m_player->AddComponent<abyss::components::Anim>(m_application->GetAssets().GetAnimation("Up"), true);
	// 	}
	// }
	// else if (m_player->GetComponent<abyss::components::State>().state == "Left")
	// {
	// 	if (m_player->GetComponent<abyss::components::Anim>().animation.GetName() != "Left")
	// 	{
	// 		m_player->AddComponent<abyss::components::Anim>(m_application->GetAssets().GetAnimation("Left"), true);
	// 	}
	// }
	// else if (m_player->GetComponent<abyss::components::State>().state == "Right")
	// {
	// 	if (m_player->GetComponent<abyss::components::Anim>().animation.GetName() != "Right")
	// 	{
	// 		m_player->AddComponent<abyss::components::Anim>(m_application->GetAssets().GetAnimation("Right"), true);
	// 	}
	// }

	// TEST, REMOVE THIS SHIT LATER
	for (auto e : m_entityManager.GetEntities())
	{
		if (m_componentManager.HasComponent<abyss::components::Anim>(e->Id()))
		{
			m_componentManager.GetComponent<abyss::components::Anim>(e->Id()).animation.Update();

			if (!m_componentManager.GetComponent<abyss::components::Anim>(e->Id()).repeat)
			{
				e->Destroy();
			}
		}
	}
}

void game::PlayScene::AISystem()
{
}

void game::PlayScene::CameraSystem()
{
	sf::View view = m_application->GetWindow().getView();
	auto &t = m_componentManager.GetComponent<abyss::components::Transform>(m_player->Id());

	// x room
	if (t.pos.x < m_midPointX - m_halfWidth)
	{
		m_room.x--;
		float x = m_room.x * Width();
		m_midPointX = x == 0 ? m_halfWidth : x + m_halfWidth;
	}
	else if (t.pos.x > m_midPointX + m_halfWidth)
	{
		m_room.x++;
		float x = m_room.x * Width();
		m_midPointX = x == 0 ? m_halfWidth : x - m_halfWidth;
	}

	// y room
	if (t.pos.y < m_midPointY - m_halfHeight)
	{
		m_room.y--;
		float y = m_room.y * Height();
		m_midPointY = y == 0 ? m_halfHeight : y + m_halfHeight;
	}
	else if (t.pos.y > m_midPointY + m_halfHeight)
	{
		m_room.y++;
		float y = m_room.y * Height();
		m_midPointY = y == 0 ? m_halfHeight : y - m_halfHeight;
	}

	if (m_follow)
	{
		// calculate view for player follow camera
		view.setCenter(t.pos);
	}
	else
	{
		// calculate view for room-base camera
		view.setCenter(sf::Vector2f(m_midPointX, m_midPointY));
	}

	m_application->GetWindow().setView(view);
}

void game::PlayScene::StatusSystem()
{
}

void game::PlayScene::SpawnPlayer()
{
	m_player = m_entityManager.GetEntities(abyss::enums::EntityTag::Player)[0];
	// m_componentManager.AddComponent(m_player->Id(), abyss::components::Input());

	// always add the animation first, so that gridToMidPixel can compute correctly
	// m_player->AddComponent<abyss::components::Anim>(m_application->GetAssets().GetAnimation("Down"), true);
	// m_player->AddComponent<abyss::components::Transform>(sf::Vector2f(72, 300));
	// m_player->AddComponent<abyss::components::BoundingBox>(m_playerInfo.boundingBoxSize, false);
	// m_player->AddComponent<abyss::components::Input>();
}

void game::PlayScene::OnEnd()
{
	m_application->Quit();
	// m_application->ChangeScene("MENU", std::make_shared<game::MenuScene>(m_application));
}

void game::PlayScene::ExecuteAction(const abyss::Action &action)
{
	// TODO: change screen drag to middle button and let the left click only drag the entities
	if (action.State() == abyss::enums::ActionState::Start)
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

		if (action.Name() == "TO_LEFT")
		{
			m_componentManager.GetComponent<abyss::components::Input>(m_player->Id()).left = true;
		}
		else if (action.Name() == "TO_RIGHT")
		{
			m_componentManager.GetComponent<abyss::components::Input>(m_player->Id()).right = true;
		}
		else if (action.Name() == "TO_UP")
		{
			m_componentManager.GetComponent<abyss::components::Input>(m_player->Id()).up = true;
		}
		else if (action.Name() == "TO_DOWN")
		{
			m_componentManager.GetComponent<abyss::components::Input>(m_player->Id()).down = true;
		}
	}
	else if (action.State() == abyss::enums::ActionState::End)
	{
		if (action.Name() == "TO_LEFT")
		{
			m_componentManager.GetComponent<abyss::components::Input>(m_player->Id()).left = false;
		}
		else if (action.Name() == "TO_RIGHT")
		{
			m_componentManager.GetComponent<abyss::components::Input>(m_player->Id()).right = false;
		}
		else if (action.Name() == "TO_UP")
		{
			m_componentManager.GetComponent<abyss::components::Input>(m_player->Id()).up = false;
		}
		else if (action.Name() == "TO_DOWN")
		{
			m_componentManager.GetComponent<abyss::components::Input>(m_player->Id()).down = false;
		}
	}
}

void game::PlayScene::DrawGrid()
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

void game::PlayScene::FillInfos()
{
	m_playerInfo.speed = 50;
	m_playerInfo.maxSpeed = 6;

	m_npcs["Npc1"].blockMove = true;
	m_npcs["Npc1"].aiInfo.type = AiType::Patrol;
	m_npcs["Npc1"].aiInfo.patrolPositions = {};

	m_enemies["Bat"].blockMove = true;
	m_enemies["Bat"].aiInfo.type = AiType::Patrol;
	m_enemies["Bat"].aiInfo.patrolPositions = {
		sf::Vector2f(20, 0),
		sf::Vector2f(0, -20),
		sf::Vector2f(-20, 0),
		sf::Vector2f(0, 20)
	};
	m_enemies["Bat"].speed = 10;
}
