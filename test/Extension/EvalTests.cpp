﻿#include "stdafx.h"
#include "../src/Extension/tinyexpr/tinyexpr.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

class CEvalTestData
{
public:
  std::string source;
  double result;

  CEvalTestData(const std::string& src, const double res) : source(src), result(res)
  {
  }
};

namespace Notepad2eTests
{
  TEST_CLASS(CEval)
  {
  public:
    TEST_METHOD(EvalTests)
    {
      const CEvalTestData data[] = {
        CEvalTestData("1+2+3", 6),
        CEvalTestData("1 2 3", 6),
        CEvalTestData("1\r\n2\r\n3", 6),
        CEvalTestData("\r\n1\r\n\r\n2\r\n3", 6),
        CEvalTestData("1+2=3", 3),
        CEvalTestData("12.34+.1", 12.44),
        CEvalTestData("12,34+,1", 12.44),
        CEvalTestData("1,2,3+1", 124),
        CEvalTestData("1,2,3 + 1,2 + ,3", 138),
        CEvalTestData("12,3 + 1,2 + ,3", 13.80),
        
      };

      for (auto i = 0; i < _countof(data); i++)
      {
        const auto info = data[i];
        double exprValue = 0.0;
        if (is_valid_expression((unsigned char*)info.source.c_str(), 1, &exprValue))
        {
          Assert::AreEqual(info.result, exprValue);
        }
        else
        {
          Assert::Fail(L"Invalid expression");
        }
      }
    }
  };

}
