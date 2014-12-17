// eJwzZDRkVNKNyK0wNLLIVWJ0LC3JZzRh9CkyDEgsKk4tYgzOzMtmTCzKLMnITS3JTHatKChKLS7OzM8LLilKTcxlTMvMSQ0HyiIkQvLBWiHyAJkBCE7


#include "BeJyz9CkyDEgsKk4tijcJzszLjjcySyzKLMnITS3JTHatKChKLS7OzM8LLilKTcyNNzZMy8xJDQfKI6RC8sH6oSoAyjofAD.h"
#include <dst-config.h>
#include <SPL/Runtime/Utility/BackoffSpinner.h>

#include <SPL/Runtime/Utility/MessageFormatter.h>

#include <streams_boost/filesystem/operations.hpp>
namespace bf = streams_boost::filesystem;


using namespace SPL;

extern int PE_Version;

#define MYPE BeJyz9CkyDEgsKk4tijcJzszLjjcySyzKLMnITS3JTHatKChKLS7OzM8LLilKTcyNNzZMy8xJDQfKI6RC8sH6oSoAyjofAD


#include <SPL/Runtime/Type/SPLType.h>

static std::vector<std::string> * javaVMArgs() {
    std::vector<std::string> * result = new std::vector<std::string>();

    result->push_back("-Xmx128m"); 
    return result;
}


MYPE::MYPE(bool isStandalone/*=false*/) 
    : SPL::PE(isStandalone, javaVMArgs())
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

