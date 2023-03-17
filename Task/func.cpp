#include "func.h"
#pragma warning(disable : 4996)

void addTask(std::string task) {
	//读取
	std::vector<std::string> lists;
	std::ifstream in("lists.txt");
	if (in.is_open()) {
		while (in) {
			std::string buff;
			getline(in, buff);
			lists.push_back(buff);
		}
	}
	in.close();
	lists.push_back(task);
	
	// 写入
	std::ofstream out("lists.txt",std::ios::out);
	for (auto p = lists.begin(); p != lists.end();p++) {
		if (*p != "" && *p != "\n" && *p != "\t" && *p != " " && *p != "\0") {
			out << *p << std::endl;
		}
	}
	out.close();
	printf("add task:%s", task.c_str());
}

void getTask(int index) {
	std::vector<std::string> lists;
	std::ifstream in("lists.txt");
	if (in.is_open()) {
		while (in) {
			std::string buff;
			getline(in, buff);
			lists.push_back(buff);
		}
	}
	in.close();
	if (index < lists.size()) {
		printf("%s", lists[index].c_str());
	}
}

void getList() {
	std::ifstream in("lists.txt");
	int index = 0;
	std::string buff;

	if (in.is_open()) {
		while (in) {
			getline(in, buff);
			if (buff != "" && buff != "\n" && buff != "\t" && buff != " " && buff != "\0") {
				printf("%d.%s\n", index, buff.c_str());
				index++;
			}
		}
	}
	in.close();
}

void getFinshTask(int index) {
	std::vector<std::string> lists;
	std::ifstream in("finshed.txt");
	std::string buff;
	if (in.is_open()) {
		while (in) {
			getline(in, buff);
			lists.push_back(buff);
		}
	}
	in.close();
	if (index < lists.size()) {
		printf("%s", lists[index].c_str());
	}
}

void finshTask(int index) {
	//读取
	std::vector<std::string> lists;
	std::string finshed;//完成的任务
	std::string buff;
	std::ifstream in("lists.txt",std::ios::in);
	if (in.is_open()) {
		while (in) {
			getline(in, buff);
			lists.push_back(buff);
		}
	}
	in.close();
	if (index < lists.size()) {
		finshed = lists[index];
		lists.erase(lists.begin() + index);
	}
	
	// 写入
	std::ofstream out("lists.txt", std::ios::out);
	for (auto p = lists.begin(); p != lists.end(); p++) {
		if (*p != "" && *p != "\n" && *p != "\t" && *p != " " && *p != "\0") {
			out << *p << std::endl;
		}
	}
	out.close();

	std::vector<std::string> finshed_list;
	in.open("finshed.txt", std::ios::in);
	if (in.is_open()) {
		while (in) {
			std::string buff;
			getline(in, buff);
			finshed_list.push_back(buff);
		}
	}
	in.close();
	finshed_list.push_back(finshed);
	
	// 写入
	out.open("finshed.txt", std::ios::out);
	for (auto p = finshed_list.begin(); p != finshed_list.end(); p++) {
		if (*p != "" && *p != "\n" && *p != "\t" && *p != " " && *p != "\0") {
			out << *p << std::endl;
		}
	}
	out.close();
	printf("finsh task:%s", finshed.c_str());
}

void findTask(std::string task) {
	std::vector<std::string> lists;
	std::ifstream in("lists.txt");
	int index = 0;
	if (in.is_open()) {
		while (in) {
			std::string buff;
			getline(in, buff);
			lists.push_back(buff);
			index++;
		}
	}
	in.close();
	auto p = std::find(lists.begin(), lists.end(), task);
	if (p == lists.end()) {
		printf("error:not found task:%s", task.c_str());
	} else {
		printf("the index of task:%s is %d", task.c_str(), p - lists.begin());
	}
}

void findFinshTask(std::string task) {
	std::vector<std::string> lists;
	std::ifstream in("finshed.txt");
	int index = 0;
	if (in.is_open()) {
		while (in) {
			std::string buff;
			getline(in, buff);
			lists.push_back(buff);
			index++;
		}
	}
	in.close();
	auto p = std::find(lists.begin(), lists.end(), task);
	if (p == lists.end()) {
		printf("error:not found task:%s", task.c_str());
	} else {
		printf("the index of task:%s is %d", task.c_str(), p - lists.begin());
	}
}

void deleteTask(int index) {
	//读取
	std::vector<std::string> lists;
	std::ifstream in("lists.txt");
	if (in.is_open()) {
		while (in) {
			std::string buff;
			getline(in, buff);
			lists.push_back(buff);
		}
	}
	in.close();
	if (index < lists.size()) {
		printf("delete task:%s", lists[index].c_str());
		lists.erase(lists.begin() + index);
	}

	// 写入
	std::ofstream out("lists.txt", std::ios::out);
	
	for (auto p = lists.begin(); p != lists.end(); p++) {
		if (*p != "" && *p != "\n" && *p != "\t" && *p != " " && *p != "\0") {
			out << *p << std::endl;
		}
	}
	out.close();
}

void getFinsh() {
	std::ifstream in("finshed.txt");
	std::string buff;
	int index = 0;
	if (in.is_open()) {
		while (in) {
			getline(in, buff);
			if (buff != "" && buff != "\n" && buff != "\t" && buff != " " && buff != "\0") {
				printf("%d.%s\n", index, buff.c_str());
				index++;
			}
		}
	}
	in.close();
}

void init() {
	FILE *out;
	out = fopen("lists.txt","w");
	fclose(out);
	out = fopen("finshed.txt","w");
	fclose(out);
	out = nullptr;
}