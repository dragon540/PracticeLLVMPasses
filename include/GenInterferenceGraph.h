#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/IRBuilder.h"

#include "llvm/Passes/PassPlugin.h"
#include "llvm/Passes/PassBuilder.h"

#include <unordered_map>
#include <string>

using namespace llvm;
using namespace std;

class GenInterferenceGraph : public PassInfoMixin<GenInterferenceGraph>
{
public:
	using Map = unordered_map<string, pair<int, int>>;
	using Graph = unordered_map<string, vector<string>>;
	
	PreservedAnalyses run(Function &F, FunctionAnalysisManager &FAM);
	Map getLiveRange(BasicBlock &BB);
	Graph createInterferenceGraph(Map &map);

};	
