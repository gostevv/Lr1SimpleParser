// eJyVkcFOwkAQhjOv0njQS7cQvfRWCB4QFFPwaqZl0m5od9fZLaU8vQsGDAhRs6fN7vf9k3_0sqcLGyUq6Lo7HuMYXA9H_09CEIQ_0E6Q2JA45anadufrgrbye24G0WuW2z6nBY6lVGztdtZ0g4ePhL1FpbBRXJ1lRx21dP8dZGY_0WIyMDs_0gh74kW4iSGeTOGbrWKoCAESpaxL_0SlhbXNZSiVbzyhrMSRhkS_1xecU8s0SEorQjuIa_1Q2mesyUtPdKf228CD4WzvmGJeSkXBHSTOP2aNo0cm_0lJNZMbI3W_02TKoffEGKGB0tD3CmdUWoPOy4IRhqZR0qB_0s64eI84dDJ8VfPc9JoPhb1r0WBBN5vGrwIWbqyJifz0cYwWSu1gu_1gCPSVnL_0uFWqfdjlnvqvmWKMP_0wSVWNnk


#include "./Lr1Parser.h"
using namespace SPL::_Operator;

#include <SPL/Runtime/Function/SPLFunctions.h>
#include <SPL/Runtime/Operator/Port/Punctuation.h>

#include <string>

#define MY_OPERATOR_SCOPE SPL::_Operator
#define MY_BASE_OPERATOR Lr1Parser_Base
#define MY_OPERATOR Lr1Parser$OP






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
   osi->setParameter(env, setup, "classLibrary", "bin");
   osi->setParameter(env, setup, "generated", true);
   osi->setParameter(env, setup, "vmArg", lit$0);


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
    instantiators_.insert(std::make_pair("Lr1Parser",&initer));
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
    param$classLibrary$0 = SPL::rstring("bin");
    addParameterValue ("classLibrary", SPL::ConstValueHandle(param$classLibrary$0));
    param$generated$0 = true;
    addParameterValue ("generated", SPL::ConstValueHandle(param$generated$0));
    addParameterValue ("vmArg", SPL::ConstValueHandle(lit$0));
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






