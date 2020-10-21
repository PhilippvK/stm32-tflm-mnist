// This file is generated. Do not edit.
// Generated on: 21.10.2020 16:44:11

#ifndef mnist_GEN_H
#define mnist_GEN_H

#include "tensorflow/lite/c/common.h"

// Sets up the model with init and prepare steps.
TfLiteStatus mnist_init();
// Returns the input tensor with the given index.
TfLiteTensor *mnist_input(int index);
// Returns the output tensor with the given index.
TfLiteTensor *mnist_output(int index);
// Runs inference for the model.
TfLiteStatus mnist_invoke();

// Returns the number of input tensors.
inline size_t mnist_inputs() {
  return 1;
}
// Returns the number of output tensors.
inline size_t mnist_outputs() {
  return 1;
}

inline void *mnist_input_ptr(int index) {
  return mnist_input(index)->data.data;
}
inline size_t mnist_input_size(int index) {
  return mnist_input(index)->bytes;
}
inline int mnist_input_dims_len(int index) {
  return mnist_input(index)->dims->data[0];
}
inline int *mnist_input_dims(int index) {
  return &mnist_input(index)->dims->data[1];
}

inline void *mnist_output_ptr(int index) {
  return mnist_output(index)->data.data;
}
inline size_t mnist_output_size(int index) {
  return mnist_output(index)->bytes;
}
inline int mnist_output_dims_len(int index) {
  return mnist_output(index)->dims->data[0];
}
inline int *mnist_output_dims(int index) {
  return &mnist_output(index)->dims->data[1];
}

#endif
