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
    void RegisterButton(ButtonComp* button);

    // ��ư ����
    void RemoveButton(ButtonComp* button);

    void RemoveAllButton();
 
    // ���콺 Ŭ�� �̺�Ʈ ó��
    void HandleClickEvent(int mouseX, int mouseY);

    // ������Ʈ: �� �����Ӹ��� ���콺 Ŭ�� �̺�Ʈ ó��
    void Update();
};


