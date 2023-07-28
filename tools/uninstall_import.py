import os
# 目录位置
target_path = "./import/"
# 读取文件
with open('./tools/file.list', encoding='utf-8') as files:
    read_list = files.readlines()
    read_list = [line.strip() for line in read_list]
# 声明
file_list: list = []
# 解析所读取的文件
which: bool = True
for read in read_list:
    if which:
        pass
    else:
        file_list.append(read)
    which = not which
# 执行赋值操作
for file in file_list:
    target: str = "{}{}".format(target_path, file)
    os.remove(target)
    print(f"removed {target}")
