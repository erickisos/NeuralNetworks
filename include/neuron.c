#include "neuron.h"

Neuron* Neuron_create(void)
{
  return (Neuron*)malloc(sizeof(Neuron));
}

void Neuron_init(Neuron* self, unsigned char name)
{
    self->name = name;
    self->output = 0;
    self->n_input = 1;
    Neuron_update_weights(self);
}

void Neuron_update_weights(Neuron* self)
{
    self->weights = (float*)malloc(sizeof(float) * self->n_input);
}

void Neuron_set_weights(Neuron* self, float* weights, unsigned char size)
{
    if(self->n_input != size)
    {
        self->n_input = size;
    }
    Neuron_update_weights(self);
    unsigned char i = 0;
    for(i = 0; i < size; i++)
    {
        self->weights[i] = weights[i];
    }
}

float Neuron_feed_forward(Neuron* self, float* inputs)
{
    self->output = 0.0;
    unsigned char i = 0;
    for(i = 0; i < self->n_input; i++)
    {
        self->output = self->output + (float)self->weights[i] * inputs[i];
    }
    return self->output;
}

void Neuron_print(Neuron* self)
{
    unsigned char i = 0;
    printf("Neuron Object {%d} < Dendritas: %d >: \n", self->name, self->n_input);
    printf("\tWeights: ");
    for(i = 0; i < self->n_input; i++)
    {
        printf("%f ", self->weights[i]);
    }
    printf("\n");
}
