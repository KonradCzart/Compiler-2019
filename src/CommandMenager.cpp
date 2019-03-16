#include "CommandMenager.hpp"
#include "MathCommandStrategy.hpp"

CommandBlock CommandMenager::getCommandIf(Condition condition, CommandBlock& ifBlock){
    CommandBlock resultBlock;
    std::string labelStart = labelMenager.getNextLabel("IF");
    std::string labelEnd = labelMenager.getLabel(labelStart, "END");
    CommandBlock conditionBlock = condition.createCommandBlock(labelEnd);

    resultBlock.addCommandToEnd(CodeCommandStrategy::create(CodeCommandStrategy::Type::NEW_BLOCK, "IF"));
    resultBlock.addCommandToEnd(LabelCommandStrategy::create(labelStart));
    resultBlock.append(conditionBlock);
    resultBlock.append(ifBlock);
    resultBlock.addCommandToEnd(CodeCommandStrategy::create(CodeCommandStrategy::Type::NEW_BLOCK, "END_IF"));
    resultBlock.addCommandToEnd(LabelCommandStrategy::create(labelEnd));

    return resultBlock;
}

CommandBlock CommandMenager::getCommandIfElse(Condition condition, CommandBlock& trueBlock, CommandBlock& falseBlock){
    CommandBlock resultBlock;
    std::string labelStart = labelMenager.getNextLabel("IF");
    std::string labelEnd = labelMenager.getLabel(labelStart, "END");
    std::string labelElse = labelMenager.getLabel(labelStart, "ELSE");
    CommandBlock conditionBlock = condition.createCommandBlock(labelElse);
    
    resultBlock.addCommandToEnd(CodeCommandStrategy::create(CodeCommandStrategy::Type::NEW_BLOCK, "IF_ELSE"));
    resultBlock.addCommandToEnd(LabelCommandStrategy::create(labelStart));
    resultBlock.append(conditionBlock);
    resultBlock.append(trueBlock);
    resultBlock.addCommandToEnd(CodeCommandStrategy::create(CodeCommandStrategy::Type::NEW_BLOCK, "TRUE_BODY"));
    resultBlock.addCommandToEnd(JumpCommandStrategy::create(labelEnd));
    resultBlock.addCommandToEnd(LabelCommandStrategy::create(labelElse));
    resultBlock.append(falseBlock);
    resultBlock.addCommandToEnd(CodeCommandStrategy::create(CodeCommandStrategy::Type::NEW_BLOCK, "FALSE_BODY"));
    resultBlock.addCommandToEnd(LabelCommandStrategy::create(labelEnd));

    return resultBlock;
}

CommandBlock CommandMenager::getCommandWhileDo(Condition condition, CommandBlock& whileBlock){
    CommandBlock resultBlock;
    std::string labelStart = labelMenager.getNextLabel("WHILE");
    std::string labelEnd = labelMenager.getLabel(labelStart, "END");
    CommandBlock conditionBlock = condition.createCommandBlock(labelEnd);

    resultBlock.addCommandToEnd(CodeCommandStrategy::create(CodeCommandStrategy::Type::NEW_BLOCK, "WHILE"));
    resultBlock.addCommandToEnd(LabelCommandStrategy::create(labelStart));
    resultBlock.append(conditionBlock);
    resultBlock.append(whileBlock);
    resultBlock.addCommandToEnd(CodeCommandStrategy::create(CodeCommandStrategy::Type::NEW_BLOCK, "BODy_WHILE"));
    resultBlock.addCommandToEnd(JumpCommandStrategy::create(labelStart));
    resultBlock.addCommandToEnd(LabelCommandStrategy::create(labelEnd));

    return resultBlock;
}

CommandBlock CommandMenager::getCommandDoWhile(Condition condition, CommandBlock& whileBlock){
    CommandBlock resultBlock;
    std::string labelStart = labelMenager.getNextLabel("WHILE");
    std::string labelEnd = labelMenager.getLabel(labelStart, "END");
    CommandBlock conditionBlock = condition.createCommandBlock(labelEnd);

    resultBlock.addCommandToEnd(CodeCommandStrategy::create(CodeCommandStrategy::Type::NEW_BLOCK, "DO_WHILE"));
    resultBlock.addCommandToEnd(LabelCommandStrategy::create(labelStart));
    resultBlock.append(whileBlock);
    resultBlock.addCommandToEnd(CodeCommandStrategy::create(CodeCommandStrategy::Type::NEW_BLOCK, "DO_WHILE_BODY"));
    resultBlock.append(conditionBlock);
    resultBlock.addCommandToEnd(JumpCommandStrategy::create(labelStart));
    resultBlock.addCommandToEnd(LabelCommandStrategy::create(labelEnd));

    return resultBlock;
}

CommandBlock CommandMenager::getCommandFor(VariablePointer iterator, VariablePointer counter, VariablePointer fromVariable, VariablePointer endVariable, CommandBlock forBlock){
    CommandBlock resultBlock;
    std::string labelStart = labelMenager.getNextLabel("FOR");
    std::string labelEnd = labelMenager.getLabel(labelStart, "END");
    VariablePointer tmpVariable = make_shared<TmpVariable>("USED");
    
    resultBlock.addCommandToEnd(AssignCommandStrategy::create(iterator, fromVariable));
    resultBlock.addCommandToEnd(AssignCommandStrategy::create(counter, endVariable));
    resultBlock.addCommandToEnd(IncDecCommandStrategy::create(IncDecCommandStrategy::Type::INC, counter));
    resultBlock.addCommandToEnd(CodeCommandStrategy::create(CodeCommandStrategy::Type::NEW_BLOCK, "FOR"));
    resultBlock.addCommandToEnd(LabelCommandStrategy::create(labelStart));
    resultBlock.addCommandToEnd(SubtractionCommandStrategy::create(tmpVariable, counter, iterator));
    resultBlock.addCommandToEnd(JumpConditionCommandStrategy::create(JumpConditionCommandStrategy::Type::JZERO, tmpVariable, labelEnd));

    resultBlock.append(forBlock);

    resultBlock.addCommandToEnd(IncDecCommandStrategy::create(IncDecCommandStrategy::Type::INC, iterator));
    resultBlock.addCommandToEnd(CodeCommandStrategy::create(CodeCommandStrategy::Type::NEW_BLOCK, "FOR_END"));

    resultBlock.addCommandToEnd(JumpCommandStrategy::create(labelStart));
    resultBlock.addCommandToEnd(LabelCommandStrategy::create(labelEnd));

    return resultBlock;
}

CommandBlock CommandMenager::getCommandForDown(VariablePointer iterator, VariablePointer counter, VariablePointer fromVariable, VariablePointer endVariable, CommandBlock forBlock){
    CommandBlock resultBlock;
    std::string labelStart = labelMenager.getNextLabel("FOR_DOWN");
    std::string labelEnd = labelMenager.getLabel(labelStart, "END");
    VariablePointer tmpVariable = make_shared<TmpVariable>("USED");
    
    resultBlock.addCommandToEnd(AssignCommandStrategy::create(iterator, fromVariable));
    resultBlock.addCommandToEnd(AssignCommandStrategy::create(counter, endVariable));
    resultBlock.addCommandToEnd(IncDecCommandStrategy::create(IncDecCommandStrategy::Type::INC, iterator));
    resultBlock.addCommandToEnd(CodeCommandStrategy::create(CodeCommandStrategy::Type::NEW_BLOCK, "FOR_DOWN"));
    resultBlock.addCommandToEnd(LabelCommandStrategy::create(labelStart));

    resultBlock.addCommandToEnd(SubtractionCommandStrategy::create(tmpVariable, iterator, counter));
    resultBlock.addCommandToEnd(JumpConditionCommandStrategy::create(JumpConditionCommandStrategy::Type::JZERO, tmpVariable, labelEnd));
    resultBlock.addCommandToEnd(IncDecCommandStrategy::create(IncDecCommandStrategy::Type::DEC, iterator));

    resultBlock.append(forBlock);
    resultBlock.addCommandToEnd(CodeCommandStrategy::create(CodeCommandStrategy::Type::NEW_BLOCK, "FOR_END"));
    resultBlock.addCommandToEnd(JumpCommandStrategy::create(labelStart));
    resultBlock.addCommandToEnd(LabelCommandStrategy::create(labelEnd));

    return resultBlock;
}
