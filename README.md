项目基于Qt库开发

## 类的继承和派生关系

```
QWidget
├─ StartMenu
└─ GameWindow

QLabel
└─ myObject
   ├─ myBlock
   └─ myCharacter
      ├─ myTower
      └─ myMonster

myProperty
```

窗口类StartMenu和GameWindow继承QWidget类

实体类myObject继承QLabel类，含有虚函数act用于派生类重载，act是实体活动的主要逻辑

myBlock类用于显示地块，含有指向存在于地块上的单位的指针，单位之间的交互基本都是通过地块作为中介进行

myCharacter类作为所有敌方和我方单位的基类，拥有指向所在地块的指针，定义了攻击和受击等函数用于实现单位的各种行为

myTower和myMonster继承myCharacter，重载了act函数用于分别执行双方单位不同的行动逻辑

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
   ├─ level
   │  ├─ 1
   │  │  ├─ archer.txt
   │  │  ├─ bat.txt
   │  │  └─ map.txt
   │  ├─ BloodMoonTower.txt
   │  └─ Spirit.txt
   ├─ main.cpp
   ├─ myblock.cpp
   ├─ myblock.h
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
   │  ├─ block
   │  │  ├─ c.png
   │  │  ├─ d.png
   │  │  ├─ gc.png
   │  │  ├─ gd.png
   │  │  ├─ gl.png
   │  │  ├─ gld.png
   │  │  ├─ glu.png
   │  │  ├─ gr.png
   │  │  ├─ grd.png
   │  │  ├─ gru.png
   │  │  ├─ gu.png
   │  │  ├─ l.png
   │  │  ├─ ld.png
   │  │  ├─ r.png
   │  │  └─ rd.png
   │  ├─ Grass Tileset.png
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