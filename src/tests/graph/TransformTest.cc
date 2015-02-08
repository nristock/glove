#include <glm/gtc/matrix_transform.hpp>

#include <glove/graph/Transform.h>
#include <vendor/gtest/gtest.h>

namespace glove {

class TransformTest : public ::testing::Test {
protected:
	const glm::vec3 defaultPosition;
	const glm::quat defaultRotation;
	const glm::vec3 defaultScale;
	glm::mat4 defaultTransformMatrix;

	const glm::vec3 parentPosition;

	const glm::vec3 position;
	glm::quat rotation;
	const glm::vec3 scale;
	glm::mat4 positionMatrix;
	glm::mat4 rotationMatrix;
	glm::mat4 scaleMatrix;
	glm::mat4 positionRotationMatrix;
	glm::mat4 positionScaleMatrix;
	glm::mat4 transformMatrix;

	glm::mat4 accumulatedMatrix;

	Transform transform;

	TransformTest() :
		defaultPosition(0, 0, 0),
		defaultRotation(),
		defaultScale(1, 1, 1),
		parentPosition(3, 5, 2),
		position(5, 10, 23.75f),
		scale(10, 2.3f, 8)
	{
        rotation = glm::angleAxis(45.7f, glm::vec3(1, 0, 0));

		defaultTransformMatrix = glm::mat4_cast(defaultRotation);
		defaultTransformMatrix = glm::scale(defaultTransformMatrix, defaultScale);
		defaultTransformMatrix = glm::translate(defaultTransformMatrix, defaultPosition);

		rotationMatrix = glm::mat4_cast(rotation);
		scaleMatrix = glm::scale(glm::mat4(), scale);
		positionMatrix = glm::translate(glm::mat4(), position);
		positionRotationMatrix = rotationMatrix * positionMatrix;
		positionScaleMatrix = scaleMatrix * positionMatrix;
		transformMatrix = rotationMatrix * scaleMatrix * positionMatrix;

		accumulatedMatrix = glm::translate(glm::mat4(), parentPosition);
		accumulatedMatrix = accumulatedMatrix * transformMatrix;
	}
};

TEST_F(TransformTest, CheckDefaultConstructor) {
	Transform transform;

	ASSERT_EQ(defaultPosition, transform.GetPosition());
	ASSERT_EQ(defaultRotation, transform.GetRotation());
	ASSERT_EQ(defaultScale, transform.GetScale());

	ASSERT_EQ(defaultTransformMatrix, transform.GetLocalTransform()) << "Default constructor fails to update local matrix.";
}

TEST_F(TransformTest, CheckPositionConstructor) {
	Transform transform(position);

	ASSERT_EQ(position, transform.GetPosition());
	ASSERT_EQ(defaultRotation, transform.GetRotation());
	ASSERT_EQ(defaultScale, transform.GetScale());

	ASSERT_EQ(positionMatrix, transform.GetLocalTransform()) << "Position constructor fails to update local matrix.";
}

TEST_F(TransformTest, CheckRotationConstructor) {
	Transform transform(rotation);

	ASSERT_EQ(defaultPosition, transform.GetPosition());
	ASSERT_EQ(rotation, transform.GetRotation());
	ASSERT_EQ(defaultScale, transform.GetScale());

	ASSERT_EQ(rotationMatrix, transform.GetLocalTransform()) << "Rotation constructor fails to update local matrix.";
}

TEST_F(TransformTest, CheckPositionRotationConstructor) {
	Transform transform(position, rotation);

	ASSERT_EQ(position, transform.GetPosition());
	ASSERT_EQ(rotation, transform.GetRotation());
	ASSERT_EQ(defaultScale, transform.GetScale());

	ASSERT_EQ(positionRotationMatrix, transform.GetLocalTransform()) << "PositionRotation constructor fails to update local matrix.";
}

TEST_F(TransformTest, CheckPositionScaleConstructor) {
	Transform transform(position, scale);

	ASSERT_EQ(position, transform.GetPosition());
	ASSERT_EQ(defaultRotation, transform.GetRotation());
	ASSERT_EQ(scale, transform.GetScale());

	ASSERT_EQ(positionScaleMatrix, transform.GetLocalTransform()) << "PositionScale constructor fails to update local matrix.";
}

TEST_F(TransformTest, CheckPositionRotationScaleConstructor) {
	Transform transform(position, rotation, scale);

	ASSERT_EQ(position, transform.GetPosition());
	ASSERT_EQ(rotation, transform.GetRotation());
	ASSERT_EQ(scale, transform.GetScale());

	ASSERT_EQ(transformMatrix, transform.GetLocalTransform()) << "PositionRotationScale constructor fails to update local matrix.";
}

TEST_F(TransformTest, CheckIdentityTransform) {
	ASSERT_EQ(Transform::Identity(), transform);
}

TEST_F(TransformTest, UpdatesPositionCorrectly) {
	transform.SetPosition(position);
	ASSERT_EQ(position, transform.GetPosition());
	ASSERT_EQ(positionMatrix, transform.GetLocalTransform()) << "Position setter doesn't update the local matrix.";
}

TEST_F(TransformTest, UpdatesRotationCorrectly) {
	Transform transform;

	transform.SetRotation(rotation);
	ASSERT_EQ(rotation, transform.GetRotation());
	ASSERT_EQ(rotationMatrix, transform.GetLocalTransform()) << "Rotation setter doesn't update the local matrix.";
}

TEST_F(TransformTest, UpdatesScaleCorrectly) {
	transform.SetScale(scale);
	ASSERT_EQ(scale, transform.GetScale());
	ASSERT_EQ(scaleMatrix, transform.GetLocalTransform()) << "Scale setter doesn't update the local matrix.";
}

TEST_F(TransformTest, CheckPositionGetterSetter) {
	transform.SetPosition(position);
	ASSERT_EQ(position, transform.GetPosition()) << "SetPosition(void) failed";
}

TEST_F(TransformTest, CheckRotationGetterSetter) {
	transform.SetRotation(rotation);
	ASSERT_EQ(rotation, transform.GetRotation()) << "SetRotation(void) failed";
}

TEST_F(TransformTest, CheckScaleGetterSetter) {
	transform.SetScale(scale);
	ASSERT_EQ(scale, transform.GetScale()) << "SetScale(void) failed";
}

TEST_F(TransformTest, CheckGlobalTransformMatrixCalculation) {
	transform.SetPosition(position);
	transform.SetScale(scale);
	transform.SetRotation(rotation);

	Transform parentTransform(parentPosition);
	transform.RecalculateAccumulatedTransform(parentTransform);

	ASSERT_EQ(accumulatedMatrix, transform.GetGlobalTransform());
}

}