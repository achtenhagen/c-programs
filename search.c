/******************************************************************************
 CS288 HW7 three search strategies: depth, breadth, and intelligent
 command example: command 16 numbers and search strategy

 fifteen 1 2 3 4 5 6 7 8 9 10 11 12 13 14 0 15 {dfs|bfs|astar}
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BF 4            /* Branching factor of the search tree */
#define N 4
#define NxN 16
#define DFS 1           /* depth first search */
#define BFS 2           /* breadth first search */
#define BEST 3          /* best first search */
#define BB 4            /* branch and bound */
#define ASTAR 5         /* A* search */
#define UNKNOWN 9       /* unknown search strategy */

#define MAX_PATH 1000

#define DN 0            /* for finding path */
#define RT 1
#define UP 2
#define LT 3
#define UK 9

#define FVAL 0          /* f=g+h, keep it simple for now */
#define GVAL 1
#define HVAL 2
#define PATH 3          /* array index, how it got to this state */

#define TRUE 1
#define FALSE 0

int level,strategy;

int nodes_same(), str_compare(), count(), find_h();
void swap(), exit_proc(), print_a_node(), print_nodes();
int toggle_dir(), solvable();
void find_path(), print_path(), find_parent();
int path[MAX_PATH], path_buf[MAX_PATH];
void prep_dir_to_str(), dir_to_str();
char *dir_to_sdir[4], strategy_s[10]; /* four directions */

struct node {
  int board[N+1][N]; /* additional row holds f, g and h */
  struct node *next;
};

struct node *start, *goal;
struct node *initialize(), *expand(), *merge(), *filter(), *move(), *prepend(), *append();
struct node *insert_node(), *check_list(), *goal_found();

int main (int argc, char **argv) {
    int iter, cnt = 0, total = 1, ocnt = 0, ccnt = 0;
    int perm;
    struct node *cp, *open, *closed, *succ, *tp;
    open = closed = succ = NULL;
    start = initialize(argc, argv); /* init initial and goal states */
    perm = solvable(start);         /* check if solvable permutation */
    if (perm & 1) { return 1; }
    open = start;
    iter = 0;
    while (open) {
        printf("%d: open=%d + clsd=%d = total=%d\n", iter, ocnt, ccnt, ocnt + ccnt);
        ocnt = count(open);
        ccnt = count(closed);
        cp = open;
        open = open->next;
        cp->next = NULL;
        succ = expand(cp);           /* get the first node from open */
        succ = filter(succ, open);   /* Find new successors */
        succ = filter(succ, closed); /* New succ list */
        cnt = count(succ);
        total = total + cnt;
        if (succ) {
            open = merge(succ, open, strategy); /* New open list */
        }
//        closed=append(cp,closed); /* New closed */
//        if ((cp=goal_found(succ,goal))) break;
//        iter++;
    }
//  printf("%s strategy: %d iterations %d nodes\n", strategy_s, iter+1, total);
//  find_path(cp,open,closed);

  return 0;
}

// Done.
int toggle_dir(int dir) {
  int opp_dir;
  // return opp direction
  return opp_dir;
}

void print_path(int n,int *path) {
  int i,p;
  //  for (i=0;i<n;i++) path[i] = path_buf[path_cnt-i-1];
  //  for (i=0;i<path_cnt;i++) printf("%d ",path[i]); printf("\n");
  //  printf("entering print_path: n=%d\n",n);

  ////  for (i=n-1;i>=0;i--) printf("%d ",*(path+i)); printf("\n");
  for (i=n-1;i>=0;i--) {
    p = *(path+i);
    if (i>0) printf("%s -> ",dir_to_sdir[p]);
    else printf("%s",dir_to_sdir[p]);
  }
  printf("\n");
  //  printf("exiting print_path\n");
}

//char **dir_to_sdir={"DN","RT","UP","LT"}; //[4];
void prep_dir_to_str(){
  //...
}

void find_path(struct node *cp,struct node *opnp, struct node *cldp){
  int i,j,dir,opp_dir;
  char *sdir,*opp_sdir;
  int path_cnt=0,p;
  struct node *tp;
  //start from the very last node that matches the goal state because
  //that has the direction info
  //toggle the direction, get the parent
  //look for that parent in closed
  //repeat until you find the initial state
}

void find_parent(struct node *cp,int prev_dir){
  int i,j,k,cnt,row=0,col=j;
}

// Expand: generate successors of the current node
struct node *expand(struct node *cp) {
  int i,j,k,cnt,row=0,col=j;
  struct node *succ,*tp;
  succ=NULL;

  /* check where 0 is. find indices i,j */
  for(i=0; i < N; i++) {
    for(j=0; j < N; j++)
      if (cp->board[i][j]==0) break;
    if (j<N) break; /* found it */
  }

  if((i+1) < N){        /* DOWN */
    tp = move(cp,i,j,i+1,j,DN);
    succ = append(tp,succ);
  }
  if((j+1) < N){        /* RIGHT */
    tp = move(cp,i,j,i,j+1,RT);
    succ = append(tp,succ);
  }
  if((i-1) < N){        /* UP */
    tp = move(cp,i,j,i-1,j,UP);
    succ = append(tp,succ);
  }
  if((j-1) < N){        /* LEFT */
    tp = move(cp,i,j,i,j-1,LT);
    succ = append(tp, succ);
  }
  return succ;
}

/* attach in the beginning */
struct node *prepend(struct node *tp, struct node *sp) {
  //.....
  return sp;
}

/* attach at the end */
struct node *append (struct node *tp, struct node *sp) {
    struct node *cp;
    cp = sp;
    while (cp != NULL) { cp = cp->next; }
    // sp->next = tp;
    return sp;
}

// Done.
void swap (struct node *cp, int i, int j, int k, int l) {
    int tmp = cp->board[i][j];
    cp->board[i][j] = cp->board[k][l];
    cp->board[k][l] = tmp;
}

struct node *move(struct node *cp,int a,int b,int x,int y,int dir) {
  struct node *newp;
  int i,j,k,l,tmp;
  // malloc
  // copy from cp
  // swap two vals
  // compute f,g,h
  // insert the direction that resulted in this node, used for printing path
  return newp;
}

// Done.
struct node *goal_found (struct node *cp, struct node *gp){
    int flg=FALSE;
    while(cp && !nodes_same(cp, gp)) { cp = cp->next; }
    if (cp == NULL) { return NULL; }
    return cp;
}

// Done.
int count (struct node *cp) {
    int cnt = 0;
    while (cp != NULL) {
        cnt++;
        cp = cp->next;
    }
    return cnt;
}

struct node *merge (struct node *succ, struct node *open, int flg) {
    struct node *csucc,*copen;
    if (flg==DFS) {    /* attach in the front: succ -> ... -> open */
        csucc = succ;
        while(csucc->next) {
            csucc = csucc->next;
        }
        csucc->next = open;
        open = succ;
    } else if (flg==BFS) {      /* attach at the end: open -> ... -> succ */
        copen = open;
        if (copen == NULL) {
            open = succ;
        } else {
            while(copen->next != NULL) {
                copen = copen->next;
            }
            copen->next = succ;
        }
    } else if (flg==BEST) {    /* Best first: sort on h value */
    //...
    } else {            /* A* search: sort on f=g+h value */
    //...
    }
    return open;
}


/* insert succ into open in ascending order of x value, where x is an array
   index: 0=f,1=g,h=2 of board[N][x]
 */
struct node *insert_node(struct node *succ,struct node *open,int x) {
   int cnt;
   struct node *copen,*topen;
   //...
   return open;
}

int find_h(int current[N+1][N],int goalp[N+1][N]) {
  int h=0,i,j,k,l,done;
  // ...
  return h;
}

// Done.
int nodes_same (struct node *xp, struct node *yp) {
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (xp->board[i][j] != yp->board[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}

/******************************************************************************
  Check succ against open and closed. Remove those succ nodes that are in open or closed.
******************************************************************************/
// Done.
struct node *filter (struct node *succ, struct node *hp) {
    struct node *lsp,*rsp;  /* lsp=left succ p, rsp=right succ p */
    struct node *cp, *sp, *tp, *np, *arr[9999];
    cp = hp;
    sp = succ;
    tp = succ;
    int cnt, i, match;
    cnt = 0;
    while (sp) {
        cp = hp;
        while (cp && !nodes_same(cp, sp)) {
          cp=cp->next;
        }
        if (cp == NULL) {
          arr[cnt] = sp;
          cnt++;
        }
        sp = sp->next;
    }
    if (cnt > 0) {
        succ = arr[0];
        arr[cnt - 1]->next = NULL;
        np = succ;
        for (i = 1; i < cnt; ++i) {
            np->next = arr[i];
            np = np->next;
        }
    } else {
        succ = NULL;
    }
    return succ;
}

// Done.
void print_nodes (struct node *cp, char name[20]) {
    int i;
    printf("%s:\n", name);
    while (cp) {
        print_a_node(cp);
        cp = cp->next;
    }
}

// Done.
void print_a_node (struct node *np) {
    int i, j;
    for (i = 0; i < N + 1; i++) {
        for (j = 0; j < N; j++) {
            printf("%2d ", np->board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Done.
int solvable (struct node *cp) {
    int i, j, k = 0, lst[NxN], cnt = 0, total = 0;
    // store grid in flat list for simplicity
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            lst[k++] = cp->board[i][j];
        }
    }
    // Sum all inversions of numbers
    for (i = 0; i < k; i++) {
        cnt = 0;
        if (i == 0) { continue; }
        if (lst[i] == 0) { continue; }
        for (j = i; j > 0; j--) {
            if (lst[j-1] == 0) { continue; }
            if (lst[i] > lst[j-1]) { cnt++; }
        }
        total += cnt;
    }
    return total;
}

// Done.
struct node *initialize (int argc, char **argv) {
    int i, j, k, npe, n, idx, gidx, inv;
    struct node *tp;
    // Create new node and read cmd args into board
    tp = (struct node *) malloc(sizeof(struct node));
    idx = 1;
    for (j = 0; j < N; j++) {
        for (k = 0; k < N; k++) { tp->board[j][k] = atoi(argv[idx++]); }
    }
    // Set f,g,h values of additional row to 0
    for (k = 0; k < N; k++) {
        tp->board[N][k] = 0;
    }
    // Assign new node to start
    tp->next = NULL;
    start = tp;
    // Print the initial state
    printf("init state: \n");
    print_a_node(start);
    // Create goal state node
    tp = (struct node *) malloc(sizeof(struct node));
    gidx = 1;
    for (j = 0; j < N; j++) {
        for (k = 0; k < N; k++) { tp->board[j][k] = gidx++; }
    }
    tp->board[N-1][N-1] = 0;
    for (k = 0; k < N; k++) { tp->board[N][k]=0; }
    tp->next = NULL;
    goal = tp;
    // Print goal state
    printf("goal state: \n");
    print_a_node(goal);
    // Determine search strategy from cmd args
    strcpy(strategy_s, argv[idx]);
    if (strcmp(strategy_s, "dfs") == 0) strategy = DFS;
    else if (strcmp(strategy_s, "bfs") == 0) strategy = BFS;
    else if (strcmp(strategy_s, "best") == 0) strategy = BEST;
    else if (strcmp(strategy_s, "bb") == 0) strategy = BB;
    else if (strcmp(strategy_s, "astar") == 0) strategy = ASTAR;
    else strategy = UNKNOWN;
    printf("strategy=%s\n", strategy_s);
    return start;
}

// Done.
void exit_proc (char *msg) {
    printf("Error: %s\n", msg);
    exit(1);
}

/*****************************************************************************
 End of file: fif.c. Fifteen Puzzle, Sequential A* 1 processor version.
*****************************************************************************/
