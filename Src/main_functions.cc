/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

Modifications by @PhilippvK:
- Change for MNIST example
- Formatted according to cpplint
- Removed Prefix from Includes
- Support tflite_micro_compiler by defining `TFLM_MODE_COMPILER`
  See: https://github.com/tum-ei-eda/tflite_micro_compiler
- Support Benchmarking by defining `BENCHMARKING`
  See: https://github.com/PhilippvK/stm32-tflm-benchmarking

==============================================================================*/

#ifdef TFLM_MODE_COMPILER
#include "tensorflow/lite/c/common.h"
#include "tensorflow/lite/kernels/internal/tensor_ctypes.h"
#include "offline_model.h"
#else
#include "tensorflow/lite/micro/kernels/micro_ops.h"
#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"
#ifdef MEMORY_REPORTING
#include "tensorflow/lite/micro/recording_micro_interpreter.h"
#else
#include "tensorflow/lite/micro/micro_interpreter.h"
#endif /* MEMORY_REPORTING */
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/version.h"
#include "model_data.h"
#endif /* TFLM_MODE_COMPILER */

#include "main_functions.h"

// TODO(PhilippvK): move somewhere else
#include "misc.h"

#ifdef BENCHMARKING
#include "benchmarking.h"
#endif /* BENCHMARKING */

// Globals, used for compatibility with Arduino-style sketches.
namespace {
  tflite::ErrorReporter *error_reporter = nullptr;
#ifndef TFLM_MODE_COMPILER
  const tflite::Model *model = nullptr;
#ifdef MEMORY_REPORTING
  tflite::RecordingMicroInterpreter* interpreter = nullptr;
#else
  tflite::MicroInterpreter* interpreter = nullptr;
#endif /* MEMORY_REPORTING */
  TfLiteTensor *input = nullptr;
  TfLiteTensor *output = nullptr;

  // Create an area of memory to use for input, output, and intermediate arrays.
  // Finding the minimum value for your model may require some trial and error.
  constexpr int kTensorArenaSize = 16 * 1024;
  uint8_t tensor_arena[kTensorArenaSize];
#endif /* TFLM_MODE_COMPILER */
  int inference_count = 0;

}  // namespace

// The name of this function is important for Arduino compatibility.
void setup() {
  // Set up logging. Google style is to avoid globals or statics because of
  // lifetime uncertainty, but since this has a trivial destructor it's okay.
  // NOLINTNEXTLINE(runtime-global-variables)
  static tflite::MicroErrorReporter micro_error_reporter;
  error_reporter = &micro_error_reporter;

#ifdef TFLM_MODE_COMPILER
  mnist_init();
#else
  // Map the model into a usable data structure. This doesn't involve any
  // copying or parsing, it's a very lightweight operation.
  model = tflite::GetModel(model_data_tflite);
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    error_reporter->Report(
      "Model provided is schema version %d not equal "
      "to supported version %d.",
      model->version(), TFLITE_SCHEMA_VERSION);
    return;
  }

    static tflite::MicroMutableOpResolver<6> resolver;
    resolver.AddConv2D();
    resolver.AddMaxPool2D();
    resolver.AddReshape();
    resolver.AddFullyConnected();
    resolver.AddSoftmax();

  // Build an interpreter to run the model with.
#ifdef MEMORY_REPORTING
  static tflite::RecordingMicroInterpreter static_interpreter(model, resolver,
                 tensor_arena,
                 kTensorArenaSize,
                 error_reporter);
#else
  static tflite::MicroInterpreter static_interpreter(model, resolver,
                 tensor_arena,
                 kTensorArenaSize,
                 error_reporter);
#endif /* MEMORY_REPORTING */
  interpreter = &static_interpreter;

  // Allocate memory from the tensor_arena for the model's tensors.
  TfLiteStatus allocate_status = interpreter->AllocateTensors();
  if (allocate_status != kTfLiteOk) {
    error_reporter->Report("AllocateTensors() failed");
    return;
  }

  // Obtain pointers to the model's input and output tensors.
  input = interpreter->input(0);
  output = interpreter->output(0);
#endif /* TFLM_MODE_COMPILER */

  // Keep track of how many inferences we have performed.
  inference_count = 0;

  // Prepare Screen
  DrawInputBox();
#ifndef FAKE_TOUCH
  PrintMNISTHint();
#endif /* FAKE_TOUCH */
}

// The name of this function is important for Arduino compatibility.
void loop() {
  static TfLiteStatus invoke_status;

  MNISTReset();
#ifndef FAKE_TOUCH
  while (!GetTouchInput()) {}
#endif /* FAKE_TOUCH */
#ifdef BENCHMARKING
  uint32_t ticks_before, ticks_after;
  ticks_before = HAL_GetTick();
#endif /* BENCHMARKING */
  fprintf(stderr, "Save image\n\r");
  SaveMNISTInput();
  // Place our calculated x value in the model's input tensor
  for (uint32_t i = 0; i < INPUT_IMAGE_SIZE * INPUT_IMAGE_SIZE; i++) {
#ifdef TFLM_MODE_COMPILER
    tflite::GetTensorData<int8_t>(mnist_input(0))[0] = (MNISTGetNNInputImage()[i]/2)-127;
#else
    input->data.int8[i] = (int8_t)(MNISTGetNNInputImage()[i]/2)-127;
#endif /* TFLM_MODE_COMPILER */
  }
#ifdef BENCHMARKING
  ticks_after = HAL_GetTick();
  update_avg_ticks(TICKS_POPULATE, (int32_t)(ticks_after-ticks_before));
#endif /* BENCHMARKING */

  // Run inference, and report any error
#ifdef BENCHMARKING
  ticks_before = HAL_GetTick();
#endif /* BENCHMARKING */
#ifdef TFLM_MODE_COMPILER
  hello_world_invoke();
#else
  invoke_status = interpreter->Invoke();
  if (invoke_status != kTfLiteOk) {
    error_reporter->Report("Invoke failed");
  }
#endif /* TFLM_MODE_COMPILER */
#ifdef BENCHMARKING
  ticks_after = HAL_GetTick();
  update_avg_ticks(TICKS_INVOKE, (int32_t)(ticks_after-ticks_before));
#endif /* BENCHMARKING */

#ifdef BENCHMARKING
  ticks_before = HAL_GetTick();
#endif /* BENCHMARKING */
#ifdef TFLM_MODE_COMPILER
  int8_t* output_array = tflite::GetTensorData<int8_t>(mnist_output(0))[0];;
#else
  int8_t* output_array = output->data.int8;
#endif /* TFLM_MODE_COMPILER */
#ifdef MEMORY_REPORTING
  // Print out detailed allocation information:
  interpreter->GetMicroAllocator().PrintAllocations();
#endif /* MEMORY_REPORTING */

  MNISTHandleOutput(output_array);
#ifdef BENCHMARKING
  ticks_after = HAL_GetTick();
  update_avg_ticks(TICKS_RESPOND, (int32_t)(ticks_after-ticks_before));
#endif /* BENCHMARKING */
}
