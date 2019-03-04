#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<queue>
#include<iostream>
using namespace std;
int sym;
int isReservedWord(char buffer[]){
    char rsvword[34][10]={"auto","break","case","char","const","continue","default",
                          "do","double","else","enum","extern","float","for","goto",
                          "if","int","long","register","return","short","signed",
                          "sizeof","static","struct","switch","typedef","union",
                          "unsigned","void","volatile","while","NULL","FILE"};
    int i,flag=0;
    for(i=0;i<34;i++){
        if(strcmp(rsvword[i],buffer)==0){
            flag=1;
            break;
        }
    }
    sym=1;
    return flag;
}
int main(){
	queue <char> cont;
    char ch,buffer[255],operators[]="+-*/%&|",assign[]="=<>!";
    FILE *fp;
    int i,j=0,flag=0,num=0,num2=0,num3=0,lib=0;
    fp=fopen("testcase.cpp","r");
    if(fp==NULL){
        printf("Error while opening the file!\n");
        exit(0);
    }
    int line=1;
    printf("--------------------------------------------------------------------- %d\n", line);
    while((ch=fgetc(fp))!=EOF){
    	if(ch=='\n'){
    		line++;
    		printf("--------------------------------------------------------------------- %d\n", line);
		}
    	if(ch=='#') lib=1;
    	if((ch=='<'||flag==4) && lib==1){
    		if(flag==3){
    			buffer[j]='\0';
				printf("%s is reserved word\n",buffer);
				j=0;
				printf("%c is symbol\n",ch);
    			flag=4;
			}
    		else if(ch=='>'&&flag==4){
    			if(!cont.empty()){
	    			for(int i=0;i<num2;i++){
	    				printf("%c",cont.front());
	    				cont.pop();
					}
					printf(" is reserved word\n");	
					printf("%c is symbol\n",ch);
					num2=0;
					flag=0;
					lib=0;
				}
			}
			else if(flag==4){
				cont.push(ch);
				num2++;
			}
    		else{
    			printf("%c is symbol\n",ch);
    			flag=4;
			}
		}
    	else if(ch=='\"'||flag==1){
    		if(ch=='\"'&&flag==1){
    			if(!cont.empty()){
	    			for(int i=0;i<num;i++){
	    				printf("%c",cont.front());
	    				cont.pop();
					}
					printf(" is sentence\n");	
					printf("%c is symbol\n", ch);
					num=0;
					flag=0;
				}
			}
			else if(flag==1){
				cont.push(ch);
				num++;
			}
    		else{
    			printf("%c is symbol\n",ch);
    			flag=1;
			}
		}
		else if(ch=='\''||flag==5){
    		if(ch=='\''&&flag==5){
    			if(!cont.empty()){
	    			for(int i=0;i<num3;i++){
	    				printf("%c",cont.front());
	    				cont.pop();
					}
					printf(" is character\n");	
					printf("%c is symbol\n", ch);
					num3=0;
					flag=0;
				}
			}
			else if(flag==5){
				cont.push(ch);
				num3++;
			}
    		else{
    			printf("%c is symbol\n",ch);
    			flag=5;
			}
		}
		else if(!isalnum(ch)&&!isspace(ch)){
			for(int i=0;i<7;i++){
				if(ch==operators[i]){
					if(sym==1) printf("%c is symbol\n",ch);
					else printf("%c is operator\n",ch);
					flag=2;
					sym=0;
					break;
				}
			}
			if(flag!=2){
				if(flag==3){
					buffer[j]='\0';
					if(isReservedWord(buffer)==1) printf("%s is reserved word\n",buffer);
					else{
						int a=0;
						for(int i=0;i<j;i++){
							if(isdigit(buffer[i])) a++;
						}
						if(a==j) printf("%s is number\n",buffer);
						else printf("%s is identifier\n",buffer);
					}
					j=0;
					flag=0;
				}
				for(int i=0;i<4;i++){
					if(ch==assign[i]){
						if(sym==1) printf("%c is symbol\n",ch);
						else printf("%c is assignment\n",ch);
						flag=2;
						sym=0;
						break;	
					}
				}
				if(flag!=2) printf("%c is symbol\n",ch);
			}
			flag=0;
		}
		else if(!isalnum(ch)&&flag==3){
			buffer[j]='\0';
			if(isReservedWord(buffer)==1) printf("%s is reserved word\n",buffer);
			else printf("%s is identifier\n",buffer);
			j=0;
			flag=0;
		}
		else if(isalnum(ch)){
			buffer[j]=ch;
			j++;
			flag=3;
		}
    }
    fclose(fp);
    return 0;
}
