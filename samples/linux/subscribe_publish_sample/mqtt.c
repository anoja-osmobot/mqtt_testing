
#include "mqtt.h"



void iot_subscribe_callback_handler(AWS_IoT_Client *pClient, char *topicName, uint16_t topicNameLen,
									IoT_Publish_Message_Params *params, void *pData) {
	IOT_UNUSED(pData);
	IOT_UNUSED(pClient);
	IOT_INFO("Subscribe callback");
	IOT_INFO("%.*s\t%.*s", topicNameLen, topicName, (int) params->payloadLen, params->payload);
}

void disconnectCallbackHandler(AWS_IoT_Client *pClient, void *data) {
	IOT_WARN("MQTT Disconnect");
	IoT_Error_t rc = FAILURE;

	if(NULL == pClient) {
		return;
	}

	IOT_UNUSED(data);

	if(aws_iot_is_autoreconnect_enabled(pClient)) {
		IOT_INFO("Auto Reconnect is enabled, Reconnecting attempt will start now");
	} else {
		IOT_WARN("Auto Reconnect not enabled. Starting manual reconnect...");
		rc = aws_iot_mqtt_attempt_reconnect(pClient);
		if(NETWORK_RECONNECTED == rc) {
			IOT_WARN("Manual Reconnect Successful");
		} else {
			IOT_WARN("Manual Reconnect Failed - %d", rc);
		}
	}
}

    /*
     struct _Client {
     Timer pingTimer;
     Timer reconnectDelayTimer;

     ClientStatus clientStatus;
     ClientData clientData;
     Network networkStack;
     };

     typedef struct _Client AWS_IoT_Client;

     typedef struct {
     bool enableAutoReconnect;			///< Set to true to enable auto reconnect
     char *pHostURL;					///< Pointer to a string defining the endpoint for the MQTT service
     uint16_t port;					///< MQTT service listening port
     char *pRootCALocation;				///< Pointer to a string defining the Root CA file (full file, not path)
     char *pDeviceCertLocation;			///< Pointer to a string defining the device identity certificate file (full file, not path)
     char *pDevicePrivateKeyLocation;        	///< Pointer to a string defining the device private key file (full file, not path)
     uint32_t mqttPacketTimeout_ms;			///< Timeout for reading a complete MQTT packet. In milliseconds
     uint32_t mqttCommandTimeout_ms;			///< Timeout for MQTT blocking calls. In milliseconds
     uint32_t tlsHandshakeTimeout_ms;		///< TLS handshake timeout.  In milliseconds
     bool isSSLHostnameVerify;			///< Client should perform server certificate hostname validation
     iot_disconnect_handler disconnectHandler;	///< Callback to be invoked upon connection loss
     void *disconnectHandlerData;			///< Data to pass as argument when disconnect handler is called
     #ifdef _ENABLE_THREAD_SUPPORT_
     bool isBlockOnThreadLockEnabled;		///< Timeout for Thread blocking calls. Set to 0 to block until lock is obtained. In milliseconds
     #endif
     } IoT_Client_Init_Params;



     typedef struct {
     char struct_id[4];			///< The eyecatcher for this structure.  must be MQTC
     MQTT_Ver_t MQTTVersion;			///< Desired MQTT version used during connection
     char *pClientID;                	///< Pointer to a string defining the MQTT client ID (this needs to be unique \b per \b device across your AWS account)
     uint16_t clientIDLen;			///< Client Id Length. 16 bit unsigned integer
     uint16_t keepAliveIntervalInSec;	///< MQTT keep alive interval in seconds.  Defines inactivity time allowed before determining the connection has been lost.
     bool isCleanSession;			///< MQTT clean session.  True = this session is to be treated as clean.  Previous server state is cleared and no stated is retained from this connection.
     bool isWillMsgPresent;			///< Is there a LWT associated with this connection?
     IoT_MQTT_Will_Options will;		///< MQTT LWT parameters.
     char *pUsername;			///< Not used in the AWS IoT Service, will need to be cstring if used
     uint16_t usernameLen;			///< Username Length. 16 bit unsigned integer
     char *pPassword;			///< Not used in the AWS IoT Service, will need to be cstring if used
     uint16_t passwordLen;			///< Password Length. 16 bit unsigned integer
     } IoT_Client_Connect_Params;

     */
    /*
     typedef struct {
     QoS qos;		///< Message Quality of Service
     uint8_t isRetained;	///< Retained messages are \b NOT supported by the AWS IoT Service at the time of this SDK release.
     uint8_t isDup;		///< Is this message a duplicate QoS > 0 message?  Handled automatically by the MQTT client.
     uint16_t id;		///< Message sequence identifier.  Handled automatically by the MQTT client.
     void *payload;		///< Pointer to MQTT message payload (bytes).
     size_t payloadLen;	///< Length of MQTT payload.
     } IoT_Publish_Message_Params;
     */
