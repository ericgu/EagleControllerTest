#pragma once

#include "AnimationBlendTo.h"

class AnimationBlendTest
{
public:
  static void Test()
  {
    TestName();
    TestNonMatching();
    TestMatching();
    TestBlend();
  }

  static void TestName()
  {
    Strip* pStrip = new Strip(1, 33);
    AnimationBlendTo iAnimation(pStrip);

    AssertEqual(iAnimation.getName(), (String) "Blend");
  }

  static void TestNonMatching()
  {
    Strip* pStrip = new Strip(1, 33);
    AnimationBlendTo iAnimation(pStrip);

    Command command("test 255,0,0,1", 0);

    bool result = iAnimation.ProcessMessage(&command);

    AssertEqual(false, result);
  }

  static void TestMatching()
  {
    Strip* pStrip = new Strip(1, 33);
    AnimationBlendTo iAnimation(pStrip);

    Command command("rgb 255,0,0,1", 0);
    
    bool result = iAnimation.ProcessMessage(&command);

    AssertEqual(true, result);
  }

  static RgbColor UpdateAndGetColor(IAnimation* pAnimation, Strip* pStrip)
  {
    pAnimation->Update();
    RgbColor color = pStrip->GetPixelColor(0);
    //cout << "Color: " << (int)color.R << " " << (int)color.G << " " << (int)color.B << endl;
    return color;
  }

  static void TestBlend()
  {
    Strip* pStrip = new Strip(1, 33);
    AnimationBlendTo animation(pStrip);

    Command command("rgb 255,0,0,1", 0);

    bool result = animation.ProcessMessage(&command);

    RgbColor color = UpdateAndGetColor(&animation, pStrip);
    AssertEqual(255, (int)color.R);
    AssertEqual(0, (int)color.G);
    AssertEqual(0, (int)color.B);

    command = Command("rgb 0,255,0,3", 0);

    animation.ProcessMessage(&command);

    color = pStrip->GetPixelColor(0);
    AssertEqual(255, (int)color.R);
    AssertEqual(0, (int)color.G);
    AssertEqual(0, (int)color.B);

    color = UpdateAndGetColor(&animation, pStrip);
    AssertEqual(82, (int)color.R);
    AssertEqual(12, (int)color.G);
    AssertEqual(0, (int)color.B);

    color = UpdateAndGetColor(&animation, pStrip);
    AssertEqual(12, (int)color.R);
    AssertEqual(82, (int)color.G);
    AssertEqual(0, (int)color.B);

    color = UpdateAndGetColor(&animation, pStrip);
    AssertEqual(0, (int)color.R);
    AssertEqual(255, (int)color.G);
    AssertEqual(0, (int)color.B);
  }
};

#pragma once
