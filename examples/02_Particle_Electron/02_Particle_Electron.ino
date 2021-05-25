/*************************************************************
  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************

  No coding required for direct digital/analog pin operations!

 *************************************************************/

#define BLYNK_PRINT Serial  // Set serial output for debug prints
//#define BLYNK_DEBUG       // Uncomment this to see detailed prints

/* Fill-in your Template ID (only if using Blynk.Cloud) */
//#define BLYNK_TEMPLATE_ID   "YourTemplateID"


// Uncomment this, if you want to set network credentials
//#include "cellular_hal.h"
//STARTUP(cellular_credentials_set("broadband", "", "", NULL));

// Run "ping blynk-cloud.com", and set Blynk IP to the shown address
#define BLYNK_IP        IPAddress(45,55,130,102)

// Set Blynk hertbeat interval.
// Each heartbeat uses ~90 bytes of data.
#define BLYNK_HEARTBEAT 60

// Set Particle keep-alive ping interval.
// Each ping uses 121 bytes of data.
#define PARTICLE_KEEPALIVE 20

#include <blynk.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "YourAuthToken";

void setup() {
  Serial.begin(9600);
  Particle.keepAlive(PARTICLE_KEEPALIVE);
  Blynk.begin(auth, BLYNK_IP);
}

void loop() {
  Blynk.run();
}
