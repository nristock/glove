#include <gmock/gmock.hpp>

#include <glove/natex/SharedLibrary.hpp>

namespace BlueDwarf {
class SharedLibraryMock : public SharedLibrary {
  public:
    MOCK_METHOD1(GetSymbol, void*(const std::string& symbolName));
};
}