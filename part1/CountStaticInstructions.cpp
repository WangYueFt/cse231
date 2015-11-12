#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/Support/raw_ostream.h"
#include <map>
#include <string>
using namespace llvm;
using namespace std;


namespace {
    class CountStaticInstructions : public ModulePass {
    public :
    
        CountStaticInstructions() : ModulePass(ID) {}
        virtual bool runOnModule(Module &M) {
            for (Module::iterator mit = M.begin(), mite = M.end(); mit != mite; ++mit) {
                for (Function::iterator fit = mit->begin(), fite = mit->end(); fit != fite; ++fit) {
                    for (BasicBlock::iterator iit = fit->begin(), iite = fit->end(); iit != iite; ++iit) {
                        //errs() << iit->getOpcodeName() << "\n";
                        map<string, int>::iterator entry = counter.find(iit->getOpcodeName());
                        if (entry == counter.end()) {
                            counter.insert(pair<string, int>(iit->getOpcodeName(), 1));
                        } else {
                            entry->second++;
                        }
                    }
                }   
            }
            return false;
        }   
    
        virtual void print(raw_ostream &O, const Module *M) const{
            int total = 0;
            for(map<string,int>::const_iterator it = counter.begin(); it != counter.end(); ++it) {
                O << it->first << ":" << it->second << "\n";
                total += it->second;
            }
            O << "Total" << ":" << total << "\n";
        }
        static char ID;
        map<string, int> counter;
    };
}
char CountStaticInstructions::ID = 0;
static RegisterPass<CountStaticInstructions> X("static", "Count Static Instructions", false, false);
