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

    // 버튼 등록
    void RegisterButton(ButtonComp* button) {
        buttons.push_back(button);
    }

    // 버튼 제거
    void RemoveButton(ButtonComp* button) {
       // buttons.erase(std::remove(buttons.begin(), buttons.end(), button), buttons.end());
    }

    // 마우스 클릭 이벤트 처리
    void HandleClickEvent(int mouseX, int mouseY) {
        for (auto& button : buttons) {
            if (button->IsClicked(mouseX, mouseY)) {
                button->OnClick(); 
            }
        }
    }

    // 업데이트: 매 프레임마다 마우스 클릭 이벤트 처리
    void Update() {
        s32 mouseX, mouseY;
        AEInputGetCursorPosition(&mouseX, &mouseY);
        mouseY = -mouseY + 450;  // 필요한 좌표 변환
        mouseX = mouseX - 800;   // 필요한 좌표 변환

        if (AEInputCheckTriggered(AEVK_LBUTTON)) {
            HandleClickEvent(mouseX, mouseY);
        }
    }
};
