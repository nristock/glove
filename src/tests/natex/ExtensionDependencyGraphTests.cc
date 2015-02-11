#include <gtest/gtest.hpp>

#include <random>

#include <glove/natex/Natex.hpp>
#include <glove/natex/ISubsystemDefinition.hpp>
#include <glove/GloveException.hpp>
#include <glove/natex/internal/ExtensionDependencyGraph.hpp>

namespace glove {

class GenericSubsystemDefinition : public ISubsystemDefinition {
  public:
    GenericSubsystemDefinition(SubsystemType myType) : myType(myType) {}

    virtual const std::string& GetSystemName() { throw GLOVE_EXCEPTION("Unexpected call"); }
    virtual const SubsystemUuid& GetSystemUuid() { throw GLOVE_EXCEPTION("Unexpected call"); }
    virtual const SubsystemType& GetSystemType() { return myType; }
    virtual const SubsystemTypeList& GetSystemDependencies() { return dependencies; }
    virtual const ISubsystemFactoryPtr& GetSystemFactory() { throw GLOVE_EXCEPTION("Unexpected call"); }

    void AddDependency(SubsystemType dependency) { dependencies.push_back(dependency); }

  private:
    SubsystemType myType;
    SubsystemTypeList dependencies;
};

class ExtensionDependencyGraphTests : public ::testing::Test {
  public:
    ExtensionDependencyGraphTests() {
        SubsystemType testSubsystemTypes[6] = {
            {0xb8, 0xd6, 0x0c, 0x12, 0x40, 0x35, 0x4a, 0x77, 0xa9, 0x5b, 0xb5, 0x48, 0x76, 0xdd, 0x9d, 0x46},
            {0xa8, 0x81, 0xc0, 0xd2, 0x16, 0x26, 0x43, 0x68, 0x9e, 0x44, 0xef, 0xc6, 0x28, 0xf3, 0x92, 0x7c},
            {0x69, 0x87, 0x18, 0x6a, 0xa6, 0x4f, 0x44, 0x07, 0xb5, 0x28, 0x32, 0xea, 0xbb, 0x9b, 0x13, 0xbf},
            {0xf8, 0x1b, 0x91, 0x5d, 0x86, 0x3b, 0x49, 0x06, 0x8e, 0xbf, 0x14, 0x59, 0x82, 0x79, 0xa5, 0x96},
            {0x81, 0xbb, 0xa0, 0xe8, 0xac, 0xa0, 0x4b, 0x57, 0xaf, 0x76, 0x7a, 0x8e, 0xbe, 0xaf, 0x1b, 0x68},
            {0x11, 0x46, 0x6f, 0x8f, 0xfe, 0xa6, 0x49, 0x70, 0x91, 0x68, 0xa5, 0xd8, 0x8d, 0xd8, 0x01, 0xb5}};

        std::default_random_engine randomGenerator;
        std::uniform_int_distribution<int> randomDistribution(0, 5);
        auto GenerateRandomNumber = std::bind(randomDistribution, randomGenerator);

        ISubsystemDefinitionPtr testSubsystems[6] = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};

        for (ushort i = 0; i < 6; ++i) {
            int subsystemIndex = 0;
            do {
                subsystemIndex = GenerateRandomNumber();
            } while (testSubsystems[subsystemIndex] != nullptr);

            testSubsystems[subsystemIndex] =
                ISubsystemDefinitionPtr(new GenericSubsystemDefinition(testSubsystemTypes[i]));
        }

        GenericSubsystemDefinition* subsystem1 = (GenericSubsystemDefinition*)testSubsystems[0].get();
        GenericSubsystemDefinition* subsystem2 = (GenericSubsystemDefinition*)testSubsystems[1].get();
        GenericSubsystemDefinition* subsystem3 = (GenericSubsystemDefinition*)testSubsystems[2].get();
        GenericSubsystemDefinition* subsystem4 = (GenericSubsystemDefinition*)testSubsystems[3].get();
        GenericSubsystemDefinition* subsystem5 = (GenericSubsystemDefinition*)testSubsystems[4].get();
        GenericSubsystemDefinition* subsystem6 = (GenericSubsystemDefinition*)testSubsystems[5].get();

        subsystem6->AddDependency(subsystem4->GetSystemType());
        subsystem6->AddDependency(subsystem2->GetSystemType());
        subsystem5->AddDependency(subsystem6->GetSystemType());
        subsystem5->AddDependency(subsystem4->GetSystemType());
        subsystem4->AddDependency(subsystem2->GetSystemType());
        subsystem4->AddDependency(subsystem3->GetSystemType());
        subsystem4->AddDependency(subsystem1->GetSystemType());
        subsystem3->AddDependency(subsystem1->GetSystemType());
        subsystem3->AddDependency(subsystem2->GetSystemType());
        subsystem2->AddDependency(subsystem1->GetSystemType());

        for (ushort i = 0; i < 6; ++i) {
            unsortedDefinitionList.push_back(testSubsystems[i]);
        }

        sortedDefinitionList.push_back(testSubsystems[0]);
        sortedDefinitionList.push_back(testSubsystems[1]);
        sortedDefinitionList.push_back(testSubsystems[2]);
        sortedDefinitionList.push_back(testSubsystems[3]);
        sortedDefinitionList.push_back(testSubsystems[5]);
        sortedDefinitionList.push_back(testSubsystems[4]);
    }

  protected:
    SubsystemDefinitionList unsortedDefinitionList;
    SubsystemDefinitionList sortedDefinitionList;
};

TEST_F(ExtensionDependencyGraphTests, SortsDependenciesCorrectly) {
    ExtensionDependencyGraph* dependencyGraph;
    ASSERT_NO_THROW(dependencyGraph = new ExtensionDependencyGraph(unsortedDefinitionList));

    SubsystemDefinitionList graphSortedList = dependencyGraph->GetSortedList();

    ASSERT_EQ(sortedDefinitionList.size(), graphSortedList.size());

    for (std::size_t i = 0; i < sortedDefinitionList.size(); ++i) {
        ISubsystemDefinitionPtr preSortedDefinition = *std::next(sortedDefinitionList.begin(), i);
        ISubsystemDefinitionPtr graphSortedDefinition = *std::next(graphSortedList.begin(), i);

        ASSERT_EQ(preSortedDefinition->GetSystemType(), graphSortedDefinition->GetSystemType());
    }

    ASSERT_NO_THROW(delete dependencyGraph);
}
}