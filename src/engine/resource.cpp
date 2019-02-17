#include "resource.hpp"

ResourceManager::ResourceManager() {
    // Init shit here...
}

ResourceManager::~ResourceManager() {
    // Shutdown shit here...
}

ShaderRef ResourceManager::loadShader(std::string name, std::string vertex, std::string fragment) {
    shaders.insert({name, Owned<Shader>(new Shader(vertex, fragment))});
	return Reference<Shader>(shaders[name]);
}

ShaderRef ResourceManager::getShader(std::string name) {
	// Make sure the shader exists before returning it
	if (shaders.find(name) == shaders.end()) {
		return Reference<Shader>();
	}
	return Reference<Shader>(shaders[name]);
}

TextureRef ResourceManager::loadTexture(std::string name, std::string path) {
    textures.insert({name, Owned<Texture>(new Texture(path))});
    return Reference<Texture>(textures[name]);
}

TextureRef ResourceManager::getTexture(std::string name) {
    // Make sure the texture exists before returning it
    if (textures.find(name) == textures.end()) {
        return Reference<Texture>();
    }
    return Reference<Texture>(textures[name]);
}