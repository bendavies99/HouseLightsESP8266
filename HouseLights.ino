#include "LightsTask.h"
#include "MQTTTask.h"
#include "OTATask.h"

#define LED_PIN D2
#define LED_COUNT 300
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
LightsTask lights_task(&strip);
MQTTTask mqtt_task;
OTATask ota_task;

void loop()
{
  lights_task.loop();
  ota_task.loop();
  mqtt_task.loop();
}
void setup()
{
  Serial.begin(115200);
  Serial.println("Beginning");
  mqtt_task.setup();
  lights_task.setup();
  ota_task.setup();
}

// void colorWipe(uint32_t r, uint32_t g, uint32_t b, int wait)
// {
//   for (int i = 0; i < strip.numPixels(); i++)
//   {                                        // For each pixel in strip...
//     setPixelColor(i, r, g, b, brightness); //  Set pixel's color (in RAM)
//     strip.show();
//     client.loop(); //  Update strip to match
//     delay(wait);   //  Pause for a moment
//     if (cancelled)
//     {
//       return;
//     }
//   }
// }

// // Theater-marquee-style chasing lights. Pass in a color (32-bit value,
// // a la strip.Color(r,g,b) as mentioned above), and a delay time (in ms)
// // between frames.
// void theaterChase(uint32_t color, int wait)
// {
//   for (int a = 0; a < 10; a++)
//   { // Repeat 10 times...
//     for (int b = 0; b < 3; b++)
//     {                //  'b' counts from 0 to 2...
//       strip.clear(); //   Set all pixels in RAM to 0 (off)
//       // 'c' counts up from 'b' to end of strip in steps of 3...
//       for (int c = b; c < strip.numPixels(); c += 3)
//       {
//         strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
//       }
//       strip.show();
//       client.loop(); // Update strip with new contents
//       delay(wait);   // Pause for a moment
//       if (cancelled)
//       {
//         cancelled = false;
//         break;
//       }
//     }
//   }
// }

// void rainbow(int wait)
// {
//   for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256)
//   {
//     for (int i = 0; i < strip.numPixels(); i++)
//     {
//       int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
//       uint32_t c = strip.gamma32(strip.ColorHSV(pixelHue));
//       uint8_t r = (uint8_t)(c >> 16);
//       uint8_t g = (uint8_t)(c >> 8);
//       uint8_t b = (uint8_t)c;
//       setPixelColor(i, r, g, b, brightness);
//     }
//     strip.show();
//     client.loop();
//     delay(wait);
//     if (cancelled)
//     {
//       cancelled = false;
//       break;
//     }
//   }
// }

// // Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
// void theaterChaseRainbow(int wait)
// {
//   int firstPixelHue = 0; // First pixel starts at red (hue 0)
//   for (int a = 0; a < 30; a++)
//   { // Repeat 30 times...
//     for (int b = 0; b < 3; b++)
//     {                //  'b' counts from 0 to 2...
//       strip.clear(); //   Set all pixels in RAM to 0 (off)
//       // 'c' counts up from 'b' to end of strip in increments of 3...
//       for (int c = b; c < strip.numPixels(); c += 3)
//       {
//         // hue of pixel 'c' is offset by an amount to make one full
//         // revolution of the color wheel (range 65536) along the length
//         // of the strip (strip.numPixels() steps):
//         int hue = firstPixelHue + c * 65536L / strip.numPixels();
//         uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
//         strip.setPixelColor(c, color);                       // Set pixel 'c' to value 'color'
//       }
//       strip.show();
//       client.loop();               // Update strip with new contents
//       delay(wait);                 // Pause for a moment
//       firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
//       if (cancelled)
//       {
//         cancelled = false;
//         break;
//       }
//     }
//   }
// }
