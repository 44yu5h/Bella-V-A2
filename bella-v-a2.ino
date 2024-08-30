#ifndef BOARD_HAS_PSRAM
#error "Please enable PSRAM !!!"
#endif

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include "epd_driver.h"
#include "./font/FiraSans.h"
#include "pins.h"

int cursor_x = 20;
int cursor_y = 50;

void dodo_dada()
{
    Serial.println("dodo dada");

    epd_poweron();
    writeln((GFXfont *)&FiraSans, "Yo my friendo", &cursor_x, &cursor_y, NULL);
    delay(500);

    cursor_x = 20;
    cursor_y += 50;

    writeln((GFXfont *)&FiraSans, "Lets be friendo forevero", &cursor_x, &cursor_y, NULL);
    delay(500);

    epd_poweroff();
}

void next_line(char *text)
{
    cursor_y += 50;
    epd_poweron();
    writeln((GFXfont *)&FiraSans, text, &cursor_x, &cursor_y, NULL);
    epd_poweroff();
}

bool connectWifi()
{
#define AP_SSID "Ayy"
#define AP_PASSWORD "Thisisdope007"

    WiFi.begin(AP_SSID, AP_PASSWORD);
    Serial.println("Connecting to the WiFi..");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("Connected to the WiFi network");
    return true;

    // check if connected(google.com->301); if not(google.com->200), reconnect
    /*HTTPClient http;
    http.begin("https://google.com");
    int res = http.GET();
    Serial.println(res);
    if (res == 301)
        return true;
    else if (res == -1)
    {
        delay(500);
        Serial.println("Reconnecting..");
        connectWifi();
    }
    else if (res == 200)
    {
        //////////check res if incorrect id/pswd is posted
        // Login to Captive Portal
        HTTPClient login;
        login.begin("https://campnet.bits-goa.ac.in:8090/httpclient.html");
        login.addHeader("Connection", "keep-alive");
        login.addHeader("Content-Type", "application/x-www-form-urlencoded");
        String body = "mode=191&username=f20230711&password=idk007&cmd=authenticate&Login=Log%2BIn";
        int res = login.POST(body);
        Serial.print("Logging in..\nres : ");
        Serial.println(res);
        if (res == 200)
        {
            Serial.println("Authentication BITS_GOA successful!");
            login.end();
            return true;
        }
        else
        {
            login.end();
            Serial.println("failed login");
            return false;
        }
    }
    return false;*/
}

void setup()
{
    Serial.begin(115200);
    delay(1000);

    epd_init();

    epd_poweron();
    epd_clear();
    epd_poweroff();
    dodo_dada();
    delay(1000);
    Serial.println("Connecting to the WiFi..");
    Serial.println(connectWifi());
}

void loop()
{
    delay(1000);
}
