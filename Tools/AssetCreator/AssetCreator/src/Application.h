//
// Created by lekrieg on 29/06/25.
//

#ifndef APPLICATION_H
#define APPLICATION_H

#include "soloud.h"
#include "soloud_wav.h"

#include "UIStuff/ImGuiArea.h"

#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <memory>

#include "AssetInfo/AudioAsset.h"
#include "AssetInfo/FontAsset.h"
#include "AssetInfo/SpriteAsset.h"
#include "imgui/imfilebrowser.h"

class Application
{
protected:
    sf::RenderWindow m_window;
    std::string m_imagePath;
    sf::Texture m_texture;
    sf::RenderTexture m_renderTexture;
    sf::Vector2f m_oldPos;

    int m_simulationSpeed = 1;
    bool m_running = true;
    bool m_dockSpaceOpen = true;
    bool m_leftButton = false;
    int m_scale = 1;

    std::vector<std::shared_ptr<abyss::asset_info::AudioAsset>> m_audios;
    std::vector<std::shared_ptr<abyss::asset_info::FontAsset>> m_fonts;
    std::vector<std::shared_ptr<abyss::asset_info::SpriteAsset>> m_sprites;
    std::map<std::string, std::shared_ptr<sf::Texture>> m_usedTextures;
    std::shared_ptr<abyss::asset_info::SpriteAsset> m_selectedSprite;

    ImGui::FileBrowser m_fileDialog;

    std::vector<std::shared_ptr<ImGuiArea>> m_imguiAreas;

    sf::Clock clock;

public:

    Application()
    {
        Init();
    }

    ~Application();
    void Run();
    void Quit();
    bool IsRunning();
    sf::RenderWindow &GetWindow();
    ImGui::FileBrowser& GetFileDialog();
    void SetImagePath(const std::string& path);
    std::string GetFilePath();
    sf::Texture& GetTexture();
    sf::RenderTexture& GetRenderTexture();
    void SetScale(int scale);
    int GetScale();
    std::vector<std::shared_ptr<abyss::asset_info::AudioAsset>>& GetAudios();
    std::vector<std::shared_ptr<abyss::asset_info::FontAsset>>& GetFonts();
    std::vector<std::shared_ptr<abyss::asset_info::SpriteAsset>>& GetSprites();
    std::map<std::string, std::shared_ptr<sf::Texture>>& GetUsedTextures();
    std::shared_ptr<abyss::asset_info::SpriteAsset>& GetSelectedSprite();
    void SetSelectedSprite(const std::shared_ptr<abyss::asset_info::SpriteAsset>& sprite);


protected:
    void Init();
    void Update();
    void UserInputSystem();
    void ShowDockSpace();
    void SetStyle();
};



#endif //APPLICATION_H
