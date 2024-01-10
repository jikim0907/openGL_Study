// #include <iostream>
#include <spdlog/spdlog.h>
#include <GLFW/glfw3.h>
using namespace std;

// int main(int argc,const char** argv){
//     cout << "hello" << endl;
//     return 0;
// }

int main(int argc, const char** argv) {
    // 시작을 알리는 로그
    SPDLOG_INFO("Start program");


    SPDLOG_INFO("Initialize glfw");
    if (!glfwInit()) {
        const char* description = nullptr;
        glfwGetError(&description); //에러 형태를 string으로 얻어오고 
        SPDLOG_ERROR("failed to initialize glfw: {}", description);//ERROR 레벨로 출력한다.
        return -1;
    }

    // glfw 윈도우 생성, 실패하면 에러 출력후 종료
    SPDLOG_INFO("Create glfw window");
    //glfwCreateWindow를 이용해서 윈도우 생성
    auto window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, //auto 변수타입 자동지정
      nullptr, nullptr);
    if (!window) {
        SPDLOG_ERROR("failed to create glfw window");
        glfwTerminate();
        return -1;
    }

    // glfw 루프 실행, 윈도우 close 버튼을 누르면 정상 종료
    SPDLOG_INFO("Start main loop");
    while (!glfwWindowShouldClose(window)) { //윈도우가 닫힌게 false면 loop를 돌게 된다.
        glfwPollEvents(); //윈도우에 관련한 이벤트가 발생했을 때 그 결과를 수집 -> 윈도우가 닫힐 때 
    }

    glfwTerminate();
    return 0;
}
