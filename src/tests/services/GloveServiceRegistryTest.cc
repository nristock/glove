#include <gmock/gmock.hpp>

#include <boost/uuid/uuid_generators.hpp>

#include <glove/services/Services.hpp>
#include <glove/services/impl/GloveServiceRegistry.hpp>
#include <glove/services/exceptions/ServiceNotFound.hpp>
#include <glove/services/exceptions/ServiceNotInitialized.hpp>

#include "tests/mock/ServiceMock.hpp"

using ::testing::Return;
using ::testing::NiceMock;
using ::testing::_;

namespace glove {

auto uuidGenerator = boost::uuids::random_generator();
const ServiceType mockServiceType = uuidGenerator();
const ServiceType mockServiceType2 = uuidGenerator();

class GloveServiceRegistryTest : public ::testing::Test {
  protected:
    GloveServiceRegistry serviceRegistry;
};

TEST_F(GloveServiceRegistryTest, CanRegisterService) {
    EXPECT_FALSE(serviceRegistry.ProvidesService(mockServiceType));

    std::shared_ptr<NiceMock<ServiceMock>> mockService = std::make_shared<NiceMock<ServiceMock>>();
    ON_CALL(*mockService, GetType()).WillByDefault(Return(mockServiceType));
    ON_CALL(*mockService, NeedsInitialization()).WillByDefault(Return(true));

    serviceRegistry.RegisterService(mockService);

    EXPECT_TRUE(serviceRegistry.ProvidesService(mockServiceType));
    EXPECT_EQ(mockService, serviceRegistry.FindService(mockServiceType));
}

TEST_F(GloveServiceRegistryTest, RegisterInitializesServices) {
    std::shared_ptr<NiceMock<ServiceMock>> mockService = std::make_shared<NiceMock<ServiceMock>>();
    ON_CALL(*mockService, GetType()).WillByDefault(Return(mockServiceType));
    ON_CALL(*mockService, NeedsInitialization()).WillByDefault(Return(true));
    EXPECT_CALL(*mockService, Init(_)).Times(1).WillOnce(Return(true));

    serviceRegistry.RegisterService(mockService);
}

TEST_F(GloveServiceRegistryTest, RegisterPreventsDoubleInit) {
    std::shared_ptr<NiceMock<ServiceMock>> mockService1 = std::make_shared<NiceMock<ServiceMock>>();
    ON_CALL(*mockService1, GetType()).WillByDefault(Return(mockServiceType));
    ON_CALL(*mockService1, NeedsInitialization()).WillByDefault(Return(true));
    EXPECT_CALL(*mockService1, Init(_)).Times(1).WillOnce(Return(true));

    std::shared_ptr<NiceMock<ServiceMock>> mockService2 = std::make_shared<NiceMock<ServiceMock>>();
    ON_CALL(*mockService2, GetType()).WillByDefault(Return(mockServiceType2));
    ON_CALL(*mockService2, NeedsInitialization()).WillByDefault(Return(true));
    EXPECT_CALL(*mockService2, Init(_)).Times(1).WillOnce(Return(true));

    serviceRegistry.RegisterService(mockService1);
    serviceRegistry.RegisterService(mockService2);
}

TEST_F(GloveServiceRegistryTest, RegisterDoesntOverrideAlreadyRegisteredTypes) {
    std::shared_ptr<NiceMock<ServiceMock>> mockService1 = std::make_shared<NiceMock<ServiceMock>>();
    ON_CALL(*mockService1, GetType()).WillByDefault(Return(mockServiceType));
    ON_CALL(*mockService1, NeedsInitialization()).WillByDefault(Return(true));
    EXPECT_CALL(*mockService1, Init(_)).Times(1).WillOnce(Return(true));

    std::shared_ptr<NiceMock<ServiceMock>> mockService2 = std::make_shared<NiceMock<ServiceMock>>();
    ON_CALL(*mockService2, GetType()).WillByDefault(Return(mockServiceType));
    ON_CALL(*mockService2, NeedsInitialization()).WillByDefault(Return(true));
    EXPECT_CALL(*mockService2, Init(_)).Times(0);

    serviceRegistry.RegisterService(mockService1);
    EXPECT_EQ(mockService1, serviceRegistry.FindService(mockServiceType));

    serviceRegistry.RegisterService(mockService2);
    EXPECT_EQ(mockService1, serviceRegistry.FindService(mockServiceType));
}

TEST_F(GloveServiceRegistryTest, FindServiceReturnsEmptySharedPtrIfServiceCouldNotBeFound) {
    EXPECT_EQ(ServiceHandle(), serviceRegistry.FindService(mockServiceType));
}

TEST_F(GloveServiceRegistryTest, GetServiceReturnsQueriedService) {
    std::shared_ptr<NiceMock<ServiceMock>> mockService = std::make_shared<NiceMock<ServiceMock>>();
    ON_CALL(*mockService, GetType()).WillByDefault(Return(mockServiceType));
    ON_CALL(*mockService, NeedsInitialization()).WillByDefault(Return(true));
    EXPECT_CALL(*mockService, Init(_)).Times(1).WillOnce(Return(true));

    serviceRegistry.RegisterService(mockService);

    EXPECT_EQ(mockService, serviceRegistry.GetService(mockServiceType));
}

TEST_F(GloveServiceRegistryTest, GetServiceThrowsServiceNotFoundIfUnknownServiceTypeIsQueried) {
    EXPECT_THROW(serviceRegistry.GetService(mockServiceType), ServiceNotFound);
}

TEST_F(GloveServiceRegistryTest, GetServiceThrowsServiceNotInitializedIfTypeOfUninitializedServiceIsQueried) {
    serviceRegistry.DeferServiceInitialization(true);

    std::shared_ptr<NiceMock<ServiceMock>> mockService = std::make_shared<NiceMock<ServiceMock>>();
    ON_CALL(*mockService, GetType()).WillByDefault(Return(mockServiceType));
    ON_CALL(*mockService, NeedsInitialization()).WillByDefault(Return(true));

    serviceRegistry.RegisterService(mockService);

    EXPECT_THROW(serviceRegistry.GetService(mockServiceType), ServiceNotInitialized);
}

TEST_F(GloveServiceRegistryTest, ProvidesInitializedService) {
    serviceRegistry.DeferServiceInitialization(true);

    std::shared_ptr<NiceMock<ServiceMock>> mockService = std::make_shared<NiceMock<ServiceMock>>();
    ON_CALL(*mockService, GetType()).WillByDefault(Return(mockServiceType));
    ON_CALL(*mockService, NeedsInitialization()).WillByDefault(Return(true));
    EXPECT_CALL(*mockService, Init(_)).Times(1).WillOnce(Return(true));

    serviceRegistry.RegisterService(mockService);

    EXPECT_FALSE(serviceRegistry.ProvidesInitializedService(mockServiceType));
    serviceRegistry.InitAllServices();
    EXPECT_TRUE(serviceRegistry.ProvidesInitializedService(mockServiceType));
}

TEST_F(GloveServiceRegistryTest, RegisterDoesNotInitializeServiceIfInitializationIsDeferred) {
    serviceRegistry.DeferServiceInitialization(true);

    std::shared_ptr<NiceMock<ServiceMock>> mockService = std::make_shared<NiceMock<ServiceMock>>();
    ON_CALL(*mockService, GetType()).WillByDefault(Return(mockServiceType));
    ON_CALL(*mockService, NeedsInitialization()).WillByDefault(Return(true));
    EXPECT_CALL(*mockService, Init(_)).Times(0);

    serviceRegistry.RegisterService(mockService);
}

TEST_F(GloveServiceRegistryTest, InitAllServicesInitializesAllServices) {
    serviceRegistry.DeferServiceInitialization(true);

    // mockServicesPassX will initialize in initialization pass #X

    std::shared_ptr<NiceMock<ServiceMock>> mockServicePass1 = std::make_shared<NiceMock<ServiceMock>>();
    ON_CALL(*mockServicePass1, GetType()).WillByDefault(Return(mockServiceType));
    ON_CALL(*mockServicePass1, NeedsInitialization()).WillByDefault(Return(true));
    EXPECT_CALL(*mockServicePass1, Init(_)).Times(1).WillOnce(Return(true));

    std::shared_ptr<NiceMock<ServiceMock>> mockServicePass2 = std::make_shared<NiceMock<ServiceMock>>();
    ON_CALL(*mockServicePass2, GetType()).WillByDefault(Return(mockServiceType2));
    ON_CALL(*mockServicePass2, NeedsInitialization()).WillByDefault(Return(true));
    EXPECT_CALL(*mockServicePass2, Init(_)).Times(2).WillOnce(Return(false)).WillOnce(Return(true));

    serviceRegistry.RegisterService(mockServicePass2);
    serviceRegistry.RegisterService(mockServicePass1);

    serviceRegistry.InitAllServices();
}

TEST_F(GloveServiceRegistryTest, RecognizesServicesWhichDontNeedInitialization) {
    std::shared_ptr<NiceMock<ServiceMock>> mockService = std::make_shared<NiceMock<ServiceMock>>();
    ON_CALL(*mockService, GetType()).WillByDefault(Return(mockServiceType));
    ON_CALL(*mockService, NeedsInitialization()).WillByDefault(Return(false));

    serviceRegistry.RegisterService(mockService);

    serviceRegistry.InitAllServices();
}
}