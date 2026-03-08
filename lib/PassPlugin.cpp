#include "ConstAddAnalysisPass.h"
#include "ConstantFoldingPass.h"
#include "ReplaceMulWithShift.h"
#include "ReplaceDivWithShift.h"
#include "DeadCodeElimination.h"
#include "TailCallOptimization.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"

using namespace llvm;

bool registerPipeline(StringRef Name, FunctionPassManager &FPM,
                      ArrayRef<PassBuilder::PipelineElement>) {
    if (Name == "add-const-analysis") {
        FPM.addPass(ConstAddAnalysisPass());
        return true;
    }
    if(Name == "const-folding") {
	FPM.addPass(ConstantFoldingPass());
	return true;
    }
    if(Name == "replace-mul") {
	    FPM.addPass(ReplaceMulWithShift());
	    return true;
    }
    if(Name == "replace-div") {
	    FPM.addPass(ReplaceDivWithShift());
	    return true;
    }
    if(Name == "dead-code-elim") {
	    FPM.addPass(DeadCodeElimination());
	    return true;
    }
    if(Name == "tail-call-opt") {
	    FPM.addPass(TailCallOptimization());
	    return true;
    }
    return false;
}

PassPluginLibraryInfo getMyPass() {
    return {
        LLVM_PLUGIN_API_VERSION, "add-const-analysis",
        LLVM_VERSION_STRING, [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(registerPipeline);
        }
    };
}

extern "C" LLVM_ATTRIBUTE_WEAK PassPluginLibraryInfo
llvmGetPassPluginInfo() {
    return getMyPass();
}

