/**************************************************************
 * Blynk is a platform with iOS and Android apps to control
 * Arduino, Raspberry Pi and the likes over the Internet.
 * You can easily build graphic interfaces for all your
 * projects by simply dragging and dropping widgets.
 *
 *   Downloads, docs, tutorials: http://www.blynk.cc
 *   Blynk community:            http://community.blynk.cc
 *   Social groups:              http://www.fb.com/blynkapp
 *                               http://twitter.com/blynk_app
 *
 * Blynk library is licensed under MIT license
 * This example code is in public domain.
 * 
 * WARNING: It is recommended to use SparkCorePolledTimer library
 *          to make periodic actions (similar to SimpleTimer on Arduino).
 *
 **************************************************************/
//#define BLYNK_DEBUG // Uncomment this to see debug prints
#define BLYNK_PRINT Serial
#include "blynk/blynk.h"

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "YourAuthToken";

// Attach a Button widget (mode: Switch) to the Digital pin 7 - and control the built-in blue led.
// Attach a Graph widget to Analog pin 1
// Attach a Gauge widget to Analog pin 2

// No coding required for direct pin operations!

void setup()
{
    Serial.begin(9600);
    delay(5000); // Allow board to settle
    Blynk.begin(auth);
}

// Attach a Button widget (mode: Push) to the Virtual pin 1 - and send sweet tweets!
BLYNK_WRITE(V1) {
    if (param.asInt() == 1) { // On button down...
        // Tweeting!
        // Note:
        //   We allow 1 tweet per minute for now.
        //   Twitter doesn't allow identical subsequent messages.
        Blynk.tweet("My Particle project is tweeting using @blynk_app and it’s awesome!\n @Particle #IoT #blynk");
        
        // Pushing notification to the app!
        // Note:
        //   We allow 1 notification per minute for now.
        Blynk.notify("You pressed the button and I know it ;)");
    }
}

// Attach a ZeRGBa widget (mode: Merge) to the Virtual pin 2 - and control the built-in RGB led!
BLYNK_WRITE(V2) {
    int r = param[0].asInt();
    int g = param[1].asInt();
    int b = param[2].asInt();
    if (r > 0 || g > 0 || b > 0) {
        RGB.control(true);
        RGB.color(r, g, b);
    } else {
        RGB.control(false);
    }
}

void loop()
{
    Blynk.run();
    
    if (ModeBtnPressed()) {
        Blynk.notify("Mode button was pressed");
    }
}

// *** Utility functions

bool ModeBtnPressed() {
    if(millis() > 5000) {
        if(BUTTON_GetDebouncedTime(BUTTON1) >= 50) {
            BUTTON_ResetDebouncedState(BUTTON1);
            return 1;
        }
    }
    return 0;
}

