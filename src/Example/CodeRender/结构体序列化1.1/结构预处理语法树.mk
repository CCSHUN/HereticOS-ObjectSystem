预处理命令<预处理命令>=生成结构体信息到头文件|生成结构体序列化到XML的代码|生成头文件结构体序列化信息到头文件
生成结构体信息到头文件<命令>=WORD(MAKESTRUCTINFO)+WORD(()+结构体名+WORD())
生成头文件结构体序列化信息到头文件<命令>=WORD(MAKE_FILE_STRUCTINFO)+WORD(()+文件路径名+WORD())
结构体名<结构体名>=词型
文件路径名<文件路径名>=词型

生成结构体序列化到XML的代码<命令>=WORD(MAKESTRUCTXMLSER)+WORD(()+结构体名+WORD())

