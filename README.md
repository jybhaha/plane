#plane

本程序是我本科生毕业设计。是一款飞行射击类游戏，模仿的是微信上的游戏**全民打飞机**，本游戏中大多数的素材也都是来自于**全民打飞机**游戏中。

本游戏主要是以**Cocos2d-x**为游戏引擎，以**C++**高级程序语言为编程语言，在**Windows 8.1**操作系统下使用**Microsoft Visual Studio 2013**、Eclipse等工具开发并最终移植到Android手机平台上。


下面是本游戏的游戏画面(动态图)：

![](https://raw.githubusercontent.com/jybhaha/plane/master/plane.gif)

##游戏基本功能

玩家启动游戏后，游戏会预先载入必要的游戏音效和图片等资源文件。进入欢迎界面后可以选择查看游戏帮助还是开始游戏。点击开始游戏进入选关界面，在此玩家可以选择自己想玩的关卡。进入游戏后游戏会检测玩家战机是否与敌机相撞、子弹是否击中敌人。当子弹打中敌人后，若敌人血量降为零，执行爆炸动画并增加积分。若主角与敌机发生碰撞，判断敌人是否血量降为零，执行爆炸动画并增加积分，并且判断主角血量是否降为零，若是，直接进入结束界面。若本场分数超过最高分数，则将分数写入本地。在结束界面中可以选择是否接受和是否重新开始。若玩家选择的是闯关模式，游戏会在一定时间后加入关主（BOSS）相关资源。若玩家选择的是无尽模式，游戏难度会随着时间难度的增加而增加。若玩家选择的是关主模式，游戏只会载入关主（BOSS）资源，不会载入普通敌机资源。

##代码解释
###Classes
本文件是游戏主代码所在。

至于各个代码的用途请参看说明文档。

###resources
本文件中存储的有本游戏使用的音效、字体、以及材质包。其中材质包使用**texturepacker**软件打包。

###qitasucai
本游戏中未使用的材质图片

###qitayinxiao
本游戏中未使用的音效

##图片
下面使游戏中的一些截图

###游戏欢迎界面
![](https://raw.githubusercontent.com/jybhaha/plane/master/photos/1.jpg)
###选关界面
![](https://raw.githubusercontent.com/jybhaha/plane/master/photos/2.jpg)
###选择主角飞机
![](https://raw.githubusercontent.com/jybhaha/plane/master/photos/4.jpg)
###游戏进行中
**左上角为暂停按钮**

**右上角为积分面板**

**左下角为导弹按钮**

**右下角为血量面板**

**图中心性飘动物是加血道具**

![](https://raw.githubusercontent.com/jybhaha/plane/master/photos/5.jpg)

**图中飘动的是加导弹道具**

![](https://raw.githubusercontent.com/jybhaha/plane/master/photos/6.jpg)

**图中飘动的是加子弹攻击力道具**
（还有一个未显示道具是增加子弹列数，即可以增加发射子弹数）

![](https://raw.githubusercontent.com/jybhaha/plane/master/photos/7.jpg)
![](https://raw.githubusercontent.com/jybhaha/plane/master/photos/8.jpg)
![](https://raw.githubusercontent.com/jybhaha/plane/master/photos/9.jpg)
![](https://raw.githubusercontent.com/jybhaha/plane/master/photos/10.jpg)

**结束画面**

![](https://raw.githubusercontent.com/jybhaha/plane/master/photos/11.jpg)

**如果喜欢请star一下！！！！**

**如果喜欢请star一下！！！！**

**如果喜欢请star一下！！！！**

**另外：**

  欢迎私信交流！
