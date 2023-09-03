#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void take_right_pipe_give_num_from_left(int *rp)
{
	close(rp[1]);
	int prime, received;
	read(rp[0], &prime, sizeof(int));
	printf("prime %d\n", prime);
	int newp[2];
	pipe(newp);
	if (read(rp[0], &received, sizeof(int)) == 0)
		exit(0);	//�ȶ�ȡ����������˵������β�ˣ�ֱ���˳�
	if (fork() == 0) {
		take_right_pipe_give_num_from_left(newp);
	} else {
		close(newp[0]);
		if (received % prime != 0)
			write(newp[1], &received, sizeof(int));	//�ȸ���֮ǰ��ȡ��

		while (read(rp[0], &received, sizeof(int))) {
			if (received % prime != 0)
				write(newp[1], &received, sizeof(int));
		}
		close(rp[0]);	//ǰ��ѭ��������˵�������ˣ���ôҲд����
		close(newp[1]);
		wait(0);
	}
	exit(0);
}

int main(int argc, char *argv[])
{
	int p[2];
	pipe(p);
	if (fork() == 0) {	//son
		take_right_pipe_give_num_from_left(p);
	} else {		//father
		close(p[0]);
		for (int i = 2; i <= 35; i++) {
			write(p[1], &i, sizeof(int));
		}
		close(p[1]);
		wait(0);	//�ȴ�������ӽ��̽���
	}
	exit(0);
}