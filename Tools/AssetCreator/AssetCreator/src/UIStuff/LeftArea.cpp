//
// Created by lekrieg on 17/07/25.
//

#include "LeftArea.h"

#include "SFML/System/Vector2.hpp"
#include "../imgui/imgui-SFML.h"
#include "../imgui/imgui.h"

#include "../Application.h"

void LeftArea::Init(Application* app)
{
    m_app = app;
}

void LeftArea::Update()
{
    DrawLeftPanel();
}

void LeftArea::DrawLeftPanel()
{
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));

    if (ImGui::Begin("Viewport"))
    {
        auto& fileDialogType = m_app->GetFileDialogType();
        if (ImGui::Button("Open image"))
        {
            ABYSS_INFO("IMG!")

            fileDialogType = FileDialogType::Texture;
            m_app->SpriteInfoOpen() = false;

            m_app->GetFileDialog().SetTypeFilters({ ".png", ".jpeg" });
            m_app->GetFileDialog().SetFlagOptions(0 | ImGuiFileBrowserFlags_CloseOnEsc);
            m_app->GetFileDialog().Open();
        }

        m_app->GetFileDialog().Display();

        if (fileDialogType == FileDialogType::Texture && m_app->GetFileDialog().HasSelected())
        {
            std::string path = m_app->GetFileDialog().GetSelected().string();
            m_app->GetFileName() = m_app->GetFileDialog().GetSelected().filename().string();

            if (!m_app->GetTexture().loadFromFile(path))
            {
                ABYSS_ERROR("Failed to load texture!")
            }

            m_app->GetFilePath() = path;

            if (!m_app->GetRenderTexture().resize(m_app->GetTexture().getSize()))
            {
                ABYSS_ERROR("Failed to resize render texture!")
            }

            m_app->GetFileDialog().ClearSelected();
        }

        ImGui::SameLine(ImGui::GetWindowWidth() - 200 - ImGui::GetStyle().WindowPadding.x);

        ImGui::BeginGroup();
        {
            static int i0 = 1;
            if (i0 < 0)
            {
                i0 = 0;
            }
            ImGui::PushItemWidth(90);
            ImGui::InputInt("Scale", &i0);

            if (ImGui::Button("Apply", ImVec2(45, 20)))
            {
                m_app->SetScale(i0);
                ABYSS_INFO("SCALE APPLIED!")

                const int s = m_app->GetScale();
                if (!m_app->GetRenderTexture().resize(sf::Vector2u((m_app->GetTexture().getSize().x * s), (m_app->GetTexture().getSize().y * s))))
                {
                    ABYSS_ERROR("Failed to resize render texture!")
                }
            }
            ImGui::EndGroup();
        }

        ImVec2 currentSize = ImGui::GetContentRegionAvail();
        static ImVec2 previousSize;

        if ((currentSize.x != previousSize.x) || (currentSize.y != previousSize.y))
        {
            previousSize = currentSize;
            currentSize = ImGui::GetContentRegionAvail();
        }

        ImGui::BeginChild("ScrollingRegion", ImVec2(currentSize.x, currentSize.y), true, ImGuiWindowFlags_AlwaysHorizontalScrollbar);
        ImGui::Image(m_app->GetRenderTexture());
        ImGui::EndChild();
    }

    ImGui::End();
    ImGui::PopStyleVar();
    // ImGui::PopFont();

    sf::Sprite sprite(m_app->GetTexture());
    const int s = m_app->GetScale();
    sprite.setScale(sf::Vector2f(s, s));

    m_app->GetRenderTexture().clear(sf::Color::Black);
    m_app->GetRenderTexture().draw(sprite);
    m_app->GetRenderTexture().display();
}