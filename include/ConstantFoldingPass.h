#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IRBuilder.h"

#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"

using namespace llvm;

class ConstantFoldingPass : public  PassInfoMixin<ConstantFoldingPass>
{
	public:
	PreservedAnalyses run(Function &F, FunctionAnalysisManager &FAM);
};

