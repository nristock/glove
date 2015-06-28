#include <gmock/gmock.hpp>

#include <glove/application/GloveApplication.hpp>

namespace {
class ApplicationFacetMock : public glove::ApplicationFacet {
  public:
    MOCK_METHOD0(Configure, void());
    MOCK_METHOD0(Bootstrap, void());
    MOCK_METHOD0(Initialize, void());
    MOCK_METHOD0(Finalize, void());
};
}

namespace glove {
TEST(ApplicationTest, ManagesFacetLifecycle) {
    auto facetMock = std::make_shared<ApplicationFacetMock>();
    EXPECT_CALL(*facetMock, Configure()).Times(1);
    EXPECT_CALL(*facetMock, Bootstrap()).Times(1);
    EXPECT_CALL(*facetMock, Initialize()).Times(1);
    EXPECT_CALL(*facetMock, Finalize()).Times(1);

    GloveApplication app;
    app.AddFacet(facetMock);

    app.Run();
}

}