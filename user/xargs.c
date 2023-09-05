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
        //����Ҫm�����м���
		for (int i=0; i<MAXARG-1; i++) {
			m[i] = paramv[i];
		}
		m[MAXARG-1] = 0;
/*�ڸ����Ĵ����У�paramv ��һ����ά�ַ����飬��ֱ�ӷ��� exec ��������Ĳ�����ʽ����ˣ���Ҫ����һ���µ��ַ�ָ������ m������ paramv �еĲ������Ƶ� m �У�ͬʱȷ�� m �����һ��Ԫ���� NULL�������� exec ������Ҫ��
���ת���Ĺ�����Ϊ����Ӧ��ͬ�Ĳ������ݷ�ʽ���Ա���ȷ�ص����ⲿ������ԣ�m ����䵱��һ���м������������ paramv �еĲ�����Ӧ�� exec ������Ҫ�Ĳ�����ʽ��*/
		if (fork() == 0) {
			exec(command, m);
			exit(0);
		} else {
			wait(0);
		}
	}
	exit(0);
}