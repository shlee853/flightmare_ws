cmake_minimum_required(VERSION 3.00)
project(myprj_flightmare)

# C++ 표준 설정
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Ofast -march=native -fopenmp)

# 출력 디렉토리 설정 (실행 파일이 생길 곳)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

# ----------------------------------------------------------------
# 1. 필수 외부 라이브러리 찾기
# ----------------------------------------------------------------
# Flightlib 헤더 파일들이 내부적으로 Eigen과 OpenCV를 참조하므로
# 여기서도 찾아주어야 컴파일 에러가 나지 않습니다.
find_package(Eigen3 REQUIRED)
find_package(OpenCV REQUIRED)

# ----------------------------------------------------------------
# 2. Flightlib 경로 설정 (이미 빌드된 파일 사용)
# ----------------------------------------------------------------
# (A) 헤더 파일 경로 (소스 코드 위치)
set(FLIGHTLIB_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/../flightmare/flightlib/include)

# (B) 라이브러리 파일 경로 (중요!)
# catkin_make로 빌드했다면 보통 workspace/devel/lib 안에 생깁니다.
# 현재 CMakeLists.txt 위치 기준으로 ../../devel/lib/libflightlib.so 가 됩니다.
set(FLIGHTLIB_LIB_FILE ${CMAKE_SOURCE_DIR}/../../devel/lib/libflightlib.so)

# 만약 위 경로에 파일이 없다면, 아래 주석을 풀고 실제 경로를 적어주세요.
# set(FLIGHTLIB_LIB_FILE /절대경로/를/적으세요/libflightlib.so)

# ----------------------------------------------------------------
# 3. 실행 파일 생성
# ----------------------------------------------------------------
# 요청하신 소스 파일 이름으로 변경했습니다.
add_executable(fmp src/fmp_connection.cpp)

# ----------------------------------------------------------------
# 4. Include 및 링크 설정
# ----------------------------------------------------------------
# 헤더 파일 경로 추가
target_include_directories(fmp PUBLIC
    ${FLIGHTLIB_INCLUDE_DIR}
    ${EIGEN3_INCLUDE_DIR}
    ${OpenCV_INCLUDE_DIRS}
)

# 라이브러리 링크 (타겟 이름이 아니라 파일 경로를 직접 지정)
target_link_libraries(fmp PUBLIC
    ${FLIGHTLIB_LIB_FILE}  # Flightlib (.so 파일)
    ${OpenCV_LIBS}         # OpenCV
    zmq     # C 라이브러리
    zmqpp   # <--- 여기! 이 줄이 추가되어야 해결됩니다.
    pthread # (혹시 모를 스레드 에러 방지용)
    stdc++fs    
)