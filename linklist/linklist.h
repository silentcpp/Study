/*linklist.h*/
#ifndef __LINKLIST_H__
#define __LINKLIST_H__
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif
    /* 初始化链表
     * @param 1, 每次插入的数据大小,如果不固定写0,
     * 下次调用inser_list的时候第3个参数写实际大小.如果数据大小固定,
     * 则直接写实际大小,下次调用insert_list的时候可以忽略第3个参数.
     * return, 成功返回链表起始地址,失败返回NULL
     * */
	void *init_list(const unsigned char data_size);

    /* 插入链表
     * @param 1，plist已初始化的链表
     * @param 2，要插入链表的数据
     * @param 3，(可选参数,如果大小不固定请写实际大小)要插入链表的数据大小
     * @return, 成功true,失败false
     * */
	bool insert_list(void *plist,const void *const data,...);

    /* 从链表删除一个数据
     * @param 1，初始化的链表
     * @param 2，处理要删除的逻辑函数
     *	@return, true停止循环，false继续循环
     * @param 3，附加参数用作判断
     * @return, 成功true,失败false
     * */
	bool delete_list(void *plist, bool(*call)(void *, void *), void *arg);

    /* 销毁链表
     * @param 1，初始化的链表指针地址
     * @return, 成功true,失败false
     * */
	bool destroy_list(void **plist);

    /* 链表逆转
     * @param 1，初始化的链表
     * @return, 成功true,失败false
     * */
	bool reversion_list(void *plist);

    /* 遍历链表
     * @param 1，初始化的链表
     * @param 2，逻辑处理函数
     *	return, true停止循环，false继续循环
     * @param 3，附加判断参数
     * @return, 回调函数的返回值 
     * */
	bool traversal_list(void *plist, bool(*call)(void *, void *), void *arg);

    /* 倒序遍历链表
     * @param 1，初始化的链表
     * @param 2，逻辑处理函数
     *	return, true停止循环，false继续循环
     * @param 3，附加判断参数
     * @return, 回调函数返回值
     * */
    bool reversion_traversal_list(void *plist, bool(*call)(void *, void *), void *arg);

    /*
     * 获取链表的大小(头节点不算在内)
     * @param 1, 初始化的链表 
     * @return, 链表大小
     * */
	const size_t get_list_size(void *plist);

    /*
     * 获取第一个节点数据
     * @param 1, 初始化的链表
     * @return, 链表数据
     * */
	void *get_list_last_data(void *plist);

    /*
     * 获取最后一个节点数据
     * @param 1, 初始化的链表
     * @return, 链表数据
     * */
	void *get_list_frist_data(void *plist);

    /*
     * 写入链表到文件
     * @param 1, 初始化的链表
     * @param 2, 保存的路径
     * @param 3, 保存模式同fopen
     * @return, true成功，false失败
     * */
	bool write_list_to_file(void *plist, const char *pathname, const char *mode);

    /*
     * 从文件读数据到list
     * @param 1, 初始化的链表
     * @param 2, 文件路径名
     * @param 3, 数据大小
     * @return, true成功,false失败
     * */
	bool read_file_to_list(void *plist, const char *pathname, const char* mode);

    /* 查找链表数据
     * @param 1, 初始化的链表
     * @param 2, 要查询的数据
     * return, 成功数据位置,失败-1
     * */
    const int find_list_data(void* plist,const void* const data);

    /* 返回节点数据
     * @param 1, 初始化的链表
     * @param 2, 下标
     * return, 如果存在返回数据,否中返回NULL
     * */
    void* at_list(void* plist,const size_t id);

    /* 设置数据大小
     * @param 1, 初始化的链表
     * @param 2, 节点大小
     * */
    void set_list_data_size(void* plist,const int size);

    /* 获取数据大小
     * @param 1, 初始化的链表
     * @return, 节点大小
     * */
    const int get_list_data_size(void* plist);
#ifdef __cplusplus
}
#endif
#endif // !__LINKLIST_H__
