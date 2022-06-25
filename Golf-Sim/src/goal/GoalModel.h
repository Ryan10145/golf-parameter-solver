#pragma once

#include "util/opengl/VertexArray.h"
#include "util/opengl/VertexBuffer.h"
#include "util/opengl/IndexBuffer.h"

#include <glm/glm.hpp>

#include <memory>
#include <vector>

class Terrain;

class GoalModel {
 public:
  const float PI = 3.14159265f;

  const int SECTOR_COUNT = 24; // divisible by 4 to ensure cardinal points are included
  const float SECTOR_STEP = 2 * PI / SECTOR_COUNT;
  const float GOAL_HEIGHT = 3.0;

  GoalModel();
  void generateModel(Terrain& terrain, glm::vec2 relativeCoords, float radius);
  void freeModel();

  std::unique_ptr<opengl::VertexArray>& getVertexArray() { return vertexArray; }
  glm::vec3 getPosition() { return pos; }
  std::vector<float>& getVertices() { return vertices; };
  std::vector<unsigned int>& getIndices() { return indices; };

  int getNumVertices() { return numVertices; }
  float getBottomHeight() { return bottomHeight; }

 private:
  glm::vec3 pos;
  std::vector<float> fullVertexData;
  std::vector<float> vertices;
  std::vector<unsigned int> indices;
  int numVertices;
  float bottomHeight;

  std::unique_ptr<opengl::VertexArray> vertexArray;
  std::unique_ptr<opengl::VertexBuffer> vertexBuffer;
  std::unique_ptr<opengl::IndexBuffer> indexBuffer;

  void addVertex(glm::vec3 a, glm::vec3 norm);
  glm::vec3 getNormal(glm::vec3 a, glm::vec3 b, glm::vec3 c);
  void addTriangle(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 norm);
};

struct GoalModelPoint {
  glm::vec2 pos;
  int row;
  int col;
  float height;
  std::vector<glm::vec3> cellPoints;
};
