# NOTE: This makefile is designed to be run from one level up in the directory
# hierarchy compared to where it resides. For instance, if this makefile is
# located at 'output/build/Makefile', then it can be launched as:
# 'make -f build/Makefile' from the 'output' directory.

ifeq ($(CXX),)
  CXX=g++
endif
PKGCONFIG := /opt/ibm/InfoSphereStreams/bin/dst-pe-pkg-config.sh
PE_INCLUDE := $(shell $(PKGCONFIG) --cflags dst-spl-pe-install)
PE_LIB := $(shell $(PKGCONFIG) --libs dst-spl-pe-install)
PE_STAND_LIB := $(shell $(PKGCONFIG) --libs dst-spl-pe-install-standalone)
SPL_CXXFLAGS = -Wall -Wno-unused -Wno-sign-compare
SPL_CXXFLAGS += -D_REENTRANT -fPIC -finline-functions -fmessage-length=0
SPL_CXXFLAGS += $(PE_INCLUDE) 
SPL_LDFLAGS = $(PE_LIB)

SPL_TYPES = build/type/BeJyrNIs3LSjNSy4xTc4vzSsxKc6sSjUpycxNNU_0pzEvMzUw2zUstSy0CACk7A8P.o \
            build/type/BeJwrMSw2MkgsyizJyE0tyUx2rSgoSi0uzszPAwB5qAnV.o \
            build/type/BeJwrMSw2Mk3LzEkNzyzJcK0oKEotLs7MzwvJD0gsKk4FAK5VAuq.o \
            build/type/BeJyrNI03Ti4uMy6pKDFOyswzTcrJT842ycnMSwUAf_1wJCo.o \
            build/type/BeJwrMSw2MkksyizJyE0tyUx2rSgoSi0uzszPCylKTQUApTULBp.o 
SPL_FUNCTIONS = 
SPL_OPERATORS = build/operator/fileWithExpressionToParseStream.o \
                build/operator/arithmeticExpressionStream.o \
                build/operator/Lr1Parser.o \
                build/operator/Sink.o 
SPL_PE_OBJS = build/pe/BeJyz9CkyDEgsKk4tijcJzszLjjcySyzKLMnITS3JTHatKChKLS7OzM8LLilKTcyNNzZMy8xJDQfKI6RC8sH6oSoAyjofAD.o 
SPL_PE_BINS = bin/Parser-a.dpe 

.PHONY: distclean clean all types functions operators pes svar

all: bin types functions operators pes svar standalone

distclean clean:
	@rm -fr bin/* build/type build/function build/operator build/pe build/svar build/standalone

bin:
	@mkdir -m 775 bin

types: $(SPL_TYPES)

build/type/BeJyrNIs3LSjNSy4xTc4vzSsxKc6sSjUpycxNNU_0pzEvMzUw2zUstSy0CACk7A8P.o: \
	    src/type/BeJyrNIs3LSjNSy4xTc4vzSsxKc6sSjUpycxNNU_0pzEvMzUw2zUstSy0CACk7A8P.h \
	    src/type/BeJyrNIs3LSjNSy4xTc4vzSsxKc6sSjUpycxNNU_0pzEvMzUw2zUstSy0CACk7A8P.cpp \
	    build/cppOptions \
	    | build/type
	@echo ' [CXX-type] enum{punct,count,size,time,dynamic,never}'
	@$(CXX) -o $@ -c $(SPL_CXXFLAGS) src/type/BeJyrNIs3LSjNSy4xTc4vzSsxKc6sSjUpycxNNU_0pzEvMzUw2zUstSy0CACk7A8P.cpp

build/type/BeJyrNI03Ti4uMy6pKDFOyswzTcrJT842ycnMSwUAf_1wJCo.o: \
	    src/type/BeJyrNI03Ti4uMy6pKDFOyswzTcrJT842ycnMSwUAf_1wJCo.h \
	    src/type/BeJyrNI03Ti4uMy6pKDFOyswzTcrJT842ycnMSwUAf_1wJCo.cpp \
	    build/cppOptions \
	    | build/type
	@echo ' [CXX-type] enum{csv,txt,bin,block,line}'
	@$(CXX) -o $@ -c $(SPL_CXXFLAGS) src/type/BeJyrNI03Ti4uMy6pKDFOyswzTcrJT842ycnMSwUAf_1wJCo.cpp

build/type/BeJwrMSw2MkgsyizJyE0tyUx2rSgoSi0uzszPAwB5qAnV.o: \
	    src/type/BeJwrMSw2MkgsyizJyE0tyUx2rSgoSi0uzszPAwB5qAnV.h \
	    src/type/BeJwrMSw2MkgsyizJyE0tyUx2rSgoSi0uzszPAwB5qAnV.cpp \
	    build/cppOptions \
	    | build/type
	@echo ' [CXX-type] tuple<rstring arithmeticExpression>'
	@$(CXX) -o $@ -c $(SPL_CXXFLAGS) src/type/BeJwrMSw2MkgsyizJyE0tyUx2rSgoSi0uzszPAwB5qAnV.cpp

build/type/BeJwrMSw2Mk3LzEkNzyzJcK0oKEotLs7MzwvJD0gsKk4FAK5VAuq.o: \
	    src/type/BeJwrMSw2Mk3LzEkNzyzJcK0oKEotLs7MzwvJD0gsKk4FAK5VAuq.h \
	    src/type/BeJwrMSw2Mk3LzEkNzyzJcK0oKEotLs7MzwvJD0gsKk4FAK5VAuq.cpp \
	    build/cppOptions \
	    | build/type
	@echo ' [CXX-type] tuple<rstring fileWithExpressionToParse>'
	@$(CXX) -o $@ -c $(SPL_CXXFLAGS) src/type/BeJwrMSw2Mk3LzEkNzyzJcK0oKEotLs7MzwvJD0gsKk4FAK5VAuq.cpp

build/type/BeJwrMSw2MkksyizJyE0tyUx2rSgoSi0uzszPCylKTQUApTULBp.o: \
	    src/type/BeJwrMSw2MkksyizJyE0tyUx2rSgoSi0uzszPCylKTQUApTULBp.h \
	    src/type/BeJwrMSw2MkksyizJyE0tyUx2rSgoSi0uzszPCylKTQUApTULBp.cpp \
	    build/cppOptions \
	    | build/type
	@echo ' [CXX-type] tuple<rstring arithmeticExpressionTree>'
	@$(CXX) -o $@ -c $(SPL_CXXFLAGS) src/type/BeJwrMSw2MkksyizJyE0tyUx2rSgoSi0uzszPCylKTQUApTULBp.cpp

build/type:
	-@mkdir -m 775 build/type

operators: $(SPL_OPERATORS)

-include build/operator/fileWithExpressionToParseStream.d
build/operator/fileWithExpressionToParseStream.o: \
	    src/operator/fileWithExpressionToParseStream.h \
	    src/operator/fileWithExpressionToParseStream.cpp\
	    build/dep/operator/fileWithExpressionToParseStream.dep  \
	    build/cppOptions \
	    | build/operator
	@echo ' [CXX-operator] fileWithExpressionToParseStream'
	@$(CXX) -o $@ -MD -I /opt/ibm/InfoSphereStreams/toolkits/spl/impl/include -DSPLJAVAFUNCTION_ADL_FILENAME=\"Parser.adl\" -c $(SPL_CXXFLAGS) src/operator/fileWithExpressionToParseStream.cpp

-include build/operator/arithmeticExpressionStream.d
build/operator/arithmeticExpressionStream.o: \
	    src/operator/arithmeticExpressionStream.h \
	    src/operator/arithmeticExpressionStream.cpp\
	    build/dep/operator/arithmeticExpressionStream.dep \
	    src/type/BeJwrMSw2MkgsyizJyE0tyUx2rSgoSi0uzszPAwB5qAnV.h \
	    src/type/BeJyrNI03Ti4uMy6pKDFOyswzTcrJT842ycnMSwUAf_1wJCo.h  \
	    build/cppOptions \
	    | build/operator
	@echo ' [CXX-operator] arithmeticExpressionStream'
	@$(CXX) -o $@ -MD -I /opt/ibm/InfoSphereStreams/toolkits/spl/impl/include -DSPLJAVAFUNCTION_ADL_FILENAME=\"Parser.adl\" -c $(SPL_CXXFLAGS) src/operator/arithmeticExpressionStream.cpp

-include build/operator/Lr1Parser.d
build/operator/Lr1Parser.o: \
	    src/operator/Lr1Parser.h \
	    src/operator/Lr1Parser.cpp\
	    build/dep/operator/Lr1Parser.dep  \
	    build/cppOptions \
	    | build/operator
	@echo ' [CXX-operator] Lr1Parser'
	@$(CXX) -o $@ -MD -I /opt/ibm/InfoSphereStreams/toolkits/spl/impl/include -I /opt/ibm/InfoSphereStreams/java/include -DSPLJAVAFUNCTION_ADL_FILENAME=\"Parser.adl\" -c $(SPL_CXXFLAGS) src/operator/Lr1Parser.cpp

-include build/operator/Sink.d
build/operator/Sink.o: \
	    src/operator/Sink.h \
	    src/operator/Sink.cpp\
	    build/dep/operator/Sink.dep \
	    src/type/BeJyrNIs3LSjNSy4xTc4vzSsxKc6sSjUpycxNNU_0pzEvMzUw2zUstSy0CACk7A8P.h \
	    src/type/BeJwrMSw2MkksyizJyE0tyUx2rSgoSi0uzszPCylKTQUApTULBp.h  \
	    build/cppOptions \
	    | build/operator
	@echo ' [CXX-operator] Sink'
	@$(CXX) -o $@ -MD -I /opt/ibm/InfoSphereStreams/toolkits/spl/impl/include -DSPLJAVAFUNCTION_ADL_FILENAME=\"Parser.adl\" -c $(SPL_CXXFLAGS) src/operator/Sink.cpp

build/operator:
	-@mkdir -m 775 -p build/operator

functions: $(SPL_FUNCTIONS)

pes: $(SPL_PE_BINS)

build/pe/BeJyz9CkyDEgsKk4tijcJzszLjjcySyzKLMnITS3JTHatKChKLS7OzM8LLilKTcyNNzZMy8xJDQfKI6RC8sH6oSoAyjofAD.o: \
	    src/pe/BeJyz9CkyDEgsKk4tijcJzszLjjcySyzKLMnITS3JTHatKChKLS7OzM8LLilKTcyNNzZMy8xJDQfKI6RC8sH6oSoAyjofAD.h \
	    src/pe/BeJyz9CkyDEgsKk4tijcJzszLjjcySyzKLMnITS3JTHatKChKLS7OzM8LLilKTcyNNzZMy8xJDQfKI6RC8sH6oSoAyjofAD.cpp  \
	    build/cppOptions \
	    | build/pe
	@echo ' [CXX-pe] pe Parser-a'
	@$(CXX) -o $@ -c $(SPL_CXXFLAGS) src/pe/BeJyz9CkyDEgsKk4tijcJzszLjjcySyzKLMnITS3JTHatKChKLS7OzM8LLilKTcyNNzZMy8xJDQfKI6RC8sH6oSoAyjofAD.cpp

PEParser-a = \
	    build/pe/BeJyz9CkyDEgsKk4tijcJzszLjjcySyzKLMnITS3JTHatKChKLS7OzM8LLilKTcyNNzZMy8xJDQfKI6RC8sH6oSoAyjofAD.o \
	    build/operator/fileWithExpressionToParseStream.o \
	    build/type/BeJwrMSw2Mk3LzEkNzyzJcK0oKEotLs7MzwvJD0gsKk4FAK5VAuq.o \
	    build/operator/arithmeticExpressionStream.o \
	    build/type/BeJwrMSw2MkgsyizJyE0tyUx2rSgoSi0uzszPAwB5qAnV.o \
	    build/type/BeJyrNI03Ti4uMy6pKDFOyswzTcrJT842ycnMSwUAf_1wJCo.o \
	    build/operator/Lr1Parser.o \
	    build/type/BeJwrMSw2MkksyizJyE0tyUx2rSgoSi0uzszPCylKTQUApTULBp.o \
	    build/operator/Sink.o \
	    build/type/BeJyrNIs3LSjNSy4xTc4vzSsxKc6sSjUpycxNNU_0pzEvMzUw2zUstSy0CACk7A8P.o 

bin/Parser-a.dpe: \
	$(PEParser-a) \
	build/dep/Parser-a.dep \
	build/ldOptions
	@echo ' [LD-pe] pe Parser-a'
	@$(CXX) $(SPL_CXXFLAGS) -o bin/Parser-a.dpe -fPIC -shared $(PEParser-a) -lstreams-stdtk-runtime -lstreams-stdtk-runtime -lstreams-stdtk-javaop -L /opt/ibm/InfoSphereStreams/java/jre/lib/amd64/j9vm -Wl,-rpath -Wl,/opt/ibm/InfoSphereStreams/java/jre/lib/amd64/j9vm -lpthread -ldl -lstreams-stdtk-runtime -lstreams-stdtk-runtime $(SPL_LDFLAGS)

build/pe:
	-@mkdir -m 775 build/pe

standalone: bin/standalone 

build/standalone/standalone.o: \
	    src/standalone/standalone.h \
	    src/standalone/standalone.cpp  \
	    build/cppOptions \
	    | build/standalone
	@echo ' [CXX-standalone] standalone'
	@$(CXX) -o $@ -c $(SPL_CXXFLAGS) src/standalone/standalone.cpp

bin/standalone: build/standalone/standalone.o build/ldOptions
	@echo ' [LD-standalone] standalone'
	@$(CXX) $(SPL_CXXFLAGS) -o bin/standalone build/standalone/standalone.o $(PE_STAND_LIB)
	@echo ' [LN-standalone] standalone '
	@ln -sf standalone bin/Parser
build/standalone:
	-@mkdir -m 775 build/standalone

