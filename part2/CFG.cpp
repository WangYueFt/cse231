#include "Node.h"
#include "Edge.h"
#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Intrinsics.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/GlobalVariable.h"
#include <map>
#include <string>
#include <iostream>
#include <vector>

using namespace llvm;
using namespace std;

namespace {
    class BranchBias : public ModulePass {
    	public :
        BranchBias() : ModulePass(ID) {}
        virtual bool runOnModule(Module &M) {
        	vector<Node> nodes = vector<Node>();
        	vector<Edge> edges = vector<Edges>();
        	int count = 0;
        	for (Module::iterator mit = M.begin(); mit != M.end(); ++mit) {
        		for (Function::iterator fit = mit->begin(), fite = mit->end(); fit != fite; ++fit) {
        			for (BasicBlock::iterator iit = fit->begin(), iite = fit->end(); iit != iite; ++iit) {
        				nodes.push_back( Node(*iit) );
        				count++;
        			}
        		}
        	}
        	count = 0;
        	for (Module::iterator mit = M.begin(); mit != M.end(); ++mit) {
        		for (Function::iterator fit = mit->begin(), fite = mit->end(); fit != fite; ++fit) {
        			for (BasicBlock::iterator iit = fit->begin(), iite = fit->end(); iit != iite; ++iit) {
        				nodes.push_back( Node(*iit) );
        			}
        		}
        	}
        }
    };
}
