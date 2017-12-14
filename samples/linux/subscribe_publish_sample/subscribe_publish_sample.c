#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

#include "mqtt.h"
//void Init_Client_Connect_Params(IoT_Client_Init_Params *,IoT_Client_Connect_Params *);
/**
 * @brief This parameter will avoid infinite loop of publish and exit the program after certain number of publishes
 */
uint32_t publishCount = 0;

/*
 *   Find the location of certificates, any changes to certificates will automatically be updated
 *   initialize MQTT Client Parameters
*/
//void Init_Client_Connect_Params(IoT_Client_Init_Params* mqttInitParams, IoT_Client_Connect_Params* connectParams){

//}


int main(int argc, char **argv) {
	//bool infinitePublishFlag = true;
	IoT_Error_t rc = FAILURE;
	AWS_IoT_Client client;
	IoT_Client_Init_Params mqttInitParams = iotClientInitParamsDefault;
	IoT_Client_Connect_Params connectParams = iotClientConnectParamsDefault;
	IoT_Publish_Message_Params paramsQOS0;
	paramsQOS0.qos = QOS0;
	paramsQOS0.isRetained = 0;
	char cPayload[100];
	paramsQOS0.payload = (void *) cPayload;
	char rootCA[PATH_MAX + 1];
  char clientCRT[PATH_MAX + 1];
  char clientKey[PATH_MAX + 1];
  char CurrentWD[PATH_MAX + 1];
  getcwd(CurrentWD, sizeof(CurrentWD));
  // Find the location of certificates, any changes to certificates will automatically be updated
  //appending and creating path dynamically
	snprintf(rootCA, PATH_MAX + 1, "%s/%s/%s", CurrentWD, certDirectory, AWS_IOT_ROOT_CA_FILENAME);
	snprintf(clientCRT, PATH_MAX + 1, "%s/%s/%s", CurrentWD, certDirectory, AWS_IOT_CERTIFICATE_FILENAME);
	snprintf(clientKey, PATH_MAX + 1, "%s/%s/%s", CurrentWD, certDirectory, AWS_IOT_PRIVATE_KEY_FILENAME);
  /*
    IOT_INFO("\nAWS IoT SDK Version %d.%d.%d-%s\n", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_TAG);
  	IOT_DEBUG("rootCA %s", rootCA);
  	IOT_DEBUG("clientCRT %s", clientCRT);
  	IOT_DEBUG("clientKey %s", clientKey);
   */
  mqttInitParams.enableAutoReconnect = false; // We enable this later below
	mqttInitParams.pHostURL = HostAddress;
	mqttInitParams.port = port;
	mqttInitParams.pRootCALocation = rootCA;
	mqttInitParams.pDeviceCertLocation = clientCRT;
	mqttInitParams.pDevicePrivateKeyLocation = clientKey;
	mqttInitParams.mqttCommandTimeout_ms = 20000;
	mqttInitParams.tlsHandshakeTimeout_ms = 5000;
	mqttInitParams.isSSLHostnameVerify = true;
	//mqttInitParams.disconnectHandler = disconnectCallbackHandler;
	mqttInitParams.disconnectHandlerData = NULL;

  connectParams.keepAliveIntervalInSec = 600;
  connectParams.isCleanSession = true;
  connectParams.MQTTVersion = MQTT_3_1_1;
  connectParams.pClientID = AWS_IOT_MQTT_CLIENT_ID;
  connectParams.clientIDLen = (uint16_t) strlen(AWS_IOT_MQTT_CLIENT_ID);
  connectParams.isWillMsgPresent = false;
	//Init_Client_Connect_Params(&mqttInitParams,&connectParams);

	//int32_t i = 0;

	rc = aws_iot_mqtt_init(&client, &mqttInitParams);
	if(SUCCESS != rc) {
		IOT_ERROR("aws_iot_mqtt_init returned error : %d ", rc);
		return rc;
	}

	//IOT_INFO("Connecting...");
	rc = aws_iot_mqtt_connect(&client, &connectParams);
	if(SUCCESS != rc) {
		IOT_ERROR("Error(%d) connecting to %s:%d", rc, mqttInitParams.pHostURL, mqttInitParams.port);
		return rc;
	}
	/*
	 * Enable Auto Reconnect functionality. Minimum and Maximum time of Exponential backoff are set in aws_iot_config.h
	 *  #AWS_IOT_MQTT_MIN_RECONNECT_WAIT_INTERVAL
	 *  #AWS_IOT_MQTT_MAX_RECONNECT_WAIT_INTERVAL
	 */
	rc = aws_iot_mqtt_autoreconnect_set_status(&client, true);
	if(SUCCESS != rc) {
		IOT_ERROR("Unable to set Auto Reconnect to true - %d", rc);
		return rc;
	}
/*
	IOT_INFO("Subscribing...");
	rc = aws_iot_mqtt_subscribe(&client, "sdkTest/sub", 11, QOS0, iot_subscribe_callback_handler, NULL);
  rc = aws_iot_mqtt_subscribe(&client, "device-reading", 11, QOS0, iot_subscribe_callback_handler, NULL);
  rc = aws_iot_mqtt_subscribe(&client, "osmobot/nonurgent/firmwareupdate", 11, QOS0, iot_subscribe_callback_handler, NULL);
	//use switch function to categorize server msg
	if(SUCCESS != rc) {
		IOT_ERROR("Error subscribing : %d ", rc);
		return rc;
	}

	//sprintf(cPayload, "%s : %d ", "hello from SDK", i);

	if(publishCount != 0) {
		infinitePublishFlag = false;
	}

	while((NETWORK_ATTEMPTING_RECONNECT == rc || NETWORK_RECONNECTED == rc || SUCCESS == rc)
		  && (publishCount > 0 || infinitePublishFlag)) {

		//Max time the yield function will wait for read messages
		rc = aws_iot_mqtt_yield(&client, 100);
		if(NETWORK_ATTEMPTING_RECONNECT == rc) {
			// If the client is attempting to reconnect we will skip the rest of the loop.
			continue;
		}
*/
		IOT_INFO("-->sleep");
		sleep(1);
		sprintf(cPayload, "%s", "{ \"nodeId\" : 12345678, \"hexString\" : \"010101394e61bc01ffffffff000001ffffffffffffffff000036010000b80200000000000000000000000000009104aa0174018c01ea034201360144010000000000000000e4036a0134014a0100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001\" }");
    paramsQOS0.payloadLen = strlen(cPayload);
    rc = aws_iot_mqtt_publish(&client, "device-reading", 14, &paramsQOS0);
		/*if(publishCount > 0) {
			publishCount--;
		}

		if(publishCount == 0 && !infinitePublishFlag) {
			break;
		}*/
	//}
/*
	// Wait for all the messages to be received
	aws_iot_mqtt_yield(&client, 100);

	if(SUCCESS != rc) {
		IOT_ERROR("An error occurred in the loop.\n");
	} else {
		IOT_INFO("Publish done\n");
	}
*/
	return rc;
}
