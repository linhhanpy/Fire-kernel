/*
 *  fire/fs/file_table.c
 *
 *  (C) 2025 Lin Honghan
 */

#include <os/fs.h>

/* 文件表数组(64项) */
struct file file_table[NR_FILE];
