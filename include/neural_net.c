#include "neural_net.h"


NeuralNet* NeuralNet_create(void)
{
    return (NeuralNet*)malloc(sizeof(NeuralNet));
}

void NeuralNet_set_name(NeuralNet* self, char* name, unsigned char name_len)
{
    unsigned char i = 0;
    self->name = (char*)malloc(sizeof(char) * name_len);
    for(i = 0; i < name_len; i++)
    {
        self->name[i] = name[i];
    }
}

void NeuralNet_init(NeuralNet* self, char* name, unsigned char name_len, unsigned char neural_number)
{
    self->number_of_neurons = neural_number;
    self->number_of_connections = 0;
    NeuralNet_set_name(self, name, name_len);
    unsigned char i = 0;
    for(i = 0; i < self->number_of_neurons; i++)
    {
        self->neurons[i] = Neuron_create();
        self->neurons[i]->name = i;
    }
}

void NeuralNet_add_connection(NeuralNet* self, unsigned char neuron_1, unsigned char neuron_2)
{
    Connection* tmp_container = (Connection*)malloc(sizeof(Connection) * self->number_of_connections);
    unsigned char i = 0;
    for(i = 0; i < self->number_of_connections; i++)
    {
        tmp_container[i].origin = self->connections[i].origin;
        tmp_container[i].end = self->connections[i].end;
    }
    self->number_of_connections++;
    self->connections = (Connection*)malloc(sizeof(Connection) * self->number_of_connections);
    for(i = 0; i < self->number_of_connections - 1; i++)
    {
        self->connections[i].origin = tmp_container[i].origin;
        self->connections[i].end = tmp_container[i].end;
    }
    self->connections[self->number_of_connections - 1].origin = neuron_1;
    self->connections[self->number_of_connections - 1].end = neuron_2;
}

void NeuralNet_autosearch_inputs(NeuralNet* self)
{
    unsigned char i = 0, j = 0;
    unsigned char* input_votes = (unsigned char*)malloc(sizeof(unsigned char) * self->number_of_neurons);
    for(i = 0; i < self->number_of_neurons; i++)
    {
        input_votes[i] = 0;
    }
    for(i = 0; i < self->number_of_connections; i++)
    {
        input_votes[self->connections[i].end]++;
    }
    unsigned char counter = 0;
    for(i = 0; i < self->number_of_neurons; i++)
    {
        if(input_votes[i] == 0)
            counter++;
    }
    self->number_of_inputs = counter;
    self->inputs = (unsigned char*)malloc(sizeof(unsigned char) * counter);
    for(i = 0, j = 0; i < self->number_of_neurons; i++)
    {
        if(input_votes[i] == 0)
        {
            self->inputs[j] = i;
            j++;
        }
    }
    printf("Inputs:\n");
    for(i = 0; i < counter; i++)
    {
        printf("\t%d\n", self->inputs[i]);
    }
    free(input_votes);
}

void NeuralNet_autosearch_hiddens(NeuralNet* self)
{
    unsigned char i, j;
    unsigned char* hidden_votes_l = (unsigned char*)malloc(sizeof(unsigned char) * self->number_of_neurons);
    unsigned char* hidden_votes_r = (unsigned char*)malloc(sizeof(unsigned char) * self->number_of_neurons);
    for(i = 0; i < self->number_of_neurons; i++)
    {
        hidden_votes_l[i] = 0;
        hidden_votes_r[i] = 0;
    }
    for(i = 0; i < self->number_of_connections; i++)
    {
        hidden_votes_l[self->connections[i].origin]++;
        hidden_votes_r[self->connections[i].end]++;
    }
    unsigned char counter = 0;
    for(i = 0; i < self->number_of_neurons; i++)
    {
        if((hidden_votes_l[i] != 0) && (hidden_votes_r[i] != 0))
        {
            counter++;
        }
    }
    self->number_of_hiddens = counter;
    self->hidden = (unsigned char*)malloc(sizeof(unsigned char) * counter);
    for(i = 0, j = 0; i < self->number_of_neurons; i++)
    {
        if((hidden_votes_l[i] != 0) && (hidden_votes_r[i] != 0))
        {
            self->hidden[j] = i;
            j++;
        }
    }
    printf("Hiddens:\n");
    for(i = 0; i < counter; i++)
    {
        printf("\t%d\n", self->hidden[i]);
    }
}

void NeuralNet_autosearch_outputs(NeuralNet* self)
{
    unsigned char i, j;
    unsigned char* output_votes = (unsigned char*)malloc(sizeof(unsigned char) * self->number_of_neurons);
    for(i = 0; i < self->number_of_neurons; i++)
    {
        output_votes[i] = 0;
    }
    for(i = 0; i < self->number_of_connections; i++)
    {
        output_votes[self->connections[i].origin]++;
    }
    unsigned char counter = 0;
    for(i = 0; i < self->number_of_neurons; i++)
    {
        if(output_votes[i] == 0)
	{
            counter++;
	}
    }
    self->number_of_outputs = counter;
    self->outputs = (unsigned char*)malloc(sizeof(unsigned char) * counter);
    for(i = 0, j = 0; i < self->number_of_neurons; i++)
    {
        if(output_votes[i] == 0)
        {
            self->outputs[j] = i;
	    j++;
	}
    }
    printf("Outputs:\n");
    for(i = 0; i < counter; i++)
    {
        printf("\t%d\n", self->outputs[i]);
    }
}

void NeuralNet_set_inputs(NeuralNet* self, unsigned char* inputs, unsigned char inputs_length)
{
    self->inputs = (unsigned char*)malloc(sizeof(unsigned char) * inputs_length);
    unsigned char i = 0;
    for(i = 0; i < inputs_length; i++)
    {
        self->inputs[i] = inputs[i];
    }
}

void NeuralNet_set_hiddens(NeuralNet* self, unsigned char* inputs, unsigned char inputs_length)
{
    self->hidden = (unsigned char*)malloc(sizeof(unsigned char) * inputs_length);
    unsigned char i = 0;
    for(i = 0; i < inputs_length; i++)
    {
        self->hidden[i] = inputs[i];
    }
}

void NeuralNet_set_outputs(NeuralNet* self, unsigned char* inputs, unsigned char inputs_length)
{
    self->outputs = (unsigned char*)malloc(sizeof(unsigned char) * inputs_length);
    unsigned char i = 0;
    for(i = 0; i < inputs_length; i++)
    {
        self->outputs[i] = inputs[i];
    }
}

void NeuralNet_autoset_neurons(NeuralNet* self)
{
    unsigned char i, j;
    unsigned char* input_number = (unsigned char*)malloc(sizeof(unsigned char) * self->number_of_neurons);
    for(i = 0; i < self->number_of_neurons; i++)
    {
        input_number[i] = 0;
    }
    for(i = 0; i < self->number_of_connections; i++)
    {
        input_number[self->connections[i].end]++;
    }
    unsigned char counter = 0;
    float unary_weight[1] = {1.0};
    float* tmp_weights = (float*)malloc(sizeof(float) * self->number_of_neurons);
    for(i = 0; i < self->number_of_neurons; i++)
    {
        if(input_number[i] == 0)
	{
            Neuron_set_weights(self->neurons[i], unary_weight, 1);
	}
        else
        {
            tmp_weights = NeuralNet_randomized_weights(input_number[i]);
            Neuron_set_weights(self->neurons[i], tmp_weights, input_number[i]);
	    free(tmp_weights);
        }
    }
}

/* LA SIGUIENTE FUNCION ES TRABAJO EN PROGRESO */
float* NeuralNet_randomized_weights(unsigned char n)
{
    float* weights = (float*)malloc(sizeof(float) * n);
    return weights;
}

float* NeuralNet_feed_forward(NeuralNet* self, float inputs[])
{
    printf("Ni se si si esta entrando alv");
    unsigned char i = 0;
    printf("Iniciado NNet F");
    float* input_layer = (float*)malloc(sizeof(float) * self->number_of_inputs);
    float* hidden_layer = (float*)malloc(sizeof(float) * self->number_of_hiddens);
    printf("Asignados los espacios de memoria de las capas");
    for(i = 0; i < self->number_of_inputs; i++)
    {
        input_layer[i] = 0;
        printf("Llamando al feed_forward de la neurona %d", i);
        Neuron_feed_forward(self->neurons[self->inputs[i]], &inputs[i]);
        input_layer[i] = self->neurons[self->inputs[i]]->output;
    }
    for(i = 0; i < self->number_of_hiddens; i++)
    {
        hidden_layer[i] = 0;
        Neuron_feed_forward(self->neurons[self->hidden[i]], input_layer);
        hidden_layer[i] = self->neurons[self->inputs[i]]->output;
    }
    for(i = 0; i < self->number_of_outputs; i++)
    {
        self->output_values[i] = 0;
        Neuron_feed_forward(self->neurons[self->outputs[i]], hidden_layer);
        self->output_values[i] = self->neurons[self->outputs[i]]->output;
    }
    float* results = self->output_values;
    return results;
}

void NeuralNet_print_conections(NeuralNet* self)
{
    unsigned char i = 0;
    printf("Conections of net: %s\n", self->name);
    for(i = 0; i < self->number_of_connections; i++)
    {
        printf("\t%d, %d\n", self->connections[i].origin, self->connections[i].end);
    }
}

void NeuralNet_print_net(NeuralNet* self)
{
    unsigned char i = 0;
    printf("NeuralNet Object {%s}: \n", self->name);
    for(i = 0; i < self->number_of_neurons; i++)
    {
        Neuron_print(self->neurons[i]);
    }
}

void NeuralNet_print_output(NeuralNet* self)
{
    printf("Net {%s} output:\n", self->name);
    unsigned char i = 0;
    for(i = 0; i < self->number_of_outputs; i++)
    {
        printf("\t%f\n", self->output_values[i]);
    }
}
