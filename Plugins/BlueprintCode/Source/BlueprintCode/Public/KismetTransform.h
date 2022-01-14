#pragma once

#include "KismetVisitor.h"

/*! Basic proof of concept turning Blueprint graph into code
 *
 * TODO:
 *  * Make sure temporary variables are uniques
 *  * Add more nodes
 */
struct KismetCodeTransform : public KismetVisitor<KismetCodeTransform, void> {
    using Return = void;
    using Super = KismetVisitor<KismetCodeTransform, void>;

    /*! Generates a function with its outputs as arguments.
     *  The function is called when the event is triggered
     */
    Return Event(UK2Node_Event* Node);

    Return DynamicCast(UK2Node_DynamicCast* Node);

    Return CallFunction(UK2Node_CallFunction* Node);

    void ExecuteArguments(UK2Node* Node);
};