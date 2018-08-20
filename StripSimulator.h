typedef unsigned char uint8_t;

class RgbColor
{
public:
  
  RgbColor()
  {
    R = 0;
    G = 0;
    B = 0;
  }

  RgbColor(uint8_t red, uint8_t green, uint8_t blue)
  {
    R = red;
    G = green;
    B = blue;
  }

  uint8_t R;
  uint8_t G;
  uint8_t B;
};

class Strip
{
private:
  int _pixelPin;
  int _pixelCount;
  RgbColor* _pColors;
  bool _showCalled;

public:
  Strip(int pixelPin, int pixelCount) :
    _pixelPin(pixelPin),
    _pixelCount(pixelCount)
  {
    _showCalled = false;
    _pColors = new RgbColor[pixelCount];
  }

  void Init()
  {
  }

  int GetPixelCount()
  {
    return _pixelCount;
  }

  void SetPixelColor(int pixelIndex, RgbColor color)
  {
    _pColors[pixelIndex] = color;
  }

  RgbColor GetPixelColor(int pixelIndex)
  {
    return _pColors[pixelIndex];
  }

  void Clear()
  {
    RgbColor black(0, 0, 0);
    for (int led = 0; led < _pixelCount; led++)
    {

    }
    Show();
  }

  void Show()
  {
    _showCalled = true;
  }

  bool GetShowCalled()
  {
    return _showCalled;
  }
};
