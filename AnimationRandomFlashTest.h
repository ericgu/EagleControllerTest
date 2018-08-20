#pragma once
#pragma once

#include "ESP8266TrueRandomClass.h"
#include "AnimationRandomFlash.h"

class AnimationRandomFlashTest
{
public:
  static void Test()
  {
    TestName();
    TestNonMatching();
    TestMatching();
    TestFlashDecay();
  }

  static void TestName()
  {
    Strip* pStrip = new Strip(1, 33);
    AnimationRandomFlash animation(pStrip);

    AssertEqual(animation.getName(), (String) "Random Flash");
  }

  static void TestNonMatching()
  {
    Strip* pStrip = new Strip(1, 33);
    AnimationRandomFlash animation(pStrip);

    Command command("test 255,0,0,1", 0);

    bool result = animation.ProcessMessage(&command);

    AssertEqual(false, result);
  }

  static void TestMatching()
  {
    Strip* pStrip = new Strip(1, 33);
    AnimationRandomFlash animation(pStrip);

    Command command("rfx4,2,10", 0);

    bool result = animation.ProcessMessage(&command);

    AssertEqual(true, result);
  }

  static RgbColor UpdateAndGetColor(IAnimation* pAnimation, Strip* pStrip)
  {
    pAnimation->Update();
    RgbColor color = pStrip->GetPixelColor(0);
    //cout << "Color: " << (int)color.R << " " << (int)color.G << " " << (int)color.B << endl;
    return color;
  }

  static void AssertColor(RgbColor color, int r, int g, int b)
  {
    AssertEqual(r, (int)color.R);
    AssertEqual(g, (int)color.G);
    AssertEqual(b, (int)color.B);
  }

  static void AssertColor(AnimationRandomFlash* pAnimation, Strip* pStrip, int r, int g, int b, int count)
  {
    for (int i = 0; i < count; i++)
    {
      AssertColor(UpdateAndGetColor(pAnimation, pStrip), r, g, b);
    }
  }

  static void TestFlashDecay()
  {
    ESP8266TrueRandom.SetCount(10);
    ESP8266TrueRandom.Set(1);
    ESP8266TrueRandom.Set(2);
    ESP8266TrueRandom.Set(3);
    ESP8266TrueRandom.Set(4);
    ESP8266TrueRandom.Set(5);
    ESP8266TrueRandom.Set(6);
    ESP8266TrueRandom.Set(7);
    ESP8266TrueRandom.Set(8);
    ESP8266TrueRandom.Set(9);
    ESP8266TrueRandom.Set(10);

    Strip* pStrip = new Strip(1, 33);
    AnimationRandomFlash animation(pStrip);

    Command command("rfx2,2,10", 1);

    bool result = animation.ProcessMessage(&command);

    AssertColor(&animation, pStrip, 12, 82, 255, 14);
    AssertColor(&animation, pStrip, 82, 152, 255, 14);
    AssertColor(&animation, pStrip, 126, 182, 255, 14);
    AssertColor(&animation, pStrip, 255, 0, 3, 14);
    AssertColor(&animation, pStrip, 61, 137, 255, 14);
  }
};


