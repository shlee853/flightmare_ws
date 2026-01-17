#include <iostream>
#include <unistd.h> // for sleep

// Flightlib 헤더 파일
#include "flightlib/bridges/unity_bridge.hpp"
#include "flightlib/objects/quadrotor.hpp"
#include "flightlib/common/types.hpp"

using namespace flightlib;

int main() {
    // 1. Unity Bridge 초기화
    UnityBridge bridge;
    
    // [수정 1] connect() 함수 제거
    // Flightlib 버전에 따라 별도의 connect 호출 없이 객체 생성이나
    // addQuadrotor 단계에서 통신 준비가 완료됩니다.
    std::cout << "Unity Bridge 초기화..." << std::endl;

    // 2. 쿼드로터(드론) 객체 생성
    std::string config_path = "/root/workspace/catkin_ws/flightmare_ws/src/flightmare/flightlib/configs/quadrotor_env.yaml";
    std::shared_ptr<Quadrotor> quad_ptr = std::make_shared<Quadrotor>(config_path);

    // [수정 2] 초기 위치 설정 방식 변경 (setPosition -> reset)
    // 위치(p), 속도(v), 회전(q), 각속도(w)를 포함하는 State 객체를 만들어야 합니다.
    QuadState initial_state;
    initial_state.setZero();
    initial_state.p << 0.0, 0.0, 5.0; // 높이 5m에서 시작
    
    // reset을 사용하여 쿼드로터 상태를 초기화
    quad_ptr->reset(initial_state);

    // 3. Bridge에 쿼드로터 등록
    bridge.addQuadrotor(quad_ptr);

    std::cout << "시뮬레이션 루프 시작..." << std::endl;

    // 4. 시뮬레이션 루프
    const int total_steps = 500;
    
    // 상태를 받아올 변수 미리 선언
    QuadState current_state;

    for (int i = 0; i < total_steps; ++i) {
        
        // [수정 3] 상태 가져오기 방식 변경 (Return -> Pointer Argument)
        // 에러 메시지에 따르면 getState(QuadState* const state) 형태입니다.
        quad_ptr->getState(&current_state);

        // 간단한 동작: z축으로 아주 조금씩 상승
        current_state.p[2] += 0.01;
        
        // 변경된 상태 적용
        quad_ptr->setState(current_state);

        // (B) 렌더링 요청 및 상태 전송
        // 이 함수가 호출될 때 Unity로 데이터가 전송됩니다.
        bridge.getRender(true); 

        // 루프 속도 조절
        usleep(20000); // 20ms
    }

    std::cout << "시뮬레이션 종료." << std::endl;
    return 0;
}