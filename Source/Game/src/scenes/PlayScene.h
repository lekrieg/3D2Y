#ifndef PLAY_SCENE_H
#define PLAY_SCENE_H

#include "../FileData.h"
#include "../core/Physics.h"
#include "../core/Scene.h"
#include "SFML/Graphics/Font.hpp"

#include <iostream>
#include <string>

namespace core
{
	class PlayScene : public Scene
	{
			PlayerInfo m_playerInfo;
			std::string m_levelPath;
			std::shared_ptr<core::Entity> m_player;
			bool m_drawTextures = true;
			bool m_drawCollision = false;
			bool m_drawGrid = false;
			bool m_follow = false;
			sf::Vector2f m_gridSize = { 64, 64 };
			sf::Text m_gridText;
			Physics m_physics;

			abyss_math::Vec2<int> m_room = { 0, 0 };
			float m_leftXOffset = 0;
			float m_rightXOffset = Width();
			float m_topOffset = 0;
			float m_bottomOffset = Height();
			float m_midPointX = Width() / 2.0f;
			float m_midPointY = Height() / 2.0f;
			float m_halfWidth = Width() / 2.0f;
			float m_halfHeight = Height() / 2.0f;

		protected:

			void Init(const std::string &levelPath) override;
			void OnEnd() override;

		public:

			PlayScene(core::GameApplication *gameApplication, const std::string &levelPath, const sf::Font commonFont) :
				Scene(gameApplication),
				m_levelPath(levelPath),
				m_gridText(commonFont)
			{
				Init(m_levelPath);
			}

			void Update(float deltaTime) override;
			void Render() override;
			void ExecuteAction(const core::Action &action) override;

		private:

			void LoadLevel(const std::string &fileName);

			sf::Vector2f GridToMidPixel(float gridX, float gridY, std::shared_ptr<core::Entity> entity);
			sf::Vector2f GetPosition(int rx, int ry, int tx, int ty) const;
			// this function takes room (r) and t(tile) coordinates and returns the vec2f game world position of the
			// center of the entity

			void MovementSystem();
			void EnemySpawnerSystem();
			void CollisionSystem();
			// - entity - tile collision
			// - player - enemy collision
			// - sword - npc collision
			// - entity - item collision
			// - black tile collision / teleporting

			void AnimationSystem();

			void AISystem();
			// - implements follow behavior
			// - implements patrol behavior

			void CameraSystem();
			// implement camera view logic

			void StatusSystem();
			// - implement lifespan here
			// - implement invencibility frames here
			// - component must be added on the player when hit
			// - it is removed when duration reachs 0

			// TODO: add spawn bullet method
			void SpawnPlayer();

			void SpawnSword(std::shared_ptr<Entity> e);
			// - should be given the apropriate lifespan
			// - spawn at the appropriate location based on player's facing direction
			// - be given damage value of 1
			// - shoulud play a slash sound

			void DrawGrid();
	};
}

#endif // !PLAY_SCENE_H
