// eJx9j1FrwkAQhNl_1UsTnXE5bsEGEBBRatC217_0WMiy4md8fuptb_0_0oazBEqh7Nvs7M43EpusU2pIL0VRoauDhzyNhVGWGb1ENBU_0nnlTf31u5P5pvb17flvOVmX1sStfb7PjqDdPoP8wzmH7si6KjrxOJ5Ake5UaEp0Py9nNAgDMMbRoRBldK27fkjfnwCeJrkYTHQvye8PW7J068MFjj0SK7JSCF7C_1wuwPQKnKtOsUV4yYWuQQYuAB7r8uQMD9RYsi7oCQoBPvAmwpD0Pm3zbXeJt_1A8YQGVi


#include "./Expression.h"
using namespace SPL::_Operator;

#include <SPL/Runtime/Function/SPLFunctions.h>
#include <SPL/Runtime/Operator/Port/Punctuation.h>


#define MY_OPERATOR_SCOPE SPL::_Operator
#define MY_BASE_OPERATOR Expression_Base
#define MY_OPERATOR Expression$OP


MY_OPERATOR_SCOPE::MY_OPERATOR::MY_OPERATOR()
: _iterationCount(0)
{
    _tuple.clear();
    
        _iters = lit$0;
    
    _tuple.set_message(lit$1); 
}

void MY_OPERATOR_SCOPE::MY_OPERATOR::allPortsReady()
{
    createThreads (1);
}

void MY_OPERATOR_SCOPE::MY_OPERATOR::process(uint32_t) 
{
    SPLAPPTRC(L_DEBUG, "Beacon startup...", SPL_OPER_DBG);
    ProcessingElement& pe = getPE();
    
    
    while(!pe.getShutdownRequested()) {
        {
            
                AutoMutex am (_mutex);
            
            
                if (_iters == 0)
                    break;
                _iters--;
            
            
        }
        submit (_tuple, 0);
        
        
    }
    
        if (_iters == 0) { // only submit if we have an explicit iterations parameter.
            submit(Punctuation::WindowMarker, 0);
            submit(Punctuation::FinalMarker, 0);
        }
    
    SPLAPPTRC(L_DEBUG, "Beacon exiting...", SPL_OPER_DBG);
}

void MY_OPERATOR_SCOPE::MY_OPERATOR::getCheckpoint(NetworkByteBuffer & opstate)
{
    AutoMutex am (_mutex);
    
    
        opstate.addUInt32(_iters);
    
    
    
}

void MY_OPERATOR_SCOPE::MY_OPERATOR::restoreCheckpoint(NetworkByteBuffer & opstate)
{
    AutoMutex am (_mutex);
    
    
        _iters = opstate.getUInt32();
    
    
    
}



static SPL::Operator * initer() { return new MY_OPERATOR_SCOPE::MY_OPERATOR(); }
bool MY_BASE_OPERATOR::globalInit_ = MY_BASE_OPERATOR::globalIniter();
bool MY_BASE_OPERATOR::globalIniter() {
    instantiators_.insert(std::make_pair("Expression",&initer));
    return true;
}

template<class T> static void initRTC (SPL::Operator& o, T& v, const char * n) {
    SPL::ValueHandle vh = v;
    o.getContext().getRuntimeConstantValue(vh, n);
}

MY_BASE_OPERATOR::MY_BASE_OPERATOR()
 : Operator() {
    PE & pe = PE::instance();
    uint32_t index = getIndex();
    initRTC(*this, lit$0, "lit$0");
    initRTC(*this, lit$1, "lit$1");
    addParameterValue ("iterations", SPL::ConstValueHandle(lit$0));
    (void) getParameters(); // ensure thread safety by initializing here
}
MY_BASE_OPERATOR::~MY_BASE_OPERATOR()
{
    for (ParameterMapType::const_iterator it = paramValues_.begin(); it != paramValues_.end(); it++) {
        const ParameterValueListType& pvl = it->second;
        for (ParameterValueListType::const_iterator it2 = pvl.begin(); it2 != pvl.end(); it2++) {
            delete *it2;
        }
    }
}




