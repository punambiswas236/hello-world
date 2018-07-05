#include <iostream>
#include<fstream>
#include <cstdio>
#include<vector>1

using namespace std;
#define WHITE  1
#define  GRAY  2
#define BLACK  3
#define NIL -1
#define INFINITE -1
#define INF -100000
int noVtx ,noEdge;
int i=0;

class queue {
    public:
        int q[100];
        int head,tail;
        queue() {
           // q =new int[s];
             head =0;
             tail =-1;
        }

        void enqueue(int i) {
                if (is_full()) {cout << " can not insert , queue is full" << endl; }
                else{
                    tail++;
                    q[tail] = i;
                    //cout <<  i <<" enqueed " <<endl;
                }
        }
        int dequeue() {
            if(!is_empty()) {
               //cout << "cannot return item" << endl ;
                 return  0;
                 }
            else {
                 int p=q[head];
                 head++;
             // cout <<  p <<"  dequeed  " <<endl;
                 return p;
            }
        }
        int is_empty() {
            if (tail<head)  {return 0; }// queue empty condition
            else  {return  1;}
        }
        int is_full() {
             if (tail== 100-1)  {return 1; } // queue full condition
             else  {return  0;}
        }

        ~queue() {delete []q;}
};
class vtx  {
    public:
        int indx;
        int colour;
        int pred;
        int distance;
        vtx *lp;
        vtx( ) {
            indx=0;
            colour =WHITE;
            pred=NIL;
            distance =INFINITE;
            lp=NULL;
        }
        vtx( int indx,vtx *lp){
            this->indx=indx;
            this->lp=lp;
            colour = WHITE;
            pred= NIL;
            distance = INFINITE;
        }
};
class edge  {
    public:
        int startVtx;
        int endVtx;
        int distance;
        int safetyScore;

        edge( ) {
            startVtx=-1;
            endVtx=0;
            distance= INF;
            safetyScore = INF;
        }
        edge( int start, int end, int dist, int score){
            this->startVtx=start;
            this->endVtx=end;
            this->distance=dist;
            this->safetyScore=score;
        }
       /* edge ( edge e) {
            this->startVtx=e.startVtx;
            this->endVtx=e.endVtx;
            this->distance=e.distance;
            this->safetyScore=e.safetyScore;
        }*/
};
class path  {
    public:
        //vector<int> pathvertices;
        vector<int> pathvertices;
        int distance;
        int safetyScore;

        path( ) {
            vector<int> pathvertices;
            distance= 0;
            safetyScore = -1;
            //cout << "path  \n";
        }
       //path(vector<int> vertices , int d, int s){
       path(int d, int s){
           // this->pathvertices=vertices;
            this->distance=d;
            this->safetyScore=s;
             cout << "path2  \n";
       }
       void addToPath(int c){
            pathvertices.push_back(c);
     }
     void showPath(){
           for(int k=0 ; k <pathvertices.size();k++ ) {cout << pathvertices[k] << " .." ;}
           cout << " \n" ;
     }
};
class graph{
     public:
     vtx  vertexSet[100];
     edge edgeSet[100];
    graph( )  {
      //cout<<"--------ENTER NUMBER OF VERTICES AND EDGES,AND THEN THE EDGES-----------   " <<endl;
     // scanf("%d%d ",&noVtx, &noEdge);
       ifstream myReadFile;
       myReadFile.open("input.txt");
       char output[100];
       if (myReadFile.is_open()) {
            myReadFile >> noVtx;
            cout << " no of vertices " << noVtx  << "\n";
            for (int i= 1;i<=noVtx;i++){ addVertex(i) ; }
            int v1, v2, d, s;
            //while (!myReadFile.eof()) {
            while (myReadFile >> v1 >> v2 >> d >> s) {
                  // myReadFile >> output;
                  //cout<< v1 << " connects to " << v2 << " with distance " << d << " and safety score " << s   <<  "\n";
                  addEdge(v1,v2, d, s);
            }
        }
                  myReadFile.close();
      }
    void addVertex(int vIndx) { vertexSet  [vIndx] .indx= vIndx ;  }
    void addEdge(int v1,int v2, int d, int s){
            //edgeSet[i] = new edge(v1, v2, d, s);
            edgeSet[i].startVtx=v1;
            edgeSet[i].endVtx=v2;
            edgeSet[i].distance=d;
            edgeSet[i].safetyScore=s;
            i++;

           if (  vertexSet[v1].lp ==NULL)  {
                    vertexSet[v1].lp = new vtx ( v2,NULL );
           }
           else {
                   vtx* cur=vertexSet[v1].lp;
                    while (cur->lp!=NULL) {  cur =cur ->lp;}
                    cur->lp=new vtx(v2,NULL);
            }

       // following code snippet is  for undirected graph only
        /*if (  vertexSet[v2].lp ==NULL)  {
                    vertexSet[v2].lp = new vtx ( v1,NULL );
           }
        else {
                  vtx *cur1 = vertexSet[v2].lp;
                  while (cur1->lp!=NULL) {  cur1=cur1->lp;}
                    cur1->lp=new vtx(v1,NULL);
            }*/
        }
       int getDistance(int v1, int v2) {
             for (int j=0; j<i; j++){
                if (edgeSet[j].startVtx == v1 and edgeSet[j].endVtx == v2 ) {
                        //cout <<"Distance between "  << v1 << " and " << v2 << " is "  << edgeSet[j].distance << " \n";
                        return edgeSet[j].distance;
                }
             }
             return -1;
        }
};
void printPath(graph G, int s, int d){
     // if (d==s) {cout <<s << " ** ";}
       if (G. vertexSet[d].pred==NIL) { cout << " no path from " << s << " to " << d << "exists \n" ;}
      else {
            printPath(G, s, G. vertexSet[d].pred );
            }
      cout << d << "_ _  ";
}
void BFS (graph g1, int s, int d){
     g1.vertexSet[s].colour =GRAY   ;
     g1.vertexSet[s].distance=0;
     g1.vertexSet[s].pred=NIL;

     queue Q ;//now  queue is empty
     Q.enqueue(s);
     int f= 0;
     while(Q.is_empty() and f==0) {
     int m =Q.dequeue();
       // cout << m <<" is dequeued " << "\n";
        vtx *cur;
        cur  = g1. vertexSet[m].lp;
        for(cur  = g1. vertexSet[m].lp; cur!=NULL and f==0 ; cur=cur->lp){
            if (  g1. vertexSet[cur->indx] .colour ==WHITE ) {
                   g1. vertexSet[cur->indx].colour= GRAY   ;
                   g1. vertexSet[cur->indx].distance= g1. vertexSet[m].distance + g1.getDistance(m,cur->indx);
                  // cout << "*************** /n";
                  // cout << " curent edge is from " << m << " to " << cur->indx << "\n" ;
                   //cout <<" distance of "  << cur ->indx << " from " << s  << "   is : " << g1. vertexSet[cur->indx].distance <<endl ;
                     g1. vertexSet[cur->indx].pred=m;
                      Q.enqueue(cur->indx);
                     // if(cur->indx==d ) {f=1;}
            }
        }
    g1. vertexSet[m].colour=BLACK  ;
    }
  if(g1. vertexSet[d].distance ==INFINITE) { cout << d << " is not reachable from " << s << "\n";}
  else { cout <<" distance of "  << d << " from " << s  << "   is : " << g1. vertexSet[d].distance <<endl ;}

   printPath(g1,  s,  d);
}

int main()
{
   graph g;
   int source, dest;

   cout << "enter the source " <<endl;
   cin >> source;
   cout << "enter the destination " <<endl;
   cin >> dest;
   BFS(g,source, dest);

   /* path c(1,2) ;
    cout << "dist is " << c.distance << " , score is " << c.safetyScore;
    c.addToPath(1);
    c.addToPath(1);
    c.addToPath(1);
    c.addToPath(1);
    c.showPath();*/


   /*vector <int> g1;

    for (int i = 1; i <= 5; i++)
        g1.push_back(i);

    cout << "Size : " << g1.size();
    cout << "\nCapacity : " << g1.capacity();
    cout << "\nMax_Size : " << g1.max_size();*/
}

