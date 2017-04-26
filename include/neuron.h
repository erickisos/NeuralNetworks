#ifndef NEURON_H
#define NEURON_H

#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    unsigned char name;
    unsigned char n_input;
    float output;
    float* weights;
} Neuron;

Neuron* Neuron_create(void);
void Neuron_init(Neuron* self, unsigned char name);
void Neuron_update_weights(Neuron* self);
void Neuron_set_weights(Neuron* self, float* weights, unsigned char size);
float Neuron_feed_forward(Neuron* self, float* inputs);
void Neuron_print(Neuron* self);

#endif
