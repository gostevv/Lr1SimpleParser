// eJydkMtqwzAQRdGvhK5tOY_02eOckNtSPNGAnXQbhKI7wQ8pIriN9feUEWigthTIbzUhzz9WVonHIkQhFwfcj1tCc91BShG81QxPHcZUW1F3SeIAsH6ZZPUtNWG_0MNnGZYJ6EXKXyKTPDe7zGlUzqeRQki33QX5zz5EeBSmpmYh1ipXfXKeQVzxnujTTbYFguLkG3_176pYfOCZwWb95l_0FMk6etVyMEUJcfE8n_0qys8K74HTwhnjFx_0XRPXLPvKWuVEBJK8mxZZ07cKilICV1BQFJ4dCA5x6JIqjjHUUeOnFoibKHtR1G9wajhtnLVS8Vb1NmsyKNfYERExzUA0b5NvX9_1ySEGIK71xFt439j6hxeBVApGe8Kvh1dIrB_1YF11Y_1JfmH_0HiloL8xABy2ipYuUX6JOALeID4x6uBh



#ifndef SPL_OPER_INSTANCE_ARITHMETICEXPRESSIONSTREAM_H_
#define SPL_OPER_INSTANCE_ARITHMETICEXPRESSIONSTREAM_H_

namespace streams_boost { namespace iostreams { class file_descriptor_source; } }
#include <SPL/Runtime/Common/Metric.h>
#include <streams_boost/filesystem/path.hpp>
#include <SPL/Runtime/Operator/Operator.h>
#include <SPL/Runtime/Operator/ParameterValue.h>
#include <SPL/Runtime/Operator/OperatorContext.h>
#include <SPL/Runtime/Operator/Port/AutoPortMutex.h>
#include <SPL/Runtime/ProcessingElement/PE.h>
#include <SPL/Runtime/Type/SPLType.h>
#include <SPL/Runtime/Utility/CV.h>
using namespace UTILS_NAMESPACE;

#include "../type/BeJwrMSw2Mk3LzEkNzyzJcK0oKEotLs7MzwvJD0gsKk4FAK5VAuq.h"
#include "../type/BeJwrMSw2MkgsyizJyE0tyUx2rSgoSi0uzszPAwB5qAnV.h"
#include "../type/BeJyrNI03Ti4uMy6pKDFOyswzTcrJT842ycnMSwUAf_1wJCo.h"

#include <bitset>

#define MY_OPERATOR arithmeticExpressionStream$OP
#define MY_BASE_OPERATOR arithmeticExpressionStream_Base
#define MY_OPERATOR_SCOPE SPL::_Operator

namespace SPL {
namespace _Operator {

class MY_BASE_OPERATOR : public Operator
{
public:
    
    typedef SPL::BeJwrMSw2Mk3LzEkNzyzJcK0oKEotLs7MzwvJD0gsKk4FAK5VAuq IPort0Type;
    typedef SPL::BeJwrMSw2MkgsyizJyE0tyUx2rSgoSi0uzszPAwB5qAnV OPort0Type;
    
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
    
    
    
    
    
protected:
    Mutex $svMutex;
    typedef std::bitset<2> OPortBitsetType;
    OPortBitsetType $oportBitset;
    Mutex $fpMutex;
    SPL::rstring param$format$0;
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
    
    
        virtual void process (Tuple const& tuple, uint32_t port);
    

    virtual void prepareToShutdown();

private:
    void initialize();
    inline void punctAndStatus(const std::string& pathName);
    void processOneFile (const std::string& pathName);
    

    int32_t _fd;
    uint64_t _tupleNumber;
    
    
    
    
    
        bool _firstTime;
        Mutex _mutex;
    
    
    Metric& _numFilesOpenedMetric;
    Metric& _numInvalidTuples;
}; 

} // namespace _Operator
} // namespace SPL

#undef MY_OPERATOR_SCOPE
#undef MY_BASE_OPERATOR
#undef MY_OPERATOR
#endif // SPL_OPER_INSTANCE_ARITHMETICEXPRESSIONSTREAM_H_


