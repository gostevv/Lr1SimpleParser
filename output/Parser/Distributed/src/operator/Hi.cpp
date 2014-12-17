// eJx9j0GLwkAMhclfEc_0dmepeequgsovCgnpeogYdbGeGJKW4v36HqoW9SE55JO99T1JTdOobr_1eqWhCeYgA7jINJURi9JzIL_0up5u_0vLX2t1c_1vY7vtDvV7Pl7UrrpN8W0I2mFrYfW_0qqvNBZyUMkntILMo_0XADAXGNLJq_0EreC59cH0kW_0S8EQmIQvxT8POnFERQgyUObwSo_1oYBNy_1CPeMrTXbHzulFRMN6BZiijwivSkAHjg_1tCSCF4IXqavlc4wbxUcn_0wfOAl23


#include "./Hi.h"
using namespace SPL::_Operator;

#include <SPL/Runtime/Function/SPLFunctions.h>
#include <SPL/Runtime/Operator/Port/Punctuation.h>


#define MY_OPERATOR_SCOPE SPL::_Operator
#define MY_BASE_OPERATOR Hi_Base
#define MY_OPERATOR Hi$OP


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
    instantiators_.insert(std::make_pair("Hi",&initer));
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




