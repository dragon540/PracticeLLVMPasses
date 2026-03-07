#include "ConstAddAnalysisPass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instruction.h"

using namespace llvm;

PreservedAnalyses ConstAddAnalysisPass::run(Function &F, FunctionAnalysisManager &FAM)
{
    outs() << F.getName() << "\n";
    Result res = getAddInstWithConstOperands(F);
    for(Instruction* I : res) {
        outs() << I->getOpcodeName() << " " << I->getOperand(0) << " " 
            << I->getOperand(1) << "\n";
    }
    return PreservedAnalyses::all();
}

ConstAddAnalysisPass::Result ConstAddAnalysisPass::getAddInstWithConstOperands(Function &F) {
    Result res;
    for(BasicBlock& BB : F) {
        for(Instruction& I : BB) {
            if(I.getOpcode() == Instruction::Add) {
                if(isa<Constant>(I.getOperand(0)) && isa<Constant>(I.getOperand(1)) ) {
                    res.push_back(&I);
                }
            }
        }
    }
    return res;
}
