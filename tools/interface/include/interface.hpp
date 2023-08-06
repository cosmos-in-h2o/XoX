#ifndef INTERFACE_HPP
#define INTERFACE_HPP
#include <string_view>
#include <vector>
enum ProgramKind{

}; 
//创建项目
void create(std::string_view name,ProgramKind pro_kind);
//创建脚本
void create(std::string_view class_name);
//构建项目
void build(std::vector<std::string_view>& flags);
//构建发布版本
void release(std::vector<std::string_view>& flags);
#endif // !INTERFACE_HPP
