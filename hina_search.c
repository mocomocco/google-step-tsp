#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int i, j, k;

#define PAGE_NUM_MAX 1483277
#define LINKED_PAGE_NUM_MAX 1065639
#define WORD_LENGTH_MAX 1024
#define PASSING_NUM_MAX 1024
#define TRIAL_CNT 1024
#define NOT_FOUND -1


char** read_page_file(char *file_name){//file_name上の名前一覧を配列に格納して返す
  FILE* file = fopen(file_name, "r");
  if(file == NULL){
    printf("Couldn't find file: %s\n", file_name);
    exit(1);
  }

  int id;
  char bf[WORD_LENGTH_MAX];
  int word_length;
  int word_index = 0;
  char** words = (char**)malloc(PAGE_NUM_MAX * sizeof(char*));

  while(1){
    int ret = fscanf(file, "%d\t%4095s\n", &id, bf);
    if(ret == EOF){
      fclose(file);
      break;
    } else {
      word_length = strlen(bf);
      if(word_length == WORD_LENGTH_MAX - 1){
        printf("Word is too long\n");
        exit(1);
      }
      char* word = (char*)malloc(word_length + 1);
      strcpy(word, bf);
      assert(word_index < PAGE_NUM_MAX);
      words[word_index++] = word;
    }
  }
  return words;
}


int** read_link_file(char *file_name){
  FILE* file = fopen(file_name, "r");
  if(file == NULL){
    printf("Couldn't find file: %s\n", file_name);
    exit(1);
  }

  int id1, id2;
  int id1_current;
  int id1_last;
  int id2_temp_stack[PAGE_NUM_MAX]; //id1_currentのリンク先のIDをid2_temp_stack[i]に順に一時的に格納する
  int id2_temp_stack_cnt; //id1_currentのリンク先の個数を一時的に数える
  int ret = fscanf(file, "%d\t%d\n", &id1, &id2);
  int** links = (int**)malloc(PAGE_NUM_MAX * sizeof(int*));

  while(1){
    id1_current = id1;
    id2_temp_stack_cnt = 0;
    id2_temp_stack[id2_temp_stack_cnt++] = id2;
    while(1){
      ret = fscanf(file, "%d\t%d\n", &id1, &id2);
      if(ret == EOF){
        if(id1_last != PAGE_NUM_MAX - 1){
          for(i = id1_last + 1; i < PAGE_NUM_MAX; i++){
            //IDがiのときリンク先がなければlinks[i][0]を-1とする
            links[i] = (int*) malloc(sizeof(int));
            links[i][0] = -1;
          }
        }
        fclose(file);
        return links;
      }else if(id1_current == id1){
        id2_temp_stack[id2_temp_stack_cnt++] = id2;
      }else{
        if(id1_current + 1 != id1){
          for(i = id1_current + 1; i < id1; i++){
            //IDがiのときリンク先がなければlinks[i][0]を-1とする
            links[i] = (int*) malloc(sizeof(int));
            links[i][0] = -1;
          }
        }
        break;
      }
    }
    links[id1_current] = (int*) malloc((id2_temp_stack_cnt + 1) * sizeof(int));
    for(i = 0; i < id2_temp_stack_cnt; i++){
      //id1_currentのリンク先のIDをlinks[id1_currrent][i]に順に保存する
      links[id1_current][i] = id2_temp_stack[i];
    }
    //links[id1_currrent][i]の最後の目印として-1を入れる
    links[id1_current][id2_temp_stack_cnt] = -1;
    id1_last = id1_current;
  }
}

void start_goal(char *start,char *goal){
  printf("start:");
  scanf("%s",start);  
  printf("goal:");
   scanf("%s",goal);
}

int search_id(char *target,char **words){
  for(i=0;i< PAGE_NUM_MAX;i++){
    if(strcmp(target,words[i])==0)return i;
}
  printf("%s:NOT FOUND!\n",target);
  return NOT_FOUND;
}

int **next_distances(int** before_stack,int goal_id,int **links,int *visited){
  //  printf("next_distances\n");
  int** next_stack=(int**)malloc((PAGE_NUM_MAX)*sizeof(int*));
     for(i = 0; i < PAGE_NUM_MAX; i++){
       next_stack[i] = (int*) malloc(10 * sizeof(int));
     }
     //   printf("next_stack_set\n");
  int current=0,before_id,next_id;
  int h,i,j;
  static int num=0;
  num++;
  // printf("before for\n");
  for(i=0;before_stack[i][0]!=-1;i++){
    before_id=before_stack[i][0];
    for(h=0;links[before_id][h]!=-1;h++){
      next_id=links[before_id][h];
      if(visited[next_id]==0){
	next_stack[current][0]=next_id;
	for(j=1;next_stack[current][j-1]!=-1;j++){
	  next_stack[current][j]=before_stack[i][j-1];
	}
	visited[next_id]=1;
	current++;
      }
         
      if(next_id==goal_id){
	//	printf("found\n");
	next_stack[0]=next_stack[current-1];
	return next_stack;
      }
    }

  }
  next_stack[current][0]=-1;
  return next_stack;

}

int *route_search(int start_id,int goal_id,int **links){
  //  printf("route_search\n");
  int *visited=(int*)malloc((PAGE_NUM_MAX)*sizeof(int));
       for(i = 0; i < PAGE_NUM_MAX; i++){
	 visited[i] = 0;
       }
       visited[start_id] = 1;

  int** stack =  (int**) malloc((PAGE_NUM_MAX) * sizeof(int*));
        for(i = 0; i < PAGE_NUM_MAX; i++){
	  stack[i] = (int*) malloc(7 * sizeof(int));
	}
        stack[0][0]=start_id;
	stack[0][1]=-1;
	stack[1][0]=-1;
  int i; 
  for(i=0;i<6;i++){
    stack=next_distances(stack,goal_id,links,visited);
    // printf("     after next_distances\n");
  if(stack[0][0]==goal_id)return stack[0];
  }
  stack[0][0]=-1;
  return stack[0];
}

int main(void){
  int n; //たどる回数
  int i;
  char start[400],goal[400];
  int start_id,goal_id;
  start_goal(start,goal);
  char** words = read_page_file("pages.txt");
  int** links = read_link_file("links.txt");//隣接リスト

  int *route;
  start_id=search_id(start,words);

  if(start_id==-1)return 0;
  goal_id=search_id(goal,words);

  if(goal_id==-1)return 0;

  // printf("start_id %d goal_id %d\n",start_id,goal_id);

  route=route_search(start_id,goal_id,links);
  if(route[0]==-1){
    printf("No route\n");
    return 0;
  }
  for(i=0;route[i]!=-1;i++){
    if(i!=0)printf("<-\n");
    printf("%s\n",words[route[i]]);
  }

  return 0;
}
