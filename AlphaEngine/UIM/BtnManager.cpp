#include "BtnManager.h"
#include <algorithm>  // std::remove_if
#include "AEEngine.h"
void ButtonManager::RegisterButton(ButtonComp* button) {
    buttons.push_back(button);
}

void ButtonManager::RemoveButton(ButtonComp* button) {
    buttons.erase(std::remove(buttons.begin(), buttons.end(), button), buttons.end());
}

void ButtonManager::RemoveAllButtons() {
    buttons.clear();  // ��� ��ư�� ����
}

void ButtonManager::HandleClickEvent(int mouseX, int mouseY) {
    for (auto& button : buttons) {
        if (button->IsClicked(mouseX, mouseY)) {
            button->OnClick();  // Ŭ�� �� ��ư�� OnClick ȣ��
        }
    }
}
void ButtonManager::HandleHoverEvent(int mouseX, int mouseY) {
    for (auto& button : buttons) {
        if (button->IsHovered(mouseX, mouseY)) {
            button->OnHover();  // Ŀ���� ��ĥ �� OnHover ȣ��
        }
    }
}
void ButtonManager::Update() {
    s32 mouseX, mouseY;
    AEInputGetCursorPosition(&mouseX, &mouseY);
    mouseY = -mouseY + 450;  // �ʿ��� ��ǥ ��ȯ
    mouseX = mouseX - 800;   // �ʿ��� ��ǥ ��ȯ
    HandleHoverEvent(mouseX, mouseY);
    if (AEInputCheckTriggered(AEVK_LBUTTON)) {
        HandleClickEvent(mouseX, mouseY);
    }
}
