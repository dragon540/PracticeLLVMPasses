#include "ReplaceDivWithShift.h"

using namespace llvm;

int isPowerOf2(int temp)
{
	int pow = 0;
	while(temp%2==0 && temp > 1) {
		temp = temp/2;
		pow++;
	}
	if(temp == 1) {
		return pow;
	}
	return -1;
}

PreservedAnalyses ReplaceDivWithShift::run(Function &F, FunctionAnalysisManager &FAM)
{
	bool modified = false;
	for(Function::iterator BB = F.begin(); BB != F.end(); BB++)
	{
		for(BasicBlock::iterator I = BB->begin(); I != BB->end();)
		{
			Instruction *Instr = &(*I);
			I++;

			if(Instr->getOpcode() == Instruction::SDiv)
			{
				Value *v1 = Instr->getOperand(0);
				Value *v2 = Instr->getOperand(1);

				ConstantInt *c1 = dyn_cast<ConstantInt>(v1);
				ConstantInt *c2 = dyn_cast<ConstantInt>(v2);

				Value *val = nullptr;
				ConstantInt *constVal = nullptr;

				if(c1 && c2) continue;
				else if(c1 == nullptr && c2 == nullptr) continue;
				else if(c1 != nullptr && c2 == nullptr)
				{
					//val = v2;
					//constVal = c1;
					continue;
				}
				else if(c1 == nullptr && c2 != nullptr)
				{
					val = v1;
					constVal = c2;
				}

				if(!constVal->getValue().isPowerOf2())
					continue;
				else{
					modified = true;
					IRBuilder<> builder(Instr);
					Value *newInstr = builder.CreateAShr(val, constVal->getValue().exactLogBase2());
				       	Instr->replaceAllUsesWith(newInstr);
					Instr->eraseFromParent();	
				}
			}
		}
	}
	return modified ? PreservedAnalyses::none() : PreservedAnalyses::all();
}
