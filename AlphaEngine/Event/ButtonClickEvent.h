#pragma once
#include "Event.h"
#include <iostream>

class ButtonClickEvent : public Event {
public:

    ButtonClickEvent(Entity* src, Entity* dst) : Event(src, dst) {}

    void DispatchEvent()  {
        // 버튼 클릭 시 처리할 로직을 여기에 작성
        std::cout << "Dispatching ButtonClickEvent for button!" << std::endl;
        if (dst) {
            dst->OnEvent(this);
        }
    }
};
