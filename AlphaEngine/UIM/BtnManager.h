#pragma once
#include <vector>
#include "../Components/ButtonComp.h"
#include "AEInput.h"

class ButtonManager {
private:
    std::vector<ButtonComp*> buttons;

    // �̱��� ����: �����ڸ� private���� ����
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
    void Update();
};
