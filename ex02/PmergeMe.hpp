#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>
#include <deque>
#include <list>
#include <iomanip>
#include <ctime>

class PmergeMe
{
private:
	std::vector<int> origin_vector;
    std::deque<int> origin_deque;
    std::list<int> origin_list;
	double	duration_vector;
	// std::chrono::nanoseconds duration_vector;
	double duration_list;
	double duration_deque;

	PmergeMe();
	PmergeMe(const PmergeMe& ref);

	void MakeSortVector(int st, int mid, int end, std::vector<int> &_origin);
	void MakeSortList(int st, int mid, int end, std::list<int> &_origin);
	void MakeSortDeque(int st, int mid, int end, std::deque<int> &_origin);
	//////////////////////////////////////////////////
	//////////////////////////////////////////////////
	void InsertSortVector(std::vector<int> &arr, int st, int end);
	void InsertSortList(std::list<int> &arr, int st, int end);
	void InsertSortDeque(std::deque<int> &arr, int st, int end);
	//////////////////////////////////////////////////
	//////////////////////////////////////////////////
	void MergeSortVector(std::vector<int> &_origin, int st, int end);
	void MergeSortList(std::list<int> &_origin, int st, int end);
	void MergeSortDeque(std::deque<int> &_origin, int st, int end);
	PmergeMe&	operator=(const PmergeMe& ref);

public:
	PmergeMe(char *argv[]);
	~PmergeMe();

	void Itos(int num, std::string &ret);
	void CallMergeInsertSort();
	void PrintVectorSort();
	void PrintListSort();
	void PrintDequeSort();
	std::vector<int>& GetOriginVector();
	std::list<int>& GetOriginList();
	std::deque<int>& GetOriginDeque();
	void PrintOriginal();
	//////////////////////////////////////////////////
	//////////////////////////////////////////////////
	double GetDurationVector();
	double GetDurationDeque();
	double GetDurationList();


};

#endif
