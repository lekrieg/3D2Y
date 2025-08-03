//
// Created by lekrieg on 18/07/25.
//

#ifndef RIGHT_AREA_H
#define RIGHT_AREA_H

#include <memory>

#include "ImGuiArea.h"

#include <vector>

namespace abyss::asset_info
{
    class Animation;
}

class RightArea : public ImGuiArea
{
private:

    bool m_openSpriteInfo = false;

    std::vector<std::string> m_spriteTypes;

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
    void DrawFrames(const std::shared_ptr<abyss::asset_info::Animation>& anim);
};



#endif //RIGHT_AREA_H
