#include "TailCallOptimization.h"

using namespace llvm;

PreservedAnalyses TailCallOptimization::run(Function &F, FunctionAnalysisManager &FAM)
{
	bool modified = false;
	for(Function::iterator BB = F.begin(); BB != F.end(); BB++)
	{
		for(BasicBlock::iterator I = BB->begin(); I != BB->end();)
		{
			Instruction *Instr = &(*I);
			I++;

			// detect call instruction
			// if call is found check if succeeding instruction is a return instruction
			// if true, replace call with branch to top of the function being called
			
			if(Instr->getOpcode() == Instruction::Call)
			{
				if(I->getOpcode() == Instruction::Ret)
				{
					modified = true;
					IRBuilder<> builder(Instr);
					CallInst *callInst = dyn_cast<CallInst>(Instr);
					// In LLVM, the BasicBlock to which branching is done should
					// belong to same Function.
					// Strictly speaking, tail call optimization is not limited to
					// recursion, TCO can be performed whenever a call is followed 
					// by a return. However, due to LLVM's constraint mentioned above
					// this implementation is only limited to TCO during recursion.
					if(callInst->getCalledFunction() == callInst->getParent())
					{
						auto bb = callInst->getParent();
						builder.CreateBr(bb);
						Instr->eraseFromParent();
						Instruction *nextInstr = &(*I);
				        	I++;	
						nextInstr->eraseFromParent();
					}
				}
			}
		}
	}
	return modified ? PreservedAnalyses::none() : PreservedAnalyses::all();
}
