#pragma once

//typedef unsigned char byte;
//#include "Serial.h"

#include "string.h"
#include "StripSimulator.h"
#include "Command.h"
#include "IAnimation.h"
#include "AnimationAlternate.h"

class IAnimationTest
{
public:
  static void Test()
  {
    TestName();
    TestPixelCount();
    TestSetPixelColor();
    TestSetPixelColorWithGamma();
    TestSetPixelColorWithGamma2();
    TestSetAllPixelColorWithGammaAndShow();
  }

  static void TestName()
  {
    Strip* pStrip = new Strip(1, 33);
    AnimationAlternate iAnimation(pStrip);

    AssertEqual(iAnimation.getName(), (String) "Alternate");
  }

  static void TestPixelCount()
  {
    Strip* pStrip = new Strip(1, 33);
    AnimationAlternate iAnimation(pStrip);

    AssertEqual(iAnimation.GetPixelCount(), 33);
  }

  static void TestSetPixelColor()
  {
    Strip* pStrip = new Strip(1, 33);
    AnimationAlternate iAnimation(pStrip);

    iAnimation.SetPixelColor(10, RgbColor(1, 2, 3));

    RgbColor stored = pStrip->GetPixelColor(10);
    AssertEqual(stored.R, 1);
    AssertEqual(stored.G, 2);
    AssertEqual(stored.B, 3);
  }


  static void TestSetPixelColorWithGamma()
  {
    Strip* pStrip = new Strip(1, 33);
    AnimationAlternate iAnimation(pStrip);

    iAnimation.SetPixelColorWithGamma(10, RgbColor(50, 100, 150));

    RgbColor stored = pStrip->GetPixelColor(10);
    AssertEqual((int) stored.R, 3);
    AssertEqual((int) stored.G, 19);
    AssertEqual((int) stored.B, 58);
  }

  static void TestSetPixelColorWithGamma2()
  {
    Strip* pStrip = new Strip(1, 33);
    AnimationAlternate iAnimation(pStrip);

    iAnimation.SetPixelColorWithGamma(10, RgbColor(200, 210, 220));

    RgbColor stored = pStrip->GetPixelColor(10);
    AssertEqual((int)stored.R, 129);
    AssertEqual((int)stored.G, 148);
    AssertEqual((int)stored.B, 169);
  }

  static void TestSetAllPixelColorWithGammaAndShow()
  {
    Strip* pStrip = new Strip(1, 33);
    AnimationAlternate iAnimation(pStrip);

    AssertEqual(pStrip->GetShowCalled(), false);

    iAnimation.SetAllPixelColorWithGammaAndShow(RgbColor(230, 240, 250));

    for (int i = 0; i < 33; i++)
    {
      RgbColor stored = pStrip->GetPixelColor(i);
      AssertEqual((int)stored.R, 191);
      AssertEqual((int)stored.G, 215);
      AssertEqual((int)stored.B, 241);
    }

    AssertEqual(pStrip->GetShowCalled(), true);
  }

};

