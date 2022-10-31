//#include <string>
//#include <stack>
//using namespace std;
//std::string str;
//using std::string;
extern void displayStart();
extern void displayClear();
extern void updateActivity(int seconds = 5);
extern void displayEnterVoiceCommandStep1();
extern void displayEnterVoiceCommandStep2();
extern void displayEnterVoiceCommandStep3(char* command, char* soFar);
//extern void displayEnterVoiceCommandStep3(string command, string soFar);
extern void displaySearchEngineResult(char* title, char* body, char* image);