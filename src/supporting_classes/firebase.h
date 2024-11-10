#ifndef FIREBASE_FUNCTIONS_H
#define FIREBASE_FUNCTIONS_H

#include "env.h"
#include <FirebaseClient.h>
#include <WiFiClientSecure.h>


class FirebaseFunctions
{
private:
    DefaultNetwork network; // initilize with boolean parameter to enable/disable network reconnection
    UserAuth user_auth;
    FirebaseApp app;
    WiFiClientSecure ssl_client;
    using AsyncClient = AsyncClientClass;
    AsyncClient aClient;
    RealtimeDatabase Database;
    AsyncResult aResult_no_callback;
    void printError(int code, const String &msg);
    void printResult(AsyncResult &aResult);

public:
    FirebaseFunctions();
    void init();
    void authHandler();
    void sendData(float tempOut, float tempIn, int timestamp);
};
#endif