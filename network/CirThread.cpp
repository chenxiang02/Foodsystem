#include "CirThread.h"
#include "core/food.h"


namespace EventFunction {

    #define SQL_Find_Protocol_Begin 10101111 //默认定义协议头

    #define SQL_Find_Protocol_End 01011111 //默认定义协议尾

    #define SQL_Find_Menu 10000010 //sql菜单语句查询

    //未采用原始套接字 暂不使用此结构体 后续优化可以考虑自定义网络协议
    typedef struct NetFood//传输格式
    {
       char protocol[9];
       char data[2048];//块拼接
       char protocol_end[9];
    }FoodMenuNetStruct;

    void DefineNetFood(FoodMenuNetStruct * arg1,int RetRight=0)//初始化传输信息结构体
    {
        strcpy(arg1->protocol,"10101111");

        memset(arg1->data,0,2048);

        strcpy(arg1->protocol_end,"01011111");
    }

    QByteArray DefineSend(QString date,int RetRight=0)//初始化传输信息
    {
        QString sendDate = "10101111" + date;
        if(RetRight == 1)//sql菜单查询
            sendDate.append("|10000010|");
        sendDate.append("01011111");
        return sendDate.toUtf8();
    }

    QString returnMenu()//时间为O(n*n)
    {
        Food findMenu;
        QMap<int,QStringList>arg =findMenu.FindData(2,QStringList("null"));
        QMap<int,QStringList>::iterator it;
        QString date;
        QStringList receiveDate;
        int i;

        for(it = arg.begin();it != arg.end();it++)
        {
            receiveDate = it.value();
            for(i = 0;i<receiveDate.size();i++)
            {
                date +=receiveDate.at(i);
                if(i!=receiveDate.size()-1)//后期拆包需要
                    date =date + QString("|");//表示一行数据中某列结束
                else
                    date = date + QString("/");//表示整个数据中某行结束
            }
        }
        return date;
    }

    int ReturnCurrentIndex(QMap<int,QTcpSocket*>& arg1,QTcpSocket * arg2)
    {
        QMap<int,QTcpSocket *>::iterator it;
        for(it = arg1.begin();it != arg1.end();it++)
        {
            if(arg1[it.key()] == arg2)
                return it.key();//返回当前socket索引

        }
    }
}


CirThread::CirThread()
{
     this->serve = new TcpServe(this);
     this->serve->listen(QHostAddress("127.0.0.1"),6666);
     this->storage = new SourceQueue;//构建消息队列
     qDebug()<<Q_FUNC_INFO<<"CirThread类构造";
}

CirThread::~CirThread()
{
    this->serve->close();
    qDebug()<<Q_FUNC_INFO<<"CirThread类析构";
}

void CirThread::dataReceive(QTcpSocket *socket, QString Data)
{
    if(Data.contains("MenuList"))
    {
        Data.remove(Data.length() - 8,8);
        qDebug()<<"----"<<Data;
        this->storage->sendMsg(Data);
    }
}

void CirThread::run()
{
    connect(this->serve,&TcpServe::SQLfind,this,&CirThread::sqlFind);
    connect(this->serve,&TcpServe::ReceiveDate,this,&CirThread::dataReceive);
}


void CirThread::sqlFind(QTcpSocket * socket,QString Data)
{
   if(Data.contains("menuList"))
    {
       QString date = EventFunction::returnMenu();//接收查询返回值
       socket->write(EventFunction::DefineSend(date,1));//返回需要的查询结构
   }
}
