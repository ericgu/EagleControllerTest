class CommandTest
{
public:
  static void Test()
  {
    TestSimple();
    TestIsMatchFailMessage();
    TestIsMatchFailNumber();
    TestIsMatch();
  }

  static void TestSimple()
  {
    Command command;

    command.Parse("fred1,2,3,4");
    AssertEqual(4, command._count);
    AssertEqual(1, command._values[0]);
    AssertEqual(2, command._values[1]);
    AssertEqual(3, command._values[2]);
    AssertEqual(4, command._values[3]);
  }

  static void TestIsMatchFailMessage()
  {
    Command command("fredx5000,180", 0);

    AssertEqual(command.IsMatch("col", 2), false);
  }

  static void TestIsMatchFailNumber()
  {
    Command command("colx5000,180", 0);

    AssertEqual(command.IsMatch("col", 3), false);
  }

  static void TestIsMatch()
  {
    Command command("colx5000,180", 0);

    AssertEqual(command.IsMatch("col", 2), true);
  }
};

