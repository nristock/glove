#pragma once

#include <list>

#include <core/GloveFwd.h>
#include <core/log/Log.h>
#include <core/natex/ISubsystemDefinition.h>

namespace {
enum NodeMarkState {
    UNMARKED,
    TEMPORARY,
    PERMANENT
};

struct DependencyGraphNode {
    const glove::ISubsystemDefinitionPtr subsystemDefinition;
    NodeMarkState markState;

    std::list<DependencyGraphNode*> dependentNodes;

    DependencyGraphNode(const glove::ISubsystemDefinitionPtr& subsystemDefinition)
        : subsystemDefinition(subsystemDefinition), markState(UNMARKED) {}
};
}

namespace glove {

class ExtensionDependencyGraph {
  public:
    typedef std::list<ISubsystemDefinitionPtr> SubsystemDefinitionList;
    typedef std::pair<SubsystemUuid, SubsystemUuid> Edge;

    ExtensionDependencyGraph(SubsystemDefinitionList& unsortedSubsystemDefinitions);
    virtual ~ExtensionDependencyGraph();

    SubsystemDefinitionList GetSortedList();

  private:
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