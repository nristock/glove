#include <random>
#include <chrono>

#include <vendor/gmock/gmock.h>

#include <core/rendering/vertex/StaticVertexData.h>
#include <core/rendering/vertex/DynamicVertexData.h>
#include <core/rendering/vertex/VertexLayouts.h>

#include "mock/MockGpuBuffer.h"
#include "mock/MockVertexData.h"
#include "mock/MockGpuBufferFactory.h"

using ::testing::Return;
using ::testing::_;

namespace glove {
TEST(StaticVertexDataTest, ConstructorStoresVertexLayoutBufferBindingMapAndNumberOfVertices) {
    std::default_random_engine generator(
        static_cast<ulong>(std::chrono::system_clock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> distribution(0, 1000);

    std::size_t numVertices = static_cast<std::size_t>(distribution(generator));

    VertexBufferBindingMap bufferBindingMap;
    bufferBindingMap[0] = IGpuBufferPtr(new MockGpuBuffer());
    bufferBindingMap[1] = IGpuBufferPtr(new MockGpuBuffer());

    VertexLayout vertexLayout;

    StaticVertexData vertexData(vertexLayout, bufferBindingMap, numVertices);

    EXPECT_EQ(vertexLayout, vertexData.GetVertexLayout());
    EXPECT_EQ(bufferBindingMap[0], vertexData.GetGpuBuffer(0));
    EXPECT_EQ(bufferBindingMap[1], vertexData.GetGpuBuffer(1));
    EXPECT_EQ(numVertices, vertexData.GetVertexCount());
    EXPECT_EQ(bufferBindingMap.size(), vertexData.GetGpuBufferCount());
}

TEST(StaticVertexDataTest, BindAllBuffersBindsAllUnderlyingGpuBuffers) {
    VertexBufferBindingMap bufferBindingMap;

    for (int i = 0; i < 5; ++i) {
        IGpuBufferPtr gpuBuffer(new MockGpuBuffer());
        EXPECT_CALL(*(MockGpuBuffer*)gpuBuffer.get(), Bind()).Times(1);

        bufferBindingMap[i] = gpuBuffer;
    }

    VertexLayout vertexLayout;

    StaticVertexData vertexData(vertexLayout, bufferBindingMap, 10);
    vertexData.BindAllBuffers();
}

TEST(DynamicVertexDataTest, ConstructorCreatesGpuBufferAndEmptyVertexList) {
    BufferUsage bufferUsage = BufferUsage::DYNAMIC;
    IGpuBufferFactoryPtr gpuBufferFactory(new MockGpuBufferFactory());
    IGpuBufferPtr gpuBuffer(new MockGpuBuffer());

    EXPECT_CALL(*(MockGpuBufferFactory*)gpuBufferFactory.get(), CreateVertexBuffer(bufferUsage)).Times(1).WillOnce(
        Return(gpuBuffer));

    DynamicVertexData<VertexLayouts::Position> vertexData(gpuBufferFactory, VertexLayouts::Position::GetLayout(),
                                                          bufferUsage);

    EXPECT_TRUE(vertexData.GetVertices().empty());
    EXPECT_EQ(0, vertexData.GetVertexCount());
    EXPECT_EQ(1, vertexData.GetGpuBufferCount());
    EXPECT_EQ(gpuBuffer, vertexData.GetGpuBuffer(0));
    EXPECT_EQ(VertexLayouts::Position::GetLayout(), vertexData.GetVertexLayout());
}

TEST(DynamicVertexDataTest, ConstructorThrowsGivenVertexLayoutWithMoreThanOneBufferSlot) {
    IGpuBufferPtr gpuBuffer(new MockGpuBuffer());

    VertexLayout inconsistentLayout;
    inconsistentLayout.AddElement(
        VertexAttribute({0, 0, VertexAttributeType::FLOAT3, VertexAttributeSemantic::POSITION}));
    inconsistentLayout.AddElement(VertexAttribute({1, 0, VertexAttributeType::FLOAT3, VertexAttributeSemantic::COLOR}));

    EXPECT_THROW(DynamicVertexData<VertexLayouts::Position> vertexData(gpuBuffer, inconsistentLayout), GloveException);
}

TEST(DynamicVertexDataTest, BufferUsageDefaultsToStatic) {
    IGpuBufferFactoryPtr gpuBufferFactory(new MockGpuBufferFactory());
    IGpuBufferPtr gpuBuffer(new MockGpuBuffer());

    EXPECT_CALL(*(MockGpuBufferFactory*)gpuBufferFactory.get(), CreateVertexBuffer(BufferUsage::STATIC))
        .Times(1)
        .WillOnce(Return(gpuBuffer));

    DynamicVertexData<VertexLayouts::Position> vertexData(gpuBufferFactory, VertexLayouts::Position::GetLayout());
}

TEST(DynamicVertexDataTest, CanContructFromExistingGpuBuffer) {
    IGpuBufferPtr gpuBuffer(new MockGpuBuffer());
    DynamicVertexData<VertexLayouts::Position> vertexData(gpuBuffer, VertexLayouts::Position::GetLayout());

    EXPECT_EQ(1, vertexData.GetGpuBufferCount());
    EXPECT_EQ(gpuBuffer, vertexData.GetGpuBuffer(0));
}

TEST(DynamicVertexDataTest, GetVertexCountReturnsSizeOfBackingIndexListr) {
    IGpuBufferPtr gpuBuffer(new MockGpuBuffer());

    DynamicVertexData<VertexLayouts::Position> vertexData(gpuBuffer, VertexLayouts::Position::GetLayout());

    EXPECT_EQ(0, vertexData.GetVertexCount());

    vertexData.GetVertices().push_back(VertexLayouts::Position());
    EXPECT_EQ(1, vertexData.GetVertexCount());

    vertexData.GetVertices().push_back(VertexLayouts::Position());
    EXPECT_EQ(2, vertexData.GetVertexCount());
}

TEST(DynamicVertexDataTest, CanSetVertexList) {
    IGpuBufferPtr gpuBuffer(new MockGpuBuffer());
    DynamicVertexData<VertexLayouts::Position> vertexData(gpuBuffer, VertexLayouts::Position::GetLayout());
    DynamicVertexData<VertexLayouts::Position>::VertexList vertices;

    vertices.push_back(VertexLayouts::Position());
    vertices.push_back(VertexLayouts::Position());
    vertices.push_back(VertexLayouts::Position());

    vertexData.SetVertices(vertices);

    EXPECT_EQ(3, vertexData.GetVertexCount());
    EXPECT_EQ(vertices, vertexData.GetVertices());
}

TEST(DynamicVertexDataTest, BindAllBuffersBindsAllUnderlayingBuffer) {
    IGpuBufferPtr gpuBuffer(new MockGpuBuffer());
    EXPECT_CALL(*(MockGpuBuffer*)gpuBuffer.get(), Bind()).Times(1);

    DynamicVertexData<VertexLayouts::Position> vertexData(gpuBuffer, VertexLayouts::Position::GetLayout());
    vertexData.BindAllBuffers();
}

TEST(DynamicVertexDataTest, FlushCallsWriteDataOfUnderlyingBuffer) {
    IGpuBufferPtr gpuBuffer(new MockGpuBuffer());
    EXPECT_CALL(*(MockGpuBuffer*)gpuBuffer.get(), WriteData(0, _)).Times(1);

    DynamicVertexData<VertexLayouts::Position> vertexData(gpuBuffer, VertexLayouts::Position::GetLayout());
    vertexData.FlushBuffer();
}

TEST(DynamicVertexDataTest, FlushWritesDataToUnderlyingBuffer) {
    IGpuBufferPtr gpuBuffer(new MockGpuBuffer());

    DynamicVertexData<VertexLayouts::Position>::VertexList vertices;

    vertices.push_back(VertexLayouts::Position());
    vertices.push_back(VertexLayouts::Position());
    vertices.push_back(VertexLayouts::Position());

    EXPECT_CALL(*(MockGpuBuffer*)gpuBuffer.get(), WriteData(vertices.size() * sizeof(VertexLayouts::Position), _))
        .Times(1);

    DynamicVertexData<VertexLayouts::Position> vertexData(gpuBuffer, VertexLayouts::Position::GetLayout());
    vertexData.SetVertices(vertices);
    vertexData.FlushBuffer();
}
}