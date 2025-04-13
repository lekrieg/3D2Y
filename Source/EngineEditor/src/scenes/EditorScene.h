#ifndef PLAY_SCENE_H
#define PLAY_SCENE_H

#include "Application.h"
#include "SFML/Graphics/Font.hpp"
#include "Scene.h"
#include "Physics.h"
#include "math/Vectors.h"

#include <string>

namespace editor
{
	class EditorScene : public abyss::Scene
	{
	        // maybe I could use a list of function pointers to add the components to UI
			// so I would have a dropdown to select what I want and add it in whatever sequence I want
			std::shared_ptr<abyss::Entity> m_selectedEntity;
			std::shared_ptr<abyss::Entity> m_dragEntity;
			std::string m_levelPath;
			bool m_drawTextures = true;
			bool m_drawCollision = false;
			bool m_drawGrid = false;
			bool m_follow = false;
			bool m_snapToGrid = true;
			bool m_isEntityInfoOpen = false;
			bool m_isAssetManagerOpen = false;
			bool m_leftClick = false;
			sf::Vector2f m_gridSize = { 64, 64 };
			sf::Text m_gridText;
			abyss::Physics m_physics;

			abyss::math::Vec2<float> m_oldPos;
			abyss::math::Vec2<int> m_room = { 0, 0 };
			float m_leftXOffset = 0;
			float m_rightXOffset = Width();
			float m_topOffset = 0;
			float m_bottomOffset = Height();
			float m_midPointX = Width() / 2.0f;
			float m_midPointY = Height() / 2.0f;
			float m_halfWidth = Width() / 2.0f;
			float m_halfHeight = Height() / 2.0f;
			float accumulatedZoom = 1;
			float actualZoom = accumulatedZoom;

		protected:

			void Init(const std::string &levelPath) override;
			void OnEnd() override;

		public:

			EditorScene(abyss::Application *editorApplication, const std::string &levelPath, const sf::Font commonFont) :
				Scene(editorApplication),
				m_levelPath(levelPath),
				m_gridText(commonFont)
			{
				Init(m_levelPath);
			}

			void Update(float deltaTime) override;
			void Render() override;
			void ExecuteAction(const abyss::Action &action) override;

			void EntityInfoGui();
			void AssetManagerGui();

		private:

			void LoadLevel(const std::string &fileName);

			sf::Vector2f GridToMidPixel(float gridX, float gridY, std::shared_ptr<abyss::Entity> entity);
			sf::Vector2f GetPosition(int rx, int ry, int tx, int ty) const;

			void AnimationSystem();
			void CameraSystem();

			void DrawGrid();
	};
}

#endif // !PLAY_SCENE_H
