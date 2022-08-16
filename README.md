# 集群聊天服务器

## 2022.8.13
完成了数据库封装，业务模块与网络库模块解耦，实现了部分登录业务和注册业务并进行了验证，目前登录业务存在用户下线后未注销问题

## 2022.8.14
完成客户端异常退出后调整User表状态为offline，点对点聊天业务（对方在线由服务器直接转发，否则存入离线消息表），添加好友（数据库操作），建群（数据库操作），加入群（数据库操作），群聊业务（点对点与GroupUser表，离线消息表的结合）

## 2022.8.15
### 完成客户端的开发
#### main线程用作发送线程，子线程用作接收线程，main线程根据for (;;)中的三种选择之一(登录、注册、退出)进行处理，其中
登录-->main线程发送信息给服务端-->main线程阻塞-->服务端发送信息给子线程-->子线程处理注册的响应逻辑-->通过信号量唤醒main线程
注册-->main线程发送信息给服务端-->main线程阻塞-->服务端发送信息给子线程-->子线程处理登录的响应逻辑-->通过信号量唤醒main线程
退出-->直接退出

#### 子线程-接收消息线程逻辑
接收范围是来自服务器的离线消息（点对点聊天，群聊消息），注册响应消息（完成了需要通过信号量唤醒main），登录响应消息（完成了需要通过信号量唤醒main）。

#### 主线程进入mainMenu
登录成功后主线程进入mainMenu，用户需要通过输入具体的命令进行操作，命令可通过哈希表--commandHandlerMap来映射对应的操作。
各种命令的输入格式如下:
unordered_map<string, string> commandMap = {
    {"help", "显示所有支持的命令，格式help"},
    {"chat", "一对一聊天，格式chat:friendid:message"},
    {"addfriend", "添加好友，格式addfriend:friendid"},
    {"creategroup", "创建群组，格式creategroup:groupname:groupdesc"},
    {"addgroup", "加入群组，格式addgroup:groupid"},
    {"groupchat", "群聊，格式groupchat:groupid:message"},
    {"loginout", "注销，格式loginout"}};

##### help-打印各种命令的作用与输入格式
##### chat-将点对点消息发送给服务器
目标用户在线就直接转发，不在线就插入数据库。
##### addfriend-向服务器发送添加好友消息
服务器收到后，修改数据库。
##### creategroup addgroup groupchat 
与addfriend同理。
##### loginout-客户端退出
先将请求发送给服务端，发送以后isMainMenuRunning置为false，客户端会退出MainMenu。

## 2022.8.16
nginx完成负载均衡配置。
完成了redis作为消息队列，实现跨服务器的聊天。

# 2022.8.17-8.20
整理项目问答
