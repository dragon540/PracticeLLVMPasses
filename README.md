# LLVM Practice Passes

This repository contains LLVM passes to perform constant folding, replacing multiply with left shift, replacing division with right shift, dead code elimination, and tail call optimization.

These middle-end compiler optimization passes are written for the purpose of learning LLVM.

## How to build
```
$ cd PracticeLLVMPasses
$ LLVM_INSTALL_DIR=/path_to_llvm_project/llvm-project/build/lib/cmake/llvm
$ cmake -DLLVM_INSTALL_DIR=$LLVM_INSTALL_DIR -S . -B build
$ cd build
$ make
```

## How to run LLVM pass

```
$ /path_to_llvm_opt_tool/-disable-output -load-pass-plugin build/lib/${PassName.so} -passes="${pass-name}" example.ll
```

