#include<bits/stdc++.h>
using namespace std;
#define INFINITY 99999

typedef   set<array<int,2>> region;
typedef set<region> List;
typedef vector<vector<int>> Grid;

struct Node
{
    region r;
    Grid grid;
    int gx;
    double fx;
};



bool operator<(const Node& a, const Node& b)
{
    return a.fx>b.fx;
}

typedef map<region,set<Node>> AdjList;
priority_queue<Node>opened_set;
set<Node> closed_set;
set<Node>open;


AdjList adj;
List nodeList;
int **a;
int size;
map<Grid,Grid> came_from;





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
region find_tile(region &node, Grid a, int x, int y, int prevC)
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

    find_tile(node,a,x+1,y,prevC);
    find_tile(node,a,x,y+1,prevC);
    find_tile(node,a,x-1,y,prevC);
    find_tile(node,a,x,y-1,prevC);



    return node;
}

void find_adjacent(region node)
{
    Node xa;
    xa.r=node;
    xa.gx=INFINITY;
    xa.fx=INFINITY;

    vector<vector<int>>v;
    for(int i=0;i<size;i++)
    {
        v.push_back(vector<int>(a[i],a[i]+size));
    }
    xa.grid=v;

    for(region ::iterator i=node.begin();i!=node.end();i++)

    {
        int x=(*i)[0];
        int y=(*i)[1];

        for(List::iterator j=nodeList.begin();j!=nodeList.end();j++)
        {
            region r=*j;
            if(node==r)continue;
            Node b;
            b.gx=INFINITY;
            b.fx=INFINITY;
            b.r=r;
            b.grid=v;


            region::iterator itr=r.find({x+1,y});

            if(itr!=r.end())
            {
                adj[node].insert(b);
                adj[r].insert(xa);
            }

            itr=r.find({x,y+1});

            if(itr!=r.end())
            {
                adj[node].insert(b);
                adj[r].insert(xa);
            }

            itr=r.find({x-1,y});

            if(itr!=r.end())
            {
                adj[node].insert(b);
                adj[r].insert(xa);
            }

            itr=r.find({x,y-1});

            if(itr!=r.end())
            {
                adj[node].insert(b);
                adj[r].insert(xa);
            }
        }

    }

}

double heuristic(region node)
{
    int s=0;
    for(region ::iterator i=node.begin();i!=node.end();i++)

    {
        int x=(*i)[0];
        int y=(*i)[1];
        s+=size-1-x+size-1-y;
    }
    return s/node.size();
}

void color_region(region &node,Grid &grid, int newC)

{

    for(region ::iterator i=node.begin();i!=node.end();i++)

    {
        int x=(*i)[0];
        int y=(*i)[1];
        grid[x][y]=newC;
    }

}

void a_star()
{

    vector<vector<int>>v;
    for(int i=0;i<size;i++)
    {
        v.push_back(vector<int>(a[i],a[i]+size));
    }

    region r;
    r=find_tile(r,v,0,0,a[0][0]);
    Node start;
    start.r=r;
    start.gx=0;
    start.fx=heuristic(r);
    start.grid=v;


    opened_set.push(start);
    open.insert(start);

    while (opened_set.size()!=0) {

        Node current=opened_set.top();


        region x;
        x=find_tile(x,current.grid,0,0,a[0][0]);
        if(x.size()==size*size)break;

        set<Node>::iterator i=open.find(current);
        open.erase(i);
        opened_set.pop();
        closed_set.insert(current);

        
        region r=current.r;
        set<Node> nbrs=adj[r];
        for(set<Node>::iterator i=nbrs.begin();i!=nbrs.end();i++)
        {
            Node nb=*i;
            if(closed_set.find(nb)!=closed_set.end())continue;



            int newg=current.gx+1;
            if(newg>=nb.gx)continue;
            nb.gx=newg;
            nb.fx=nb.gx+heuristic(nb.r);
            region::iterator p=nb.r.begin();
            int x=(*p)[0];
            int y=(*p)[1];
            int col=a[x][y];
            region t;
            t=find_tile(t,nb.grid,0,0,nb.grid[0][0]);
            color_region(t,nb.grid,col);

            came_from[nb.grid]=current.grid;

            if(open.find(nb)==open.end())
            {
                opened_set.push(nb);
                open.insert(nb);
            }
            
        }
        

    }

}



int main()
{
    //cout<<"asd";
    size=14;
    int move=0;
    create_table(size);
    vector<vector<int>>v;
    for(int i=0;i<size;i++)
    {
        v.push_back(vector<int>(a[i],a[i]+size));
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
            find_tile(current_node,v,i,j,a[i][j]);
            nodeList.insert(current_node);
        }
    }

    for(List::iterator i=nodeList.begin();i!=nodeList.end();i++)
    {
        region r=*i;
        find_adjacent(r);
//        for(region::iterator j=r.begin();j!=r.end();j++)
//        {
//            cout<<"x= "<<(*j)[0]<<" y="<<(*j)[1]<<" "<<copy[(*j)[0]][(*j)[1]]<<"\n";
//        }cout<<"\n\n";
    }
    a_star();
    cout<<nodeList.size()<<"\n\n";

    for(AdjList::iterator i=adj.begin();i!=adj.end();i++)
    {
        region r=i->first;
        for(region::iterator j=r.begin();j!=r.end();j++)
        {
            cout<<"x= "<<(*j)[0]<<" y="<<(*j)[1]<<" "<<a[(*j)[0]][(*j)[1]]<<"\n";
        }cout<<"\n\nAdjacent\n";



    }








//    List ls=i->second;

//    for(List::iterator k=ls.begin();k!=ls.end();k++)
//    {
//        region r=*k;
//        for(region::iterator j=r.begin();j!=r.end();j++)
//        {
//            cout<<"x= "<<(*j)[0]<<" y="<<(*j)[1]<<" "<<a[(*j)[0]][(*j)[1]]<<"\n";
//        }
//    }cout<<"end\n";










//    for(region::iterator j=current_node.begin();j!=current_node.end();j++)
//                {
//                    cout<<"x= "<<(*j)[0]<<" y="<<(*j)[1]<<"\n";
//                }


//    for(int i=0; i<size; i++)
//        {
//            for(int j=0; j<size; j++)
//            {
//                cout<<a[i][j]<<" ";
//            }
//            cout<<"\n";
//        }



}



//void color_region(region &node, int newC)

//{
//    for(region ::iterator i=node.begin();i!=node.end();i++)

//    {
//        int x=(*i)[0];
//        int y=(*i)[1];
//        a[x][y]=newC;
//    }

//}











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
