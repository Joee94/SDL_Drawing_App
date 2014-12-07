#include "SaveFile.h"

SaveFile::SaveFile()
{
}

SaveFile::~SaveFile()
{
}

int SaveFile::Save(std::string fileName)
{
   FILE *f;
   errno_t err;

   if ((err = fopen_s(&f, "savedata.txt", "w")) != 0)
   {
      return 0;
   }
}
