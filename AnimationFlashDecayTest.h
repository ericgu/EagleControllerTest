#pragma once
#pragma once

#include "ESP8266TrueRandomClass.h"
#include "AnimationFlashDecay.h"

class AnimationFlashDecayTest
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
    AnimationFlashDecay animation(pStrip);

    AssertEqual(animation.getName(), (String) "Flash decay");
  }

  static void TestNonMatching()
  {
    Strip* pStrip = new Strip(1, 33);
    AnimationFlashDecay animation(pStrip);

    Command command("test 255,0,0,1", 0);

    bool result = animation.ProcessMessage(&command);

    AssertEqual(false, result);
  }

  static void TestMatching()
  {
    Strip* pStrip = new Strip(1, 33);
    AnimationFlashDecay animation(pStrip);

    Command command("fdcx250,10,500", 0);

    bool result = animation.ProcessMessage(&command);

    AssertEqual(true, result);
  }

  static RgbColor UpdateAndGetColor(IAnimation* pAnimation, Strip* pStrip)
  {
    pAnimation->Update();
    RgbColor color = pStrip->GetPixelColor(0);
    cout << "Color: " << (int)color.R << " " << (int)color.G << " " << (int)color.B << endl;
    return color;
  }

  static void AssertColor(RgbColor color, int r, int g, int b)
  {
    AssertEqual(r, (int)color.R);
    AssertEqual(g, (int)color.G);
    AssertEqual(b, (int)color.B);
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
    AnimationFlashDecay animation(pStrip);

    Command command("fdcx250,10,500", 1);

    bool result = animation.ProcessMessage(&command);

    animation.SetColorAndSteps(50, 100, 150, 20, 20);

    AssertColor(animation.GetColor(), 80, 161, 242);
    AssertColor(animation.GetColor(), 76, 153, 229);
    AssertColor(animation.GetColor(), 72, 144, 216);
    AssertColor(animation.GetColor(), 68, 136, 204);
    AssertColor(animation.GetColor(), 63, 127, 191);
    AssertColor(animation.GetColor(), 59, 119, 178);
    AssertColor(animation.GetColor(), 55, 110, 165);
    AssertColor(animation.GetColor(), 51, 102, 153);
    AssertColor(animation.GetColor(), 46, 93, 140);
    AssertColor(animation.GetColor(), 42, 85, 127);
    AssertColor(animation.GetColor(), 38, 76, 114);
    AssertColor(animation.GetColor(), 34, 68, 102);
    AssertColor(animation.GetColor(), 29, 59, 89);
    AssertColor(animation.GetColor(), 25, 51, 76);
    AssertColor(animation.GetColor(), 21, 42, 63);
    AssertColor(animation.GetColor(), 17, 34, 51);
    AssertColor(animation.GetColor(), 12, 25, 38);
    AssertColor(animation.GetColor(), 8, 17, 25);
    AssertColor(animation.GetColor(), 4, 8, 12);
  }
};

