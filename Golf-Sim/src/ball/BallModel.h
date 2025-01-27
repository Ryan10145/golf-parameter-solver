#pragma once

#include "util/opengl/IndexBuffer.h"
#include "util/opengl/VertexArray.h"
#include "util/opengl/VertexBuffer.h"

#include <memory>
#include <vector>

class BallModel {
 public:
  const float PI = 3.14159265f;

  const int SECTOR_COUNT = 18;
  const int STACK_COUNT = 9;

  const float SECTOR_STEP = 2 * PI / SECTOR_COUNT;
  const float STACK_STEP = PI / STACK_COUNT;

  BallModel();
  void freeModel();

  std::unique_ptr<opengl::VertexArray>& getVertexArray() { return vertexArray; }
  int getIndexDataSize() { return indexData.size(); }

 private:
  std::vector<float> vertexData;
  std::vector<unsigned int> indexData;

  std::unique_ptr<opengl::VertexArray> vertexArray;
  std::unique_ptr<opengl::VertexBuffer> vertexBuffer;
  std::unique_ptr<opengl::IndexBuffer> indexBuffer;

  static bool instantiated;
};
