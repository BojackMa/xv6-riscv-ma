#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"
#define MAX_LEN 100

int main(int argc, char *argv[]) {
	char *command = argv[1];
	char bf;
	char paramv[MAXARG][MAX_LEN]; // arguments
	char *m[MAXARG];

	while (1) {
		int count = argc-1;  // # of current arguments
		memset(paramv, 0, MAXARG * MAX_LEN);
		// copy the parameter of command
		for (int i=1; i<argc; i++) {
			strcpy(paramv[i-1], argv[i]);
		}

		int cursor = 0; // cursor pointing the char position in single_arg
//		int flag = 0; // flag indicating whether thers is argument preceding space
		int read_result;

		while (((read_result = read(0, &bf, 1))) > 0 && bf != '\n') {
			if (bf == ' ' ) {
				count++;
				// reset flag and p
				cursor = 0;
//				flag = 0;
			}
			else if (bf != ' ') {
				paramv[count][cursor++] = bf;
//				flag = 1;
			}
		}
		// encounters EOF of input or \n
		if (read_result <= 0) {
			break;
		}
        //必须要m做个中间人
		for (int i=0; i<MAXARG-1; i++) {
			m[i] = paramv[i];
		}
		m[MAXARG-1] = 0;
/*在给定的代码中，paramv 是一个二维字符数组，不直接符合 exec 函数所需的参数形式。因此，需要创建一个新的字符指针数组 m，并将 paramv 中的参数复制到 m 中，同时确保 m 的最后一个元素是 NULL，以满足 exec 函数的要求。
这个转换的过程是为了适应不同的参数传递方式，以便正确地调用外部命令。所以，m 数组充当了一个中间变量，帮助将 paramv 中的参数适应到 exec 函数需要的参数形式。*/
		if (fork() == 0) {
			exec(command, m);
			exit(0);
		} else {
			wait(0);
		}
	}
	exit(0);
}