fn=$1
opt -analyze -load $LLVMLIB/CSE231.so -static < $1/${fn##*/}.bc | awk 'NR!=1'