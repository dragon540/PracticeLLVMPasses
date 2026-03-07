#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/IRBuilder.h"

#include "llvm/Passes/PassPlugin.h"
#include "llvm/Passes/PassBuilder.h"

using namespace llvm;

class DeadCodeElimination : public PassInfoMixin<DeadCodeElimination>
{
public:
	PreservedAnalyses run(Function &F, FunctionAnalysisManager &FAM);
};
