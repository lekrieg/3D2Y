//
// Created by lekrieg on 18/07/25.
//

#include "RightArea.h"

#include "../Application.h"
#include "../imgui/imgui.h"
#include "../imgui//imgui-SFML.h"
#include "../Logger.h"

void RightArea::Init(Application *app)
{
    m_app = app;

    m_spriteTypes = abyss::enums::GetSpriteTypeNames();
}

void RightArea::Update()
{
    DrawRightArea();
}

void RightArea::DrawRightArea()
{
    ImGui::ShowDemoWindow();

    DrawTopMenuBar();
}

void RightArea::DrawTopMenuBar()
{
    if (ImGui::Begin("Asset stuff"))
    {
        if (ImGui::Button("Load asset"))
        {
            ABYSS_INFO("L!")
        }

        ImGui::SameLine();

        if (ImGui::Button("Save asset"))
        {
            ABYSS_INFO("S!")
        }

        DrawSpritesStuff();
        DrawAudiosStuff();
        DrawFontsStuff();
    }

    if (m_openSpriteInfo)
    {
        DrawSpriteInfo();
    }

    ShowWarningModal(popupMessage);

    ImGui::End();
}

void RightArea::DrawSpriteInfo()
{
    const auto& sprite =  m_app->GetSelectedSprite();
    if (ImGui::Begin("Sprite info", &m_openSpriteInfo))
    {
        DrawSpriteTypeCombobox();

        ImGui::Separator();

        ImGui::Text(sprite->assetName);
        ImGui::PushItemWidth(90);
        if (ImGui::Button("Edit name"))
        {
            ImGui::OpenPopup("edit_name_popup");
        }
        if (ImGui::BeginPopup("edit_name_popup"))
        {
            ImGui::InputText("Name", sprite->assetName, IM_ARRAYSIZE(sprite->assetName));
            ImGui::EndPopup();
        }

        ImGui::Separator();

        DrawAnimationArea();
    }

    ShowWarningModal(popupMessage);

    ImGui::End();
}

void RightArea::DrawSpritesStuff()
{
    if (!ImGui::CollapsingHeader("Sprites"))
    {
        std::string path = m_app->GetFilePath();

        if (ImGui::Button("New"))
        {
            if (path.empty())
            {
                ImGui::OpenPopup("WarningPopup");
                m_warningPopupOpen = true;
                popupMessage = "You need to open a texture before creating a sprite!";
            }
            else
            {
                if (!m_app->GetUsedTextures()[path])
                {
                    m_app->GetUsedTextures()[std::move(path)] = std::make_shared<sf::Texture>(m_app->GetTexture());
                }

                auto s = std::make_shared<abyss::asset_info::SpriteAsset>(path);
                s->AddAnimation();
                m_app->GetSprites().emplace_back(s);
            }
        }

        if (ImGui::BeginTable("SpriteTable", 4))
        {
            static int imgButtonId = 0;
            for (const auto& sprite : m_app->GetSprites())
            {
                ImGui::TableNextColumn();
                sf::Sprite s(*m_app->GetUsedTextures()[sprite->filePath]);
                s.setOrigin(sprite->defaultFrame->halfSize[0]);
                s.setTextureRect(sf::IntRect(sf::Vector2<int>(
                    sprite->defaultFrame->position[0].x * static_cast<int>(sprite->defaultFrame->size[0].x), sprite->defaultFrame->position[0].y * static_cast<int>(sprite->defaultFrame->size[0].y)),
                    sf::Vector2<int>(static_cast<int>(sprite->defaultFrame->size[0].x), static_cast<int>(sprite->defaultFrame->size[0].y))));

                if (ImGui::ImageButton("ImgButton##" + imgButtonId, s, sf::Vector2f(32, 32)))
                {
                    m_openSpriteInfo = true;
                    m_app->SetSelectedSprite(sprite);
                }

                imgButtonId++;
            }

            imgButtonId = 0;
            ImGui::EndTable();
        }
    }
}

void RightArea::DrawAudiosStuff()
{
    if (!ImGui::CollapsingHeader("Audios"))
    {
    }
}

void RightArea::DrawFontsStuff()
{
    if (!ImGui::CollapsingHeader("Fonts"))
    {
    }
}

void RightArea::DrawSpriteTypeCombobox()
{
    auto& sprite = m_app->GetSelectedSprite();

    static ImGuiComboFlags flags = 0;
    const std::string tagString = abyss::enums::SpriteTypeToString(sprite->spriteType);

    static int itemSelectedIndex = 0;
    for (int i = 0; i < m_spriteTypes.size(); i++)
    {
        if (strcmp(m_spriteTypes[i].c_str(), tagString.c_str()) == 0)
        {
            itemSelectedIndex = i;
            break;
        }
    }

    if (const char* comboPreviewValue = m_spriteTypes[itemSelectedIndex].c_str(); ImGui::BeginCombo("Type", comboPreviewValue, flags))
    {
        static ImGuiTextFilter filter;
        if (ImGui::IsWindowAppearing())
        {
            ImGui::SetKeyboardFocusHere();
            filter.Clear();
        }
        ImGui::SetNextItemShortcut(ImGuiMod_Ctrl | ImGuiKey_F);
        filter.Draw("##Filter", -FLT_MIN);

        for (int n = 0; n < m_spriteTypes.size(); n++)
        {
            const bool is_selected = (itemSelectedIndex == n);
            if (filter.PassFilter(m_spriteTypes[n].c_str()))
            {
                if (ImGui::Selectable(m_spriteTypes[n].c_str(), is_selected))
                {
                    itemSelectedIndex = n;
                    sprite->spriteType = abyss::enums::StringToSpriteType(m_spriteTypes[itemSelectedIndex].c_str());
                    break;
                }
            }
        }
        ImGui::EndCombo();
    }
}

void RightArea::DrawAnimationArea()
{
    auto& sprite = m_app->GetSelectedSprite();

    ImGui::Text("Animations");
    if (ImGui::Button("+"))
    {
        sprite->AddAnimation();
    }

    ImGui::SameLine(ImGui::GetWindowWidth() - 150 - ImGui::GetStyle().WindowPadding.x);
    static int animeSpeed = 0;
    ImGui::InputInt("Speed", &animeSpeed);

    animeSpeed = animeSpeed < 0 ? 0 : animeSpeed;
    if (animeSpeed >= 0 && animeSpeed != sprite->speed)
    {
        sprite->speed = animeSpeed;
    }

    int i = 0;
    for (const auto& anim : sprite->animations)
    {
        // Use SetNextItemOpen() so set the default state of a node to be open. We could
        // also use TreeNodeEx() with the ImGuiTreeNodeFlags_DefaultOpen flag to achieve the same thing!
        if (i == 0)
        {
            ImGui::SetNextItemOpen(true, ImGuiCond_Once);
        }

        // Here we use PushID() to generate a unique base ID, and then the "" used as TreeNode id won't conflict.
        // An alternative to using 'PushID() + TreeNode("", ...)' to generate a unique ID is to use 'TreeNode((void*)(intptr_t)i, ...)',
        // aka generate a dummy pointer-sized value to be hashed. The demo below uses that technique. Both are fine.
        ImGui::PushID(i);
        if (ImGui::TreeNode("", anim->name))
        {
            if (m_app->GetUsedTextures()[m_app->GetSelectedSprite()->filePath])
            {
                DrawFrames(anim);
            }

            ImGui::PushItemWidth(90);
            if (ImGui::Button("Edit name"))
            {
                ImGui::OpenPopup("edit_name_popup");
            }
            if (ImGui::BeginPopup("edit_name_popup"))
            {
                ImGui::InputText("Name##" + i, anim->name, IM_ARRAYSIZE(anim->name));
                ImGui::EndPopup();
            }

            ImGui::Text("Animation frame");
            ImGui::SameLine();
            if (ImGui::Button("+"))
            {
                anim->AddFrame(sf::Vector2f(32, 32));
            }

            ImGui::Separator();
            for (int j = 0; j < anim->size.size(); j++)
            {
                float newSize[] = {anim->size[j].x, anim->size[j].y};
                ImGui::PushID(j + i);
                ImGui::InputFloat2("Size", newSize);
                anim->SetSize(sf::Vector2f(newSize[0], newSize[1]), j);
                ImGui::PopID();

                int newPos[] = {anim->position[j].x, anim->position[j].y};
                ImGui::PushID(j + i);
                ImGui::InputInt2("Position", newPos);
                anim->position[j].x = newPos[0];
                anim->position[j].y = newPos[1];
                ImGui::PopID();
            }
            ImGui::Separator();

            ImGui::TreePop();
        }
        ImGui::PopID();

        i++;
    }
}

void RightArea::DrawFrames(const std::shared_ptr<abyss::asset_info::Animation>& anim)
{
    int scale = m_app->GetScale();
    for (int i = 0; i < anim->size.size(); i++)
    {
        sf::RectangleShape rect;
        rect.setSize(sf::Vector2f(anim->size[i].x * scale, anim->size[i].y * scale));
        rect.setOrigin(sf::Vector2f(anim->halfSize[i].x * scale, anim->halfSize[i].y * scale));
        rect.setPosition(sf::Vector2(((anim->size[i].x * anim->position[i].x) + anim->halfSize[i].x) * scale, ((anim->size[i].y * anim->position[i].y) + anim->halfSize[i].y) * scale));
        rect.setFillColor(sf::Color(0, 0, 0, 0));
        rect.setOutlineColor(sf::Color(255, 0, 0, 255));
        rect.setOutlineThickness(1);
        m_app->GetRenderTexture().draw(rect);
    }
}
