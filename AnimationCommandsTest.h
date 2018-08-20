#pragma once

#include "AnimationCommands.h"

class AnimationCommandsTest
{
public:
  static void Test()
  {
    TestSingle();
    TestLoadSingle();
    TestSave();
    TestRoundTrip();
    TestSaveTwo();
    TestRoundTripTwo();
    TestGetNextSegment();
    TestAddComplex();
    TestAddTen();
    TestGetNextSegmentSingle();
    TestLoadFromStringSimpleThenComplex();
  }

  static void TestSingle()
  {
    AnimationCommands animationCommands;

    Command command("Test 55", 5);
    animationCommands.Add(command);

    AssertEqual(1, animationCommands.Count());
    Command stored = animationCommands.GetSegment(0);
    AssertEqual(String("Test 55"), stored._message);
    AssertEqual(5, stored._period);
  }

  static void TestLoadSingle()
  {
    AnimationCommands animationCommands;

    animationCommands.LoadFromString("cxx15,15,15");

    AssertEqual(1, animationCommands.Count());
    Command stored = animationCommands.GetSegment(0);
    AssertEqual(String("cxx15,15,15"), stored._message);
    AssertEqual(1000000, stored._period);
  }

  static void TestSave()
  {
    AnimationCommands animationCommands;

    Command command("cxx15,15,15", 5);
    animationCommands.Add(command);

    String saveFormat = animationCommands.SaveToString();

    AssertEqual(String("$5$cxx15,15,15"), saveFormat);
  }

  static void TestRoundTrip()
  {
    AnimationCommands animationCommands;

    Command command("cxx15,15,15", 5);
    animationCommands.Add(command);

    String saveFormat = animationCommands.SaveToString();

    AnimationCommands animationCommandsLoaded;
    animationCommandsLoaded.LoadFromString(saveFormat);

    AssertEqual(1, animationCommandsLoaded.Count());
    Command stored = animationCommandsLoaded.GetSegment(0);
    AssertEqual(String("cxx15,15,15"), stored._message);
    AssertEqual(5, stored._period);
  }

  static void TestSaveTwo()
  {
    AnimationCommands animationCommands;

    animationCommands.Add(Command("cxx15,15,15", 5));
    animationCommands.Add(Command("ffcx33,33,33,33", 6));

    String saveFormat = animationCommands.SaveToString();

    AssertEqual(String("$5$cxx15,15,15$6$ffcx33,33,33,33"), saveFormat);
  }

  static void TestRoundTripTwo()
  {
    AnimationCommands animationCommands;

    animationCommands.Add(Command("cxx15,15,15", 5));
    animationCommands.Add(Command("ffcx33,33,33,33", 6));

    String saveFormat = animationCommands.SaveToString();

    AnimationCommands animationCommandsLoaded;
    animationCommandsLoaded.LoadFromString(saveFormat);

    AssertEqual(2, animationCommandsLoaded.Count());
    Command stored = animationCommandsLoaded.GetSegment(0);
    AssertEqual(String("cxx15,15,15"), stored._message);
    AssertEqual(5, stored._period);

    Command stored2 = animationCommandsLoaded.GetSegment(1);
    AssertEqual(String("ffcx33,33,33,33"), stored2._message);
    AssertEqual(6, stored2._period);
  }

  static void TestGetNextSegment()
  {
    AnimationCommands animationCommands;

    animationCommands.LoadFromString("$5$cxx15,15,15$6$ffcx33,33,33,33");

    AssertEqual(String("cxx15,15,15"), animationCommands.GetNextMessage()->_message);
    AssertEqual(0, animationCommands.GetNextMessage());
    AssertEqual(0, animationCommands.GetNextMessage());
    AssertEqual(0, animationCommands.GetNextMessage());
    AssertEqual(0, animationCommands.GetNextMessage());
    AssertEqual(0, animationCommands.GetNextMessage());
    AssertEqual(String("ffcx33,33,33,33"), animationCommands.GetNextMessage()->_message);
    AssertEqual(0, animationCommands.GetNextMessage());
    AssertEqual(0, animationCommands.GetNextMessage());
    AssertEqual(0, animationCommands.GetNextMessage());
    AssertEqual(0, animationCommands.GetNextMessage());
    AssertEqual(0, animationCommands.GetNextMessage());
    AssertEqual(0, animationCommands.GetNextMessage());
    AssertEqual(String("cxx15,15,15"), animationCommands.GetNextMessage()->_message);
  }

  static void TestGetNextSegmentSingle()
  {
    AnimationCommands animationCommands;

    animationCommands.LoadFromString("$25$cxx15,15,15");
    AssertEqual(1, animationCommands.Count());

    AssertEqual(String("cxx15,15,15"), animationCommands.GetNextMessage()->_message);
    AssertEqual(0, animationCommands.GetNextMessage());
    AssertEqual(0, animationCommands.GetNextMessage());
    AssertEqual(0, animationCommands.GetNextMessage());
    AssertEqual(0, animationCommands.GetNextMessage());
    AssertEqual(0, animationCommands.GetNextMessage());
    AssertEqual(0, animationCommands.GetNextMessage());
    AssertEqual(0, animationCommands.GetNextMessage());
    AssertEqual(0, animationCommands.GetNextMessage());
    AssertEqual(0, animationCommands.GetNextMessage());
    AssertEqual(0, animationCommands.GetNextMessage());
  }

  static void TestAddComplex()
  {
    AnimationCommands animationCommands;

    animationCommands.Add(Command(String("$5$cxx15,15,15$6$ffcx33,33,33,33"), -1));

    AssertEqual(2, animationCommands.Count());
    Command stored = animationCommands.GetSegment(0);
    AssertEqual(String("cxx15,15,15"), stored._message);
    AssertEqual(5, stored._period);

    Command stored2 = animationCommands.GetSegment(1);
    AssertEqual(String("ffcx33,33,33,33"), stored2._message);
    AssertEqual(6, stored2._period);
  }

  static void TestLoadFromStringSimpleThenComplex()
  {
    AnimationCommands animationCommands;

    animationCommands.LoadFromString(String("test 515"));
    animationCommands.LoadFromString(String("$5$cxx15,15,15$6$ffcx33,33,33,33"));

    AssertEqual(2, animationCommands.Count());
    Command stored = animationCommands.GetSegment(0);
    AssertEqual(String("cxx15,15,15"), stored._message);
    AssertEqual(5, stored._period);

    Command stored2 = animationCommands.GetSegment(1);
    AssertEqual(String("ffcx33,33,33,33"), stored2._message);
    AssertEqual(6, stored2._period);
  }

  static void TestAddTen()
  {
    AnimationCommands animationCommands;

    for (int i = 0; i < 20; i++)
    {
      animationCommands.Add(Command("cxx15,15,15", 5));
    }

    String saveFormat = animationCommands.SaveToString();

    AssertEqual(20, animationCommands.Count());
  }
};
