// eJydkMtqwzAQRdGvhK5tOY_02eOckNtSPNGAnXQbhKI7wQ8pIriN9feUEWigthTIbzUhzz9WVonHIkQhFwfcj1tCc91BShG81QxPHcZUW1F3SeIAsH6ZZPUtNWG_0MNnGZYJ6EXKXyKTPDe7zGlUzqeRQki33QX5zz5EeBSmpmYh1ipXfXKeQVzxnujTTbYFguLkG3_176pYfOCZwWb95l_0FMk6etVyMEUJcfE8n_0qys8K74HTwhnjFx_0XRPXLPvKWuVEBJK8mxZZ07cKilICV1BQFJ4dCA5x6JIqjjHUUeOnFoibKHtR1G9wajhtnLVS8Vb1NmsyKNfYERExzUA0b5NvX9_1ySEGIK71xFt439j6hxeBVApGe8Kvh1dIrB_1YF11Y_1JfmH_0HiloL8xABy2ipYuUX6JOALeID4x6uBh




#include "./arithmeticExpressionStream.h"
using namespace SPL::_Operator;

#include <SPL/Runtime/Function/SPLFunctions.h>
#include <SPL/Runtime/Operator/Port/Punctuation.h>

#include <string>

#define MY_OPERATOR_SCOPE SPL::_Operator
#define MY_BASE_OPERATOR arithmeticExpressionStream_Base
#define MY_OPERATOR arithmeticExpressionStream$OP


#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fstream>
#include <signal.h>

#include <streams_boost/iostreams/stream.hpp>
#include <streams_boost/iostreams/filtering_streambuf.hpp>
#include <streams_boost/iostreams/device/file_descriptor.hpp>


#include <SPL/Runtime/Common/ApplicationRuntimeMessage.h>
#include <SPL/Toolkit/IOHelper.h>
#include <SPL/Toolkit/RuntimeException.h>

#include <SPL/Runtime/Operator/OperatorMetrics.h>
#include <SPL/Runtime/Utility/LogTraceMessage.h>

using namespace std;
using namespace streams_boost::iostreams;

#define DEV_NULL "/dev/null"


// defines for error checking conditions
#define CHECK_FAIL      \
    if (failedRead)                                   \
        _numInvalidTuples.incrementValueNoLock()

    #define DO_ERROR(msg)                             \
        do { _numInvalidTuples.incrementValueNoLock();   \
          const FormattableMessage& $msg = msg;       \
          SPLTRACEMSG (L_ERROR, $msg, SPL_OPER_DBG);  \
          THROW (SPLRuntimeFileSourceOperator, $msg);} while (0)
    #define DO_ERROR_FILESOURCE(msg) DO_ERROR(msg)
    #define CHECK_ERROR(msg)                          \
        if (fs.fail() && !getPE().getShutdownRequested()) \
            DO_ERROR(msg)


MY_OPERATOR_SCOPE::MY_OPERATOR::MY_OPERATOR()
    : MY_BASE_OPERATOR(), _fd(-1),
         
         
        
        
        
           _firstTime(true),
        
        
        _numFilesOpenedMetric(getContext().getMetrics().getCustomMetricByName("nFilesOpened")),
        _numInvalidTuples(getContext().getMetrics().getCustomMetricByName("nInvalidTuples"))
{
    _numFilesOpenedMetric.setValueNoLock(0);
    _numInvalidTuples.setValueNoLock(0);
}

void MY_OPERATOR_SCOPE::MY_OPERATOR::prepareToShutdown()
{
    if (_fd >= 0) {
        ::close(_fd);
        _fd = -1;
    }
}

void MY_OPERATOR_SCOPE::MY_OPERATOR::initialize()
{
    
}



void MY_OPERATOR_SCOPE::MY_OPERATOR::punctAndStatus(const string& pathName)
{

    submit (Punctuation::WindowMarker, 0);


}

void MY_OPERATOR_SCOPE::MY_OPERATOR::processOneFile (const string& pathName)
{
    SPL::BeJwrMSw2MkgsyizJyE0tyUx2rSgoSi0uzszPAwB5qAnV tuple$;
    
    namespace bf = streams_boost::filesystem;
    SPLAPPTRC(L_DEBUG, "Using '" << pathName << "' as the workload file...", SPL_OPER_DBG);

    int32_t fd = ::open (pathName.c_str(), O_RDONLY | O_LARGEFILE);
    if (fd < 0) {
        
        
        const FormattableMessage& m = 
                  SPL_APPLICATION_RUNTIME_FAILED_OPEN_INPUT_FILE(
                      pathName, RuntimeUtility::getErrorNoStr());
        SPLLOGMSG(L_ERROR, m, SPL_OPER_DBG);
        SPLTRACEMSG(L_ERROR, m, SPL_OPER_DBG);
        THROW (SPLRuntimeFileSourceOperator, m);
    }
    
        file_descriptor_source fd_src (fd, true);
    
    _numFilesOpenedMetric.incrementValueNoLock();
    filtering_streambuf<input> filt_str;
    
    
    filt_str.push (fd_src);
    
        istream fs (&filt_str);
    
    fs.imbue(locale::classic());

    _fd = fd;
    _tupleNumber = 0; 
    





bool failedRead = false;
while(!getPE().getShutdownRequested() && !fs.eof()) {
    _tupleNumber++;
    if (SPL::safePeek(fs) == EOF) break;
    bool doSubmit = true;
    try {
        
            SPL::rstring& t = tuple$.get_arithmeticExpression();
            std::getline (fs, t, '\n');
            
            if (fs.fail() || (fs.eof() && t.empty())) break;
        



    } catch (const SPLRuntimeException& e) {
        // Add the filename & tuple number
        DO_ERROR_FILESOURCE(
            SPL_APPLICATION_RUNTIME_FILE_SOURCE_SINK_FILENAME_TUPLE(_tupleNumber, pathName, e.getExplanation()));

    } catch (const std::exception& e) {
        DO_ERROR(SPL_APPLICATION_RUNTIME_EXCEPTION(e.what()));
        _numInvalidTuples.incrementValueNoLock();
        doSubmit = false;
    } catch (...) {
        DO_ERROR(SPL_APPLICATION_RUNTIME_UNKNOWN_EXCEPTION);
        _numInvalidTuples.incrementValueNoLock();
        doSubmit = false;
    }
    if (doSubmit)
        submit (tuple$, 0);
}

    if (_fd < 0) {
        // We closed it already.  Prevent an error message
        int newFd = ::open (DEV_NULL, O_RDONLY);
        ::dup2 (newFd, _fd);
        ::close(newFd);
    }
    _fd = -1; // no longer using this



    punctAndStatus(pathName);
}


void MY_OPERATOR_SCOPE::MY_OPERATOR::process (Tuple const& tuple, uint32_t port)
{
    AutoPortMutex am(_mutex, *this);
    const SPL::BeJwrMSw2Mk3LzEkNzyzJcK0oKEotLs7MzwvJD0gsKk4FAK5VAuq& t = static_cast<const SPL::BeJwrMSw2Mk3LzEkNzyzJcK0oKEotLs7MzwvJD0gsKk4FAK5VAuq&>(tuple);
    if (_firstTime) {
        _firstTime = false;
        initialize();
    }
    
    processOneFile (t.get_fileWithExpressionToParse());
}


static SPL::Operator * initer() { return new MY_OPERATOR_SCOPE::MY_OPERATOR(); }
bool MY_BASE_OPERATOR::globalInit_ = MY_BASE_OPERATOR::globalIniter();
bool MY_BASE_OPERATOR::globalIniter() {
    instantiators_.insert(std::make_pair("arithmeticExpressionStream",&initer));
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
    param$format$0 = "line";
    addParameterValue ("format", SPL::ConstValueHandle(param$format$0));
    (void) getParameters(); // ensure thread safety by initializing here
    $oportBitset = OPortBitsetType(std::string("01"));
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

void MY_BASE_OPERATOR::tupleLogic(Tuple const & tuple, uint32_t port) {
}


void MY_BASE_OPERATOR::processRaw(Tuple const & tuple, uint32_t port) {
    tupleLogic (tuple, port);
    static_cast<MY_OPERATOR_SCOPE::MY_OPERATOR*>(this)->MY_OPERATOR::process(tuple, port);
}


void MY_BASE_OPERATOR::punctLogic(Punctuation const & punct, uint32_t port) {
}

void MY_BASE_OPERATOR::processRaw(Punctuation const & punct, uint32_t port) {
    punctLogic (punct, port);
    
    if (punct == Punctuation::FinalMarker) {
        process(punct, port);
        bool forward = false;
        {
            AutoPortMutex $apm($fpMutex, *this);
            $oportBitset.reset(port);
            if ($oportBitset.none()) {
                $oportBitset.set(1);
                forward=true;
            }
        }
        if(forward)
            submit(punct, 0);
        return;
    }
    
    process(punct, port);
}




