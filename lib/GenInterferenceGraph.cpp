#include "GenInterferenceGraph.h"

using namespace llvm;
using namespace std;

//using unordered_map<Value, pair<int, int>> = Map;
PreservedAnalyses GenInterferenceGraph::run(Function &F, FunctionAnalysisManager &FAM)
{
	Function::iterator BB = F.begin();
	while(BB != F.end()) 
	{
		BasicBlock &currentBB = *BB;

		// find live ranges of all virtual registers
		Map liveRange = getLiveRange(currentBB);
		Map::iterator mp = liveRange.begin();
		while(mp != liveRange.end())
		{
			errs() << mp->first << " : " << mp->second.first << " " << mp->second.second << "\n";
			mp++;
		}
		
		// build interference graph
		Graph interferenGraph = createInterferenceGraph(liveRange);
		Graph::iterator g_it = interferenGraph.begin();
		while(g_it != interferenGraph.end())
		{
			errs() << g_it->first << " : ";
			for(int i = 0; i < g_it->second.size(); i++)
			{
				errs() << g_it->second[i] << " ";
			}
			errs() << "\n";
			g_it++;
		}

		BB++;
	}
	return PreservedAnalyses::all();	
}

GenInterferenceGraph::Map GenInterferenceGraph::getLiveRange(BasicBlock &BB)
{
	Map liveRange;
	BasicBlock::iterator Instr = BB.begin();
	int lineNo = 0;
	while(Instr != BB.end())
	{
		lineNo++;

		// check if a new temporary is assigned in this instruction
		if((Instr->getType())->isVoidTy())
		{
			Instr++;
			continue;
		}

		// add a new field for temporary in liveRange Map
		//errs() << Instr->getName() << " " << lineNo << "\n";
		auto name = Instr->getName().str();
		liveRange[name] = make_pair(lineNo, lineNo);

		// check its RHS to find what temporaries are live at this point
		for(int i = 0; i < Instr->getNumOperands(); i++)
		{
			auto temp = (Instr->getOperand(i))->getName().str();
			if(liveRange.find(temp) != liveRange.end())
			{
				liveRange[temp].second = lineNo;
			}
		}

		Instr++;
	}
	return liveRange;
}

GenInterferenceGraph::Graph GenInterferenceGraph::createInterferenceGraph(Map &map)
{
	Graph graph;
	Map::iterator it = map.begin();
	while(it != map.end())
	{
		int  var_start = it->second.first;
		int  var_end   = it->second.second;
		auto var       = it->first;
		// if node doesn't exist, create it
		if(graph.find(var) == graph.end())
		{
			// create a node
			graph[var].push_back({});
		}
		
		Graph::iterator g_it = graph.begin();
		while(g_it != graph.end())
		{
			auto temp_var = g_it->first;
			if(temp_var != var)
			{
				int temp_start = map[temp_var].first;
				int temp_end   = map[temp_var].second;

				if((temp_start >= var_start && temp_start <= var_end) || 
				   (temp_end <= var_end && temp_end >= var_start)
				  )
				{
					graph[var].push_back(temp_var);
					graph[temp_var].push_back(var);
				}
			}
			g_it++;
		}
		
		it++;
	}
	return graph;
}
