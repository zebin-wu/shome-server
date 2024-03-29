/**
 * dev.h
 * 这个头文件包含设备的描述的结构体, 以及操作它的各种方法, 还包含todo任务的方法
 * DevConfig是一个通用的对一个设备进行描述的结构体, 它包括设备属性全面的描述
 * 你可以轻松的将各种设备接入到这个系统中来
 * 
 * 设备的类型可以无限扩展, 详情看dev-type.h
 * 
 * todo任务的相关结构体在dev-detail.h中定义
 * 
 * 所有的设备, todo, set, room都是由链表管理, 通过get...list()来获取链表的头结点的指针
 * 
 */
#ifndef _DEVICE_TREE_H
#define _DEVICE_TREE_H

#include <stdint.h>
#include <stdbool.h>

#include "dev-ext.h"
#include "../dev-type.h"

//设备属性
typedef struct DevConfig {
    bool        isOnline;       //是否在线
    char        id[ID_LEN + 1]; //设备的唯一标识
    char        name[NAME_LEN]; //设备名
    dev_type_t  type;           //设备的类型
    node_t      *keyList_head;  //key-value链表
    void        *ep_event;      //eventConfig指针
    void        *todolist_head;
    void        *tasklist_head;
    room_t      *room;          //所在的房间
} DevConfig_t;

//获得链表头指针的地址
extern node_t *devlist_head;
extern node_t *todolist_head;
extern node_t *setlist_head;
extern node_t *roomlist_head;

/**
 * ext_base子类获取一个新的Id
 * @head ext_base子类的链表
 * @return new id
*/
int ext_getNewId(node_t *head);

/**
 * @brief 对Id进行重新排序 回调函数
 * @param ext ext_base结构地址
 * @param tmp 传入的ID, 每次会叠加
 * @example uint32_t tmp; travelList(list_head, (manipulate_callback)ext_sortId_cb, &tmp);
*/
void ext_sortId_cb(ext_base_t *ext, int *tmp);
/**
 * @brief 比较ID
*/
bool ext_isId(ext_base_t *ext, const id_t *id);

//dev
DevConfig_t *initDevConfig();
bool isDevId(DevConfig_t *devConfig, const char *id);
void destoryDevConfig(DevConfig_t *devConfig);
//todo
void registerTodo(todo_t *todo);
void destoryTodo(todo_t *todo);
bool isMeetCon_sensor(todo_t *todo, DevConfig_t *devConfig);
void runTodo(todo_t *todo);
//task-set 任务集
task_set_t *initTaskSet();
void destoryTaskSet(task_set_t *set);
void registerSet(task_set_t *set);
void runTaskSet(task_set_t *set);
//task-dev
task_dev_t *initTaskDev();
void registerTaskDev(task_dev_t *task);
void destoryTaskDev(task_dev_t *task);
void runTaskDev(task_dev_t *task);
void updateTaskDev(task_dev_t *task, node_t *keylist_head);
//room
room_t *initRoom();
void registerRoom(room_t *room);
void destoryRoom(room_t *room);
//room_dev
room_dev_t *initRoomDev();
void destoryRoomDev(room_dev_t *room_dev);
bool isRoomDevId(room_dev_t *room_dev, const char *id);
void registerRoomDev(room_dev_t *room_dev, room_t *room);
//con_time
int setDays(con_time_t *con_time, const char *buf); // '*'表示该位已设置
char *daysToStr(con_time_t *con_time, char *buf, uint8_t buflen);
#ifdef DEBUG_DEV
void printDev(DevConfig_t *dev);
void printTodo(todo_t *todo);
void printSet(task_set_t *set);
void printTask(task_dev_t *task);
void printRoom(room_t *room);
void printRoomDev(room_dev_t *room_dev);
#endif //DEBUG_DEV

#endif //_DEVICE_TREE_H