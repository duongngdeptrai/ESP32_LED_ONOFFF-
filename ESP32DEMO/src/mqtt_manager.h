#pragma once
#include <PubSubClient.h>

void reconnect(PubSubClient &client, const char* mqtt_user, const char* mqtt_pass);
