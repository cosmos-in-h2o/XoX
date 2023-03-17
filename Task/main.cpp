#include <Windows.h>
#include "func.h"
/// task init		------init task.
/// task -a <task>	------add a <task>. 
/// task -gt		------get all task.
/// task -gf		------get all task in finshed.
/// task -gt <index>------get the <index>th in all task.
/// task -gf <index>------get the <index>th in all finshed task.
/// task -d	<task>	------delete <task>.
/// task -ft <task>	------find index of <task>.
/// task -ff <task>	------find index of <task> in finshed.
/// task -f <index>	------finshed the <index>th.
/// task --help		------get help.
int main(int argc, char *argv[]) {
	SetConsoleCP(65001);
	if (argc == 2) {
		if (strcmp(argv[1], "init") == 0) {
			init();
		} 
		else if (strcmp(argv[1], "--help") == 0) {
			printf("task init		------init task."
				"task -a <task>		------add a <task>."
				"task -gt			------get all task."
				"task -gf			------get all task in finshed."
				"task -gt <index>	------get the <index>th in all task."
				"task -gf <index>	------get the <index>th in all finshed task."
				"task -d <task>		------delete <task>."
				"task -ft <task>	------find index of <task>."
				"task -ff <task>	------find index of <task> in finshed."
				"task -f <index>	------finshed the <index>th."
				"task --help		------get help.");
		} 
		else if(strcmp(argv[1], "-gt") == 0) {
			getList();
		} 
		else if(strcmp(argv[1], "-gf") == 0) {
			getFinsh();
		} 
		else {
			printf("error");
		}
	} 
	else if (argc == 3) {
		if (strcmp(argv[1], "-a") == 0) {
			addTask(argv[2]);
		} 
		else if (strcmp(argv[1], "-gt") == 0) {
			getTask(atoi(argv[2]));
		} 
		else if (strcmp(argv[1], "-gf") == 0) {
			getFinshTask(atoi(argv[2]));
		} 
		else if (strcmp(argv[1], "-d") == 0) {
			deleteTask(atoi(argv[2]));
		} 
		else if (strcmp(argv[1], "-ft") == 0) {
			findTask(argv[2]);
		} 
		else if (strcmp(argv[1], "-ff") == 0) {
			findFinshTask(argv[2]);
		} 
		else if (strcmp(argv[1], "-f") == 0) {
			finshTask(atoi(argv[2]));
		} 
		else {
			printf("error");
		}
	} 
	else {
		printf("error");
	}
	return 0;
}