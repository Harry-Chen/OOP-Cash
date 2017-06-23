# Expensé 项目说明
<img src="../icons/logo.png" />
> Yet another accounting tool

## 写在前面
The project is made with ❤ by:

* 2016010981 陈晟祺 （代码中作者标识为 Harry Chen）
* 2016010912 王安冬 （代码中作者标识为 Ice Coffee）
* 2016010997 牛辰昊
* 2015010467 钮泽平

除了本页以外，整个项目的文档使用 Doxygen 生成，文中提到的各个实现细节均配置了相应的跳转链接，点击可直接导向相应的类/文件进行查看。我们基本为每个类、每个源文件都加上了可读的注释（包括版权头和简要说明），这些均可以直接在本 HTML 文档中进行查看（需要进入相应的 .h/.cpp 文件，而非类本身，才能看到版权文件头）。由于队员习惯的不同，部分注释由中文撰写，部分由英语撰写。

由于我们使用的演示平台比较特殊，只有付费用户才能进行离线导出，而采用逐一截图的方法让我无法接受。<b>故我在本文档中基本包含了展示的 slides 的所有内容，未将其一同打包。 </b>

如果尝试编译项目时遇到问题，请参见本文最后的“编译说明”部分。如有任何问题，可联系 [Harry Chen](mailto:harry-chen@outlook.com)

## 背景介绍
日常生活中，我们经常会面临几个重要的问题：我的钱去哪了？为什么我又没钱了？隔壁老王还欠我多少钱？

对于这些问题，养成记账的习惯可以避免很多不必要的麻烦。目前移动端，各色记账软件层出不穷；但在 PC 端，专门软件并不多，而且有着种种问题：太复杂（如 GNU Cash）、收费（如金蝶随手记）、杀鸡用牛刀（如 Excel）等等。

因此 ，我们开发了 Expensé，一款很 naïve 的记账软件，用来满足这个需求。

## 需求分析
* 基本记账功能：简单记账法，含收入、支出、转账、借还款
* 多账户支持：钱包、在线支付、银行卡等
* 多用户支持：注册与登陆系统、用户数据隔离
* 多货币支持：支持不同汇率的货币
* 收支分类支持：饮食、交通、学习、在马路边捡到的……
* 多条件组合查询：金额范围、日期范围、账户、时间、备注、状态等参数，其中的一个或多个
* 统计与可视化：选定时间段的统计（年月日周）、条件查询结果的统计、统计图表（折线图、柱状图）的绘制
* 数据持久化与备份：数据库连接与存储、数据导入导出（JSON）
* 多前端实现：GUI、<i>CLI</i>（最终未实现）
* 日志与审计：调试模式下完整的日志记录，生产模式则只记录错误

## 人员分工
注：任务量与列出的具体条数并非成正比

* 陈晟祺（组长）
    * 项目整体架构、模型抽象
    * 需(xiang)求(mu)控(jing)制(li)
    * 后端数据综合处理、数据库连接
    * 账单组合查询
    * 模块整合、代码规范
    * 程序 i18n 框架与多语言翻译
    * 程序员催促师兼 Bug Hunter

* 王安冬
    * 美工、GUI 设计
    * 主程序框架
    * 登陆窗口
    * 用户管理、设置
    * 数据导入导出

* 钮泽平
    * 账单、增、删、改
    * 分类、账户、货币管理
    * 程序多线程化
    * 性能调优

* 牛辰昊
    * 综合查询模块
    * 数据可视化（绘图）
    * 账单查询与详情呈现

## 框架设计
项目整体架构大致如下图：

<img src="../artwork/architecture.png" width="1000px" />

本项目采用了比较经典的存储——持久——业务——展现四层逻辑，每层通过对应的接口与上下层沟通，用户请求通过每层的处理得到实现。

项目整体的 UML 图略去。各个类的 UML 图，以及各类之间的调用、依赖关系，均在文档中给出。


## 技术细节
各个核心模块在上述的需求分析以及项目架构中已有提及，解释说明与详细实现可见各个模块对应的类对应的文档（包括且不限于类页面、头文件页面、实现页面）。本节只补充代码文档中未涉及的部分。

### 设计模式（部分）：
* 模板方法（Template Method），见 [ItemManager](@ref ItemManager)
* 生成器模式（Builder Pattern），见 [Query](@ref Query)
* 单例模式（Singleton Pattern），见 [DatabaseHelper](@ref DatabaseHelper) 以及 [ItemSearcher](@ref ItemSearcher)
* 策略模式（Strategy Pattern），见 [applyChangeStrategy](@ref applyChangeStrategy)
* 抽象工厂模式（Abstract Factory Pattern），见 [PlotSystem](@ref PlotSystem)

### 设计思想：
* 借鉴与分享
    * 多使用现成的开源方案，不重复发明轮子
    * 项目以 Apache 2.0 协议开源
* 前后端分离与解耦合
    * 后端：底层基础接口（增删改查）
    * 前端：增强功能（绘图、统计等）
* 多线程并行
    * 异步进行耗时操作
    * 分离UI线程与IO线程

### 开源资源
* Qt 5.8.0 & C++ STL & boost：跨平台、全功能的开发库
* QCustomPlot (http://www.qcustomplot.com/)：成熟的 Qt 绘图控件
* SQLite (https://www.sqlite.org)：轻巧的小型 SQL 数据库
* sqlpp11 (https://github.com/rbock/sqlpp11)：基于 C++ 11 的方便易用的 ORM （对象关系模型）
* Log11  (https://github.com/meox/Log11)：基于 C++ 11 的小巧、线程安全的日志库
* date (https://github.com/HowardHinnant/date)：基于 C++ 11 的时间日期处理库
* Doxygen (http://doxygen.org)：强大的自动文档生成工具
* Git & GitHub：最<b>清真</b>的版本控制与源码管理系统

## 编译说明
### 环境说明
本项目在以下环境编译通过且能运行：
* Qt 5.8.0 (windows-x86-msvc2015_64) with MSVC 14.0 (shipped with VS 2015 Update 3)
* Qt 5.8.0 (windows-x86-msvc2015_64) with MSVC 14.1 (shipped with VS 2017 RC)
* Qt 5.8.0 (mac-x64-clang) with Clang 8.1.0 (shipped with XCode 8.3.2)

在下列环境编译通过但未测试运行：
* Arch Linux with Qt 5.9.0
* Ubuntu 17.04 with Qt 5.8.0

在下列环境确认无法编译通过：
* Qt <= 5.5.0

### 编译方法
本项目的编译还需要 qmake, CMake 以及 GNU Make 的支持。一般的编译步骤为：

1. 单独编译 `sqlpp11-connector-sqlite3` 库：
~~~~~
git clone https://github.com/rbock/sqlpp11-connector-sqlite3.git
mkdir build && cd build
cmake ../sqlpp11-connector-sqlite3/
make
~~~~~
2. 将得到的静态库文件（.a或者.lib）复制到本项目的 `libs` 目录下
3. 在 `OOP-Cash.pro` 文件中添加对该库的引用，如 `LIBS += -Llibs -lyourlib`
4. 执行 `qmake`
5. 执行 `make release`
6. 如要得到英语版本，可将源码目录中 `lang/en_US.qm` 复制到编译得到程序的工作目录

注：上述步骤只可用于编译 Release 版本，编译 Debug 版本需要将上述的库也进行 Debug 编译。我在项目中已经包含了对某些平台预编译的该库（for Windows 10 x64 & macOS 10.10）并在 `OOP-Cash.pro` 中进行了配置，但依旧不保证可以立刻正确编译运行。

### 多语言支持
1. 在项目根目录执行 `lupdate lang/en_US.ts`
2. 使用 `Qt Linguist` 等工具更新翻译
3. 执行 `lrelease lang/en_US.ts`
4. 用新得到的 `lang/en_US.qm` 覆盖老的文件


## 项目总结


