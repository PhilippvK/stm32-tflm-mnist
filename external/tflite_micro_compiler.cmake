# CMake Module to Build and Run the TFLite Micro Compiler
#
# Further Information: https://github.com/cpetig/tflite_micro_compiler

INCLUDE(ExternalProject)

IF(NOT TF_SRC)
  MESSAGE(FATAL_ERROR "TF_SRC is not defined!")
ENDIF()

IF(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/external/tflite_micro_compiler/src")
  MESSAGE(FATAL_ERROR "Submodule `external/tflite_micro_compiler` not checked out!"
    "Please run `git submodule update --init --recursive`!")
ENDIF()

IF(NOT EXISTS "${TF_SRC}/tensorflow/lite/tools/make/downloads")
  MESSAGE(FATAL_ERROR "TFLM dependencies missing. Please run:"
    "${TF_SRC}/tensorflow/lite/tools/make/download_dependencies.sh")
ENDIF()

EXTERNALPROJECT_ADD(tflm_compiler
  PREFIX tflm_compiler
  SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/tflite_micro_compiler"
  INSTALL_COMMAND cmake -E echo "Skipping install step."
  CMAKE_CACHE_ARGS
    -DTF_DIR:PATH=${TF_SRC}
)

SET(TFLM_COMPILER_EXECUTABLE ${CMAKE_CURRENT_BINARY_DIR}/tflm_compiler/src/tflm_compiler-build/compiler)

IF(${TFLM_MODE} STREQUAL compiler)
  ADD_DEFINITIONS(-DTFLM_MODE_COMPILER)
ENDIF()

SET(TFLM_COMPILER_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/Src/")

# Run `make convert FILE=models/other/model.tflite` to generate `Src/offline_model.cc`
ADD_CUSTOM_TARGET(
  convert
  COMMAND test ! -z $$FILE || (echo 'Please define .tflite file using `make convert FILE=...`' && false)
  COMMAND ${TFLM_COMPILER_EXECUTABLE} $$FILE ${TFLM_COMPILER_OUTPUT_DIRECTORY}/offline_model.cc ${TFLM_EXAMPLE}_
  COMMAND mv ${TFLM_COMPILER_OUTPUT_DIRECTORY}/offline_model.cc.h ${TFLM_COMPILER_OUTPUT_DIRECTORY}/offline_model.h
)

ADD_DEPENDENCIES(convert tflm_compiler)
