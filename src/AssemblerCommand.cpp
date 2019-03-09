#include "AssemblerCommand.hpp"

AssemblerCommand::AssemblerCommand(AssemblerInstruction instruction, RegisterType firstRegister, RegisterType seccondRegister){
    this->instruction = instruction;
    this->firstRegister = firstRegister;
    this->secondRegister = seccondRegister;
    this->label = "EMPTY";
    jumpNumber = 0;
}

AssemblerCommand::AssemblerCommand(AssemblerInstruction instruction, RegisterType firstRegister, std::string label){
    this->instruction = instruction;
    this->firstRegister = firstRegister;
    this->secondRegister = RegisterType::A;
    this->label = label;
    jumpNumber = 0;
}

AssemblerCommand::AssemblerCommand(AssemblerInstruction instruction, RegisterType firstRegister, long long num){
    this->instruction = instruction;
    this->firstRegister = firstRegister;
    this->secondRegister = RegisterType::A;
    this->label = "EMPTY";
    jumpNumber = num;
}

AssemblerCommand::AssemblerCommand(AssemblerInstruction instruction, std::string l){
    this->instruction = instruction;
    this->firstRegister = RegisterType::A;
    this->secondRegister = RegisterType::A;
    this->label = l;
    jumpNumber = 0;
}

AssemblerCommand::AssemblerCommand(AssemblerInstruction instruction, long long num){
    this->instruction = instruction;
    this->firstRegister = RegisterType::A;
    this->secondRegister = RegisterType::A;
    this->label = "EMPTY";
    jumpNumber = num;
}

AssemblerCommand::AssemblerCommand(AssemblerInstruction instruction, RegisterType firstRegister){
    this->instruction = instruction;
    this->firstRegister = firstRegister;
    this->secondRegister = RegisterType::A;
    this->label = "EMPTY";
    jumpNumber = 0;
}

std::ostream& operator<<(std::ostream &strm, const AssemblerCommand &command){
    switch(command.instruction){
       case AssemblerInstruction::Get : strm << "GET " << command.firstRegister; break;
       case AssemblerInstruction::Put : strm << "PUT " << command.firstRegister; break;
       case AssemblerInstruction::Load : strm << "LOAD " << command.firstRegister; break;
       case AssemblerInstruction::Store : strm << "STORE " << command.firstRegister; break;
       case AssemblerInstruction::Copy : strm << "COPY " << command.firstRegister << " " << command.secondRegister; break;
       case AssemblerInstruction::Add : strm << "ADD " << command.firstRegister << " " << command.secondRegister; break;
       case AssemblerInstruction::Sub : strm << "SUB " << command.firstRegister << " " << command.secondRegister; break;
       case AssemblerInstruction::Half : strm << "HALF " << command.firstRegister; break;
       case AssemblerInstruction::Inc : strm << "INC " << command.firstRegister; break;
       case AssemblerInstruction::Dec : strm << "DEC " << command.firstRegister; break;
       case AssemblerInstruction::Jump : strm << "JUMP "  << command.jumpNumber; break;
       case AssemblerInstruction::Jzero : strm << "JZERO " << command.firstRegister << " "  << command.jumpNumber; break;
       case AssemblerInstruction::Jodd : strm << "JODD " << command.firstRegister << " " << command.jumpNumber; break;
       case AssemblerInstruction::Halt : strm << "HALT "; break;
       case AssemblerInstruction::Label : strm << "LABEL " << command.label; break;
       case AssemblerInstruction::Com : strm  << command.label; break;
       default: break;
    }
    return strm;
};

std::string AssemblerCommand::getLabel(){
    return label;
}

void AssemblerCommand::setJumpNumber(long long jumpNumber){
    this->jumpNumber=jumpNumber;
}

AssemblerInstruction AssemblerCommand::getInstruction(){
    return instruction;
}