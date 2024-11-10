#include "firebase.h"

FirebaseFunctions::FirebaseFunctions() : user_auth(API_KEY, USER_EMAIL, USER_PASSWORD), aClient(ssl_client, getNetwork(network))
{
}

void FirebaseFunctions::init()
{
    ssl_client.setInsecure();
    ssl_client.setBufferSizes(4096, 1024);
    initializeApp(aClient, app, getAuth(user_auth), aResult_no_callback);
    authHandler();
    app.getApp<RealtimeDatabase>(Database);
    Database.url(DATABASE_URL);
    // In case setting the external async result to the sync task (optional)
    // To unset, use unsetAsyncResult().
    aClient.setAsyncResult(aResult_no_callback);
}

void FirebaseFunctions::authHandler()
{
    unsigned long ms = millis();
    while (app.isInitialized() && !app.ready() && millis() - ms < 120 * 1000)
    {
        // The JWT token processor required for ServiceAuth and CustomAuth authentications.
        // JWT is a static object of JWTClass and it's not thread safe.
        // In multi-threaded operations (multi-FirebaseApp), you have to define JWTClass for each FirebaseApp,
        // and set it to the FirebaseApp via FirebaseApp::setJWTProcessor(<JWTClass>), before calling initializeApp.
        JWT.loop(app.getAuth());
        printResult(aResult_no_callback);
    }
}

void FirebaseFunctions::sendData(float tempOut, float tempIn, int timestamp)
{
    object_t json;
    object_t json_items[3];
    JsonWriter writer;
    writer.create(json, "", ""); 
    writer.create(json_items[0], "temp_out", tempOut);
    writer.create(json_items[1], "temp_in", tempIn);
    writer.create(json_items[2], "timestamp", timestamp);
    writer.join(json, 3, json_items[0], json_items[1], json_items[2]);

    Serial.print("Push JSON... ");
    String name = Database.push<object_t>(aClient, "boiler_room_sensor", json);
    if (aClient.lastError().code() == 0)
        Firebase.printf("ok, name: %s\n", name.c_str());
    else
        printError(aClient.lastError().code(), aClient.lastError().message());
}

void FirebaseFunctions::printResult(AsyncResult &aResult)
{
    if (aResult.isEvent())
    {
        Firebase.printf("Event task: %s, msg: %s, code: %d\n", aResult.uid().c_str(), aResult.appEvent().message().c_str(), aResult.appEvent().code());
    }

    if (aResult.isDebug())
    {
        Firebase.printf("Debug task: %s, msg: %s\n", aResult.uid().c_str(), aResult.debug().c_str());
    }

    if (aResult.isError())
    {
        Firebase.printf("Error task: %s, msg: %s, code: %d\n", aResult.uid().c_str(), aResult.error().message().c_str(), aResult.error().code());
    }
}

void FirebaseFunctions::printError(int code, const String &msg)
{
    Firebase.printf("Error, msg: %s, code: %d\n", msg.c_str(), code);
}