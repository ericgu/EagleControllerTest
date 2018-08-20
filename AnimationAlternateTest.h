#pragma once

class AnimationAlternateTest
{
public:
  static void Test()
  {
    TestName();
    TestNonMatching();
    TestMatching();
    TestAlternate();
  }

  static void TestName()
  {
    Strip* pStrip = new Strip(1, 33);
    AnimationAlternate iAnimation(pStrip);

    AssertEqual(iAnimation.getName(), (String) "Alternate");
  }

  static void TestNonMatching()
  {
    Strip* pStrip = new Strip(1, 33);
    AnimationAlternate iAnimation(pStrip);

    Command command("test 1,3,3,4", 0);

    bool result = iAnimation.ProcessMessage(&command);
    AssertEqual(false, result);
  }

  static void TestMatching()
  {
    Strip* pStrip = new Strip(1, 33);
    AnimationAlternate iAnimation(pStrip);

    Command command("alt 1,3,3,4,5,6,7", 0);

    bool result = iAnimation.ProcessMessage(&command);

    AssertEqual(true, result);
  }

  static void TestAlternate()
  {
    Strip* pStrip = new Strip(1, 33);
    AnimationAlternate iAnimation(pStrip);

    Command command("alt 255,0,0,0,255,0,2");

    bool result = iAnimation.ProcessMessage(&command);

    iAnimation.Update();

    RgbColor color = pStrip->GetPixelColor(0);
    //cout << "Color: " << (int) color.R << " " << (int) color.G << " " << (int)color.B << endl;
    AssertEqual(255, (int) color.R);
    AssertEqual(0, (int)color.G);
    AssertEqual(0, (int)color.B);

    iAnimation.Update();

    color = pStrip->GetPixelColor(0);
    //cout << "Color: " << (int)color.R << " " << (int)color.G << " " << (int)color.B << endl;
    AssertEqual(0, (int)color.R);
    AssertEqual(255, (int)color.G);
    AssertEqual(0, (int)color.B);

    iAnimation.Update();

    color = pStrip->GetPixelColor(0);
    //cout << "Color: " << (int)color.R << " " << (int)color.G << " " << (int)color.B << endl;
    AssertEqual(0, (int)color.R);
    AssertEqual(255, (int)color.G);
    AssertEqual(0, (int)color.B);

    iAnimation.Update();

    color = pStrip->GetPixelColor(0);
    //cout << "Color: " << (int)color.R << " " << (int)color.G << " " << (int)color.B << endl;
    AssertEqual(255, (int)color.R);
    AssertEqual(0, (int)color.G);
    AssertEqual(0, (int)color.B);

    iAnimation.Update();

    color = pStrip->GetPixelColor(0);
    //cout << "Color: " << (int)color.R << " " << (int)color.G << " " << (int)color.B << endl;
    AssertEqual(255, (int)color.R);
    AssertEqual(0, (int)color.G);
    AssertEqual(0, (int)color.B);
  }
};

#pragma once
