// eJwzYHQsLclnNGYMzszLZkwsyizJyE0tyUx2rSgoSi0uzszPCy4pSk3MZUzLzEkNB8oiJELyAxKLilMh8gCd1Rrz


#include "BeJwzCc7My443MkssyizJyE0tyUx2rSgoSi0uzszPCy4pSk3MjTc2TMvMSQ0HyiOkQvIDEouKU6EqAKN5BsP.h"
#include <dst-config.h>
#include <SPL/Runtime/Utility/BackoffSpinner.h>

#include <SPL/Runtime/Utility/MessageFormatter.h>

#include <streams_boost/filesystem/operations.hpp>
namespace bf = streams_boost::filesystem;


using namespace SPL;

extern int PE_Version;

#define MYPE BeJwzCc7My443MkssyizJyE0tyUx2rSgoSi0uzszPCy4pSk3MjTc2TMvMSQ0HyiOkQvIDEouKU6EqAKN5BsP



MYPE::MYPE(bool isStandalone/*=false*/) 
    : SPL::PE(isStandalone, NULL)
{
   PE_Version = 3100;
   BackoffSpinner::setYieldBehaviour(BackoffSpinner::Auto);
}


void MYPE::registerResources(const std::string & applicationDir, const std::string & streamsInstallDir)
{
    SPL::RuntimeMessageFormatter & formatter = SPL::RuntimeMessageFormatter::instance(); 
    { 
        bf::path p(streamsInstallDir);
        p /= "/toolkits/com.ibm.streams.bigdata";
        formatter.registerToolkit("com.ibm.streams.bigdata", p.string()); 
    } 
    { 
        bf::path p(streamsInstallDir);
        p /= "/toolkits/com.ibm.streams.cep";
        formatter.registerToolkit("com.ibm.streams.cep", p.string()); 
    } 
    { 
        bf::path p(streamsInstallDir);
        p /= "/toolkits/com.ibm.streams.db";
        formatter.registerToolkit("com.ibm.streams.db", p.string()); 
    } 
    { 
        bf::path p(streamsInstallDir);
        p /= "/toolkits/com.ibm.streams.financial";
        formatter.registerToolkit("com.ibm.streams.financial", p.string()); 
    } 
    { 
        bf::path p(streamsInstallDir);
        p /= "/toolkits/com.ibm.streams.inet";
        formatter.registerToolkit("com.ibm.streams.inet", p.string()); 
    } 
    { 
        bf::path p(streamsInstallDir);
        p /= "/toolkits/com.ibm.streams.messaging";
        formatter.registerToolkit("com.ibm.streams.messaging", p.string()); 
    } 
    { 
        bf::path p(streamsInstallDir);
        p /= "/toolkits/com.ibm.streams.mining";
        formatter.registerToolkit("com.ibm.streams.mining", p.string()); 
    } 
    { 
        bf::path p(streamsInstallDir);
        p /= "/toolkits/com.ibm.streams.timeseries";
        formatter.registerToolkit("com.ibm.streams.timeseries", p.string()); 
    } 
}


MAKE_PE(SPL::MYPE);

