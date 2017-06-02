#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define NOT_FOUND NULL	

FILE *fp,*fp2;
/*char *str,str2[50];*/
int i=0,h=0;
int c[27]={9,10,16,23,25,2,5,7,11,12,15,21,22,24,0,1,3,4,6,8,13,14,17,18,19,20};
/*9 10 16 20 23 25 2 5 7 11 12 15 21 22 24 0 1 3 4 6 8 13 14 17 18 19 20*/
/*J K Q X Z 
  C F H L M P V W Y
  A B D E G I N O R S T U*/

typedef struct tree_t {
int se;
int score;	 
char *word;
int *key;
struct tree_t *n0;
struct tree_t *n1;
struct tree_t *n2;
struct tree_t *n3;
struct tree_t *n4;
struct tree_t *n5;
struct tree_t *n6;
struct tree_t *n7;

} tree_type;

tree_type *make_tree (int x) {
tree_type *tree;
tree = (tree_type *) malloc (sizeof (tree_type));
tree->se=x;
tree->n0=NULL;
tree->n1=NULL;
tree->n2=NULL;
tree->n3=NULL;
tree->n4=NULL;
tree->n5=NULL;
tree->n6=NULL;
tree->n7=NULL;

return (tree);
}


tree_type *insert (int *key, char *word, tree_type *tree ,int h) {
char str[4],str2[3];
tree_type *new_tree;

if(tree==NULL){printf("first\n");
tree = make_tree(1);}
 if(h<=25){ 
   if(key[h]==0){ 
     if (tree->n0 == NULL) {
new_tree = make_tree (h);
       tree->n0 = new_tree;
     }
    tree->n0= insert (key, word, tree->n0,++h);
   }
   else if(key[h]==1){ 
     if (tree->n1 == NULL) {
       new_tree = make_tree (h);
       tree->n1 = new_tree;
     }
     tree->n1=insert (key, word, tree->n1,++h);
   }
   else if(key[h]==2){ 
     if (tree->n2 == NULL) {
       new_tree = make_tree (h);
       tree->n2 = new_tree;
     }
     tree->n2=insert (key, word, tree->n2,++h);
   }
   else if(key[h]==3){ 
     if (tree->n3 == NULL) {
       new_tree = make_tree (h);
       tree->n3 = new_tree;
     }
tree->n3=insert (key, word, tree->n3,++h);
   }
   else if(key[h]==4){ 
     if (tree->n4 == NULL) {
       new_tree = make_tree (h);
       tree->n4 = new_tree;
}
     tree->n4=insert (key, word, tree->n4,++h);
   }
   else if(key[h]==5){ 
      if (tree->n5 == NULL) {
       new_tree = make_tree (h);
       tree->n5 = new_tree;
     }
     tree->n5=insert (key, word, tree->n5,++h);
   }
   else if(key[h]==6){ 
     if (tree->n6 == NULL) {
       new_tree = make_tree (h);
       tree->n6 = new_tree;
     }
     tree->n6=insert (key, word, tree->n6,++h);
   }
   else{ 
     if (tree->n7 == NULL) {
       new_tree = make_tree (h);
       tree->n7 = new_tree;
     }
     tree->n7=insert (key, word, tree->n7,++h);
   }
  
} else{ tree->word=word;
}
 return tree;
}

void sort(char* word,int *num){
int numr[26]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

 for(h=0;h<strlen(word);h++){
i=word[h]-97;
if(i<0)i=word[h]-65;
if((0<=i)&&(i<=26))numr[i]++;
}

for(h=0;h<26;h++){
num[h]=numr[c[h]];
fprintf(fp2,"%d ",num[h]);
}

 num[25]=num[25]-num[2];
 /*for(h=0;h<26;h++){
  printf("%d",num[h]);}
  printf("\n");*/
}

tree_type *dictionary_tree(tree_type *tree){
int num[26];
 char *str;
int r;
 fp=fopen("dictionary.txt","r");
/* fp=fopen("a.txt","r");*/
/*fp=fopen("apple.txt","r");*/
if(fp==NULL){
printf("no file\n");
}
fp2=fopen("dictionary-sort.txt","w");
/*  fp2=fopen("dictionary-sort2.txt","w");*/
tree=make_tree(0);

 while(1){ 
str = (char*)malloc(sizeof(str));
   i=fscanf(fp,"%s",str);
   if(i==EOF){fclose(fp);
     return(tree);}
  if(strcmp(&str[16],"")==0){
for(h=0;h<26;h++){
num[h]=0;}
sort(str,num);

tree=insert(num,str,tree,0);


fprintf(fp2,"%s\n",str);
  
}

}

fclose(fp);

fclose(fp2);


return(tree);
}

char *search(int *target, tree_type *tree, int num){
 
if((tree==NULL)&&(num<25)){return (NOT_FOUND);}
 if(num<26){ 
   if(target[num]==0){
return (search(target,tree->n0,++num));
}
 else if(target[num]==1){
return (search (target,tree->n1,++num));
}
 else if(target[num]==2){
return (search (target,tree->n2,++num));
}
 else if(target[num]==3){
return (search (target,tree->n3,++num));
}
 else if(target[num]==4){ 
return (search (target,tree->n4,++num));
}
 else if(target[num]==5){ 
return (search (target,tree->n5,++num));
 }
 else if(target[num]==6){ 
   return (search (target,tree->n6,++num));
 }
 else{ 
   return (search (target,tree->n7,++num));
 }
     
 }
  return (tree->word);}

int main(){
  tree_type *tree;
  char ques[17];
  char *ans;
  int target[26];
  int target1[26];
  int target2[26];
  int no0list[16];
  int no0list_num[16];
  int g;
  tree=NULL;
  tree=dictionary_tree(tree);
  while(1){printf("characters?\n");
    scanf("%s",ques);
    strcat(ques,"");
    sort(ques,target);/*ソートされた配列が帰ってくる*/
   
    ans = search(target,tree,0);
  
      if (ans == NOT_FOUND) {
	for(i=0;i<26;i++)target1[i]=target[i];
    g=0;
    for(i=25;0<i;i--){
      if(target1[i]!=0){
	 no0list[g]=i;
	 no0list_num[g]=target[i];
	g++;
      }
   }//no0list(何文字目に0以上の数字があるか)を作る
    for(i=0;i<16;i++){printf("%d ",no0list[i]);}
    if(ans==NOT_FOUND){
      for(i=0;i<26;i++)target2[i]=target1[i];

      for(h=0;h<16;h++){ for(i=0;i<26;i++)target2[i]=target1[i];
      for(i=0;i<no0list_num[h];i++){
	target2[no0list[h]]--;
      ans=search(target2,tree,0);
      if(ans!=NOT_FOUND)break;
      /*searchをくりかえす*/}}
    }
  
    if(ans==NOT_FOUND)printf ("見つかりませんでした。\n");
     /*ans==NOT_FOUNDなら*/ } else {
      printf ("%s\n", ans);
    }
  }
}
