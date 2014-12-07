#pragma once
#include <string>
#include <iostream>
class SaveFile
{
public:
   SaveFile();
   ~SaveFile();
   int Save(std::string fileName);
};

