#ifndef _CONFIG_H
#define _CONFIG_H

/* 内核配置头文件 */

/*
 * Defines for what uname() should return 
 */
/* 定义了uname()函数的返回值 */
#define UTS_SYSNAME "Fire"
#define UTS_NODENAME "(none)"   /* set by sethostname() */
#define UTS_RELEASE "0"		    /* patchlevel */
#define UTS_VERSION "0.0.0"
#define UTS_MACHINE "i386"      /* hardware type */

/* Don't touch these, unless you really know what your doing. */
/* 请不要随意修改下面定义值，除非你知道自己正在干什么。 */
#define DEF_INITSEG	    0x9000  /* 引导扇区程序将被移动到的段位置 */
#define DEF_SYSSEG	    0x1000  /* 系统模块被加载到内存的段位置 */
#define DEF_SETUPSEG	0x9020  /* setup程序代码的段位置 */
#define DEF_SYSSIZE	    0x3000  /* 内核系统模块的默认最大节数(1节=16bit) */

/*
 * The root-device is no longer hard-coded. You can change the default
 * root-device by changing the line ROOT_DEV = XXX 
 */
#endif
