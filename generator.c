#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//1-ok,0-fooooo
int draw_vert_lines(int num, int len, int** mat, int x, int y){
	if(len<=x){	
		int row_start=(x-len)/2;
		int col_start=y-num*2-2;
		if(col_start<0) col_start=0;
		if(((y%2==0)&&(num<=y/2))||((num<=y/2+1)&&(y%2==1))){
				int i,j,tempnum;
				i=0;
				j=0;
				
				
				for(i;i<len;i++)					
					for(j=col_start, tempnum=num;j<y/2, tempnum>0;j+=2,tempnum--){
						mat[row_start+i][j]=1;
						
						
					}
				
		}	
		else
			return 0;

		
		
	}
	else
		return 0;
	return 1;
}

int draw_hor_lines(int num, int len, int** mat, int x, int y){
	if(len<=y){	
		int col_start=(y-len)/2;
		int row_start=x-num*2-2;
		if(row_start<0) row_start=0;
		if(((y%2==0)&&(num<=y/2))||((num<=y/2+1)&&(y%2==1))){
				int i,j,tempnum;
				i=0;
				j=0;
						
				
				for(i=row_start, tempnum=num; tempnum>0;tempnum--,i+=2){
					for(j=col_start;j<col_start+len;j++)
						mat[i][j]=1;

				}

			}
			else
				return 0;
	}
	else
		return 0;
	return 1;
}



void erraze_image(int **image, int x, int y){
	int i,j;
	for(i=0;i<x;i++)
		for(j=0;j<y;j++)
			image[i][j]=0;

}

void draw_image_screen(int **image, int x, int y){
	int i,j;
	for(i=0;i<x;i++){
		for(j=0;j<y;j++)
			printf("%d ",image[i][j]);
		printf("\n");
	}

}

void write_file(char *fname, int **image, int x, int y){
	int i,j;
	FILE *f;
	f=fopen(fname,"wt");

	fprintf(f,"P1\n");
	fprintf(f,"%d %d\n",y,x);

	for(i=0;i<x;i++){
		for(j=0;j<y;j++)
			fprintf(f,"%d ",image[i][j]);
		fprintf(f,"\n");
	}
	fclose(f);


}


int main(){
	int ** image;
	int i,j;
	int x,y,num;
	srand(time(NULL));//магия - привязываем генератор к дате, чтобы при каждом запуске числа разнились
	x=rand()%50;//stroki
	y=rand()%50;//stolbci
	//num=4;//chislo polos
	//len=5;//dlina polos
	image=(int**)malloc(x*sizeof(int*));
					for(i=0;i<x;i++){
						image[i]=(int*)malloc(y*sizeof(int));				
					}

	char *fname="testhor.pbm";
	char *fname2="testvert.pbm";
	erraze_image(image,x,y);
	

	num=rand()%(x/2);
	if(num==0) num=1;
	draw_hor_lines(num,rand()%y+1,image,x,y);
	write_file(fname,image,x,y);
	
	erraze_image(image,x,y);

	num=rand()%(y/2);
	if(num==0) num=1;
	draw_vert_lines(num,rand()%x+1,image,x,y);
	write_file(fname2,image,x,y);
	
	return 0;

}
