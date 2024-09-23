#pragma once
#include <string>
#include <vector>

class Texture
{
private:
    Texture(); //Private constructor. Texture creation method in static function
    unsigned int m_tex = 0;
    int m_height = 0, m_width = 0;
    const char* m_name;
public:
    ~Texture();
    static Texture* Load(const char* _filename); //Load function to create textures
    static Texture* LoadCubeMap(const std::vector<std::string>& filenames); //Load function to create cubeMaps
    unsigned int GetId();
    const char* GetName();
};
