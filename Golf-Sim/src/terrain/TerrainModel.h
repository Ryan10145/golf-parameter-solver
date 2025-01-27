#pragma once

#include "util/opengl/VertexArray.h"
#include "util/opengl/VertexBuffer.h"

#include <glm/glm.hpp>

#include <memory>
#include <vector>

class TerrainModel {
 public:
  TerrainModel();
  void generateModel(std::vector<float>* heightMap, int numCols, int numRows,
                     float mapWidth, float mapHeight, glm::vec2 goalPos,
                     float goalRadius);
  void freeModel();

  std::unique_ptr<opengl::VertexArray>& getVertexArray() { return vertexArray; }

  int getNumVertices() { return numVertices; }

 private:
  int numCols;
  int numRows;
  float mapWidth;
  float mapHeight;
  std::vector<float>* heightMap;
  std::vector<float> vertices;
  int numVertices;

  std::unique_ptr<opengl::VertexArray> vertexArray;
  std::unique_ptr<opengl::VertexBuffer> vertexBuffer;

  std::pair<float, float> getXZ(int index);
  void addVertex(int index, std::vector<float>& norm);
  std::vector<float> getNormal(int i1, int i2, int i3);
};
