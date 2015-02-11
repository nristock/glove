#include <random>
#include <chrono>

#include <gmock/gmock.hpp>

#include <glove/rendering/vertex/StaticIndexData.hpp>
#include <glove/rendering/vertex/DynamicIndexData.hpp>

#include "tests/rendering/mock/MockGpuBuffer.hpp"
#include "tests/rendering/mock/MockVertexData.hpp"
#include "tests/rendering/mock/MockGpuBufferFactory.hpp"

using ::testing::Return;
using ::testing::_;

namespace glove {
TEST(StaticIndexDataTest, ConstructorStoresGpuBufferAndNumverOfIndices) {
    std::default_random_engine generator(
        static_cast<ulong>(std::chrono::system_clock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> distribution(0, 1000);

    IGpuBufferPtr gpuBuffer(new MockGpuBuffer());
    std::size_t numIndices = static_cast<std::size_t>(distribution(generator));

    StaticIndexData indexData(gpuBuffer, numIndices);

    EXPECT_EQ(gpuBuffer, indexData.GetGpuBuffer());
    EXPECT_EQ(numIndices, indexData.GetIndexCount());
}

TEST(StaticIndexDataTest, BindBufferBindsUnderlyingGpuBuffer) {
    IGpuBufferPtr gpuBuffer(new MockGpuBuffer());
    EXPECT_CALL(*(MockGpuBuffer*)gpuBuffer.get(), Bind()).Times(1);

    StaticIndexData indexData(gpuBuffer, 10);
    indexData.BindBuffer();
}

TEST(DynamicIndexDataTest, ConstructorCreatesGpuBufferAndEmptyIndexList) {
    IGpuBufferFactoryPtr gpuBufferFactory(new MockGpuBufferFactory());
    IGpuBufferPtr gpuBuffer(new MockGpuBuffer());

    EXPECT_CALL(*(MockGpuBufferFactory*)gpuBufferFactory.get(), CreateIndexBuffer()).Times(1).WillOnce(
        Return(gpuBuffer));

    DynamicIndexData<unsigned int> indexData(gpuBufferFactory);

    EXPECT_EQ(gpuBuffer, indexData.GetGpuBuffer());
    EXPECT_TRUE(indexData.GetIndices().empty());
    EXPECT_EQ(0, indexData.GetIndexCount());
}

TEST(DynamicIndexDataTest, BindBufferBindsUnderlyingGpuBuffer) {
    IGpuBufferFactoryPtr gpuBufferFactory(new MockGpuBufferFactory());
    IGpuBufferPtr gpuBuffer(new MockGpuBuffer());

    EXPECT_CALL(*(MockGpuBufferFactory*)gpuBufferFactory.get(), CreateIndexBuffer()).Times(1).WillOnce(
        Return(gpuBuffer));
    EXPECT_CALL(*(MockGpuBuffer*)gpuBuffer.get(), Bind()).Times(1);

    DynamicIndexData<unsigned int> indexData(gpuBufferFactory);
    indexData.BindBuffer();
}

TEST(DynamicIndexDataTest, FlushCallsWriteDataOfUnderlyingBuffer) {
    IGpuBufferFactoryPtr gpuBufferFactory(new MockGpuBufferFactory());
    IGpuBufferPtr gpuBuffer(new MockGpuBuffer());

    EXPECT_CALL(*(MockGpuBufferFactory*)gpuBufferFactory.get(), CreateIndexBuffer()).Times(1).WillOnce(
        Return(gpuBuffer));
    EXPECT_CALL(*(MockGpuBuffer*)gpuBuffer.get(), WriteData(0, _)).Times(1);

    DynamicIndexData<unsigned int> indexData(gpuBufferFactory);
    indexData.FlushBuffer();
}

TEST(DynamicIndexDataTest, FlushWritesDataToUnderlyingBuffer) {
    IGpuBufferFactoryPtr gpuBufferFactory(new MockGpuBufferFactory());
    IGpuBufferPtr gpuBuffer(new MockGpuBuffer());

    EXPECT_CALL(*(MockGpuBufferFactory*)gpuBufferFactory.get(), CreateIndexBuffer()).Times(1).WillOnce(
        Return(gpuBuffer));

    DynamicIndexData<unsigned int>::IndexList indices;

    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(3);

    EXPECT_CALL(*(MockGpuBuffer*)gpuBuffer.get(), WriteData(indices.size() * sizeof(unsigned int), _)).Times(1);

    DynamicIndexData<unsigned int> indexData(gpuBufferFactory);
    indexData.SetIndices(indices);
    indexData.FlushBuffer();
}

TEST(DynamicIndexDataTest, GetIndexCountReturnsSizeOfBackingIndexListr) {
    IGpuBufferFactoryPtr gpuBufferFactory(new MockGpuBufferFactory());
    IGpuBufferPtr gpuBuffer(new MockGpuBuffer());

    EXPECT_CALL(*(MockGpuBufferFactory*)gpuBufferFactory.get(), CreateIndexBuffer()).Times(1).WillOnce(
        Return(gpuBuffer));

    DynamicIndexData<unsigned int> indexData(gpuBufferFactory);

    EXPECT_EQ(0, indexData.GetIndexCount());

    indexData.GetIndices().push_back(5);
    EXPECT_EQ(1, indexData.GetIndexCount());

    indexData.GetIndices().push_back(2);
    EXPECT_EQ(2, indexData.GetIndexCount());
}

TEST(DynamicIndexDataTest, CanSetIndexList) {
    IGpuBufferFactoryPtr gpuBufferFactory(new MockGpuBufferFactory());
    IGpuBufferPtr gpuBuffer(new MockGpuBuffer());

    EXPECT_CALL(*(MockGpuBufferFactory*)gpuBufferFactory.get(), CreateIndexBuffer()).Times(1).WillOnce(
        Return(gpuBuffer));

    DynamicIndexData<unsigned int> indexData(gpuBufferFactory);
    DynamicIndexData<unsigned int>::IndexList indices;

    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(3);

    indexData.SetIndices(indices);

    EXPECT_EQ(3, indexData.GetIndexCount());
    EXPECT_EQ(indices, indexData.GetIndices());
}
}