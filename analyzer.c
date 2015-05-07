#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>		

void find_hor_lines(int **image, int x, int y){
	int i,j,num,len;
	int on_line;
	num=0;
	for(i=0;i<x;i++){
		len=0;on_line=0;
		for(j=0;j<y;j++){

			if(image[i][j]==1){
				if(len==0){
				len+=1;
				on_line=1;
				}
				else{
					if(on_line!=2)
						len+=1;
				}
			}
			else{
				if(on_line==1){
					on_line=2;
					if(len>=2)
						num+=1;
				}

			}


			}

		}


	

	printf("число горизонтальных линий - %d\n",num);


}

void find_vert_lines(int **image, int x, int y){
	int i,j,num,len;
	int on_line;
	num=0;
	
	for(j=0;j<y;j++){
		len=0;on_line=0;
		for(i=0;i<x;i++){

			if(image[i][j]==1){
				if(len==0){
				len+=1;
				on_line=1;
				}
				else{
					if(on_line!=2)
						len+=1;
				}
			}
			else{
				if(on_line==1){
					on_line=2;
					if(len>=2)
						num+=1;
				}

			}

		}


	}

	printf("число вертикальных линий - %d\n",num);


}



int num_check(char a){
	if(a=='1'||a=='0')
		return 1;
	return 0;
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


int main(int argc, char *argv[]){
	int j,i,ii=0;
	int ** image;
	int read_len=120;
	char tempsym[read_len];
	int col,row,temp;
	FILE *f;

		f=fopen(argv[1],"r");

		if(f==0){
			printf("Файл с таким именем не найден.\n");
			
		}
		//обрабатываем файл
		//считываем The "magic number" (с) http://netpbm.sourceforge.net/doc/pbm.html
		fgets(tempsym, read_len, f);
		fgets(tempsym, read_len, f);
		if(( (int) tempsym[0])>=48 && ((int) tempsym[0])<=57){//проверяем, является ли первый символ числом
				
			col=0;
			row=0;
			i=0;
			while(( (int) tempsym[i])>=48 && ((int) tempsym[i])<=57 && i<70){//считаем для начала число столбцов
				col=col*10+(int)tempsym[i]-(int)('0');
				
				i++;
			}
				
			i++;
			//проверяем, не вышли ли мы за рамки дозволенного
			if(i>3 ){
				printf("Ошибка в файле. \n");
			}

			while(( (int) tempsym[i])>=48 && ((int) tempsym[i])<=57 && i<70){//считаем число строк
				row=row*10+(int)tempsym[i]-(int)('0');
				
				i++;
			}
				
			//и вновь проверим, все ли хорошо
			if(i>7){
				printf("Ошибка в файле. \n");
			}

			
			//выделяем память под матрицу для изображения
			image=(int**)malloc(row*sizeof(int*));
				for(i=0;i<row;i++){
					image[i]=(int*)malloc(col*sizeof(int));				
				}

			// главное веселье - считываем изображение
			temp=1;
			for(i=0; i<row && temp ;i++){
				if(fgets(tempsym, read_len, f)!=NULL){//взяли новую строку, заодно глянули, не конец ли файла
					for(j=0;j<col&&temp;j++){
						if(num_check(tempsym[j*2]))//проверем, тот ли символ
							image[i][j]=atoi(&tempsym[j*2]);

							else {//если все же не тот
								temp=0;
							}
						}
					}
					else temp=0;//если внезапно наступил конец
				}
				fclose(f);//закрыли файл
				//смотрим, не было ли проблем
				if(!temp){
					printf("Ошибка в файле. \n");
					erraze_image(image,row,col);
					
				}

			}
			find_hor_lines(image, row, col);
			find_vert_lines(image, row, col);
			erraze_image(image,row,col);
	

	return 0;
}

