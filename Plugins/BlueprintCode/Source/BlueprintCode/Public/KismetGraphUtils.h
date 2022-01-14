#pragma once

#include "CoreMinimal.h"

void GetArgumentReturns(class UK2Node* Node, TArray<FString>& Args, TArray<FString>& Outs);

void GetNodeOutputs(class UK2Node* Node, TArray<FString>& Outs);

UK2Node* FindNextExecutionNode(UK2Node* Node);

TArray<UK2Node*> FindRoots(UEdGraph* Graph);

FString Join(FString Sep, TArray<FString> Strings);

int CountInputPins(TArray<UEdGraphPin*> const& Pins);
