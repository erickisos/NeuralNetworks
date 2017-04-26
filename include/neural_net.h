#ifndef NEURAL_NET_H
#define NEURAL_NET_H

#include "neuron.h"

#define MAX_NEURONS 100


typedef struct
{
    unsigned char origin;
    unsigned char end;
} Connection;

typedef struct
{
    unsigned char number_of_neurons;
    unsigned char number_of_connections;
    unsigned char number_of_inputs;
    unsigned char number_of_hiddens;
    unsigned char number_of_outputs;
    Connection* connections;
    unsigned char* inputs;
    unsigned char* hidden;
    unsigned char* outputs;
    float* output_values;
    char* name;
    Neuron* neurons[MAX_NEURONS];
} NeuralNet;

NeuralNet* NeuralNet_create(void);
void NeuralNet_set_name(NeuralNet* self, char* name, unsigned char name_len);
void NeuralNet_init(NeuralNet* self, char* name, unsigned char name_len, unsigned char neural_number);
void NeuralNet_add_connection(NeuralNet* self, unsigned char neuron_1, unsigned char neuron_2);
void NeuralNet_autosearch_inputs(NeuralNet* self);
void NeuralNet_autosearch_hiddens(NeuralNet* self);
void NeuralNet_autosearch_outputs(NeuralNet* self);
void NeuralNet_autoset_neurons(NeuralNet* self);
void NeuralNet_set_inputs(NeuralNet* self, unsigned char* inputs, unsigned char inputs_length);
void NeuralNet_set_hiddens(NeuralNet* self, unsigned char* inputs, unsigned char inputs_length);
void NeuralNet_set_outputs(NeuralNet* self, unsigned char* inputs, unsigned char inputs_length);
void NeuralNet_autoset_neurons(NeuralNet* self);
void NeuralNet_feed_forward(NeuralNet* self, float* inputs);
void NeuralNet_print_conections(NeuralNet* self);
void NeuralNet_print_net(NeuralNet* self);
void NeuralNet_print_output(NeuralNet* self);
float* NeuralNet_randomized_weights(unsigned char n);

#endif