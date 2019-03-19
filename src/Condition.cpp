#include "Condition.hpp"
#include <iostream>
#include "CommandStrategy.hpp"
#include "MathCommandStrategy.hpp"

Condition::Condition() {}

Condition::Condition(Condition::Type type, VariablePointer leftVariable, VariablePointer rightVariable) {
    this->type = type;
    this->leftVariable = leftVariable;
    this->rightVariable = rightVariable;
}

CommandBlock Condition::createCommandBlock(std::string labelJump){
    CommandBlock block;
    VariablePointer tmpVariable = make_shared<TmpVariable>("USED");
    std::string labelHelp1 = labelJump + "_HELP1";
    std::string labelHelp2 = labelJump + "_HELP2";

    switch (type){
        case EQUAL:
            block.addCommandToEnd(SubtractionCommandStrategy::create(tmpVariable, rightVariable, leftVariable));
            block.addCommandToEnd(JumpConditionCommandStrategy::create(JumpConditionCommandStrategy::Type::JZERO, tmpVariable, labelHelp1));
            block.addCommandToEnd(JumpCommandStrategy::create(labelJump));
            block.addCommandToEnd(LabelCommandStrategy::create(labelHelp1));
            block.addCommandToEnd(SubtractionCommandStrategy::create(tmpVariable, leftVariable, rightVariable));
            block.addCommandToEnd(JumpConditionCommandStrategy::create(JumpConditionCommandStrategy::Type::JZERO, tmpVariable, labelHelp2));
            block.addCommandToEnd(JumpCommandStrategy::create(labelJump));
            block.addCommandToEnd(LabelCommandStrategy::create(labelHelp2));
            break;
        case NOT_EQUAL:
            block.addCommandToEnd(SubtractionCommandStrategy::create(tmpVariable, rightVariable, leftVariable));
            block.addCommandToEnd(JumpConditionCommandStrategy::create(JumpConditionCommandStrategy::Type::JZERO, tmpVariable, labelHelp1));
            block.addCommandToEnd(JumpCommandStrategy::create(labelHelp2));
            block.addCommandToEnd(LabelCommandStrategy::create(labelHelp1));
            block.addCommandToEnd(SubtractionCommandStrategy::create(tmpVariable, leftVariable, rightVariable));
            block.addCommandToEnd(JumpConditionCommandStrategy::create(JumpConditionCommandStrategy::Type::JZERO, tmpVariable, labelJump));
            block.addCommandToEnd(LabelCommandStrategy::create(labelHelp2));
            break;
        case LESSER:
            block.addCommandToEnd(SubtractionCommandStrategy::create(tmpVariable, rightVariable, leftVariable));
            block.addCommandToEnd(JumpConditionCommandStrategy::create(JumpConditionCommandStrategy::Type::JZERO, tmpVariable, labelJump));
            break;
        case GREATER:
            block.addCommandToEnd(SubtractionCommandStrategy::create(tmpVariable, leftVariable, rightVariable));
            block.addCommandToEnd(JumpConditionCommandStrategy::create(JumpConditionCommandStrategy::Type::JZERO, tmpVariable, labelJump));
            break;
        case LESSER_EQUAL:
            block.addCommandToEnd(AssignCommandStrategy::create(tmpVariable, rightVariable));
            block.addCommandToEnd(IncDecCommandStrategy::create(IncDecCommandStrategy::Type::INC, tmpVariable));
            block.addCommandToEnd(SubtractionCommandStrategy::create(tmpVariable, tmpVariable, leftVariable));
            block.addCommandToEnd(JumpConditionCommandStrategy::create(JumpConditionCommandStrategy::Type::JZERO, tmpVariable, labelJump));
            break;
        case GREATER_EQUAL:
            block.addCommandToEnd(AssignCommandStrategy::create(tmpVariable, leftVariable));
            block.addCommandToEnd(IncDecCommandStrategy::create(IncDecCommandStrategy::Type::INC, tmpVariable));
            block.addCommandToEnd(SubtractionCommandStrategy::create(tmpVariable, tmpVariable, rightVariable));
            block.addCommandToEnd(JumpConditionCommandStrategy::create(JumpConditionCommandStrategy::Type::JZERO, tmpVariable, labelJump));
            break;
        default:

            break;
    } 
    return block;    
}