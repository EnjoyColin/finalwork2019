执行文件：[program_name].exe
输入文件：input.logo  
输出文件：output.bmp 
命令详解见PDF文件
命令说明文档：doc.txt
错误信息输出：errorLog.txt
执行过程中创建的文件夹：traces

先写头信息！

命令：
[VALUE]可以是数字（整数或小数）或者变量名

DEF A [VALUE]
ADD A [VALUE]	//A+=[VALUE]
MOVE [VALUE]
TURN [VALUE]	//顺时针
COLOR [R] [G] [B]
CLOAK	//隐身

LOOP [VALUE]	//循环语句
	...
END LOOP

CALL [FUNCTION NAME]([PARA1], [PARA2], ...)

FUNC [FUNCTION NAME]([PARA1], [PARA2], ...)

//add-ons 附加功能
MINUS A [VALUE]	//A-=[VALUE]
MULTIPLY A [VALUE]	//A*=[VALUE]
DIVIDE A [VALUE]	//A/=[VALUE]

SET_WIDTH [VALUE]	//设置画笔宽度

IF [VALUE] EQUAL [VALUE]	//三种IF语句
或者：IF [VALUE] GREATER_THAN [VALUE]
或者：IF [VALUE] LESS_THAN [VALUE]
	...
END IF



