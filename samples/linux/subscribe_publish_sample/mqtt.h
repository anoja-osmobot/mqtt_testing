#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

#include "aws_iot_config.h"
#include "aws_iot_log.h" // all Debug messages
#include "aws_iot_version.h"
#include "aws_iot_mqtt_client_interface.h"


char certDirectory[PATH_MAX + 1] = "../../../certs"; //Default cert location
char HostAddress[255] = AWS_IOT_MQTT_HOST; //Default MQTT HOST URL is pulled from the aws_iot_config.h
uint32_t port = AWS_IOT_MQTT_PORT; //Default MQTT port is pulled from the aws_iot_config.h


void iot_subscribe_callback_handler(AWS_IoT_Client *, char *, uint16_t ,
									IoT_Publish_Message_Params *, void *);
void disconnectCallbackHandler(AWS_IoT_Client *, void *);
