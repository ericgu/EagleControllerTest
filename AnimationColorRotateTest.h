#pragma once
#pragma once

#include "AnimationColorRotate.h"

class AnimationColorRotateTest
{
public:
  static void Test()
  {
    TestName();
    TestNonMatching();
    TestMatching();
    TestRotate();

    TestInterpolate();
  }

  static void TestName()
  {
    Strip* pStrip = new Strip(1, 33);
    AnimationColorRotate animation(pStrip);

    AssertEqual(animation.getName(), (String) "Color rotate");
  }

  static void TestNonMatching()
  {
    Strip* pStrip = new Strip(1, 33);
    AnimationColorRotate animation(pStrip);

    Command command("test 255,0,0,1", 0);

    bool result = animation.ProcessMessage(&command);

    AssertEqual(false, result);
  }

  static void TestMatching()
  {
    Strip* pStrip = new Strip(1, 33);
    AnimationColorRotate animation(pStrip);

    Command command("col 600,200", 0);

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
    //cout << "Assert: " << (int)color.R << " " << (int)color.G << " " << (int)color.B << endl;
    AssertEqual(r, (int)color.R);
    AssertEqual(g, (int)color.G);
    AssertEqual(b, (int)color.B);
  }

  static void SkipSteps(AnimationColorRotate& animation, int steps)
  {
    for (int i = 0; i < steps; i++)
    {
      RgbColor color = animation.GetColor();
      //cout << "Color: " << (int)color.R << " " << (int)color.G << " " << (int)color.B << endl;
    }
  }

  static void TestRotate()
  {
    Strip* pStrip = new Strip(1, 33);
    AnimationColorRotate animation(pStrip);

    Command command("col 60,200", 1);

    bool result = animation.ProcessMessage(&command);

    int brightness = 200;
    int brightnessTwo = 170;

    AssertColor(animation.GetColor(), brightness, 0, 0);
    SkipSteps(animation, 9);

    AssertColor(animation.GetColor(), brightnessTwo, brightnessTwo, 0);
    SkipSteps(animation, 9);

    AssertColor(animation.GetColor(), 0, brightness, 0);
    SkipSteps(animation, 9);

    AssertColor(animation.GetColor(), 0, brightnessTwo, brightnessTwo);
    SkipSteps(animation, 9);

    AssertColor(animation.GetColor(), 0, 0, brightness);
    SkipSteps(animation, 9);

    AssertColor(animation.GetColor(), brightnessTwo, 0, brightnessTwo);
    SkipSteps(animation, 9);

    AssertColor(animation.GetColor(), brightness, 0, 0);
  }

  static void TestInterpolate()
  {
    AnimationColorRotate animation(0);

    Command command("rgb 255,0,0,1", 1);

    animation.ProcessMessage(&command);

    int value = animation.Interpolate(0, 10, 0);
    AssertEqual(0, value);

    value = animation.Interpolate(0, 10, 0.5);
    AssertEqual(5, value);

    value = animation.Interpolate(0, 10, 1.0);
    AssertEqual(10, value);
  }
};

#pragma once
