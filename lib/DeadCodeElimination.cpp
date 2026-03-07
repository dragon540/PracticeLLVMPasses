#include "DeadCodeElimination.h"

#include <unordered_map>

using namespace llvm;

PreservedAnalyses DeadCodeElimination::run(Function &F, FunctionAnalysisManager &FAM)
{
	bool modified = false;
	// Mapping between Value* and if it is used
	std::unordered_map<Value*, bool> valueUsed;
	for(Function::iterator BB = F.begin(); BB != F.end(); BB++)
	{
		for(BasicBlock::iterator Instr = BB->begin(); Instr != BB->end(); Instr++)
		{
			//Instruction *I = &(*Instr);
			//I++;

			// Store instruction in map, and mark it as not used (i.e false)
			valueUsed[&(*Instr)] = false;

			int operandCount = Instr->getNumOperands();
			for(int i = 0; i < operandCount; i++)
			{
				Value *op = Instr->getOperand(i);
				if(valueUsed.find(op) == valueUsed.end())
				{
					continue;
				}
				else 
				{
					valueUsed[op] = true;
				}
			}
		}
	}

	for(auto i : valueUsed)
	{
		if(i.second == false)
		{
			Instruction *I = dyn_cast<Instruction>(i.first);
			if(!I->isTerminator())
			{
				I->eraseFromParent();
			}
		}
	}	
	return modified ? PreservedAnalyses::none() : PreservedAnalyses::all();	
}
