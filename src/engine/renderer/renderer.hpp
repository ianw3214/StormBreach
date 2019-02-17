#pragma once

#include "memory/pointers.hpp"
#include "util/vec.hpp"
#include "util/rect.hpp"

#include "opengl/glwrapper.hpp"
#include "opengl/shader.hpp"

class Engine;
class Renderer {

public:

    Renderer(Engine * engine);
    ~Renderer();

    void setClearColour(float r=0.f, float g=0.f, float b=0.f, float a=0.f) const;
    void clear() const;
    void setScreenSize(int width, int height);

    void drawLine(Vec2i v1, Vec2i v2, Colour colour = {1.f, 0.f, 0.f}, const std::string& shader = "");
	void drawRect(Rect rect, Colour colour = { 1.f, 0.f, 0.f }, const std::string& shader = "");
	void drawRect(Vec2i v, int width, int height, Colour colour = { 1.f, 0.f, 0.f }, const std::string& shader = "");
	void drawRectOutline(Rect rect, Colour colour = { 1.f, 0.f, 0.f }, const std::string& shader = "");
	void drawRectOutline(Vec2i v, int width, int height, Colour colour = { 1.f, 0.f, 0.f }, const std::string& shader = "");
	void drawTexture(Vec2i v1, int width, int height, const Texture& texture, const std::string& shader = "");
	void drawTexture(Vec2i v1, int width, int height, const std::string& name, const std::string& shader = "");
	void drawTexture(Vec2i v, int width, int height, Vec2i src, int src_w, int src_h ,const Texture& texture, const std::string& shader = "");
	void drawTexture(Vec2i v, int width, int height, Vec2i src, int src_w, int src_h ,const std::string& name, const std::string& shader = "");

private:
    void drawTriangles(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
	void drawLines(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
	void drawLineStrip(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
	void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, GLenum type);

private:
    Reference<Engine> engine;
};