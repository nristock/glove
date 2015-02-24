#include <gmock/gmock.hpp>

#include <boost/uuid/uuid_generators.hpp>

#include <glove/services/Services.hpp>

#include "tests/mock/ServiceRegistryMock.hpp"

using ::testing::Return;
using ::testing::NiceMock;
using ::testing::_;

namespace {
auto uuidGenerator = boost::uuids::random_generator();
const glove::ServiceType serviceType = uuidGenerator();
}

namespace glove {
TEST(BasicServiceTest, CanStoreServiceType) {
    BasicService service(::serviceType);

    EXPECT_EQ(::serviceType, service.GetType());
}

TEST(BasicServiceTest, InitReturnsTrue) {
    BasicService service(::serviceType);
    ServiceRegistryMock mockRegistry;

    EXPECT_TRUE(service.Init(mockRegistry));
}
}