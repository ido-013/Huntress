#pragma once
#include <vector>
#include "../Components/ButtonComp.h"  
#include "AEInput.h"
#include "AEEngine.h"

class ButtonManager {
private:
    std::vector<ButtonComp*> buttons;

    ButtonManager() {}
public:
    static ButtonManager& GetInstance() {
        static ButtonManager instance;
        return instance;
    }

    // ��ư ���
    void RegisterButton(ButtonComp* button) {
        buttons.push_back(button);
    }

    // ��ư ����
    void RemoveButton(ButtonComp* button) {
        for (auto it = buttons.begin(); it != buttons.end(); it++)
        {
            if (*it == button)
            {
                buttons.erase(it);
                break;
            }
        }
    }

    void RemoveAllButton()
    {

        buttons.clear();
    }
    // ���콺 Ŭ�� �̺�Ʈ ó��
    void HandleClickEvent(int mouseX, int mouseY) {
        for (auto& button : buttons) {
            if (button->IsClicked(mouseX, mouseY)) {
                button->OnClick(); 
            }
        }
    }

    // ������Ʈ: �� �����Ӹ��� ���콺 Ŭ�� �̺�Ʈ ó��
    void Update();
};

inline void ButtonManager::Update() {
    s32 mouseX, mouseY;
    AEInputGetCursorPosition(&mouseX, &mouseY);
    mouseY = -mouseY + 450;  // �ʿ��� ��ǥ ��ȯ
    mouseX = mouseX - 800;   // �ʿ��� ��ǥ ��ȯ

    if (AEInputCheckTriggered(AEVK_LBUTTON)) {
        HandleClickEvent(mouseX, mouseY);
    }
}
