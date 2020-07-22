/*linklist.c*/
#include "linklist.h"
#include <stdio.h>

/*节点声明*/
typedef struct node {
    /*数据长度*/
    unsigned char length;

    /*数据指针*/
    void *pdata;

    /*下一个节点地址*/
    struct node *pnext;
}node_t, *pnode_t;

/*链表声明*/
typedef struct list {
    /*链表大小*/
    size_t list_size;

    /*保存节点大小*/
    int node_size;

    /*保存头节点*/
    pnode_t phead;

    /*保存尾节点*/
    pnode_t ptail;
}list_t, *plist_t;

#define _get_pnode(__PVOID)\
    ((plist_t)__PVOID)->phead

#define _get_first_pnode(__PVOID)\
    _get_pnode(__PVOID)->pnext

void *init_list(const unsigned char data_size)
{
    plist_t new_list = NULL;
    do
    {
        new_list = (plist_t)malloc(sizeof(list_t));
        if (!new_list)
        {
            fprintf(stderr, "%s:%d:failed to malloc new_list", __FUNCTION__, __LINE__);
            break;
        }
        memset(new_list,0x00,sizeof(list_t));
        new_list->node_size = data_size;
        new_list->list_size = 0;
        new_list->phead = (pnode_t)malloc(sizeof(node_t));
        memset(new_list->phead, 0x00, sizeof(node_t));
        new_list->phead->length = 0;
        new_list->phead->pdata = NULL;
        new_list->phead->pnext = NULL;
        new_list->ptail = new_list->phead;
    }while(0);
	return (void*)new_list;
}
 
/*插入链表内部调用
 * */
static bool _insert_list(void* plist,const void* const data)
{
    bool ret = false;
    do
    {
        if (!plist || !data)
        {
            fprintf(stderr, "%s:%d plist or data is null\n", __FUNCTION__, __LINE__);
            break;
        }

        pnode_t new_node = (pnode_t)malloc(sizeof(node_t));
        if (!new_node)
        {
            fprintf(stderr, "%s:%d:failed to malloc new_node", __FUNCTION__, __LINE__);
            break;
        }

        plist_t new_plist = (plist_t)plist;
        new_node->pdata = malloc(new_plist->node_size);
        new_node->length = new_plist->node_size;
        memcpy(new_node->pdata, data, new_plist->node_size);

#if 0
        /*头节点插入*/
        pnode_t pnext = new_plist->phead;
        new_node->pnext = pnext->pnext;
        pnext->pnext = new_node;
#endif

#if 1
        /*尾节点插入*/
        pnode_t ptail = new_plist->ptail;
        //printf("new_node %p\n", new_node);
        new_node->pnext = NULL;
        ptail->pnext = new_node;
        /*记录下一个节点位置*/
        new_plist->ptail = ptail->pnext;
#endif
        new_plist->list_size++;
        ret = true;
    }while(0);
    return ret;
}

bool insert_list(void* plist,const void* const data,...)
{
    bool result = false;
    int* node_size = &((plist_t)plist)->node_size;
    if (*node_size == 0)
    {
        va_list ap;
        va_start(ap,data);
        *node_size = va_arg(ap,int);
        result = _insert_list(plist,data);
        *node_size = 0;
        va_end(ap);
    }
    else
    {
        result = _insert_list(plist,data);
    }
    return result;
}

bool delete_list(void *plist, bool(*func)(void *, void *), void *arg)
{
    bool ret = false;
    do
    {
        if (!plist || !func) {
            fprintf(stderr, "%s:%d plist or callback function is null\n", __FUNCTION__, __LINE__);
            break;
        }

        plist_t new_plist = (plist_t)plist;
        int pos = 1;
        pnode_t pnode = new_plist->phead->pnext;

        /*根据回调函数找到要删除的节点位置*/
        while (pnode)
        {
            if (func(pnode->pdata, arg))
                break;
            pos++;
            pnode = pnode->pnext;
        }

        if (!pnode)
        {
            fprintf(stderr, "%s:%d not found node\n", __FUNCTION__, __LINE__);
            break;
        }

        if (new_plist->list_size < pos || !pos)
        {
            fprintf(stderr, "%s:%d delete unsatisfied condition\n", __FUNCTION__, __LINE__);
            break;
        }
        else
        {
            pnode_t pcurrent = new_plist->phead, pdel;

            /*遍历到删除的节点的前一个节点位置*/
            for (int i = 0; i < pos - 1; i++)
                pcurrent = pcurrent->pnext;

            pdel = pcurrent->pnext;
            pcurrent->pnext = pdel->pnext;

            //printf("pdel %p,pdel->pnext %p\n",pdel, pdel->pnext);
            /*如果删除的是尾节点，则重新记录删除后的尾节点地址*/
            if (pos == new_plist->list_size)
                new_plist->ptail = pcurrent;

            free(pdel->pdata);
            pdel->pdata = NULL;
            free(pdel);
            pdel = NULL;
        }
        new_plist->list_size--;
        ret = true;
    }while(0);
	return ret;
}
 
bool destroy_list(void **plist)
{
    bool ret = false;
    do
    {
        plist_t *new_plist = (plist_t *)plist;
        if (!*new_plist)
        {
            fprintf(stderr, "%s:%d plist is null\n", __FUNCTION__, __LINE__);
            break;
        }

        pnode_t pcurrent = (*new_plist)->phead, pnext;
        while (pcurrent)
        {
            pnext = pcurrent->pnext;
            free(pcurrent->pdata);
            free(pcurrent);
            pcurrent = pnext;
        }
        free(*new_plist);
        *new_plist = NULL;
        ret = true;
    }while(0);
    return ret;
}
 
bool reversion_list(void *plist)
{
    bool ret = false;
    do{
        if (!plist)
        {
            fprintf(stderr, "%s:%d plist is null\n", __FUNCTION__, __LINE__);
            break;
        }

        plist_t new_plist = (plist_t)plist;
        pnode_t pprevious, pnext, pcurrent;
        pprevious = new_plist->phead->pnext;
        pnext = new_plist->phead->pnext->pnext;
        new_plist->phead->pnext->pnext = NULL;

        while (pnext)
        {
            pcurrent = pnext->pnext;
            pnext->pnext = pprevious;
            pprevious = pnext;
            pnext = pcurrent;
        }
        new_plist->phead->pnext = pprevious;
        ret = true;
    }while(0);
    return ret;
}
 
bool traversal_list(void *plist, bool(*call)(void *, void *), void *arg)
{
    bool ret = false,success = false;
    do{
        if (!plist || !call)
        {
            fprintf(stderr, "%s:%d plist is null\n", __FUNCTION__, __LINE__);
            break;
        }

        plist_t new_plist = (plist_t)plist;
        pnode_t pnode = new_plist->phead->pnext;
        while (pnode)
        {
            if (call(pnode->pdata, arg))
            {
                success = true;
                break;
            }
            pnode = pnode->pnext;
        }

        if (!success)
        {
            break;
        }
        ret = true;
    }while(0);
    return ret;
}
 
bool reversion_traversal_list(void *plist, bool(*call)(void *, void *), void *arg)
{
    bool ret = false,success = false;
    do{
        if (!plist || !call)
        {
            fprintf(stderr, "%s:%d plist is null\n", __FUNCTION__, __LINE__);
            break;
        }

        reversion_list(plist);
        plist_t new_plist = (plist_t)plist;
        pnode_t pnode = new_plist->phead->pnext;
        while (pnode)
        {
            if (call(pnode->pdata, arg))
            {
                success = true;
                break;
            }
            pnode = pnode->pnext;
        }
        reversion_list(plist);
        if (!success)
        {
            break;
        }
        ret = true;
    }while(0);
    return ret;
}
 
const size_t get_list_size(void *plist)
{
	return ((plist_t)plist)->list_size;
}
 
void *get_list_frist_data(void *plist)
{
	if (!plist) {
		fprintf(stderr, "%s:%d plist is null\n", __FUNCTION__, __LINE__);
		return NULL;
	}
	pnode_t pnode = ((plist_t)plist)->phead->pnext;
	return !pnode ? (void *)NULL : (void *)pnode->pdata;
}
 
void *get_list_last_data(void *plist)
{
	if (!plist) {
		fprintf(stderr, "%s:%d plist is null\n", __FUNCTION__, __LINE__);
		return NULL;
	}
 
	pnode_t pnode = ((plist_t)plist)->phead->pnext;
 
	while (pnode) {
		if (!pnode->pnext)
			break;
		pnode = pnode->pnext;
	}
	return !pnode ? (void *)NULL : (void *)pnode->pdata;
}
 
bool write_list_to_file(void *plist, const char *pathname, const char *mode)
{
	bool ret = false,success = true;
 
	do {
		if (!plist) {
			fprintf(stderr, "%s:%d plist is null\n", __FUNCTION__, __LINE__);
			break;
		}
 
		pnode_t pnode = _get_pnode(plist)->pnext;
		if (!pnode) {
            fprintf(stderr,"%s:%d node is null\n",__FUNCTION__,__LINE__);
			break;
		}
 
		FILE *pfile = fopen(pathname, mode);
		if (!pfile) {
            fprintf(stderr,"%s:%d open file %s fail\n",__FUNCTION__,__LINE__,pathname);
			break;
		}
 
		while (pnode) {
			if (fwrite(&pnode->length, sizeof(pnode->length), 1, pfile) != 1) {
				fprintf(stderr, "%s:%d failed to list write file\n", __FUNCTION__, __LINE__);
                success = false;
				break;
			}

            if (fwrite(pnode->pdata,pnode->length,1,pfile) != 1){
				fprintf(stderr, "%s:%d failed to list write file\n", __FUNCTION__, __LINE__);
                success = false;
				break;
            }
			pnode = pnode->pnext;
		}

		fclose(pfile);
        if (!success)
        {
            break;
        }
        ret = true;
	} while (0);
	return ret;
}
 
bool read_file_to_list(void *plist, const char *pathname,const char* mode)
{
	bool ret = false;
	do {
		if (!plist) {
			fprintf(stderr, "%s:%d plist is null\n", __FUNCTION__, __LINE__);
			break;
		}
 
		FILE *pfile = fopen(pathname, mode);
		if (!pfile) {
            fprintf(stderr,"%s:%d open %s fail\n",__FUNCTION__,__LINE__,pathname);
			break;
		}

        char data[BUFSIZ] = {};
        unsigned char node_data_len = 0;
		while (!feof(pfile)) {
			if (fread(&node_data_len, sizeof(node_data_len), 1, pfile) != 1){
                fprintf(stderr,"%s:%d fread fail\n",__FUNCTION__,__LINE__);
				break;
            }
            
            memset(data,0x00,sizeof(data));
            if (fread(data,node_data_len,1,pfile) != 1){
                fprintf(stderr,"%s:%d fread fail\n",__FUNCTION__,__LINE__);
                break;
            }
			insert_list(plist, data,node_data_len);
		}
		fclose(pfile);
        ret = true;
	} while (0);
	return ret;
}

const int find_list_data(void* plist,const void* const data)
{
    int index = -1,current_index = 0;
    do{
        if (!plist || !data)
        {
            break;
        }

        pnode_t pnode = _get_pnode(plist)->pnext;
        while(pnode)
        {
            if (!memcmp(pnode->pdata,data,((plist_t)plist)->node_size))
            {
                index = current_index;
                break;
            }
            current_index++;
            pnode = pnode->pnext;
        }
    }while(0);
    return index;
}

void* at_list(void* plist,const size_t index)
{
    size_t i = 0;
    void* pdata = NULL;
    do{
        if (!plist)
        {
            break;
        }

        pnode_t pnode = _get_first_pnode(plist);
        while(pnode)
        {
            if (i == index)
            {
                pdata = pnode->pdata;
                break;
            }
            else if (i > index)
            {
                break;
            }
            i++;
            pnode = pnode->pnext;
        }
    }while(false);
    return pdata;
}

void set_list_data_size(void* plist,const int size)
{
    ((plist_t)plist)->node_size = size;
}

const int get_list_data_size(void* plist)
{
    return ((plist_t)plist)->node_size;
}
