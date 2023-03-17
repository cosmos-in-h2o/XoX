#ifndef FUNC_H
#define FUNC_H
#include <stdio.h>
#include <fstream>
#include <vector>
#include <string>
//初始化
void init();
//添加任务
void addTask(std::string task);
//获取任务列表
void getTaskList();
//获取完成的任务列表
void getFinshList();
//获取任务
void getTask(int index); 
//获取完成的任务
void getFinshTask(int index); 
//删除任务
void deleteTask(int index); 
//删除完成的任务
void deleteFinshedTask(int index);
//查找任务
void findTask(std::string task); 
//查找完成的任务
void findFinshTask(std::string task);
//完成任务
void finshTask(int index); 
#endif