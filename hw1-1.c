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
struct tree_t *n8;
struct tree_t *n9;
struct tree_t *n10;
struct tree_t *n11;
struct tree_t *n12;
struct tree_t *n13;
struct tree_t *n14;
struct tree_t *n15;
struct tree_t *n16;

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
tree->n8=NULL;
tree->n9=NULL;
tree->n10=NULL;
tree->n11=NULL;
tree->n12=NULL;
tree->n13=NULL;
tree->n14=NULL;
tree->n15=NULL;
tree->n16=NULL;
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
   else if(key[h]==7){ 
     if (tree->n7 == NULL) {
       new_tree = make_tree (h);
       tree->n7 = new_tree;
     }
     tree->n7=insert (key, word, tree->n7,++h);
   }
   else if(key[h]==8){ 
     if (tree->n8 == NULL) {
       new_tree = make_tree (h);
       tree->n8 = new_tree;
     }
     tree->n8=insert (key, word, tree->n8,++h);
   }    
   else if(key[h]==9){ 
     if (tree->n9 == NULL) {
       new_tree = make_tree (h);
       tree->n9 = new_tree;
     }
     tree->n9=insert (key, word, tree->n9,++h);
   }
   else if(key[h]==10){ 
     if (tree->n10 == NULL) {
       new_tree = make_tree (h);
       tree->n10 = new_tree;
     }
     tree->n10=insert (key, word, tree->n10,++h);
   }
   else if(key[h]==11){ 
     if (tree->n11 == NULL) {
       new_tree = make_tree (h);
       tree->n11 = new_tree;
     }
     tree->n11=insert (key, word, tree->n11,++h);
   }
   else if(key[h]==12){ 
     if (tree->n12 == NULL) {
       new_tree = make_tree (h);
       tree->n12 = new_tree;
     }
     tree->n12=insert (key, word, tree->n12,++h);
   }
   else if(key[h]==13){ 
     if (tree->n13 == NULL) {
       new_tree = make_tree (h);
       tree->n13 = new_tree;
     }
     tree->n13=insert (key, word, tree->n13,++h);
   }
   else if(key[h]==14){ 
     if (tree->n0 == NULL) {
       new_tree = make_tree (h);
       tree->n14 = new_tree;
     }
     tree->n14=insert (key, word, tree->n14,++h);
   }
   else if(key[h]==15){ 
     if (tree->n15 == NULL) {
       new_tree = make_tree (h);
       tree->n15 = new_tree;
     }
     tree->n15=insert (key, word, tree->n15,++h);
   }
   else { 
     if (tree->n16 == NULL) {
       new_tree = make_tree (h);
       tree->n16 = new_tree;
     }
     tree->n16=insert (key, word, tree->n16,++h);
   }
} else{ tree->word=word;
}
 return tree;
}

void sort(char* word,int *num){
int numr[26]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

for(h=0;h<16;h++){
i=word[h]-97;
if(i<0)i=word[h]-65;
if((0<=i)&&(i<=26))numr[i]++;
}

for(h=0;h<26;h++){
num[h]=numr[c[h]];
fprintf(fp2,"%d ",num[h]);
}

 num[25]=num[25]-num[2];

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
 else if(target[num]==7){ 
   return (search (target,tree->n7,++num));
 }
 else if(target[num]==8){ 
   return (search (target,tree->n8,++num));
 }
 else if(target[num]==9){ 
   return (search (target,tree->n9,++num));
 }
 else if(target[num]==10){ 
   return (search (target,tree->n10,++num));
 }
 else if(target[num]==11){ 
   return (search (target,tree->n11,++num));
 }
 else if(target[num]==12){ 
   return (search (target,tree->n12,++num));
 }
 else if(target[num]==13){ 
   return (search (target,tree->n13,++num));
 }
 else if(target[num]==14){ 
   return (search (target,tree->n14,++num));
 }
 else if(target[num]==15){ 
   return (search (target,tree->n15,++num));
 }
 else if(target[num]==16){ 
   return (search (target,tree->n16,++num));
 }
     
 }
  return (tree->word);}

int main(){
  tree_type *tree;
  char ques[17];
  char *ans;
  int target[26];
  tree=NULL;
  tree=dictionary_tree(tree);
  while(1){printf("characters?\n");
    scanf("%s",ques);
    strcat(ques,"");
    sort(ques,target);/*ソートされた配列が帰ってくる*/
   
    ans = search(target,tree,0);
    if (ans == NOT_FOUND) {
      printf ("見つかりませんでした。\n");
    } else {
      printf ("%s\n", ans);
    }
  }
}
