#include <random>
#include <iostream>
#include <vector>

int main() {
    std::random_device rd; // 시드값 생성
    std::mt19937 gen(rd()); // Mersenne Twister 알고리즘 사용
    std::uniform_int_distribution<int> dis(1, 1000); // 1~1000 범위의 균등 분포 생성

    std::vector<int> nums(3000);
    for(int i = 0; i < 3000; i++) {
        nums[i] = dis(gen);
    }

    // 생성된 랜덤 정수 출력
    for(int i = 0; i < 3000; i++) {
        std::cout << nums[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
