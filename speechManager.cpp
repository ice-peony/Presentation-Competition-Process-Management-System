#include "speechManager.h"

//���캯��
SpeechManager::SpeechManager()
{
    //����  ��ʼ������������
    this->initSpeech();

    //���� ����ѡ��
    this->createSpeaker();

    //��ȡ��¼
    this->loadRecord();
}

//�˵�����
void SpeechManager::show_Menu()
{
    cout << "********************************" << endl;
    cout << "******** ��ӭ�μ��ݽ����� ******" << endl;
    cout << "********* 1.��ʼ�ݽ����� *******" << endl;
    cout << "********* 2.�鿴�����¼ *******" << endl;
    cout << "********* 3.��ձ�����¼ *******" << endl;
    cout << "********* 0.�˳��������� *******" << endl;
    cout << "********************************" << endl;
    cout << endl;
}

//�˳�����
void SpeechManager::exitSystem()
{
    cout << "��ӭ�´�ʹ��" << endl;
//    system("pause");
    exit(0);
}

//��ʼ������������
void SpeechManager::initSpeech()
{
    //�����ÿ�
    this->v1.clear();
    this->v2.clear();
    this->v_Victory.clear();
    this->m_Speaker.clear();

    //��ʼ����������
    this->m_Index = 1;

    this->m_Record.clear();
}

//��ʼ������12��ѡ��
void SpeechManager::createSpeaker()
{
    string nameSeed = "ABCDEFGHIJKL";
    for (int i=0 ; i<nameSeed.size() ; i++)
    {
        string name = "ѡ��" ;
        name += nameSeed[i];

        //��������ѡ��
        Speaker sp;
        sp.m_Name = name; //�����ָ�������
        for(int j=0 ; j<2 ; j++)  //��������ѭ�������޸��� i->j ѭ�����ڲ� [i]->[j]
        {
            sp.m_Score[j] = 0; //��ʼ��2�ֳɼ�
        }

        //12��ѡ�ֱ��
        this->v1.push_back (i + 10001);

        //ѡ�ֱ�� �Լ���Ӧ��ѡ�� ��ŵ�map��
        this->m_Speaker.insert(make_pair (i + 10001 , sp ));
    }
}

//��ʼ���� - �������̿���
void SpeechManager::startSpeech()
{
        //��һ�ֱ���
        //1.��ǩ
        this->speechDraw();

        //2.����
        this->speechContest();

        //3.��ʾ�������
        this->showScore();

        //�ڶ��ֱ���
        this->m_Index++;
        //1.��ǩ
        this->speechDraw();

        //2.����
        this->speechContest();

        //3.��ʾ���ս��
        this->showScore();

        //4.�������
        this->saveRecord();

        //���ñ���
        //����  ��ʼ������������
        this->initSpeech();

        //���� ����ѡ��
        this->createSpeaker();

        //��ȡ��¼
        this->loadRecord();

        cout << "���������ϣ�" << endl;
        system("pause");
        system("cls");
}

//��ǩ
void SpeechManager::speechDraw()
{
    cout << "��<< " << this->m_Index << " >>�ֱ���ѡ�����ڳ�ǩ " << endl;
    cout << "**************************" << endl;
    cout << "��ǩ���ݽ�˳�����£�" << endl;
    if (this->m_Index == 1)
    {
        random_shuffle(v1.begin() , v1.end());
        for(vector<int>::iterator it = v1.begin() ; it != v1.end() ; it++) //��������������ǰ��Ҫ�� ������ ::
        {
            cout << *it << " ";
        }
        cout << endl;
    }else
    {
        random_shuffle(v2.begin() , v2.end());
        for(vector<int>::iterator it = v2.begin() ; it != v2.end() ; it++)
        {
            cout << *it << " ";
        }cout << endl;
    }
    cout << "**************************" << endl;
    system("pause");
    cout << endl;
}

//����
void SpeechManager::speechContest()
{

    srand((unsigned int)time(NULL)); //�������������

    cout << "----------------�� " << this->m_Index << " �ֱ�����ʽ��ʼ��------------------" << endl;

    //׼����ʱ���������С��ɼ�
    multimap<double , int , greater<double> >groupScore; //������ʱ����������key������valѡ�ֱ��

    int num = 0; //��¼��Ա����6��Ϊ1��

    vector<int> v_Srv;  //��������Ա����
    if (this->m_Index == 1)
    {
        v_Srv = v1;
    }else
    {
        v_Srv = v2;
    }

    cout << "�� " << this->m_Index << " С�����ʱ�ĳɼ���" << endl;
    //�������в���ѡ��
    for(vector<int>::iterator it = v_Srv.begin() ; it != v_Srv.end() ; it++)
    {
        num++; //ÿ6����һ��

        //��ί���
         deque<double> d;

        for(int i=0 ; i<10 ; i++)
        {
            double score = (rand()%401+600)/10.f; //����600~100 ����������ٳ���10 �Ϳ��Եõ�С��
//            cout << score << " ";
            d.push_back(score);
        }

        sort(d.begin() , d.end() , greater<double>()); //���� ���ǵð���ͷ�ļ�
        d.pop_back();
        d.pop_front(); //����������ͷɾ��βɾ�ķ�����ȥ����ֵ

        double sum = accumulate(d.begin() , d.end() , 0.0f); //��ȡ�ܷ֡�0.0f��ʾ��ʼ�ۼ�ֵ��д��������ʾΪС�����������������㷨 ���ǵð���ͷ�ļ�
        double avg = sum/ (double)d.size();  //��ȡƽ���� ǿתΪ������֮�����

        //��ӡÿ����ƽ����
        cout << "��ţ�" <<*it << " ѡ�֣�" << this->m_Speaker[*it].m_Name << "��ȡƽ����Ϊ��" <<avg << endl;

        this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;  //�ѷ����ŵ�������

        //6����һ�飬����ʱ��������
        groupScore.insert(make_pair(avg,*it)); //key�ǵ÷֣�value�Ǿ���ѡ�ֱ��


        //ÿ6��ȡ��ǰ����
        if (num%6 ==0) //��numΪ6������ǵ�һС��
        {
            cout << "�� " << num/6 << " С��������Σ�" << endl;
            for (multimap<double,int,greater<double>>::iterator it = groupScore.begin() ; it != groupScore.end() ; it++)
            {
                cout << "��ţ�" << it->second << "\t������" << this->m_Speaker[it->second].m_Name << "\t�ɼ���"
                << this->m_Speaker[it->second].m_Score[this->m_Index-1] << endl;
            }

            int count1 = 0;//ȡǰ����
            for(multimap<double,int,greater<double>>::iterator it = groupScore.begin() ; it != groupScore.end() && count1<3; it++ , count1++)
            {
                if(this->m_Index == 1)
                {
                    v2.push_back((*it).second);
                }else
                {
                    v_Victory.push_back((*it).second);
                }
            }
            groupScore.clear();
            cout <<endl;
        }
     }
     cout << "-------------�� " << this->m_Index << " �ֱ������--------------" << endl;
}

//��ʾ�������
void SpeechManager::showScore()
{
    cout << "-------------�� " << this->m_Index << " �ֽ���ѡ����Ϣ����--------------" << endl;
    vector<int> v;
    if (this->m_Index == 1)
    {
        v = v2;
    }
    else
    {
        v = v_Victory;
    }

    for(vector<int>::iterator it = v.begin() ; it != v.end() ; it++)
    {
        cout << "ѡ�ֱ�ţ�" << *it << "\t������" << m_Speaker[*it].m_Name << "\t�ɼ���"
                << m_Speaker[*it].m_Score[this->m_Index-1] << endl;  //[*it] ��map�����У�ͨ��keyֵ���ҵ���Ӧ��valueֵ
    }
    cout << endl;
    system("pause");
    system("cls");
    this->show_Menu();
}

//�����¼
void SpeechManager::saveRecord()
{
    ofstream ofs;
    ofs.open("speech.csv",ios::out | ios::app); //��׷�ӣ�app���Ĵ򿪷�ʽ

    //��ÿ��������д�뵽�ļ���
    for(vector<int>::iterator it = v_Victory.begin() ; it != v_Victory.end() ; it++)
    {
        ofs << *it << "," << m_Speaker[*it].m_Score[1] << ",";  //[]��0�ǵ�һ�α����ĳɼ���1�ǵڶ��εĳɼ�
    } //ǰ�����ĳɼ�������
    ofs <<endl;

    ofs.close();
    cout << "��¼�Ѿ�����" << endl;

    //���˼�¼���ļ���Ϊ��
    this->fileIsEmpty = false;

    system("pause");
    system("cls");
}

//��ȡ��¼
void SpeechManager::loadRecord()
{
    ifstream ifs("speech.csv",ios::in); //����������

    if( !ifs.is_open() ) //�ļ���ʧ����
    {
        this->fileIsEmpty = true;
        cout << "�ļ������ڣ�" << endl;
        ifs.close();
        return;
    }

    //�ļ�������
    char ch;
    ifs >> ch; //��һ���ַ����ȶ�ȡһ�����������β��˵���ǿ��ļ�
    if ( ifs.eof() )
    {
        cout << "�ļ�Ϊ�գ�" << endl;
        this->fileIsEmpty = true;
        ifs.close();
        return;
    }

    //�ļ���Ϊ��
    this->fileIsEmpty = false;
    ifs.putback(ch); //��ȡ�ĵ����ַ��Ż�ȥ

    string data;
    int index = 0; //�ڼ������

    while(ifs >> data)
    {
//        cout << data << endl;
        vector<string> v; //���6��string�ַ���

        int pos = -1; //�鵽","λ�õı���
        int start = 0;

        while(true)
        {
            pos = data.find("," , start); //��0��ʼ����
            if(pos == -1 )
            {
                break;
            }
            string tmp = data.substr(start , pos - start); //�ҵ��ˣ����зָ� ����1 ��ʼλ�ã�����2  ��ȡ����
            v.push_back(tmp);
            start = pos + 1;
        }
        this->m_Record.insert(make_pair(index,v));
        index++;
    }
    ifs.close();
}

//��ʾ����÷�
void SpeechManager::showRecord()
{
    if(this->fileIsEmpty)
    {
        cout << "�ļ������ڣ����¼Ϊ�գ�" << endl;
    }else
    {
        for(int i=0; i<this->m_Record.size() ; i++)
        {
            cout << "��" << i+1 << "��" <<
            "�ھ���ţ�" << this->m_Record[i][0] << "�÷֣�" << this->m_Record[i][1] << " "
            "�Ǿ���ţ�" << this->m_Record[i][2] << "�÷֣�" << this->m_Record[i][3] << " "
            "������ţ�" << this->m_Record[i][4] << "�÷֣�" << this->m_Record[i][5] << " "
            <<endl;
        }
    }

    system("pause");
    system("cls");
}

//��ռ�¼
void SpeechManager::clearRecord()
{
    cout << "ȷ����գ�" << endl;
    cout << "1.ȷ��" << endl;
    cout << "2.����" << endl;

    int select = 0;
    cin >> select;
    if (select == 1)
    {
        //��ģʽ ios::trunc �������ɾ���ļ������´���
        ofstream ofs("speech.csv", ios::trunc);
        ofs.close();

        //��ʼ������
        this->initSpeech();

        //����ѡ��
        this->createSpeaker();

        //��ȡ�����¼
        this->loadRecord();
        cout << "��ճɹ�" << endl;
    }
    system("pause");
    system("cls");
}


//��������
SpeechManager::~SpeechManager()
{

}
