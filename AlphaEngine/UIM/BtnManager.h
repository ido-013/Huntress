#pragma once
#include <vector>
#include "../Components/ButtonComp.h"
#include "AEInput.h"

class ButtonManager {
private:
    std::vector<ButtonComp*> buttons;

    // 싱글톤 패턴: 생성자를 private으로 정의
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
