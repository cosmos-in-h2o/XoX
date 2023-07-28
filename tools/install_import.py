import shutil
# 目录位置
root_path = "./"
target_path = "./import/"
# 读取文件
with open('./tools/file.list', encoding='utf-8') as files:
    read_list = files.readlines()
    read_list = [line.strip() for line in read_list]
# 声明
dir_list: list = []
file_list: list = []
# 解析所读取的文件
which: bool = True
for read in read_list:
    if which:
        dir_list.append(read)
    else:
        file_list.append(read)
    which = not which
# 执行赋值操作
for dir, file in zip(dir_list, file_list):
    source: str = "{}{}{}".format(root_path, dir, file)
    target: str = "{}{}".format(target_path, file)
    shutil.copy(source, target)
    print(f"installed {target}")
