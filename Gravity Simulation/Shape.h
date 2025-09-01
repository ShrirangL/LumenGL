#pragma once

#include <vector>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Program.h"
#include "Renderer.h"
#include "Point.h"
#include "Globals.h"
#include "Texture.h"

constexpr float PI = 3.14159265358979323846;

enum ShapeProgram
{
	SHAPE_FILL = 0, SHAPE_EDGE
};

class Shape
{
protected:
	Point mCentre;
	std::vector<float>mVertices;
	std::vector<unsigned int>mIndices;
	VertexArray mVA;
	VertexBuffer mVB;
	VertexBufferLayout mVBL;
	IndexBuffer mIB;
	Program fillProgram;
	Program edgeProgram;
	glm::mat4 mModel;
	glm::vec3 mColor;
	Texture* mTexture = nullptr;
	bool mHasTexture = false;

	void setVBDataSizeAndCount();
	void setVBLLayout3Floats();
	void setVBLLayout3Pos3Norm();
	void setVBLayout3Pos3Norm2Tex();
	virtual void setLayout();
	void setVABufferAndLayout();
	void setIBDataAndSize();

	void build();

public:

	Shape();
	Shape(float x, float y, float z);
	Shape(const Point& centre);
	Shape(const Point& centre, const glm::vec3& color);
	Shape(float x, float y, float z, glm::mat4 mat);
	Shape(float x, float y, float z, glm::mat4 mat, const glm::vec3& color);
	~Shape();

	virtual void generateVerticesAndIndices() = 0;

	void setPrograms(const Program* const fill, const Program* const edge);
	void setFillProgram(const Program* const fill);
	void setEdgeProgram(const Program* const edge);
	void setPrograms(const char* fillVertexSrc, const char* fillFragmentSrc, const char* edgeVertexSrc, const char* edgeFragmentSrc);
	void setFillProgram(const char* fillVertexSrc, const char* fillFragmentSrc);
	void setEdgeProgram(const char* edgeVertexSrc, const char* edgeFragmentSrc);

	void setModelMatrix(const glm::mat4& matrix);
	void setViewMatrix(const glm::mat4& matrix);
	void setProjectionMatrix(const glm::mat4& matrix);

	void setCameraViewPositionVector(const glm::vec3& vec);
	void setLightPositionVector(const glm::vec3& vec);
	void setLightColorVector(const glm::vec3& vec);
	void setObjectColorVector(const glm::vec3& vec);

	void setUniform1i(const char* name, int value);
	void setUniform1f(const char* name, float value);
	void setUniform3f(const char* name, float v0, float v1, float v2);
	void setUniformVector3fv(const char* name, const glm::vec3& vec);
	void setUniformMatrix4fv(const char* name, const glm::mat4& matrix);
	void setUniform1i(ShapeProgram prog, const char* name, int value);
	void setUniform1f(ShapeProgram prog, const char* name, float value);
	void setUniform3f(ShapeProgram prog, const char* name, float v0, float v1, float v2);
	void setUniformVector3fv(ShapeProgram prog, const char* name, const glm::vec3& vec);
	void setUniformMatrix4fv(ShapeProgram prog, const char* name, const glm::mat4& matrix);

	void setStaticUniforms();
	void setDynamicUniforms();
	void setAllUniforms();

	void setColor(float red, float green, float blue);
	void setColor(const Point& color);
	void setColor(const glm::vec3& color);

	void setUseTexture();
	void setTexture(Texture* tex);
	void setTexture(const std::string& path);

	void draw3D();
	void draw2D();

	void rotateAroundAxis(const glm::vec3& axis, float angleDegrees);
	void rotateAroundXaxis(float angleDegrees);
	void rotateAroundYaxis(float angleDegrees);
	void rotateAroundZaxis(float angleDegrees);

	void moveAlongVector(const glm::vec3& dir, float distance);
	void moveAlongX(float distance);
	void moveAlongY(float distance);
	void moveAlongZ(float distance);
	
	void snapShapeCentreToCircularOrbit(const Point& orbitCenter, const glm::vec3& axis, float radius);
	void revolveAroundAxis(const Point& point, const glm::vec3& axis, float angleDegrees);
	void revolveAroundXaxis(const Point& point, float angleDegrees);
	void revolveAroundYaxis(const Point& point, float angleDegrees);
	void revolveAroundZaxis(const Point& point, float angleDegrees);

	void snapShapeCentreToEllipticalOrbit(const Point& ellipseCenter, const glm::vec3& axis, float semiMajorRadius, float semiMinorRadius);
	void revolveEllipticallyAroundAxis(const Point& center, const glm::vec3& axis, float angleDegrees, float semiMajorRadius, float semiMinorRadius);
};