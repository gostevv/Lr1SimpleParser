// eJx9j1FrwkAQhNl_1UsTnXE5bsEGEBBRatC217_0WMiy4md8fuptb_0_0oazBEqh7Nvs7M43EpusU2pIL0VRoauDhzyNhVGWGb1ENBU_0nnlTf31u5P5pvb17flvOVmX1sStfb7PjqDdPoP8wzmH7si6KjrxOJ5Ake5UaEp0Py9nNAgDMMbRoRBldK27fkjfnwCeJrkYTHQvye8PW7J068MFjj0SK7JSCF7C_1wuwPQKnKtOsUV4yYWuQQYuAB7r8uQMD9RYsi7oCQoBPvAmwpD0Pm3zbXeJt_1A8YQGVi

#include <SPL/Runtime/Utility/Mutex.h>

#ifndef SPL_OPER_INSTANCE_EXPRESSION_H_
#define SPL_OPER_INSTANCE_EXPRESSION_H_

#include <SPL/Runtime/Operator/Operator.h>
#include <SPL/Runtime/Operator/ParameterValue.h>
#include <SPL/Runtime/Operator/OperatorContext.h>
#include <SPL/Runtime/Operator/Port/AutoPortMutex.h>
#include <SPL/Runtime/ProcessingElement/PE.h>
#include <SPL/Runtime/Type/SPLType.h>
#include <SPL/Runtime/Utility/CV.h>
using namespace UTILS_NAMESPACE;

#include "../type/BeJwrMczxMs9NLS5OTE8FABvbAR4.h"


#define MY_OPERATOR Expression$OP
#define MY_BASE_OPERATOR Expression_Base
#define MY_OPERATOR_SCOPE SPL::_Operator

namespace SPL {
namespace _Operator {

class MY_BASE_OPERATOR : public Operator
{
public:
    
    typedef SPL::BeJwrMczxMs9NLS5OTE8FABvbAR4 OPort0Type;
    
    MY_BASE_OPERATOR();
    
    ~MY_BASE_OPERATOR();
    
    
    
    
    SPL::uint32 lit$0;
    SPL::list<SPL::uint8 > lit$1;
    
    
protected:
    Mutex $svMutex;
    void checkpointStateVariables(NetworkByteBuffer & opstate) const {
    }
    void restoreStateVariables(NetworkByteBuffer & opstate) {
    }
private:
    static bool globalInit_;
    static bool globalIniter();
    ParameterMapType paramValues_;
    ParameterMapType& getParameters() { return paramValues_;}
    void addParameterValue(std::string const & param, ConstValueHandle const& value)
    {
        ParameterMapType::iterator it = paramValues_.find(param);
        if (it == paramValues_.end())
            it = paramValues_.insert (std::make_pair (param, ParameterValueListType())).first;
        it->second.push_back(&ParameterValue::create(value));
    }
    void addParameterValue(std::string const & param)
    {
        ParameterMapType::iterator it = paramValues_.find(param);
        if (it == paramValues_.end())
            it = paramValues_.insert (std::make_pair (param, ParameterValueListType())).first;
        it->second.push_back(&ParameterValue::create());
    }
};


class MY_OPERATOR : public MY_BASE_OPERATOR 
{
public:
   MY_OPERATOR();
  
   void allPortsReady();
   void process(uint32_t index);
   virtual void getCheckpoint(NetworkByteBuffer & opstate);
   virtual void restoreCheckpoint(NetworkByteBuffer & opstate);
private:
   SPL::BeJwrMczxMs9NLS5OTE8FABvbAR4 _tuple;
   SPL::uint32 _iters;
   Mutex _mutex;
   uint64_t _iterationCount;
   uint64_t IterationCount() const { return _iterationCount;}
}; 

} // namespace _Operator
} // namespace SPL

#undef MY_OPERATOR_SCOPE
#undef MY_BASE_OPERATOR
#undef MY_OPERATOR
#endif // SPL_OPER_INSTANCE_EXPRESSION_H_


