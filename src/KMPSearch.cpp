#include "KMPSearch.h"


//#define METHOD_1
using namespace std;

vector<int> kmpAlgorithm(const string& H, const string& N, int* pi);
void calcPi(const string& N, int* pi);
int max(int v1, int v2);

int main(void)
{
	string H = "aabaabacaabaabacaabaabac";
	string N = "aabaabac";

	vector<int> position;
	vector<int>::iterator it;

	int* pi = new int[N.size()-1];
	for (int i = 0; i < N.size(); ++i)
	{
		pi[i] = 0;
	}
	calcPi(N, pi);

	position = kmpAlgorithm(H, N, pi);

	for (it = position.begin(); it != position.end(); ++it)
	{
		cout << *it << endl;
	}

	return 0;
}

void calcPi(const string& N, int* pi)
{
#ifdef METHOD_1 /* O(N^3) */
	int m = N.size();
	for (int begin = 1; begin < m; ++begin)
	{
		for (int i = 0; i + begin < m; ++i)
		{
			if (N[begin + i] != N[i]) break;
			// i+1 글자가 대응
			pi[begin + i] = max(pi[begin + i], i + 1);
		}
	}
#elif defined(METHOD_2)
	int m = N.size();
	for (int begin = 1; begin < m; ++begin)
	{
		for (int i = 0; (i + begin) < m; ++i)
		{
			if (N[begin + i] != N[i]) break;
			/* 기존 pi 값 갱신 */
			pi[begin + i] = max(pi[begin + i], i + 1);
		}
	}
#else /* Method 3 (Use KMP Algorithm) */
	int m = N.size();
	int begin = 1, matched = 0;

	while (begin + matched < m)
	{
		if (N[begin + matched] == N[matched])
		{
			++matched;
			pi[begin + matched - 1] = matched;/* 매칭이 이루어질 때마다 pi value 수정 */
		}
		else
		{
			if (matched == 0) /* 일치하는 것이 없는 경우 */
				++begin;
			else
			{
				begin += matched - pi[begin + matched];
				matched = pi[matched - 1];
			}
		}
	}
#endif
}

int max(int v1, int v2)
{
	if (v1 >= v2)
		return v1;
	return v2;
}

/* KMP Algorithm */
vector<int> kmpAlgorithm(const string& H, const string& N, int* pi)
{
	vector<int> ret;

	int n = H.size();
	int m = N.size();

	int begin = 0;
	int matched = 0;

	while (begin <= (n - m))
	{
		if (matched < m && H[begin + matched] == N[matched])
		{
			++matched;
			if (matched == m) ret.push_back(begin);
		}
		else
		{
			if (matched == 0)
				++begin;
			else
			{
				begin += matched - pi[matched - 1];
				//begin을 옮겨도 pi[matched-1] 만큼은 일치하니깐 matched를 접두, 접미사가 되는 string 길이만큼 더 움직여도 괜찮음
				matched = pi[matched - 1];
			}
		}
	}
	return ret;
}
