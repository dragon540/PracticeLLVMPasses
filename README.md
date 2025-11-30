# LLVM Practice Passes

## How to build
1. `$ cd PracticeLLVMPasses`

2. `$ LLVM_INSTALL_DIR=/path_to_llvm_project/llvm-project/build/lib/cmake/llvm`

3. `$ cmake -DLLVM_INSTALL_DIR=$LLVM_INSTALL_DIR -S . -B build`

4. `$ cd build`

5. `$ make`

## How to run LLVM pass

1. `$ /path_to_llvm_opt_tool/-disable-output -load-pass-plugin build/lib/${PassName.so} -passes="${pass-name}" example.ll`

