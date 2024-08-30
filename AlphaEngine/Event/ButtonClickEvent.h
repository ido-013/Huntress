#pragma once
#include "Event.h"
#include <iostream>

class ButtonClickEvent : public Event {
public:

    ButtonClickEvent(Entity* src, Entity* dst) : Event(src, dst) {}

    void DispatchEvent()  {
        // ��ư Ŭ�� �� ó���� ������ ���⿡ �ۼ�
        std::cout << "Dispatching ButtonClickEvent for button!" << std::endl;
        if (dst) {
            dst->OnEvent(this);
        }
    }
};
