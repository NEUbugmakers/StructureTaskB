//
// Created by charol on 2020/12/31.
//

#ifndef STRUCTURETASKB_HEAD_H
#define STRUCTURETASKB_HEAD_H

#pragma once
#ifndef HUNGARIAN_H
#define HUNGARIAN_H
#include "main.h"
class Hungarian :public AdjMatrix{
public:
    Hungarian(AdjMatrix Adj):AdjMatrix(Adj){}
    bool find(int i);
    int getMaxLength();
    void init_isUsed(){memset(IsUsed,0,sizeof(IsUsed));}

public:
    bool search_P();//寻找未匹配的点
    bool match_(int u);//匹配DFS
    int MaxMatch();//HK算法，输出最大匹配数
    void print_adj();//输出到显示结构体
private:
    int MaxLength;
    bool IsUsed[MAX];

private:
    int Mx[MAX],My[MAX];
    int dx[MAX],dy[MAX],dis;
};

bool Hungarian::search_P() {
    queue<int>Q;
    dis=INF;
    memset(dx,-1,sizeof(dx));
    memset(dy,-1,sizeof(dy));
    for(int i=0;i<getnTeacher();i++)
        if(Mx[i]==-1)
        {
            Q.push(i);
            dx[i]=0;
        }
    while(!Q.empty())
    {
        int u=Q.front();
        Q.pop();
        if(dx[u]>dis)  break;
        for(int v=0;v<getnCourse();v++)
            if(getMap(u,v)&&dy[v]==-1)
            {
                dy[v]=dx[u]+1;
                if(My[v]==-1)  dis=dy[v];
                else
                {
                    dx[My[v]]=dy[v]+1;
                    Q.push(My[v]);
                }
            }
    }
    return dis!=INF;
}

bool Hungarian::match_(int u) {
    for(int v=0;v<getnCourse();v++)
        if(!IsUsed[v]&&getMap(u,v)&&dy[v]==dx[u]+1)
        {
            IsUsed[v]=true;
            if(My[v]!=-1&&dy[v]==dis) continue;
            if(My[v]==-1||match_(My[v]))
            {
                My[v]=u;
                Mx[u]=v;
                return true;
            }
        }
    return false;
}
int Hungarian::MaxMatch(){
    int res=0;
    memset(Mx,-1,sizeof(Mx));
    memset(My,-1,sizeof(My));
    while(search_P())
    {
        memset(IsUsed,0,sizeof(IsUsed));
        for(int i=0;i<getnTeacher();i++)
            if(Mx[i]==-1&&match_(i))  res++;
    }
    return res;
}


void Hungarian::print_adj() {
    for (int i = 0; i <getnCourse() ; ++i) {
        if (My[i] == 0){
            continue;
        }else{
            vector<int>a;
            a.push_back(My[i]);
            setAdjNode(i,a);
        }
    }
}

#endif
#endif //STRUCTURETASKB_HEAD_H
