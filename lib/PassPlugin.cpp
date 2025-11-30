#include "ConstAddAnalysisPass.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"

using namespace llvm;

bool registerPipeline(StringRef Name, FunctionPassManager &FPM,
                      ArrayRef<PassBuilder::PipelineElement>) {
    if (Name == "add-const-analysis") {
        FPM.addPass(ConstAddAnalysisPass());
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

