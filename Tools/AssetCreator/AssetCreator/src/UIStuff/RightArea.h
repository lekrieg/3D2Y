//
// Created by lekrieg on 18/07/25.
//

#ifndef RIGHT_AREA_H
#define RIGHT_AREA_H

#include <algorithm>
#include <memory>

#include "ImGuiArea.h"
#include "../AssetInfo/Animation.h"

#include <vector>

 class RightArea : public ImGuiArea
{
private:
    std::vector<std::string> m_spriteTypes;
    std::string m_assetFilePath;

public:

    void Init(Application* app) override;
    void Update() override;

private:

    void DrawRightArea();
    void DrawTopMenuBar();
    void DrawSpriteInfo();
    void DrawSpritesStuff();
    void DrawAudiosStuff();
    void DrawFontsStuff();

    void DrawSpriteTypeCombobox();
    void DrawAnimationArea();
    void DrawFrames(const std::shared_ptr<Animation>& anim);

    void Serialize(const std::string &path);
    bool Deserialize(const std::string &path);

    template <typename TVec, typename TType>
    void RemoveDeadItems(TVec vec)
    {
        vec.erase(std::remove_if(vec.begin(), vec.end(), [](TType& e) { return !e->isActive;  }), vec.end());
    }
};



#endif //RIGHT_AREA_H
