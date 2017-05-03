记账软件
---

实现语言： C++ 11
平台： Qt 5.8 on Windows / Linux / macOS  
学习的技术：  

* Git 
  - SourceTree on Windwos & macOS
  - git on Linux
* 多线程 GUI
* 前后端分离
* SQL

拟采用的第三方库：  

* Qt GUI & XML & Network（optional）
* SQLite ORM：https://github.com/rbock/sqlpp11
* QCustomPlot绘图：http://www.qcustomplot.com/
* CSV导入导出：https://libqxt.bitbucket.io/doc/0.6/qxtcsvmodel.html 或 https://github.com/iamantony/qtcsv
* 日志：https://github.com/muflihun/easyloggingpp

基本设计：  
--
* 前后端分离
  - 所有数据操作均在后端进行
  - 前端仅调用后端暴露的 API 进行数据查询与修改
  - 可开发 GUI <del>与 Console 两套前端 （optional）</del>
* 简单记账（即非复式）
* 多用户支持
  - 简单的用户注册与认证系统，独立数据表
  - <del>加密存储数据（optional）</del>
* 支持多个形式的账户
  - 现金    
  - 在线支付账户
  - 银行卡（带自动结息/还款提醒等功能）
* 支持操作
  - 收入
  - 支出
  - 转账（用户自身账户间以及外部）
  - 借/还款跟踪
* 所有操作的日志记录
* 统计与可视化
  - 按时间周期的收入支出统计（如年月周日账单）
  - 任意选择时间段的统计
  - 回溯到任意时间点查看账户情况
  - 所有统计信息可以图和表形式呈现
* 数据持久化与备份
  - 使用 SQLite 作为数据库后端
  - 支持导出导入数据到固定格式（如CSV/XML/JSON）
  - 支持服务器端备份与恢复（optional）
  
```C++
template<typename T>
class ItemManager{
	// 所有 Manager 类型的基类
    ItemManager() = delete;
	// 构造方法：传入数据库连接
    ItemManager(sqlpp::sqlite3::connection *_db):db(_db){}
	// 获取当前所有特化类型的对象
    virtual QVector<T> getAllItems() = 0;
	// 新增对象
    virtual ID addItem(const T &newItem) = 0;
	// 通过ID移除特定对象
    virtual bool removeItemById(const int itemId) = 0;
	// 修改对应对象
    virtual bool modifyItem(const T &newItem) = 0;
}
```

### 表User 

|字段|类型|说明|
|---|---|---|
|*id*|integer|auto_increment|
|username|text||
|nickname|text|非必需|
|password|text||


```C++
class UserManager : public ItemManager<User>
{
public:
    QVector<User> getAllItems();
    ID addItem(const User &newItem);
	// 只能移除当前登录的用户
    bool removeItemById(const int itemId);
	// 只能修改当前登录的用户
    bool modifyItem(const User &newItem);
    ID login(const User& loginInfo);
    void logout();
}

class User{
public:
    User(ID _id = -1, QString _username = QString(), QString _nickname = QString(), QString _password = QString());
    ID id;
    QString username;
    QString nickname;
}
```

### 表Account 

|字段|类型|说明|
|---|---|---|
|*id*|integer|auto_increment|
|name|text||
|uid|integer|User(id)|
|cid|integer|Currency(id)|

```C++
class AccountManager : public ItemManager<Account>
{
public:
    AccountManager(UserManager *userMan);
    QVector<Account> getAllItems();
	// 只能为当前登录的用户中增加账户
    ID addItem(const Account &newItem);
    bool removeItemById(const int itemId);
	// 只能修改当前登录用户名下的账户
    bool modifyItem(const Account &newItem);
}

class Account{
public:
    Account(ID _id = -1, QString _name = QString(), ID _uid = -1, ID _cid = -1);
    ID id;
    QString name;
    ID uid;
    ID cid;
}
```

### 表Category
|字段|类型|说明|
|---|---|---|
|*id*|integer|auto_increment|
|name|text||
|uid|integer|User(id)，但若为-1代表系统内置的全局分类|

```C++
class CategoryManager : public ItemManager<Category>
{
public:
	//构造方法：传入 UserManager *
    CategoryManager(UserManager *userMan);
	// 获取当前用户创建的和全局的所有分类
    QVector<Category> getAllItems();
	// 只能给当前用户添加、移除、修改分类
    ID addItem(const Category &newItem);
    bool removeItemById(const int itemId);
    bool modifyItem(const Category &newItem);
};

class Category
{
public:
    Category(ID _id = -1, QString _name = QString(), ID _uid = -1);
    ID id;
    QString name;
    ID uid;
}
```


### 表Currency 

|字段|类型|说明|
|---|---|---|
|*id*|integer|auto_increment|
|uid|integer|User(id)，但若为-1代表系统内置的全局分类|
|name|text||
|rate|integer|含两位小数的整数形式（如12.34->1234)|

```C++
class CurrencyManager : public ItemManager<Currency>
{
public:
    CurrencyManager(UserManager *userMan);
	// 获取当前用户创建的和全局的所有货币
    QVector<Currency> getAllItems();
	// 只能给当前用户添加、移除、修改货币
    ID addItem(const Currency &newItem);
    bool removeItemById(const int itemId);
    bool modifyItem(const Currency &newItem);
};

class Currency{
public:
    Currency(ID _id = -1, ID _uid = -1, QString _name = QString(), unsigned int _rate = 0100);
    ID id;
    ID uid;
    QString name;
    unsigned int rate;
}
```

### 表Bill 

|字段|类型|说明|
|---|---|---|
|*id*|auto_increment||
|from|integer|Account(id)，如为-1则表示不存在|
|to|integer|Account(id)，如为-1则表示不存在|
|creator|integer|User(id)|
|category|integer|Catrgory(id)
|quantity|integer|交易数额|
|ctime|integer|交易写入的精确时间（转换为QDateTime）|
|finished|integer|已完成|
|time|integer|发生的（准确）日期（转换为QDate）|
|note|text|备注，可为空|

注：对于quantity的货币选取，默认为from对应的account对应的货币。但如果from为-1，则为to对应的货币。

```C++
class BillManager : public ItemManager<Bill>
{
public:
    BillManager(UserManager *userMan);
    QVector<Bill> getAllItems();
    ID addItem(const Bill &newItem);
    bool removeItemById(const int itemId);
    bool modifyItem(const Bill &newItem);
};


class Bill{
    Bill(ID _id = -1, ID _from = -1, ID _to = -1,
         ID _creator = -1, ID _category = -1, int _quantity = 0,
         QDateTime _ctime = QDateTime::currentDateTime(),
         bool _finished = true,
         QDate _date = QDate::currentDate(),
         QString _note = QString());
    ID id;
    ID from;
    ID to;
    ID creator;
    ID category;
    int quantity;
    QDateTime ctime;
    bool finished;
    QDate date;
    QString note;
}
```

```C++
class Query
{
public:
	// 具体用法可见代码
    static Query newQuery(sqlpp::sqlite3::connection *_db);
    Query& addCreatorId(ID _creatorId);
    Query& addFromAccountId(ID _fromAccountId);
    Query& addToAccountId(ID _toAccountId);
    Query& addCategoryId(ID _categoryId);
    Query& setQuantityRange(unsigned int from, unsigned int to);
    Query& setDateRange(const QDate &start, const QDate &end);
    Query& setFinished(bool _finished);
    Query& setKeyword(const QString &_keyword);
    QVector<Bill> doQuery();
};

```
