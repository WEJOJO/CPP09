#include "PmergeMe.hpp"

#include <chrono>/////

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "arg ERR" << std::endl;
        exit(1);
    }
    PmergeMe   pmerge_me(argv);
    pmerge_me.PrintOriginal();
    pmerge_me.CallMergeInsertSort();
    pmerge_me.PrintVectorSort();

    std::cout << "Time to process a range of  " << pmerge_me.GetOriginVector().size() << " elements with std::vector : " << pmerge_me.GetDurationVector().count()*0.001 << " us" << std::endl;
    std::cout << "Time to process a range of  " << pmerge_me.GetOriginDeque().size() << " elements with std::deque : " << pmerge_me.GetDurationDeque().count()*0.001 << " us" << std::endl;
    std::cout << "Time to process a range of  " << pmerge_me.GetOriginList().size() << " elements with std::list : " << pmerge_me.GetDurationList().count()*0.001 << " us" << std::endl;

    // std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
    // MergeSortVector(origin_vector, 0, origin_vector.size() - 1);
    // std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();
    // std::chrono::nanoseconds duration = std::chrono::duration_cast<std::chrono::nanoseconds>((end - start));
    // std::cout << "수행 시간: " << duration.count()*0.001 << " us" << std::endl;


    // pmerge_me.PrintDequeSort();
    // pmerge_me.PrintListSort();
}
