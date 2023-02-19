#pragma once

#include <glad/glad.h>

#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

#include "OpenGLFramebuffer.h"

#define ASSERT(x) if(!(x)) __debugbreak();
//call GlClearError than call a given function
//than check error
//# - turns to string
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class GameObject;

namespace Vipera
{
    class Scene;
}

class Renderer {
public:
    Renderer();

    void Clear() const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void Draw(Vipera::Scene& scene, Shader& shader);
    void Draw(const IndexBuffer& ib) const;

    void DrawSkybox(GameObject& model, Shader& shader) const;

    Vipera::OpenGLFramebuffer* GetFrameBuffer() { return frameBuffer; }

private:
    Vipera::OpenGLFramebuffer* frameBuffer;
};