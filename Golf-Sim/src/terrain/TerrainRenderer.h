#pragma once

#include "terrain/TerrainModel.h"

#include <util/opengl/Shader.h>

#include <queue>

namespace opengl {
class PerspectiveCamera;
}

namespace lights {
class LightScene;
}

struct TerrainRenderJob {
  TerrainModel& model;
  glm::vec3 position;
  glm::vec3 color;
  glm::vec2 startPos;
  float highlightRadius;
  glm::vec3 highlightColor;
};

class TerrainRenderer {
 public:
  TerrainRenderer();

  void render(opengl::PerspectiveCamera& camera, lights::LightScene& lightScene,
              opengl::Shader* shader = nullptr);
  void renderLightDepth(opengl::Shader& lightDepthShader,
                        lights::LightScene& lightScene, int dirLightIndex);
  void add(TerrainRenderJob job);
  void freeRenderer();
  void reloadShader() { shader.load(); }

 private:
  opengl::Shader shader;
  std::queue<TerrainRenderJob> queue;
};
