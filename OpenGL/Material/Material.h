#pragma once
#include <string>
#include <vector>

#include "../../Math/Vector3/Vector3.h"
#include "../Textures/Texture.h"

class Shader;

class Material
{
private:
    Texture* m_texture;
    std::vector<Texture*> m_textures;
    Shader* m_shader;
    std::string m_name;

    Vector3 m_color;
    Vector3 m_diffuse;
    Vector3 m_specular;
    float m_shininess;
    
public:
    Material(Texture* _texture, Shader* _shader);
    Material(Texture* _texture, Shader* _shader, std::string& _name);
    Material(Texture* _texture, Shader* _shader, std::string& _name, const Vector3& _color = Vector3(1.0f, 1.0f, 1.0f),
const Vector3& _diffuse = Vector3(1.0f, 1.0f, 1.0f), const Vector3& _specular = Vector3(0.5f, 0.5f, 0.5f), float _shininess = 32.0f);
    void Prepare();

    Shader* GetShader() const;
    
    std::string& GetName();

    void ShowGUIDetails();
    void AddTexture(Texture* _texture);
};
