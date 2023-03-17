#include <Windows.h>
#include "func.h"
///task init				------init task.\n
///task add <task>			------add a <task>.\n
///task get -t				------get all task.\n
///task get -f				------get all task in finshed.\n
///task get -t <index>		------get the <index>th in all task.\n
///task get -f <index>		------get the <index>th in all finshed task.\n
///task delete -t <task>	------delete <task>.\n
///task delete -f <task>	------delete finshed <task>.\n
///task find -t <task>		------find index of <task>.\n
///task find -f <task>		------find index of <task> in finshed.\n
///task finsh <index>		------finshed the <index>th.\n
///task help				------get help.\n

int main(int argc, char *argv[]) {
	SetConsoleCP(65001);
	if (argc == 2) {
		if (strcmp(argv[1], "init") == 0) {
			init();
			return 0;
		} 
		else if (strcmp(argv[1], "help") == 0) {
			printf(
				"task init				------init task.\n"
				"task add <task>		------add a <task>.\n"
				"task get -t			------get all task.\n"
				"task get -f			------get all task in finshed.\n"
				"task get -t <index>	------get the <index>th in all task.\n"
				"task get -f <index>	------get the <index>th in all finshed task.\n"
				"task delete -t <task>	------delete <task>.\n"
				"task delete -f <task>	------delete finshed <task>.\n"
				"task find -t <task>	------find index of <task>.\n"
				"task find -f <task>	------find index of <task> in finshed.\n"
				"task finsh <index>		------finshed the <index>th.\n"
				"task help				------get help.\n"
			);
			return 0;
		}
		printf("error");
	} 
	else if (argc == 3) {
		if (strcmp(argv[1], "add") == 0) {
			addTask(argv[2]);
			return 0;
		}
		else if (strcmp(argv[1], "get") == 0) {
			if (strcmp(argv[2], "-t") == 0) {
				getTaskList();
			}
			else if (strcmp(argv[2], "-f") == 0) {
				getFinshList();
			}
			else {
				printf("error");
			}
			return 0;
		}
		if (strcmp(argv[1], "finsh") == 0) {
			finshTask(atoi(argv[2]));
			return 0;
		}
		printf("error");
	} 
	else if (argc == 4) {
		if (strcmp(argv[1], "get") == 0) {
			if (strcmp(argv[2], "-t")) {
				getTask(atoi(argv[3]));
			}
			else if (strcmp(argv[2], "-f")) {
				getFinshTask(atoi(argv[3]));
			}
			else {
				printf("error");
			}
			return 0;
		}
		if (strcmp(argv[1], "delete") == 0) {
			if (strcmp(argv[2], "-t") == 0) {
				deleteTask(atoi(argv[3]));
				printf("-t\n");
			}
			else if (strcmp(argv[2], "-f") == 0) {
				deleteFinshedTask(atoi(argv[3]));
				printf("-f\n");
			}
			else {
				printf("error");
			}
			return 0;
		}
		if (strcmp(argv[1], "find") == 0) {
			printf("find\n");
			if (strcmp(argv[2], "-t") == 0) {
				findTask(argv[3]);
			}
			else if (strcmp(argv[2], "-f") == 0) {
				findFinshTask(argv[3]);
			}
			else {
				printf("error");
			}
			return 0;
		}
		printf("error");
	}
	else {
		printf("error");
	}
	return 0;
}