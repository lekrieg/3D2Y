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
#include "Utils/FileDialogType.h"
#include "imgui/imfilebrowser.h"
#include "Archiver/FileArchiverHelper.h"

class Application
{
protected:
    sf::RenderWindow m_window;
    std::string m_imagePath;
    std::string m_fileName;
    sf::RenderTexture m_renderTexture;
    sf::Vector2f m_oldPos;
    archiver::Archive m_archiver;

    int m_simulationSpeed = 1;
    bool m_running = true;
    bool m_dockSpaceOpen = true;
    bool m_leftButton = false;
    bool m_openSpriteInfo = false;
    bool m_openAutoCut = false;

    std::vector<std::shared_ptr<AudioAsset>> m_audios;
    std::vector<std::shared_ptr<FontAsset>> m_fonts;
    std::vector<std::shared_ptr<SpriteAsset>> m_sprites;
    std::map<std::string, std::shared_ptr<sf::Texture>> m_usedTextures;
    std::map<std::string, std::string> m_fileNames;
    std::shared_ptr<SpriteAsset> m_selectedSprite;

    ImGui::FileBrowser m_fileDialog;
    FileDialogType m_fileDialogType;

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
    FileDialogType& GetFileDialogType();
    void SetImagePath(const std::string& path);
    std::string& GetFilePath();
    std::string& GetFileName();
    sf::RenderTexture& GetRenderTexture();
    std::vector<std::shared_ptr<AudioAsset>>& GetAudios();
    std::vector<std::shared_ptr<FontAsset>>& GetFonts();
    std::vector<std::shared_ptr<SpriteAsset>>& GetSprites();
    std::map<std::string, std::shared_ptr<sf::Texture>>& GetUsedTextures();
    std::map<std::string, std::string>& GetFileNames();
    std::shared_ptr<SpriteAsset>& GetSelectedSprite();
    void SetSelectedSprite(const std::shared_ptr<SpriteAsset>& sprite);
    bool& SpriteInfoOpen();
    bool& AutoCutOpen();
    archiver::Archive& GetArchiver();


protected:
    void Init();
    void Update();
    void UserInputSystem();
    void ShowDockSpace();
    void SetStyle();
};



#endif //APPLICATION_H
