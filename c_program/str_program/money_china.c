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

