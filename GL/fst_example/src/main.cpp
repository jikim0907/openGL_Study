// #include <iostream>
#include <spdlog/spdlog.h>
#include <glad/glad.h> //glfw3 include하기 전에 추가해야한다.
#include <GLFW/glfw3.h>

using namespace std;

//when frame buffer size is chaned
void OnFramebufferSizeChange(GLFWwindow* window, int width, int height) {
    SPDLOG_INFO("framebuffer size changed: ({} x {})", width, height);
    glViewport(0, 0, width, height);
}

void OnKeyEvent(GLFWwindow* window,
    int key, int scancode, int action, int mods) {
    SPDLOG_INFO("key: {}, scancode: {}, action: {}, mods: {}{}{}",
        key, scancode,
        action == GLFW_PRESS ? "Pressed" :
        action == GLFW_RELEASE ? "Released" :
        action == GLFW_REPEAT ? "Repeat" : "Unknown",
        mods & GLFW_MOD_CONTROL ? "C" : "-",
        mods & GLFW_MOD_SHIFT ? "S" : "-",
        mods & GLFW_MOD_ALT ? "A" : "-");
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void Render() {
    glClearColor(0.1f, 0.2f, 0.3f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, const char** argv) {

    SPDLOG_INFO("Start program");

    SPDLOG_INFO("Initialize glfw");
    if (!glfwInit()) {
        const char* description = nullptr;
        glfwGetError(&description); //에러 형태를 string으로 얻어오고 
        SPDLOG_ERROR("failed to initialize glfw: {}", description);//ERROR 레벨로 출력한다.
        return -1;
    }

    //GLFW 윈도우를 생성하기 전에 만들기 희망하는 OpenGL 버전을 추가
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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
    
    //윈도우가 만들어지면서 함께 생성된 context를 사용
    //어떤 윈도우에 대해서 그려라 라는 기능이 없고, 현재 대상이 되는 context(윈도우)에 그림을 그리는 기능 뿐임
    glfwMakeContextCurrent(window);

    // glad를 활용한 OpenGL 함수 로딩
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        SPDLOG_ERROR("failed to initialize glad");
        glfwTerminate();
        return -1;
    } //이 코드 후에 GL 함수를 사용할 수 있다. glGetString와 같은 함수들....

    const char* glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));
    SPDLOG_INFO("OpenGL context version: {}", glVersion);

    //context 버퍼사이즈가 변경될 때 callback을 할 수 있게 하기 위한 설정
    OnFramebufferSizeChange(window, WINDOW_WIDTH, WINDOW_HEIGHT); //size 수동으로 변경
    glfwSetFramebufferSizeCallback(window,OnFramebufferSizeChange);
    glfwSetKeyCallback(window,OnKeyEvent);

    // glfw 루프 실행, 윈도우 close 버튼을 누르면 정상 종료
    SPDLOG_INFO("Start main loop");
    while (!glfwWindowShouldClose(window)) { //윈도우가 닫힌게 false면 loop를 돌게 된다.
        glfwPollEvents(); //윈도우에 관련한 이벤트가 발생했을 때 그 결과를 수집 -> 윈도우가 닫힐 때 
        glClearColor(0.0f, 0.1f, 0.2f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
