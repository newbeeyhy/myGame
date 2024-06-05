项目基于Qt库开发

## 操作说明
1. 怪物按时间顺序生成，到达终点扣除关卡HP，消灭所有怪物获得胜利。
2. 防御塔使用鼠标拖动到地块上进行部署，每个防御塔消耗100cost，每击杀一个怪物增加50cost。
3. 右侧词缀栏显示我方词缀，每种词缀初始数量为1个，击杀怪物有20%概率随机获得一种词缀。
4. 词缀通过拖动施予我方防御塔，每个防御塔可以装备两个词缀，词缀持续时间无限，一旦装备无法更换。
5. 怪物击杀我方单位同样有20%概率获得随机敌方词缀，敌方词缀会自动为新生成的怪物装备。
6. 敌方词缀最多两个，每当敌方获得新的词缀，若已经拥有两个词缀，会将最早获得的删除，并加入新获得的词缀。
7. 词缀的功能主要为改变数值，获得新的能力。
8. 存档功能，游戏内暂停，并点击“save”，选择保存位置，可以将当前游戏状态保存。
9. 在开始界面点击“Load Game”，选择已有的存档，可以加载之前保存的游戏状态。
10. 倍速功能，初始为一倍速，点击“>>”开启二倍速，点击“>”恢复一倍速。
11. 我方词缀效果介绍：
   - 狂暴：攻击力和生命值翻倍，攻击速度减半。
   - 冰冻：攻击使敌方目标移动速度和攻击速度减半。
   - 放血：攻击会使敌方单位处于流血状态，处于流血状态的敌方单位每秒受到一定的真实伤害。
   - 群攻：可以同时攻击两个敌方单位。
   - 击晕：每次攻击有20%的概率使攻击目标停止行动一秒。
   - 反隐：可以攻击和阻挡迷彩和隐匿的敌方单位。
   - 连击：攻击速度翻倍。
12. 敌方词缀效果介绍：
   - 复生：首次死亡可以复活一次。
   - 活力：生命值翻倍。
   - 坚固：防御力翻倍。
   - 急速：移动速度翻倍。
   - 力量：攻击力翻倍。
   - 削弱：攻击可使我方单位攻击力下降。
   - 亡语：死亡时对以自身为中心的九格中的我方单位造成一次巨额伤害。
   - 隐匿：无法被我方远程单位攻击。
   - 闪现：被阻挡时可以直接移动至我方单位身后，有5秒的冷却时间。

## 类的继承和派生关系

```
QDialog
├─ StartMenu
└─ LevelSelectMenu

QWidget
└─ GameWindow

QLabel
└─ myObject
   ├─ myBlood
   ├─ myBlock
   └─ myCharacter
      ├─ myTower
      └─ myMonster

myProperty
```

- 对话框类 **StartMenu** 和 **LevelSelectMenu** 继承 **QDialog** 类。

- 游戏窗口类 **GameWindow** 继承 **QWidget** 类。

- 实体类 **myObject** 继承 **QLabel** 类，含有虚函数 **act()** 用于派生类重载，**act()** 是实体活动的主要逻辑。

- **myBlood** 类用于显示单位血条。

- **myBlock** 类用于显示地块，含有指向存在于地块上的单位的指针，单位之间的交互基本都是通过地块作为中介进行。

- **myCharacter** 类作为所有敌方和我方单位的基类，拥有指向所在地块的指针，定义了攻击和受击等函数用于实现单位的各种行为。

- **myTower** 和 **myMonster** 继承 **myCharacter** ，重载了 **act()** 函数用于分别执行双方单位不同的行动逻辑。

## 文件结构（不包含用于生成和编译的文件）
```
demo
├─ demo.pro.user
├─ README.md
└─ src
   ├─ demo.pro
   ├─ demo.pro.user
   ├─ gamewindow.cpp
   ├─ gamewindow.h
   ├─ gamewindow.ui
   ├─ gem.ico
   ├─ level
   │  ├─ 1
   │  │  ├─ archer.mst
   │  │  ├─ bat.mst
   │  │  └─ map.mp
   │  ├─ 2
   │  │  ├─ archer1.mst
   │  │  ├─ archer2.mst
   │  │  ├─ archer3.mst
   │  │  ├─ archer4.mst
   │  │  ├─ archer5.mst
   │  │  ├─ bat1.mst
   │  │  ├─ bat2.mst
   │  │  ├─ bat3.mst
   │  │  ├─ bat4.mst
   │  │  ├─ bat5.mst
   │  │  └─ map.mp
   │  ├─ BloodMoonTower.twr
   │  └─ Spirit.twr
   ├─ levelselectmenu.cpp
   ├─ levelselectmenu.h
   ├─ levelselectmenu.ui
   ├─ main.cpp
   ├─ myblock.cpp
   ├─ myblock.h
   ├─ myblood.cpp
   ├─ myblood.h
   ├─ mycharacter.cpp
   ├─ mycharacter.h
   ├─ mymonster.cpp
   ├─ mymonster.h
   ├─ myobject.cpp
   ├─ myobject.h
   ├─ myproperty.cpp
   ├─ myproperty.h
   ├─ mytower.cpp
   ├─ mytower.h
   ├─ recourse
   │  ├─ BGM
   │  │  ├─ Der Hexenkonig.mp3
   │  │  ├─ Founding Stone.mp3
   │  │  ├─ In Originium Covered Fields.mp3
   │  │  ├─ Merciful Broken Sun.mp3
   │  │  └─ shenchizhiying.mp3
   │  ├─ block
   │  │  ├─ c.png
   │  │  ├─ d.png
   │  │  ├─ gc.png
   │  │  ├─ gd.png
   │  │  ├─ gl.png
   │  │  ├─ gld.png
   │  │  ├─ glrd.png
   │  │  ├─ glru.png
   │  │  ├─ glrud.png
   │  │  ├─ glu.png
   │  │  ├─ gr.png
   │  │  ├─ grd.png
   │  │  ├─ gru.png
   │  │  ├─ gu.png
   │  │  ├─ l.png
   │  │  ├─ ld.png
   │  │  ├─ r.png
   │  │  └─ rd.png
   │  ├─ blood
   │  │  ├─ 0.png
   │  │  ├─ 10.png
   │  │  ├─ 100.png
   │  │  ├─ 12.png
   │  │  ├─ 14.png
   │  │  ├─ 16.png
   │  │  ├─ 18.png
   │  │  ├─ 2.png
   │  │  ├─ 20.png
   │  │  ├─ 22.png
   │  │  ├─ 24.png
   │  │  ├─ 26.png
   │  │  ├─ 28.png
   │  │  ├─ 30.png
   │  │  ├─ 32.png
   │  │  ├─ 34.png
   │  │  ├─ 36.png
   │  │  ├─ 38.png
   │  │  ├─ 4.png
   │  │  ├─ 40.png
   │  │  ├─ 42.png
   │  │  ├─ 44.png
   │  │  ├─ 46.png
   │  │  ├─ 48.png
   │  │  ├─ 50.png
   │  │  ├─ 52.png
   │  │  ├─ 54.png
   │  │  ├─ 56.png
   │  │  ├─ 58.png
   │  │  ├─ 6.png
   │  │  ├─ 60.png
   │  │  ├─ 62.png
   │  │  ├─ 64.png
   │  │  ├─ 66.png
   │  │  ├─ 68.png
   │  │  ├─ 70.png
   │  │  ├─ 72.png
   │  │  ├─ 74.png
   │  │  ├─ 76.png
   │  │  ├─ 78.png
   │  │  ├─ 8.png
   │  │  ├─ 80.png
   │  │  ├─ 82.png
   │  │  ├─ 84.png
   │  │  ├─ 86.png
   │  │  ├─ 88.png
   │  │  ├─ 90.png
   │  │  ├─ 92.png
   │  │  ├─ 94.png
   │  │  ├─ 96.png
   │  │  └─ 98.png
   │  ├─ buff
   │  │  ├─ bingdong.png
   │  │  ├─ fangxie.png
   │  │  ├─ fusheng.png
   │  │  ├─ huoli.png
   │  │  ├─ jiangu.png
   │  │  ├─ jisu.png
   │  │  ├─ jiyun.png
   │  │  ├─ kuaigong.png
   │  │  ├─ kuangbao.png
   │  │  ├─ liliang.png
   │  │  ├─ qungong.png
   │  │  ├─ tudu.png
   │  │  ├─ wangyu.png
   │  │  ├─ yingyan.png
   │  │  └─ yinni.png
   │  ├─ Grass Tileset.png
   │  ├─ icon
   │  │  └─ gem.png
   │  ├─ monster
   │  │  ├─ archer-fliped.gif
   │  │  ├─ archer.gif
   │  │  ├─ archerattk.gif
   │  │  ├─ archerattkf.gif
   │  │  ├─ bat-x4-fliped.gif
   │  │  ├─ bat-x4.gif
   │  │  ├─ frog-x4-fliped.gif
   │  │  ├─ frog-x4.gif
   │  │  ├─ ghost-x4-fliped.gif
   │  │  ├─ ghost-x4.gif
   │  │  ├─ skeleton-x4-fliped.gif
   │  │  └─ skeleton-x4.gif
   │  ├─ spirit
   │  │  ├─ Attack.gif
   │  │  ├─ Attackf.gif
   │  │  ├─ Idle.gif
   │  │  └─ Idlef.gif
   │  ├─ tower
   │  │  └─ BloodMoonTower.gif
   │  └─ vfx
   ├─ resource.qrc
   ├─ startmenu.cpp
   ├─ startmenu.h
   └─ startmenu.ui
```