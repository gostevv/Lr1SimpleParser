// eJxFyTEKgDAMAEDyle4OFQdXB_1dCBV2LRAyaVpII_0nsFB289Dx5cNfHl65YddKcVaCBS3iDeashByoFihApJyFZGo7m_1DkFVKjmaYGJYaMfx3T_0GEpIofv8AsykkCR


#include "BeJwzCc7My443NAuuLC5JzQ0oyi9ILSrJTC2ONzJLLMosychNLclMdq0oKEotLs7MzwsuKUpNzI03NkzLzEkNB8ojpELyAxKLilOhKgDqFCKH.h"
#include <dst-config.h>
#include <SPL/Runtime/Utility/BackoffSpinner.h>

#include <SPL/Runtime/Utility/MessageFormatter.h>

#include <streams_boost/filesystem/operations.hpp>
namespace bf = streams_boost::filesystem;


using namespace SPL;

extern int PE_Version;

#define MYPE BeJwzCc7My443NAuuLC5JzQ0oyi9ILSrJTC2ONzJLLMosychNLclMdq0oKEotLs7MzwsuKUpNzI03NkzLzEkNB8ojpELyAxKLilOhKgDqFCKH


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

