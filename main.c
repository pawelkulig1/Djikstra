//http://eduinf.waw.pl/inf/alg/001_search/0138.php

#include <stdio.h>
#include <math.h>
#include <windows.h>

#define INFINITY 10000
#define NNODES 6
#define EMPTYVAL -1

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

int lower_reach_cost(double *distance, double *nDone);
void get_data_from_file(struct nodes *n_rcv, struct con *c_rcv);
double dist(double x1, double y1, double x2, double y2);
void init_table(double *r_dist, double *r_nnumber, double *r_nDone, double *r_Done, int s);
void init_con(struct con *r_con);
int get_connection(int node_number, int con_number, struct con *r_con);
double dist_between_nodes(int n1, int n2, struct nodes *r_n);
int get_every_node(struct con *r_c, struct nodes *r_n, int nnum, int order);
void print_tab_vert(double *tab, int len);
void print_tab_hori(double *tab, int len);
int get_element_sorted(double *r_nDone, int n, struct nodes *n_rcv, struct con *c_rcv);
int find(double *tab, double val); //1 if exist
int get_closest_node(struct con *r_c, struct nodes *r_n, int nnum, double *nDone, double *Done); //working
void reset(double *nDone2, double *Done2);


double nDone_l=NNODES;



int main()
{
    struct nodes node[NNODES];
    struct con conn[NNODES*(NNODES-1)];
    init_con(conn); //set every element to -1
    get_data_from_file(node, conn);
    //printf("%f", dist(-4,4,-5,5));
    //printf("%f", node[1].x);
    //double nDone_l=NNODES;
    double distance[NNODES]; //distance between nodes d[]
    double node_number[NNODES]; //number of node p[]
    double nDone[NNODES]; //nodes not calculated Q
    double Done[NNODES]; //nodes calculated S
    init_table(distance, node_number, nDone, Done, NNODES);

    distance[0] = 0;
    node_number[0] = -1;
    nDone[0] = -1;
    Done[0]  =0;

    int i=0;
    int next_node=0;
    double next_dist = 0;

    double nDone2[NNODES];
    double Done2[NNODES];


    int node_checking = 0;
    next_node = 0;
    int next_node2=-1;
    double temp_dist = 0;

    reset(nDone2, Done2);


    while(1)
    {
        printf("next_node : %d \n", next_node);

        while(1)
        {
            next_node2 = get_closest_node(conn, node, next_node, nDone2, Done2);

            temp_dist = dist_between_nodes(next_node, next_node2, node);
            if(next_node2 == -1) break;
            printf("%d \n", next_node2);
            if(distance[next_node2]> temp_dist + distance[next_node])
            {
                distance[next_node2] = temp_dist + distance[next_node];
                node_number[next_node2] = next_node;
            }
        }
        reset(nDone2, Done2);

        //next_node = get_closest_node(conn, node, next_node, nDone, Done);

        if(next_node == -1)
        {
            node_checking = lower_reach_cost(distance, nDone);
            if(node_checking == -1) break;

            print_tab_vert(nDone,NNODES);
            print_tab_vert(Done,NNODES);
            print_tab_hori(distance,NNODES);
            print_tab_hori(node_number,NNODES);

            Sleep(1000);
            printf("node checking:  %d", node_checking);
            nDone[node_checking] = -1;

            //Sleep(1000);
        }
        next_node = get_closest_node(conn, node, node_checking, nDone, Done);

    }

    print_tab_vert(nDone,NNODES);
    print_tab_vert(Done,NNODES);
    print_tab_hori(distance,NNODES);
    print_tab_hori(node_number,NNODES);

    return 0;
}

int lower_reach_cost(double *distance, double *nDone)
{
    int i=0, j=-1;
    int min = INFINITY;
    for(i=0; i<NNODES; i++)
    {
        if((distance[i]< min) && (find(nDone, i)!=-1))//and not checked
        {
            min = distance[i];
            j=i;

        }
    }
    return j;
}


int get_closest_node(struct con *r_c, struct nodes *r_n, int nnum, double *nDone2, double *Done2) //working
{

    double closest = INFINITY; //should be bigger than longest possible distance between 2 nodes
    int closest_node = -1;
    int i=0;
    double temp = 0;

    while(1)
    {
        temp = dist_between_nodes(nnum, get_connection(nnum, i, r_c), r_n); //distance between nodes(nnum and that one on the and of i connection)

        if(temp == -1) //every connection checked - closest found
        {
            nDone2[closest_node] = -1;
            Done2[find(Done2, -1)] = closest_node;
            return closest_node;
        }

        if(temp<closest)
        {
            if(find(nDone2, get_connection(nnum,i, r_c))!=-1) //get_connection convert number of connection too number of node, i is connection number
            {
                closest_node = get_connection(nnum,i, r_c);
                closest = temp;
            }
        }

        i++;
    }
    return -1;
}


void reset(double *nDone2, double *Done2)
{
    int i =0;
    for(i=0;i<NNODES;i++)
    {
        nDone2[i] = i;
        Done2[i] = EMPTYVAL;
    }
    nDone2[0]=-1;
    //Done2[0]=0;
}

int find(double *tab, double val) //checking if element exists in tab
{
    int i=0;
    for(i=0;i<NNODES; i++)
    {
        if(tab[i]== val) return i;
    }
    return -1;
}


void print_tab_vert(double *tab, int len)
{
    printf("----------------------------\n");
    int i=0;
    for(i; i<len;i++)
    {
        printf("tab[%d]: %f \n",i, tab[i]);
    }
    printf("----------------------------\n");
}

void print_tab_hori(double *tab, int len)
{
    printf("----------------------------\n");
    int i;
    for(i=0; i<len;i++)
    {
        printf("%8.3f | ", tab[i]);
    }
    printf("\n");
    printf("----------------------------\n");
}

double dist_between_nodes(int n1, int n2, struct nodes *r_n)
{
    if(n1 == EMPTYVAL || n2 == EMPTYVAL) return EMPTYVAL;
    return (dist(r_n[n1].x, r_n[n1].y, r_n[n2].x, r_n[n2].y));
}

int get_connection(int node_number, int con_number, struct con *r_con) //return "con_number" connection from "node_number" node
{
    int i=0;
    int c=0;
    for(i;i<NNODES*(NNODES-1);i++)
    {
        if(r_con[i].b == node_number || r_con[i].e == node_number)
        {
            /*if(c==con_number) return i;*/
            if(c==con_number)
            {
                if(r_con[i].b == node_number) return r_con[i].e;
                else return r_con[i].b;
            }
            c++; //we should reach this standard and leave c :)
        }
    }
    return EMPTYVAL;
}

void init_table(double *r_dist, double *r_nnumber, double *r_nDone, double *r_Done, int s)
{
    int i=0;
    for(i;i<s;i++)
    {
        r_dist[i] = INFINITY;
        r_nnumber[i] = EMPTYVAL;
        r_nDone[i] = i;
        r_Done[i] = EMPTYVAL;
    }
    r_dist[0]=0; //always 0 to itself
}

void init_con(struct con *r_con)
{
    int i=0;
    for(i; i<NNODES*(NNODES-1);i++)
    {
        r_con[i].b=EMPTYVAL;
        r_con[i].e=EMPTYVAL;
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
