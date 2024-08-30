#pragma once
#include <vector>
#include "../Event/Button.h"
#include "AEInput.h"

class ButtonManager {
private:
    std::vector<Button*> buttons;
    ButtonManager() {}
public:
    static ButtonManager& GetInstance() {
        static ButtonManager instance;
        return instance;
    }

    void RegisterButton(Button* button) {
        buttons.push_back(button);
    }

    void HandleClickEvent(int mouseX, int mouseY) {
        for (auto& button : buttons) {
            if (button->IsClicked(mouseX, mouseY)) {
                button->OnClick();  
            }
        }
    }

    void Update() {
        s32 mouseX, mouseY;
        AEInputGetCursorPosition(&mouseX, &mouseY);
        mouseY = -mouseY + 450; 
        mouseX = mouseX - 800; 

        if (AEInputCheckTriggered(AEVK_LBUTTON)) {
            HandleClickEvent(mouseX, mouseY);
        }
    }
};
