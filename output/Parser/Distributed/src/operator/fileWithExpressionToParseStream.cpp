// eJydUcFOwkAQzfxK40E9dFtATXrDAAcKhgSiFxKztgNsut1dZwdL_0_1UWQRIaT2ZO8zLz5r033ulQ5tIxUpKMFGHGluplJg1EPxVDEIaCa4fiGacVzZdVb170Z824eGnqZpqlkU3Hlmf_0ad5UX9NRtPVpMZgM04fX4f4z3AUtSR_004psIlotZkpBnUmYLP1h8wjbaSn4cnLBeBwOxsyWKdg1l6WVeKiMqS4V3MkPhJHmkd02xyCVLMNYgDCD_19QLx9dn4rGXIbf_0xZ5wQIniN6FaqROgois8yr8ed5DYx0_0W_0dngbhPfrdcgHDu46_08ooHqGW9d_1nep3x4xsisM7SJcX_1PAMUUMu0URrfFO_1GB0fovbJmZRfHFOHiI_1oGPcerBP




#include "./fileWithExpressionToParseStream.h"
using namespace SPL::_Operator;

#include <SPL/Runtime/Function/SPLFunctions.h>
#include <SPL/Runtime/Operator/Port/Punctuation.h>


#define MY_OPERATOR_SCOPE SPL::_Operator
#define MY_BASE_OPERATOR fileWithExpressionToParseStream_Base
#define MY_OPERATOR fileWithExpressionToParseStream$OP


#include <streams_boost/filesystem/path.hpp>
#include <streams_boost/filesystem/operations.hpp>
#include <streams_boost/filesystem/exception.hpp>
#include <SPL/Runtime/Common/ApplicationRuntimeMessage.h>
#include <SPL/Runtime/Utility/LogTraceMessage.h>
#include <SPL/Runtime/Operator/OperatorMetrics.h>
#include <SPL/Toolkit/RuntimeException.h>
#include <SPL/Toolkit/Utility.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define WARNANDTHROW(except,msg)                \
    do {                                        \
        const FormattableMessage& m = msg;      \
        SPLTRACEMSG (L_ERROR, m, SPL_FUNC_DBG); \
        THROW_STRING (except, m);               \
    } while (0)

using namespace std;
using namespace SPL;

typedef pair<string, time_t> FileInfo;

static bool sortFunction (const FileInfo& left, const FileInfo& right)
{
    
        return left.second < right.second;
    
}

MY_OPERATOR_SCOPE::MY_OPERATOR::MY_OPERATOR()
: MY_BASE_OPERATOR(),
  _numDirectoryScans (getContext().getMetrics().getCustomMetricByName("nScans"))
{
    _numDirectoryScans.setValueNoLock(0);
}
void MY_OPERATOR_SCOPE::MY_OPERATOR::allPortsReady()
{
    createThreads (1);
}

#define CLEAN_INTERVAL 10

    namespace bf = streams_boost::filesystem;
static void ensureRenameDir (const bf::path& dir)
{
    if (bf::exists (dir)) {
        if (!bf::is_directory(dir))
            WARNANDTHROW (SPLRuntimeDirectoryScanOperator,
                        SPL_APPLICATION_RUNTIME_NOT_DIR(dir.string()));
    } else {
        try {
            bf::create_directory (dir);
        } catch (...) {
            WARNANDTHROW (SPLRuntimeDirectoryScanOperator,
                        SPL_APPLICATION_RUNTIME_DIR_NOT_EXIST(dir.string()));
        }
    }
}

void MY_OPERATOR_SCOPE::MY_OPERATOR::process(uint32_t) 
{
    SPLAPPTRC(L_DEBUG, "DirectoryScan startup...", SPL_OPER_DBG);
    double lastScanStartTime;
    double scanWaitTime = lit$1;

    // Figure out input directory and open it
    string directoryName = lit$0;
    bf::path dir = directoryName;
    SPLAPPTRC(L_DEBUG, "Using '" << directoryName << "' as the directory...", SPL_OPER_DBG);

    const ProcessingElement& pe = getPE();
    bf::directory_iterator end_itr; // default construction yields past-the-end
    if (0) 
    { // Ignore any existing files at startup time
        AutoMutex am (_mutex);
        for (bf::directory_iterator itr(dir); itr != end_itr; ++itr) {
            if (bf::is_directory(*itr)) {
                continue;
            }
            string component = itr->leaf();
            SPLAPPTRC(L_DEBUG, "Ignoring file '" << component << '\'', SPL_OPER_DBG);
            rstring file = itr->string();
            // Have we seen this file before?
            struct stat fInfo;
            if (::stat (file.c_str(), &fInfo) < 0) {
                SPLAPPTRC(L_DEBUG, "'stat' of  file '" << file << "' failed: " << RuntimeUtility::getErrorNoStr(), SPL_OPER_DBG);
                continue;
            }
            if (S_ISREG(fInfo.st_mode)) {
                _fileCreationTimes.insert (FileInfo (file, fInfo.st_ctime));
            }
        }
    }
    
        pe.blockUntilShutdownRequest(lit$2);
    
    if (!bf::exists(dir))
        WARNANDTHROW (SPLRuntimeDirectoryScanOperator, SPL_APPLICATION_RUNTIME_DIR_NOT_EXIST(directoryName));
    if (!bf::is_directory(dir))
        WARNANDTHROW (SPLRuntimeDirectoryScanOperator, SPL_APPLICATION_RUNTIME_NOT_DIR(directoryName));

    


    string pattern = SPL::rstring(".*\\.txt");

    uint32_t timeToClean = CLEAN_INTERVAL;


    while (!pe.getShutdownRequested()) {
        lastScanStartTime = Functions::Time::getTimestampInSecs();
        vector<FileInfo> foundFiles;

        for (bf::directory_iterator itr(dir); itr != end_itr; ++itr) {
            if (pe.getShutdownRequested())
                break; // give up now if we are shutting down
            if (bf::is_directory(*itr))
                continue;
            string component = itr->leaf();
            SPLAPPTRC(L_DEBUG, "Found file '" << component << '\'', SPL_OPER_DBG);
            
            
                list<rstring> matchRes;
                try {
                    matchRes = Functions::String::regexMatch(component, pattern);
                } catch (SPLRuntimeInvalidArgumentException & e) {
                    WARNANDTHROW (SPLRuntimeDirectoryScanOperator, SPL_APPLICATION_RUNTIME_REGEXP_FAILED_COMPILE(pattern));
                }
                if (matchRes.empty()) {
                    SPLAPPTRC(L_DEBUG, "File '" << component << "' did not match pattern -- skipping",
                           SPL_OPER_DBG);
                    continue;
                }
            
            rstring file = itr->string();
            // Have we seen this file before?
            struct stat fInfo;
            if (::stat (file.c_str(), &fInfo) < 0) {
                SPLAPPTRC(L_DEBUG, "'stat' of  file '" << file << "' failed: "
                                << RuntimeUtility::getErrorNoStr(), SPL_OPER_DBG);
                continue;
            }
            if (!S_ISREG(fInfo.st_mode)) {
                SPLAPPTRC(L_DEBUG, "Skipping non-regular file '" << file << '\'', SPL_OPER_DBG);
                continue;
            }
            typedef tr1::unordered_map<string, time_t>::iterator iterator;
            FileInfo fi(file, fInfo.st_ctime);
            AutoMutex am (_mutex);
            pair<FileInfoMapType::iterator, bool> it = _fileCreationTimes.insert (fi);
            if (!it.second) {
                // was previously there - check time
                if (it.first->second == fInfo.st_ctime) {
                    // already seen
                    SPLAPPTRC(L_DEBUG, "Already sent '" << component << "', skipping", SPL_OPER_DBG);
                    continue;
                }
                // update the time and continue
                it.first->second = fInfo.st_ctime;
            }
            foundFiles.push_back (fi);
        }

        if (foundFiles.size() > 1)
            sort (foundFiles.begin(), foundFiles.end(), sortFunction);

        // Now send all the files in order them...
        vector<FileInfo>::const_iterator it;
        for (it = foundFiles.begin(); it != foundFiles.end(); it++) {
            string baseName = bf::path(it->first).leaf();
            
            
            
            OPort0Type tuple$(rstring(it->first));
            submit (tuple$, 0);
        }

        // Do a period cleanup
        if (--timeToClean == 0) {
            SPLAPPTRC(L_DEBUG, "Starting cleanup", SPL_OPER_DBG);
            timeToClean = CLEAN_INTERVAL;

            tr1::unordered_map<string, time_t>::iterator it = _fileCreationTimes.begin();
            while (it != _fileCreationTimes.end()) {
                // Is the file gone?
                if (!bf::exists(bf::path(it->first))) {
                    SPLAPPTRC(L_DEBUG, "Entry for file '" << it->first << "' removed", SPL_OPER_DBG);
                    it = _fileCreationTimes.erase (it);
                }
                else {
                    ++it;
                }
            }

            SPLAPPTRC(L_DEBUG, "Finished cleanup", SPL_OPER_DBG);
        }

        // finished one scan
        _numDirectoryScans.incrementValueNoLock();

        // pause until next scan
        double currentTime = Functions::Time::getTimestampInSecs();
        if ((currentTime - lastScanStartTime) < scanWaitTime)
            pe.blockUntilShutdownRequest(scanWaitTime - (currentTime - lastScanStartTime));
    }

    SPLAPPTRC(L_DEBUG, "DirectoryScan exiting...", SPL_OPER_DBG);
}

void MY_OPERATOR_SCOPE::MY_OPERATOR::getCheckpoint(NetworkByteBuffer & opstate)
{
    AutoMutex am(_mutex);
    

    // Save file time information
    opstate.addUInt32(_fileCreationTimes.size());
    FileInfoMapType::iterator it;
    for (it = _fileCreationTimes.begin(); it != _fileCreationTimes.end(); it++) {
        opstate.addSTLString (it->first);
        opstate.addUInt64 (it->second);
    }
}

void MY_OPERATOR_SCOPE::MY_OPERATOR::restoreCheckpoint(NetworkByteBuffer & opstate)
{
    AutoMutex am(_mutex);
    
    _fileCreationTimes.clear();
    uint32_t n = opstate.getUInt32();
    while (n) {
        n--;
        std::string f;
        opstate.getSTLString(f);
        uint64_t t = opstate.getUInt64();
        _fileCreationTimes.insert(FileInfo(f,t));
    }
}

static SPL::Operator * initer() { return new MY_OPERATOR_SCOPE::MY_OPERATOR(); }
bool MY_BASE_OPERATOR::globalInit_ = MY_BASE_OPERATOR::globalIniter();
bool MY_BASE_OPERATOR::globalIniter() {
    instantiators_.insert(std::make_pair("fileWithExpressionToParseStream",&initer));
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
    initRTC(*this, lit$2, "lit$2");
    addParameterValue ("directory", SPL::ConstValueHandle(lit$0));
    addParameterValue ("sleepTime", SPL::ConstValueHandle(lit$1));
    param$pattern$0 = SPL::rstring(".*\\.txt");
    addParameterValue ("pattern", SPL::ConstValueHandle(param$pattern$0));
    addParameterValue ("initDelay", SPL::ConstValueHandle(lit$2));
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




