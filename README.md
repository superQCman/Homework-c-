# Homework-c++
代码模块介绍：

- HelloWorldScene 初始化场景

- Scene_one 菜单场景

- Game_fist 第一关

- game_first_second 第二关

- store_message 统一管理不同场景的共用变量

- player player类（包括玩家和boss）

- Barrier 障碍物类（包括武器类）

- Difficult 难度选择场景

- choose 仓库场景，选择皮肤，武器

- PoolScene 商店场景

有啥不懂的可以在GitHub或微信上问我。

# 以下是对头文件的详细总结
这是一个命名为AppDelegate.h的头文件，代码中包含了对cocos2d头文件的引用。

class AppDelegate : private cocos2d::Application 是一个继承自cocos2d::Application的类。

这个类包含了以下几个成员函数：

- AppDelegate：构造函数。
- ~AppDelegate：析构函数。
- initGLContextAttrs：初始化OpenGL上下文属性的函数。
- applicationDidFinishLaunching：初始化Director和Scene的代码。
- applicationDidEnterBackground：当应用程序进入后台时调用的函数。
- applicationWillEnterForeground：当应用程序重新进入前台时调用的函数。

该头文件的作用是定义了一个AppDelegate类，它是一个应用程序的入口点，并包含了应用程序的生命周期函数。

## 1. Barrier.h

这个程序文件名为Barrier.h，主要是定义了一系列的类和它们的成员函数。

1. Barrier_base类是一个基类，它包含了一些公共成员变量和纯虚函数。它被其他类继承并实现。

2. rocket类继承自Barrier_base类，它实现了父类中的纯虚函数，并添加了自己的特有函数。

3. rocket_back类也继承自Barrier_base类，它同样实现了父类中的纯虚函数，并添加了自己的特有函数。

4. weapon类继承自rocket_back类，它添加了一个额外的成员变量和纯虚函数。

5. pensil类继承自weapon类，它实现了父类中的纯虚函数。

6. razor类同样继承自weapon类，它也实现了父类中的纯虚函数。

7. NotMove类继承自Barrier_base类，它实现了父类中的纯虚函数，并添加了自己的特有函数。

8. Falldown类也继承自Barrier_base类，它实现了父类中的纯虚函数，并添加了自己的特有函数。

这个程序文件是一个C++头文件，定义了障碍物类的继承关系，并实现了一些成员函数。

## 2. choose.h

这个程序文件名是`choose.h`，代码包含了一个名为`Choose`的类，继承自`Difficulty`类。它还包含了`cocos2d.h`和`ui/CocosGUI.h`两个头文件。

`Choose`类有以下成员函数和成员变量：
- `createScene()`：静态函数，用于创建一个cocos2d场景对象。
- `init()`：覆盖`Difficulty`类的虚函数，用于初始化。
- `ui::Button* return_button`：一个UI按钮对象，用于返回按钮。
- `selectDifficulty(int level)`：选择困难等级的函数。
- `selectDifficulty_2(int level)`：选择困难等级的函数。
- `selectDifficulty_3(int level)`：选择困难等级的函数。
- `cocos2d::Sprite* spriteD`：一个cocos2d精灵对象。
- `cocos2d::Sprite* spriteD2`：一个cocos2d精灵对象。
- `cocos2d::Sprite* spriteD3`：一个cocos2d精灵对象。
- `cocos2d::Label* coinLabel`：显示金币数量的标签。
- `int level`：困难等级变量。
- `cocos2d::Label* levelLabel`：显示困难等级的标签。

该文件中的代码使用了预处理指令`#ifndef`和`#define`，来防止重复包含头文件。可以推测该文件是一个用于选择游戏困难等级的界面类。

## 3. Difficulty.h

这是一个名为Difficulty.h的头文件，用于定义一个名为Difficulty的类。这个类继承自cocos2d::Scene类，并用于创建一个场景对象。类中包含了一些成员变量和成员函数，如按钮对象、精灵对象、标签对象等。其中，createScene函数用于创建场景，init函数用于初始化场景，selectDifficulty函数用于选择难度级别。此外，还定义了一些成员变量和成员函数用于处理游戏难度相关的逻辑。

## 4. Game_first.h

这个程序文件是名为Game_first.h的头文件。它包含了一些必要的头文件和一些类的定义。其中包含了一个游戏场景类Game_first，这个类继承自Scene_one类。这个类中定义了一些成员变量和成员函数，包括创建场景的静态函数，初始化函数，关闭菜单回调函数，更新函数，按键按下和释放事件处理函数等。此外，还有一些私有成员变量和一些容器类型的变量，用于存储不同类型的障碍物、武器等。

## 5. game_first_second.h

这是一个名为game_first_second的头文件，包含了一些必要的头文件和类的声明。这个类继承自Game_first类，并添加了一些额外的成员和方法。它定义了一些变量、函数和成员变量，并声明了一些继承的方法。它还定义了一些私有成员变量和公有成员函数。这个头文件的目的是提供一个游戏的第二个场景。

## 6. HelloWorldScene.h

这个文件是一个Cocos2d-x游戏项目中的场景类的头文件。它包含了类声明和一些函数定义，如创建场景、初始化场景和关闭场景的回调函数。这个文件通过宏定义和条件编译实现了头文件的保护措施，避免被重复包含。该类是从Cocos2d-x的Scene类派生而来，用于构建游戏的场景。

## 7. player.h

该文件名为player.h，是一个源代码文件。代码定义了一个名为Base_player的基类和两个派生类Fireboy和Teacher。Base_player类具有以下成员函数和成员变量：

- 成员函数：
  - BigJump：纯虚函数，用于大跳的动作。
  - Jump：纯虚函数，用于跳的动作。
  - Move：纯虚函数，用于移动的动作。
  - set_accuracy_time：纯虚函数，用于设置准确时间。
  - set_sleep_time：纯虚函数，用于设置睡眠时间。
  - set_small_sleep_time：纯虚函数，用于设置小睡眠时间间隔。
  - set_blood：纯虚函数，用于设置血量。
  - throw_weapon：纯虚函数，用于投掷武器。
- 成员变量：
  - time：double类型，时间。
  - sleep：double类型，睡眠。
  - full_energy：double类型，满能量。
  - energy：double类型，能量。
  - velocity_player：double类型，玩家速度。
  - faster：bool类型，是否加快。
  - sprite：Sprite类型，精灵。
  - animate：Animate类型，动画。
  - animation：Animation类型，动画。
  - repeat：RepeatForever类型，重复。
  - frames：Vector<SpriteFrame*>类型，精灵帧。
  - reward：int类型，奖励。
  - blood_now：double类型，当前血量。
  - blood：double类型，血量。
  - jump_max：int类型，最大跳跃次数。
  - die：bool类型，是否死亡。
  - ready：bool类型，是否准备。
  - sequence：cocos2d::Sequence*类型，序列。

Fireboy类是Base_player类的派生类，具有以下成员函数和成员变量：

- 构造函数：用于初始化Fireboy的数据。
- 重写的成员函数：
  - BigJump：重写基类的BigJump函数。
  - Jump：重写基类的Jump函数。
  - Move：重写基类的Move函数。
  - set_accuracy_time：重写基类的set_accuracy_time函数。
  - set_sleep_time：重写基类的set_sleep_time函数。
  - set_small_sleep_time：重写基类的set_small_sleep_time函数。
  - set_blood：重写基类的set_blood函数。
  - throw_weapon：重写基类的throw_weapon函数。

Teacher类是Fireboy类的派生类，具有以下成员函数和成员变量：

- 构造函数：用于初始化Teacher的数据。
- 重写的成员函数：
  - set_blood：重写基类的set_blood函数。
  - throw_weapon：重写基类的throw_weapon函数。

该程序文件主要定义了玩家的基类和两个派生类，用于描述玩家的属性和行为。

## 8. PoolScene.h

该文件是一个名为"PoolScene.h"的头文件，用于定义一个名为"PoolScene"的类。该类继承自"Scene_one"类，并使用了"cocos2d"和"Scene_one.h"的头文件。

该类包含了以下成员函数和成员变量：
- 静态函数"createScene()"用于创建一个cocos2d场景对象。
- 虚函数"init()"用于初始化场景。
- 指针类型成员变量"show_reward"，用于显示奖励信息。
- 定义了一个私有成员变量"show_warning"，它是一个指向Label的指针，初始值为NULL。
- 整型成员变量"n"，用于记录按钮点击次数。
- spriteArray是一个长度为4的Sprite指针数组，用于存储图片。
- 函数"spriteTouched"是一个私有成员函数，接受一个指向Ref对象的指针和一个浮点数newYPosition作为参数，用于处理精灵图片的触摸事件。

类定义的最后使用了宏CREATE_FUNC(PoolScene)，该宏用于自定义创建一个该类的实例的静态函数。

## 9. Scene_one.h

这是一个名为Scene_one.h的头文件，它定义了一个名为Scene_one的类，该类继承自cocos2d::Scene。头文件还包含了cocos2d.h头文件，并使用了cocos2d命名空间。

Scene_one类具有一些成员函数，例如createScene()、init()、menuCloseCallback()、update()和setCloseItem()。它还声明了一个closeItem成员变量，类型为MenuItemImage*，以及一个show_reward成员变量，类型为Label*。

此外，Scene_one类还继承了一个名为sprite的类，该类继承自Sprite，并声明了一个纯虚函数movement()。

头文件中还定义了两个私有成员变量background和background2，类型均为Sprite*，以及一个名为velocity的float变量。

头文件的最后，使用了CREATE_FUNC宏来声明一个Scene_one对象的创建函数。

## 10. store_message.h

这是一个名为store_message的头文件，它定义了一个类store_message。该类包含了一些静态成员变量和静态成员函数。

静态成员变量:
- coin: 代表金币数量，类型为int。
- player: 代表玩家名称，类型为string。
- background: 代表背景图片，类型为string。
- wepon_first: 代表第一个武器，类型为string。
- wepon_second: 代表第二个武器，类型为string。
- DegreeOfDif: 代表难度等级，类型为int。
- paidPlayer: 一个有3个元素的int数组，用于记录已购买的玩家。
- paidWeapon: 一个有4个元素的int数组，用于记录已购买的武器。
- choosePlayer: 一个有3个元素的int数组，用于记录选择的玩家。
- chooseWeapon: 一个有4个元素的int数组，用于记录选择的武器。
- PlayerNames: 一个有3个元素的string数组，用于存储玩家名称。
- WeaponNames: 一个有4个元素的string数组，用于存储武器名称。
- WeaponPower: 一个有4个元素的int数组，用于存储武器的威力。
- StoreList: 一个有4个元素的string数组，用于存储商店列表。

该头文件没有实现具体的函数，只定义了类和成员变量。

## 11. 用一张Markdown表格简要描述以下文件的功能：AppDelegate.h, Barrier.h, choose.h, Difficulty.h, Game_first.h, game_first_second.h, HelloWorldScene.h, player.h, PoolScene.h, Scene_one.h, store_message.h。

| 文件                 | 功能                                                         |
|--------------------|------------------------------------------------------------|
| AppDelegate.h      | 定义了应用程序的入口点，并包含应用程序的生命周期函数。                                    |
| Barrier.h          | 定义了与障碍物相关的类和函数，包括火箭、武器等。                                                |
| choose.h           | 定义了一个选择界面的类，用于选择游戏难度等级。                                               |
| Difficulty.h       | 定义了一个游戏难度相关的类，包括场景的创建、初始化和难度选择功能。                          |
| Game_first.h       | 定义了一个游戏场景类，包含了场景的创建、初始化和游戏逻辑处理等。                             |
| game_first_second.h | 在Game_first类的基础上添加额外的功能，实现第二个游戏场景。                                     |
| HelloWorldScene.h  | 定义了一个名为HelloWorldScene的场景类，用于创建游戏的场景对象。                                 |
| player.h           | 定义了一个玩家类及其派生类，包括玩家属性和行为方法的定义。                                      |
| PoolScene.h        | 定义了一个游泳池场景类，包括场景的创建、初始化和游戏相关的逻辑处理功能。                        |
| Scene_one.h        | 定义了一个名为Scene_one的场景类，继承自cocos2d::Scene，具有场景的创建、初始化和逻辑处理的功能。 |
| store_message.h    | 定义了一个存储游戏信息的类，包括金币数量、玩家、武器、难度等级等信息的存储和管理。                  |

## 整体场景继承关系
|头文件	|继承关系|
|-------|--------|
|AppDelegate.h	|继承自cocos2d::Application|
|Barrier.h	|Barrier_base类被其他子类继承并实现|
|choose.h	|Choose类继承自Difficulty类|
|Difficulty.h	|Difficulty类继承自cocos2d::Scene|
|Game_first.h	|Game_first类继承自Scene_one类|
|game_first_second.h	|game_first_second类继承自Game_first类|
|HelloWorldScene.h	|HelloWorldScene类继承自cocos2d::Scene|
|player.h	|Base_player类被Fireboy和Teacher两个类继承|
|PoolScene.h	|PoolScene类继承自Scene_one类|
|Scene_one.h	|Scene_one类继承自cocos2d::Scene|
|store_message.h	|store_message类没有继承关系|

## 头文件Barrier.h（障碍物类）中各个类的继承关系
在头文件Barrier.h中，存在几个类之间的继承关系：

Barrier_base类是一个基类，其他类继承并实现了该基类。
rocket类继承自Barrier_base类。
rocket_back类继承自Barrier_base类。
weapon类继承自rocket_back类。
pensil类继承自weapon类。
razor类也继承自weapon类。
NotMove类继承自Barrier_base类。
Falldown类也继承自Barrier_base类。

继承关系示意图如下：
```
         Barrier_base
            /     \
           /       \
     rocket       rocket_back
       |             |
    weapon        NotMove
       |   
    /     \
  pencil  razor
```

其中，Barrier_base是顶级基类，rocket、rocket_back和NotMove是直接继承自Barrier_base的子类，weapon是继承自rocket_back的子类，pensil和razor是继承自weapon的子类，Falldown是继承自Barrier_base的子类。

## 头文件player.h（玩家以及boss类）中各个类的继承关系
在头文件player.h中，存在如下的类和继承关系：

Base_player类是一个基类，没有继承其他类。
Fireboy类继承自Base_player类。
Teacher类也继承自Base_player类。

所以，继承关系可以表示为：
```
   Base_player
        |
     Fireboy
     /  |  \
    /   |   \
Teacher Fox  Rat
