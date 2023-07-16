// 01HelloLua.cpp : �������̨Ӧ�ó������ڵ㡣
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
	return 0; //���ؽ������
}

// lua����C++ ��ȡlua���ݵĲ���
int CTest1(lua_State* l)
{
	size_t len;
	const char* s = lua_tolstring(l, 1, &len);
	int n = lua_tonumber(l, 2);
	bool b = lua_toboolean(l, 3);
	printf("%s %d %d\n", s, n, b);
	return 0;
}

// ��ȡlua���ݵ��б�
int CTestArr(lua_State* L)
{
	printf("init arr\n");
	int len = luaL_getn(L, 1);
	for (int i = 1; i <= len; i++) {
		lua_pushnumber(L, i);  //1 ��ջ�ײ�ѹ����
		lua_gettable(L, 1); // 2 ����1 �����ֵ����� ��table[i] ѹջ��
		size_t size;
		printf("%s\n", lua_tolstring(L, -1, &size));
		// ��2�ı����ֵ���
		lua_pop(L, 1);
	}

	return 0; //���ؽ������
}

// ��ȡlua���ݵı�
int CTestTab(lua_State* L)
{
	
	// 0����ȡ 1 ջ�е�λ�ã� name ��key
	lua_getfield(L, 1, "name"); // ָ��key��ȡֵ
	printf("=%s\n", lua_tostring(L, -1));
	
	// 1��ѭ������
	// lua_pushnil(L);
	//while (lua_next(L, 1) != 0) {

	//	// lua_next��key����ջ��val����ջ
	//	// ����val��ջ��
	//	printf("key = %s\n", lua_tostring(L, -2));
	//	printf("vale = %s\n", lua_tostring(L, -1));
	//	lua_pop(L, 1);
	//}

	// 2���ͼ��   ��һ��������ɶ
    // luaL_checktype(L, 1, LUA_TTABLE);  // ����ֱ�����쳣
	//if (lua_type(L, 1) != LUA_TTABLE) //  �����쳣
	//{
	//	luaL_argerror(l, 1, "bad argument");
	//}
	return 0;

}

// lua����C++ʱ����lua����ֵ
int CTestRe(lua_State* L) {

	
	// ��ջ����һ���ַ���
	lua_pushstring(L, "return value");

	// ��ջ����Ԫ�ص����� lua���� ������һ��
	return 1;
}

// lua����C++ʱ����lua���ر�
int CTestReTable(lua_State* L) {

	lua_newtable(L);   // ��ջ         /* creates a table */
	lua_pushstring(L, "name"); //   key ����ջ
	lua_pushstring(L, "c to lua name"); //   val ��ջ
	// ��ʱ val ��ջ���� table��ջ��

	// ����key value�� ����table
	lua_settable(L, -3);  // -3

	lua_pushstring(L, "age"); // -1  key
	lua_pushnumber(L, 9); // -2  val
	lua_settable(L, -3);  // -3
	return 1;
}


int main(int argc, char* argv[])
{
	lua_State *lua = lua_open();
	//�򿪻�����
	luaopen_base(lua);

	//��table��
	luaopen_table(lua);

	//��IO��
	luaL_openlibs(lua);

	//��string��
	luaopen_string(lua);

	//��math��
	luaopen_math(lua);

	// ע�ắ�� lua����C++
	lua_register(lua, "CTest", CTest);
	lua_register(lua, "CTest1", CTest1);
	lua_register(lua, "CTestArr", CTestArr); 
	lua_register(lua, "CTestTab", CTestTab); 
	lua_register(lua, "CTestRe", CTestRe);
	lua_register(lua, "CTestReTable", CTestReTable);

	// C++ ��lua���ݱ�
	lua_newtable(lua);   /* ������  ��ʱջ�б��ڵײ� */
	lua_pushstring(lua, "name");  
	lua_pushstring(lua, "����");
	// ��ǰ����������ֵ���ڱ���
	lua_settable(lua, -3);
	lua_pushstring(lua, "age");
	lua_pushinteger(lua, 15);
	// ��ǰ����������ֵ���ڱ���
	lua_settable(lua, -3);

	// �������ó�ȫ�ֱ���  ջ������Ϊȫ�ֱ���
	lua_setglobal(lua, "person");


	if (luaL_loadfile(lua, "main.lua"))
	{
		// ȡ������ջ�� lua������루���룩�������ջ�Ķ���
	    // -1 ��ջ�� 1 ջ��
		const char * error = lua_tostring(lua, -1);
		printf("%s\n ִ�нű��ļ�ʧ��", error);
		return -1;
	}

	// ִ�й��̵ı��� 
	if (lua_pcall(lua, 0, 0, 0))
	{
		const char * error = lua_tostring(lua, -1);
		printf("%s\n ִ�нű��ļ�ʧ��", error);

		return -1;
	}

	// C++ ����lua *****
	// ��ȡluaȫ�ֱ���

	// ��ȡȫ�ֱ�����ջ���� һ���Ǹ��������
	lua_getglobal(lua, "lua");
	// ȡջ��
	printf("��ȡlua�ű�ȫ�ֱ��� lua ta = %s\n", lua_tostring(lua, -1));
	// �ָ���ջ ����ջ��,����1һ��ֵ  1�������
	lua_pop(lua, 1);

	// ��ȡȫ�ֱ������ջ���� һ���Ǹ��������
	lua_getglobal(lua, "conf");
	lua_getfield(lua, -1, "titlname");
	printf("title = %s\n", lua_tostring(lua, -1));
	lua_pop(lua, 1);
	lua_getfield(lua, -1, "height");
	printf("height = %d\n", (int)lua_tonumber(lua, -1));
	// �� ����ֵ  һ������
	lua_pop(lua, 1);
	lua_pop(lua, 1);


	// ****** C++����lua����
	// ��ȡջ��������ջ���ȣ� 
	// һ��ӦΪҪ�ظ�ջ�����Ի�ǰ���ӡ����֤ջ���ظ�
	printf("-------top is %d\n", lua_gettop(lua));
	int ferr = lua_gettop(lua);
	lua_getglobal(lua, "ferror");
	ferr++;
	lua_getglobal(lua, "event1");  // дevent1�����ñ���
	// ��Ҫ������ֱ��ѹ�� ע��lua_pcall�ĵڶ����������Ǹú����Ĳ�������
	lua_pushstring(lua, "key");  
	lua_newtable(lua);   /* ������  ��ʱջ�б��ڵײ� */
	lua_pushstring(lua, "name");
	lua_pushstring(lua, "����");
	lua_settable(lua, -3);

	// ���ú���,  �ڶ������� ��θ������������Ƿ���ֵ����
	
	// ���ĸ����������쳣����ʱ������ת���ܳ��쳣��
	// ��ʱ��Ҫע���ջ��һ������,�����Ҫpop������ǰ���ջһ��
	if (lua_pcall(lua, 2, 1, ferr) != 0) // ferr ���쳣��ջ���������Ǹ�printf���Ǵ�ӡferr��ֵ        ��
	{
		printf("%s ִ�к���ʧ��\n", lua_tostring(lua, -1));
		lua_pop(lua, 1);
	}
	else {

		//// ���ص�ֵ
		//printf("lua return ��%s\n ", lua_tostring(lua, -1));
		//lua_pop(lua, 1);
		// ���ر�
		lua_getfield(lua, -1, "id");  // ��ֵѹ��ջ��
		printf("return table id = %d\n", (int)lua_tonumber(lua, -1));
		lua_pop(lua, 2); // ����ֵ��Ҫ��ջ

	}

	// ��ferro ��ջ
	lua_pop(lua, 1);
	printf("------top is %d\n", lua_gettop(lua));

	return 0;
}

