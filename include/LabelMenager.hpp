#ifndef __LABELMENAGER_HH__
#define __LABELMENAGER_HH__

#include <string>

class LabelMenager{
private:
   long long labelIndex;

public:
   LabelMenager();
   ~LabelMenager() = default;

   std::string getNextLabel(std::string infix);
   std::string getLabel(std::string label, std::string suffix);

};

#endif