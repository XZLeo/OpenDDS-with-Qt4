#!/bin/bash
#
# 根据丢包率设置脚本退出值  # 第一行注释/bin/bash则默认bash解释，/bin/sh则默认sh解释
# |是管道，标准输出转到下一个命令的标准输入

function analysis(){
    packloss=0;
    while :; do 
        ping -c1 -w2 8.8.8.8 | grep "packets" | awk -F, \
		'{array=(${$3// / })}' #用\换行，还记得awk需要空格，\后面连注释都不能有
:<<EOF
	# 根据上面packloss的值打印和返回值
        if [ "$?" == 0 ]; then
            if [ "$packloss" == "0" ]; then
                echo "net packet loss = 0%"
                exit 0 # 丢包 0% 脚本退出状态值 为 0
            elif [ "$packloss" == "1" ]; then
                echo "net packet loss <= 10%"
                exit 1 # 丢包 <= 10% 脚本退出状态值 为 1
            else
                echo "net packet loss > 10%"
                exit 2 #丢包 > 10% 脚本退出状态值 为 2
            fi
       else
            echo "Undiscovered IP " # 网络不可用ping 命令错误,退出值为3
            exit 3
       fi
EOF
       done
}
analysis #此时才开始执行前面定义的函数

#之前的while没有done报错
#w 后面是2ms，等待每次回复的超时时间
#grep命令是一种强大的文本搜索工具，它能使用正则表达式搜索文本，并把匹 配的行打印出来
#那一行由grep读出来之后，由逗号作为分割符
#ping -c1 -w2 8.8.8.8 && ping -c2 -w2 8.8.8.8 | grep "packets"  将有packets的那句打出来
# ping -c1 8.8.8.8 | grep "packets"
#输出： 1 packets transmitted, 1 received, 0% packet loss, time 0ms
#awk 将-F后指定的分隔符,将每行分成多段，从1开始计数

#命令
# ping -c1 -w2 8.8.8.8| grep "packets" | awk -F, '{print $3}'
# 输出0% packet loss

# ping的输出： 1 packets transmitted, 1 received, 0% packet loss, time 0ms
# grep抓取带packets的行， awk打印$3 为0% packet loss
:<<EOF
		    split($3,m," ");  #按逗号分隔后，$3为
                    if (m[1] = "0%")  #字符串判断用=，不是==
		    then  
                        packloss=0; # 丢包 0% 
                    elif (m[1] <= "10%")
	 	    then
                        packloss=1; # 丢包 <= 10%
                    else 
                        packloss=2 # 丢包 > 10%
		    fi
EOF


#命令太长使用\换行
