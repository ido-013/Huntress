#include "BtnManager.h"
#include <algorithm>  
#include "AEEngine.h"

void ButtonManager::RegisterButton(ButtonComp* button) {
    buttons.push_back(button);
}

void ButtonManager::RemoveButton(ButtonComp* button) {
    buttons.erase(std::remove(buttons.begin(), buttons.end(), button), buttons.end());
}

void ButtonManager::RemoveAllButtons() {
    buttons.clear();  
}

void ButtonManager::HandleClickEvent(int mouseX, int mouseY) {
    for (auto& button : buttons) {
        if (button->IsClicked(mouseX, mouseY)) {
            button->OnClick();  
        }
    }
}

void ButtonManager::HandleHoverEvent(int mouseX, int mouseY) {
    for (auto& button : buttons) {
        bool currentlyHovered = button->IsHovered(mouseX, mouseY); 

        if (currentlyHovered && !button->isHovered) {
            button->OnHover(); 
            button->isHovered = true;  
        }
        else if (!currentlyHovered && button->isHovered) {
            button->OnHoverOut(); 
            button->isHovered = false;  
        }
    }
}

void ButtonManager::Update() {
    s32 mouseX, mouseY;
    AEInputGetCursorPosition(&mouseX, &mouseY);
    mouseY = -mouseY + 450;  
    mouseX = mouseX - 800;  

    HandleHoverEvent(mouseX, mouseY);  

    if (AEInputCheckTriggered(AEVK_LBUTTON)) {
        HandleClickEvent(mouseX, mouseY);  
    }
}
