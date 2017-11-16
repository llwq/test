#include <QCoreApplication>

#include <cmath>
#include <vector>
#include <iostream>
using namespace std;

#define  min(x,y) ((x)<(y)?(x):(y))
#define  max(x,y) ((x)>(y)?(x):(y))
const static float PI=3.141592;

//点
struct point
{
    float x;
    float y;
};

//长方形
struct rectangle
{
    point cetpt;        // 中心点
    float length;       //长
    float width;        //宽
    float lux;
    float luy;
    float rux;
    float ruy;
    float ldx;
    float ldy;
    float rdx;
    float rdy;
    rectangle(float x,float y, float l,float w)
    {
       cetpt.x=x;
       cetpt.y=y;
       length=l;
       width=w;
       lux=cetpt.x - length/2;
       luy=cetpt.y + width/2;
       rux=cetpt.x + length/2;
       ruy=cetpt.y + width/2;
       ldx=cetpt.x - length/2;
       ldy=cetpt.y - width/2;
       rdx=cetpt.x + length/2;
       rdy=cetpt.y - width/2;
    }
};

//椭圆
struct  ellipse
{
    float longaxis;         //长轴
    float shortaxis;        //短轴，不用给出，由两焦点和长轴计算得出
    point fospt1;           //焦点1
    point fospt2;           //焦点2
    point cetpt;           //中心点
    float ang;              //旋转角度,统一为弧度制
    //float offsetx;          //中心点与原点X轴偏移量
    //float offsety;          //中心点与原点y轴偏移量
    ellipse(float x1, float y1, float x2, float y2, float l)
    {
        longaxis=l;
        fospt1.x=x1;
        fospt1.y=y1;
        fospt2.x=x2;
        fospt2.y=y2;
        cetpt.x=(fospt1.x+fospt2.x)/2;
        cetpt.y=(fospt1.y+fospt2.y)/2;
        shortaxis=sqrt(pow(longaxis,2) - pow(fospt2.y - fospt1.y,2) - pow(fospt2.x - fospt1.x,2));
        float a=fospt1.y-fospt2.y;
        float b=fospt1.x-fospt2.x;
        if(fabs(a)<0.000001)
        {
            ang=0.0;
        }
        else if(fabs(b)<0.000001)
        {
            ang=PI/2;
        }
        else
            ang=atan(a/b);
    }
};

//椭圆弧
struct ellipseArc
{
    point cenpt;
    point laxpt;            //长轴端点
    float staAng;           //开始角度
    float endAng;           //结束角度
    float longaxis;
    float shortaxis;
};


//求椭圆与直线的相交点,返回相交坐标点和数量
int interPoint(ellipse &elp, float x1, float y1,float x2, float y2, vector<point> &pt, int flag)
{
    int cnt=0;
    float m=elp.longaxis/2;
    float n=elp.shortaxis/2;
    float tempx1=0.0,tempx2=0.0,tempy1=0.0,tempy2=0.0;            //保存交点坐标
    if(y1==y2)
    {
        tempy1=tempy2=y1;
        tempx1=elp.cetpt.x - m*sqrt(1-pow(tempy1-elp.cetpt.y,2)/pow(n,2));
        tempx2=elp.cetpt.x + m*sqrt(1-pow(tempy2-elp.cetpt.y,2)/pow(n,2));

          //平移不可行
//        float k=0;                           //直线的斜率
//        k=(y1-y2)/(x1-x2);
//        float b=y1 - k * x1;                //直线的偏移量
//        float delta = n * n + k * k * m * m - b * b;    //判别式
//        if(delta<=0)
//        {
//            return 0;
//        }
//        else
//        {
//            tempx1= (- m * m * k * b - m * n * sqrt(delta))/(n * n + m * m * k *k) + elp.cetpt.x;     //求解出的x1
//            tempx2= (- m * m * k * b + m * n * sqrt(delta))/(n * n + m * m * k *k) + elp.cetpt.x;     //求解出的x2
//            tempy1= k * tempx1 + b;                                                     //求解出的y1
//            tempy2= k * tempx2 + b;                                                     //求解出的y2
//        }

    }
    if(x1==x2)
    {
        tempx1=tempx2=x1;
        tempy1=elp.cetpt.y - n*sqrt(1-pow(tempx1-elp.cetpt.x,2)/pow(m,2));
        tempy2=elp.cetpt.y + n*sqrt(1-pow(tempx2-elp.cetpt.x,2)/pow(m,2));
    }

    //按一定顺序插入交点
    if(flag<=1)
    {
        //判断点是否在长方形范围
        if( ((tempx1 >= x1 && tempx1 <= x2) || (tempx1 <= x1 && tempx1 >= x2)) &&
                ((tempy1 >= y1 && tempy1 <= y2) || (tempy1 <= y1 && tempy1 >= y2))  )
        {
            cnt++;                                                //交点数+1
            point pt1={tempx1,tempy1};                              //保存交点的坐标
            pt.push_back(pt1);
        }

        if( ((tempx2 >= x1 && tempx2 <= x2) || (tempx2 <= x1 && tempx2 >= x2)) &&
                ((tempy2 >= y1 && tempy2 <= y2) || (tempy2 <= y1 && tempy2 >= y2))  )
        {
            cnt++;
            point pt1={tempx2,tempy2};
            pt.push_back(pt1);
        }
    }
    else    //上边与左边需调换交点插入顺序
    {
        if( ((tempx2 >= x1 && tempx2 <= x2) || (tempx2 <= x1 && tempx2 >= x2)) &&
                ((tempy2 >= y1 && tempy2 <= y2) || (tempy2 <= y1 && tempy2 >= y2))  )
        {
            cnt++;
            point pt1={tempx2,tempy2};
            pt.push_back(pt1);
        }
        if( ((tempx1 >= x1 && tempx1 <= x2) || (tempx1 <= x1 && tempx1 >= x2)) &&
                ((tempy1 >= y1 && tempy1 <= y2) || (tempy1 <= y1 && tempy1 >= y2))  )
        {
            cnt++;
            point pt1={tempx1,tempy1};
            pt.push_back(pt1);
        }
    }
    return cnt;
}

//返回两点距离
float distance(float x1, float y1, float x2, float y2)
{
    return sqrt(pow(x1-x2,2)+ pow(y1-y2,2));
}

//判断椭圆与矩形是否相交，正方形内或边上最靠近椭圆的点在不在椭圆内，如椭圆在矩形外返回0
bool collision(ellipse elp, rectangle rec)
{

    int dx = min(elp.fospt1.x, rec.cetpt.x + rec.length * 0.5);         //x轴坐标比较
    int dx1 = max(dx, rec.cetpt.x - rec.length * 0.5);
    int dy = min(elp.fospt1.y, rec.cetpt.y + rec.width * 0.5);          //y轴坐标比较
    int dy1 = max(dy, rec.cetpt.y - rec.width * 0.5);

    int dis1= sqrt((dx1 - elp.fospt1.x) * (dx1 - elp.fospt1.x) + (dy1 - elp.fospt1.y) * (dy1 - elp.fospt1.y));  //到焦点1的距离

    dx =  min(elp.fospt2.x, rec.cetpt.x + rec.length * 0.5);
    dx1 = max(dx, rec.cetpt.x - rec.length * 0.5);
    dy = min(elp.fospt2.y, rec.cetpt.y + rec.width * 0.5);
    dy1 = max(dy, rec.cetpt.y - rec.width * 0.5);

    int dis2= sqrt((dx1 - elp.fospt2.x) * (dx1 - elp.fospt2.x) + (dy1 - elp.fospt2.y) * (dy1 - elp.fospt2.y));  //到焦点2的距离

    if(dis1+dis2 <= elp.longaxis)   //相切或相离
        return 1;
    return 0;

}

////点到直线的距离
//float ptToLine(point &pt, float x1, float y1, float x2, float y2)
//{
//    float A=0;                            //直线的斜率
//    if(x1 != x2)
//        A=(y2-y1)/(x2-x1);
//    float B=-1;
//    float C=y2 - A * x2;                  //直线的偏移量
//    float d=(float)labs((A * pt.x + B * pt.y + C)/sqrt(pow(A,2) + pow(B,2)));
//    return d;
//}


////直线与圆是否相交(适用于圆在长方形内或相交)
//void hasInter(ellipse &elp, rectangle &rec, float e[])
//{
//    e[0]=ptToLine(elp.fospt1, rec.lux, rec.luy, rec.rux, rec.ruy)
//                +  ptToLine(elp.fospt2, rec.lux, rec.luy, rec.rux, rec.ruy) - elp.longaxis;
//    e[1]=ptToLine(elp.fospt1, rec.rux, rec.ruy, rec.rdx, rec.rdy)
//            +  ptToLine(elp.fospt2, rec.rux, rec.ruy, rec.rdx, rec.rdy) - elp.longaxis;
//    e[2]=ptToLine(elp.fospt1, rec.rdx, rec.rdy, rec.ldx, rec.ldy)
//                +  ptToLine(elp.fospt2, rec.rdx, rec.rdy, rec.ldx, rec.ldy) - elp.longaxis;
//    e[3]=ptToLine(elp.fospt1, rec.lux, rec.luy, rec.ldx, rec.ldy) +
//              ptToLine(elp.fospt2, rec.lux, rec.luy, rec.ldx, rec.ldy) - elp.longaxis;
//}

//判断点是否在长方形内，满足条件返回0
bool inRectangle(float x, float y, rectangle &rec)
{
    float a= x - (rec.cetpt.x - rec.length * 0.5);
    float b= x - (rec.cetpt.x + rec.length * 0.5);
    float c= y - (rec.cetpt.y - rec.width * 0.5);
    float d= y - (rec.cetpt.y + rec.width * 0.5);
    if( a * b < 0 && c * d < 0)
        return 0;
    else
        return 1;
}

//两数交换
void swap(float &a,float &b)
{
    float temp;
    temp=a;
    a=b;
    b=temp;
}

//计算未旋转前的角度
float calAngle(float x1, float y1, ellipse elp)
{
    float x;
    float y;
    x=x1 - elp.cetpt.x;
    y=y1 - elp.cetpt.y;
    x=x * cos(elp.ang) + y * sin(elp.ang);                  //未旋转前的坐标
    y=y * cos(elp.ang) - x * sin(elp.ang);

    float b=y*elp.longaxis;
    float a=x*elp.shortaxis;
    float ang;

    if(fabs(a)<0.000001)
    {
        if(b>0)
            ang=PI/2;
        else
            ang=3*PI/2;
    }
    else if(fabs(b)<0.000001)
    {
        if(a>0)
            ang=0;
        else
            ang=PI;
    }
    else
    {
        ang=atan(b/a);
        if(x<0)                                                 //与中心点比较在第几象限
            ang+=PI;
        if(ang<0)
            ang+=2*PI;
    }
    cout<<"standard cordinate:"<<x<<" "<<y<<endl;
    return ang;
}

//先寻找vector中第一对在同一条线的点，再输出
void searchLine(vector<point> pt, int cnt, ellipse &elp)
{
    vector<point>::iterator pt_iter=pt.begin();
    float temp1x,temp1y,temp2x,temp2y;
    float from=0,to=0;
    while(pt_iter!=pt.end())
    {
        temp1x=pt_iter->x;
        temp1y=pt_iter->y;
        pt_iter++;
        temp2x=pt_iter->x;
        temp2y=pt_iter->y;
        if(temp1x==temp2x || temp2y==temp1y)
            break;
    }
    while(cnt--)
    {
        if(pt_iter==pt.end())           //怎么判断到没到末尾？
            pt_iter=pt.begin();
        from=calAngle(pt_iter->x,pt_iter->y,elp);
        pt_iter++;
        if(pt_iter==pt.end())
            pt_iter=pt.begin();
        to=calAngle(pt_iter->x,pt_iter->y,elp);
        if(to<from)
            to+=2*PI;
        //arc.staAng=from;
        //arc.endAng=to;
        cout<<from*180/PI<<", "<<to*180/PI<<endl;
        pt_iter++;
        cnt--;
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //初始化
    ellipseArc arc;
    //rectangle rec(-2,0,4,2);
    //ellipse elp(-2,0,-3,0,4);    //一段圆弧
    //rectangle rec(-2,0,4,3);
    //ellipse elp(-2,0,-3,0,4);    //两段圆弧
    //rectangle rec(0,0,8,6);
    //ellipse elp(1,1,3,1,8);     //一段圆弧
    rectangle rec(0,0,8,5);
    ellipse elp(1,0,-1,0,9);    //四段圆弧

    cout<<"center point:("<<rec.cetpt.x<<","<<rec.cetpt.y<<"), length: "<<rec.length<<", width: "<<rec.width<<endl;
    cout<<"focus point1:("<<elp.fospt1.x<<","<<elp.fospt1.y<<"), longaxis: "<<elp.longaxis<<endl;
    cout<<"focus point2:("<<elp.fospt2.x<<","<<elp.fospt2.y<<"), shortaxis: "<<elp.shortaxis<<endl;
    cout<<"rotate angle:"<<elp.ang*180/PI<<endl;
    cout<<endl;

    float d[4]={0};
    int cnt=0;                           //交点数
    vector<point> pt;                   //保存相交点坐标
    vector<point>::iterator pt_iter=pt.begin();
    //hasInter(elp,rec,d);

    //判断长方形四个顶点的位置
    d[0]=distance(rec.lux, rec.luy, elp.fospt1.x, elp.fospt1.y) +
            distance(rec.lux, rec.luy, elp.fospt2.x, elp.fospt2.y) - elp.longaxis;      //左上顶点
    d[1]=distance(rec.rux, rec.ruy, elp.fospt1.x, elp.fospt1.y) +
            distance(rec.rux, rec.ruy, elp.fospt2.x, elp.fospt2.y) - elp.longaxis;      //右上顶点
    d[2]=distance(rec.rdx, rec.rdy, elp.fospt1.x, elp.fospt1.y) +
            distance(rec.rdx, rec.rdy, elp.fospt2.x, elp.fospt2.y) - elp.longaxis;      //右下顶点
    d[3]=distance(rec.ldx, rec.ldy, elp.fospt1.x, elp.fospt1.y) +
            distance(rec.ldx, rec.ldy, elp.fospt2.x, elp.fospt2.y) - elp.longaxis;      //左下顶点

    cout<<d[0]<<" "<<d[1]<<" "<<d[2]<<" "<<d[3]<<endl;
    if(d[0]<=0 && d[0]<=0 && d[2]<=0 && d[3]<=0)
    {
        cout<<"the rectangle is in the ellipse"<<endl;                           //长方形在椭圆内
    }
    else
    {
        if(!collision(elp,rec))
            cout<<"the ellipse is outside the rectangle"<<endl;                  //椭圆在长方形外
        else
        {
            cnt+=interPoint(elp,rec.ldx,rec.ldy,rec.rdx,rec.rdy, pt, 0);  //下边
            cnt+=interPoint(elp,rec.rux,rec.ruy,rec.rdx,rec.rdy, pt, 1);  //右边
            cnt+=interPoint(elp,rec.lux,rec.luy,rec.rux,rec.ruy, pt, 2);  //上边
            cnt+=interPoint(elp,rec.ldx,rec.ldy,rec.lux,rec.luy, pt, 3);  //左边
            //hasInter(elp,rec,e);                                              //直线镜像
            vector<point>::iterator pt_temp=pt_iter++;
            if(cnt<=2 && pt_temp->x==pt_iter->x && pt_temp->y==pt_iter->y)
                cout<<"the ellipse is in the rectangle"<<endl;                   //椭圆在长方形内
            else
                cout<<"the ellipse intersects with the rectangle"<<endl;         //椭圆与长方形相交
        }
    }
    cout<<"interpoint count:"<<cnt<<endl;
    cout<<endl;

    for(pt_iter = pt.begin();pt_iter !=pt.end();pt_iter++)
    {
        cout<<"real cordinate: "<<pt_iter->x<<" "<<pt_iter->y<<endl;
        cout<<"angle:"<<calAngle(pt_iter->x,pt_iter->y,elp)*180/PI<<endl;
    }
    cout<<endl;
    pt_iter=pt.begin();
    if(2==cnt)                                                                  //只有两个点
    {
        float from=0,to=0,temp;
        from=calAngle(pt_iter->x,pt_iter->y,elp);
        pt_iter++;
        to=calAngle(pt_iter->x,pt_iter->y,elp);
        if(from==to)                                                            //排除相切的情况
        {
            arc.staAng=0;
            arc.endAng=2*PI;
        }
        else
        {
            if(to<from)
                to+=2*PI;
            temp=(from+to)/2;
            if(inRectangle(elp.cetpt.x+elp.longaxis*cos(temp)/2,elp.cetpt.y+elp.shortaxis*sin(temp)/2,rec))
                swap(from,to);
            arc.staAng=from;
            arc.endAng=to;
        }
        cout<<"cordinates: "<<pt_iter->x<<", "<<pt_iter->y<<endl;
        cout<<"start angle:"<<arc.staAng*180/PI<<", end angle:"<<arc.endAng*180/PI<<endl;
    }
    else                  //需要找到同一条线上的两点，从第二点开始
    {
        searchLine(pt,cnt,elp);
    }

    return a.exec();
}
