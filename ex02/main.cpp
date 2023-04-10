#include "PmergeMe.hpp"

#include <chrono>/////

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "arg ERR" << std::endl;
        exit(1);
    }

    PmergeMe   pmerge_me(argv);

    pmerge_me.CallMergeInsertSort();

    pmerge_me.PrintVectorSort();
    pmerge_me.PrintDequeSort();
    pmerge_me.PrintListSort();
}
