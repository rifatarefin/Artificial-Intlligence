#include<bits/stdc++.h>
using namespace std;

typedef   set<array<int,2>> region;
typedef set<region> List;
typedef map<region,set<region>> AdjList;



List nodeList;
int **a;
int size;

void create_table(int size)
{
    a=new int*[size];
    for(int i=0;i<size;i++)
    {
        a[i]=new int[size];
        for(int j=0;j<size;j++)
        {
            a[i][j]=rand()%6;
        }
    }

}

void print_table(int size)
{
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            cout<<a[i][j]<<" ";
        }
        cout<<"\n";
    }
}
//finds number of covered tiles
region find_tile(region &node, int x, int y, int prevC)
{
    //cout<<x<<" "<<y<<"\n";


    if (x < 0 || x >= size || y < 0 || y >= size )return node;
    if (a[x][y]!=prevC)
    {


        return node;
    }

    bool b=node.find({x,y})!=node.end();
    if(b==true)return node;

    node.insert({x,y});

    find_tile(node,x+1,y,prevC);
    find_tile(node,x,y+1,prevC);
    find_tile(node,x-1,y,prevC);
    find_tile(node,x,y-1,prevC);



    return node;
}

void color_region(region &node, int newC)

{
    for(region ::iterator i=node.begin();i!=node.end();i++)

    {
        int x=(*i)[0];
        int y=(*i)[1];
        a[x][y]=newC;
    }

}


int main()
{
    //cout<<"asd";
    size=5;
    int move=0;
    create_table(size);
    int copy[size][size];
    for(int i=0;i<size;i++)
    {
         memcpy(copy[i],a[i],size*sizeof(a[0][0]));
    }



    print_table(size);
    region current_node;
    //neighbor colors of current node
    set<int>color;

    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            current_node.clear();
            find_tile(current_node,i,j,a[i][j]);
            nodeList.insert(current_node);
        }
    }

    for(List::iterator i=nodeList.begin();i!=nodeList.end();i++)
    {
        region r=*i;
        for(region::iterator j=r.begin();j!=r.end();j++)
        {
            cout<<"x= "<<(*j)[0]<<" y="<<(*j)[1]<<" "<<copy[(*j)[0]][(*j)[1]]<<"\n";
        }cout<<"\n\n";
    }
    cout<<nodeList.size()<<"\n";


//    for(region::iterator j=current_node.begin();j!=current_node.end();j++)
//                {
//                    cout<<"x= "<<(*j)[0]<<" y="<<(*j)[1]<<"\n";
//                }


    for(int i=0; i<size; i++)
        {
            for(int j=0; j<size; j++)
            {
                cout<<a[i][j]<<" ";
            }
            cout<<"\n";
        }



}















//    for(List ::iterator i=AdjList.begin();i!=AdjList.end();i++ )
//    {
//        region a=i->first;
//        for(region::iterator i=a.begin();i!=a.end();i++)
//        {
//            cout<<"x= "<<(*i)[0]<<" y="<<(*i)[1]<<"\n";
//        }
//        cout<<"Adj\n";
//        list<region> b=i->second;
//        for(list<region>::iterator i=b.begin();i!=b.end();i++)
//        {
//            region c=*i;
//            for(region::iterator j=a.begin();j!=a.end();j++)
//            {
//                cout<<"x= "<<(*j)[0]<<" y="<<(*j)[1]<<"\n";
//            }


//        }

//    }


//for(List ::iterator i=AdjList.begin();i!=AdjList.end();i++ )
//{
//    region a=i->first;
//    for(region::iterator i=a.begin();i!=a.end();i++)
//    {
//        cout<<"x= "<<(*i)[0]<<" y="<<(*i)[1]<<" "<<copy[(*i)[0]][(*i)[1]]<<"\n";
//    }
//    cout<<"Adj\n";
//    list<region> b=i->second;
//    for(list<region>::iterator j=b.begin();j!=b.end();j++)
//    {
//        region c=*j;
//        for(region::iterator k=c.begin();k!=c.end();k++)
//        {
//            cout<<"x= "<<(*k)[0]<<" y="<<(*k)[1]<<" "<<copy[(*k)[0]][(*k)[1]]<<"\n";
//        }


//    }cout<<"end\n\n";

//}
