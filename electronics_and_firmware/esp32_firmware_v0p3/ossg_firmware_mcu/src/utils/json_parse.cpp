#include "json_parse.hpp"
#include "cJSON.h"	
#include "esp_log.h"
#include "message_types.hpp"

static const char *TAG = "JSON";

JsonMessageParser::JsonMessageParser(char * jsonString) {     // Constructor
	messageTypesList = MessageTypes();
	JsonMessageParser::parseJson(jsonString);
}

JsonMessageParser::~JsonMessageParser() {     // Deconstructor
	//delete json object
	cJSON_Delete(jsonObj);
}

char * JsonMessageParser::getMessageType(){
	//get the type of the message
	messageType = getJsonKey(messageTypesList.MESSAGE_TYPE_LOCAL);

	return messageType;
}

char * JsonMessageParser::getJsonKey(const char * key){
	char * value;
	if (cJSON_GetObjectItem(jsonObj, key)) {
		value = cJSON_GetObjectItem(jsonObj, key)->valuestring;
	} else {
		value = (char *)"fuck";
	}
	return value;
}

//tester to make json object from scratch, not yet used
void JsonMessageParser::makeJson(){
	cJSON *root = cJSON_CreateObject();
	cJSON_AddStringToObject(root, "version", IDF_VER);
	cJSON_AddStringToObject(root, "cores", "test_core_num");
	cJSON_AddTrueToObject(root, "flag_true");
	cJSON_AddFalseToObject(root, "flag_false");

	//const char *my_json_string = cJSON_Print(root);
	char *my_json_string = cJSON_Print(root);
	//ESP_LOGI(TAG, "my_json_string\n%s",my_json_string);
	cJSON_Delete(root);
}

//take a string, parse as json, pull out the message type, which all message should have
void JsonMessageParser::parseJson(char * jsonString){
	//deserialize
	jsonObj = cJSON_Parse(jsonString);

	// char *parsedJsonString = cJSON_Print(jsonObj);
	// ESP_LOGI(TAG, "Parsed JSON string: %s", parsedJsonString);

	//clean up
	// cJSON_free(parsedJsonString); // Buffers returned by cJSON_Print must be freed by the caller.
}