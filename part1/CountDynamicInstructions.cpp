#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Intrinsics.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Support/raw_ostream.h"
#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <string>
using namespace llvm;
using namespace std;
namespace {
    class CountDynamicInstructions : public ModulePass {
        public :
        CountDynamicInstructions() : ModulePass(ID) {}
        virtual bool runOnModule(Module &M) {
            vector<int> allInstrucion;
            IRBuilder<> bBuilder(M.getContext());
            IRBuilder<> bBuilder1(M.getContext());
            // set insert point
            vector<Type*> args;
            // one int parameter
            args.push_back(IntegerType::get(M.getContext(), 32));
            FunctionType* oneArg = FunctionType::get(Type::getVoidTy(M.getContext()),args,false);
            // generate merge function, _Z5is function on the .bc file 
            Constant* merge = M.getOrInsertFunction("_Z5mergei", oneArg);
            Function* callMerge = dyn_cast<Function>(merge);
            // generate print function
            vector<Type*> voidargs;
            // no parameter
            FunctionType* voidArg = FunctionType::get(Type::getVoidTy(M.getContext()),voidargs,false);
            Constant* print = M.getOrInsertFunction("_Z5printv", voidArg);
            Function* callPrint = dyn_cast<Function>(print);

            for (Module::iterator mit = M.begin(), mite = M.end(); mit != mite; ++mit) {
                for (Function::iterator fit = mit->begin(), fite = mit->end(); fit != fite; ++fit) {
                    bBuilder.SetInsertPoint(fit->getFirstInsertionPt());
                    allInstrucion.clear();
                    for (BasicBlock::iterator iit = fit->begin(), iite = fit->end(); iit != iite; ++iit) {
                        int instuct = iit->getOpcode();
                        string name = iit->getOpcodeName();
                        // whether it is the return instruction
                        if (name == "ret")
                            bBuilder1.SetInsertPoint(iit);
                        allInstrucion.push_back(instuct);
                    }
                    for (vector<int>::iterator it = allInstrucion.begin(); it != allInstrucion.end(); ++it){
                        Value* opcode = ConstantInt::get(Type::getInt32Ty(M.getContext()), *it);
                        bBuilder.CreateCall(callMerge, opcode);
                    }
                }
                // if it is the main function, print
                if (mit->getName() == "main") {
                    bBuilder1.CreateCall(callPrint);
                }
            }
            
            return false;
        }
        virtual void print(raw_ostream &O, const Module *M) const{
            O << "CFG begin:" << endl;
            for(int i=0; i<nodes.size(); i++){
                O << "NodeId:" << nodes[i].num() << endl;
                vector<Edge> edges;
                edges = nodes[i].getInedges();
                O << "IN:"
                for(int j=0; j<edges.size(); j++)
                    O << edges[j].num() << " ";
                O << endl;
                edges = nodes[i].getOutedges();
                O << "OUT:"
                for(int j=0; j<edges.size(); j++)
                    O << edges[j].num() << " ";
                O << endl;
            }
            O << "CFG end" << endl;
        }
        static char ID;
    };
}
char CountDynamicInstructions::ID = 0;
static RegisterPass<CountDynamicInstructions> X("dynamic", "Count Dynamic Instructions", false, false);