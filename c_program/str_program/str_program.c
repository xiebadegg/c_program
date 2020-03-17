/***
str :输入字符串
target: 要去除的字符
****/
int delete_char(char str[], char target)
{
	int i, j;
	for (i = j = 0; str[i] != '\0'; i++)
	{
		if (str[i] != target)
		{
			str[j++] = str[i];
		}
	}
	str[j] = '\0';
}

//获取年月份且转为int型
//入口为 日期 例：2019-12-01
//出口 int 年
//出口 int 月
int get_int_ym(const  char *date ,int *y ,int * m)
{
	char *stop; //转换时截止位置
	char str_m[2];
	char str_y[4];	
	memset(str_m, 0x00, sizeof(str_m) );
	memset(str_y, 0x00, sizeof(str_y) );
	//取月
	strncpy( str_m, date+5, sizeof(str_m) );
	str_m[2] = '\0';
	//取年
	strncpy( str_y, date, sizeof(str_y) );
	str_y[4] = '\0';
	
	//转换月为int
	*m = strtol( str_m, &stop, 10  ) ;
	*y = strtol( str_y, &stop, 10  ) ;
	return 0;	
}
//判断年月是否连续
//入口：上一年月 ，格式：2019-01
//入口:本年月：格式：2019-01
//返回： 0-连续，非0-不连续
int judge_years_mouth_continuous( char *last_date_, char *this_date_ )
{
	int int_last_y = 0;
	int int_last_m= 0;
	int int_this_y = 0;
	int int_this_m = 0;
	//获取年 和月 转为 int型
	get_int_ym(last_date_, &int_last_y, &int_last_m);
	get_int_ym(this_date_, &int_this_y, &int_this_m);
	BSPAppDbgLog( __FILE__, __LINE__, "######int_this_y[%d], int_this_m[%d], int_last_y[%d], int_last_m[%d]########" ,int_this_y, int_this_m,int_last_y,int_last_m);
	//先判断年份相同的连续月情况
	if( int_this_y == int_last_y)
	{
		if( 1 == abs(int_this_m - int_last_m )  )
		{
			//连续
			return 0;
		}
		else
		{
			//不连续
			return 1;
		}
	}
	//年连续
	else if ( 1 == abs( int_this_y - int_last_y) )
	{
		if(11 == abs(  int_this_m - int_last_m ) )
		{
			//连续
			return 0;
		}
		else
		{
			//不连续
			return 1;
		}
		
	}
	else
	{
		//不连续
		return 1;
	}
}