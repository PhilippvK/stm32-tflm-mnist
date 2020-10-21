## Compiler Models

Find out more about the compiler [HERE](https://github.com/tum-ei-eda/tflite_micro_compiler)!

The following commands were used to generate the compiler models:

```
compiler other/MNIST_full_quanitization.tflite compiler/offline_model.cc mnist_
mv compiler/offline_model.cc.h compiler/offline_model.h
```

In the end, replace `Src/offline_model.cc/h` with the generated files! 
