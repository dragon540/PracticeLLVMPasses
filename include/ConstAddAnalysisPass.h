//
// Created by shobhit on 11/30/25.
//

#ifndef PRACTICELLVMPASSES_CONSTADDANALYSISPASS_H
#define PRACTICELLVMPASSES_CONSTADDANALYSISPASS_H

#include "llvm/IR/PassManager.h"
#include "llvm/IR/Instruction.h"

namespace llvm
{
class ConstAddAnalysisPass : public PassInfoMixin<ConstAddAnalysisPass> 
{
    using Result = llvm::SmallVector<llvm::Instruction*, 0>;
public:
    PreservedAnalyses run(Function &F, FunctionAnalysisManager &FAM);

    Result getAddInstWithConstOperands(Function &F);
};
}


#endif //PRACTICELLVMPASSES_CONSTADDANALYSISPASS_H