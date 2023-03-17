#ifndef FUNC_H
#define FUNC_H
#include <stdio.h>
#include <fstream>
#include <vector>
#include <string>
void init(); //
void addTask(std::string task);//
void getList();//
void getFinsh(); //
void getTask(int index); //
void getFinshTask(int index); //
void deleteTask(int index); //
void findTask(std::string task); //
void findFinshTask(std::string task);//
void finshTask(int index); //
void removeEmpty(std::vector<std::string>&out);
#endif