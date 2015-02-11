#pragma once

#include <list>

#include "glove/GloveApi.hpp"
#include "glove/log/Log.hpp"
#include "glove/natex/Natex.hpp"

namespace glove {

class GLOVE_API_EXPORT ExtensionDependencyGraph {
  public:
    ExtensionDependencyGraph(SubsystemDefinitionList& unsortedSubsystemDefinitions);
    virtual ~ExtensionDependencyGraph();

    SubsystemDefinitionList GetSortedList();

  private:
    enum NodeMarkState { UNMARKED, TEMPORARY, PERMANENT };

    struct DependencyGraphNode {
        const ISubsystemDefinitionPtr subsystemDefinition;
        NodeMarkState markState;

        std::list<DependencyGraphNode*> dependentNodes;

        DependencyGraphNode(const ISubsystemDefinitionPtr& subsystemDefinition)
            : subsystemDefinition(subsystemDefinition), markState(UNMARKED) {}

        bool DependsOnSystemType(const SubsystemType& subsystemType);
    };

    typedef std::list<DependencyGraphNode> GraphNodeList;

    logging::GloveLogger logger;
    GraphNodeList graphNodes;
    SubsystemDefinitionList sortedSubsystemList;

    bool ContainsSubsystemDefinition(const ISubsystemDefinitionPtr& subsystemDefinition);
    void BuildEdges();
    void Sort();

    void VisitNode(DependencyGraphNode& node);
};

} /* namespace glove */