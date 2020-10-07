#include <stdio.h>
#include<stdlib.h>


int main(void){
     int NumV=0;// количество вершин
     int NumN=0;// количество узлов
     int is_directed=0;// ориентированность графа
     int is_weight=0;// взвешенность графа
     int c;
	 FILE *MatrFile=fopen("matr.txt", "r");
	 if(MatrFile==NULL){
        printf("No such File");
     }else{
        printf("File is read\n");
        while(!feof(MatrFile)){              
            if((fgetc(MatrFile))==';'){
                NumV++;
            }
        } 
        fclose(MatrFile);
        FILE *MatrFile=fopen("matr.txt", "r");
        while((c=fgetc(MatrFile))!=';'){
            if(c==',')
                NumN++;
        }
        NumN++;
        fclose(MatrFile);
        int Arr [NumV][NumN]; // матрица инцидентности
        int loop[NumN];// массив петель
        MatrFile=fopen("matr.txt", "r");
        for(int i=0;i<NumV;i++){
            int j=0;
            while((c=fgetc(MatrFile))!=';')
                fscanf(MatrFile,"%d",&Arr[i][j++]);
        }
        fclose(MatrFile);

// проверяем является ли граф ориентрованным или взвешенным
        
        for (int i = 0; i < NumV; i++){
		    for (int j = 0; j < NumN; j++){
			    printf("%d ",Arr[i][j]);
                if (Arr[i][j]>1)
                    is_weight=1;
                if(Arr[i][j]<0)
                    is_directed=1;
            }
            printf("\n");
	    }  
        char weight[NumN];// массив взвешенных узлов
        if(is_weight){
            for (int j = 0; j < NumN; j++){
                for (int i = 0; i < NumN; i++){
                    if (Arr[i][j]>0)
                        weight[j]=Arr[i][j];
                }
             printf("%d - %d\n",j ,weight[j]);
            }
        }
    
        char VertNames[NumV]; // массив вершин
        for (int i = 0; i < NumV; i++)
            VertNames[i]='a'+i;
        char Connect[NumN][2];// содержит соединенные вершины
        for (int j = 0; j < NumN; j++){
            int k=0;
            for (int i = 0; i < NumV; i++){
                if(Arr[i][j]<0)
                    Connect[j][1]=VertNames[i];
                if (Arr[i][j]>0)
                    Connect[j][k++]=VertNames[i];   
             }
        }
        printf("\n");
        for (int i = 0; i < NumN; i++){
           loop[i]=0;
	        for (int j = 0; j < 2; j++){
                if(!Connect[i][j]){
                    loop[i]=1;
                    Connect[i][j]=Connect[i][j-1];
                }
		        printf("%c ",Connect[i][j]);
            }
            printf("\n");
	    }  

        // создание графа на языке dot и компиляция файла

        FILE *GraphFile=fopen("graph.dot", "w");
        if(GraphFile==NULL){
            printf("Problem with making a file");
        }else{
            printf("File is read\n");
            if(is_directed)
                fprintf(GraphFile,"di");
            fprintf(GraphFile,"graph Test {\n");
            for (int i = 0; i < NumN; i++){
                if(!is_directed)
                    fprintf(GraphFile,"%c -- %c ",Connect[i][0],Connect[i][1]);
                else{
                    fprintf(GraphFile,"%c -> %c ",Connect[i][0],Connect[i][1]);
                    }
                if (is_weight)
                    fprintf(GraphFile,"[label= %d] \n",weight[i]);
                }
            fprintf(GraphFile,"}\n");
            fclose(GraphFile);
            system("dot -Tpng graph.dot -o graph.png");
            system("xdg-open graph.png");
        }

        char Power[NumV];//степень вершины
        int is_con=1;// степень вершины больше 2
        for (int i = 0; i < NumV; i++){
            Power[i]=0;
            for (int j = 0; j < NumN; j++){
                if ((Arr[i][j]) && (!loop[j]))
                    Power[i]++;
            }
            if (Power[i]<2)
                is_con=0;
        }
        if(is_con){
            printf("This graph is connected\n");
        }else{
            printf("This graph is not connected\n");
        }
    }
 return 0;
}


