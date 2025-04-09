#include "Scene.h"
#include "SFML/Graphics/PrimitiveType.hpp"
#include "SFML/System/Vector2.hpp"

#include "../imgui/imgui-SFML.h"
#include "../imgui/imgui.h"

int core::Scene::Width() const
{
	return m_gameApplication->GetWindow().getSize().x;
}

int core::Scene::Height() const
{
	return m_gameApplication->GetWindow().getSize().y;
}

void core::Scene::DrawLine(sf::Vector2<float> p1, sf::Vector2f p2)
{
	std::array line =
	{
		sf::Vertex{ p1 },
		sf::Vertex{ p2 }
	};

	m_gameApplication->GetWindow().draw(line.data(), line.size(), sf::PrimitiveType::Lines);
}

void core::Scene::EntityInfoGui()
{
   	if (!m_selectedEntity || !m_isEntityInfoOpen)
	{
	   return;
	}

    ImGui::Begin("Entity Info", &m_isEntityInfoOpen);

	ImGui::End();
}

void core::Scene::AssetManagerGui()
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
			if (ImGui::BeginTable("TableTest", 5))
			{
				for (auto &a : m_gameApplication->GetAssets().GetAnimations())
				{
					ImGui::ImageButton(a.first.c_str(), a.second.GetSprite(), a.second.GetSize());
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
