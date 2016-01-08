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
// No coding is required for direct pin operations!

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

// Attach a Slider widget to the Virtual pin 2 - and control the built-in RGB led!
BLYNK_WRITE(V2) {
    if (param.asInt() > 0) {
        RGB.control(true);
        
        byte rgb[3];
        HsvToRgb(param.asDouble()/255, 1, 1, rgb);
        RGB.color(rgb[0], rgb[1], rgb[2]);
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

void HsvToRgb(double h, double s, double v, byte rgb[]) {
    double r, g, b;

    int i = int(h * 6);
    double f = h * 6 - i;
    double p = v * (1 - s);
    double q = v * (1 - f * s);
    double t = v * (1 - (1 - f) * s);

    switch(i % 6){
        case 0: r = v, g = t, b = p; break;
        case 1: r = q, g = v, b = p; break;
        case 2: r = p, g = v, b = t; break;
        case 3: r = p, g = q, b = v; break;
        case 4: r = t, g = p, b = v; break;
        case 5: r = v, g = p, b = q; break;
    }

    rgb[0] = r * 255;
    rgb[1] = g * 255;
    rgb[2] = b * 255;
}

