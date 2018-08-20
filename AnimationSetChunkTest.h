#pragma once

#include "AnimationSetChunk.h"

class AnimationSetChunkTest
{
public:
  static void Test()
  {
    TestName();
    TestNonMatching();
    TestMatching();
    TestChunking();
  }

  static void TestName()
  {
    Strip* pStrip = new Strip(1, 33);
    AnimationSetChunk animation(pStrip);

    AssertEqual(animation.getName(), (String) "Set chunk");
  }

  static void TestNonMatching()
  {
    Strip* pStrip = new Strip(1, 33);
    AnimationSetChunk animation(pStrip);

    Command command("test 255,0,0,1", 0);

    bool result = animation.ProcessMessage(&command);

    AssertEqual(false, result);
  }

  static void TestMatching()
  {
    Strip* pStrip = new Strip(1, 33);
    AnimationSetChunk animation(pStrip);

    Command command("chunk 5,1,2,3", 0);

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

  static void TestChunking()
  {
    Strip* pStrip = new Strip(1, 33);
    AnimationSetChunk animation(pStrip);

    Command command("chunk 5,1,2,3,7,10,20,30,1,77,88,99", 1);

    bool result = animation.ProcessMessage(&command);

    for (int i = 0; i < 5; i++)
    {
      AssertColor(animation.GetColor(i), 1, 2, 3);
    }

    for (int i = 5; i < 12; i++)
    {
      AssertColor(animation.GetColor(i), 10, 20, 30);
    }

    for (int i = 12; i < 13; i++)
    {
      AssertColor(animation.GetColor(i), 77, 88, 99);
    }
  }
};

#pragma once
