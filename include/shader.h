#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // 包含glad来获取所有的必须OpenGL头文件

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

class Shader
{
public:
    // 着色器程序的ID
    unsigned int ID;
    
    // 构造器读取并构建着色器
    Shader(const GLchar *vertexPath, const GLchar *fragmentPath);
    // 使用/激活程序
    void use();
    // uniform工具函数
    void setBool(const string &name, bool value) const;
    void setInt(const string &name, int value) const;
    void setFloat(const string &name, float value) const;
};

#endif