require './ruby_help_methods.rb'


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
STDOUT << "Enter x:  "
x = cin (x)
STDOUT << "Enter y:  "
y = cin (y)
STDOUT << "\n" << ref.val + ptr.val << findMax(x, y) << "\n"
STDOUT << "Min value is: " << (x < y ? x : y) << "\n"
gets
