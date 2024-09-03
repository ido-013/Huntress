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

    // 버튼 등록
    void RegisterButton(ButtonComp* button);

    // 버튼 제거
    void RemoveButton(ButtonComp* button);

    void RemoveAllButton();
 
    // 마우스 클릭 이벤트 처리
    void HandleClickEvent(int mouseX, int mouseY);

    // 업데이트: 매 프레임마다 마우스 클릭 이벤트 처리
    void Update();
};


