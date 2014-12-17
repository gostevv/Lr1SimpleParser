// eJydksFO4zAQhjWvUnGAS2K6i1bqLbAFbUnaStnuFU3TUWJI7DCeNLhPjymiu6UViJUPlmV_13_1z22LV11ImutfjRaIJrnLWgtmMIgyiKxbcUX9Kk5yz_17v1inf3OlU_1DfLtQMr2f_1Eoz63xRTdOizlaPyt6OraTuR7bps_0RmVs5_06qgaHLj6YfZQOq83Ez9W4hdPQ85Lm2vVbdxmnvSXF4_0J_0fNCKjiHEO9EQT5PRyN2wtqUABBXtqE4LAkbh6tGm7i3_1OBaLChukR3xXc3n8QoFwVhDcAFFjc5NsaEg3dPt208HAYzmW0eGRaUNDc4gkbC57ISumehVleolI_1vPbAdwSYYYhVZv5NLamtAEUrgjuLLGCRqBdZNw_0V7_19iC7U8haqoZEF_0Onlsk5bc1hJt1aDlhUktwdI07PYA_1fEa_0iL3UONPD2G0EQHY339zIK7JE6_1_1vboAmVv4F5aXK3u_1sa6_07f9YeRVMj0DNwDAaC


#include "./SystemProperties.h"
using namespace SPL::_Operator;

#include <SPL/Runtime/Function/SPLFunctions.h>
#include <SPL/Runtime/Operator/Port/Punctuation.h>

#include <string>

#define MY_OPERATOR_SCOPE SPL::_Operator
#define MY_BASE_OPERATOR SystemProperties_Base
#define MY_OPERATOR SystemProperties$OP






#include <dlfcn.h>

#include <SPL/Toolkit/JavaOp.h>
#include <SPL/Toolkit/RuntimeException.h>

MY_OPERATOR_SCOPE::MY_OPERATOR::MY_OPERATOR()
{
  /* Get a handle to the Java virtual machine */
  size_t vmOptionsCount = 1;
SPL::rstring vmOptions[vmOptionsCount];
vmOptions[0] = lit$0;


  jboolean startedJVM;
  const std::string javaOpDir = getenv("STREAMS_INSTALL") ? std::string(getenv("STREAMS_INSTALL")) + "/toolkits/spl/spl/utility/JavaOp" : "/opt/ibm/InfoSphereStreams/toolkits/spl/spl/utility/JavaOp";

  SPL::JNI::JVMControl *jvmControl = SPL::JNI::JVMControl::getJVM(
     javaOpDir.c_str(), vmOptions, vmOptionsCount, &startedJVM);
   
  /* Attach to the JVM  for the duration of the initialization */
  JNIEnv * env = jvmControl->attach();

  /* How we invoke methods against an OperatorSetup instance */
  SPL::JNI::OpSetupInvoker* osi = jvmControl->getOpSetupInvoker();

  /* OperatorSetup instance specific to this operator */
  jobject setup = osi->newSetup(env, this); 

  /* SPL kind of operator being executed - added in 3.0 */
     osi->setParameter(env, setup, "[kind]", SPL::rstring("spl.utility::JavaOp"));

   
  /**
     Pass the parameters into my OperatorSetup instance.
  */
     osi->setParameter(env, setup, "className", SPL::rstring("lr1.ParserMachine"));
   osi->setParameter(env, setup, "classLibrary", "");
   osi->setParameter(env, setup, "generated", true);
   osi->setParameter(env, setup, "vmArg", lit$0);
   osi->setParameter(env, setup, "arithmeticExpression", iport$0.get_arithmeticExpression());


  /**
    Pass input port information into the Java operator.
 
    Are logic clauses present.
   
    Pass the windowing information for each port as
    a list of values for the parameter '[window].N' where
    N is the index of the windowed input port.
  */
     osi->setParameter(env, setup, "[inputPortLogic].0", "none");
 hasTupleLogic = false;


  
  /* At this point all the initialization information has been
     passed to OperatorSetup. Create a JNIBridge instance object
     we use to communicate with the user's Operator implementation
     at runtime.
  */
  
  _bi = jvmControl->getBridgeInvoker();
  _bridge = _bi->newBridge(env, this, setup, startedJVM, (jboolean) false);
        
  /* Completed Java initialization, detach from the JVM */
  jvmControl->detach();

  _bi->construct();

  void * handle = dlopen("libstreams-stdtk-javaop.so", RTLD_LAZY);
  if (!handle) {
    const FormattableMessage& m = SPL_APPLICATION_RUNTIME_EXCEPTION("libstreams-stdtk-javaop.so");
    THROW_STRING(SPLRuntimeJavaOperator, m);
  }
  _fp = (FP) dlsym(handle, "callProcessTupleWithNativeByteBuffer");
}

MY_OPERATOR_SCOPE::MY_OPERATOR::~MY_OPERATOR() 
{
    _bi->destruct();
}

void MY_OPERATOR_SCOPE::MY_OPERATOR::allPortsReady() 
{
    _bi->allPortsReady(_bridge);
    createThreads(1);
}
 
void MY_OPERATOR_SCOPE::MY_OPERATOR::prepareToShutdown() 
{
   _bi->shutdown(_bridge);
}

void MY_OPERATOR_SCOPE::MY_OPERATOR::process(uint32_t idx)
{
   _bi->complete(_bridge);
}

void MY_OPERATOR_SCOPE::MY_OPERATOR::process(Tuple & tuple, uint32_t port)
{
}

void MY_OPERATOR_SCOPE::MY_OPERATOR::process(Tuple const & tuple, uint32_t port)
{
   _bi->processTuple(_bridge, tuple, port);
}

void MY_OPERATOR_SCOPE::MY_OPERATOR::process(Punctuation const & punct, uint32_t port)
{
   _bi->processPunctuation(_bridge, punct, port);
}

static SPL::Operator * initer() { return new MY_OPERATOR_SCOPE::MY_OPERATOR(); }
bool MY_BASE_OPERATOR::globalInit_ = MY_BASE_OPERATOR::globalIniter();
bool MY_BASE_OPERATOR::globalIniter() {
    instantiators_.insert(std::make_pair("SystemProperties",&initer));
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
    param$className$0 = SPL::rstring("lr1.ParserMachine");
    addParameterValue ("className", SPL::ConstValueHandle(param$className$0));
    param$classLibrary$0 = SPL::rstring("");
    addParameterValue ("classLibrary", SPL::ConstValueHandle(param$classLibrary$0));
    param$generated$0 = true;
    addParameterValue ("generated", SPL::ConstValueHandle(param$generated$0));
    addParameterValue ("vmArg", SPL::ConstValueHandle(lit$0));
    addParameterValue ("arithmeticExpression");
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






