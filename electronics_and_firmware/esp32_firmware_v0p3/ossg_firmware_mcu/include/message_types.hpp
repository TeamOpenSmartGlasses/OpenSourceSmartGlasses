#pragma once

class MessageTypes {
    public: 
        //top level
        const char* MESSAGE_TYPE_LOCAL = "MESSAGE_TYPE_LOCAL";
        const char* TIMESTAMP = "TIMESTAMP";

        //DATA TYPES
        const char* POV_IMAGE = "POV_IMAGE";
        const char* JPG_BYTES_BASE64 = "JPG_BYTES_BASE64";

        //specific message types (after MESSAGE_TYPE_*)
        //TRANSCRIPTS
        const char* FINAL_TRANSCRIPT = "FINAL_TRANSCRIPT";
        const char* INTERMEDIATE_TRANSCRIPT = "INTERMEDIATE_TRANSCRIPT";
        const char* TRANSCRIPT_TEXT = "TRANSCRIPT_TEXT";
        const char* TRANSCRIPT_ID = "TRANSCRIPT_ID";

        //VOICE COMMANDS
        const char* VOICE_COMMAND_RESPONSE = "VOICE_COMMAND_RESPONSE";
        const char* COMMAND_RESULT = "COMMAND_RESULT";
        const char* COMMAND_NAME = "COMMAND_NAME";
        const char* COMMAND_RESPONSE_DISPLAY_STRING = "COMMAND_RESPONSE_DISPLAY_STRING";
        //voice command event
        const char* VOICE_COMMAND_STREAM_EVENT = "VOICE_COMMAND_STREAM_EVENT";
        const char* VOICE_COMMAND_STREAM_EVENT_TYPE = "VOICE_COMMAND_STREAM_EVENT_TYPE";
        const char* WAKE_WORD_EVENT_TYPE = "WAKE_WORD_EVENT_TYPE";
        const char* COMMAND_EVENT_TYPE = "COMMAND_EVENT_TYPE";
        const char* CANCEL_EVENT_TYPE = "CANCEL_EVENT_TYPE";
        const char* RESOLVE_EVENT_TYPE = "RESOLVE_EVENT_TYPE";
        const char* TEXT_RESPONSE_EVENT_TYPE = "TEXT_RESPONSE_EVENT_TYPE";
        const char* COMMAND_ARGS_EVENT_TYPE = "COMMAND_ARGS_EVENT_TYPE";
        const char* REQUIRED_ARG_EVENT_TYPE = "REQUIRED_ARG_EVENT_TYPE";
        const char* ARG_NAME = "ARG_NAME";
        const char* ARG_OPTIONS = "ARG_OPTIONS";
        const char* INPUT_VOICE_STRING = "INPUT_VOICE_STRING";
        const char* VOICE_ARG_EXPECT_TYPE = "VOICE_ARG_EXPECT_TYPE";
        const char* VOICE_ARG_EXPECT_NATURAL_LANGUAGE = "VOICE_ARG_EXPECT_NATURAL_LANGUAGE";
        const char* VOICE_COMMAND_LIST = "VOICE_COMMAND_LIST";
        const char* INPUT_WAKE_WORD = "INPUT_WAKE_WORD";
        const char* INPUT_VOICE_COMMAND_NAME = "INPUT_VOICE_COMMAND_NAME";

        //AUTOCITER/WEARABLE-REFERENCER
        const char* AUTOCITER_START = "AUTOCITER_START";
        const char* AUTOCITER_STOP = "AUTOCITER_STOP";
        const char* AUTOCITER_PHONE_NUMBER = "AUTOCITER_PHONE_NUMBER";
        const char* AUTOCITER_POTENTIAL_REFERENCES = "AUTOCITER_POTENTIAL_REFERENCES";
        const char* AUTOCITER_REFERENCE_DATA = "AUTOCITER_REFERENCE_DATA";

        //request user UI to display a list of possible choices to dipslay
        const char* REFERENCE_SELECT_REQUEST = "REFERENCE_SELECT_REQUEST";
        const char* REFERENCES = "REFERENCES";

        //FACE/PERSON SIGHTING
        const char* FACE_SIGHTING_EVENT = "FACE_SIGHTING_EVENT";
        const char* FACE_NAME = "FACE_NAME";

        //SMS
        const char* SMS_REQUEST_SEND = "SMS_REQUEST_SEND";
        const char* SMS_MESSAGE_TEXT = "SMS_MESSAGE_TEXT";
        const char* SMS_PHONE_NUMBER = "SMS_PHONE_NUMBER";

        //AUDIO
        //AUDIO
        const char* AUDIO_CHUNK_ENCRYPTED = "AUDIO_CHUNK_ENCRYPTED";
        const char* AUDIO_CHUNK_DECRYPTED = "AUDIO_CHUNK_DECRYPTED";
        const char* AUDIO_DATA = "AUDIO_DATA";


        //COMMS
        const char* PING = "PING";

        //UI
        const char* UI_UPDATE_ACTION = "UI_UPDATE_ACTION";
        const char* PHONE_CONNECTION_STATUS = "PHONE_CONNECTION_STATUS";

    //    //command responses to show
    //    const char* NATURAL_LANGUAGE_QUERY = "NATURAL_LANGUAGE_QUERY";
    //    const char* TEXT_RESPONSE = "NATURAL_LANGUAGE_QUERY";
    //    const char* TEXT_QUERY = "TEXT_QUERY";
    //    const char* VISUAL_SEARCH_RESULT = "VISUAL_SEARCH_RESULT";
    //    const char* VISUAL_SEARCH_QUERY = "VISUAL_SEARCH_QUERY";
    //    const char* VISUAL_SEARCH_IMAGE= "VISUAL_SEARCH_IMAGE";
    //    const char* VISUAL_SEARCH_DATA = "VISUAL_SEARCH_DATA";
    //    const char* SEARCH_ENGINE_RESULT = "SEARCH_ENGINE_RESULT";
    //    const char* SEARCH_ENGINE_RESULT_DATA = "SEARCH_ENGINE_RESULT_DATA";
    //    const char* TRANSLATION_RESULT = "TRANSLATION_RESULT";
    //    const char* AFFECTIVE_SUMMARY_RESULT = "AFFECTIVE_SUMMARY_RESULT";
    //    const char* COMMAND_SWITCH_MODE = "COMMAND_SWITCH_MODE";

        //command responses to show
        //Natural language
        const char* NATURAL_LANGUAGE_QUERY = "NATURAL_LANGUAGE_QUERY";
        const char* TEXT_QUERY = "TEXT_QUERY";
        //visual search
        const char* VISUAL_SEARCH_RESULT = "VISUAL_SEARCH_RESULT"; //this is the ASG facing term
        const char* VISUAL_SEARCH_IMAGE= "VISUAL_SEARCH_IMAGE";
        const char* VISUAL_SEARCH_QUERY = "VISUAL_SEARCH_QUERY"; //this is the glbox facing term
        const char* VISUAL_SEARCH_DATA = "VISUAL_SEARCH_DATA"; //this is the payload
        //search engine
        const char* SEARCH_ENGINE_QUERY = "SEARCH_ENGINE_QUERY";
        const char* SEARCH_ENGINE_RESULT = "SEARCH_ENGINE_RESULT";
        const char* SEARCH_ENGINE_RESULT_DATA = "SEARCH_ENGINE_RESULT_DATA";
        const char* SEARCH_ENGINE_RESULT_DATA_TITLE = "title";
        const char* SEARCH_ENGINE_RESULT_DATA_BODY = "body";
        const char* SEARCH_ENGINE_RESULT_DATA_IMAGE = "image";

        //I/O
        const char* SG_TOUCHPAD_EVENT = "SG_TOUCHPAD_EVENT";
        const char* SG_TOUCHPAD_KEYCODE = "SG_TOUCHPAD_KEYCODE";

        //translation
        const char* TRANSLATE_TEXT_QUERY = "TRANSLATE_TEXT_QUERY";
        const char* TRANSLATE_TEXT_DATA = "TRANSLATE_TEXT_DATA";
        const char* TRANSLATE_TEXT_RESULT = "TRANSLATE_TEXT_RESULT";
        const char* TRANSLATE_TEXT_RESULT_DATA = "TRANSLATION_RESULT_DATA";

        //object translation
        const char* OBJECT_TRANSLATION_RESULT = "OBJECT_TRANSLATION_RESULT";
        const char* OBJECT_TRANSLATION_RESULT_DATA = "OBJECT_TRANSLATION_RESULT_DATA";

        const char* AFFECTIVE_SUMMARY_RESULT = "AFFECTIVE_SUMMARY_RESULT";
        const char* COMMAND_SWITCH_MODE = "COMMAND_SWITCH_MODE";

        //control the current mode of the ASG
        const char* ACTION_SWITCH_MODES = "ACTION_SWITCH_MODES";
        const char* NEW_MODE = "NEW_MODE";
        const char* MODE_VISUAL_SEARCH = "MODE_VISUAL_SEARCH";
        const char* MODE_LIVE_LIFE_CAPTIONS = "MODE_LIVE_LIFE_CAPTIONS";
        const char* MODE_HOME = "MODE_HOME";
        const char* MODE_CONVERSATION_MODE = "MODE_CONVERSATION_MODE";
        const char* MODE_SOCIAL_MODE = "MODE_SOCIAL_MODE";
        const char* MODE_REFERENCE_GRID = "MODE_REFERENCE_GRID";
        const char* MODE_WEARABLE_FACE_RECOGNIZER = "MODE_WEARABLE_FACE_RECOGNIZER";
        const char* MODE_LANGUAGE_TRANSLATE = "MODE_LANGUAGE_TRANSLATE";
        const char* MODE_OBJECT_TRANSLATE = "MODE_OBJECT_TRANSLATE";
        const char* MODE_TEXT_LIST = "MODE_TEXT_LIST";
        const char* MODE_TEXT_BLOCK = "MODE_TEXT_BLOCK";
        const char* MODE_BLANK = "MODE_BLANK";
        const char* MODE_SEARCH_ENGINE_RESULT = "MODE_SEARCH_ENGINE_RESULT";
};


