# 记账软件

---

实现语言： C++ **14**（ORM库的限制）  
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
* SQLite ORM：https://github.com/fnc12/sqlite_orm
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

###表User 

|字段|类型|说明|
|---|---|---|
|*id*|auto_increment||
|name|varchar||
|password|varchar||


```C++
class UserManager{
    QVector<User> getAllUsers();
    bool addUser(User &user);
    bool removeUser(User &user);
    bool changePassword(QString newPassword);
    bool login(User &user);
}

class User{
    QString username;
    QString password;
    int uid;
public:
    QVector<Account> getAccounts()
}
```

###表Account 

|字段|类型|说明|
|---|---|---|
|*id*|auto_increment||
|name|varchar||
|uid|integer|User::id|
|cid|integer|Currency::id|

```C++
class AccountManager{
    User *user;
private:
    QVector<Account> getAllAccounts();
    bool addAccount(Account &account);
    bool removeAccount(Account &account);
}

class Account{
    int id;
    QString name;
    int uid;
    int cid;
    int balance;
public:
    QVector<Account> getOwners();
    Currency getCurrency();
    bool setOwners(QVector<Account> owners);
    bool setCurrency(Currency currency);
}
```


###表Currency 

|字段|类型|说明|
|---|---|---|
|*id*|auto_increment||
|name|varchar||
|rate|number||

```C++
class Currency{
    int id;
    QString name;
    int rate;
    get,set;
}
```

###表Bill 

|字段|类型|说明|
|---|---|---|
|*id*|auto_increment||
|from|integer|Account::id|
|to|number|Account::id|
|creator|integer|User::id|
|quantity|integer||
|ctime|datetime|交易写入的精确时间|
|finished|bool|已完成|
|time|datetime|发生的（准确）日期|
|note|varchar||

```C++
class Bill{
    int id;
    int fromAccountId;
    int toAccountId;
    int creatorId;
    int quantity;
    QDateTime createTime;
    bool finished;
    QDateTime finishTime;
    QString note;
    public:
    get,set
}
```

```C++
class Query{
    QVector<int> creatorIds;
    QVector<int> fromAccountIds;
    QVector<int> toAccountIds;
    QPair<int,int> quantityRange;
    QPair<QDateTime,QDateTime> timeRange;
    bool finished;
    friend class QueryFactory;
    QString keyword;
    public:
        QVector<Bill>* doQuery(){
            
        }
}

class QueryFactory{
    Query *query
public:    
    QueryFactory(){
    }
    init(){
        if(query) delete query;
        query = new Query();
    }
    ~QueryFactory(){
        delete query;
    }
    QueryFactory& addCreator(int _creatorID){
        query->creatorIds.push_back(_creatorID);
        return *this;
    }
    QueryFactory& addFromAccount(int _fromAccountID){
        query->fromAccountIds.push_back(_fromAccountID);
        return *this;
    }
    const Query& build(){
        return *query;
    }
    
    .....
}
QueryFactory factory;
factory.init();
factory.addCreator(1);
factory.addtoAccount(29);
QVector<Bill>* results = factory.build().doQuery();
```
