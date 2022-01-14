#include "GenerateCode.h"
#include "KismetGraphUtils.h"
#include "KismetTransform.h"
#include "KismetGraphDebug.h"

// Kismet
void GeneratePythonFromBlueprint(UBlueprint* Source) {

    // TArray<UEdGraph*> UbergraphPages;
    // TArray<UEdGraph*> FunctionGraphs;
    // TArray<UEdGraph*> DelegateSignatureGraphs;
    // TArray<UEdGraph*> MacroGraphs;
    // TArray<UEdGraph*> IntermediateGeneratedGraphs;
    // TArray<UEdGraph*> EventGraphs;
    // 
    // For each event graph 
    for (UEdGraph* Graph : Source->UbergraphPages) {
        DumpGraph(Graph);
    }

    KismetCodeTransform transform;

    for (UEdGraph* Graph : Source->UbergraphPages) {
        auto Roots = FindRoots(Graph);
        for (UK2Node* GraphNode : Roots) {
            UE_LOG(LogBlueprintCode, Display, TEXT("===================="));
            transform.Exec(GraphNode);
        }
    }
}
