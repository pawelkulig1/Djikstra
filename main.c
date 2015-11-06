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
double dist_between_nodes(int n1, int n2, struct nodes *r_n);
int get_closest_node(struct con *r_c, struct nodes *r_n, int nnum, double *nDone, double *Done);
int find(double *tab, double val);
void print_tab_vert(double *tab);
void print_tab_hori(double *tab);

int main()
{


    struct nodes node[6];
    struct con conn[6*5];
    init_con(conn); //set every element to -1
    get_data_from_file(node, conn);
    //printf("%f", dist(-4,4,-5,5));
    //printf("%f", node[1].x);

    double distance[6]; //distance between nodes d[]
    double node_number[6]; //number of node p[]
    double nDone[6]; //nodes not calculated Q
    double Done[6]; //nodes calculated S
    init_table(distance, node_number, nDone, Done, 6);

    int n = 5;
    //if()
    distance[0] = 0;
   // print_tab_vert(nDone);
    //print_tab_vert(Done);
    print_tab_hori(distance);
    print_tab_hori(node_number);
    int i=0;
    int temp=0;
    //while(1)
    {
        temp = get_closest_node(conn, node, i, nDone, Done);
        distance[temp]=dist_between_nodes(i, temp, node);
        temp = get_closest_node(conn, node, i, nDone, Done);
        distance[temp]=dist_between_nodes(i, temp, node);
        temp = get_closest_node(conn, node, i, nDone, Done);
        distance[temp]=dist_between_nodes(i, temp, node);
        //if(temp==-1)
        //{
        //    break;
        //}


        //i++;
    }
    print_tab_vert(nDone);
    print_tab_vert(Done);
    print_tab_hori(distance);
    print_tab_hori(node_number);
    //node_number[0]
    //distance[1] = get_closest_node(conn, node, 1, nDone, Done);


    //printf("return : %i\n", get_closest_node(conn, node, n, nDone, Done));
   // printf("return : %i\n", get_closest_node(conn, node, n, nDone, Done));
   // printf("return : %i\n", get_closest_node(conn, node, n, nDone, Done));
    //printf("return : %i\n", get_closest_node(conn, node, n, nDone, Done));
   // printf("return : %i\n", get_closest_node(conn, node, n, nDone, Done));
    //printf("return : %i\n", get_closest_node(conn, node, n, nDone, Done));

    //printf("%i",  find(nDone, 7));



    return 0;
}

int get_closest_node(struct con *r_c, struct nodes *r_n, int nnum, double *nDone, double *Done) //working
{
    if(nDone[nnum]==nnum) //closest to me is me
    {
        nDone[nnum] = -1;
        Done[find(Done, -1)] = nnum;
        return nnum;
    }

    double closest = 100000; //should be bigger than longest possible distance between 2 nodes
    int closest_node = -1;
    int i=0;
    double temp = 0;

    while(1)
    {
        temp = dist_between_nodes(nnum, get_connection(nnum, i, r_c), r_n); //distance between nodes(nnum and that one on the and of i connection)

        if(temp == -1) //every connection checked - closest chosen
        {
            nDone[closest_node] = -1;
            Done[find(Done, -1)] = closest_node;
            return closest_node;
        }

        if(temp<closest)
        {
            if(find(nDone, get_connection(nnum,i, r_c))!=-1) //get_connection convert number of connection too number of node, i is connection number
            {
                closest_node = get_connection(nnum,i, r_c);
                closest = temp;
            }
        }

        i++;
    }
    return -1;

}

void print_tab_vert(double *tab)
{
    printf("----------------------------\n");
    int i=0;
    for(i; i<6;i++)
    {
        printf("tab[%d]: %f \n",i, tab[i]);
    }
    printf("----------------------------\n");
}

void print_tab_hori(double *tab)
{
    printf("----------------------------\n");
    int i;
    for(i=0; i<6;i++)
    {
        printf("%8.3f | ", tab[i]);
    }
    printf("\n");
    printf("----------------------------\n");
}


double dist_between_nodes(int n1, int n2, struct nodes *r_n)
{
    if(n1 == -1 || n2 == -1) return -1;
    return (dist(r_n[n1].x, r_n[n1].y, r_n[n2].x, r_n[n2].y));
}

int get_connection(int node_number, int con_number, struct con *r_con)
{
    int i=0;
    int c=0;
    for(i;i<6*(6-1);i++)
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

int find(double *tab, double val)
{
    int i=0;
    for(i;i<6;i++)
    {
        if(tab[i] == val) return i;
    }
    return -1;
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
