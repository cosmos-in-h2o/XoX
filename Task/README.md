#Task
##文档
###-指令
- task init-----------------------初始化
- task add \<task>------------添加任务
- task get -t--------------------获取任务列表
- task get -f--------------------获取已完成任务列表
- task get -t \<index>--------获取第\<index>个任务
- task get -f \<index>--------获取第\<index>个已完成的任务
- task delete -t \<task>------删除第\<index>个任务
- task delete -f \<task>------删除第\<index>个已完成的任务
- task find -t \<task>---------获取任务\<task>的位置
- task find -f \<task>---------获取已完成的任务\<task>的位置
- task finsh \<index>--------完成第\<index>的任务
- task help--------------------获取帮助
###-函数
```c++
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
```
##版本
###-2022.3.11
- 第一个版本
###-2023.3.17
- 修改了部分函数名，更符合常理
- 修复help指令输出不换行bug
- 增加删除完成任务指令
- 优化addTask函数与finshTask