//
// Created by mahon on 1/4/2024.
//

#ifndef ADAPTER2_GAS_MIXER_CLIENT_H
#define ADAPTER2_GAS_MIXER_CLIENT_H

#include "gas_data.h"
#include "gas_sensor.h"

typedef struct gas_mixer_client {
    // private data of gas_mixer hardware... here
    //

    gas_data_t data;
    callback_fn fn_handler;

} gas_mixer_client_t;

void gas_mixer_client_init(gas_mixer_client_t* me);
void gas_mixer_client_cleanup(gas_mixer_client_t* me);
gas_mixer_client_t* gas_mixer_client_create();
void gas_mixer_client_destroy(gas_mixer_client_t* me);

void gas_mixer_client_handle_new_data(void* me,gas_data_t data);
void gas_mixer_client_subcribe(gas_mixer_client_t* me, gas_sensor_t* const gas_sensor);
void gas_mixer_client_unsubcribe(gas_mixer_client_t* me, gas_sensor_t* const gas_sensor);

#endif //ADAPTER2_GAS_MIXER_CLIENT_H
