#include <vendor/gmock/gmock.h>

#include <core/GloveFwd.h>
#include <core/GloveCore.h>

namespace glove {
class MockGloveCore : public GloveCore {
public:
    MockGloveCore() : GloveCore(1, new const char*[1]{""}) {}

    MOCK_CONST_METHOD0(GetEventBus, const EventBusPtr&());
};
}