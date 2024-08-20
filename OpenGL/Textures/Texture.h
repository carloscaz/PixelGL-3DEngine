#pragma once

class Texture
{
private:
    Texture();
    unsigned int m_tex = 0;
    int m_height = 0, m_width = 0;
public:
    static Texture* Load(const char* _filename);
    unsigned int GetId();
};
