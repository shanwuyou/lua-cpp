--luaµ÷ÓÃC++
CTest()
CTest1("test", 1, true)
local arr = {"A001", "B002"}
CTestArr(arr)
local tab = {name = "zhangr", SEX = "N"}
CTestTab(tab)
local re = CTestRe();
print("re = ", re)
local re = CTestReTable();
print("re = ", re["name"])
print("age = ", re["age"])
lua = 'test'

conf = 
{
	titlname = "first lua",
	height = 1080
}

print("name = ", person["name"])
print("age = ", person.age)
function ferror(e)
	print("my error:" .. e);
	return "lua change error"
end
function event(e, obj)
	print("C++ call lua function")
	print(e);
	print(obj.name);
	--return "hello"
	return {id = 1}
end