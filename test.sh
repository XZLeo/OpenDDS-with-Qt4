#!/bin/bash
#
# 根据丢包率设置脚本退出值  # 第一行注释/bin/bash则默认bash解释，/bin/sh则默认sh解释
# |是管道，标准输出转到下一个命令的标准输入

function analysis(){
    packloss=0;
    while :; do 
        ping -c1 -w2 8.8.8.8 | grep "packets" | awk -F, '{
		split($3,a," ");
		if (m[1]="0%")
		{
		   packloss=0;
		}else
		{
		   packloss=1;
		}
	}'

	# 根据上面packloss的值打印和返回值
        if [ "$?" == 0 ]; then
            if [ "$packloss" == "0" ]; then
                echo "net packet loss = 0%"
                exit 0 # 丢包 0% 脚本退出状态值 为 0
            else
                echo "net packet loss > 10%"
                exit 2 #丢包 > 10% 脚本退出状态值 为 2
            fi
       else
            echo "Undiscovered IP " # 网络不可用ping 命令错误,退出值为3
            exit 3
       fi

       done
}
