#pragma once
#include <vector>
#include "../Components/ButtonComp.h"
#include "AEInput.h"

class ButtonManager {
private:
    std::vector<ButtonComp*> buttons;
    ButtonManager() {}
   
public:
    static ButtonManager& GetInstance() {
        static ButtonManager instance;
        return instance;
    }

    void RegisterButton(ButtonComp* button);
    void RemoveButton(ButtonComp* button);
    void RemoveAllButtons();

    void HandleClickEvent(int mouseX, int mouseY);
    void HandleHoverEvent(int mouseX, int mouseY);
    void Update();
};
