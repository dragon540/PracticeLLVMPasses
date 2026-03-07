#include "ConstantFoldingPass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instruction.h"

using namespace llvm;

PreservedAnalyses ConstantFoldingPass::run(Function &F, FunctionAnalysisManager &FAM)
{
	bool modified = false;
	Function::iterator BB = F.begin();
	while(BB != F.end())
	{
		BasicBlock::iterator Instr = BB->begin();
		while(Instr != BB->end())
		{
			Instruction *tempInstr = &(*Instr);
			++Instr;
			if(tempInstr->isBinaryOp())
			{
				ConstantInt *o1 = dyn_cast<ConstantInt>(tempInstr->getOperand(0));
				ConstantInt *o2 = dyn_cast<ConstantInt>(tempInstr->getOperand(1));
				if(o1 && o2)
				{
					modified = true;
					IRBuilder<> builder(tempInstr);
					auto val1 = o1->getSExtValue();
					auto val2 = o2->getSExtValue();
					Value *resVal = nullptr;
					auto res = 0;
					if(tempInstr->getOpcode() == Instruction::Add)
					{
						res = val1 + val2;
					}
					else if(tempInstr->getOpcode() == Instruction::Sub)
					{
						res = val1 - val2;
					}
					else if(tempInstr->getOpcode() == Instruction::Mul)
					{
						res = val1 * val2;
					}
					else if(tempInstr->getOpcode() == Instruction::SDiv)
					{
						res = val1 / val2;
					}
					resVal = builder.getInt32(res);
					tempInstr->replaceAllUsesWith(resVal);
					tempInstr->eraseFromParent();
				}
			}
			//Instr++;
		}
		BB++;
	}
	return modified ? PreservedAnalyses::none() : PreservedAnalyses::all();
}

