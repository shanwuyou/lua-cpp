// 01HelloLua.cpp : 定义控制台应用程序的入口点。
//
extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}
#include <string.h>

int CTest(lua_State* l)
{
	printf("init CTEST\n");
	return 0; //返回结果个数
}

// lua调用C++ 或取lua传递的参数
int CTest1(lua_State* l)
{
	size_t len;
	const char* s = lua_tolstring(l, 1, &len);
	int n = lua_tonumber(l, 2);
	bool b = lua_toboolean(l, 3);
	printf("%s %d %d\n", s, n, b);
	return 0;
}

// 获取lua传递的列表
int CTestArr(lua_State* L)
{
	printf("init arr\n");
	int len = luaL_getn(L, 1);
	for (int i = 1; i <= len; i++) {
		lua_pushnumber(L, i);  //1 ：栈底部压数字
		lua_gettable(L, 1); // 2 ：将1 的数字弹出， 将table[i] 压栈底
		size_t size;
		printf("%s\n", lua_tolstring(L, -1, &size));
		// 将2的表数字弹出
		lua_pop(L, 1);
	}

	return 0; //返回结果个数
}

// 获取lua传递的表
int CTestTab(lua_State* L)
{
	
	// 0、获取 1 栈中的位置， name 是key
	lua_getfield(L, 1, "name"); // 指定key获取值
	printf("=%s\n", lua_tostring(L, -1));
	
	// 1、循环遍历
	// lua_pushnil(L);
	//while (lua_next(L, 1) != 0) {

	//	// lua_next，key先入栈，val后入栈
	//	// 所以val在栈顶
	//	printf("key = %s\n", lua_tostring(L, -2));
	//	printf("vale = %s\n", lua_tostring(L, -1));
	//	lua_pop(L, 1);
	//}

	// 2类型检查   第一个参数是啥
    // luaL_checktype(L, 1, LUA_TTABLE);  // 报错直接抛异常
	//if (lua_type(L, 1) != LUA_TTABLE) //  不抛异常
	//{
	//	luaL_argerror(l, 1, "bad argument");
	//}
	return 0;

}

// lua调用C++时，给lua返回值
int CTestRe(lua_State* L) {

	
	// 给栈顶放一个字符串
	lua_pushstring(L, "return value");

	// 将栈顶的元素弹出给 lua变量 ，弹出一个
	return 1;
}

// lua调用C++时，给lua返回表
int CTestReTable(lua_State* L) {

	lua_newtable(L);   // 入栈         /* creates a table */
	lua_pushstring(L, "name"); //   key 先入栈
	lua_pushstring(L, "c to lua name"); //   val 入栈
	// 此时 val 在栈顶， table在栈底

	// 弹出key value， 设置table
	lua_settable(L, -3);  // -3

	lua_pushstring(L, "age"); // -1  key
	lua_pushnumber(L, 9); // -2  val
	lua_settable(L, -3);  // -3
	return 1;
}


int main(int argc, char* argv[])
{
	lua_State *lua = lua_open();
	//打开基本库
	luaopen_base(lua);

	//打开table库
	luaopen_table(lua);

	//打开IO库
	luaL_openlibs(lua);

	//打开string库
	luaopen_string(lua);

	//打开math库
	luaopen_math(lua);

	// 注册函数 lua调用C++
	lua_register(lua, "CTest", CTest);
	lua_register(lua, "CTest1", CTest1);
	lua_register(lua, "CTestArr", CTestArr); 
	lua_register(lua, "CTestTab", CTestTab); 
	lua_register(lua, "CTestRe", CTestRe);
	lua_register(lua, "CTestReTable", CTestReTable);

	// C++ 给lua传递表
	lua_newtable(lua);   /* 创建表  此时栈中表在底部 */
	lua_pushstring(lua, "name");  
	lua_pushstring(lua, "张三");
	// 将前两个弹出，值放在表中
	lua_settable(lua, -3);
	lua_pushstring(lua, "age");
	lua_pushinteger(lua, 15);
	// 将前两个弹出，值放在表中
	lua_settable(lua, -3);

	// 将表设置成全局变量  栈顶设置为全局变量
	lua_setglobal(lua, "person");


	if (luaL_loadfile(lua, "main.lua"))
	{
		// 取顶部的栈， lua会把载入（编译）报错放在栈的顶部
	    // -1 是栈顶 1 栈底
		const char * error = lua_tostring(lua, -1);
		printf("%s\n 执行脚本文件失败", error);
		return -1;
	}

	// 执行过程的编译 
	if (lua_pcall(lua, 0, 0, 0))
	{
		const char * error = lua_tostring(lua, -1);
		printf("%s\n 执行脚本文件失败", error);

		return -1;
	}

	// C++ 调用lua *****
	// 获取lua全局变量

	// 获取全局变量放栈顶， 一般是搞参数配置
	lua_getglobal(lua, "lua");
	// 取栈顶
	printf("获取lua脚本全局变量 lua ta = %s\n", lua_tostring(lua, -1));
	// 恢复堆栈 弹出栈顶,弹出1一个值  1代表个数
	lua_pop(lua, 1);

	// 获取全局变量表放栈顶， 一般是搞参数配置
	lua_getglobal(lua, "conf");
	lua_getfield(lua, -1, "titlname");
	printf("title = %s\n", lua_tostring(lua, -1));
	lua_pop(lua, 1);
	lua_getfield(lua, -1, "height");
	printf("height = %d\n", (int)lua_tonumber(lua, -1));
	// 表， 两个值  一共三个
	lua_pop(lua, 1);
	lua_pop(lua, 1);


	// ****** C++调用lua函数
	// 获取栈顶，返回栈长度， 
	// 一般应为要回复栈，所以会前后打印，保证栈被回复
	printf("-------top is %d\n", lua_gettop(lua));
	int ferr = lua_gettop(lua);
	lua_getglobal(lua, "ferror");
	ferr++;
	lua_getglobal(lua, "event1");  // 写event1故意让报错
	// 若要参数则直接压， 注意lua_pcall的第二个参数，是该函数的参数个事
	lua_pushstring(lua, "key");  
	lua_newtable(lua);   /* 创建表  此时栈中表在底部 */
	lua_pushstring(lua, "name");
	lua_pushstring(lua, "张三");
	lua_settable(lua, -3);

	// 调用函数,  第二个参数 入参个数，第三个是返回值个数
	
	// 第四个参数，是异常处理时，函数转移跑出异常。
	// 此时需要注意堆栈多一个函数,最后需要pop，保持前后堆栈一致
	if (lua_pcall(lua, 2, 1, ferr) != 0) // ferr 将异常放栈顶，下面那个printf就是打印ferr的值        是
	{
		printf("%s 执行函数失败\n", lua_tostring(lua, -1));
		lua_pop(lua, 1);
	}
	else {

		//// 返回单值
		//printf("lua return ：%s\n ", lua_tostring(lua, -1));
		//lua_pop(lua, 1);
		// 返回表
		lua_getfield(lua, -1, "id");  // 将值压倒栈顶
		printf("return table id = %d\n", (int)lua_tonumber(lua, -1));
		lua_pop(lua, 2); // 表与值都要出栈

	}

	// 将ferro 出栈
	lua_pop(lua, 1);
	printf("------top is %d\n", lua_gettop(lua));

	return 0;
}

