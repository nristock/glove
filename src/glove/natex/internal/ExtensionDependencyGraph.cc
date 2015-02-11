#include <queue>

#include "glove/natex/internal/ExtensionDependencyGraph.hpp"
#include "glove/natex/ISubsystemDefinition.hpp"

namespace glove {

ExtensionDependencyGraph::ExtensionDependencyGraph(SubsystemDefinitionList& unsortedSubsystemDefinitions) {
    for (ISubsystemDefinitionPtr& currentSubsystemDefinition : unsortedSubsystemDefinitions) {
        if (!ContainsSubsystemDefinition(currentSubsystemDefinition)) {
            graphNodes.push_back(DependencyGraphNode(currentSubsystemDefinition));
        }
    }

    BuildEdges();
    Sort();
}

void ExtensionDependencyGraph::BuildEdges() {
    for (DependencyGraphNode& currentGraphNode : graphNodes) {
        for (DependencyGraphNode& probableDependentGraphNode : graphNodes) {
            if (probableDependentGraphNode.DependsOnSystemType(currentGraphNode.subsystemDefinition->GetSystemType())) {
                currentGraphNode.dependentNodes.push_back(&probableDependentGraphNode);
            }
        }
    }
}

void ExtensionDependencyGraph::Sort() {
    for (DependencyGraphNode& currentGraphNode : graphNodes) {
        if (currentGraphNode.markState == UNMARKED) {
            VisitNode(currentGraphNode);
        }
    }
}

bool ExtensionDependencyGraph::ContainsSubsystemDefinition(const ISubsystemDefinitionPtr& subsystemDefinition) {
    for (const DependencyGraphNode& node : graphNodes) {
        if (node.subsystemDefinition == subsystemDefinition) {
            return true;
        }
    }

    return false;
}

void ExtensionDependencyGraph::VisitNode(DependencyGraphNode& node) {
    if (node.markState == TEMPORARY) {
        LOG(logger, warning, "Found probable non DAG dependency graph");
        return;
    }

    if (node.markState == PERMANENT) {
        return;
    }

    node.markState = TEMPORARY;
    for (DependencyGraphNode* dependentNode : node.dependentNodes) {
        VisitNode(*dependentNode);
    }

    node.markState = PERMANENT;
    sortedSubsystemList.push_front(node.subsystemDefinition);
}

SubsystemDefinitionList ExtensionDependencyGraph::GetSortedList() {
    return sortedSubsystemList;
}

ExtensionDependencyGraph::~ExtensionDependencyGraph() {
}

bool ExtensionDependencyGraph::DependencyGraphNode::DependsOnSystemType(const SubsystemType& subsystemType) {
    for (const SubsystemType& currentSubsystemType : subsystemDefinition->GetSystemDependencies()) {
        if (currentSubsystemType == subsystemType) {
            return true;
        }
    }

    return false;
}
}
