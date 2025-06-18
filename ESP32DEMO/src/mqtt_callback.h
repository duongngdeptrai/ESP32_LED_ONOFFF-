#pragma once
#include <PubSubClient.h>

void mqtt_callback(char* topic, byte* payload, unsigned int length);
