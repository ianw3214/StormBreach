#pragma once

#include <string>
#include <memory>
#include <unordered_map>

#include "memory/pointers.hpp"

#include "opengl/shader.hpp"
#include "opengl/glwrapper.hpp"

// Typedefs for QoL
typedef Reference<Shader> ShaderRef;
typedef Owned<Shader>& ShaderRefPtr;
typedef Reference<Texture> TextureRef;
typedef Owned<Texture>& TextureRefPtr;

class ResourceManager {
public:
    ResourceManager();
    ~ResourceManager();

    // Don't allow copy/move constructing
    ResourceManager(ResourceManager& other) = delete;
    ResourceManager(ResourceManager&& other) = delete;

    ShaderRef loadShader(std::string name, std::string vertex, std::string fragment);
    ShaderRef getShader(std::string name);

    TextureRef loadTexture(std::string name, std::string path);
    TextureRef getTexture(std::string name);
    
private:
    std::unordered_map<std::string, Owned<Shader>> shaders;
    std::unordered_map<std::string, Owned<Texture>> textures;
};