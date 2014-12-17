// eJwzYHQsLclnNGT0yAQAD6ECCv



#ifndef BEJWZ8SIMBWAC1QFD_H_
#define BEJWZ8SIMBWAC1QFD_H_

#include <SPL/Runtime/ProcessingElement/PE.h>

#define MYPE BeJwz8siMBwAC1QFD

namespace SPL 
{
    class MYPE : public SPL::PE
    {
    public:
        MYPE(bool isStandalone=false);

        virtual void registerResources(const std::string & applicationDir, const std::string & streamsInstallDir);

    };
} // end namespace SPL

#undef MYPE

#endif // BEJWZ8SIMBWAC1QFD_H_

