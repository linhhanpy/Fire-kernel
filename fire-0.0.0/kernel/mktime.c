/*
 *  fire/kernel/mktime.c
 *
 *  (C) 2025 Lin Honghan
 */

#include <time.h>

#define MINUTE 60
#define HOUR (60*MINUTE)
#define DAY (24*HOUR)
#define YEAR (365*DAY)

/* interestingly, we assume leap-years */
/* 以闰年为基础，每个月开始时的秒数时间 */
static int month[12] = {
	0,
	DAY*(31),
	DAY*(31+29),
	DAY*(31+29+31),
	DAY*(31+29+31+30),
	DAY*(31+29+31+30+31),
	DAY*(31+29+31+30+31+30),
	DAY*(31+29+31+30+31+30+31),
	DAY*(31+29+31+30+31+30+31+31),
	DAY*(31+29+31+30+31+30+31+31+30),
	DAY*(31+29+31+30+31+30+31+31+30+31),
	DAY*(31+29+31+30+31+30+31+31+30+31+30)
};

/**
 * 计算从1970年1月1日0时起到开机当日经过的秒数
 * @param[in]	tm	当前时间
 * @return		返回从1970年1月1日0时起到开机当日经过的秒数	
 */
long kernel_mktime(struct tm * tm)
{
	long res;
	int year;

	/* tm_year是2位表示方式，处理2000年的问题（例如：2018=>18+100-70） */
	if (tm->tm_year < 70)
		tm->tm_year += 100;

	year = tm->tm_year - 70;
/* magic offsets (y+1) needed to get leapyears right.*/
/* 由于UNIX计年份y是从1970年算起。到1972年就是一个闰年，因此过3年才收到了第1个闰年的影响，
 即从1970年到当前年份经过的闰年数为(y+1)/4 */
	res = YEAR * year + DAY * ((year+1)/4);
	
	res += month[tm->tm_mon];
/* and (y+2) here. If it wasn't a leap-year, we have to adjust */
/* 如果月份大于2月，则需要判断当前年份是否为闰年，计算公式为(year+2)%4。非闰年则需要减去1
 天，因为month[]这个数组以闰年为假设的 */
	if (tm->tm_mon>1 && ((year+2)%4)) { 
		res -= DAY;
	}
	res += DAY * (tm->tm_mday - 1);
	res += HOUR * tm->tm_hour;
	res += MINUTE * tm->tm_min;
	res += tm->tm_sec;
	return res;
}
