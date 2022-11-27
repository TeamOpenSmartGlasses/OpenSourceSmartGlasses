#ifndef JsonMessageParser_H
#define JsonMessageParser_H
#include "cJSON.h"	
#include "message_types.hpp"

class JsonMessageParser
{
    char * messageType;
    cJSON *jsonObj;

    public:
		MessageTypes messageTypesList;
        JsonMessageParser(char * jsonString);
		char * getMessageType();
		char * getJsonKey(const char * key);
        ~JsonMessageParser();

    private:
        void makeJson();
        void parseJson(char * jsonString);
};

#endif