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
#include <string>
using namespace llvm;
using namespace std;
namespace {
    class BranchBias : public ModulePass {
        public :
        BranchBias() : ModulePass(ID) {}
        virtual bool runOnModule(Module &M) {
            IRBuilder<> bBuilder(M.getContext());
            IRBuilder<> bBuilder1(M.getContext());

            vector<Type*> args;
            // one int parameter
            PointerType* ptr = PointerType::get(IntegerType::get(M.getContext(), 8), 0);
            args.push_back(ptr);
            
            FunctionType* oneArg = FunctionType::get(Type::getVoidTy(M.getContext()),args,false);
            // generate merge function
            Constant* merge = M.getOrInsertFunction("_Z8funcNamePc", oneArg);
            
            Function* callMerge = dyn_cast<Function>(merge);

            vector<Type*> argss;
            // one int parameter
            argss.push_back(ptr);
            argss.push_back(Type::getInt1Ty(M.getContext()));
            FunctionType* twoArg = FunctionType::get(Type::getVoidTy(M.getContext()),argss,false);
            // generate count taken branch funtion
            Constant* taken = M.getOrInsertFunction("_Z6branchPcb", twoArg);
            Function* callTaken = dyn_cast<Function>(taken);

            // generate print function
            vector<Type*> voidargs;
            // no parameter
            FunctionType* voidArg = FunctionType::get(Type::getVoidTy(M.getContext()),voidargs,false);
            Constant* print = M.getOrInsertFunction("_Z5printv", voidArg);
            Function* callPrint = dyn_cast<Function>(print);
            
            vector<BasicBlock*> allBranchBlock;

            for (Module::iterator mit = M.begin(); mit != M.end(); ++mit) {
                Constant *charArray = ConstantDataArray::getString(M.getContext(), mit->getName(), true);
                GlobalVariable* gvar_array__str = new GlobalVariable(M,
                                                                     charArray->getType(),
                                                                     true,
                                                                     GlobalValue::InternalLinkage,
                                                                     charArray, // has initializer, specified below
                                                                     mit->getName());
                gvar_array__str->setAlignment(8);
                ConstantInt* const_int32_6 = ConstantInt::get(M.getContext(), APInt(32, StringRef("0"), 10));
                vector<Constant*> const_ptr_5_indices;
                const_ptr_5_indices.push_back(const_int32_6);
                const_ptr_5_indices.push_back(const_int32_6);
                Constant* const_ptr_5 = ConstantExpr::getGetElementPtr(gvar_array__str, const_ptr_5_indices);

                for (Function::iterator fit = mit->begin(), fite = mit->end(); fit != fite; ++fit) {
                    bBuilder.SetInsertPoint(fit->getFirstInsertionPt());
                    bBuilder.CreateCall(callMerge, const_ptr_5);
                    for (BasicBlock::iterator iit = fit->begin(), iite = fit->end(); iit != iite; ++iit) {
                        string name = iit->getOpcodeName();
                        // whether it is the return instruction
                        if (name == "ret")
                            bBuilder1.SetInsertPoint(iit);
                        // branch instruciton?
                        else if (name == "br") {
                            BranchInst* branch = dyn_cast<BranchInst>(iit);
                            if (branch->isConditional()) {
                                Value* conditon = branch->getCondition();
                                bBuilder.SetInsertPoint(fit->getTerminator());
                                vector<Value*> transfer;
                                transfer.push_back(const_ptr_5);
                                transfer.push_back(conditon);
                                bBuilder.CreateCall(callTaken, transfer);
                            }
                        }
                    }
                }

                // if it is the main function, print
                if (mit->getName() == "main") {
                    bBuilder1.CreateCall(callPrint);
                }
            }
            
            return false;
        }
        static char ID;
    };
}
char BranchBias::ID = 0;
static RegisterPass<BranchBias> X("branch", "Count branch", false, false);