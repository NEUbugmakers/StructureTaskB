//
// Created by charol on 2020/12/31.
//

#ifndef STRUCTURETASKB_MAIN_H
#define STRUCTURETASKB_MAIN_H
#include <iostream>
#include <vector>
#include <queue>
#include <memory.h>

#define INF 0x3f3f3f3f
using namespace std;
#define MAX 100


//template <class T>
class AdjMatrix {
public:
    //nT为老师的数量 nC为课程的数量
    AdjMatrix(int nT = 0, int nC = 0):nTeacher(nT),nCourse(nC) {
        memset(color,0,sizeof(color));
        for (int i = 0; i < MAX; ++i) {
            memset(map[i],0,sizeof(map[i]));
        }
    }
    int getMap(int i, int j) { return map[i][j]; }
    vector<int> getAdjNode(int i) { return AdjNode[i]; }
    string getTeacher(int i) { return teacher[i]; }
    string getCourse(int i) { return course[i]; }
    int getnTeacher() { return nTeacher; }
    int getnCourse() { return nCourse; }
    void setMap(int i, int j, int n) { map[i][j] = n; }
    void setAdjNode(int i, vector<int> n) { AdjNode[i] = n; }
    void setTeacher(int i, string p) { teacher[i] = p; }
    void setCourse(int i, string p) { course[i] = p; }
    void setnTeacher(int n) { nTeacher = n; }
    void setnCourse(int n) { nCourse = n; }

    //todo:新增函数
    bool paint_dfs(int vertice,int c);
    bool CheckBgraph();
private:
    int nTeacher, nCourse;//nT为老师的数量 nC为课程的数量

    int map[MAX][MAX];//各个节点之间的权重(为0时说明未连接 为1时说明已连接)

    //保存各个节点的连接信息（适应多重匹配）
    //由于是老师数量大于课程 所以此节点为课程节点
    //统一使用此变量保存最终信息方便UI输出
    vector<int> AdjNode[MAX];
    int color[MAX];

    string teacher[MAX];
    string course[MAX];

};



bool AdjMatrix::paint_dfs(int vertice,int c){//一般为c=1
    this->color[vertice] = c;
    for (int i = 0; i < MAX; ++i) {
        if(this->map[vertice][i] == 1){
            if (this->color[i] == c){
                return false;
            }
            if(this->color[i] == 0 && !paint_dfs(i,-c)){
                return false;
            }
        }
    }
    return true;
}

bool AdjMatrix::CheckBgraph() {
    for (int i = 0; i < MAX; ++i) {
        if(color[i] == 0){
            if (!paint_dfs(i,1)){
                return true;
            }
        }
    }
}




#endif //STRUCTURETASKB_MAIN_H
