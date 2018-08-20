#include "ESP8266TrueRandomClass.h"
#include "AnimationIndividual.h"

class AnimationIndividualTest
{
public:
  static void Test()
  {
    TestName();
    TestNonMatching();
    TestMatching();
    TestIndividual();
  }

  static void TestName()
  {
    Strip* pStrip = new Strip(1, 33);
    AnimationIndividual animation(pStrip);

    AssertEqual(animation.getName(), (String) "Individual");
  }

  static void TestNonMatching()
  {
    Strip* pStrip = new Strip(1, 33);
    AnimationIndividual animation(pStrip);

    Command command("test 255,0,0,1", 0);

    bool result = animation.ProcessMessage(&command);

    AssertEqual(false, result);
  }

  static void TestMatching()
  {
    Strip* pStrip = new Strip(1, 33);
    AnimationIndividual animation(pStrip);

    Command command("indx33,FFFFFF", 0);

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

  static void TestIndividual()
  {
    Strip* pStrip = new Strip(1, 33);
    AnimationIndividual animation(pStrip);

    Command command("indx1,FFFEFDAA8866", 0);

    bool result = animation.ProcessMessage(&command);
    animation.Update();

    AssertColor(pStrip->GetPixelColor(0), 255, 254, 253);
    AssertColor(pStrip->GetPixelColor(1), 170, 136, 102);
  }
};


