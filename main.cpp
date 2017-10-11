#include<bits/stdc++.h>
using namespace std;

typedef   set<array<int,2>> tile;
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

tile find_tile(tile &node, int x, int y, int prevC)
{
    cout<<x<<" "<<y<<"\n";

    if (x < 0 || x >= size || y < 0 || y >= size)return node;
    if (a[x][y]!=prevC)return node;

    bool b=node.find({x,y})!=node.end();
    if(b==true)return node;

    node.insert({x,y});
    find_tile(node,x+1,y,prevC);
    find_tile(node,x,y+1,prevC);
    find_tile(node,x-1,y,prevC);
    find_tile(node,x,y-1,prevC);


    return node;
}

int main()
{
    //cout<<"asd";
    size=6;
    create_table(size);

    print_table(size);
    tile node;

    find_tile(node,4,0,a[4][0]);
    for(tile ::iterator i=node.begin();i!=node.end();i++)
    {
        cout<<"x= "<<(*i)[0]<<" y="<<(*i)[1]<<"\n";
    }


}
