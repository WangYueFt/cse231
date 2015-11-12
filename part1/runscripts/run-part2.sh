fn=$1
CPPFLAGS=`llvm-config --cppflags`
LLVMLIBS=`llvm-config --libs`
LDFLAGS=`llvm-config --ldflags`
clang $CPPFLAGS -O0 -emit-llvm -c /cse231/llvm/src/lib/CSE231/helper/dynamic.cpp -o /cse231/llvm/src/lib/CSE231/helper/dynamic.bc
opt -load $LLVMLIB/CSE231.so -dynamic < $1/${fn##*/}.bc > $1/${fn##*/}.opt.bc

llvm-link $1/${fn##*/}.opt.bc /cse231/llvm/src/lib/CSE231/helper/dynamic.bc -o $1/${fn##*/}.linked.bc
llc -filetype=obj $1/${fn##*/}.linked.bc -o=$1/${fn##*/}.o
g++  $1/${fn##*/}.o $LLVMLIBS $LDFLAGS -o $1/${fn##*/}.exe
cd $1
$1/${fn##*/}.exe