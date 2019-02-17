#include "renderer.hpp"

#include <GL/glew.h>

#include "engine.hpp"
#include "resource.hpp"

#define BASIC_VERT_PATH "res/shaders/screenCoord.vert"
#define BASIC_FRAG_PATH "res/shaders/singleColour.frag"
#define TEXTR_FRAG_PATH "res/shaders/texture.frag"

// Constants for rendering shapes
const unsigned int LINE_INDICES[2] = { 0, 1 };
const unsigned int SQUARE_INDICES[6] = { 0, 1, 3, 0, 2, 3 };
const unsigned int RECT_OUTLINE_INDICES[8] = { 0, 1, 1, 3, 3, 2, 2, 0 };

Renderer::Renderer(Engine * engine) : engine(engine) {
    // Default clear colour to black
    setClearColour();

    // Initialize default shaders
	ShaderRef basicShader = engine->getResources()->loadShader("basic", BASIC_VERT_PATH, BASIC_FRAG_PATH);
	ShaderRef textureShader = engine->getResources()->loadShader("texture", BASIC_VERT_PATH, TEXTR_FRAG_PATH);
	// Set the screen size uniforms of the shaders to a default
	setScreenSize(engine->getConfig().window_width, engine->getConfig().window_height);
}

Renderer::~Renderer() {
    // Do nothing for now...
}


void Renderer::setClearColour(float r, float g, float b, float a) const {
    glClearColor(r, g, b, a);
}

void Renderer::clear() const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::setScreenSize(int width, int height) {
	ShaderRef basicShader = engine->getResources()->getShader("basic");
	basicShader->setUniform1i("u_screen_width", width);
	basicShader->setUniform1i("u_screen_height", height);
	
	ShaderRef textureShader = engine->getResources()->getShader("texture");
	textureShader->setUniform1i("u_screen_width", width);
	textureShader->setUniform1i("u_screen_height", height);
}

void Renderer::drawLine(Vec2i v1, Vec2i v2, Colour colour, ShaderRef shader) {
	int positions[4] = { v1.x, v1.y, v2.x, v2.y };
	VertexArray va;
	VertexBuffer vb(positions, sizeof(int) * 4);
	IndexBuffer ib(LINE_INDICES, 2);
	// Specify the layout of the buffer data
	VertexBufferLayout layout;
	layout.push_int(2);
	va.addBuffer(vb, layout);

	// Set the uniform to draw the right colour
	if (!shader) {
		shader = engine->getResources()->getShader("basic");
		shader->setUniform4f("u_colour", colour.x, colour.y, colour.z, 1.f);
	}
	drawLines(va, ib, *shader);
}

void Renderer::drawRect(Rect rect, Colour colour, ShaderRef shader) {
	drawRect(rect.pos, rect.w, rect.h, colour, shader);
}

void Renderer::drawRect(Vec2i v, int width, int height, Colour colour, ShaderRef shader) {
	int positions[8] = {
		v.x, v.y,
		v.x + width, v.y,
		v.x, v.y + height,
		v.x + width, v.y + height
	};
	VertexArray va;
	VertexBuffer vb(positions, sizeof(int) * 8);
	IndexBuffer ib(SQUARE_INDICES, 6);
	// Specify the layout of the buffer data
	VertexBufferLayout layout;
	layout.push_int(2);
	va.addBuffer(vb, layout);

	// Issue the actual draw call
	if (!shader) {
		shader = engine->getResources()->getShader("basic");
		shader->setUniform4f("u_colour", colour.x, colour.y, colour.z, 1.f);
	}
	drawTriangles(va, ib, *shader);
}

void Renderer::drawRectOutline(Rect rect, Colour colour, ShaderRef shader) {
	drawRectOutline(rect.pos, rect.w, rect.h, colour, shader);
}

void Renderer::drawRectOutline(Vec2i v, int width, int height, Colour colour, ShaderRef shader) {
	int positions[8] = {
		v.x, v.y,
		v.x + width, v.y,
		v.x, v.y + height,
		v.x + width, v.y + height
	};
	VertexArray va;
	VertexBuffer vb(positions, sizeof(int) * 8);
	IndexBuffer ib(RECT_OUTLINE_INDICES, 8);
	// Specify the layout of the buffer data
	VertexBufferLayout layout;
	layout.push_int(2);
	va.addBuffer(vb, layout);

	// Issue the actual draw call
	if (!shader) {
		shader = engine->getResources()->getShader("basic");
		shader->setUniform4f("u_colour", colour.x, colour.y, colour.z, 1.f);
	}
	drawLineStrip(va, ib, *shader);
}

void Renderer::drawTexture(Vec2i v, int width, int height, const Texture & texture, ShaderRef shader) {
	int positions[8] = {
		v.x, v.y,
		v.x + width, v.y,
		v.x, v.y + height,
		v.x + width, v.y + height
	};
	float textures[8] = {
		0.f, 1.f,
		1.f, 1.f,
		0.f, 0.f,
		1.f, 0.f
	};
	VertexArray		va;
	VertexBuffer	vb_pos(positions, sizeof(int) * 8);
	VertexBuffer	vb_tex(textures, sizeof(float) * 8);
	IndexBuffer		ib(SQUARE_INDICES, 6);
	// Specify the layout of the buffer data
	VertexBufferLayout layout_pos;
	layout_pos.push_int(2);
	va.addBuffer(vb_pos, layout_pos, 0);
	VertexBufferLayout layout_tex;
	layout_tex.push_float(2);
	va.addBuffer(vb_tex, layout_tex, 1);

	// Bind the texture and draw
	texture.bind();
	if (!shader) {
		shader = engine->getResources()->getShader("texture");
	}
	drawTriangles(va, ib, *shader);
}

void Renderer::drawTexture(Vec2i v1, int width, int height, const std::string & name, ShaderRef shader) {
	TextureRef texture = engine->getResources()->getTexture(name);
	if (texture) {
		drawTexture(v1, width, height, *texture, shader);
	} else {
		drawRect(v1, width, height, Colour{1.f, 0.f, 1.f});
	}
}

template<typename T>
T lerp(const T& start, const T& end, float percentage) {
	return start + static_cast<T>(static_cast<float>(end - start) * percentage);
}
void Renderer::drawTexture(Vec2i v, int width, int height, Vec2i src, int src_w, int src_h, const Texture& texture, ShaderRef shader) {
	int t_w = texture.getWidth();
	int t_h = texture.getHeight();
	int positions[8] = {
		v.x, v.y,
		v.x + width, v.y,
		v.x, v.y + height,
		v.x + width, v.y + height
	};
	// TODO: (Ian) Move this into shader code
	float textures[8] = {
		lerp(0.f, 1.f, static_cast<float>(src.x) / static_cast<float>(t_w)),
		lerp(0.f, 1.f, static_cast<float>(src.y + src_h) / static_cast<float>(t_h)),
		lerp(0.f, 1.f, static_cast<float>(src.x + src_w) / static_cast<float>(t_w)),
		lerp(0.f, 1.f, static_cast<float>(src.y + src_h) / static_cast<float>(t_h)),
		lerp(0.f, 1.f, static_cast<float>(src.x) / static_cast<float>(t_w)),
		lerp(0.f, 1.f, static_cast<float>(src.y) / static_cast<float>(t_h)),
		lerp(0.f, 1.f, static_cast<float>(src.x + src_w) / static_cast<float>(t_w)),
		lerp(0.f, 1.f, static_cast<float>(src.y) / static_cast<float>(t_h))
	};
	VertexArray		va;
	VertexBuffer	vb_pos(positions, sizeof(int) * 8);
	VertexBuffer	vb_tex(textures, sizeof(float) * 8);
	IndexBuffer		ib(SQUARE_INDICES, 6);
	// Specify the layout of the buffer data
	VertexBufferLayout layout_pos;
	layout_pos.push_int(2);
	va.addBuffer(vb_pos, layout_pos, 0);
	VertexBufferLayout layout_tex;
	layout_tex.push_float(2);
	va.addBuffer(vb_tex, layout_tex, 1);

	// Bind the texture and draw
	texture.bind();
	if (!shader) {
		shader = engine->getResources()->getShader("texture");
	}
	drawTriangles(va, ib, *shader);
}

void Renderer::drawTexture(Vec2i v, int width, int height, Vec2i src, int src_w, int src_h, const std::string& name, ShaderRef shader) {
	TextureRef texture = engine->getResources()->getTexture(name);
	if (texture) {
		drawTexture(v, width, height, src, src_w, src_h, *texture, shader);
	} else {
		drawRect(v, width, height, Colour{1.f, 0.f, 1.f});
	}
}


void Renderer::drawTriangles(const VertexArray & va, const IndexBuffer & ib, const Shader & shader) {
	shader.bind();
	draw(va, ib, shader, GL_TRIANGLES);
}

void Renderer::drawLines(const VertexArray & va, const IndexBuffer & ib, const Shader & shader) {
	shader.bind();
	draw(va, ib, shader, GL_LINES);
}

void Renderer::drawLineStrip(const VertexArray & va, const IndexBuffer & ib, const Shader & shader) {
	shader.bind();
	draw(va, ib, shader, GL_LINE_STRIP);
}

void Renderer::draw(const VertexArray & va, const IndexBuffer & ib, const Shader & shader, GLenum type) {
	shader.bind();
	va.bind();
	ib.bind();

	glDrawElements(type, ib.getCount(), GL_UNSIGNED_INT, nullptr);
}