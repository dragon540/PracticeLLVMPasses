#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/IRBuilder.h"

#include "llvm/Passes/PassPlugin.h"
#include "llvm/Passes/PassBuilder.h"

using namespace llvm;

struct ReplaceDivWithShift : PassInfoMixin<ReplaceDivWithShift>
{
	PreservedAnalyses run(Function &F, FunctionAnalysisManager &FAM);
};
