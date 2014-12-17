// eJwzYHQsLclnNGL0yGQMzszLBgAg6ARG



#ifndef BEJWZ8SIMNWNOZMUOBWARYQNR_H_
#define BEJWZ8SIMNWNOZMUOBWARYQNR_H_

#include <SPL/Runtime/ProcessingElement/PE.h>

#define MYPE BeJwz8siMNwnOzMuOBwARYQNr

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

#endif // BEJWZ8SIMNWNOZMUOBWARYQNR_H_

