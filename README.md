# Curve-Maker

利用C++实现脚本绘图功能。

原理是任意多个小杆以不同的角速度旋转，最外侧的小杆末端所绘制出的曲线，比如：

![image](https://github.com/leehyukshuai/Curve-Maker/blob/main/example/curve1.bmp)

![image](https://github.com/leehyukshuai/Curve-Maker/blob/main/example/curve2.bmp)

# Usage Example

curve -i myScript -t 2.3 -r 100 -c blue -o myCurve.bmp

调用curve.exe，输入脚本(-i)指定为myScript，运行时间(-t)指定为2.3秒，每秒采样率(-r)指定为100，画笔颜色(-c)指定为blue，输出文件(-o)指定为myCurve.bmp。

当采样率低时，绘制出的曲线像是多边形一样，采样率高就会平滑一些，运行时间自己可以摸索，颜色只支持几种颜色(可以看Color类的代码)

# Script Example

每一行对应一个小杆，先是长度(单位:像素pixels)，后是转速(单位:转每秒rps)，长度必须是整数，而转速可以是分数表示，比如1/3。
