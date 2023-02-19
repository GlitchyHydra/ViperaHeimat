#include "Renderer.h"
#include <iostream>


#include "Scene/Scene.h"

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error] (" << error << "): " << function <<
            " " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}

Renderer::Renderer()
{
    frameBuffer = new Vipera::OpenGLFramebuffer();
}

void Renderer::Clear() const
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib,
    const Shader& shader) const
{
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::DrawSkybox(GameObject& model, Shader& shader) const
{
    shader.Bind();

    const Mesh* mesh = (&model.GetMeshes()[0]);

    mesh->va.Bind();
    Draw(mesh->ib);
    mesh->va.Unbind();

    shader.Unbind();
}

void Renderer::Draw(const IndexBuffer& ib) const
{
    
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, 0));
    
}


