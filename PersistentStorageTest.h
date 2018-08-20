#pragma once

typedef unsigned char byte;
#include "Serial.h"

#include "PersistentStorage.h"



class PersistentStorageTest
{
public:
	static void Test()
	{
		TestSimple();
		TestSaveLoad();
		TestSave1001Load1002();
    TestLEDMax();
    TestReset();
	}

	static void TestSimple()
	{
		String hostName("HostName");
		String password("Pass word");
		String ssid("the ssid");

		PersistentStorage persistentStorage;
		persistentStorage.HostNameSet(hostName);
		persistentStorage.PasswordSet(password);
		persistentStorage.SsidSet(ssid);

		AssertEqual(persistentStorage.HostNameGet(), hostName);
		AssertEqual(persistentStorage.PasswordGet(), password);
		AssertEqual(persistentStorage.SsidGet(), ssid);
	}

	static void TestSaveLoad()
	{
		String hostName("HostName");
		String password("Pass word");
		String ssid("the ssid");

		PersistentStorage persistentStorage;
		persistentStorage.SsidSet(ssid);
		persistentStorage.PasswordSet(password);
		persistentStorage.HostNameSet(hostName);
		persistentStorage._ledCount = 511;
		strcpy(persistentStorage._storedAnimation, "stored animation");
		persistentStorage.Save();

		PersistentStorage persistentStorageLoaded;
		persistentStorageLoaded.Load();

		AssertEqual(persistentStorageLoaded._version, 1002);
		AssertEqual(persistentStorageLoaded._size, 4096);

		AssertEqual(persistentStorageLoaded.SsidGet(), ssid);
		AssertEqual(persistentStorageLoaded.PasswordGet(), password);
		AssertEqual(persistentStorageLoaded.HostNameGet(), hostName);

		AssertEqual(persistentStorageLoaded._ledCount, 511);
		AssertEqual((String) persistentStorageLoaded._storedAnimation, (String) "stored animation");
	}

	static void TestSave1001Load1002()
	{
		String hostName("HostName");
		String password("Pass word");
		String ssid("the ssid");

		PersistentStorageV1001 persistentStorage;
		persistentStorage._ledCount = 100;
		strcpy(persistentStorage._storedAnimation, "stored animation");
		persistentStorage.Save();

		PersistentStorage persistentStorageLoaded;
		persistentStorageLoaded.Load();

		AssertEqual(persistentStorageLoaded._version, 1002);
		AssertEqual(persistentStorageLoaded._size, 4096);

		AssertEqual(persistentStorageLoaded._ledCount, 100);
		AssertEqual((String)persistentStorageLoaded._storedAnimation, (String) "stored animation");
	}

  static void TestLEDMax()
  {
    PersistentStorage persistentStorage;
    persistentStorage._ledCount = 2112;
    persistentStorage.Save();

    PersistentStorage persistentStorageLoaded;
    persistentStorageLoaded.Load();

    AssertEqual(persistentStorageLoaded._ledCount, 33);
  }

  static void TestDefaultAnimation()
  {
    PersistentStorage persistentStorage;
    persistentStorage._storedAnimation[0] = 255;
    persistentStorage.Save();

    PersistentStorage persistentStorageLoaded;
    persistentStorageLoaded.Load();

    AssertEqual((String)persistentStorageLoaded._storedAnimation, (String) "colx500,180");
  }
  
  static void TestReset()
  {
    PersistentStorage persistentStorage;
    persistentStorage.Reset();

    PersistentStorage persistentStorageLoaded;
    persistentStorageLoaded.Load();

    AssertEqual(persistentStorageLoaded._version, 1002);
    AssertEqual(persistentStorageLoaded._size, 4096);
    AssertEqual(persistentStorageLoaded.SsidGet(), (String)"");
    AssertEqual(persistentStorageLoaded.PasswordGet(), (String)"");
    AssertEqual(persistentStorageLoaded.HostNameGet(), (String)"");

    AssertEqual(persistentStorageLoaded._ledCount, 33);
    AssertEqual((String)persistentStorageLoaded._storedAnimation, (String) "colx500,180");

  }
};
