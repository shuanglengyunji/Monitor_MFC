# 图像显示
## 程序介绍
本程序从8000端口上通过UDP协议接收图像数据，
每次接收一行（1024个)像素。
然后显示在图像屏幕上。

本程序为一个很老的项目的辅助程序，
很多功能都已经残缺或存在问题。
不适合在生产环境中使用。
也不适合作为后续开发的基础Demo。

只不过这个程序的确能正常的显示实时图像，
在这个角度上是存在参考价值的。

## 代码梳理
*（所有代码都集中在ROTESTDlg.cpp中。）*

### 1.核心执行流程
1. OnInitDialog中InitSocket()函数创建socket，
   开启UDP接收端口（独立线程）。
2. UDP接收线程的处理函数为pRecvParam()。
3. 程序接收的是灰度图像，每个像素1字节。
   pRecvParam()每次从socket中读取1024个字节（一行像素），存入imagedata[]数组的对应行中。
   然后发送WM_RECVDATA消息。
4. 程序接收到WM_RECVDATA消息，进入消息响应函数OnRecvData()。
   OnRecvData()中，根据imagedata[]的内容，重新绘制图像窗口，完成图像显示。

### 2.总结
程序分为2部分，UDP接收和图像显示。
UDP接收在pRecvParam()，独占一个线程工作。
图像显示功能由OnRecvData()函数实现，在主线程里进行（我觉得是主线程，因为要操作界面上的对象）。
两个部分之间通过WM_RECVDATA消息沟通，WM_RECVDATA在socket接收到1帧图像并存入imagedata[]数组时触发。

