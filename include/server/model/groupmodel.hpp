#ifndef GROUPMODEL_H
#define GROUPMODEL_H

#include "group.hpp"
#include <string>
#include <vector>
using namespace std;

// 维护群组信息的操作接口方法，用于操作AllGroup与GroupUser两张表
class GroupModel
{
public:
    // 创建群组
    bool createGroup(Group &group);
    // 加入群组
    void addGroup(int userid, int groupid, string role);
    // 查询用户所在群组信息
    vector<Group> queryGroups(int userid);
    // 根据指定的groupid查询群组用户id列表，除userid自己，主要用于群聊业务给群组其它成员群发消息
    // 如果在线就收到，不在线就存到离线消息数据库中
    vector<int> queryGroupUsers(int userid, int groupid);
};

#endif