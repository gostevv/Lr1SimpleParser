// eJyVkcFOwkAQhjOv0njQS7cQvfRWCB4QFFPwaqZl0m5od9fZLaU8vQsGDAhRs6fN7vf9k3_0sqcLGyUq6Lo7HuMYXA9H_09CEIQ_0E6Q2JA45anadufrgrbye24G0WuW2z6nBY6lVGztdtZ0g4ePhL1FpbBRXJ1lRx21dP8dZGY_0WIyMDs_0gh74kW4iSGeTOGbrWKoCAESpaxL_0SlhbXNZSiVbzyhrMSRhkS_1xecU8s0SEorQjuIa_1Q2mesyUtPdKf228CD4WzvmGJeSkXBHSTOP2aNo0cm_0lJNZMbI3W_02TKoffEGKGB0tD3CmdUWoPOy4IRhqZR0qB_0s64eI84dDJ8VfPc9JoPhb1r0WBBN5vGrwIWbqyJifz0cYwWSu1gu_1gCPSVnL_0uFWqfdjlnvqvmWKMP_0wSVWNnk

#include <SPL/Toolkit/JavaOp.h>


#ifndef SPL_OPER_INSTANCE_LR1PARSER_H_
#define SPL_OPER_INSTANCE_LR1PARSER_H_

#include <SPL/Runtime/Operator/Operator.h>
#include <SPL/Runtime/Operator/ParameterValue.h>
#include <SPL/Runtime/Operator/OperatorContext.h>
#include <SPL/Runtime/Operator/Port/AutoPortMutex.h>
#include <SPL/Runtime/ProcessingElement/PE.h>
#include <SPL/Runtime/Type/SPLType.h>
#include <SPL/Runtime/Utility/CV.h>
using namespace UTILS_NAMESPACE;

#include "../type/BeJwrMSw2MkgsyizJyE0tyUx2rSgoSi0uzszPAwB5qAnV.h"
#include "../type/BeJwrMSw2MkksyizJyE0tyUx2rSgoSi0uzszPCylKTQUApTULBp.h"

#include <bitset>

#define MY_OPERATOR Lr1Parser$OP
#define MY_BASE_OPERATOR Lr1Parser_Base
#define MY_OPERATOR_SCOPE SPL::_Operator

namespace SPL {
namespace _Operator {

class MY_BASE_OPERATOR : public Operator
{
public:
    
    typedef SPL::BeJwrMSw2MkgsyizJyE0tyUx2rSgoSi0uzszPAwB5qAnV IPort0Type;
    typedef SPL::BeJwrMSw2MkksyizJyE0tyUx2rSgoSi0uzszPCylKTQUApTULBp OPort0Type;
    
    MY_BASE_OPERATOR();
    
    ~MY_BASE_OPERATOR();
    
    inline void tupleLogic(Tuple const & tuple, uint32_t port);
    void processRaw(Tuple const & tuple, uint32_t port);
    
    inline void punctLogic(Punctuation const & punct, uint32_t port);
    void processRaw(Punctuation const & punct, uint32_t port);
    
    inline void submit(Tuple & tuple, uint32_t port)
    {
        Operator::submit(tuple, port);
    }
    inline void submit(Punctuation const & punct, uint32_t port)
    {
        Operator::submit(punct, port);
    }
    
    
    
    SPL::rstring lit$0;
    
    
protected:
    Mutex $svMutex;
    typedef std::bitset<2> OPortBitsetType;
    OPortBitsetType $oportBitset;
    Mutex $fpMutex;
    SPL::rstring param$className$0;
    SPL::rstring param$classLibrary$0;
    SPL::boolean param$generated$0;
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
  // constructor
  MY_OPERATOR();

  // destructor
  virtual ~MY_OPERATOR(); 

  // notify port readiness
  void allPortsReady(); 

  // notify termination
  void prepareToShutdown(); 

  // processing for source and threaded operators   
  void process(uint32_t idx);
    
  // tuple processing for mutating ports 
  void process(Tuple & tuple, uint32_t port);
    
  // tuple processing for non-mutating ports
  void process(Tuple const & tuple, uint32_t port);

  // punctuation processing
  void process(Punctuation const & punct, uint32_t port);
private:
  // members
  
  /** How we invoke actions on the Java Operator implementation */
  SPL::JNI::JNIBridgeInvoker* _bi;
  
  /* The instance of the JNIBridge used to wrap the Java Operator implementation */
  jobject _bridge;

  typedef void (*FP)(SPL::JNI::JNIBridgeInvoker&, jobject, NativeByteBuffer &, uint32_t);
  FP _fp;
  
  bool hasTupleLogic;
  
public:
    
  // handle byte buffers being send as is
  virtual void processRaw(NativeByteBuffer & buffer, uint32_t port)
  {
     (*_fp)(*_bi, _bridge, buffer, port);
  }
  
  //Java operators handle byte buffers directly
  virtual bool sendRawBufferData() { return !hasTupleLogic; }
}; 

} // namespace _Operator
} // namespace SPL

#undef MY_OPERATOR_SCOPE
#undef MY_BASE_OPERATOR
#undef MY_OPERATOR
#endif // SPL_OPER_INSTANCE_LR1PARSER_H_


