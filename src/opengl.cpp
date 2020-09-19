//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <iostream>
//
//using namespace std;
//
//void framebuffer_size_callback(GLFWwindow *window, int width, int height);
//void processInput(GLFWwindow *window);
//
////GLFW：GLFW是一个专门针对OpenGL的C语言库，它提供了一些渲染物体所需的最低限度的接口。
////它允许用户创建OpenGL上下文，定义窗口参数以及处理用户输入，这正是我们需要的。
//
////GLAD：因为OpenGL只是一个标准/规范，具体的实现是由驱动开发商针对特定显卡实现的。由于OpenGL驱动版本众多，
////它大多数函数的位置都无法在编译时确定下来，需要在运行时查询。所以任务就落在了开发者身上，
////开发者需要在运行时获取函数地址并将其保存在一个函数指针中供以后使用。
////取得地址的方法因平台而异，在Windows上会是类似这样：
//// 定义函数原型
////typedef void (*GL_GENBUFFERS) (GLsizei, GLuint*);
//// 找到正确的函数并赋值给函数指针
////GL_GENBUFFERS glGenBuffers  = (GL_GENBUFFERS)wglGetProcAddress("glGenBuffers");
//// 现在函数可以被正常调用了
////GLuint buffer;
////glGenBuffers(1, &buffer);
////你可以看到代码非常复杂，而且很繁琐，我们需要对每个可能使用的函数都要重复这个过程。幸运的是，有些库能简化此过程，其中GLAD是目前最新，也是最流行的库。
//int main(int argc, const char *argv[])
//{
//    int w = 800,h = 600;
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//#ifdef __APPLE__
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
//#endif
//
//
//    GLFWwindow *window = glfwCreateWindow(w, h, "LearnOpenGL", NULL, NULL);
//    if (window == NULL)
//    {
//        std::cout << "fail to create window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//
//    glfwMakeContextCurrent(window);
//    //注册这个函数，告诉GLFW我们希望每当窗口调整大小的时候调用这个函数
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//    {
//        std::cout << "Failed to initialize GLAD" << std::endl;
//        return -1;
//    }
//    //查询GL_MAX_VERTEX_ATTRIBS来获取具体的上限
//    int nrAttributes;
//    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
//    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
//    //①顶点着色器:
//    const char *vertexShaderSource = "#version 330 core\n"
//    "layout (location = 0) in vec3 aPos;\n"// 位置变量的属性位置值为0
//    "out vec4 vertexColor;\n"// 为片段着色器指定一个颜色输出
//    "void main()\n"
//    "{\n"
//        // "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//        "gl_Position = vec4(aPos,1.0);\n"// 注意我们如何把一个vec3作为vec4的构造器的参数
//        "vertexColor = vec4(0.5,0.0,0.0,1.0);\n"// 把输出变量设置为暗红色
//    "}\0";
//    //②编译顶点着色器:
//    //我们首先要做的是创建一个着色器对象，注意还是用ID来引用的。所以我们储存这个顶点着色器为unsigned int，然后用glCreateShader创建这个着色器
//    unsigned int vertexShader;
//    vertexShader = glCreateShader(GL_VERTEX_SHADER);
//    //把这个着色器源码附加到着色器对象上，然后编译它：
//    //glShaderSource函数把要编译的着色器对象作为第一个参数。
//    //第二参数指定了传递的源码字符串数量，这里只有一个。
//    //第三个参数是顶点着色器真正的源码，
//    //第四个参数我们先设置为NULL。
//    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//    glCompileShader(vertexShader);
//    //[OPTIONAL]检查是否编译成功
//    //定义一个整型变量来表示是否成功编译
//    int  success;
//    //定义了一个储存错误消息（如果有的话）的容器
//    char infoLog[512];
//    //用glGetShaderiv检查是否编译成功。如果编译失败，我们会用glGetShaderInfoLog获取错误消息
//    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//    //打印它。
//    if(!success)
//    {
//        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//        cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
//    }else{
//        cout << "SHADER::VERTEX::COMPILATION_SUCCESS" << endl;
//    }
//    //③片段着色器:
//    const char *fragmentShaderSource = "#version 330 core\n"
//    "out vec4 FragColor;\n"
//    "in vec4 vertexColor;\n"// 从顶点着色器传来的输入变量（名称相同、类型相同）
//    "void main()\n"
//    "{\n"
//        // "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//        "FragColor = vertexColor;\n"
//    "}\n\0";
//    //④编译片段着色器：
//    //编译片段着色器的过程与顶点着色器类似，只不过我们使用GL_FRAGMENT_SHADER常量作为着色器类型：
//    unsigned int fragmentShader;
//    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//    glCompileShader(fragmentShader);
//    //[OPTIONAL]检查是否编译成功
//    //用glGetShaderiv检查是否编译成功。如果编译失败，我们会用glGetShaderInfoLog获取错误消息
//    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
//    //打印它。
//    if(!success)
//    {
//        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
//        cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
//    }else{
//        cout << "SHADER::FRAGMENT::COMPILATION_SUCCESS" << endl;
//    }
//    //⑤着色器程序：
//    //着色器程序对象(Shader Program Object)是多个着色器合并之后并最终链接完成的版本。如果要使用刚才编译的着色器我们必须把它们链接(Link)为一个着色器程序对象，然后在渲染对象的时候激活这个着色器程序。已激活着色器程序的着色器将在我们发送渲染调用的时候被使用。
//    //当链接着色器至一个程序的时候，它会把每个着色器的输出链接到下个着色器的输入。当输出和输入不匹配的时候，你会得到一个连接错误。
//    unsigned int shaderProgram;
//    shaderProgram = glCreateProgram();
//    //⑥链接着色器
//    //glCreateProgram函数创建一个程序，并返回新创建程序对象的ID引用。现在我们需要把之前编译的着色器附加到程序对象上，然后用glLinkProgram链接它们：
//    glAttachShader(shaderProgram, vertexShader);
//    glAttachShader(shaderProgram, fragmentShader);
//    glLinkProgram(shaderProgram);
//    //[OPTIONAL]检查是否链接成功
//    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//    if(!success) {
//        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
//        cout << "LINK::PROGRAM::LINK_FAILED" << endl;
//    }else{
//        cout << "LINK::PROGRAM::LINK_SUCCESS" << endl;
//    }
//    //得到的结果就是一个程序对象，我们可以调用glUseProgram函数，用刚创建的程序对象作为它的参数，以激活这个程序对象：
//    // glUseProgram(shaderProgram);
//    //在把着色器对象链接到程序对象以后，记得删除着色器对象，我们不再需要它们了：
//    glDeleteShader(vertexShader);
//    glDeleteShader(fragmentShader);
//
//
//    float vertices[] = {
//        0.5f, 0.5f, 0.0f,   // 右上角
//        0.5f, -0.5f, 0.0f,  // 右下角
//        -0.5f, -0.5f, 0.0f, // 左下角
//        -0.5f, 0.5f, 0.0f   // 左上角
//    };
//
//    // float vertices[] = {
//    // -0.5f, -0.5f, 0.0f,
//    //  0.5f, -0.5f, 0.0f,
//    //  0.0f,  0.5f, 0.0f
//    // };
//    unsigned int indices[] = { // 注意索引从0开始!
//        0, 1, 3, // 第一个三角形
//        1, 2, 3  // 第二个三角形
//    };
//    unsigned int VBO, VAO, EBO;
//    //⑦顶点数组对象(Vertex Array Object, VAO)：
//    //顶点数组对象(Vertex Array Object, VAO)可以像顶点缓冲对象那样被绑定，任何随后的顶点属性调用都会储存在这个VAO中。
//    //这样的好处就是，当配置顶点属性指针时，你只需要将那些调用执行一次，之后再绘制物体的时候只需要绑定相应的VAO就行了。这使在不同顶点数据和属性配置之间切换变得非常简单，只需要绑定不同的VAO就行了。刚刚设置的所有状态都将存储在VAO中
//    glGenVertexArrays(1, &VAO);
//    //顶点缓冲对象是我们在OpenGL教程中第一个出现的OpenGL对象。就像OpenGL中的其它对象一样，这个缓冲有一个独一无二的ID，所以我们可以使用glGenBuffers函数和一个缓冲ID生成一个VBO对象：
//    glGenBuffers(1, &VBO);
//    glGenBuffers(1, &EBO);
//    //要想使用VAO，要做的只是使用glBindVertexArray绑定VAO。从绑定之后起，我们应该绑定和配置对应的VBO和属性指针，之后解绑VAO供之后使用。
//    //当我们打算绘制一个物体的时候，我们只要在绘制物体前简单地把VAO绑定到希望使用的设定上就行了。这段代码应该看起来像这样:
//    // ..:: 初始化代码（只运行一次 (除非你的物体频繁改变)） :: ..
//    // !!!1. 绑定VAO
//    glBindVertexArray(VAO);
//    //!!!把我们的顶点数组复制到一个顶点缓冲中，供OpenGL使用
//    //OpenGL有很多缓冲对象类型，顶点缓冲对象的缓冲类型是GL_ARRAY_BUFFER。OpenGL允许我们同时绑定多个缓冲，只要它们是不同的缓冲类型。我们可以使用glBindBuffer函数把新创建的缓冲绑定到GL_ARRAY_BUFFER目标上
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    //从这一刻起，我们使用的任何（在GL_ARRAY_BUFFER目标上的）缓冲调用都会用来配置当前绑定的缓冲(VBO)。然后我们可以调用glBufferData函数，它会把之前定义的顶点数据复制到缓冲的内存中：
//    //glBufferData是一个专门用来把用户定义的数据复制到当前绑定缓冲的函数。
//    //它的第一个参数是目标缓冲的类型：顶点缓冲对象当前绑定到GL_ARRAY_BUFFER目标上。
//    //第二个参数指定传输数据的大小(以字节为单位)；用一个简单的sizeof计算出顶点数据大小就行。
//    //第三个参数是我们希望发送的实际数据。
//    //第四个参数指定了我们希望显卡如何管理给定的数据。它有三种形式：
//    //GL_STATIC_DRAW ：数据不会或几乎不会改变。
//    //GL_DYNAMIC_DRAW：数据会被改变很多。
//    //GL_STREAM_DRAW ：数据每次绘制时都会改变。
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    //!!!复制我们的索引数组到一个索引缓冲中，供OpenGL使用
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//    //⑧链接顶点属性
//    //glVertexAttribPointer函数的参数非常多，所以我会逐一介绍它们：
//    //第一个参数指定我们要配置的顶点属性。还记得我们在顶点着色器中使用layout(location = 0)定义了position顶点属性的位置值(Location)吗？它可以把顶点属性的位置值设置为0。
//    //因为我们希望把数据传递到这一个顶点属性中，所以这里我们传入0。
//    //第二个参数指定顶点属性的大小。顶点属性是一个vec3，它由3个值组成，所以大小是3。
//    //第三个参数指定数据的类型，这里是GL_FLOAT(GLSL中vec*都是由浮点数值组成的)。
//    //第四个参数定义我们是否希望数据被标准化(Normalize)。如果我们设置为GL_TRUE，所有数据都会被映射到0（对于有符号型signed数据是-1）到1之间。我们把它设置为GL_FALSE。
//    //第五个参数叫做步长(Stride)，它告诉我们在连续的顶点属性组之间的间隔。由于下个组位置数据在3个float之后，我们把步长设置为3 * sizeof(float)。
//    //要注意的是由于我们知道这个数组是紧密排列的（在两个顶点属性之间没有空隙）我们也可以设置为0来让OpenGL决定具体步长是多少（只有当数值是紧密排列时才可用）。
//    //一旦我们有更多的顶点属性，我们就必须更小心地定义每个顶点属性之间的间隔，我们在后面会看到更多的例子（译注: 这个参数的意思简单说就是从这个属性第二次出现的地方到整个数组0位置之间有多少字节）。
//    //第六个参数的类型是void*，所以需要我们进行这个奇怪的强制类型转换。它表示位置数据在缓冲中起始位置的偏移量(Offset)。由于位置数据在数组的开头，所以这里是0。我们会在后面详细解释这个参数。
//
//    //1. 设置顶点属性指针
//    //每个顶点属性从一个VBO管理的内存中获得它的数据，而具体是从哪个VBO（程序中可以有多个VBO）获取则是通过在调用glVertexAttribPointer时绑定到GL_ARRAY_BUFFER的VBO决定的。
//    //由于在调用glVertexAttribPointer之前绑定的是先前定义的VBO对象，顶点属性0现在会链接到它的顶点数据。
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//    //现在我们已经定义了OpenGL该如何解释顶点数据，我们现在应该使用glEnableVertexAttribArray，以顶点属性位置值作为参数，启用顶点属性；顶点属性默认是禁用的。
//    glEnableVertexAttribArray(0);
//
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    // glBindVertexArray(0);
//    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//    //渲染循环(Render Loop)
//    while (!glfwWindowShouldClose(window))
//    {
//        //我们还可以将我们的函数注册到其它很多的回调函数中。
//        //比如说，我们可以创建一个回调函数来处理手柄输入变化，处理错误消息等。
//        //我们会在创建窗口之后，渲染循环初始化之前注册这些回调函数。
//        processInput(window);
//        //glClearColor函数是一个状态设置函数
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        //而glClear函数则是一个状态使用的函数，它使用了当前的状态来获取应该清除为的颜色。
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        //⑨绘制物体
//        //当我们渲染一个物体时要使用着色器程序
//        glUseProgram(shaderProgram);
//        // glBindVertexArray(VAO);因为之前绑定过了，只要不调用glBindVertexArray(0);来清除的话，这里可以不用再次绑定了
//        // glDrawArrays(GL_TRIANGLES, 0, 3);
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//
//        //glfwSwapBuffers函数会交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色值的大缓冲），
//        //它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上。
//        //双缓冲(Double Buffer):详见README.md
//        glfwSwapBuffers(window);
//        //glfwPollEvents函数检查有没有触发什么事件（比如键盘输入、鼠标移动等）、更新窗口状态，
//        //并调用对应的回调函数（可以通过回调方法手动设置）
//        glfwPollEvents();
//    }
//    // optional: de-allocate all resources once they've outlived their purpose:
//    glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &VBO);
//    glDeleteBuffers(1, &EBO);
//    glDeleteProgram(shaderProgram);
//    //当渲染循环结束后我们需要正确释放/删除之前的分配的所有资源。我们可以在main函数的最后调用glfwTerminate函数来完成。
//    glfwTerminate();
//    return 0;
//}
//
////当用户改变窗口的大小的时候，视口也应该被调整。
////当窗口被第一次显示的时候framebuffer_size_callback也会被调用.对于视网膜(Retina)显示屏，width和height都会明显比原输入值更高一点。
//void framebuffer_size_callback(GLFWwindow *window, int width, int height)
//{
//    glViewport(0, 0, width, height);
//}
//
////处理手柄输入变化
//void processInput(GLFWwindow *window)
//{
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//    {
//        glfwSetWindowShouldClose(window, true);
//    }
//}
