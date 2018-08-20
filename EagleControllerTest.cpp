// EagleControllerTest.cpp : Defines the entry point for the console application.
//

#define _CRT_SECURE_NO_WARNINGS

#include "stdafx.h"
#include <iostream>
using namespace std;

#include "String.h"

//#define AssertEqual(a, b) {if (!(a == b)) cout << "Failed " << __FUNCTION__ << ". Expected, received: >" << a << "< != >" << b << "<" << endl;}
#define AssertEqual(a, b) {if (!(a == b)) cout << "Failed " << __FUNCTION__ << ". Expected, received: " << a << " != " << b << "" << endl;}
//#define AssertEqual(a, b) {if (!(a == b)) __debugbreak;}

#include "PersistentStorageTest.h"
#include "IAnimationTest.h"
#include "AnimationAlternateTest.h"
#include "CommandTest.h"
#include "AnimationBlendTest.h"
#include "AnimationColorRotateTest.h"
#include "AnimationSetChunkTest.h"
#include "AnimationFlashDecayTest.h"
#include "AnimationRandomFlashTest.h"
#include "AnimationCommandsTest.h"
#include "AnimationIndividualTest.h"
#include "TokenizerTest.h"

int main()
{
	PersistentStorageTest::Test();
  IAnimationTest::Test();
  AnimationAlternateTest::Test();
  CommandTest::Test();
  AnimationBlendTest::Test();
  AnimationColorRotateTest::Test();
  AnimationFlashDecayTest::Test();
  AnimationSetChunkTest::Test();
  AnimationRandomFlashTest::Test();
  AnimationCommandsTest::Test();
  AnimationIndividualTest::Test();
  TokenizerTest::Test();

  return 0;
}

