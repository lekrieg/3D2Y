//
// Created by lekrieg on 17/07/25.
//

#ifndef LEFT_AREA_H
#define LEFT_AREA_H

#include "ImGuiArea.h"


class LeftArea : public ImGuiArea
{
public:

    void Init(Application* app) override;
    void Update() override;

private:

    void DrawLeftPanel();
};

#endif //LEFT_AREA_H
