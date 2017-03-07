/*
 * ���ü�¼���Ӻ���lock_set.c
 *
 * ��¼����Ϊ��ȡ����д���������ж�ȡ���ֳ�Ϊ������������ʹ���
 * ���̶��ܹ����ļ���ͬһ���ֽ�����ȡ������д�����ֳ�Ϊ��������
 * ���κ�ʱ��ֻ����һ���������ļ���ĳ�����ֽ���д��������Ȼ����
 * �ļ���ͬһ���ֲ���ͬʱ������ȡ����д������
 *
 * fcntl��lock�ṹ������ʾ��
 * struct flock {
 * short l_type;
 * off_t l_start;
 * short l_whence;
 * off_t l_len;
 * pid_t l_pid;
 * }
 *
 * ���ɣ�Ϊ���������ļ���ͨ���ķ����ǽ�l_start˵��Ϊ0��l_whence
 * ˵��ΪSEEK_SET��l_len˵��Ϊ0��
 */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>


void print_lock(struct flock lock)
{
        printf(" -----------------------------\n");

        if (lock.l_type == F_RDLCK) {
                printf("\tl_type: F_RDLCK\n");
        }
        else if (lock.l_type == F_WRLCK) {
                printf("\tl_type: F_WRLCK\n");
        }
        else if (lock.l_type == F_UNLCK) {
                printf("\tl_type: F_UNLCK\n");
        }

        printf("\tl_start: %d\n", (int)lock.l_start);

        if (lock.l_whence == SEEK_SET) {
                printf("\tl_whence: SEEK_SET\n");
        }
        else if (lock.l_whence == SEEK_CUR) {
                printf("\tl_whence: SEEK_CUR\n");
        }
        else if (lock.l_whence == SEEK_END) {
                printf("\tl_whence: SEEK_END\n");
        }

        printf("\tl_len: %d\n", (int)lock.l_len);

        printf(" -----------------------------\n");
}

void lock_set(int fd, int type)
{
        struct flock lock;

        /*��ֵlock�ṹ�壬���������ļ�*/
        lock.l_whence = SEEK_SET;
        lock.l_start = 0;
        lock.l_len = 0;

        while (1) {
                lock.l_type = type;

                /*
                 * ���ݲ�ͬ��type�����ļ������������
                 * ����ɹ����򷵻�0��ʧ���򷵻�1��
                 * ���������һ���ļ�ԭ���Ѿ������˻���������ô�ٵ���fcntl
                 * �������ͻ�ʧ�ܣ�����-1��
                 */
                if ((fcntl(fd, F_SETLK, &lock)) == 0) {
                        /*����ǹ�����*/
                        if (lock.l_type == F_RDLCK) {
                                printf("read only set by %d\n", getpid());
                        }
                        /*����ǻ�����*/
                        else if (lock.l_type == F_WRLCK) {
                                printf("write lock set by %d\n", getpid());
                        }
                        else if (lock.l_type == F_UNLCK) {
                                printf("release lock by %d\n", getpid());
                        }
                        print_lock(lock);
                        return;
                }
                else {
                        /*
                         * ���lock��������Ҳ���ǽ��ļ�fd�ļ�����Ϣ���뵽lock�ṹ��
                         * ����ɹ��򷵻�0
                         * ���ʧ���򷵻�-1
                         */
                        if ((fcntl(fd, F_GETLK, &lock)) == 0) {
                                if (lock.l_type != F_UNLCK) {
                                        if (lock.l_type == F_RDLCK) {
                                                printf("read lock already set by %d\n", lock.l_pid);
                                        }
                                        else if (lock.l_type == F_WRLCK) {
                                                printf("write lock already set by %d\n", lock.l_pid);
                                        }
                                        getchar();
                                }
                        }
                        else {
                                printf("cannot get the description of struck flock.\n");
                        }
                }
        }
}
 

/*
 * �����ļ���д��
 */


void die(char *msg)
{
        perror(msg);
        exit(1);
}

int open_file(void)
{
        int fd;

        if ((fd = open("/tmp/hello.c", O_CREAT | O_TRUNC | O_RDWR, 0666)) < 0) {
                perror("open error");
				exit(-1);
        }
        else {
                printf("Open file: hello.c %d\n", fd);
        }

        return fd;
}

void close_file(int fd)
{
        if (close(fd) < 0) {
				perror("close error");
				exit(-1);
        }
        else {
                printf("Close file: hello.c\n");
        }
}

int main(void)
{
        int fd;

        fd = open_file();

		/*���ļ���д����*/
//      lock_set(fd, F_WRLCK);
        /*���ļ��Ӷ�ȡ��*/
        lock_set(fd, F_RDLCK);
        /*�ȴ��������������*/
        getchar();
        /*���ļ�����*/
        lock_set(fd, F_UNLCK);
        getchar();
        close_file(fd);

        return 0;
}
