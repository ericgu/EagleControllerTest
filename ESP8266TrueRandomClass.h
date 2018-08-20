#pragma once
class ESP8266TrueRandomClass
{
  int* _pValues;
  int _count;
  int _allocated;
  int _current;

public:
  void SetCount(int allocated)
  {
    _allocated = allocated;
    _current = 0;
    _count = 0;
    _pValues = new int[allocated];
  }

  void Set(int value)
  {
    *(_pValues + _count) = value;
    _count++;
  }

  int random()
  {
    int value = *(_pValues + _current);
    _current = (_current + 1) % _count;
    return value;
  }

  int random(int max)
  {
    return random();
  }
};

ESP8266TrueRandomClass ESP8266TrueRandom;