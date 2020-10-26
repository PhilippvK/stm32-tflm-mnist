/*
    Copyright 2020 <TODO>

    See `models/README.md` for details!
==============================================================================*/

// This is a standard TensorFlow Lite model file that has been converted into a
// C data array, so it can be easily compiled into a binary for devices that
// don't have a file system. It was created using the command:
// xxd -i sine_model.tflite > sine_model_data.cc (TODO)

#ifndef SRC_MODEL_DATA_H_
#define SRC_MODEL_DATA_H_

extern const unsigned char model_data_tflite[];
extern const unsigned int model_data_tflite_len;

#endif  // SRC_MODEL_DATA_H_
