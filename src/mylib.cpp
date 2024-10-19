#include "mylib.h"

// Eigen을 사용하여 VectorXd의 합을 계산하는 함수
double vector_sum(const Eigen::VectorXd& vec) {
    return vec.sum();  // Eigen의 sum() 메서드를 사용하여 벡터 합 계산
}
