/*
 *  fire/fs/ioctl.c
 *
 *  (C) 2025 Lin Honghan
 */

#include <string.h>
#include <errno.h>
#include <sys/stat.h>

#include <os/sched.h>

extern int tty_ioctl(int dev, int cmd, int arg);
extern int pipe_ioctl(struct m_inode *pino, int cmd, int arg);

/* 定义输入输出控制(ioctl)函数指针类型 */
typedef int (*ioctl_ptr)(int dev,int cmd,int arg);

/* 取系统中设备种数的宏 */
#define NRDEVS ((sizeof (ioctl_table))/(sizeof (ioctl_ptr)))

/* ioctl操作函数指针表 */
static ioctl_ptr ioctl_table[]={
	NULL,		/* nodev */
	NULL,		/* /dev/mem */
	NULL,		/* /dev/fd */
	NULL,		/* /dev/hd */
	tty_ioctl,	/* /dev/ttyx */
	tty_ioctl,	/* /dev/tty */
	NULL,		/* /dev/lp */
	NULL};		/* named pipes */
	
/**
 * 输入输出控制
 * 该函数首先判断参数给出的文件描述符是否有效。然后根据对应i节点中文件属性判断文件类型，并根据
 * 具体文件类型调用相关的处理函数。
 * @param[in]	fd		文件描述符
 * @param[in]	cmd		命令码
 * @param[in]	arg		参数
 * @retval		成功返回0，失败返回出错码
 */
int sys_ioctl(unsigned int fd, unsigned int cmd, unsigned long arg)
{	
	struct file * filp;
	int dev, mode;

	if (fd >= NR_OPEN || !(filp = current->filp[fd])) {
		return -EBADF;
	}
	if (filp->f_inode->i_pipe) {
		return (filp->f_mode&1) ? pipe_ioctl(filp->f_inode,cmd,arg) : -EBADF;
	}
	mode = filp->f_inode->i_mode;
	if (!S_ISCHR(mode) && !S_ISBLK(mode)) {
		return -EINVAL;
	}
	dev = filp->f_inode->i_zone[0];
	if (MAJOR(dev) >= NRDEVS) {
		return -ENODEV;
	}
	if (!ioctl_table[MAJOR(dev)]) {
		return -ENOTTY;
	}
	return ioctl_table[MAJOR(dev)](dev,cmd,arg);
}
