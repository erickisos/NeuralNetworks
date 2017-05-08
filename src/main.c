#include <neuron.h>
#include <neural_net.h>
#include <stdio.h>
#include <stdlib.h>


float w[] = {1};//{-0.32};
float ww[] = {1};
float www[] = {1};
float wwww[] = {1};
float wwwww[] = {1};
float w_5[] = {-0.0023, 10.23, -0.0123, 0.45, 0.98213};
float ww_5[] = {123.32, -0.2345, 2.21004, 0.00910054, -12.987};
float www_5[] = {0, .12, -0.32, 0.1234, -12.654};
float w_3[] = {0.123, -0.0023, -3.54};
float ww_3[] = {6.53, -0.2365, -12.482307};
float test[] = {1, -1, 1, -1, 1};

int main(int argc, char** argv)
{
    NeuralNet* net = NeuralNet_create();
    NeuralNet_init(net, "test", 4, 10);
    NeuralNet_add_connection(net, 0, 5);
    NeuralNet_add_connection(net, 0, 6);
    NeuralNet_add_connection(net, 0, 7);
    NeuralNet_add_connection(net, 1, 5);
    NeuralNet_add_connection(net, 1, 6);
    NeuralNet_add_connection(net, 1, 7);
    NeuralNet_add_connection(net, 2, 5);
    NeuralNet_add_connection(net, 2, 6);
    NeuralNet_add_connection(net, 2, 7);
    NeuralNet_add_connection(net, 3, 5);
    NeuralNet_add_connection(net, 3, 6);
    NeuralNet_add_connection(net, 3, 7);
    NeuralNet_add_connection(net, 4, 5);
    NeuralNet_add_connection(net, 4, 6);
    NeuralNet_add_connection(net, 4, 7);
    NeuralNet_add_connection(net, 5, 8);
    NeuralNet_add_connection(net, 5, 9);
    NeuralNet_add_connection(net, 6, 8);
    NeuralNet_add_connection(net, 6, 9);
    NeuralNet_add_connection(net, 7, 8);
    NeuralNet_add_connection(net, 7, 9);
    NeuralNet_print_conections(net);
    NeuralNet_autosearch_inputs(net);
    NeuralNet_autosearch_hiddens(net);
    NeuralNet_autosearch_outputs(net);
    NeuralNet_autoset_neurons(net);

    Neuron_set_weights(net->neurons[5], w_5, 5);
    Neuron_set_weights(net->neurons[6], ww_5, 5);
    Neuron_set_weights(net->neurons[7], www_5, 5);

    Neuron_set_weights(net->neurons[8], w_3, 3);
    Neuron_set_weights(net->neurons[9], ww_3, 3);

    NeuralNet_print_net(net);


    Neuron* a = Neuron_create();
    Neuron* b = Neuron_create();
    Neuron* c = Neuron_create();
    Neuron* d = Neuron_create();
    Neuron* e = Neuron_create();
    Neuron* f = Neuron_create();
    Neuron* g = Neuron_create();
    Neuron* h = Neuron_create();
    Neuron* i = Neuron_create();
    Neuron* j = Neuron_create();

    Neuron_init(a, 1);
    Neuron_init(b, 2);
    Neuron_init(c, 3);
    Neuron_init(d, 4);
    Neuron_init(e, 5);
    Neuron_init(f, 6);
    Neuron_init(g, 7);
    Neuron_init(h, 8);
    Neuron_init(i, 9);
    Neuron_init(j, 10);
    Neuron_set_weights(a, w, 1);
    Neuron_set_weights(b, ww, 1);
    Neuron_set_weights(c, www, 1);
    Neuron_set_weights(d, wwww, 1);
    Neuron_set_weights(e, wwwww, 1);
    Neuron_set_weights(f, w_5, 5);
    Neuron_set_weights(g, ww_5, 5);
    Neuron_set_weights(h, www_5, 5);
    Neuron_set_weights(i, w_3, 3);
    Neuron_set_weights(j, ww_3, 3);

    printf("\n====  ====\n");

    Neuron_print(a);
    Neuron_print(b);
    Neuron_print(c);
    Neuron_print(d);
    Neuron_print(e);
    Neuron_print(f);
    Neuron_print(g);
    Neuron_print(h);
    Neuron_print(i);
    Neuron_print(j);

    Neuron_feed_forward(a, &test[0]);
    Neuron_feed_forward(b, &test[1]);
    Neuron_feed_forward(c, &test[2]);
    Neuron_feed_forward(d, &test[3]);
    Neuron_feed_forward(e, &test[4]);
    float out_layer1[] = {
        a->output,
        b->output,
        c->output,
        d->output,
        e->output
    };
    Neuron_feed_forward(f, out_layer1);
    Neuron_feed_forward(g, out_layer1);
    Neuron_feed_forward(h, out_layer1);
    float out_layer2[] = {
        f->output,
        g->output,
        h->output
    };
    Neuron_feed_forward(i, out_layer2);
    Neuron_feed_forward(j, out_layer2);
    printf("La salida de la red neuronal es: %f, %f\n", i->output, j->output);

    /*
     * Pruebas del feed forward
    

    unsigned char uchar_i = 0;
    float input_layer[net->number_of_inputs]; //(float*)malloc(sizeof(float) * net->number_of_inputs);
    float hidden_layer[net->number_of_hiddens]; //(float*)malloc(sizeof(float) * net->number_of_hiddens);
    printf("Capas: %d, %d, %d\n", net->number_of_inputs, net->number_of_hiddens, net->number_of_outputs);
    printf("Reservados los espacios de memoria en las capas");
    for(uchar_i = 0; uchar_i < net->number_of_inputs; uchar_i++)
    {
        input_layer[uchar_i] = 0;
        printf("\n\tLlamando al feed forward de la neurona %d", uchar_i);
        input_layer[uchar_i] = Neuron_feed_forward(net->neurons[net->inputs[uchar_i]], &test[uchar_i]);
    }
    printf("\nLlamando feed forwards a mano\n");
    printf("Number of neurons: %d", net->number_of_neurons);
    printf("\nhidden 0\n");
    hidden_layer[0] = Neuron_feed_forward(net->neurons[5], input_layer);
    printf("\nhidden 1\n");
    hidden_layer[1] = Neuron_feed_forward(net->neurons[6], input_layer);
    printf("\nhidden 2\n");
    hidden_layer[2] = Neuron_feed_forward(net->neurons[7], input_layer);
    printf("Number_of_outputs: %d", net->number_of_outputs);
    printf("\noutput 0\n");
    net->output_values[0] = Neuron_feed_forward(net->neurons[8], hidden_layer);
    printf("\noutput 1\n");
    net->output_values[1] = Neuron_feed_forward(net->neurons[9], hidden_layer);
    printf("\nAcabdo el amano\n");
    
     * Aqui termina el feed forward
     */

    //NeuralNet_feed_forward(net, test);

    //NeuralNet_print_output(net);
    return 0;
}
