#pragma once
#include "Event.h"
#include <iostream>

class ButtonClickEvent : public Event {
public:
    // �� ���� �μ��� �޴� ������ �߰�
    ButtonClickEvent(Entity* src, Entity* dst) : Event(src, dst) {}

    void DispatchEvent();
};
