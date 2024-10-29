#include <stdio.h>
#include <stdlib.h>
#include <liegroup_robotics.h>
#include <iostream>
#include <chrono>  // 시간 측정을 위한 라이브러리
#include <ctime>   // 난수 생성을 위한 라이브러리
#include <cmath>   // M_PI 상수를 사용하기 위한 라이브러리

// shared object에서 제공하는 함수 선언
extern "C" {
    LIEGROUP_API void CoriolisMatrix_wrapper(const double* thetalist_array, const double* dthetalist_array, double* C_array);
}

int main() {
    // 난수 생성 초기화
    std::srand(std::time(0));

    // 랜덤 값으로 -π에서 +π 사이의 thetalist와 dthetalist 설정
    double thetalist[7];
    double dthetalist[7];
    for (int i = 0; i < 7; i++) {
        thetalist[i] = -M_PI + static_cast<double>(rand()) / RAND_MAX * (2 * M_PI);  // -π와 +π 사이의 랜덤 값
        dthetalist[i] = -M_PI + static_cast<double>(rand()) / RAND_MAX * (2 * M_PI); // -π와 +π 사이의 랜덤 값
    }

    double torques[7] = {0,};
    double C_array[7 * 7] = {0,};

    // 시간 측정 시작
    auto start = std::chrono::high_resolution_clock::now();

    // 함수 호출 반복문
    int num_iterations = 10000;
    for (int i = 0; i < num_iterations; i++) {
        CoriolisMatrix_wrapper(thetalist, dthetalist, C_array);
    }

    // 시간 측정 종료
    auto end = std::chrono::high_resolution_clock::now();

    // 전체 시간 및 평균 시간 계산 및 출력
    std::chrono::duration<double> elapsed = end - start;
    double average_time_per_call = (elapsed.count() * 1e6) / num_iterations; // 마이크로초로 변환

    std::cout << "Execution time for loop: " << elapsed.count() << " seconds." << std::endl;
    std::cout << "Average execution time per call: " << average_time_per_call << " microseconds." << std::endl;

    // 결과 출력
    MatrixNd C;
    std::cout << "C Result: " << std::endl;
    int count = 0;
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            C(j, i) = C_array[count++];
        }
    }

    std::cout << C << std::endl;

    return 0;
}
