# External Projects

This directory contains Git Submodules to optional Dependencies.

Do use the external projects make sure to run `git submodule update --init --recursive` first.


## TFLite Mirco Compiler

Set `SET(ENABLE_TFLM_COMPILER ON)` after `FIND_PACKAGE(TFLite REQUIRED)` to

If providing `TF_SRC` manually, also make sure to run `tensorflow/lite/tools/make/download_dependencies.sh` before trying to use the custom target `make convert`.

### Usage

To convert a `model.tflite` file to an `offline_model.cc` run the following in your `build` directory:

```
make convert FILE=model.tflite
```
