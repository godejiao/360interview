#include <stdio.h>
#include <assert.h>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

#define H_ARRAYSIZE(a) \
    ((sizeof(a) / sizeof(*(a))) / \
    static_cast<size_t>(!(sizeof(a) % sizeof(*(a)))))

struct Mountain
{
	int left;
	int high;
	int right;
};
/*--------------将字符串肢解成山的三维--------------------*/
vector<Mountain>getMountian(string &s)
{
	vector<string>moun;
	size_t mountian_size = stoi(s);//得到山的座数
	vector<int>enter_pos;//'\n'的位置
	size_t pos = 0;//'\n'的当前位置
	for(int i=0;i!=mountian_size;++i){
		pos = s.find('\n', pos);
		++pos;
		enter_pos.push_back(pos);
	}
	for (int i = 0; i != mountian_size - 1; ++i) {
		string c;//每座山的三维的字符串，带有','
		c.assign(s.begin() + enter_pos[i], s.begin() + enter_pos[i + 1]-1);
		moun.push_back(c);
	}
	string c;
	c.assign(s.begin() + enter_pos[mountian_size - 1], s.end());
	moun.push_back(c);
	
	/*---------将每座山的字符串肢解成整数--------------*/
	vector<Mountain>mountian(mountian_size,Mountain());
	size_t i = 0;
	for (auto &r : moun) {
		size_t comma = 0;		
		mountian[i].left = stoi(r);
		//cout << "left: "<<stoi(r) << endl;
		comma = r.find(',', comma);
		++comma;
		//cout << string(r.begin() + comma, r.end()) << endl << "right: " << stoi(string(r.begin() + comma, r.end())) << endl;
		mountian[i].right = stoi(string(r.begin() + comma, r.end()));
		comma = r.find(',', comma);
		++comma;
		//cout << string(r.begin() + comma, r.end()) << endl << "hight: " << stoi(string(r.begin() + comma, r.end())) << endl;
		mountian[i].high = stoi(string(r.begin() + comma, r.end()));
		++i;
	}
	return mountian;
}
/*---------当前山顶到达下一座山的steps---------*/
int getVerticalStepsToNextMoun(Mountain &curr, Mountain&next)
{
	if (curr.right < next.left)
		return curr.high + next.high;//下山curr，上山next；
	else
		return abs(curr.high - next.high);
}

int resolve(const char* input)
{
	string s = input;
	auto mountian=getMountian(s);
	for (int i = 0; i != mountian.size(); ++i)
	    	cout << mountian[i].left << " " << mountian[i].high << " "<< mountian[i].right << endl;
	int steps = 0;

	int vertical_steps = mountian[0].high;
	for (int i = 0; i != mountian.size()-1; ++i) {
		vertical_steps += getVerticalStepsToNextMoun(mountian[i], mountian[i + 1]);
	}
	vertical_steps += mountian[mountian.size() - 1].high;

	steps += vertical_steps + mountian[mountian.size() - 1].right;
	return steps;
}

int main(int argc, char* argv[]) 
{
    const char* input[] = {
        "3\n1,3,2\n2,4,4\n6,7,5\n", //The giving example
        "1\n1,2,1\n",
        "2\n1,2,1\n2,3,2",
        "3\n1,2,1\n2,3,2\n3,6,1",
        "4\n1,2,1\n2,3,2\n3,6,1\n5,8,2",
        "5\n1,2,1\n2,3,2\n3,6,1\n5,8,2\n7,9,1",
        "1\n0,1,1",
        "2\n0,1,1\n2,4,3",
        "3\n0,1,1\n2,4,3\n3,5,1",
        "4\n0,1,1\n2,4,3\n3,5,1\n5,6,1",
        "5\n0,1,1\n2,4,3\n3,5,1\n5,6,1\n6,8,3",
        //TODO please add more test case here
        };
    int expectedSteps[] = {25, 4, 7, 10, 14, 15, 3, 12, 13, 14, 20};
    for (size_t i = 0; i < H_ARRAYSIZE(input); ++i)
    {
        assert(resolve(input[i]) == expectedSteps[i]);
    }
    return 0;
}
