cmake_minimum_required(VERSION 2.6)
project(neuron C)

include_directories(include)

add_library(neuron_object SHARED
  include/neuron.h
  include/neuron.c
)
add_library(neuralnet_object SHARED
  include/neural_net.h
  include/neural_net.c
)

add_executable(neuron_test src/main.c)
target_link_libraries(neuron_test neuron_object neuralnet_object)