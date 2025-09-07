#include "IDrawable.h"

void IDrawable::setVBDataSizeAndCount()
{
	mVB.setDataSizeAndCount(mVertices.data(), mVertices.size() * sizeof(float), mVertices.size()/(mVBL.getStrideInBytes()/sizeof(float)));
}

void IDrawable::setVBLLayout3Floats()
{
	mVBL.pushVertexBufferLayoutElement(GL_FLOAT, 3);
}
void IDrawable::setVBLLayout3Pos3Norm()
{
	mVBL.pushVertexBufferLayoutElement(GL_FLOAT, 3);
	mVBL.pushVertexBufferLayoutElement(GL_FLOAT, 3);
}

void IDrawable::setVBLayout3Pos3Norm2Tex()
{
	mVBL.pushVertexBufferLayoutElement(GL_FLOAT, 3);
	mVBL.pushVertexBufferLayoutElement(GL_FLOAT, 3);
	mVBL.pushVertexBufferLayoutElement(GL_FLOAT, 2);
}

void IDrawable::setLayout()
{
	setVBLayout3Pos3Norm2Tex();
}

void IDrawable::setVABufferAndLayout()
{
	mVA.addBufferAndLayout(mVB, mVBL);
}

void IDrawable::setIBDataAndSize()
{
	mIB.setDataAndCount(mIndices.data(), mIndices.size());
}

void IDrawable::build()
{
	generateVerticesAndIndices();
	setLayout();
	setVBDataSizeAndCount();
	setVABufferAndLayout();
	setIBDataAndSize();
}

IDrawable::IDrawable()
	: mCentre(), mModel(1.0f), mColor(0.0627f, 0.4863f, 0.0627f)
{
}

IDrawable::IDrawable(float x, float y, float z)
	: mCentre(x, y, z), mModel(1.0f), mColor(0.0627f, 0.4863f, 0.0627f)
{
}

IDrawable::IDrawable(const Point& centre)
	: mCentre(centre), mModel(1.0f), mColor(0.0627f, 0.4863f, 0.0627f)
{
}

IDrawable::IDrawable(const Point& centre, const glm::vec3& color)
	: mCentre(centre), mModel(1.0f), mColor(color)
{
}

IDrawable::IDrawable(float x, float y, float z, glm::mat4 mat)
	: mCentre(x, y, z), mModel(mat), mColor(0.0627f, 0.4863f, 0.0627f)
{
}

IDrawable::IDrawable(float x, float y, float z, glm::mat4 mat, const glm::vec3& color)
	: mCentre(x, y, z), mModel(mat), mColor(color)
{
}

IDrawable::~IDrawable()
{
	if(mTexture)
		delete mTexture;
}

void IDrawable::setPrograms(const Program* const fill, const Program* const edge)
{
	fillProgram.setVertexAndFragmentSources(fill->getVertexShaderSource().data(), fill->getFragmentShaderSource().data());
	edgeProgram.setVertexAndFragmentSources(edge->getVertexShaderSource().data(), edge->getFragmentShaderSource().data());

	setStaticUniforms();
}

void IDrawable::setFillProgram(const Program* const fill)
{
	fillProgram.setVertexAndFragmentSources(fill->getVertexShaderSource().data(), fill->getFragmentShaderSource().data());

	setStaticUniforms();
}

void IDrawable::setEdgeProgram(const Program* const edge)
{
	edgeProgram.setVertexAndFragmentSources(edge->getVertexShaderSource().data(), edge->getFragmentShaderSource().data());

	setStaticUniforms();
}

void IDrawable::setPrograms(const char* fillVertexSrc, const char* fillFragmentSrc, const char* edgeVertexSrc, const char* edgeFragmentSrc)
{
	fillProgram.setVertexAndFragmentSources(fillVertexSrc, fillFragmentSrc);
	edgeProgram.setVertexAndFragmentSources(edgeVertexSrc, edgeFragmentSrc);

	setStaticUniforms();
}

void IDrawable::setFillProgram(const char* fillVertexSrc, const char* fillFragmentSrc)
{
	fillProgram.setVertexAndFragmentSources(fillVertexSrc, fillFragmentSrc);

	setStaticUniforms();
}

void IDrawable::setEdgeProgram(const char* edgeVertexSrc, const char* edgeFragmentSrc)
{
	edgeProgram.setVertexAndFragmentSources(edgeVertexSrc, edgeFragmentSrc);

	setStaticUniforms();
}

void IDrawable::setModelMatrix(const glm::mat4& matrix)
{
	mModel = matrix;
	fillProgram.setUniformMatrix4floats("model", mModel);
	edgeProgram.setUniformMatrix4floats("model", mModel);
}

void IDrawable::setViewMatrix(const glm::mat4& matrix)
{
	fillProgram.setUniformMatrix4floats("view", matrix);
	edgeProgram.setUniformMatrix4floats("view", matrix);
}

void IDrawable::setProjectionMatrix(const glm::mat4& matrix)
{
	fillProgram.setUniformMatrix4floats("projection", matrix);
	edgeProgram.setUniformMatrix4floats("projection", matrix);
}

void IDrawable::setCameraViewPositionVector(const glm::vec3& vec)
{
	fillProgram.setUniformVector3floats("viewPos", vec);
	edgeProgram.setUniformVector3floats("viewPos", vec);
}

void IDrawable::setLightPositionVector(const glm::vec3& vec)
{
	fillProgram.setUniformVector3floats("lightPos", vec);
	edgeProgram.setUniformVector3floats("lightPos", vec);
}

void IDrawable::setLightColorVector(const glm::vec3& vec)
{
	fillProgram.setUniformVector3floats("lightColor", vec);
	edgeProgram.setUniformVector3floats("lightColor", vec);
}

void IDrawable::setObjectColorVector(const glm::vec3& vec)
{
	fillProgram.setUniformVector3floats("objectColor", vec);
	edgeProgram.setUniformVector3floats("objectColor", vec);
}

void IDrawable::setUniform1i(const char* name, int value)
{
	fillProgram.setUniform1integer(name, value);
	edgeProgram.setUniform1integer(name, value);
}

void IDrawable::setUniform1f(const char* name, float value)
{
	fillProgram.setUniform1float(name, value);
	edgeProgram.setUniform1float(name, value);
}

void IDrawable::setUniform3f(const char* name, float v0, float v1, float v2)
{
	fillProgram.setUniform3floats(name, v0, v1, v2);
	edgeProgram.setUniform3floats(name, v0, v1, v2);
}

void IDrawable::setUniformVector3fv(const char* name, const glm::vec3& vec)
{
	fillProgram.setUniformVector3floats(name, vec);
	edgeProgram.setUniformVector3floats(name, vec);
}

void IDrawable::setUniformMatrix4fv(const char* name, const glm::mat4& matrix)
{
	fillProgram.setUniformMatrix4floats(name, matrix);
	edgeProgram.setUniformMatrix4floats(name, matrix);
}

void IDrawable::setUniform1i(ShapeProgram prog, const char* name, int value)
{
	if (prog == ShapeProgram::SHAPE_FILL)
		fillProgram.setUniform1integer(name, value);
	else
		edgeProgram.setUniform1integer(name, value);
}

void IDrawable::setUniform1f(ShapeProgram prog, const char* name, float value)
{
	if (prog == ShapeProgram::SHAPE_FILL)
		fillProgram.setUniform1float(name, value);
	else
		edgeProgram.setUniform1float(name, value);
}

void IDrawable::setUniform3f(ShapeProgram prog, const char* name, float v0, float v1, float v2)
{
	if (prog == ShapeProgram::SHAPE_FILL)
		fillProgram.setUniform3floats(name, v0, v1, v2);
	else
		edgeProgram.setUniform3floats(name, v0, v1, v2);
}

void IDrawable::setUniformVector3fv(ShapeProgram prog, const char* name, const glm::vec3& vec)
{
	if (prog == ShapeProgram::SHAPE_FILL)
		fillProgram.setUniformVector3floats(name, vec);
	else
		edgeProgram.setUniformVector3floats(name, vec);
}

void IDrawable::setUniformMatrix4fv(ShapeProgram prog, const char* name, const glm::mat4& matrix)
{
	if (prog == ShapeProgram::SHAPE_FILL)
		fillProgram.setUniformMatrix4floats(name, matrix);
	else
		edgeProgram.setUniformMatrix4floats(name, matrix);
}

void IDrawable::setStaticUniforms()
{
	setModelMatrix(mModel);
	setLightPositionVector(gLightPos); //Light position doesn't change
	setLightColorVector(gLightColor); //Light color doesn't change
	setObjectColorVector(mColor); //Object color doesn't change
}

void IDrawable::setDynamicUniforms()
{
	setViewMatrix(gView);
	setProjectionMatrix(gProjection);
	setCameraViewPositionVector(cameraPos);
	setUseTexture();
}

void IDrawable::setAllUniforms()
{
	setStaticUniforms();
	setDynamicUniforms();
}

void IDrawable::setColor(float red, float green, float blue)
{
	mColor.x = red;
	mColor.y = green;
	mColor.z = blue;
	setObjectColorVector(mColor);
}

void IDrawable::setColor(const Point& color)
{
	mColor.x = color.x;
	mColor.y = color.y;
	mColor.z = color.z;
	setObjectColorVector(mColor);
}

void IDrawable::setColor(const glm::vec3& color)
{
	mColor = color;
	setObjectColorVector(mColor);
}

void IDrawable::setUseTexture()
{
	if (mHasTexture)
	{
		setUniform1i("u_UseTexture", 1);
		mTexture->setActiveTextureAndBind(0);
		setUniform1i("u_Texture", 0);
	}
	else
		setUniform1i("u_UseTexture", 0);
}

void IDrawable::setTexture(Texture* texture)
{
	mTexture = texture;
	if (mTexture != nullptr)
	{
		mHasTexture = true;
		setUniform1i("u_UseTexture", 1);
	}
}

void IDrawable::setTexture(const std::string& path)
{
	mTexture = new Texture(path);
	if (mTexture != nullptr)
	{
		mHasTexture = true;
		setUniform1i("u_UseTexture", 1);
	}
}

void IDrawable::draw3D()
{
	setDynamicUniforms();

	Renderer::getInstance().drawObject(mVA, mVB, &mIB, fillProgram, &edgeProgram, FILL, GL_TRIANGLES);

	if (mHasTexture && mTexture != nullptr)
		mTexture->unbindTexture();
}

void IDrawable::draw2D()
{
	setDynamicUniforms();
	Renderer::getInstance().drawObject(mVA, mVB, &mIB, fillProgram, &edgeProgram, EDGE, GL_LINES);
}

void IDrawable::draw()
{
	IDrawable::draw3D();
}

void IDrawable::rotateAroundAxis(const glm::vec3& axis, float angleDegrees)
{
	glm::vec3 centerVec(mCentre.x, mCentre.y, mCentre.z);
	glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(angleDegrees), glm::normalize(axis));

	for (size_t i = 0; i < mVertices.size(); i += mVBL.getStrideInFloats()) // step by 6 floats
	{
		// Position
		glm::vec3 vertex(mVertices[i], mVertices[i + 1], mVertices[i + 2]);
		vertex -= centerVec; // Translate to origin
		vertex = glm::vec3(rotation * glm::vec4(vertex, 1.0f)); // Rotate
		vertex += centerVec; // Translate back

		mVertices[i] = vertex.x;
		mVertices[i + 1] = vertex.y;
		mVertices[i + 2] = vertex.z;

		// Normal
		glm::vec3 normal(mVertices[i + 3], mVertices[i + 4], mVertices[i + 5]);
		normal = glm::vec3(rotation * glm::vec4(normal, 0.0f)); // Rotate normal only
		normal = glm::normalize(normal); // Normalize to be safe

		mVertices[i + 3] = normal.x;
		mVertices[i + 4] = normal.y;
		mVertices[i + 5] = normal.z;
	}

	setVBDataSizeAndCount(); // Upload new vertex positions (and normals) to GPU
}

void IDrawable::rotateAroundXaxis(float angleDegrees)
{
	rotateAroundAxis(glm::vec3(1.0f, 0.0f, 0.0f), angleDegrees);
}

void IDrawable::rotateAroundYaxis(float angleDegrees)
{
	rotateAroundAxis(glm::vec3(0.0f, 1.0f, 0.0f), angleDegrees);
}

void IDrawable::rotateAroundZaxis(float angleDegrees)
{
	rotateAroundAxis(glm::vec3(0.0f, 0.0f, 1.0f), angleDegrees);
}

void IDrawable::moveAlongVector(const glm::vec3& dir, float distance)
{
	glm::vec3 moveVec = glm::normalize(dir) * distance;

	// Translate all vertices
	for (size_t i = 0; i < mVertices.size(); i += 3)
	{
		mVertices[i] += moveVec.x;
		mVertices[i + 1] += moveVec.y;
		mVertices[i + 2] += moveVec.z;
	}

	// Update center
	mCentre.x += moveVec.x;
	mCentre.y += moveVec.y;
	mCentre.z += moveVec.z;

	setVBDataSizeAndCount(); // Send updated data to GPU
}


void IDrawable::moveAlongX(float distance)
{
	moveAlongVector(glm::vec3(1.0f, 0.0f, 0.0f), distance);
}

void IDrawable::moveAlongY(float distance)
{
	moveAlongVector(glm::vec3(0.0f, 1.0f, 0.0f), distance);
}

void IDrawable::moveAlongZ(float distance)
{
	moveAlongVector(glm::vec3(0.0f, 0.0f, 1.0f), distance);
}

void IDrawable::revolveAroundAxis(const Point& point, const glm::vec3& axis, float angleDegrees)
{
	glm::vec3 centerPoint(point.x, point.y, point.z);
	glm::vec3 normAxis = glm::normalize(axis);
	glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(angleDegrees), normAxis);

	for (size_t i = 0; i < mVertices.size(); i += mVBL.getStrideInFloats())
	{
		// Position
		glm::vec3 vertex(mVertices[i], mVertices[i + 1], mVertices[i + 2]);
		vertex -= centerPoint;
		vertex = glm::vec3(rotation * glm::vec4(vertex, 1.0f));
		vertex += centerPoint;

		mVertices[i] = vertex.x;
		mVertices[i + 1] = vertex.y;
		mVertices[i + 2] = vertex.z;

		// Normal
		glm::vec3 normal(mVertices[i + 3], mVertices[i + 4], mVertices[i + 5]);
		normal = glm::vec3(rotation * glm::vec4(normal, 0.0f));
		normal = glm::normalize(normal);

		mVertices[i + 3] = normal.x;
		mVertices[i + 4] = normal.y;
		mVertices[i + 5] = normal.z;
	}

	// Rotate the center point as well
	glm::vec3 centerVec(mCentre.x, mCentre.y, mCentre.z);
	centerVec -= centerPoint;
	centerVec = glm::vec3(rotation * glm::vec4(centerVec, 1.0f));
	centerVec += centerPoint;

	mCentre.x = centerVec.x;
	mCentre.y = centerVec.y;
	mCentre.z = centerVec.z;

	setVBDataSizeAndCount();
}


void IDrawable::revolveAroundXaxis(const Point& point, float angleDegrees)
{
	revolveAroundAxis(point, glm::vec3(1.0f, 0.0f, 0.0f), angleDegrees);
}

void IDrawable::revolveAroundYaxis(const Point& point, float angleDegrees)
{
	revolveAroundAxis(point, glm::vec3(0.0f, 1.0f, 0.0f), angleDegrees);
}

void IDrawable::revolveAroundZaxis(const Point& point, float angleDegrees)
{
	revolveAroundAxis(point, glm::vec3(0.0f, 0.0f, 1.0f), angleDegrees);
}
