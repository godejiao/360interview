#include <stdlib.h>
#include<iostream>
#include "qh_vector.h"
#include <assert.h>
#include <string>
using namespace std;
using namespace qh;

int main(int argc, char* argv[])
{
    //TODO ��������ӵ�Ԫ���ԣ�Խ��Խ�ã�����·��������ԽȫԽ��
    //TODO ��Ԫ����д����ο�INIParser�Ǹ���Ŀ����Ҫдһ��printf��Ҫ��assert���ж����жϡ�

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

