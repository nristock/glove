#include "ExtensionDependencyGraph.h"

#include <queue>

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
            for (const SubsystemType& subsystemType :
                 probableDependentGraphNode.subsystemDefinition->GetSystemDependencies()) {
                if (subsystemType == currentGraphNode.subsystemDefinition->GetSystemType()) {
                    currentGraphNode.dependentNodes.push_back(&probableDependentGraphNode);
                }
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

ExtensionDependencyGraph::SubsystemDefinitionList ExtensionDependencyGraph::GetSortedList() {
    return sortedSubsystemList;
}

ExtensionDependencyGraph::~ExtensionDependencyGraph() {}
}