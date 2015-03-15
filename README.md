# MechEmpire II
# RobotAppearanceReader

By 狄学长

-----------------------

读取 libRobotAI.so 的小程序，生成JSON格式的文本文件，包含该机甲AI的外观信息。

make:

    make all

run:

    ./RobotAppearanceReader ./libmyAI.so ./appearance.json

output format:

    {“name”:”小操蛋”,”author”:”狄学长”,”weapon”:1,”engine”:0,”wr”:-50,”wg”:-50,”wb”:-50,”er”:-50,”eg”:-50,”eb:-50”}

