#ifndef SPEECHMANAGER_H_INCLUDED
#define SPEECHMANAGER_H_INCLUDED

#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <ctime>
#include <functional>
#include <numeric>
#include <deque>
#include <fstream>

#include "speaker.h"

using namespace std;

//设计演讲管理类
class SpeechManager
{
public:

    //构造函数
    SpeechManager();

    //菜单功能
    void show_Menu();

    //退出功能
    void exitSystem();

    //析构函数
    ~SpeechManager();

    //初始化容器和属性
    void initSpeech();


    //成员属性
    //比赛选手 容器 12人
    vector<int> v1;

    //第一轮晋级容器 6人
    vector<int> v2;

    //胜利前三名容器 3人
    vector<int> v_Victory;

    //存放编号 以及对应的具体选手容器
    map<int,Speaker> m_Speaker;  //报错！ 间隔之间用 逗号, 不是matlab的输入习惯

    //记录比赛轮数
    int m_Index;

    //初始化创建12名选手
    void createSpeaker();

    //开始比赛 - 比赛流程控制
    void startSpeech();

    //抽签
    void speechDraw();

    //比赛
    void speechContest();

    //显示比赛结果
    void showScore();

    //保存记录
    void saveRecord();

    //读取记录
    void loadRecord();

    //文件为空的标志
    bool fileIsEmpty;

    //往届记录
    map<int,vector<string>> m_Record;

    //显示往届得分
    void showRecord();

    //清空记录
    void clearRecord();
};



#endif // SPEECHMANAGER_H_INCLUDED
