#include <iostream>

using namespace std;

#define INF 9999
#define VISITED 1
#define NOT_VISITED 0

class Router
{
    int **graph;
    int *dist;
    int *set;
    int numOfNodes;
    void dijkstra(int src);
    int emptySet();
    int lowestDistInSet();
  public:
    Router();
    ~Router();
    void getRoute(int src, int dst);
};

int main()
{
    Router router;
    router.getRoute(1,4);
}

Router::Router()
{
    cout << "Enter number of nodes: ";
    cin >> numOfNodes;
    graph = new int *[numOfNodes];
    cout << "Enter weighted graph G" << endl;
    for (int i = 0; i < numOfNodes; i++)
    {
        graph[i] = new int[numOfNodes];
        cout << "Enter row number " << i + 1 << " : ";
        for (int j = 0; j < numOfNodes; j++)
            cin >> graph[i][j];
    }
    dist = new int[numOfNodes];
    set = new int[numOfNodes];
}

Router::~Router()
{
    for(int i=0;i<numOfNodes;i++)
    {
        delete[] graph[i];
    }
    delete[] graph;
    delete[] set;
    delete[] dist;
}

void Router::dijkstra(int src)
{
    int current,lowest;
    for(int i=0;i<numOfNodes;i++)
    {
        dist[i] = INF;
        set[i] = NOT_VISITED; 
    }
    dist[src] = 0;
    while(!emptySet())
    {
        current = lowestDistInSet();
        set[current] = VISITED;
        for(int i=0;i<numOfNodes;i++)
        {
            if(set[i]!=VISITED&&graph[current][i]>=0)
            {
                if(dist[i] > dist[current]+graph[current][i])
                {
                    dist[i] = dist[current]+graph[current][i];
                }
            }
        }
    }
}

void Router::getRoute(int src,int dst)
{
    dijkstra(src);
    cout<<"dist from src to dst is: "<<dist[dst]<<endl;
}

int Router::emptySet()
{
    for(int i=0;i<numOfNodes;i++)
    {
        if(set[i]==NOT_VISITED)
        {
            return 0;
        }
    }
    return 1;
}

int Router::lowestDistInSet()
{
    int current=INF,currentIndex=0;
    for(int i=0;i<numOfNodes;i++)
    {
        if(set[i]==NOT_VISITED&&dist[i]<current)
        {
            current = dist[i];
            currentIndex = i;
        }
    }
    return currentIndex;
}