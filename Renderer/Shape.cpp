#include "Shape.h"

void Shape::setVBDataSizeAndCount()
{
	mVB.setDataSizeAndCount(mVertices.data(), mVertices.size() * sizeof(float), mVertices.size()/(mVBL.getStrideInBytes()/sizeof(float)));
}

void Shape::setVBLLayout3Floats()
{
	mVBL.push<float>(3);
}
void Shape::setVBLLayout3Pos3Norm()
{
	mVBL.push<float>(3);
	mVBL.push<float>(3);
}

void Shape::setVBLayout3Pos3Norm2Tex()
{
	mVBL.push<float>(3);
	mVBL.push<float>(3);
	mVBL.push<float>(2);
}

void Shape::setLayout()
{
	setVBLayout3Pos3Norm2Tex();
}

void Shape::setVABufferAndLayout()
{
	mVA.addBufferAndLayout(mVB, mVBL);
}

void Shape::setIBDataAndSize()
{
	mIB.setDataAndCount(mIndices.data(), mIndices.size());
}

void Shape::build()
{
	generateVerticesAndIndices();
	setLayout();
	setVBDataSizeAndCount();
	setVABufferAndLayout();
	setIBDataAndSize();
}

Shape::Shape()
	: mCentre(), mModel(1.0f), mColor(0.0627f, 0.4863f, 0.0627f)
{
}

Shape::Shape(float x, float y, float z)
	: mCentre(x, y, z), mModel(1.0f), mColor(0.0627f, 0.4863f, 0.0627f)
{
}

Shape::Shape(const Point& centre)
	: mCentre(centre), mModel(1.0f), mColor(0.0627f, 0.4863f, 0.0627f)
{
}

Shape::Shape(const Point& centre, const glm::vec3& color)
	: mCentre(centre), mModel(1.0f), mColor(color)
{
}

Shape::Shape(float x, float y, float z, glm::mat4 mat)
	: mCentre(x, y, z), mModel(mat), mColor(0.0627f, 0.4863f, 0.0627f)
{
}

Shape::Shape(float x, float y, float z, glm::mat4 mat, const glm::vec3& color)
	: mCentre(x, y, z), mModel(mat), mColor(color)
{
}

Shape::~Shape()
{
	delete mTexture;
}

void Shape::setPrograms(const Program* const fill, const Program* const edge)
{
	fillProgram.setVertexAndFragmentSources(fill->getVertexShaderSource().data(), fill->getFragmentShaderSource().data());
	edgeProgram.setVertexAndFragmentSources(edge->getVertexShaderSource().data(), edge->getFragmentShaderSource().data());

	setStaticUniforms();
}

void Shape::setFillProgram(const Program* const fill)
{
	fillProgram.setVertexAndFragmentSources(fill->getVertexShaderSource().data(), fill->getFragmentShaderSource().data());

	setStaticUniforms();
}

void Shape::setEdgeProgram(const Program* const edge)
{
	edgeProgram.setVertexAndFragmentSources(edge->getVertexShaderSource().data(), edge->getFragmentShaderSource().data());

	setStaticUniforms();
}

void Shape::setPrograms(const char* fillVertexSrc, const char* fillFragmentSrc, const char* edgeVertexSrc, const char* edgeFragmentSrc)
{
	fillProgram.setVertexAndFragmentSources(fillVertexSrc, fillFragmentSrc);
	edgeProgram.setVertexAndFragmentSources(edgeVertexSrc, edgeFragmentSrc);

	setStaticUniforms();
}

void Shape::setFillProgram(const char* fillVertexSrc, const char* fillFragmentSrc)
{
	fillProgram.setVertexAndFragmentSources(fillVertexSrc, fillFragmentSrc);

	setStaticUniforms();
}

void Shape::setEdgeProgram(const char* edgeVertexSrc, const char* edgeFragmentSrc)
{
	edgeProgram.setVertexAndFragmentSources(edgeVertexSrc, edgeFragmentSrc);

	setStaticUniforms();
}

void Shape::setModelMatrix(const glm::mat4& matrix)
{
	mModel = matrix;
	fillProgram.setUniformMatrix4fv("model", mModel);
	edgeProgram.setUniformMatrix4fv("model", mModel);
}

void Shape::setViewMatrix(const glm::mat4& matrix)
{
	fillProgram.setUniformMatrix4fv("view", matrix);
	edgeProgram.setUniformMatrix4fv("view", matrix);
}

void Shape::setProjectionMatrix(const glm::mat4& matrix)
{
	fillProgram.setUniformMatrix4fv("projection", matrix);
	edgeProgram.setUniformMatrix4fv("projection", matrix);
}

void Shape::setCameraViewPositionVector(const glm::vec3& vec)
{
	fillProgram.setUniformVector3fv("viewPos", vec);
	edgeProgram.setUniformVector3fv("viewPos", vec);
}

void Shape::setLightPositionVector(const glm::vec3& vec)
{
	fillProgram.setUniformVector3fv("lightPos", vec);
	edgeProgram.setUniformVector3fv("lightPos", vec);
}

void Shape::setLightColorVector(const glm::vec3& vec)
{
	fillProgram.setUniformVector3fv("lightColor", vec);
	edgeProgram.setUniformVector3fv("lightColor", vec);
}

void Shape::setObjectColorVector(const glm::vec3& vec)
{
	fillProgram.setUniformVector3fv("objectColor", vec);
	edgeProgram.setUniformVector3fv("objectColor", vec);
}

void Shape::setUniform1i(const char* name, int value)
{
	fillProgram.setUniform1i(name, value);
	edgeProgram.setUniform1i(name, value);
}

void Shape::setUniform1f(const char* name, float value)
{
	fillProgram.setUniform1f(name, value);
	edgeProgram.setUniform1f(name, value);
}

void Shape::setUniform3f(const char* name, float v0, float v1, float v2)
{
	fillProgram.setUniform3f(name, v0, v1, v2);
	edgeProgram.setUniform3f(name, v0, v1, v2);
}

void Shape::setUniformVector3fv(const char* name, const glm::vec3& vec)
{
	fillProgram.setUniformVector3fv(name, vec);
	edgeProgram.setUniformVector3fv(name, vec);
}

void Shape::setUniformMatrix4fv(const char* name, const glm::mat4& matrix)
{
	fillProgram.setUniformMatrix4fv(name, matrix);
	edgeProgram.setUniformMatrix4fv(name, matrix);
}

void Shape::setUniform1i(ShapeProgram prog, const char* name, int value)
{
	if (prog == ShapeProgram::SHAPE_FILL)
		fillProgram.setUniform1i(name, value);
	else
		edgeProgram.setUniform1i(name, value);
}

void Shape::setUniform1f(ShapeProgram prog, const char* name, float value)
{
	if (prog == ShapeProgram::SHAPE_FILL)
		fillProgram.setUniform1f(name, value);
	else
		edgeProgram.setUniform1f(name, value);
}

void Shape::setUniform3f(ShapeProgram prog, const char* name, float v0, float v1, float v2)
{
	if (prog == ShapeProgram::SHAPE_FILL)
		fillProgram.setUniform3f(name, v0, v1, v2);
	else
		edgeProgram.setUniform3f(name, v0, v1, v2);
}

void Shape::setUniformVector3fv(ShapeProgram prog, const char* name, const glm::vec3& vec)
{
	if (prog == ShapeProgram::SHAPE_FILL)
		fillProgram.setUniformVector3fv(name, vec);
	else
		edgeProgram.setUniformVector3fv(name, vec);
}

void Shape::setUniformMatrix4fv(ShapeProgram prog, const char* name, const glm::mat4& matrix)
{
	if (prog == ShapeProgram::SHAPE_FILL)
		fillProgram.setUniformMatrix4fv(name, matrix);
	else
		edgeProgram.setUniformMatrix4fv(name, matrix);
}

void Shape::setStaticUniforms()
{
	setModelMatrix(mModel);
	setLightPositionVector(gLightPos); //Light position doesn't change
	setLightColorVector(gLightColor); //Light color doesn't change
	setObjectColorVector(mColor); //Object color doesn't change
}

void Shape::setDynamicUniforms()
{
	setViewMatrix(gView);
	setProjectionMatrix(gProjection);
	setCameraViewPositionVector(cameraPos);
	setUseTexture();
}

void Shape::setAllUniforms()
{
	setStaticUniforms();
	setDynamicUniforms();
}

void Shape::setColor(float red, float green, float blue)
{
	mColor.x = red;
	mColor.y = green;
	mColor.z = blue;
	setObjectColorVector(mColor);
}

void Shape::setColor(const Point& color)
{
	mColor.x = color.x;
	mColor.y = color.y;
	mColor.z = color.z;
	setObjectColorVector(mColor);
}

void Shape::setColor(const glm::vec3& color)
{
	mColor = color;
	setObjectColorVector(mColor);
}

void Shape::setUseTexture()
{
	if (mHasTexture)
	{
		setUniform1i("u_UseTexture", 1);
		mTexture->bind(0);
		setUniform1i("u_Texture", 0);
	}
	else
		setUniform1i("u_UseTexture", 0);
}

void Shape::setTexture(Texture* texture)
{
	mTexture = texture;
	if (mTexture != nullptr)
	{
		mHasTexture = true;
		setUniform1i("u_UseTexture", 1);
	}
}

void Shape::setTexture(const std::string& path)
{
	mTexture = new Texture(path);
	if (mTexture != nullptr)
	{
		mHasTexture = true;
		setUniform1i("u_UseTexture", 1);
	}
}

void Shape::draw3D()
{
	setAllUniforms();

	Renderer::getInstance().draw(mVA, mVB, &mIB, fillProgram, &edgeProgram, FILL, GL_TRIANGLES);

	if (mHasTexture && mTexture != nullptr)
		mTexture->unBind();
}

void Shape::draw2D()
{
	setDynamicUniforms();
	Renderer::getInstance().draw(mVA, mVB, &mIB, fillProgram, &edgeProgram, EDGE, GL_LINES);
}

void Shape::rotateAroundAxis(const glm::vec3& axis, float angleDegrees)
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

void Shape::rotateAroundXaxis(float angleDegrees)
{
	rotateAroundAxis(glm::vec3(1.0f, 0.0f, 0.0f), angleDegrees);
}

void Shape::rotateAroundYaxis(float angleDegrees)
{
	rotateAroundAxis(glm::vec3(0.0f, 1.0f, 0.0f), angleDegrees);
}

void Shape::rotateAroundZaxis(float angleDegrees)
{
	rotateAroundAxis(glm::vec3(0.0f, 0.0f, 1.0f), angleDegrees);
}

void Shape::moveAlongVector(const glm::vec3& dir, float distance)
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


void Shape::moveAlongX(float distance)
{
	moveAlongVector(glm::vec3(1.0f, 0.0f, 0.0f), distance);
}

void Shape::moveAlongY(float distance)
{
	moveAlongVector(glm::vec3(0.0f, 1.0f, 0.0f), distance);
}

void Shape::moveAlongZ(float distance)
{
	moveAlongVector(glm::vec3(0.0f, 0.0f, 1.0f), distance);
}

void Shape::snapShapeCentreToCircularOrbit(const Point& orbitCenter, const glm::vec3& axis, float radius)
{
	glm::vec3 normAxis = glm::normalize(axis);

	// Choose arbitrary vector not parallel to axis
	glm::vec3 arbitrary = (std::abs(normAxis.x) < 0.99f)
		? glm::vec3(1.0f, 0.0f, 0.0f)
		: glm::vec3(0.0f, 1.0f, 0.0f);

	// Create orthonormal basis (u, v) for orbit plane
	glm::vec3 u = glm::normalize(glm::cross(normAxis, arbitrary));
	glm::vec3 v = glm::normalize(glm::cross(normAxis, u));

	// Relative vector from orbit center to shape center
	glm::vec3 toCentre = glm::vec3(mCentre.x, mCentre.y, mCentre.z) - glm::vec3(orbitCenter.x, orbitCenter.y, orbitCenter.z);

	// Remove component along axis (project onto orbit plane)
	glm::vec3 planar = toCentre - glm::dot(toCentre, normAxis) * normAxis;

	// Normalize planar direction
	glm::vec3 direction = glm::length(planar) > 0.0f ? glm::normalize(planar) : u;

	// Compute new center on circle
	glm::vec3 newCentre = glm::vec3(orbitCenter.x, orbitCenter.y, orbitCenter.z) + direction * radius;

	// Apply height offset (original height along axis)
	float height = glm::dot(toCentre, normAxis);
	newCentre += height * normAxis;

	// Compute shift vector
	glm::vec3 delta = newCentre - glm::vec3(mCentre.x, mCentre.y, mCentre.z);

	// Move shape
	for (size_t i = 0; i < mVertices.size(); i += 3)
	{
		mVertices[i + 0] += delta.x;
		mVertices[i + 1] += delta.y;
		mVertices[i + 2] += delta.z;
	}

	mCentre.x = newCentre.x;
	mCentre.y = newCentre.y;
	mCentre.z = newCentre.z;

	setVBDataSizeAndCount(); // Upload updated positions
}

void Shape::revolveAroundAxis(const Point& point, const glm::vec3& axis, float angleDegrees)
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


void Shape::revolveAroundXaxis(const Point& point, float angleDegrees)
{
	revolveAroundAxis(point, glm::vec3(1.0f, 0.0f, 0.0f), angleDegrees);
}

void Shape::revolveAroundYaxis(const Point& point, float angleDegrees)
{
	revolveAroundAxis(point, glm::vec3(0.0f, 1.0f, 0.0f), angleDegrees);
}

void Shape::revolveAroundZaxis(const Point& point, float angleDegrees)
{
	revolveAroundAxis(point, glm::vec3(0.0f, 0.0f, 1.0f), angleDegrees);
}

void Shape::snapShapeCentreToEllipticalOrbit(const Point& ellipseCenter, const glm::vec3& axis, float semiMajorRadius, float semiMinorRadius)
{
	glm::vec3 normAxis = glm::normalize(axis);

	// Create u-v basis perpendicular to axis
	glm::vec3 arbitrary = (std::abs(normAxis.x) < 0.99f)
		? glm::vec3(1.0f, 0.0f, 0.0f)
		: glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 u = glm::normalize(glm::cross(normAxis, arbitrary));
	glm::vec3 v = glm::normalize(glm::cross(normAxis, u));

	// Project current centre relative to ellipse center
	glm::vec3 c = glm::vec3(mCentre.x, mCentre.y, mCentre.z) - glm::vec3(ellipseCenter.x, ellipseCenter.y, ellipseCenter.z);
	float cu = glm::dot(c, u);
	float cv = glm::dot(c, v);

	// Normalize in ellipse space (a, b) to force point onto ellipse
	float ellipseAngle = std::atan2(cv / semiMinorRadius, cu / semiMajorRadius);
	glm::vec3 closestOnEllipse = semiMajorRadius * std::cos(ellipseAngle) * u + semiMinorRadius * std::sin(ellipseAngle) * v;

	// Preserve height along axis
	float height = glm::dot(c, normAxis);
	glm::vec3 newCentre = glm::vec3(ellipseCenter.x, ellipseCenter.y, ellipseCenter.z) + closestOnEllipse + height * normAxis;

	// Compute offset
	glm::vec3 delta = newCentre - glm::vec3(mCentre.x, mCentre.y, mCentre.z);

	// Apply offset to all vertices and center
	for (size_t i = 0; i < mVertices.size(); i += 3)
	{
		mVertices[i + 0] += delta.x;
		mVertices[i + 1] += delta.y;
		mVertices[i + 2] += delta.z;
	}

	mCentre.x = newCentre.x;
	mCentre.y = newCentre.y;
	mCentre.z = newCentre.z;

	setVBDataSizeAndCount(); // Upload updated positions
}

void Shape::revolveEllipticallyAroundAxis(const Point& center, const glm::vec3& axis, float angleDegrees, float semiMajorRadius, float semiMinorRadius)
{
	snapShapeCentreToEllipticalOrbit(center, axis, semiMajorRadius, semiMinorRadius);

	glm::vec3 normalizedAxis = glm::normalize(axis);

	glm::vec3 arbitrary = (std::abs(normalizedAxis.x) < 0.99f)
		? glm::vec3(1.0f, 0.0f, 0.0f)
		: glm::vec3(0.0f, 1.0f, 0.0f);

	glm::vec3 u = glm::normalize(glm::cross(normalizedAxis, arbitrary));
	glm::vec3 v = glm::normalize(glm::cross(normalizedAxis, u));

	float angleRad = glm::radians(angleDegrees);
	glm::vec3 offset = semiMajorRadius * cos(angleRad) * u + semiMinorRadius * sin(angleRad) * v;
	glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(angleDegrees), normalizedAxis);

	for (size_t i = 0; i < mVertices.size(); i += mVBL.getStrideInFloats())
	{
		glm::vec3 vertex(mVertices[i], mVertices[i + 1], mVertices[i + 2]);
		glm::vec3 direction = vertex - glm::vec3(center.x, center.y, center.z);
		float distance = glm::length(direction);

		glm::vec3 newPos = glm::vec3(center.x, center.y, center.z) + offset + normalizedAxis * glm::dot(direction, normalizedAxis);
		mVertices[i] = newPos.x;
		mVertices[i + 1] = newPos.y;
		mVertices[i + 2] = newPos.z;

		// Rotate normal
		glm::vec3 normal(mVertices[i + 3], mVertices[i + 4], mVertices[i + 5]);
		normal = glm::vec3(rotation * glm::vec4(normal, 0.0f));
		normal = glm::normalize(normal);

		mVertices[i + 3] = normal.x;
		mVertices[i + 4] = normal.y;
		mVertices[i + 5] = normal.z;
	}

	// Move centre of shape as well
	glm::vec3 centerVec(mCentre.x, mCentre.y, mCentre.z);
	glm::vec3 direction = centerVec - glm::vec3(center.x, center.y, center.z);
	float projection = glm::dot(direction, normalizedAxis);
	glm::vec3 newCenter = glm::vec3(center.x, center.y, center.z) + offset + normalizedAxis * projection;

	mCentre.x = newCenter.x;
	mCentre.y = newCenter.y;
	mCentre.z = newCenter.z;

	setVBDataSizeAndCount(); // Upload updated vertices
}