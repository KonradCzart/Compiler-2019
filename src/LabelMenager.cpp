#include "LabelMenager.hpp"
#include <sstream>

LabelMenager::LabelMenager(){
    labelIndex = 1;
}

std::string LabelMenager::getNextLabel(std::string suffix){
   std::stringstream l;
   l << "LABEL_";
   l << labelIndex << "_";
   labelIndex++;
   l << suffix;

   return l.str();
}

std::string LabelMenager::getLabel(std::string label, std::string suffix){
   std::stringstream l;
   l << label << "_" << suffix;

   return l.str();
}