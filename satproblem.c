//elif gokpinar
#include <stdio.h>
#include <string.h>
#include <math.h>

//Prints array
printArray(int array[],int size){
	int k;
	for(k=0; k<size; k++){
		printf("%d ",array[k]);
	}
	printf("\n");
}
void differentSequence(int array[], int startIndex, int lastIndex,int valueArray[],int valueSize,int truthSize,int clause)
{
    if(startIndex==lastIndex)
    {
		check(valueArray,valueSize,array,truthSize,clause);
    }
    int i;
    for(i=startIndex;i<=lastIndex;i++)
    {
        //swapping numbers
        int temp=array[i];
        array[i]=array[startIndex];
        array[startIndex]=temp;
        differentSequence(array, startIndex+1, lastIndex,valueArray,valueSize,truthSize,clause);
        //swapping numbers
        int temp2=array[i];
        array[i]=array[startIndex];
        array[startIndex]=temp2;	
        
    }
}
//Checks the truth value for each propositions
void check(int valueArray[],int valueSize,int truthArray[],int truthSize,int clause){
	
	int i,j,k,total=0,tsize,isclause=0;
	
	
		for(j=0; j<valueSize; j++){
					
			if(valueArray[j]!=0){
				if(valueArray[j]>0){
					
					total=total+truthArray[valueArray[j]-1];
				}	
				else{
					int absolute=abs(valueArray[j]);
					total=total+!truthArray[absolute-1];
				}
			}
			if(valueArray[j]==0){
				if(total==0){
				break;
				}
				else{
				total=0;
				isclause=isclause+1;
				continue;
				}
			}
	
		}
		
			FILE *output=fopen("output.cnf","w");
			if(isclause==clause){
				printf("SAT\n\n");
				fprintf(output,"%s\n\n","SAT");
				j=0;
				for(i=0; i<truthSize; i++){
					
					if(truthArray[i]>0){
						printf("%d  ",j+1);
						fprintf(output,"%d  ",j+1);
						j++;
					}
					else {
						printf("%d  ",-(j+1));
						fprintf(output,"%d  ",-(j+1));
						j++;
					}
				}
			    exit(0);
				}
			
			fclose(output);

}

//**********************************************MAIN******************************************
int main(){
	FILE *read;
	
	read=fopen("input.cnf","r");
	int pass=0;
	char string[30];
	int clause,numberOfVariables,count,number;
	
	while(!feof(read)){
			if(pass<2){
			fscanf(read,"%s",string);
			//printf("%s ",string);		
			}
			if(2==pass){
			fscanf(read,"%d",&numberOfVariables);	
			}
			if(3==pass){
			fscanf(read,"%d",&clause);
			}
			if(3<pass){
			fscanf(read,"%d",&number);
			}
		pass++;			
	}
	fclose(read);

	read=fopen("input.cnf","r");
	int valueArray[pass-4];
	pass=0;
	int index=-1;
	while(!feof(read)){
		
			if(pass<2){
			fscanf(read,"%s",string);
	
			}
			if(2==pass){
			fscanf(read,"%d",&numberOfVariables);
		
			}
			if(3==pass){
			fscanf(read,"%d",&clause);

			}
			if(3<pass){
			index++;
			fscanf(read,"%d",&number);
			valueArray[index]=number;
			}
		pass++;				
	}
	fclose(read);

	int truthValues[numberOfVariables];
	int i,j,k;
	int truthValues2[numberOfVariables];
	for(i=0; i<numberOfVariables; i++){
		truthValues[i]=1;
		truthValues2[i]=1;

	}
	check(valueArray,index+1,truthValues2,numberOfVariables,clause);
	
	for(i=0; i<numberOfVariables;i++){
		for(j=0; j<i+1; j++){
		truthValues[j]=0;
	}	
		differentSequence(truthValues, 0, numberOfVariables-1,valueArray,index+1,numberOfVariables,clause);	
		}
	FILE *output2=fopen("output.cnf","w");
	printf("UNSAT");
	fprintf(output2,"%s\n\n","UNSAT");

}
