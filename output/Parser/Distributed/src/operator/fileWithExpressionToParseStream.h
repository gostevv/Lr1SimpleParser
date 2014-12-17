// eJydUcFOwkAQzfxK40E9dFtATXrDAAcKhgSiFxKztgNsut1dZwdL_0_1UWQRIaT2ZO8zLz5r033ulQ5tIxUpKMFGHGluplJg1EPxVDEIaCa4fiGacVzZdVb170Z824eGnqZpqlkU3Hlmf_0ad5UX9NRtPVpMZgM04fX4f4z3AUtSR_004psIlotZkpBnUmYLP1h8wjbaSn4cnLBeBwOxsyWKdg1l6WVeKiMqS4V3MkPhJHmkd02xyCVLMNYgDCD_19QLx9dn4rGXIbf_0xZ5wQIniN6FaqROgois8yr8ed5DYx0_0W_0dngbhPfrdcgHDu46_08ooHqGW9d_1nep3x4xsisM7SJcX_1PAMUUMu0URrfFO_1GB0fovbJmZRfHFOHiI_1oGPcerBP



#include <SPL/Runtime/Common/Metric.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


#ifndef SPL_OPER_INSTANCE_FILEWITHEXPRESSIONTOPARSESTREAM_H_
#define SPL_OPER_INSTANCE_FILEWITHEXPRESSIONTOPARSESTREAM_H_

#include <SPL/Runtime/Common/Metric.h>
#include <SPL/Runtime/Operator/Operator.h>
#include <SPL/Runtime/Operator/ParameterValue.h>
#include <SPL/Runtime/Operator/OperatorContext.h>
#include <SPL/Runtime/Operator/Port/AutoPortMutex.h>
#include <SPL/Runtime/ProcessingElement/PE.h>
#include <SPL/Runtime/Type/SPLType.h>
#include <SPL/Runtime/Utility/CV.h>
using namespace UTILS_NAMESPACE;

#include "../type/BeJwrMSw2Mk3LzEkNzyzJcK0oKEotLs7MzwvJD0gsKk4FAK5VAuq.h"


#define MY_OPERATOR fileWithExpressionToParseStream$OP
#define MY_BASE_OPERATOR fileWithExpressionToParseStream_Base
#define MY_OPERATOR_SCOPE SPL::_Operator

namespace SPL {
namespace _Operator {

class MY_BASE_OPERATOR : public Operator
{
public:
    
    typedef SPL::BeJwrMSw2Mk3LzEkNzyzJcK0oKEotLs7MzwvJD0gsKk4FAK5VAuq OPort0Type;
    
    MY_BASE_OPERATOR();
    
    ~MY_BASE_OPERATOR();
    
    
    
    
    SPL::rstring lit$0;
    SPL::float64 lit$1;
    SPL::float64 lit$2;
    
    
protected:
    Mutex $svMutex;
    SPL::rstring param$pattern$0;
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
  
   virtual void process(uint32_t index);

   virtual void allPortsReady();
   virtual void getCheckpoint(NetworkByteBuffer & opstate);
   virtual void restoreCheckpoint(NetworkByteBuffer & opstate);
private:
   typedef std::tr1::unordered_map<std::string, time_t> FileInfoMapType;
   FileInfoMapType _fileCreationTimes;
   Metric &_numDirectoryScans;
   Mutex _mutex;
}; 

} // namespace _Operator
} // namespace SPL

#undef MY_OPERATOR_SCOPE
#undef MY_BASE_OPERATOR
#undef MY_OPERATOR
#endif // SPL_OPER_INSTANCE_FILEWITHEXPRESSIONTOPARSESTREAM_H_

