//
// Created by lekrieg on 18/07/25.
//

#include "RightArea.h"

#include <fstream>

#include "../Application.h"
#include "../imgui/imgui.h"
#include "../imgui//imgui-SFML.h"
#include "../Logger.h"
#include "../Serialization/Serializer.h"
#include "../Utils/FileDialogType.h"
#include "../Logger.h"
#include "yaml-cpp/emitter.h"
#include "yaml-cpp/exceptions.h"
#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/parse.h"

void RightArea::Init(Application *app)
{
    m_app = app;

    m_spriteTypes = GetSpriteTypeNames();
}

void RightArea::Update()
{
    DrawRightArea();

    RemoveDeadItems<std::vector<std::shared_ptr<SpriteAsset>>&, std::shared_ptr<SpriteAsset>>(m_app->GetSprites());
    RemoveDeadItems<std::vector<std::shared_ptr<AudioAsset>>&, std::shared_ptr<AudioAsset>>(m_app->GetAudios());
    RemoveDeadItems<std::vector<std::shared_ptr<FontAsset>>&, std::shared_ptr<FontAsset>>(m_app->GetFonts());

    for (const auto& s : m_app->GetSprites())
    {
        RemoveDeadItems<std::vector<std::shared_ptr<Animation>>&, std::shared_ptr<Animation>>(s->animations);

        for (const auto& a : s->animations)
        {
            RemoveDeadItems<std::vector<std::shared_ptr<Frame>>&, std::shared_ptr<Frame>>(a->frames);
        }
    }
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
        auto& fileDialogType = m_app->GetFileDialogType();
        if (ImGui::Button("Load asset"))
        {
            m_app->SpriteInfoOpen() = false;

            m_app->GetFileDialog().SetTypeFilters({ ".asset" });
            m_app->GetFileDialog().SetFlagOptions(0 | ImGuiFileBrowserFlags_CloseOnEsc);
            fileDialogType = FileDialogType::Load;
            m_app->GetFileDialog().Open();
        }

        ImGui::SameLine();

        if (ImGui::Button("Save asset"))
        {
            m_app->GetFileDialog().SetTypeFilters({ ".asset" });
            m_app->GetFileDialog().SetFlagOptions(0 | ImGuiFileBrowserFlags_CloseOnEsc | ImGuiFileBrowserFlags_EnterNewFilename | ImGuiFileBrowserFlags_CreateNewDir);
            fileDialogType = FileDialogType::Save;
            m_app->GetFileDialog().Open();
        }

        if ((fileDialogType == FileDialogType::Load || fileDialogType == FileDialogType::Save) && m_app->GetFileDialog().HasSelected())
        {
            std::string path = m_app->GetFileDialog().GetSelected().string();
            m_abyssPath = m_app->GetFileDialog().GetSelected().remove_filename().string();

            switch (fileDialogType)
            {
                case FileDialogType::Save:
                    m_assetFilePath = path.empty() ? "DefaultName.asset" : path;
                    if (m_assetFilePath.find(".asset") == std::string::npos)
                    {
                        m_assetFilePath.append(".asset");
                    }

                    ArchiveData();
                    Serialize(m_assetFilePath);
                    break;
                case FileDialogType::Load:
                    Deserialize(path);
                    break;
                case FileDialogType::Texture:
                case FileDialogType::None:
                    break;
            }

            m_app->GetFileDialog().ClearSelected();
        }

        DrawSpritesStuff();
        DrawAudiosStuff();
        DrawFontsStuff();

        m_app->GetFileDialog().Display();
    }

    if (m_app->SpriteInfoOpen())
    {
        DrawSpriteInfo();
    }

    if (m_app->AutoCutOpen())
    {
        DrawAutoCutStuff();
    }

    ShowWarningModal(popupMessage);

    ImGui::End();
}

void RightArea::DrawSpriteInfo()
{
    const auto& sprite =  m_app->GetSelectedSprite();
    if (ImGui::Begin("Sprite info", &m_app->SpriteInfoOpen()))
    {
        DrawSpriteTypeCombobox();

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
                if (m_app->GetFileNames()[path].empty())
                {
                    m_app->GetFileNames()[path] = m_app->GetFileName();
                }

                auto s = std::make_shared<SpriteAsset>(path);
                s->fileName = m_app->GetFileName();
                s->AddAnimation();
                m_app->GetSprites().emplace_back(s);
            }
        }

        ImGui::SameLine();

        if (ImGui::Button("Auto cut"))
        {
            if (path.empty())
            {
                ImGui::OpenPopup("WarningPopup");
                m_warningPopupOpen = true;
                popupMessage = "You need to open a texture before creating a sprite!";
            }
            else
            {
                m_app->AutoCutOpen() = true;
            }
        }

        if (ImGui::BeginTable("SpriteTable", 4))
        {
            int imgButtonId = 0;
            for (const auto& sprite : m_app->GetSprites())
            {
                // m_app->LoadTexture(sprite->filePath);

                ImGui::TableNextColumn();
                sf::Sprite s(*m_app->GetUsedTextures()[sprite->filePath]);
                s.setOrigin(sprite->animations[0]->frames[0]->halfSize);
                s.setTextureRect(sf::IntRect(sf::Vector2<int>(
                    sprite->animations[0]->frames[0]->position.x,
                    sprite->animations[0]->frames[0]->position.y),
                    sf::Vector2<int>(static_cast<int>(sprite->animations[0]->frames[0]->size.x), static_cast<int>(sprite->animations[0]->frames[0]->size.y))));

                ImGui::PushID(UniqueId(imgButtonId));
                if (ImGui::ImageButton("ImgButton", s, sf::Vector2f(32, 32)))
                {
                    m_app->GetFilePath() = sprite->filePath;

                    m_app->SpriteInfoOpen() = true;

                    if (!m_app->GetRenderTexture().resize(m_app->GetUsedTextures()[sprite->filePath]->getSize()))
                    {
                        ABYSS_ERROR("Failed to resize render texture!");
                    }

                    m_app->SetSelectedSprite(sprite);
                }

                ImGui::PopID();

                std::string popupName = "delete_popup" + std::to_string(imgButtonId);
                if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(1))
                {
                    ImGui::OpenPopup(popupName.c_str());
                }

                if (ImGui::BeginPopup(popupName.c_str()))
                {
                    ImGui::PushItemWidth(90);
                    ImGui::PushID(UniqueId(imgButtonId));
                    if (ImGui::Button("Delete"))
                    {
                        sprite->isActive = false;
                        m_app->SpriteInfoOpen() = false;
                    }
                    ImGui::PopID();

                    ImGui::EndPopup();
                }

                imgButtonId++;
            }
            ImGui::EndTable();
        }
    }
}

void RightArea::DrawAudiosStuff()
{
    if (!ImGui::CollapsingHeader("Audios"))
    {
        auto& audios = m_app->GetAudios();
        auto& fileDialog = m_app->GetFileDialog();

        ImGui::PushID(UniqueId(__LINE__));
        if (ImGui::Button("+"))
        {
            audios.emplace_back(std::make_shared<AudioAsset>());
        }
        ImGui::PopID();

        for (int i = 0; i < audios.size(); i++)
        {
            ImGui::PushID(UniqueId(i + __LINE__));
            if (ImGui::Button("Delete"))
            {
                audios[i]->isActive = false;
            }
            ImGui::PopID();

            auto& fileDialogType = m_app->GetFileDialogType();
            ImGui::PushID(UniqueId(i));
            if (ImGui::Button("Select audio"))
            {
                fileDialogType = FileDialogType::Audio;

                fileDialog.SetTypeFilters({ ".mp3", ".mkv" });
                fileDialog.SetFlagOptions(0 | ImGuiFileBrowserFlags_CloseOnEsc);
                fileDialog.Open();
            }
            ImGui::PopID();

            if (fileDialogType == FileDialogType::Audio && fileDialog.HasSelected())
            {
                audios[i]->filePath = fileDialog.GetSelected().string();
                audios[i]->fileName = fileDialog.GetSelected().filename().string();

                fileDialog.ClearSelected();
            }

            ImGui::SameLine();
            if (audios[i]->filePath.empty())
            {
                ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "X");
            }
            else
            {
                ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "O");
            }

            ImGui::PushID(UniqueId(i));
            ImGui::Text(audios[i]->fileName.c_str());
            ImGui::PopID();

            ImGui::Separator();
        }
    }
}

void RightArea::DrawFontsStuff()
{
    if (!ImGui::CollapsingHeader("Fonts"))
    {
        auto& fonts = m_app->GetFonts();
        auto& fileDialog = m_app->GetFileDialog();

        ImGui::PushID(UniqueId(__LINE__));
        if (ImGui::Button("+"))
        {
            fonts.emplace_back(std::make_shared<FontAsset>());
        }
        ImGui::PopID();

        for (int i = 0; i < fonts.size(); i++)
        {
            ImGui::PushID(UniqueId(i + __LINE__));
            if (ImGui::Button("Delete"))
            {
                fonts[i]->isActive = false;
            }
            ImGui::PopID();

            auto& fileDialogType = m_app->GetFileDialogType();
            ImGui::PushID(UniqueId(i));
            if (ImGui::Button("Select font"))
            {
                fileDialogType = FileDialogType::Font;

                fileDialog.SetTypeFilters({ ".ttf" });
                fileDialog.SetFlagOptions(0 | ImGuiFileBrowserFlags_CloseOnEsc);
                fileDialog.Open();
            }
            ImGui::PopID();

            if (fileDialogType == FileDialogType::Font && fileDialog.HasSelected())
            {
                fonts[i]->filePath = fileDialog.GetSelected().string();
                fonts[i]->fileName = fileDialog.GetSelected().filename().string();

                fileDialog.ClearSelected();
            }

            ImGui::SameLine();
            if (fonts[i]->filePath.empty())
            {
                ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "X");
            }
            else
            {
                ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "O");
            }

            ImGui::PushID(UniqueId(i));
            ImGui::Text(fonts[i]->fileName.c_str());
            ImGui::PopID();

            ImGui::Separator();
        }
    }
}

void RightArea::DrawSpriteTypeCombobox()
{
    auto& sprite = m_app->GetSelectedSprite();

    static ImGuiComboFlags flags = 0;
    const std::string tagString = SpriteTypeToString(sprite->spriteType);

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
                    sprite->spriteType = StringToSpriteType(m_spriteTypes[itemSelectedIndex].c_str());
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

    ImGui::PushItemWidth(90);
    ImGui::InputInt("Speed", &sprite->speed);
    sprite->speed = sprite->speed < 0 ? 0 : sprite->speed;

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
        ImGui::PushID(UniqueId(i + __LINE__));
        if (ImGui::TreeNode("animations_tree_node", anim->name))
        {
            if (m_app->GetUsedTextures()[m_app->GetSelectedSprite()->filePath])
            {
                DrawFrames(anim);
            }

            ImGui::PushItemWidth(90);
            ImGui::PushID(UniqueId(i));
            if (ImGui::Button("Edit name"))
            {
                ImGui::OpenPopup("edit_name_popup");
            }

            if (ImGui::BeginPopup("edit_name_popup"))
            {
                ImGui::PushID(UniqueId(i));
                ImGui::InputText("Name", anim->name, IM_ARRAYSIZE(anim->name));
                ImGui::PopID();

                ImGui::EndPopup();
            }
            ImGui::PopID();

            if (sprite->animations.size() > 1)
            {
                ImGui::SameLine();
                ImGui::PushItemWidth(90);
                ImGui::PushID(UniqueId(i + __LINE__));
                if (ImGui::Button("Delete"))
                {
                    anim->isActive = false;
                }
                ImGui::PopID();
            }

            ImGui::Text("Animation frame");
            ImGui::SameLine();
            if (ImGui::Button("+"))
            {
                anim->AddFrame(sf::Vector2f(32, 32));
            }

            for (int j = 0; j < anim->frames.size(); j++)
            {
                float newSize[] = {anim->frames[j]->size.x, anim->frames[j]->size.y};
                ImGui::PushID(UniqueId(j));
                ImGui::InputFloat2("Size", newSize);
                anim->SetSize(anim->frames[j], sf::Vector2f(newSize[0], newSize[1]));
                ImGui::PopID();

                if (anim->frames.size() > 1)
                {
                    ImGui::PushItemWidth(90);
                    ImGui::SameLine(230);
                    ImGui::PushID(UniqueId(j));
                    if (ImGui::Button("Delete"))
                    {
                        anim->frames[j]->isActive = false;
                    }
                    ImGui::PopID();
                }

                int newPos[] = {anim->frames[j]->position.x, anim->frames[j]->position.y};
                ImGui::PushID(UniqueId(j));
                ImGui::InputInt2("Position", newPos);
                anim->frames[j]->position.x = newPos[0];
                anim->frames[j]->position.y = newPos[1];
                ImGui::PopID();

                ImGui::Separator();
            }

            ImGui::TreePop();
        }
        ImGui::PopID();

        i++;
    }
}

void RightArea::DrawFrames(const std::shared_ptr<Animation>& anim)
{
    for (int i = 0; i < anim->frames.size(); i++)
    {
        sf::RectangleShape rect;
        rect.setSize(sf::Vector2f(anim->frames[i]->size.x, anim->frames[i]->size.y));
        rect.setOrigin(sf::Vector2f(anim->frames[i]->halfSize.x, anim->frames[i]->halfSize.y));
        rect.setPosition(sf::Vector2(anim->frames[i]->position.x + anim->frames[i]->halfSize.x, anim->frames[i]->position.y + anim->frames[i]->halfSize.y));
        rect.setFillColor(sf::Color(0, 0, 0, 0));
        rect.setOutlineColor(sf::Color(255, 0, 0, 255));
        rect.setOutlineThickness(1);
        m_app->GetRenderTexture().draw(rect);
    }
}

void RightArea::DrawAutoCutStuff()
{
    if (ImGui::Begin("Auto cut stuff", &m_app->AutoCutOpen()))
    {
        static float size[] {0.0f, 0.0f};
        ImGui::InputFloat2("Cut size", size);

        static ImGuiComboFlags flags = 0;
        static int itemSelectedIndex = 0;
        static SpriteType sType;

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
                        sType = StringToSpriteType(m_spriteTypes[itemSelectedIndex].c_str());
                        break;
                    }
                }
            }
            ImGui::EndCombo();
        }

        if (ImGui::Button("Cut everything"))
        {
            auto& t = m_app->GetUsedTextures()[m_app->GetFilePath()];
            float textureSize[] = {static_cast<float>(t->getSize().x), static_cast<float>(t->getSize().y)};

            int rowsAmount = static_cast<int>(textureSize[1] / size[1]);
            int columnsAmount = static_cast<int>(textureSize[0] / size[0]);

            for (int i = 0; i < rowsAmount; i++)
            {
                for (int j = 0; j < columnsAmount; j++)
                {
                    if (m_app->GetFileNames()[m_app->GetFilePath()].empty())
                    {
                        m_app->GetFileNames()[m_app->GetFilePath()] = m_app->GetFileName();
                    }

                    auto s = std::make_shared<SpriteAsset>(m_app->GetFilePath());
                    s->fileName = m_app->GetFileName();
                    s->spriteType = sType;
                    s->AddAnimation();
                    s->animations[0]->frames[0]->size = sf::Vector2f(size[0], size[1]);
                    s->animations[0]->frames[0]->halfSize = sf::Vector2f(size[0] / 2, size[1] / 2);
                    s->animations[0]->frames[0]->position = sf::Vector2i(j * static_cast<int>(size[0]),  i * static_cast<int>(size[0]));
                    m_app->GetSprites().emplace_back(s);
                }
            }
        }
    }

    ImGui::End();
}

void RightArea::Serialize(const std::string &path)
{
    ABYSS_INFO("Serializing: %s", path.c_str());

    YAML::Emitter emitter;
    Serializer(m_app).Serialize(emitter);

    std::ofstream filepath(path);
    filepath << emitter.c_str();
}

bool RightArea::Deserialize(const std::string &path)
{
    ABYSS_INFO("Deserializing: %s", path.c_str());
    YAML::Node root;
    try
    {
        root = YAML::LoadFile(path);
    }
    catch (YAML::ParserException& e)
    {
        ABYSS_ERROR("Failed to deserialize scene!");
        return false;
    }

    m_abyssPath += "data.abyss";
    char* dataFileName = new char[m_abyssPath.size() + 1];
    strcpy(dataFileName, m_abyssPath.c_str());
    m_app->GetArchiver().ReadArchiveFile(dataFileName);

    Serializer(m_app).Deserialize(root);

    m_app->GetArchiver().CloseArchive();

    delete[] dataFileName;
    return true;
}

bool RightArea::ArchiveData()
{
    int totalFiles = 0;
    std::vector<std::string> filePaths;
    std::vector<std::string> fileNames;

    for (const auto& item : m_app->GetAudios())
    {
        if (!item->fileName.empty())
        {
            totalFiles++;
            filePaths.push_back(item->filePath);
            fileNames.push_back(item->fileName);
        }
    }

    for (const auto& item : m_app->GetFonts())
    {
        if (!item->fileName.empty())
        {
            totalFiles++;
            filePaths.push_back(item->filePath);
            fileNames.push_back(item->fileName);
        }
    }

    for (const auto& item : m_app->GetFileNames())
    {
        totalFiles++;
        filePaths.push_back(item.first);
        fileNames.push_back(item.second);
    }

    m_abyssPath += "data.abyss";
    char* dataFileName = new char[m_abyssPath.size() + 1];
    strcpy(dataFileName, m_abyssPath.c_str());
    char tmpFolder[] = "tmpData";

    if (m_app->GetArchiver().ReadArchiveFile(dataFileName))
    {
        for (int i = 0; i < fileNames.size(); i++)
        {
            char n[fileNames[i].size() + 1];
            strcpy(n, fileNames[i].c_str());
            if (m_app->GetArchiver().GetFileIndex(n) < 0)
            {
                continue;
            }

            m_app->GetArchiver().Extract(n, tmpFolder);

            // auto& toRemove = filePaths[i];
            // filePaths.erase(std::find(filePaths.begin(), filePaths.end(), toRemove));

            std::string filePath = tmpFolder;
            filePath += "/" + fileNames[i];
            filePaths[i]= filePath;
        }
    }

    const auto& headers = new archiver::ArchiveFileHeader[totalFiles];
    for (int i = 0; i < totalFiles; i++)
    {
        char n[fileNames[i].size() + 1];
        strcpy(n, fileNames[i].c_str());
        headers[i].SetFileName(n);
    }

    if (m_app->GetArchiver().WriteArchiveFile(dataFileName, headers, filePaths, totalFiles))
    {
        ABYSS_INFO("Archive %s created!", dataFileName);
    }
    else
    {
        ABYSS_ERROR("Error creating archive %s!", dataFileName);
        return false;
    }

    delete[] headers;
    delete[] dataFileName;

    m_app->GetArchiver().CloseArchive();

    m_app->GetArchiver().DeleteFolder(tmpFolder);

    return true;
}