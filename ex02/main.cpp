#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>
#include <deque>
#include <list>

#include <chrono>/////

void MakeSortDeque(int st, int mid, int end, std::deque<int> &_origin) {
    std::deque<int> t1;
    std::deque<int> t2;
    int t1_ind = 0;
    int t2_ind = 0;
    int t_st = st;

    for (int t = st; t != mid + 1; t++)
        t1.push_back(_origin[t]);
    for (int t = mid + 1; t <= end; t++)
        t2.push_back(_origin[t]);

    while (st <= end) {
        if ((t1_ind < t1.size() && t1[t1_ind] <= t2[t2_ind]) ||
            t2_ind >= t2.size()) {
            _origin[st] = t1[t1_ind];
            t1_ind++;
        } else if ((t2_ind < t2.size() && t1[t1_ind] > t2[t2_ind]) ||
                   t1_ind >= t1.size()) {
            _origin[st] = t2[t2_ind];
            t2_ind++;
        }
        st++;
    }
}

void MakeSortVector(int st, int mid, int end, std::vector<int> &_origin) {
    std::vector<int> t1;
    std::vector<int> t2;
    int t1_ind = 0;
    int t2_ind = 0;
    int t_st = st;

    for (int t = st; t != mid + 1; t++)
        t1.push_back(_origin[t]);
    for (int t = mid + 1; t <= end; t++)
        t2.push_back(_origin[t]);

    while (st <= end) {
        if ((t1_ind < t1.size() && t1[t1_ind] <= t2[t2_ind]) ||
            t2_ind >= t2.size()) {
            _origin[st] = t1[t1_ind];
            t1_ind++;
        } else if ((t2_ind < t2.size() && t1[t1_ind] > t2[t2_ind]) ||
                   t1_ind >= t1.size()) {
            _origin[st] = t2[t2_ind];
            t2_ind++;
        }
        st++;
    }
}

void MakeSortList(int st, int mid, int end, std::list<int> &_origin) {
    std::list<int> t1;
    std::list<int> t2;
    std::list<int>::iterator iter;
    std::list<int>::iterator st_iter;
    std::list<int>::iterator t1_iter;
    std::list<int>::iterator t2_iter;


	int  i = 0;
	iter = _origin.begin();
	while(i < st)
	{
		iter++;
		i++;
	}
	st_iter = iter;
	while(i <= end)
	{
		if (i < mid+1)
			t1.push_back(*iter);
		else
			t2.push_back(*iter);
		iter++;
		i++;
	}
	t1_iter = t1.begin();
	t2_iter = t2.begin();
    while (st_iter != iter) {
        if ((t1_iter != t1.end() && *t1_iter <= *t2_iter) || t2_iter == t2.end()) {
            *st_iter = *t1_iter;
            t1_iter++;
        } else if ((t2_iter != t2.end() && *t1_iter > *t2_iter) || t1_iter == t1.end()) {
            *st_iter = *t2_iter;
            t2_iter++;
        }
        st_iter++;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
void InsertSortDeque(std::deque<int> &arr, int st, int end)
{
    int stand;
    int back_ind;

    for (int stand_ind = st + 1; stand_ind <= end; stand_ind++) {
        back_ind = stand_ind;
        stand = arr[stand_ind];
        for (int curr = stand_ind - 1; curr >= st; curr--) //st!
            if (stand < arr[curr]) {
                arr[back_ind] = arr[curr];
                back_ind--;
            }
        arr[back_ind] = stand;
    }
}

void InsertSortVector(std::vector<int> &arr, int st, int end)
{
    int stand;
    int back_ind;

    for (int stand_ind = st + 1; stand_ind <= end; stand_ind++) {
        back_ind = stand_ind;
        stand = arr[stand_ind];
        for (int curr = stand_ind - 1; curr >= st; curr--) //st!
            if (stand < arr[curr]) {
                arr[back_ind] = arr[curr];
                back_ind--;
            }
        arr[back_ind] = stand;
    }
}

void InsertSortList(std::list<int> &arr, int st, int end)
{
    int stand;
    std::list<int>::iterator iter;
    std::list<int>::iterator back_iter;
    std::list<int>::iterator start_iter;
    std::list<int>::iterator curr_iter;

    int i = 0;
    iter = arr.begin();
    while(i<st)
    {
        iter++;
        i++;
    }
    start_iter = iter;//변화없음
    iter++;
    i++;
    while(i<=end)
    {
        back_iter = iter;
        stand = *iter; //주석처리X 담고있어야 함
        iter--;
        curr_iter = iter; //한 칸 전 담기
        iter++; //iter 원상 복구
        while(curr_iter!=arr.begin() && curr_iter!=start_iter)//start_iter인 부분 와일 후에 처리 필요
        {
            if (stand < *curr_iter)//*iter
            {
                *back_iter = *curr_iter;
                back_iter--;
            }
            curr_iter--;
        }
        if (stand < *curr_iter)
        {
                *back_iter = *curr_iter;
                back_iter--;
        }
        *back_iter = stand;
        iter++;
        i++;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
void MergeSortDeque(std::deque<int> &_origin, int st, int end) {
    int mid;
    if (end-st+1 <= 100)
    {
        InsertSortDeque(_origin,st,end);
        return;
    }

    int _size = end - st + 1;
    mid = ((st + end) / 2);
    MergeSortDeque(_origin, st, mid);
    MergeSortDeque(_origin, mid + 1, end);
    MakeSortDeque(st, mid, end, _origin);
    return;
}

void MergeSortVector(std::vector<int> &_origin, int st, int end) {
    int mid;
    if (end-st+1 <= 100)///길이가 10이하인 배열에 관하여... // deque로 처리할 것이라면 ex00서 빼기 //(st == end) k==10인 상황
    {
        InsertSortVector(_origin,st,end);
        return;
    }

    ////////////////MergeSort Only////////////////
    // if (end==st)
    //     return;
    ////////////////MergeSort Only////////////////

    int _size = end - st + 1;
    mid = ((st + end) / 2);
    MergeSortVector(_origin, st, mid);
    MergeSortVector(_origin, mid + 1, end);
    MakeSortVector(st, mid, end, _origin);
    return;
}

void MergeSortList(std::list<int> &_origin, int st, int end) { //함수명 바꿔줄 것.
    int mid;
    if (end-st+1 <= 100)///길이가 10이하인 배열에 관하여... // deque로 처리할 것이라면 ex00서 빼기 //(st == end) k==10인 상황
    {
        InsertSortList(_origin,st,end);
        return;
    }

    // if (end == st)
    //     return ;
    int _size = end - st + 1;
    mid = ((st + end) / 2);
    MergeSortList(_origin, st, mid);
    MergeSortList(_origin, mid + 1, end);
    MakeSortList(st, mid, end, _origin);
    return;
}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
void Itos(int num, std::string &ret) {
	if (num >= 10) {
		Itos(num / 10, ret);
		ret += static_cast<char>((num % 10) + 48);
	} else
		ret += static_cast<char>(num + 48);
}

int main(int argc, char *argv[]) {
    std::vector<int> origin_vector;
    std::deque<int> origin_deque;
    std::list<int> origin_list;

    std::string token;

    if (argc < 2) {
        std::cout << "arg ERR" << std::endl;
        exit(1);
    }
    int i = 1;
    int node;

    while (argv[i]) {
        std::stringstream ss(argv[i]);
        while (ss >> token)
        {
            node = atoi(token.c_str());
            std::string _itos; // 초기화
            Itos(node, _itos);
            if (node <= 0 || _itos != token)
            {
                std::cout << "Error: arg err" << std::endl;
                exit(1);
            }
            origin_vector.push_back(node);
            origin_deque.push_back(node);
            origin_list.push_back(node);
        }
        i++;
    }

    // std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
    MergeSortVector(origin_vector, 0, origin_vector.size() - 1);
    // std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();
    // std::chrono::nanoseconds duration = std::chrono::duration_cast<std::chrono::nanoseconds>((end - start));
    // std::cout << "수행 시간: " << duration.count()*0.001 << " us" << std::endl;

    MergeSortDeque(origin_deque, 0, origin_deque.size() - 1);
    MergeSortList(origin_list, 0, origin_list.size() - 1);





    std::cout << "=======vector========" << std::endl;
    for (int j = 0; j < origin_vector.size(); j++)
        std::cout << origin_vector[j] << " ";
    std::cout << std::endl;

    std::cout << "=======deque========" << std::endl;
    for (int j = 0; j < origin_deque.size(); j++)
        std::cout << origin_deque[j] << " ";
    std::cout << std::endl;

    std::cout << "=======list========" << std::endl;
	std::list<int>::iterator o_iter;
	o_iter = origin_list.begin();
	for (;o_iter!=origin_list.end();o_iter++)
		std::cout << *o_iter << " ";
	std::cout << std::endl;
}
