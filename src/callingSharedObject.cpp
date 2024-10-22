#include <stdio.h>
#include <stdlib.h>
#include <liegroup_robotics.h>
#include <iostream>

// shared object에서 제공하는 함수 선언
extern "C" {
    LIEGROUP_API void GravityForces_wrapper(const double* thetalist_array,double* torque_array) ;

}

int main() {
    // 테스트용 thetalist 값 설정
    double thetalist[7] = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6};
    double torques[7] ={0,};
    // 함수 호출
    for(int i =0;i<10000;i++)
     GravityForces_wrapper(thetalist,torques);

    // 결과 출력
    std::cout << "Gravity Forces Result: " << std::endl;
    for (int i = 0; i < 7; i++) {
        std::cout << "result[" << i << "] = " << torques[i] << std::endl;
    }

    // 동적으로 할당된 메모리 해제
    // delete[] result;

    return 0;
}
