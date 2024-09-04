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
    buttons.clear();  // 모든 버튼을 제거
}

void ButtonManager::HandleClickEvent(int mouseX, int mouseY) {
    for (auto& button : buttons) {
        if (button->IsClicked(mouseX, mouseY)) {
            button->OnClick();  // 클릭 시 버튼의 OnClick 호출
        }
    }
}
void ButtonManager::HandleHoverEvent(int mouseX, int mouseY) {
    for (auto& button : buttons) {
        if (button->IsHovered(mouseX, mouseY)) {
            button->OnHover();  // 커서가 겹칠 때 OnHover 호출
        }
    }
}
void ButtonManager::Update() {
    s32 mouseX, mouseY;
    AEInputGetCursorPosition(&mouseX, &mouseY);
    mouseY = -mouseY + 450;  // 필요한 좌표 변환
    mouseX = mouseX - 800;   // 필요한 좌표 변환
    HandleHoverEvent(mouseX, mouseY);
    if (AEInputCheckTriggered(AEVK_LBUTTON)) {
        HandleClickEvent(mouseX, mouseY);
    }
}
