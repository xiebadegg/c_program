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

/*********
 * 将字符串通过分隔符截取至数组函数 
 * 入口参数:in_str,输入源字符串，const
 *入口参数 :len ,输出输出字符数组的列数，即：sizeof(*out_list)
 *入口参数 :demlit ,分隔符字符串
 *出口参数 :out_list 保存分割后字符串的输出数组
 *出口参数 ：list_num ,数组中的字符串个数（几行字符串）
 调用实例：char *str = "111,222,333,444"
 	   int i = 0;
	   int j = 0;
	   char list[4][4];
	   str_spilt(str, ',', i, list, j);
 * *******/
int str_spilt(const char *in_str, const char *demlit, const int len, char **out_list, int *list_num)
{
	char *s = strdup(in_str);
	int i = 0;
	char *token = NULL;
	/* 获取第一个子字符串 */
	token = strtok(s, demlit);
	/* 继续获取其他的子字符串 */
	while (token != NULL)
	{
		strcpy((char *)out_list + len * i, token);
		token = strtok(NULL, demlit);
		i++;
	}
	*list_num = i;
	free(s);
	s = NULL;
	return 0;
}

/** \brief MoneyToChinaHanZi()将数字金额转换为汉字大写的金额。理论上支持任意位数的金额(只要计算机能支持足够长的数字位数)。
 *        实际支持的位数由char mony[1024]变量的长度确定，还与计算机数据类型能表示的最大长度有关。
 * \param    money 输入数字金额. money的值不小于0.
 * \param    chinaHZ 输出参数，输出转换后的汉字大写金额。
 * \return   失败返回-1，金额小于0；　
 *           成功返回转换后的大写金额字符串;
 */
int MoneyToChinaHanZi(double money, char *chinaHZ)
{
	char *cpaiHZnum[] = {"零", "壹", "贰", "叁", "肆", "伍", "陆", "柒", "捌", "玖"};
	char *unitL[] = {"拾", "佰", "仟", "万", "拾", "佰", "仟", "亿"};
	char *yuan[] = {"元"};
	char *unitR[] = {"角", "分"};
	char mony[1024];
	memset(mony, 0x00, sizeof(mony));
	//强制类型转换
	sprintf(mony, "%.2lf", money);
	if (mony[0] == '-')
	{
		BSPAppErrLog(__FILE__, __LINE__, "金额[%.2lf]不能为负值", mony);
		sprintf(g_acRspMsg, "金额[%.2lf]不能为负值", mony);
		return -1;
	}
	int i = 0;
	int dotIndex = 0; //记录小数点位置索引
	int slen = strlen(mony);
	//获取小数点位置索引
	for (i = 0; i < slen; i++)
	{
		if (mony[i] == '.')
		{
			dotIndex = i;
			break;
		}
	}
	//处理小数点左边
	strcpy(chinaHZ, "\0"); //防止chinHZ内有脏数据时连接多余数据
	//处理第一个字符的值
	i = 0;
	strcat(chinaHZ, cpaiHZnum[mony[i] - 0x30]);
	if (dotIndex - i - 2 >= 0)
	{
		strcat(chinaHZ, unitL[(dotIndex - i - 2) % 8]);
	}
	else
	{
		//strcat(chinaHZ,yuan[0]);
	}
	//从第二个字符开始处理
	for (i = 0 + 1; i < dotIndex; i++)
	{
		int tt = 0;
		if (mony[i] == '0')
		{
			tt = dotIndex - 2 - i;
			if (tt % 8 == 7)
			{
				strcat(chinaHZ, unitL[7]); //单位:亿
			}
			//单位万的位置及其左边三位数字全部是0，则数字金额中不加单位万
			if (tt % 8 == 3 && mony[i] == '0' && mony[i - 1] == '0' && mony[i - 2] == '0' && mony[i - 3] == '0')
			{
				continue;
			}
			if (tt % 8 == 3)
			{
				strcat(chinaHZ, unitL[3]); //单位:万
			}
			continue;
		}
		if (mony[i - 1] == '0' && mony[i] != '0')
		{
			strcat(chinaHZ, cpaiHZnum[0]);
			strcat(chinaHZ, cpaiHZnum[mony[i] - 0x30]);
			if (dotIndex - i == 1) //个位，连接单位元
			{
				// strcat(chinaHZ, yuan[0]);
			}
			else if (dotIndex - i > 1)
			{
				strcat(chinaHZ, unitL[(dotIndex - i - 2) % 8]);
			}
		}
		if (mony[i - 1] != '0' && mony[i] != '0')
		{
			strcat(chinaHZ, cpaiHZnum[mony[i] - 0x30]);
			if (dotIndex - i == 1) //个位，连接单位元
			{
				//strcat(chinaHZ, yuan[0]);
			}
			else if (dotIndex - i > 1) //不是个位，连接相应的单位
			{
				strcat(chinaHZ, unitL[(dotIndex - i - 2) % 8]);
			}
		}
	}
	strcat(chinaHZ, yuan[0]); //不管多少位，整数部分最后都要连接单位:元
	//小数点后两位不全为0, 则处理小数点后的
	if (!(mony[dotIndex + 1] == '0' && mony[dotIndex + 2] == '0'))
	{
		//连接点和小数点后两位
		for (i = dotIndex + 1; i <= dotIndex + 2; i++)
		{
			if ((i == dotIndex + 2) && mony[i] == '0')
			{
				//小数点后面第二位为0时，不做任何处理,如 0.70元转为 柒角
				continue;
			}
			strcat(chinaHZ, cpaiHZnum[mony[i] - 0x30]);
			if (mony[i] != '0') //如果小点后不为0则加单位
			{
				strcat(chinaHZ, unitR[(i - dotIndex - 1)]);
			}
		}
	}
	chinaHZ[strlen(chinaHZ)] = '\0';
	return 0;
}

