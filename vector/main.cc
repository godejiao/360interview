#include <stdlib.h>
#include<iostream>
#include "qh_vector.h"
#include <assert.h>
#include <string>
using namespace std;
using namespace qh;

int main(int argc, char* argv[])
{
    //TODO 在这里添加单元测试，越多越好，代码路径覆盖率越全越好
    //TODO 单元测试写法请参考INIParser那个项目，不要写一堆printf，要用assert进行断言判断。

   	vector<int>veci;
	assert(veci.size()==0);
	//cout << veci.size() << endl;
	for (int i = 0; i != 10; ++i)
		veci.push_back(i);
	veci.pop_back();
	size_t index=0;
	for (auto &r : veci)
		assert(r==veci[index++]);
    assert(veci.size()==9);
	for(int i=0;i!=veci.size();++i)
		assert(veci[i]==i);
	

#ifdef WIN32
    system("pause");
#endif

	return 0;
}

