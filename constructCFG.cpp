#include "Node.h"
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
    class CFG : public ModulePass {
    	public :
        CFG() : ModulePass(ID) {}
        virtual bool runOnModule(Module &M) {
        	nodes = vector<Node>();
            edges = vector<Edge>();
            map<Instruction *,int> m = map<Instruction *,int>();
            Edge lastEdge = Edge();
            Edge currentEdge;
        	int count = 0;
        	for (Module::iterator mit = M.begin(); mit != M.end(); ++mit) {
        		for (Function::iterator fit = mit->begin(), fite = mit->end(); fit != fite; ++fit) {
        			for (BasicBlock::iterator iit = fit->begin(), iite = fit->end(); iit != iite; ++iit) {
                        m.insert(pair<Instruction *,int>(&(*iit),count));
        				nodes.push_back( Node(&(*iit),count++));
        			}
        		}
        	}
        	count = 0;
        	for (Module::iterator mit = M.begin(); mit != M.end(); ++mit) {
        		for (Function::iterator fit = mit->begin(), fite = mit->end(); fit != fite; ++fit) {
                    bool flag = true;
        			for (BasicBlock::iterator iit = fit->begin(), iite = fit->end(); iit != iite; ++iit) {
                        currentEdge = Edge();
                        BasicBlock::iterator tiit = iit;
                        tiit++;
                        edges.push_back(currentEdge);
                        if(tiit != fit->end())
                            nodes[count].addOutEdge(currentEdge);
                        if(flag)
                            flag = false;
                        else
                            nodes[count].addInEdge(lastEdge);
                        lastEdge = currentEdge;
                        count++;
        			}
                    const TerminatorInst *TInst = fit->getTerminator();
                    int idx0 = m.find((Instruction *)TInst)->second;
                    for (unsigned I = 0, NSucc = TInst->getNumSuccessors(); I < NSucc; ++I) {
                        BasicBlock *Succ = TInst->getSuccessor(I);
                        currentEdge = Edge();
                        Instruction *ttt = &(*(Succ->begin()));
                        int idx = m.find(ttt)->second;
                        nodes[idx0].addOutEdge(currentEdge);
                        nodes[idx].addInEdge(currentEdge);
                    }
        		}
        	}
            
            in.elems.push_back(new ConstElem("add", 123));
            in.elems.push_back(new ConstElem("add1", 321));
            out = nodes[9].CPFlowOp(in);
            return true;
        }
        virtual void print(raw_ostream &O, const Module *M) const{
            O << "CFG begin:" << "\n";
            for(size_t i=0; i<nodes.size(); i++){
                O << "NodeId:" << nodes[i].num() << "\n";
                O << "Node:"  << *(nodes[i].inst) << "\n";
                O << "Operand:"  << nodes[i].inst->getOpcodeName() << "\n";
                const vector<Edge> edges = nodes[i].getInEdges();
                O << "IN:";
                for(size_t j=0; j<edges.size(); j++)
                    O << edges[j].num() << " ";
                O << "\n";
                const vector<Edge> edgess = nodes[i].getOutEdges();
                O << "OUT:";
                for(size_t j=0; j<edgess.size(); j++)
                    O << edgess[j].num() << " ";
                O << "\n";
                O << "\n";
                
            }
            O << "CFG end" << "\n";
            string s = nodes[6].inst->getOpcodeName();
            // ConstantInt* c = dyn_cast<ConstantInt>(v);
            //ConstantInt* result = dyn_cast<ConstantInt>(c);
            //int a = result->getValue().getLimitedValue();
            //char* s = (char*)result;
            // const string s = c->getName().data();
            O << "Operand:" << s << "\n";
            //O << "Operand:"  << a << "\n";

            for (size_t i = 0; i < out.elems.size(); i++) {
                O << out.elems[i]->getName() << " " << out.elems[i]->getValue() << " \n";
            }
            
        }
        static char ID;
        vector<Node> nodes;
        vector<Edge> edges;
        ConstProLattice<ConstElem> in;
        ConstProLattice<ConstElem> out;
    };
}
char CFG::ID = 0;
static RegisterPass<CFG> X("cfg", "CFG", false, false);
