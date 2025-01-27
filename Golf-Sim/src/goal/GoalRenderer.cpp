#include "GoalRenderer.h"

#include "util/opengl/PerspectiveCamera.h"
#include "lights/Lights.h"

#include <glad/glad.h>

GoalRenderer::GoalRenderer()
    : shader("assets/shaders/GoalVertexShader.vert",
             "assets/shaders/GoalFragmentShader.frag") {}

void GoalRenderer::render(opengl::PerspectiveCamera& camera,
                          lights::LightScene& lightScene,
                          opengl::Shader* shader) {
  if (shader == nullptr) {
    shader = &this->shader;
  }

  shader->activate();
  shader->setVec3f("material.ambient", 0.0f, 0.0f, 0.0f);
  shader->setVec3f("material.specular", 0.025f, 0.025f, 0.025f);
  shader->setFloat("material.shininess", 2);
  shader->setVec3f("viewPos", camera.getPos());
  shader->setMat4f("view", false, camera.getViewMatrix());
  shader->setMat4f("projection", false, camera.getProjectionMatrix());

  lights::setLightScene(shader, lightScene);

  while (queue.size()) {
    GoalRenderJob job = queue.front();
    queue.pop();

    job.model.getVertexArray()->bind();

    shader->setVec3f("material.diffuse", job.color);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, job.model.getPosition());
    shader->setMat4f("model", false, glm::value_ptr(model));
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawArrays(GL_TRIANGLES, 0, job.model.getNumVertices());
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
}

void GoalRenderer::renderLightDepth(opengl::Shader& lightDepthShader,
                                    lights::LightScene& lightScene,
                                    int dirLightIndex) {
  lightDepthShader.activate();
  lightDepthShader.setMat4f(
      "lightSpaceMatrix", false,
      glm::value_ptr(lightScene.dirLights[dirLightIndex].lightSpaceMatrix));

  while (queue.size()) {
    GoalRenderJob job = queue.front();
    queue.pop();

    job.model.getVertexArray()->bind();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, job.model.getPosition());
    lightDepthShader.setMat4f("model", false, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 0, job.model.getNumVertices());
  }
}

void GoalRenderer::add(GoalRenderJob job) { queue.push(job); }

void GoalRenderer::freeRenderer() { shader.free(); }
