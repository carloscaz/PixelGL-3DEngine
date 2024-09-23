#pragma once

class GUIWindow
{
public:
    GUIWindow() {};
    virtual ~GUIWindow(){};
    virtual void DrawWindow() = 0;
};
