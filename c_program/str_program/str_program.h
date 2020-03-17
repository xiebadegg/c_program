/***
str :输入字符串
target: 要去除的字符
****/
int delete_char(char str[], char target);

/******
获取年月份且转为int型
入口为 日期 例：2019-12-01
出口 int 年
出口 int 月
*******/
int get_int_ym(const  char *date ,int *y ,int * m);
/*****
判断年月是否连续
入口：上一年月 ，格式：2019-01
入口:本年月：格式：2019-01
返回： 0-连续，非0-不连续
******/
int judge_years_mouth_continuous( char *last_date_, char *this_date_ );
