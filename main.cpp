#include<bits/stdc++.h>
using namespace std;

typedef   set<array<int,2>> region;
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

region find_tile(region &node,set<int>&color, int x, int y, int prevC)
{
    //cout<<x<<" "<<y<<"\n";

    if (x < 0 || x >= size || y < 0 || y >= size)return node;
    if (a[x][y]!=prevC)
    {
        color.insert(a[x][y]);
        return node;
    }

    bool b=node.find({x,y})!=node.end();
    if(b==true)return node;

    node.insert({x,y});
    find_tile(node,color,x+1,y,prevC);
    find_tile(node,color,x,y+1,prevC);
    find_tile(node,color,x-1,y,prevC);
    find_tile(node,color,x,y-1,prevC);


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
    size=4;
    int move=0;
    create_table(size);

    print_table(size);
    region node;
    set<int>color;

    find_tile(node,color,0,0,a[0][0]);

    for(region ::iterator i=node.begin();i!=node.end();i++)
    {
        cout<<"x= "<<(*i)[0]<<" y="<<(*i)[1]<<"\n";
    }
    for(set<int>::iterator i=color.begin();i!=color.end();i++)
    {
        cout<<"color "<<*i<<" ";
    }cout<<"\n";
    while (true)
    {
        if(node.size()==size*size)break;
        int input;
        cin>>input;
        if(color.find(input)==color.end())continue;
        else cout<<"Yes\n";
        color_region(node,input);
        print_table(size);
        color.clear();
        node.clear();
        find_tile(node,color,0,0,a[0][0]);


        for(set<int>::iterator i=color.begin();i!=color.end();i++)
        {
            cout<<"color "<<*i<<" ";
        }cout<<"Moves: "<<++move<<"\n";



    }



}
