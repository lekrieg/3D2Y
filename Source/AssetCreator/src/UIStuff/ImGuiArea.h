//
// Created by lekrieg on 17/07/25.
//

#ifndef IMGUI_AREA_H
#define IMGUI_AREA_H
#include <string>
#include "../imgui/imgui.h"

class Application;

class ImGuiArea
{
protected:

    Application* m_app = nullptr;

    bool m_warningPopupOpen = false;
    std::string popupMessage;

public:

    virtual ~ImGuiArea() = default;

    virtual void Init(Application* app) = 0;
    virtual void Update() = 0;

    void ShowWarningModal (const std::string& message)
    {
        ImVec2 center = ImGui::GetMainViewport()->GetCenter();
        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

        if (ImGui::BeginPopupModal("WarningPopup", NULL, ImGuiWindowFlags_AlwaysAutoResize))
        {
            ImGui::Text(message.c_str());
            ImGui::Separator();

            if (ImGui::Button("OK", ImVec2(120, 0)))
            {
                m_warningPopupOpen = false;
                ImGui::CloseCurrentPopup();
            }
            ImGui::SetItemDefaultFocus();
            ImGui::EndPopup();
        }
    }

    const char* UniqueId(int index = 0)
    {
        std::string tmpS(__FILE__);
        tmpS.append(std::to_string(__LINE__));
        tmpS.append(std::to_string(index));

        char* id = new char[tmpS.size() + 1];
        strcpy(id, tmpS.c_str());
        return id;
    }
};

#endif //IMGUI_AREA_H
