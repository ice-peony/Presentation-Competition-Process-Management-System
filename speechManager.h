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

//����ݽ�������
class SpeechManager
{
public:

    //���캯��
    SpeechManager();

    //�˵�����
    void show_Menu();

    //�˳�����
    void exitSystem();

    //��������
    ~SpeechManager();

    //��ʼ������������
    void initSpeech();


    //��Ա����
    //����ѡ�� ���� 12��
    vector<int> v1;

    //��һ�ֽ������� 6��
    vector<int> v2;

    //ʤ��ǰ�������� 3��
    vector<int> v_Victory;

    //��ű�� �Լ���Ӧ�ľ���ѡ������
    map<int,Speaker> m_Speaker;  //���� ���֮���� ����, ����matlab������ϰ��

    //��¼��������
    int m_Index;

    //��ʼ������12��ѡ��
    void createSpeaker();

    //��ʼ���� - �������̿���
    void startSpeech();

    //��ǩ
    void speechDraw();

    //����
    void speechContest();

    //��ʾ�������
    void showScore();

    //�����¼
    void saveRecord();

    //��ȡ��¼
    void loadRecord();

    //�ļ�Ϊ�յı�־
    bool fileIsEmpty;

    //�����¼
    map<int,vector<string>> m_Record;

    //��ʾ����÷�
    void showRecord();

    //��ռ�¼
    void clearRecord();
};



#endif // SPEECHMANAGER_H_INCLUDED
