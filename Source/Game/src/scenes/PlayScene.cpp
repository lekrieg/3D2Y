// #include "PlayScene.h"

// #include "MenuScene.h"

// #include "../core/Action.h"
// #include "../core/Assets.h"
// #include "../core/Physics.h"

// #include "../core/components/Anim.h"
// #include "../core/components/Jump.h"
// #include "../core/components/Transform.h"

// #include "../FileData.h"
// #include "../utils/Logger.h"
// #include "../utils/MathFunc.h"

// #include "../imgui/imgui-SFML.h"
// #include "SFML/Graphics/View.hpp"
// #include "SFML/System/Angle.hpp"
// #include "SFML/System/Vector2.hpp"
// #include "SFML/Window/Mouse.hpp"
// #include <cmath>
// #include <cstdlib>
// #include <fstream>
// #include <math.h>
// #include <string>

// void core::PlayScene::Update(float deltaTime)
// {
// 	m_entityManager.Update();

// 	if (!m_paused)
// 	{
// 		MovementSystem();
// 		CollisionSystem();
// 		CameraSystem();
// 	}

// 	AnimationSystem();
// }

// void core::PlayScene::Init(const std::string &levelPath)
// {
// 	RegisterAction(sf::Keyboard::Key::P, "PAUSE");
// 	RegisterAction(sf::Keyboard::Key::Escape, "QUIT");
// 	RegisterAction(sf::Keyboard::Key::T, "TOGGLE_TEXTURE");
// 	RegisterAction(sf::Keyboard::Key::C, "TOGGLE_COLLISION");
// 	RegisterAction(sf::Keyboard::Key::G, "TOGGLE_GRID");
// 	RegisterAction(sf::Keyboard::Key::Y, "TOGGLE_CAMERA_TYPE");
// 	RegisterAction(sf::Keyboard::Key::A, "TO_LEFT");
// 	RegisterAction(sf::Keyboard::Key::D, "TO_RIGHT");
// 	RegisterAction(sf::Keyboard::Key::W, "TO_UP");
// 	RegisterAction(sf::Keyboard::Key::S, "TO_DOWN");
// 	RegisterAction(sf::Keyboard::Key::Num1, "TOGGLE_ASSET_MANAGER");

// 	m_gridText.setCharacterSize(12);
// 	m_gridText.setFont(m_gameApplication->GetAssets().GetFont("elementalis"));

// 	LoadLevel(levelPath);
// }

// void core::PlayScene::LoadLevel(const std::string &fileName)
// {
// 	ABYSS_INFO("Info...");
// 	ABYSS_WARNING("Warning...");
// 	ABYSS_ERROR("Error...");

// 	// TODO: Check how to better reset the manager
// 	m_entityManager = core::EntityManager();

// 	std::ifstream ifs(fileName, std::ifstream::in);

// 	std::string itemType;
// 	while (ifs.good())
// 	{
// 		ifs >> itemType;
// 		if (itemType.compare("Player") == 0)
// 		{
// 			ifs >> m_playerInfo.gridLocation.x >> m_playerInfo.gridLocation.y >> m_playerInfo.boundingBoxSize.x >>
// 				m_playerInfo.boundingBoxSize.y >> m_playerInfo.speed.x >> m_playerInfo.speed.y >>
// 				m_playerInfo.maxSpeed >> m_playerInfo.gravity >> m_playerInfo.bulletAnimation;
// 		}
// 	}

// 	SpawnPlayer();

// 	// should position the entity with the grid x,y read from the file
// 	// brick->AddComponent<Transform>(GridX, GridY, brick);
// }

// sf::Vector2f core::PlayScene::GridToMidPixel(float gridX, float gridY, std::shared_ptr<core::Entity> entity)
// {
// 	/* TODO: must return a vector2 indicating where the center position of the entity should be
// 	 * you must use the entity animation size to position it correctly
// 	 * the size of the grid width and height is stored in m_gridSize.x and m_gridSize.y
// 	 * the bottom left corner of th animation should be with the bottom left of the grid cell
// 	 */

// 	auto &spriteSize = entity->GetComponent<components::Anim>().animation.GetSize();
// 	return sf::Vector2f((gridX * m_gridSize.x) + (spriteSize.x / 2.0f),
// 						Height() - ((gridY * m_gridSize.y) + (spriteSize.y / 2.0f)));
// }

// void core::PlayScene::Render()
// {
// 	if (!m_paused)
// 	{
// 		m_gameApplication->GetWindow().clear(sf::Color::Black);
// 	}
// 	else
// 	{
// 		m_gameApplication->GetWindow().clear(sf::Color(104, 104, 104));
// 	}

// 	// auto& playerPos = m_player->GetComponent<core::components::Transform>().pos;
// 	// float windowCenterX = std::max(m_gameApplication->GetWindow().getSize().x / 2.0f, playerPos.x);
// 	// sf::View view = m_gameApplication->GetWindow().getView();
// 	// view.setCenter(sf::Vector2<float>(windowCenterX, m_gameApplication->GetWindow().getSize().y -
// 	// view.getCenter().y)); m_gameApplication->GetWindow().setView(view);

// 	for (auto e : m_entityManager.GetEntities())
// 	{
// 		if (m_drawTextures)
// 		{
// 			auto &transform = e->GetComponent<core::components::Transform>();
// 			if (e->HasComponent<core::components::Anim>())
// 			{
// 				// TODO: check if I can get the sprite and dont waste the calls to GetSprite
// 				auto &animation = e->GetComponent<core::components::Anim>();
// 				animation.animation.GetSprite().setRotation(sf::degrees(transform.angle));
// 				animation.animation.GetSprite().setPosition(sf::Vector2<float>(transform.pos.x, transform.pos.y));
// 				animation.animation.GetSprite().setScale(sf::Vector2<float>(transform.scale.x, transform.scale.y));

// 				m_gameApplication->GetWindow().draw(animation.animation.GetSprite());
// 			}
// 		}

// 		if (m_drawCollision)
// 		{
// 			if (e->HasComponent<core::components::BoundingBox>())
// 			{
// 				auto &boundingBox = e->GetComponent<core::components::BoundingBox>();
// 				auto &transform = e->GetComponent<core::components::Transform>();

// 				sf::RectangleShape rect;
// 				rect.setSize(sf::Vector2f(boundingBox.size.x - 1, boundingBox.size.y - 1));
// 				rect.setOrigin(sf::Vector2f(boundingBox.halfSize.x, boundingBox.halfSize.y));
// 				rect.setPosition(sf::Vector2<float>(transform.pos.x, transform.pos.y));
// 				rect.setFillColor(sf::Color(0, 0, 0, 0));
// 				rect.setOutlineColor(sf::Color(255, 255, 255, 255));
// 				rect.setOutlineThickness(1);
// 				m_gameApplication->GetWindow().draw(rect);
// 			}
// 		}
// 	}

// 	// room rx, ry
// 	// tile tx, ty
// 	// I need to do a vector2 that will track the room number (I will increment and decrement according with
// 	// the direction I go)
// 	// this will be multiplied by h and w of the window
// 	// the rest of the math is basically the same

// 	if (m_drawGrid)
// 	{
// 		DrawGrid();
// 	}

// 	sf::CircleShape circ;
// 	circ.setFillColor(sf::Color::Red);
// 	circ.setRadius(2.f);
// 	circ.setPosition(m_player->GetComponent<components::Anim>().animation.GetSprite().getPosition());
// 	m_gameApplication->GetWindow().draw(circ);

// 	// sf::Vertex v[] =
// 	//{
// 	//	sf::Vertex((m_player->GetComponent<components::Transform>().pos))
// 	// };

// 	// m_gameApplication->GetWindow().draw(v, 50, sf::Points);

// 	ImGui::SFML::Render(m_gameApplication->GetWindow());

// 	m_gameApplication->GetWindow().display();
// }

// // TODO: Re-implement the jump and check physics
// // TODO: Implement the maxmimum player speed in both x and y directions

// void core::PlayScene::MovementSystem()
// {
// 	auto &playerTransform = m_player->GetComponent<components::Transform>();
// 	// auto& playerJump = m_player->GetComponent<components::Jump>();
// 	sf::Vector2f playerVelocity;

// 	if (m_player->HasComponent<components::Input>())
// 	{
// 		auto &playerInput = m_player->GetComponent<components::Input>();

// 		if (playerInput.left)
// 		{
// 			playerVelocity.x -= m_playerInfo.speed.x;

// 			m_player->GetComponent<components::State>().state = "Left";
// 		}
// 		else if (playerInput.right)
// 		{
// 			playerVelocity.x += m_playerInfo.speed.x;

// 			m_player->GetComponent<components::State>().state = "Right";
// 		}

// 		if (playerInput.down)
// 		{
// 			playerVelocity.y += m_playerInfo.speed.y;

// 			m_player->GetComponent<components::State>().state = "Down";
// 		}

// 		if (playerInput.up)
// 		{
// 			playerVelocity.y -= m_playerInfo.speed.y;

// 			m_player->GetComponent<components::State>().state = "Up";
// 		}
// 	}

// 	playerTransform.velocity = playerVelocity;

// 	for (auto e : m_entityManager.GetEntities())
// 	{
// 		e->GetComponent<components::Transform>().previousPos = e->GetComponent<components::Transform>().pos;
// 		e->GetComponent<components::Transform>().pos +=
// 			e->GetComponent<components::Transform>().velocity * m_gameApplication->DeltaTime();
// 	}
// }

// void core::PlayScene::EnemySpawnerSystem()
// {
// }

// void core::PlayScene::CollisionSystem()
// {
// 	/*
// 	 * SFML (0,0) pos is on  the top-left corner
// 	 * this means jumping will have a negative y and gravity will have a positive y
// 	 * also, something below something else will have a y value greater than it
// 	 * also, something above something else will have a y value less than it
// 	 *
// 	 * TODO: implement bullet / tile collision
// 	 * destroy the tile if it has brick collision
// 	 *
// 	 * TODO: make a better animation system
// 	 *
// 	 * TODO: dont let the player walk off the map (left or right)
// 	 *
// 	 * TODO: make a big collider to block top collision instead of multiple mini box colliders
// 	 */

// 	for (auto e : m_entityManager.GetEntities())
// 	{
// 		sf::Vector2f overlap = m_physics.GetOverlap(m_player, e);
// 		if (overlap.x > 0 && overlap.y > 0)
// 		{
// 			auto &playerTransform = m_player->GetComponent<components::Transform>();
// 			auto &eTransform = e->GetComponent<components::Transform>();
// 			auto &playerBB = m_player->GetComponent<components::BoundingBox>();
// 			auto &eBB = e->GetComponent<components::BoundingBox>();

// 			sf::Vector2f previousOverlap = m_physics.GetPreviousOverlap(m_player, e);
// 			if (!e->GetComponent<components::BoundingBox>().isTrigger)
// 			{

// 				if (previousOverlap.y > 0)
// 				{
// 					if ((playerTransform.pos.x + playerBB.halfSize.x) < (eTransform.pos.x + eBB.halfSize.x))
// 					{
// 						playerTransform.pos.x -= overlap.x;
// 					}
// 					else if ((playerTransform.pos.x + playerBB.halfSize.x) > (eTransform.pos.x + eBB.halfSize.x))
// 					{
// 						playerTransform.pos.x += overlap.x;
// 					}
// 				}
// 				else if (previousOverlap.x > 0)
// 				{
// 					if ((playerTransform.pos.y + playerBB.halfSize.y) < (eTransform.pos.y + eBB.halfSize.y))
// 					{
// 						playerTransform.pos.y -= overlap.y;
// 						playerTransform.velocity.y = 0;

// 						m_player->GetComponent<components::Jump>().isJumping = false;
// 						m_player->GetComponent<components::Input>().hitCounter = 0;
// 						m_player->GetComponent<components::Jump>().jumpTime = 0;
// 						// m_player->GetComponent<components::Input>().up = false;

// 						// TODO: try using a modifier count so I can block going left and right
// 					}
// 					else if ((playerTransform.pos.y + playerBB.halfSize.y) > (eTransform.pos.y + eBB.halfSize.y))
// 					{
// 						playerTransform.pos.y += overlap.y;

// 						m_player->GetComponent<components::Jump>().jumpTime = 0.0f;
// 						m_player->GetComponent<components::Jump>().isJumping = false;
// 						playerTransform.velocity = sf::Vector2f(0.0f, 0.0f);
// 					}
// 				}
// 			}
// 			else
// 			{
// 				if (e->Tag() == core::EntityTag::Dangerous)
// 				{
// 					if (playerTransform.pos.y + 0.2f > eTransform.pos.y)
// 					{
// 						if (playerTransform.pos.x < eTransform.pos.x - 50.0f ||
// 							eTransform.pos.x + 50.0f < playerTransform.pos.x)
// 						{
// 							continue;
// 						}

// 						OnEnd();
// 					}

// 					// TODO: make the player respawn instead of returning to the menu
// 					// TODO: maybe apply some damage and reset player position instead of returning to menu
// 				}
// 				else if (e->Tag() == core::EntityTag::Default)
// 				{
// 					if (playerTransform.pos.y + 0.2f > eTransform.pos.y)
// 					{
// 						if (playerTransform.pos.x < eTransform.pos.x - 50.0f ||
// 							eTransform.pos.x + 50.0f < playerTransform.pos.x)
// 						{
// 							continue;
// 						}

// 						int index = m_gameApplication->GetGameManager().sceneIndex;
// 						m_gameApplication->GetGameManager().clearedLevels[index] = true;

// 						OnEnd();
// 					}
// 				}
// 			}
// 		}

// 		// TODO: add enemy collision later
// 	}
// }

// void core::PlayScene::AnimationSystem()
// {
// 	auto &playerInput = m_player->GetComponent<components::Input>();

// 	if (m_player->GetComponent<core::components::State>().state == "Down")
// 	{
// 		if (m_player->GetComponent<components::Anim>().animation.GetName() != "Down")
// 		{
// 			m_player->AddComponent<components::Anim>(m_gameApplication->GetAssets().GetAnimation("Down"), true);
// 		}

// 		/*auto& playerTransform = m_player->GetComponent<components::Transform>();
// 		if (playerInput.left)
// 		{
// 			playerTransform.scale.x = -1;
// 		}
// 		else if (playerInput.right)
// 		{
// 			playerTransform.scale.x = 1;
// 		}*/
// 	}
// 	else if (m_player->GetComponent<core::components::State>().state == "Up")
// 	{
// 		if (m_player->GetComponent<components::Anim>().animation.GetName() != "Up")
// 		{
// 			m_player->AddComponent<components::Anim>(m_gameApplication->GetAssets().GetAnimation("Up"), true);
// 		}
// 	}
// 	else if (m_player->GetComponent<core::components::State>().state == "Left")
// 	{
// 		if (m_player->GetComponent<components::Anim>().animation.GetName() != "Left")
// 		{
// 			m_player->AddComponent<components::Anim>(m_gameApplication->GetAssets().GetAnimation("Left"), true);
// 		}
// 	}
// 	else if (m_player->GetComponent<core::components::State>().state == "Right")
// 	{
// 		if (m_player->GetComponent<components::Anim>().animation.GetName() != "Right")
// 		{
// 			m_player->AddComponent<components::Anim>(m_gameApplication->GetAssets().GetAnimation("Right"), true);
// 		}
// 	}

// 	// TEST, REMOVE THIS SHIT LATER
// 	for (auto e : m_entityManager.GetEntities())
// 	{
// 		if (e->HasComponent<core::components::Anim>())
// 		{
// 			e->GetComponent<core::components::Anim>().animation.Update();

// 			if (!e->GetComponent<core::components::Anim>().repeat)
// 			{
// 				e->Destroy();
// 			}
// 		}
// 	}
// }

// void core::PlayScene::CameraSystem()
// {
// 	sf::View view = m_gameApplication->GetWindow().getView();
// 	auto &t = m_player->GetComponent<core::components::Transform>();

// 	// x room
// 	if (t.pos.x < m_midPointX - m_halfWidth)
// 	{
// 		m_room.x--;
// 		float x = m_room.x * Width();
// 		m_midPointX = x == 0 ? m_halfWidth : x + m_halfWidth;
// 	}
// 	else if (t.pos.x > m_midPointX + m_halfWidth)
// 	{
// 		m_room.x++;
// 		float x = m_room.x * Width();
// 		m_midPointX = x == 0 ? m_halfWidth : x - m_halfWidth;
// 	}

// 	// y room
// 	if (t.pos.y < m_midPointY - m_halfHeight)
// 	{
// 		m_room.y--;
// 		float y = m_room.y * Height();
// 		m_midPointY = y == 0 ? m_halfHeight : y + m_halfHeight;
// 	}
// 	else if (t.pos.y > m_midPointY + m_halfHeight)
// 	{
// 		m_room.y++;
// 		float y = m_room.y * Height();
// 		m_midPointY = y == 0 ? m_halfHeight : y - m_halfHeight;
// 	}

// 	if (m_follow)
// 	{
// 		// calculate view for player follow camera
// 		view.setCenter(t.pos);
// 	}
// 	else
// 	{
// 		// calculate view for room-base camera
// 		view.setCenter(sf::Vector2f(m_midPointX, m_midPointY));
// 	}

// 	m_gameApplication->GetWindow().setView(view);
// }

// void core::PlayScene::SpawnPlayer()
// {
// 	m_player = m_entityManager.AddEntity(core::EntityTag::Player);

// 	// always add the animation first, so that gridToMidPixel can compute correctly
// 	m_player->AddComponent<core::components::Anim>(m_gameApplication->GetAssets().GetAnimation("Down"), true);
// 	m_player->AddComponent<core::components::Transform>(sf::Vector2f(72, 300));
// 	m_player->AddComponent<core::components::BoundingBox>(m_playerInfo.boundingBoxSize, false);
// 	m_player->AddComponent<core::components::Input>();
// }

// void core::PlayScene::OnEnd()
// {
// 	m_gameApplication->ChangeScene("MENU", std::make_shared<core::MenuScene>(m_gameApplication));
// }

// void core::PlayScene::ExecuteAction(const core::Action &action)
// {
// 	if (action.State() == core::ActionState::Start)
// 	{
// 		if (action.Name() == "TOGGLE_TEXTURE")
// 		{
// 			m_drawTextures = !m_drawTextures;
// 		}
// 		else if (action.Name() == "TOGGLE_COLLISION")
// 		{
// 			m_drawCollision = !m_drawCollision;
// 		}
// 		else if (action.Name() == "TOGGLE_GRID")
// 		{
// 			m_drawGrid = !m_drawGrid;
// 		}
// 		else if (action.Name() == "TOGGLE_CAMERA_TYPE")
// 		{
// 			m_follow = !m_follow;
// 		}
// 		else if (action.Name() == "PAUSE")
// 		{
// 			SetPaused(!m_paused);
// 		}
// 		else if (action.Name() == "QUIT")
// 		{
// 			OnEnd();
// 		}
// 		else if (action.Name() == "LEFT_CLICK")
// 		{
// 			m_selectedEntity = {};
// 			sf::Vector2f worldPos =
// 				m_gameApplication->GetWindow().mapPixelToCoords(sf::Vector2i(action.Pos().x, action.Pos().y));

// 			for (auto e : m_entityManager.GetEntities())
// 			{
// 				if (m_physics.IsInside(abyss_math::Vec2<float>(worldPos.x, worldPos.y), e))
// 				{
// 					m_isEntityInfoOpen = true;
// 					m_selectedEntity = e;
// 					break;
// 				}
// 			}
// 		}
// 		else if (action.Name() == "TOGGLE_ASSET_MANAGER")
// 		{
// 			m_isAssetManagerOpen = !m_isAssetManagerOpen;
// 		}

// 		if (action.Name() == "TO_LEFT")
// 		{
// 			m_player->GetComponent<components::Input>().left = true;
// 		}
// 		else if (action.Name() == "TO_RIGHT")
// 		{
// 			m_player->GetComponent<components::Input>().right = true;
// 		}
// 		else if (action.Name() == "TO_UP")
// 		{
// 			m_player->GetComponent<components::Input>().up = true;
// 		}
// 		else if (action.Name() == "TO_DOWN")
// 		{
// 			m_player->GetComponent<components::Input>().down = true;
// 		}
// 	}
// 	else if (action.State() == core::ActionState::End)
// 	{
// 		if (action.Name() == "TO_LEFT")
// 		{
// 			m_player->GetComponent<components::Input>().left = false;
// 		}
// 		else if (action.Name() == "TO_RIGHT")
// 		{
// 			m_player->GetComponent<components::Input>().right = false;
// 		}
// 		else if (action.Name() == "TO_UP")
// 		{
// 			m_player->GetComponent<components::Input>().up = false;
// 		}
// 		else if (action.Name() == "TO_DOWN")
// 		{
// 			m_player->GetComponent<components::Input>().down = false;
// 		}
// 	}
// }

// void core::PlayScene::DrawGrid()
// {
// 	float leftX = m_midPointX - Width();
// 	float rightX = m_midPointX + Width();
// 	float nextGridX = leftX - std::fmod(leftX, m_gridSize.x);

// 	float topY = m_midPointY - Height();
// 	float bottomY = m_midPointY + Height();
// 	float nextGridY = topY - std::fmod(topY, m_gridSize.y);

// 	// draw Y lines
// 	for (float x = nextGridX; x < rightX; x += m_gridSize.x)
// 	{
// 		DrawLine(sf::Vector2f(x, topY), sf::Vector2f(x, bottomY));
// 	}

// 	// draw X lines
// 	for (float y = nextGridY; y < bottomY; y += m_gridSize.y)
// 	{
// 		DrawLine(sf::Vector2f(leftX, y), sf::Vector2f(rightX, y));

// 		// draw text inside grid
// 		for (float x = nextGridX; x < rightX; x += m_gridSize.x)
// 		{
// 			int xCell = static_cast<int>(std::floor(x / m_gridSize.x));
// 			int yCell = static_cast<int>(std::floor(y / m_gridSize.y));

// 			m_gridText.setString("(" + std::to_string(xCell) + "," + std::to_string(yCell) + ")");
// 			m_gridText.setPosition(sf::Vector2<float>(x + 3, y + 2));
// 			m_gameApplication->GetWindow().draw(m_gridText);
// 		}
// 	}
// }
