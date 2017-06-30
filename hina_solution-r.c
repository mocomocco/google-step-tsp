#include<stdio.h>
#include<stdlib.h>
#include<math.h>


typedef struct wayanddistance{
  float distance;
  int way[8];
  int visit;
}wayanddistance;

typedef struct pointdata{
  int pointnum;
  float xposition;
  float yposition;
  wayanddistance shortestway[256];
}pointdata;


FILE *OpenFile(char *open_filename){
  FILE *fp;
  fp=fopen(open_filename,"r");
  if(fp==NULL){
    printf("cannot find:%s\n",open_filename);
    return 0;
  }
  return fp;
}

void ReadFileAndList(FILE *fp,pointdata *positionlst,int *pointcounter){
  float xposition,yposition;
  char tmp[2480];
  char xchar,ychar;
  fscanf(fp,"%c,%c",&xchar,&ychar);
  while( fscanf(fp,"%f,%f",&xposition,&yposition)!=EOF){
    positionlst[*pointcounter].pointnum=*pointcounter+1.0;
    positionlst[*pointcounter].xposition=xposition;
    positionlst[*pointcounter].yposition=yposition;
    *pointcounter+=1;
  }
}

void OpenFileAndList(char *open_filename,pointdata *positionlst,int *pointcounter){
  FILE *fp;
  char tmp[5];
  fp=OpenFile(open_filename);
  ReadFileAndList(fp,positionlst,pointcounter);
  fclose(fp);
}

void MakeLeftPoint(int *leftpointlst,int pointcounter,int *leftpoint){
  int decimal=0;
  int base=1;
  for(int i=0;i<pointcounter;i++){
    decimal=decimal+leftpointlst[i]*base;
    base *= 2;
  }
  *leftpoint=decimal;
}
void MakeLeftPointLst(int decimal,int pointcounter,int *leftpointlst){
  int base = 1;
  int binary;
  for (int i=0;i<pointcounter;i++){
    binary=decimal%2;
    decimal=decimal/2;
    leftpointlst[i]=binary;
  }
}

float GetDistance(pointdata a,pointdata b){
  float dx=fabsf(a.xposition-b.xposition);
  float dy=fabsf(a.yposition-b.yposition);
  return sqrt(pow(dx,2)+pow(dy,2));
}

int EverOrNeverVisited(pointdata *positionlst,int leftpoint,int currentpointnum){
  int visit;
  wayanddistance currentwayanddistance;
  currentwayanddistance=positionlst[currentpointnum-1].shortestway[leftpoint-1];
  if(currentwayanddistance.visit==1){
    printf("have been to\n");
    printf("distance=%f\n",currentwayanddistance.distance);
    visit=1;
  }
  else {
    printf("neverbeento\n");
    visit=0;}
  return visit;
    }

int GetLeftPointCounter(int *leftpointlst,int pointcounter){
  int counter=0;
    for(int i=0;i<pointcounter;i++){
      counter+=leftpointlst[i];
    }
    printf("leftpointcounter:%d\n",counter);
    return counter; 
}

int GetNextPointNum(int *leftpointlst,int nextpointnum,int pointcounter){
  for(;nextpointnum-1<pointcounter;nextpointnum++){
    if(leftpointlst[nextpointnum-1]==1)break;
  }
  printf("nextpointnum:%d\n",nextpointnum);
  return nextpointnum;
}

wayanddistance DirectWayAndDistance(pointdata *positionlst,int currentpointnum,int leftpoint,int nextpointnum){
  positionlst[currentpointnum-1].shortestway[leftpoint-1].distance=GetDistance(positionlst[currentpointnum-1],positionlst[nextpointnum-1]);
  positionlst[currentpointnum-1].shortestway[leftpoint-1].way[0]=currentpointnum;
  positionlst[currentpointnum-1].shortestway[leftpoint-1].way[1]=nextpointnum;
  return  positionlst[currentpointnum-1].shortestway[leftpoint-1];
}
  

wayanddistance RecGetShortestWay(pointdata *positionlst,int pointcounter,int leftpoint,int currentpointnum){
  printf("RecGetShortestWay\n");
  printf("(positionlst,pointcounter=%d,leftpoint=%d,currentpointnum=%d)\n\n",pointcounter,leftpoint,currentpointnum);

  int EverVisit=EverOrNeverVisited(positionlst,leftpoint,currentpointnum);
  printf("EverVisit:%d\n",EverVisit);
  if(EverVisit){
    return positionlst[currentpointnum-1].shortestway[leftpoint-1];
  }
  else {
    printf("neverbeento\n");
    positionlst[currentpointnum-1].shortestway[leftpoint-1].visit=1;
    positionlst[currentpointnum-1].shortestway[leftpoint-1].distance=INFINITY;
  }

  int leftpointlst[pointcounter];
  int newleftpoint;
  int nextpointnum;
  float distance;
  int leftpointcounter=0;
  wayanddistance shortestway;

  newleftpoint=leftpoint;

  MakeLeftPointLst(leftpoint,pointcounter,leftpointlst);

  leftpointcounter=GetLeftPointCounter(leftpointlst,pointcounter);

  nextpointnum=1;

  while(1){
    nextpointnum++;
    for(int i=0;i<leftpointcounter;i++)printf("\t");
    printf("currentpointnum : %d\n",currentpointnum);
    nextpointnum=GetNextPointNum(leftpointlst,nextpointnum,pointcounter);   
    if(nextpointnum-1>=pointcounter)break;
    for(int i=0;i<leftpointcounter;i++)printf("\t");
    for(int i=0;i<pointcounter;i++){
      printf("%d ",leftpointlst[i]);
    }
    printf("\n↓\n");

    leftpointlst[nextpointnum-1]=0;
    for(int i=0;i<leftpointcounter;i++)printf("\t");

    for(int i=0;i<pointcounter;i++){
      printf("%d ",leftpointlst[i]);
    }
    printf("\n");
    MakeLeftPoint(leftpointlst,pointcounter,&newleftpoint);
    for(int i=0;i<leftpointcounter;i++)printf("\t");

    printf("newleftpoint : %d\n\n",newleftpoint);

    if(newleftpoint==0){
      for(int i=0;i<leftpointcounter;i++)printf("\t");
      printf("return DirectWayAndDistance\n");
        return  DirectWayAndDistance(positionlst,currentpointnum,leftpoint,nextpointnum);
    }
    else{
      float first,rest;
      for(int i=0;i<leftpointcounter;i++)printf("\t");

      printf("first\n");
      first=RecGetShortestWay(positionlst,pointcounter,leftpoint-newleftpoint,currentpointnum).distance;
      for(int i=0;i<leftpointcounter;i++)printf("\t");
      printf("first : RecGetShortestWay(positionlst,pointcounter,%d,%d).distance=%f\n",leftpoint-newleftpoint,currentpointnum, first);
      for(int i=0;i<leftpointcounter;i++)printf("\t");
      printf("rest\n");
      rest= RecGetShortestWay(positionlst,pointcounter,newleftpoint,nextpointnum).distance;
      for(int i=0;i<leftpointcounter;i++)printf("\t");

 printf("rest : RecGetShortestWay(positionlst,pointcounter,%d,%d).distance=%f\n",newleftpoint,nextpointnum, rest);
 for(int i=0;i<leftpointcounter;i++)printf("\t");

      printf("RecGetShortestWay(positionlst,pointcounter,%d,%d).distance+RecGetShortestWay(positionlst,pointcounter,%d,%d).distance\n",newleftpoint,nextpointnum,leftpoint-newleftpoint,currentpointnum);
      printf("a\n");
      distance=rest+first;
      printf("b\n");  
for(int i=0;i<leftpointcounter;i++)printf("\t");

    printf("distance : %f\n\n\n",distance);
for(int i=0;i<leftpointcounter;i++)printf("\t");

 printf("///////////////////////////////////////////////////////\n");
for(int i=0;i<leftpointcounter;i++)printf("\t");
 printf("currentpointnum:%d|leftpoint:%d: shortestway.distance :%f\n///////////////////////////////////////////////////////\n\n\n\n",currentpointnum,leftpoint,positionlst[currentpointnum-1].shortestway[leftpoint-1].distance);
    if(distance<positionlst[currentpointnum-1].shortestway[leftpoint-1].distance){
      printf("renewal distance : %f\n",distance);
      printf("///////////////////////////////////////////////////// \n");
      positionlst[currentpointnum-1].shortestway[leftpoint-1].distance=distance;
      positionlst[currentpointnum-1].shortestway[leftpoint-1].way[0]=currentpointnum;
      for(int i=1;i<=leftpointcounter;i++){
	positionlst[currentpointnum-1].shortestway[leftpoint-1].way[i]=RecGetShortestWay(positionlst,pointcounter,newleftpoint,nextpointnum).way[i-1];
	printf("%d\n", RecGetShortestWay(positionlst,pointcounter,newleftpoint,nextpointnum).way[i-1]);
      }//for(int i=1;i<=leftpointcounter;i++)
    }// if(distance<shortestway.distance)
    }//else
     leftpointlst[nextpointnum-1]=1;
  }
  printf("return\n");
  return positionlst[currentpointnum-1].shortestway[leftpoint-1];
}

void memorization(pointdata *positionlst,int pointcounter){
  int leftpoint=pow(2,pointcounter)-1;
  wayanddistance shortestway,shortestway1;
  printf("memorization\n");
  for(int i=0;i<pointcounter;i++){
    for(int j=0;j<leftpoint;j++){
      positionlst[i].shortestway[j].visit=0;
      positionlst[i].shortestway[j].distance=INFINITY;
      }
  }
  leftpoint-=1;

  shortestway=RecGetShortestWay(positionlst,pointcounter,leftpoint,1);

  printf("finish memorization!\n");
  printf("distance:%f\n",shortestway.distance);
  for(int i=0;i<pointcounter;i++){
    printf("%d\n",shortestway.way[i]-1);
  }
}

void OpenFileAndListTest(pointdata *testpositionlst,int *testpointcounter){
  printf("OpenFileAndListTest\n");
  OpenFileAndList("ForTest.txt",testpositionlst,testpointcounter);
  for(int i=1;i<=*testpointcounter;i++){
    if(( testpositionlst[i-1].pointnum!=i)||(testpositionlst[i-1].xposition)!=(float)i*2||(testpositionlst[i-1]).yposition!=(float)i*2+1.0){
      printf("ERROR : OpenFileAndList\n ");
    }
  }

  printf("PASS : OpenFileAndList\n");
}

void MakeLeftPointLstTest(pointdata *testpositionlst,int testpointcounter){
  printf("MakeLeftPointLstTest\n");
  int testleftpoint=pow(2,testpointcounter)-1;
  int testleftpointlst[testpointcounter-1];
  MakeLeftPointLst(testleftpoint,testpointcounter,testleftpointlst);
  for(int i;i<testpointcounter;i++){
    if(testleftpointlst[i]!=1){
      printf("ERROR:MakeLeftPointLst\n");
      break;
    }
  }
  printf("PASS:MakeLeftPointLst\n");
}

void memorizationTest(pointdata *testpositionlst,int testpointcounter){
  printf("memorizationTest\n");
  MakeLeftPointLstTest(testpositionlst,testpointcounter);

}

void test(){
  pointdata *testpositionlst;
  int testpointcounter=0;
  testpositionlst=(pointdata*)malloc(sizeof(pointdata)*2480);
 
  printf("start test\n");
  OpenFileAndListTest(testpositionlst,&testpointcounter);
  memorizationTest(testpositionlst,testpointcounter);
}


int main(int argc,char *open_filename[]){

  if(argc==1){
    printf("No filename\n");
    return 0;
  }

  test();

  pointdata *positionlst;
  int pointcounter=0;
  positionlst=(pointdata*)malloc(sizeof(pointdata)*16);
  OpenFileAndList(open_filename[1],positionlst,&pointcounter);

  for(int i=0;i<pointcounter;i++){
    printf("No %d | x %f | y %f \n",positionlst[i].pointnum,positionlst[i].xposition,positionlst[i].yposition);
  }

  if (pointcounter<=8)memorization(positionlst,pointcounter);
  else printf("too much point!\n");
}
