#pragma once
#include <string>
#include <vector>

class Texture
{
private:
    Texture();
    unsigned int m_tex = 0;
    int m_height = 0, m_width = 0;

    const char* m_name;
public:
    static Texture* Load(const char* _filename);
    static Texture* LoadCubeMap(const std::vector<std::string>& filenames);
    unsigned int GetId();
    const char* GetName();
};
