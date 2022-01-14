#include "KismetTransform.h"
#include "KismetGraphUtils.h"


DEFINE_LOG_CATEGORY_STATIC(LogBCGen, All, All);

#define GENPRINT(fmt, ...) \
    UE_LOG(LogBCGen, Display, TEXT(fmt), __VA_ARGS__);




void KismetCodeTransform::CallFunction(UK2Node_CallFunction* Node) {
    TArray<FString> Args;
    TArray<FString> Outs;

    // Generate the code to compute the arguments
    ExecuteArguments(Node);

    // TODO: We need to generate the code for the Arguments
    GetArgumentReturns(Node, Args, Outs);

    if (Outs.Num() > 0){
        GENPRINT("    %s = %s(%s)",
            *Join(",", Outs),
            *Node->GetFunctionName().ToString(),
            *Join(",", Args)
        );
    }
    else {
        GENPRINT("    %s(%s)",
            *Node->GetFunctionName().ToString(),
            *Join(",", Args)
        );
    }

    Super::Exec(FindNextExecutionNode(Node));
    return Return();
}

void KismetCodeTransform::ExecuteArguments(UK2Node* Node) {
    for (auto Pin : Node->Pins) {
        // Ignore execution pins
        if (Pin->PinType.PinCategory == "exec") {
            continue;
        }

        if (Pin->Direction == EGPD_Input) {
            for (auto Link: Pin->LinkedTo) {
                auto GraphNode = Link->GetOwningNode();
                Super::Exec(Cast<UK2Node>(GraphNode));
            }
        }
    }
}

void KismetCodeTransform::DynamicCast(UK2Node_DynamicCast* Node) {
    TArray<FString> Args;
    TArray<FString> Outs;

    // Generate the code to compute the arguments
    ExecuteArguments(Node);

    // TODO: We need to generate the code for the Arguments
    GetArgumentReturns(Node, Args, Outs);

    // Get the outputs
    GetNodeOutputs(Node, Outs);
    GENPRINT("    %s = Cast(%s, %s)",
        *Join(",", Outs),
        *Node->TargetType->GetName(),
        *Join(",", Args)
    );

    // TODO: Handle the Cast Failed exec pin
    // 
    //LogBCUtils: Display: >> Input Pins :
    //LogBCUtils: Display: >>> Name: '' exec(Links : 1)
    //LogBCUtils: Display: >>> Name: 'Object' object(Links : 1)
    //LogBCUtils: Display: >> Output Pins :
    //LogBCUtils: Display: >>> Name: '' exec(Links : 1)
    //LogBCUtils: Display: >>> Name: 'Cast Failed' exec(Links : 0)
    //LogBCUtils: Display: >>> Name: 'As Floating Health' object(Links : 2)
    //LogBCUtils: Display: >>> Name: 'Success' bool(Links : 0)

    Super::Exec(FindNextExecutionNode(Node));
    return Return();
}

void KismetCodeTransform::Event(UK2Node_Event* Node) {
    GENPRINT("def %s():", *Node->GetFunctionName().ToString());

    // Kepp traversing
    auto Next = FindNextExecutionNode(Node);
    // Event is not implemented
    if (Next == nullptr) {
        GENPRINT("    pass");
    }
    // 

    Super::Exec(Next);
    return Return();
}
