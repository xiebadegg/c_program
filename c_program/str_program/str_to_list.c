/*********
 * 将字符串通过分隔符截取至数组函数
 * 入口参数:in_str,输入源字符串，const
 *入口参数 :len ,输出输出字符数组的列数，即：sizeof(*out_list)
 *入口参数 :demlit ,分隔符字符串
 *出口参数 :out_list 保存分割后字符串的输出数组
 *出口参数 ：list_num ,数组中的字符串个数（几行字符串）
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
