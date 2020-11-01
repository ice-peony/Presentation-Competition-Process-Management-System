#include "speechManager.h"

//构造函数
SpeechManager::SpeechManager()
{
    //调用  初始化容器和属性
    this->initSpeech();

    //调用 创建选手
    this->createSpeaker();

    //读取记录
    this->loadRecord();
}

//菜单功能
void SpeechManager::show_Menu()
{
    cout << "********************************" << endl;
    cout << "******** 欢迎参加演讲比赛 ******" << endl;
    cout << "********* 1.开始演讲比赛 *******" << endl;
    cout << "********* 2.查看往届记录 *******" << endl;
    cout << "********* 3.清空比赛记录 *******" << endl;
    cout << "********* 0.退出比赛程序 *******" << endl;
    cout << "********************************" << endl;
    cout << endl;
}

//退出功能
void SpeechManager::exitSystem()
{
    cout << "欢迎下此使用" << endl;
//    system("pause");
    exit(0);
}

//初始化容器和属性
void SpeechManager::initSpeech()
{
    //容器置空
    this->v1.clear();
    this->v2.clear();
    this->v_Victory.clear();
    this->m_Speaker.clear();

    //初始化比赛轮数
    this->m_Index = 1;

    this->m_Record.clear();
}

//初始化创建12名选手
void SpeechManager::createSpeaker()
{
    string nameSeed = "ABCDEFGHIJKL";
    for (int i=0 ; i<nameSeed.size() ; i++)
    {
        string name = "选手" ;
        name += nameSeed[i];

        //创建具体选手
        Speaker sp;
        sp.m_Name = name; //把名字赋给对象
        for(int j=0 ; j<2 ; j++)  //报错！！！循环变量修改了 i->j 循环体内部 [i]->[j]
        {
            sp.m_Score[j] = 0; //初始化2轮成绩
        }

        //12名选手编号
        this->v1.push_back (i + 10001);

        //选手编号 以及对应的选手 存放到map中
        this->m_Speaker.insert(make_pair (i + 10001 , sp ));
    }
}

//开始比赛 - 比赛流程控制
void SpeechManager::startSpeech()
{
        //第一轮比赛
        //1.抽签
        this->speechDraw();

        //2.比赛
        this->speechContest();

        //3.显示晋级结果
        this->showScore();

        //第二轮比赛
        this->m_Index++;
        //1.抽签
        this->speechDraw();

        //2.比赛
        this->speechContest();

        //3.显示最终结果
        this->showScore();

        //4.保存分数
        this->saveRecord();

        //重置比赛
        //调用  初始化容器和属性
        this->initSpeech();

        //调用 创建选手
        this->createSpeaker();

        //读取记录
        this->loadRecord();

        cout << "本剧比赛完毕！" << endl;
        system("pause");
        system("cls");
}

//抽签
void SpeechManager::speechDraw()
{
    cout << "第<< " << this->m_Index << " >>轮比赛选手正在抽签 " << endl;
    cout << "**************************" << endl;
    cout << "抽签后演讲顺序如下：" << endl;
    if (this->m_Index == 1)
    {
        random_shuffle(v1.begin() , v1.end());
        for(vector<int>::iterator it = v1.begin() ; it != v1.end() ; it++) //报错！！！迭代器前面要加 作用域 ::
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

//比赛
void SpeechManager::speechContest()
{

    srand((unsigned int)time(NULL)); //创建随机数种子

    cout << "----------------第 " << this->m_Index << " 轮比赛正式开始：------------------" << endl;

    //准备临时容器，存放小组成绩
    multimap<double , int , greater<double> >groupScore; //创建临时容器，保存key分数，val选手编号

    int num = 0; //记录人员数，6个为1组

    vector<int> v_Srv;  //比赛的人员容器
    if (this->m_Index == 1)
    {
        v_Srv = v1;
    }else
    {
        v_Srv = v2;
    }

    cout << "第 " << this->m_Index << " 小组比赛时的成绩：" << endl;
    //遍历所有参赛选手
    for(vector<int>::iterator it = v_Srv.begin() ; it != v_Srv.end() ; it++)
    {
        num++; //每6个人一组

        //评委打分
         deque<double> d;

        for(int i=0 ; i<10 ; i++)
        {
            double score = (rand()%401+600)/10.f; //创建600~100 的随机数，再除以10 就可以得到小数
//            cout << score << " ";
            d.push_back(score);
        }

        sort(d.begin() , d.end() , greater<double>()); //排序 ，记得包含头文件
        d.pop_back();
        d.pop_front(); //先排序，再用头删和尾删的方法，去掉最值

        double sum = accumulate(d.begin() , d.end() , 0.0f); //获取总分。0.0f表示起始累加值，写成这样表示为小数。常用算数生成算法 ，记得包含头文件
        double avg = sum/ (double)d.size();  //获取平均分 强转为浮点数之间相除

        //打印每个人平均分
        cout << "编号：" <<*it << " 选手：" << this->m_Speaker[*it].m_Name << "获取平均分为：" <<avg << endl;

        this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;  //把分数放到容器中

        //6个人一组，用临时容器保存
        groupScore.insert(make_pair(avg,*it)); //key是得分，value是具体选手编号


        //每6人取出前三名
        if (num%6 ==0) //当num为6，这就是第一小组
        {
            cout << "第 " << num/6 << " 小组比赛名次：" << endl;
            for (multimap<double,int,greater<double>>::iterator it = groupScore.begin() ; it != groupScore.end() ; it++)
            {
                cout << "编号：" << it->second << "\t姓名：" << this->m_Speaker[it->second].m_Name << "\t成绩："
                << this->m_Speaker[it->second].m_Score[this->m_Index-1] << endl;
            }

            int count1 = 0;//取前三名
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
     cout << "-------------第 " << this->m_Index << " 轮比赛完毕--------------" << endl;
}

//显示比赛结果
void SpeechManager::showScore()
{
    cout << "-------------第 " << this->m_Index << " 轮晋级选手信息如下--------------" << endl;
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
        cout << "选手编号：" << *it << "\t姓名：" << m_Speaker[*it].m_Name << "\t成绩："
                << m_Speaker[*it].m_Score[this->m_Index-1] << endl;  //[*it] 再map容器中，通过key值，找到对应的value值
    }
    cout << endl;
    system("pause");
    system("cls");
    this->show_Menu();
}

//保存记录
void SpeechManager::saveRecord()
{
    ofstream ofs;
    ofs.open("speech.csv",ios::out | ios::app); //用追加（app）的打开方式

    //将每个人数据写入到文件中
    for(vector<int>::iterator it = v_Victory.begin() ; it != v_Victory.end() ; it++)
    {
        ofs << *it << "," << m_Speaker[*it].m_Score[1] << ",";  //[]中0是第一次比赛的成绩，1是第二次的成绩
    } //前三名的成绩保存完
    ofs <<endl;

    ofs.close();
    cout << "记录已经保存" << endl;

    //有了记录，文件不为空
    this->fileIsEmpty = false;

    system("pause");
    system("cls");
}

//读取记录
void SpeechManager::loadRecord()
{
    ifstream ifs("speech.csv",ios::in); //输入流对象

    if( !ifs.is_open() ) //文件打开失败了
    {
        this->fileIsEmpty = true;
        cout << "文件不存在！" << endl;
        ifs.close();
        return;
    }

    //文件清空情况
    char ch;
    ifs >> ch; //用一个字符，先读取一个，如果读到尾部说明是空文件
    if ( ifs.eof() )
    {
        cout << "文件为空！" << endl;
        this->fileIsEmpty = true;
        ifs.close();
        return;
    }

    //文件不为空
    this->fileIsEmpty = false;
    ifs.putback(ch); //读取的单个字符放回去

    string data;
    int index = 0; //第几届比赛

    while(ifs >> data)
    {
//        cout << data << endl;
        vector<string> v; //存放6个string字符串

        int pos = -1; //查到","位置的变量
        int start = 0;

        while(true)
        {
            pos = data.find("," , start); //从0开始查找
            if(pos == -1 )
            {
                break;
            }
            string tmp = data.substr(start , pos - start); //找到了，进行分割 参数1 起始位置，参数2  截取长度
            v.push_back(tmp);
            start = pos + 1;
        }
        this->m_Record.insert(make_pair(index,v));
        index++;
    }
    ifs.close();
}

//显示往届得分
void SpeechManager::showRecord()
{
    if(this->fileIsEmpty)
    {
        cout << "文件不存在，或记录为空！" << endl;
    }else
    {
        for(int i=0; i<this->m_Record.size() ; i++)
        {
            cout << "第" << i+1 << "届" <<
            "冠军编号：" << this->m_Record[i][0] << "得分：" << this->m_Record[i][1] << " "
            "亚军编号：" << this->m_Record[i][2] << "得分：" << this->m_Record[i][3] << " "
            "季军编号：" << this->m_Record[i][4] << "得分：" << this->m_Record[i][5] << " "
            <<endl;
        }
    }

    system("pause");
    system("cls");
}

//清空记录
void SpeechManager::clearRecord()
{
    cout << "确认清空？" << endl;
    cout << "1.确认" << endl;
    cout << "2.返回" << endl;

    int select = 0;
    cin >> select;
    if (select == 1)
    {
        //打开模式 ios::trunc 如果存在删除文件并重新创建
        ofstream ofs("speech.csv", ios::trunc);
        ofs.close();

        //初始化属性
        this->initSpeech();

        //创建选手
        this->createSpeaker();

        //获取往届记录
        this->loadRecord();
        cout << "清空成功" << endl;
    }
    system("pause");
    system("cls");
}


//析构函数
SpeechManager::~SpeechManager()
{

}
