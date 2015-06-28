#include <gtest/gtest.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glove/world/Transform.hpp>

namespace {
const glm::vec3 defaultPosition{0, 0, 0};
const glm::quat defaultRotation{};
const glm::vec3 defaultScale{1, 1, 1};

const glm::vec3 position{5, 10, 23.75f};
const glm::quat rotation = glm::angleAxis(45.7f, glm::vec3(1, 0, 0));
const glm::vec3 scale{10, 2.3f, 8};
const glm::mat4 transformMatrix =
    glm::mat4_cast(rotation) * glm::scale(glm::mat4(), scale) * glm::translate(glm::mat4(), position);
};

namespace BlueDwarf {
TEST(TransformTest, CheckDefaultConstructor) {
    Transform transform;

    EXPECT_EQ(defaultPosition, transform.GetPosition());
    EXPECT_EQ(defaultRotation, transform.GetRotation());
    EXPECT_EQ(defaultScale, transform.GetScale());
}

TEST(TransformTest, CheckPositionConstructor) {
    Transform transform{position};

    EXPECT_EQ(position, transform.GetPosition());
    EXPECT_EQ(defaultRotation, transform.GetRotation());
    EXPECT_EQ(defaultScale, transform.GetScale());
};

TEST(TransformTest, CheckRotationConstructor) {
    Transform transform{rotation};

    EXPECT_EQ(defaultPosition, transform.GetPosition());
    EXPECT_EQ(rotation, transform.GetRotation());
    EXPECT_EQ(defaultScale, transform.GetScale());
};

TEST(TransformTest, CheckPositionRotationConstructor) {
    Transform transform{position, rotation};

    EXPECT_EQ(position, transform.GetPosition());
    EXPECT_EQ(rotation, transform.GetRotation());
    EXPECT_EQ(defaultScale, transform.GetScale());
};

TEST(TransformTest, CheckPositionScaleConstructor) {
    Transform transform{position, scale};

    EXPECT_EQ(position, transform.GetPosition());
    EXPECT_EQ(defaultRotation, transform.GetRotation());
    EXPECT_EQ(scale, transform.GetScale());
};

TEST(TransformTest, CheckPositionRotationScaleConstructor) {
    Transform transform{position, rotation, scale};

    EXPECT_EQ(position, transform.GetPosition());
    EXPECT_EQ(rotation, transform.GetRotation());
    EXPECT_EQ(scale, transform.GetScale());
};

TEST(TransformTest, CheckIdentityTransform) {
    EXPECT_EQ(defaultPosition, Transform::Identity.GetPosition());
    EXPECT_EQ(defaultRotation, Transform::Identity.GetRotation());
    EXPECT_EQ(defaultScale, Transform::Identity.GetScale());
}

TEST(TransformTest, UpdatesPositionCorrectly) {
    Transform transform;
    transform.SetPosition(position);
    EXPECT_EQ(position, transform.GetPosition());
}

TEST(TransformTest, UpdatesRotationCorrectly) {
    Transform transform;
    transform.SetRotation(rotation);
    EXPECT_EQ(rotation, transform.GetRotation());
}

TEST(TransformTest, UpdatesScaleCorrectly) {
    Transform transform;
    transform.SetScale(scale);
    EXPECT_EQ(scale, transform.GetScale());
}

TEST(TransformTest, CalculatesMatrixCorrectly) {
    Transform transform{position, rotation, scale};

    EXPECT_EQ(transformMatrix, transform.ToMatrix());
}

TEST(TransformTest, AccumulatesCorrectly) {
    Transform transformA;
    Transform transformB{position, rotation, scale};

    transformA.Accumulate(transformB);
    EXPECT_EQ(defaultPosition + position, transformA.GetPosition());
    EXPECT_EQ(defaultRotation * rotation, transformA.GetRotation());
    EXPECT_EQ(defaultScale * scale, transformA.GetScale());
}
}