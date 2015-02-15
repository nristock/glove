#include <gmock/gmock.hpp>

#include <glove/GloveFwd.hpp>
#include <glove/GloveCore.hpp>
#include <glove/configuration/Configuration.hpp>

namespace glove {
class MockGloveCore : public GloveCore {
public:
    MockGloveCore() : GloveCore(Configuration(), nullptr, nullptr, nullptr, nullptr) {}

    MOCK_CONST_METHOD0(GetEventBus, const EventBusPtr&());
};
}