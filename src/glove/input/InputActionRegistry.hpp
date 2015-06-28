#pragma once

#include <vector>
#include <unordered_map>

#include "glove/BlueDwarfApi.hpp"
#include "glove/services/Services.hpp"
#include "glove/input/Input.hpp"

namespace BlueDwarf {
class BD_API_EXPORT InputActionRegistry : public BasicService {
  public:
    static const ServiceType serviceType;

    InputActionRegistry();

    void RegisterInputAction(InputActionHandle inputAction);
    void MapActionKey(const Key& key, InputActionHandle inputAction);

  private:
    std::vector<InputActionHandle> inputActions;
    std::unordered_map<std::size_t, InputActionHandle> actionMappings;

};
}