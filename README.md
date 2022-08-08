# Curve-Maker

利用C++实现脚本绘图功能。

原理是任意多个小杆以不同的角速度旋转，最外侧的小杆末端所绘制出的曲线，比如：

![image](https://github.com/leehyukshuai/Curve-Maker/blob/main/example/curve1.bmp)

![image](https://github.com/leehyukshuai/Curve-Maker/blob/main/example/curve2.bmp)

# Usage

curve -i myScript -t 2.3 -r 100 -o myCurve.bmp

调用curve.exe，输入脚本(-i)指定为myScript，运行时间(-t)指定为2.3秒，每秒采样率(-r)指定为100，输出文件(-o)指定为myCurve.bmp。
