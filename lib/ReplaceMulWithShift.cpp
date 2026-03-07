#include "ReplaceMulWithShift.h"

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

PreservedAnalyses ReplaceMulWithShift::run(Function &F, FunctionAnalysisManager &FAM)
{
	bool modified = false;
	for(Function::iterator BB = F.begin(); BB != F.end(); BB++)
	{
		for(BasicBlock::iterator Instr = BB->begin(); Instr != BB->end();)
		{
			Instruction *I = &(*Instr);
			Instr++;
			if(I->getOpcode() == Instruction::Mul)
			{
				Value *v1 = I->getOperand(0);
				Value *v2 = I->getOperand(1);

				ConstantInt *c1 = dyn_cast<ConstantInt>(v1);
				ConstantInt *c2 = dyn_cast<ConstantInt>(v2);

				Value *val = nullptr;
				ConstantInt *constVal = nullptr;

				// if both are const, then do nothing
				if(c1 && c2) continue;
				// if both are not const, then do nothing
				else if(c1 == nullptr && c2 == nullptr) continue;
				// if one is const, check further
				else if(c1 == nullptr && c2 != nullptr) {
					val = v1;
					constVal = c2;
				}
				else if(c2 == nullptr && c1 != nullptr) {
					val = v2;
					constVal = c1;
				}
				// check if const is power of 2
				auto num = constVal->getSExtValue();
				int exp = isPowerOf2(num);
				if(exp == -1)
					continue;
				else 
				{
					modified = true;
					IRBuilder<> builder(I);
					Value *expVal = builder.getInt32(exp);
					Value *newInstr = builder.CreateShl(val, expVal);
					I->replaceAllUsesWith(newInstr);
					I->eraseFromParent();
				}
			}
		}
	}
	return modified ? PreservedAnalyses::none() : PreservedAnalyses::all();
}
