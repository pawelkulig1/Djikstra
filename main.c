//http://eduinf.waw.pl/inf/alg/001_search/0138.php

#include <stdio.h>
#include <math.h>

struct nodes
{
    double x; //x, y of node position
    double y;
};

struct con
{
    double b; //number of node where connection begins
    double e; //where it ends
};

void get_data_from_file(struct nodes *n_rcv, struct con *c_rcv);
double dist(double x1, double y1, double x2, double y2);
void init_table(double *r_dist, double *r_nnumber, double *r_nDone, double *r_Done, int s);
void init_con(struct con *r_con);
int get_connection(int node_number, int con_number, struct con *r_con);

int main()
{


    struct nodes node[6];
    struct con conn[6*5];
    init_con(conn); //set every element to -1
    get_data_from_file(node, conn);
    //printf("%f", dist(-4,4,-5,5));
    //printf("%f", node[1].x);

    double distance[6]; //distance between nodes
    double node_number[6]; //number of node
    double nDone[6]; //nodes not calculated
    double Done[6]; //nodes calculated
    init_table(distance, node_number, nDone, Done, 6);

    printf("%i", get_connection(4,2,conn)); //works!




    return 0;
}

int get_connection(int node_number, int con_number, struct con *r_con)
{
    int i=0;
    int c=0;
    for(i;i<6*(6-1);i++)
    {
        if(r_con[i].b == node_number || r_con[i].e == node_number)
        {
            //printf("%i", i);

            if(c==con_number) return i;
            c++; //we should reach this standard and leave c :)
        }
    }
    return -1;
}

void init_table(double *r_dist, double *r_nnumber, double *r_nDone, double *r_Done, int s)
{
    int i=0;
    for(i;i<s;i++)
    {
        r_dist[i] = 100000;
        r_nnumber[i] = -1;
        r_nDone[i] = i;
        r_Done[i] = -1;
    }
    r_dist[0]=0; //always 0 to itself
}

void init_con(struct con *r_con)
{
    int i=0;
    for(i; i<6*(6-1);i++)
    {
        r_con[i].b=-1;
        r_con[i].e=-1;
    }
}

double dist(double x1, double y1, double x2, double y2)
{
    return sqrt(pow(x1-x2,2) + pow(y1-y2,2));

}
void get_data_from_file(struct nodes *n_rcv, struct con *c_rcv)
{
    /*FILE *f;
    f = fopen("nodes.txt", "rt");
    while((c=fgetc(f)) != EOF) printf("%c", c);*/

    n_rcv[0].x = 0;
    n_rcv[0].y = 0;
    n_rcv[1].x = -5;
    n_rcv[1].y = 1;
    n_rcv[2].x = -1;
    n_rcv[2].y = 5;
    n_rcv[3].x = -4;
    n_rcv[3].y = 6;
    n_rcv[4].x = 1;
    n_rcv[4].y = 8;
    n_rcv[5].x = 4;
    n_rcv[5].y = 6;

    c_rcv[0].b = 0;
    c_rcv[0].e = 1;
    c_rcv[1].b = 0;
    c_rcv[1].e = 2;
    c_rcv[2].b = 0;
    c_rcv[2].e = 5;
    c_rcv[3].b = 1;
    c_rcv[3].e = 3;
    c_rcv[4].b = 1;
    c_rcv[4].e = 2;
    c_rcv[5].b = 2;
    c_rcv[5].e = 3;
    c_rcv[6].b = 2;
    c_rcv[6].e = 5;
    c_rcv[7].b = 3;
    c_rcv[7].e = 4;
    c_rcv[8].b = 4;
    c_rcv[8].e = 5;

}
