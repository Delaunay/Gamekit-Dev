#pragma once

#include "BlueprintCode.h"

#include "K2Node.h"
#include "K2Node_FunctionEntry.h"
#include "K2Node_SetVariableOnPersistentFrame.h"
#include "K2Node_VariableSet.h"
#include "K2Node_VariableGet.h"
#include "K2Node_CallFunction.h"
#include "K2Node_Event.h"
#include "K2Node_DynamicCast.h"

template <typename Impl, typename Return, typename... Args>
struct KismetVisitor {
    enum class NodeKind {
        Unknown,
        CallFunction,
        VariableGet,
        Event,
        DynamicCast,
    };

    const NodeKind ClassNodeTypeMapping(UK2Node* Node) {
        static TMap<UClass*, NodeKind> Mapping{
            {UK2Node_CallFunction::StaticClass(), NodeKind::CallFunction},
            {UK2Node_VariableGet::StaticClass(), NodeKind::VariableGet},
            {UK2Node_Event::StaticClass(), NodeKind::Event},
            {UK2Node_DynamicCast::StaticClass(), NodeKind::DynamicCast},
        };

        UClass* Class = Node->GetClass();
        if (!Mapping.Contains(Class)) {
            return NodeKind::Unknown;
        }

        return Mapping[Class];
    }

    // Exec find the underlying type of a UK2 node and call the correct implementation
    Return Exec(UK2Node* Node, Args... args) {
        if (Node == nullptr) {
            return Return();
        }

        switch (ClassNodeTypeMapping(Node)) {

        case NodeKind::CallFunction: {
            if (auto NodeCast = Cast<UK2Node_CallFunction>(Node)) {
                return static_cast<Impl&>(*this).CallFunction(NodeCast, args...);
            }
        }
        case NodeKind::Event: {
            if (auto NodeCast = Cast<UK2Node_Event>(Node)) {
                return static_cast<Impl&>(*this).Event(NodeCast, args...);
            }
        }
        case NodeKind::DynamicCast: {
            if (auto NodeCast = Cast<UK2Node_DynamicCast>(Node)) {
                return static_cast<Impl&>(*this).DynamicCast(NodeCast, args...);
            }
        }

        // Edge cases
        case NodeKind::Unknown: {
            UE_LOG(LogBlueprintCode, Display, TEXT("Unknown class %s"), *Node->GetClass()->GetName());
            return Return();
        }
        }

        UE_LOG(LogBlueprintCode, Display, TEXT("Unreachable %s (Cast Error should be imposible)"), *Node->GetClass()->GetName());
        return Return();
    }

    // Fallbacks
    Return Event(UK2Node_Event* Node, Args... args) {
        UE_LOG(LogBlueprintCode, Warning, TEXT("Event was not implemented"));
        return Return();
    }

    Return CallFunction(UK2Node_CallFunction* Node, Args... args) {
        UE_LOG(LogBlueprintCode, Warning, TEXT("CallFunction was not implemented"));
        return Return();
    }

    Return DynamicCast(UK2Node_DynamicCast* Node, Args... args) {
        UE_LOG(LogBlueprintCode, Warning, TEXT("DynamicCast was not implemented"));
        return Return();
    }
};

