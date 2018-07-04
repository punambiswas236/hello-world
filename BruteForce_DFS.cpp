#include <iostream>
#include <cstdio>
#include<fstream>
#include <string>
#include<vector>
using namespace std;

#define WHITE  1
#define  GRAY  2
#define BLACK  3
#define NIL -1
#define INFINITE -1
#define INF -100000

int i=0;

class graph;
void DFS_VISIT(graph g1,int k) ;


int noVtx ,noEdge;
int time =0;

class vtx  {
    public:
        int indx;
        int colour;
        int d;
        int f;
        int pred;
        vtx *lp;

        vtx( ) {
            indx=0;
            colour =WHITE;
            pred =-1;
            d =0 ;
            f=0;
            lp=NULL;
        }
        vtx( int indx,vtx *lp){
            this->indx=indx;
            this->lp=lp;
            this->colour =WHITE;
            this->pred =-1;
            this->d =0 ;
            this->f=0;

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
//vtx  vertexSet[100];
//edge edgeSet[100];

class graph{
     public:

  vtx  vertexSet[100];
edge edgeSet[100];


    graph( )  {
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
                    //cout <<v1 <<  "  and " << v2 << " added (v1 is includedd for the first time)  "  << endl;
           }
           else {
                   vtx* cur=vertexSet[v1].lp;

                    while (cur->lp!=NULL) {  cur =cur ->lp;}
                    cur->lp=new vtx(v2,NULL);
                    //  cout <<v1 <<  "  and " << v2 << " added (v1 was already included )  "  << endl;
            }

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
        void DFS(int s) {
    int t;
    if( vertexSet[s].colour ==WHITE) {DFS_VISIT(s);}
    cout << "\n DFS started" ;
   /* for (t=1 ;t<=noVtx;t++ ) {
            if( vertexSet[t].colour ==WHITE) {
                DFS_VISIT(g1,t);
            }
    }*/
     for (t=1 ;t<=noVtx;t++ ) {
         cout << t << "     ";
        cout << "discovered at: " << vertexSet[t].d<< "    " ;
        cout << "finished at : " << vertexSet[t].f<< endl;
     }
}
void DFS_VISIT(int k) {
        cout << "\scanning  : " << k<< endl;
        time =time+1;
        vertexSet[k].d=time;
        cout << "\ n entering time is updated to  " <<  vertexSet[k].d << endl;

        vertexSet[k].colour =GRAY;
        vtx *cur;
       //  cout << " \n lp of " << k << "  is " <<  g1. vertexSet[k].lp << endl;
        for(cur  = vertexSet[k].lp; cur!=NULL   ; cur=cur->lp) {
             // cout<< "\ n inside adjacency list ";
                if(vertexSet [cur->indx].colour==WHITE ) {
                       vertexSet [cur->indx].pred=k;
                        DFS_VISIT(cur ->indx);
                }
        }

        vertexSet[k].colour =   BLACK;
       cout << "\ n" <<  vertexSet[k].indx << "visit finished  " <<endl;
        time =time+1;
        vertexSet[k].f=time;
        cout << "\n  finishing time is updated to  " << vertexSet[k].f << endl;
}

};


int main(){
    graph g;
    g.DFS(1);

}
