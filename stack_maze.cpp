#include <iostream>
#define SIZE 100
#define BOR 5
using namespace std;

/// footstep
typedef struct Foot
{
    int x;
    int y;
} Foot;

/// move direction
typedef struct Direction
{
    int x;
    int y;
} Direction;

/// save the footstep
typedef struct Stack
{
    Foot data[SIZE];
    int base;
    int top;
} Stack;

Direction u = {-1,0};
Direction r = {0,1};
Direction d = {1,0};
Direction l = {0,-1};


/** dir:0->up,1->right,2->down,3->left */
bool moveStep(char (*p)[BOR],int (*p2)[BOR],Foot &foot,int dir);

/** check the input is right p:map(*->wall,#->road)*/
void printMap2(int (*p)[BOR]);

/** check the map status p:map (-1->wall,0->road)*/
void printMap(char (*p)[BOR]);

/** some func about the stack */
void initStack(Stack &);
void popStack(Stack &,Foot &e);
void pushStack(Stack &,Foot e);
Foot getStackTop(Stack);
bool isStackEmpty(Stack);
void showStep(Stack S);

/** check if found the end point */
bool isFound(Foot point);


bool moveStep(char (*p)[BOR],int (*p2)[BOR],Foot &foot,int dir)
{
    int x,y;
    switch(dir)
    {
    case 0:
        x = foot.x+u.x;
        y = foot.y+u.y;
        cout<<"move up:"<<endl;
        break;
    case 1:
        x = foot.x+r.x;
        y = foot.y+r.y;
        cout<<"move right:"<<endl;
        break;
    case 2:
        x = foot.x+d.x;
        y = foot.y+d.y;
        cout<<"move down:"<<endl;
        break;
    case 3:
        x = foot.x+l.x;
        y = foot.y+l.y;
        cout<<"move left:"<<endl;
        break;
    }
    /// check the next footstep if out of map border
    if((x<0||x>=BOR)||(y<0||y>=BOR))
    {
        cout<<"log.out border"<<endl;
        return false;
    }
    /// check the next footstep is road
    if(p[x][y] == '#')
    {
        /// check the next footstep if still not walked
        if(p2[x][y] == 0)
        {
            foot.x = x;
            foot.y = y;
            return true;
        }
        else
            cout<<"("<<x<<","<<y<<") was walked."<<endl;
    }
    else
        cout<<"("<<x<<","<<y<<") not is road."<<endl;
    return false;
}


void initStack(Stack &S)
{
    S.base = 0;
    S.top = 0;
}
void pushStack(Stack &S,Foot e)
{
    S.data[S.top] = e;
    S.top++;
    cout<<"push:"<<"("<<e.x<<","<<e.y<<")."<<endl;
}
void popStack(Stack &S,Foot &e)
{
    if(isStackEmpty(S))
    {
        cout<<"stack null."<<endl;
        return;
    }
    e = S.data[--S.top];
}
Foot getStackTop(Stack S)
{
    Foot temp;
    if(isStackEmpty(S))
    {
        cout<<"stack null."<<endl;
        temp.x = -1;
        temp.y = -1;
        return temp;
    }
    int top = S.top-1;
    return S.data[top];
}
bool isStackEmpty(Stack S)
{
    if(S.base == S.top)
        return true;
    return false;
}
void showStep(Stack S)
{
    cout<<"=== path ==="<<endl;
    while(S.base<S.top){
        cout<<"("<<S.data[S.base].x<<","<<S.data[S.base].y<<")"<<endl;
        S.base++;
    }
}

bool isFound(Foot point,Foot endp)
{
    if((point.x == endp.x)&&(point.y == endp.y))
        return true;
    return false;
}

void printMap(char (*p)[BOR])
{
    cout<<"----- map ----"<<endl;
    for(int i = 0; i<BOR; i++)
    {
        for(int j = 0; j<BOR; j++)
        {
            cout<<p[i][j]<<",";
        }
        cout<<endl;
    }
}
void printMap2(int (*p)[BOR])
{
    cout<<"----- mapstatu ----"<<endl;
    for(int i = 0; i<BOR; i++)
    {
        for(int j = 0; j<BOR; j++)
        {
            cout<<p[i][j]<<",";
        }
        cout<<endl;
    }
}


int main(void)
{
    const int row = BOR;
    const int col = BOR;
    char mymap[row][col];/// map
    int mymap2[row][col];/// map status
    Stack traceStack;
    initStack(traceStack);
    bool isfound = false;

    /// * wall(statu:-1)，#road(statu:0) ,walked(statu:1)
    for(int i = 0; i<row; i++)
    {
        for(int j = 0; j<col; j++)
        {
            cin>>mymap[i][j];
            if(mymap[i][j]=='*')
                mymap2[i][j] = -1;
            else
                mymap2[i][j] = 0;
        }
    }
    printMap(mymap);
    printMap2(mymap2);
    Foot start;
    Foot endp;
    cout<<"start.x:";
    cin>>start.x;
    cout<<"start.y:";
    cin>>start.y;
    cout<<"end.x:";
    cin>>endp.x;
    cout<<"end.y:";
    cin>>endp.y;
    cout<<"start:("<<start.x<<","<<start.y<<")"<<endl;
    cout<<"end:("<<endp.x<<","<<endp.y<<")"<<endl;
    if(mymap[start.x][start.y] == '#'){
        if((start.x == endp.x)&&(start.y == endp.y))
        {
            cout<<"neednt walk...."<<endl;
            return 1;
        }
    }
    mymap2[start.x][start.y] = 1;
    pushStack(traceStack,start);
    Foot temp,origin,cant;
    while(!isStackEmpty(traceStack))
    {
        temp = getStackTop(traceStack);
        cout<<"stack top:("<<temp.x<<","<<temp.y<<")"<<endl;
        origin = temp;
        ///move up:
        while(moveStep(mymap,mymap2,temp,0))
        {
            if(isFound(temp,endp))
            {
                isfound = true;
                goto end_code;
            }
            pushStack(traceStack,temp);
            mymap2[temp.x][temp.y] = 1;
        }

        ///move right
        while(moveStep(mymap,mymap2,temp,1))
        {
            if(isFound(temp,endp))
            {
                isfound = true;
                goto end_code;
            }
            pushStack(traceStack,temp);
            mymap2[temp.x][temp.y] = 1;
        }
        ///move down
        while(moveStep(mymap,mymap2,temp,2))
        {
            if(isFound(temp,endp))
            {
                isfound = true;
                goto end_code;
            }
            pushStack(traceStack,temp);
            mymap2[temp.x][temp.y] = 1;
        }
        ///move left
        while(moveStep(mymap,mymap2,temp,3))
        {
            if(isFound(temp,endp))
            {
                isfound = true;
                goto end_code;
            }
            pushStack(traceStack,temp);
            mymap2[temp.x][temp.y] = 1;
        }
        if((temp.x == origin.x)&&(temp.y == origin.y))
        {
            popStack(traceStack,cant);
            cout<<"("<<cant.x<<","<<cant.y<<") cant walk"<<endl;
            mymap2[temp.x][temp.y] = -1;
        }
    }
end_code:
    if(isfound){
        cout<<"found"<<endl;
        showStep(traceStack);
    }
    else
        cout<<"cant found"<<endl;
    return 0;
}
