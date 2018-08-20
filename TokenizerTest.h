class TokenizerTest
{
public:
  static void Test()
  {
    TestEmpty();
    TestOne();
  }

  static void TestEmpty()
  {
    Tokenizer tokenizer("", '$');

    AssertEqual(String(""), tokenizer.GetToken());
    AssertEqual(true, tokenizer.GetFinished());
  }

  static void TestOne()
  {
    Tokenizer tokenizer("$test", '$');

    AssertEqual(String("test"), tokenizer.GetToken());
    AssertEqual(true, tokenizer.GetFinished());
  }


  static void TestTwo()
  {
    Tokenizer tokenizer("$test$best", '$');

    AssertEqual(String("test"), tokenizer.GetToken());
    AssertEqual(String("best"), tokenizer.GetToken());

    AssertEqual(true, tokenizer.GetFinished());
  }
};


