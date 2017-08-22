# C++ To C#/Ruby Code Converter

C++ To C#/Ruby Code Converter – a desktop application which purpose is to translate С++ programs' source code into analogous (or similar) C#, Ruby code. The main idea is that this application can help developers to convert their C++ codebase (libraries) into C#, Ruby (if such need arises) a lot quicker than converting them fully manually. This app can convert all code in editor or convert only snippets and store translated code in clipboard.

Code converters DLLs (C#, Ruby) were developed with Visual Studio 2013 and GUI part of the application was developed with RAD Studio XE5. 
For more convenient test compilation and code execution this app additionally includes 3rd-party С++ compiler (g++ from Dev-C++ 4.9.9.2) and Ruby interpreter (1.9.3). C# test compilation requires .NET Framework 3.5 or higher.

Full application can be downloaded [here](https://www.dropbox.com/s/d9xk7n5s1eap1x3/Cpp2CsharpRuby_CodeConverter.rar?dl=0).

Code converter *supports*:
- Basic С++ types and using user types
- Pointers and references (variable can have only one pointer or reference) (Ruby only)
- Standard С++ literals (without prefixes and suffixes)
- С++ expressions (main, postfix, unary and etc.)
- С++ operators (expression, condition, loops, switch and etc.)
- Simple variable declaration (without qualifiers)
- Simple function declarations (without qualifiers)
- Console I/O (cin and cout)
- Comments between operators and functions

Code converter *does not support*:
- Preprocessor directives
- Classes and templates
- User type declaration 
- Global vars and constants
- Type casts
- Pointer arithmetic
- Literals' prefixes and suffixes
- Operator "new" qualifiers
- Labels and "goto" operator
- Exceptions
- Passing parameters by pointer (passing reference by value applies instead)


**C++ to Ruby code translation example:**

C++
```cs
#include <iostream>

using namespace std;

int findMax(int a, int b)
{
if (a >= b)
return a;
else
return b;
}

int main() 
{
    /* variables */
    string resultStr1 = "Max ";
    string& ref = resultStr1;
    string resultStr2 = "value is: ";
    string *ptr = &resultStr2;
    int x, y;
    
    //entering values
    cout << "Enter x: ";
    cin >> x;
    cout << "Enter y: ";
    cin >> y;
    
    //result
    cout << endl << ref + *ptr << findMax(x, y) << std::endl;
    std::cout << "Min: " << (x < y ? x : y) << endl;
    
    return 0;
}
```

Ruby:
```ruby
require './help_methods.rb'

def findMax (a, b)
    if notfalse(a >= b)
        return a
    else
        return b
    end
end

# MAIN

resultStr1 = "Max "
ref = Ref.new(:resultStr1, binding)
resultStr2 = "value is: "
ptr = Ptr.new(:resultStr2, binding)
x = 0; y = 0
STDOUT << "Enter x: "
x = cin (x)
STDOUT << "Enter y: "
y = cin (y)
STDOUT << "\n" << ref.val + ptr.val << findMax(x, y) << "\n"
STDOUT << "Min: " << (x < y ? x : y) << "\n"
return 0
```

**Screenshots:**

Main window:
![Main window](https://github.com/sp0wk/Cpp2CsharpRuby_CodeConverter/raw/master/screenshots/screen_main.png)

Translation of functions:
![functions](https://github.com/sp0wk/Cpp2CsharpRuby_CodeConverter/raw/master/screenshots/screen_functions.png)

Translation of one function:
![function](https://github.com/sp0wk/Cpp2CsharpRuby_CodeConverter/raw/master/screenshots/screen_function.png)

Translation of var declarations:
![vardecl1](https://github.com/sp0wk/Cpp2CsharpRuby_CodeConverter/raw/master/screenshots/screen_vardecl1.png)
![vardecl2](https://github.com/sp0wk/Cpp2CsharpRuby_CodeConverter/raw/master/screenshots/screen_vardecl2.png)

Translation of expressions:
![expr](https://github.com/sp0wk/Cpp2CsharpRuby_CodeConverter/raw/master/screenshots/screen_expr.png)

Translation of condition operator:
![condition](https://github.com/sp0wk/Cpp2CsharpRuby_CodeConverter/raw/master/screenshots/screen_condition.png)

Translation of loops:
![loops](https://github.com/sp0wk/Cpp2CsharpRuby_CodeConverter/raw/master/screenshots/screen_loops.png)

Translation of switch operator:
![switch](https://github.com/sp0wk/Cpp2CsharpRuby_CodeConverter/raw/master/screenshots/screen_switch.png)