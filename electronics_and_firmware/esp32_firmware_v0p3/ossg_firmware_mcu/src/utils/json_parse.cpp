#include "cJSON.h"	
#include "esp_log.h"
#include "../include/message_types.h"

static const char *TAG = "JSON";

void makeJson(){
	cJSON *root = cJSON_CreateObject();
	cJSON_AddStringToObject(root, "version", IDF_VER);
	cJSON_AddStringToObject(root, "cores", "test_core_num");
	cJSON_AddTrueToObject(root, "flag_true");
	cJSON_AddFalseToObject(root, "flag_false");

	//const char *my_json_string = cJSON_Print(root);
	char *my_json_string = cJSON_Print(root);
	ESP_LOGI(TAG, "my_json_string\n%s",my_json_string);
	cJSON_Delete(root);
}

void parseJson(char * jsonString){
	ESP_LOGI(TAG, "Deserialize.....");
    MessageTypes myMessageTypes = MessageTypes();
	ESP_LOGI(TAG, "Go message types.....");
	cJSON *jsonObj = cJSON_Parse(jsonString);
	ESP_LOGI(TAG, "Parsed.....");

	char *parsedJsonString = cJSON_Print(jsonObj);
	ESP_LOGI(TAG, "my_parsed json_string\n%s",parsedJsonString);

	if (cJSON_GetObjectItem(jsonObj, myMessageTypes.MESSAGE_TYPE_LOCAL)) {
        ESP_LOGI(TAG, "FOund object.....");
		char *message_type = cJSON_GetObjectItem(jsonObj, myMessageTypes.MESSAGE_TYPE_LOCAL)->valuestring;
		ESP_LOGI(TAG, "version=%s",message_type);
	}

    //clean up
    //delete json object
	cJSON_Delete(jsonObj);
	// Buffers returned by cJSON_Print must be freed by the caller.
	// Please use the proper API (cJSON_free) rather than directly calling stdlib free.
	cJSON_free(parsedJsonString);
}