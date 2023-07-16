
Ctest()
--[[
--print("hello Lua")print("hello Lua")
-- 全局变量 a = 10  不会释放， 局部变量可自动释放
--[[
local a = 123
local b= tostring(a)
local html = [[
<html>
</html>
]]
local n = nil
--html = "test1".."test2"
--print("string len = "..string.len(html))
--print("sub string = "..string.sub(html,3,5))
local b,e = string.find(html,"html");
--print("b = "..b .."  e="..e);
local re = string.gsub(html,"html","body");
--print("html = ".. html);
--print("re = ".. re);
if((1==1 and 1==3) or 3==3) then
	--print("1==1")
elseif (2==2) then	
	--print("2==2")	
else
	--print("in else")
end


while( not(i < 0)) do
	print("i="..i)
	i = i-1
	if(i == 90) then
		print("break while")
		break
	end
end

--  repeat类似while循环
local i = 100
repeat 
	i = i + 1;
	--print("i = " .. i);
until i>110

-- 数值for循环 从1 ~ 10  第三个参数省略了 
-- for var = 1,10,2 do   1 ~ 10 每次间隔两个值
for var = 1,10 do
	--print("var = " .. var)
end

-- 泛型循环  i是索引  v 是值
local days={"Sun","Mon","Tue"}
for i,v in pairs(days) do
	print(i.."=="..v);
end

local tab = { [1] = "A",[2] = "B",[4] = "D"}
for i,v in ipairs(tab) do
	---print(i.."--"..v);
end

local tab1 = {"001,002,003"}

for i,v in ipairs(tab1) do
	print("value = ")
end




--]]



local b= 123
--print(type(tostring(b)));
--print(type(tonumber(b)));
--[[

--]]
page = [[

<HTML>

<HEAD>

<TITLE>An HTML Page</TITLE>

</HEAD>

<BODY>

Lua

</BODY>

</HTML>

]]
--print("测试\"")
local pos = {};
b,e = string.find(page,"HE.D")
--print(b.."-"..e)
local val = string.sub(page,b,e);
--print(val)

local r = string.gsub(page,"HEAD","XCJ")
--print(r)

if(1==12 and 2==2 or 2==1) then
--print("1==1")
elseif(1==1) then
	--print("1==2")
else
	--print("else")
end
a = 2
if(not (a == 1)) then
	--print("not a == 1")
end

local i = 5
while i > 0 do
	i = i-1
	--print( "w " .. i)

end


repeat
	i = i + 1;
	if(i>3) then
		break;
	end

	--print("r i = " .. i)
until i>5
for var = 1,5,2 do
	--print("var ".. var)
end


days = {"Sunday", "Monday", "Tuesday", "Wednesday",

              "Thursday", "Friday", "Saturday"}

for i,v in ipairs(days) do

    --print(i.."ipairs:" .. v);

end
local tabFiles = {
[1] = "index",
[2] = "test2",
[3] = "test3",
[4] = "test1",
}
--tabFiles["x"] = "123";
--print("========== ipairs ============")
for k, v in pairs(tabFiles) do
	--print(k, v)
end
--print("========== pairs =============")
for k, v in pairs(tabFiles) do
--print(k, v)
end
local tab1 = {"001","002","003"}
table.insert(tab1,2,"002-2")
table.insert(tab1,"004");
for i,v in ipairs(tab1) do
	print("v = ".. v);
end

local t1 = {
	a=123,
	b="345"
}
t1["c"] = {a="xxx",b="bbb"}
t1["c"]["x"] = "123"
--print(t1["c"][1])

t1 = {3,5,7,9,998}

--print(t1[1])

table.insert(t1,2,34);
--print("remove = " .. table.remove(t1,3))
local len = table.getn(t1);

for k,v in pairs(t1) do
	--print(v)
end


function test(p1,...)
	local len = table.getn(arg);
	--print(arg["n"])
	for k,v in pairs(arg) do
		--print("argv["..k.."] = " .. v)
	end

end


test(1,21,33,14,65)


local eventfun = function(p1)
	--print("event fun = " .. p1)
end
eventfun(345)


function func()
	--print("my func 1")
end
func()
function func()
	--print("my func 2")
end
func()
local re = nil;
re = CTest("ssss1","ssss2");
ta = {};
ta["name"] = "xiaoming";
ta["age"] = "13";
ta["city"] = "中文城市";
--ta[3] = "nanjing";
--ta["test"] = 456;
--ta = {"xc","cj","qj"}
--dump(ta);
--print( debug.traceback() )

local i = 0;
re = CTestTable("ccc	",2,	ta)
--[[
while true do
CTest()
testTable = {}
--CTestTable(1,2,	4,ta)
i = i + 1
if(i%10000 == 0)  then
print("@@@memory", collectgarbage("count"))
end
end
 print(collectgarbage("collect"))
]]

luavar = "lua to c++";
print("re=")
print(re["name"]);
print("cvar = " .. cvar.name)
print("cname = " .. cname)

function LEvent()
	print("Levent")
end
--print("test" ,123,true);
--local bool = true print(bool)








--[[
local tab1 = {"001","002","003"}
for i,v in ipairs(tab1) do
	print("value= " .. v);
end
print("===== insert =====")
table.insert(tab1,3,"002-2")
for i,v in ipairs(tab1) do
	print("value= " .. v);
end
-- 默认末尾插入
table.insert(tab1,"004");
print("===== insert back=")
for i,v in ipairs(tab1) do
	print("value= " .. v);
end
print("===== remove =======")
table.remove(tab1,3)
for i,v in ipairs(tab1) do
	print("value= " .. v);
end
table.remove(tab1)
print("=====remove back====")
for i,v in ipairs(tab1) do
	print("value="..v)
end


local tab2 = {id=123,age=20}
tab2["name"] = "xiaoming"
tab2["id"] = nil;
for k,v in pairs(tab2) do
	print(k .. " : " .. v)
end

local tab3 = {}
tab3[1] = {"name1","name2"};
tab3[2] = {"value1","value2"};

for k,v in pairs(tab3) do
	for k2,v2 in pairs(v) do
		print("k2="..k2," v2="..v2);
	end
end

]]

function test(...)
    // 获取参数个数
	local len = table.getn(arg);
	print("arg len is ".. len);
	for a = 1,len do
		print("arg"..a.."="..arg[a])
	end
	--[[print(p1)
	if(p1 == nil) then
		p1="001"
	end
	if(p2 == nil) then
		p2 = "002"
	end
	
	print("p1="..p1.." p2="..p2)]]
	print("in test function")
	return 1,"name";
end
local fun1 = test;
local event = function (p1)
	print("event = ".. p1);
end
--event("key")
--local re,n = fun1(123,"name")


function test(...)
	print("new test");
end
test();
--print("re =" .. re .. ","..n);




int n = luaL_getn(l, 1);  /* get size of table */
for (int i = 1; i <= n; ++i) {
	lua_pushnumber(l, i);
	lua_gettable(l, 3);  //读取table[i]，table位于的位置。
	printf(" [%s] ",lua_tostring(l, -1));
   lua_pop(l, 1);
}
	size_t s;


		size_t s;
		lua_gettable(L, 1); printf("top=%d %s\n", lua_gettop(L), lua_tolstring(L, -1, &s));
		lua_pop(L, 1);

]]

















