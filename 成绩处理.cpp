#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
struct pass
{
	int id;
	int problem_id;
	char date[66];
	char time[66];
}record[66666]; 
long f1(char ch_date[66],char ch_time[66],char c_date[66],char c_time[66])//计算时长 
{
	struct tm time_long;
	time_t t1,t2;			
	time_long.tm_year=1000*(ch_date[0]-'0')+100*(ch_date[1]-'0')+10*(ch_date[2]-'0')+(ch_date[3]-'0')-1900;
	time_long.tm_mon=10*(ch_date[5]-'0')+(ch_date[6]-'0')-1;
	time_long.tm_mday=10*(ch_date[8]-'0')+(ch_date[9]-'0');
	time_long.tm_hour=10*(ch_time[0]-'0')+(ch_time[1]-'0');
	time_long.tm_min=10*(ch_time[3]-'0')+(ch_time[4]-'0');
	time_long.tm_sec=10*(ch_time[6]-'0')+(ch_time[7]-'0');
	t1=mktime(&time_long);
	time_long.tm_year=1000*(c_date[0]-'0')+100*(c_date[1]-'0')+10*(c_date[2]-'0')+(c_date[3]-'0')-1900;
	time_long.tm_mon=10*(c_date[5]-'0')+(c_date[6]-'0')-1;
	time_long.tm_mday=10*(c_date[8]-'0')+(c_date[9]-'0');
	time_long.tm_hour=10*(c_time[0]-'0')+(c_time[1]-'0');
	time_long.tm_min=10*(c_time[3]-'0')+(c_time[4]-'0');
	time_long.tm_sec=10*(c_time[6]-'0')+(c_time[7]-'0');	
	t2 = mktime(&time_long);
	return (t2-t1)*1.0/60.0;
}
int main()
{
	FILE*fp1=fopen("c2017.txt","r");
	FILE*fp2=fopen("过题记录.txt","w");	
	FILE*fp3=fopen("成绩.txt","w");	
	FILE*fp4=fopen("功能一.txt","w"); 
	if(!fp1||!fp2||!fp3||!fp4)
	{
		printf("Can not open file.\n");
		
	}
	int i=0,j,count[301],e,f,L,N;	
	char shangchu[66];	
	fgets(shangchu,66,fp1);
	while(!feof(fp1))
	{
		fscanf(fp1,"%d %d %s %s",&record[i].id,&record[i].problem_id,record[i].date,record[i].time);							
		i++;			
	}
	printf("请老师耐心等待12秒钟!\n");
	printf("做了大作业后才知道自己在排序上还有很多不足。\n"); 
	int T; 
	char t[66],tt[66];
		for(e=0;e<i-1;e++)//按照ID升序顺序，给每道题的提交时间按先后顺序排序 
		{
			for(f=0;f<i-e-1;f++)
			{
				if(record[f].id==record[f+1].id&&(strcmp(record[f].date,record[f+1].date)>0))
				{
					strcpy(t,record[f].date);
					strcpy(record[f].date,record[f+1].date);
					strcpy(record[f+1].date,t);
					T=record[f].problem_id;
					record[f].problem_id=record[f+1].problem_id;
					record[f+1].problem_id=T;
					strcpy(tt,record[f].time);
					strcpy(record[f].time,record[f+1].time);
					strcpy(record[f+1].time,tt);
				}
				if(record[f].id==record[f+1].id&&((strcmp(record[f].date,record[f+1].date)==0))&&(strcmp(record[f].time,record[f+1].time)>0))
				{
					strcpy(t,record[f].time);
					strcpy(record[f].time,record[f+1].time);
					strcpy(record[f+1].time,t);
					T=record[f].problem_id;
					record[f].problem_id=record[f+1].problem_id;
					record[f+1].problem_id=T;
				}				
			}		
		}//
		printf("十分感谢老师的配合！\n");
		printf("请输入两个整数分别为时长L和过题数N！\n"); 
		scanf("%d %d",&L,&N); 
		int x,y,z,b,Record[66666]={0},REcord[66666]={0},s[66666]={0};
		printf("这一次是自己关于标记方面的短板，还请老师等个5秒钟！\n");		
		 for(e=0;e<i;e++)
		{
			z=f1(record[e].date,record[e].time,record[e+N-1].date,record[e+N-1].time);							
			if((record[e].id==record[e+N-1].id)&&(z<=L))
			{
				for(f=0;f<i-e-1;f++)
				{				
					for(x=0,s[e]=0,y=0;;)					
					{
						s[e]++;
						REcord[e]=1;						
						Record[e+y]=1;
						y++;
						if(y>=N) x=1;
						if(x=1&&f1(record[e].date,record[e].time,record[e+y].date,record[e+y].time)>L) break; 
					}
				}		
			}			
			
		}
		
			for(b=0;b<i;b++)
			{
				y=0; 
				if((REcord[b]==1)) 
				{
					fprintf(fp4,"ID 	开始时间	结束时间 时长（min） 过题数 \n");
					fprintf(fp4,"******************************************************\n");
					fprintf(fp4,"%d %s %s %s %s %d  %d\n",record[b].id,record[b].date,record[b].time,record[b+s[b]-1].date,record[b+s[b]-1].time,f1(record[b].date,record[b].time,record[b+s[b]-1].date,record[b+s[b]-1].time),s[b]);
				}
				for (x=0;x<s[b];x++)
				{
					fprintf(fp4,"	%d %s %s\n",record[b+x].problem_id,record[b+x].date,record[b+x].time);
					y=1;
				} 
				if(y) b=b+s[b];
			}				
		char start_date[301][66],start_time[301][66],end_date[301][66],end_time[301][66]; 				
		int L_time[301],pass_problem[301];	
		for(e=0,f=0;f<i;f++)
		{
			if(record[f].id!=record[f+1].id) 
			{
				e++;
				strcpy(end_date[e],record[f].date);
				strcpy(end_time[e],record[f].time);
				strcpy(start_date[e+1],record[f+1].date);
				strcpy(start_time[e+1],record[f+1].time);								
			}
			pass_problem[e]++;
		}		
		strcpy(start_date[0],record[0].date);
		strcpy(start_time[0],record[0].time);
		strcpy(end_date[0],record[53].date);
		strcpy(end_time[0],record[53].time);
		pass_problem[0]=pass_problem[0]+1;		
		fprintf(fp2,"ID 	开始时间	结束时间 总时长（min） 过题数 \n");
		fprintf(fp2,"******************************************************\n");
		fprintf(fp2,"%d %s %s %s %s %d  %d\n",record[0].id,start_date[0],start_time[0],end_date[0],end_time[0],f1(start_date[0],start_time[0],end_date[0],end_time[0]),pass_problem[0]);		
		for(e=1,j=0;j<i-2;j++)
		{
			
			fprintf(fp2,"	%d 		%s %s\n",record[j].problem_id,record[j].date,record[j].time);
			if(record[j].id!=record[j+1].id)
			{
				fprintf(fp2,"******************************************************\n");
				fprintf(fp2,"\n");				
				fprintf(fp2,"ID 	开始时间	结束时间 总时长（min） 过题数 \n");
				fprintf(fp2,"******************************************************\n");
				fprintf(fp2,"%d %s %s %s %s %d %d\n",record[j+1].id,start_date[e+1],start_time[e+1],end_date[e+1],end_time[e+1],f1(start_date[e+1],start_time[e+1],end_date[e+1],end_time[e+1]),pass_problem[e]);				
				e++;
			}
		}
		fprintf(fp2,"******************************************************\n");	
		printf("请老师再次耐心的等待20秒钟!\n");  			
		int p,q,r,R;
		for(p=0;p<i;p++)/**///按照problem_id升序顺序，给每道题的提交时间按先后顺序排序  
		{
			for(q=0;q<i-p-1;q++)
			{
				if(record[q-1].problem_id>record[q].problem_id)
				{
					r=record[q-1].problem_id;
					record[q-1].problem_id=record[q].problem_id;
					record[q].problem_id=r;
					strcpy(t,record[q-1].date);
					strcpy(record[q-1].date,record[q].date);
					strcpy(record[q].date,t);
					strcpy(tt,record[q-1].time);
					strcpy(record[q-1].time,record[q].time);
					strcpy(record[q].time,tt);
					R=record[q-1].id;
					record[q-1].id=record[q].id;
					record[q].id=R;
				}
			}
		}
		printf("这又是一次排序，过程比较漫长还请老师体谅。\n");		
		for(e=0;e<i-1;e++)
		{
			for(f=0;f<i-e-1;f++)
			{
				if(record[f-1].problem_id==record[f].problem_id&&(strcmp(record[f-1].date,record[f].date)>0))
				{
					strcpy(t,record[f-1].date);
					strcpy(record[f-1].date,record[f].date);
					strcpy(record[f].date,t);
					R=record[f-1].id;
					record[f-1].id=record[f].id;
					record[f].id=R;
					strcpy(tt,record[f-1].time);
					strcpy(record[f-1].time,record[f].time);
					strcpy(record[f].time,tt);
					
				}
				if(record[f-1].problem_id==record[f].problem_id&&(strcmp(record[f-1].date,record[f].date)==0)&&(strcmp(record[f-1].time,record[f].time)>0))
				{
					strcpy(t,record[f-1].time);
					strcpy(record[f-1].time,record[f].time);
					strcpy(record[f].time,t);					
					R=record[f-1].id;
					record[f-1].id=record[f].id;
					record[f].id=R;
				}				
			}
			
		}/**/ 
		printf("万分感谢老师的再次配合！\n");
		int grade[301]={0},fenshu[66666];
		for(e=0,q=0;q<i;q++)
		{	
			 if(e==0) fenshu[q]=32;					
			 if(e>0&&e<12) fenshu[q]=32;
			 if(e>=12&&e<24) fenshu[q]=16;
			 if(e>=24&&e<48) fenshu[q]=8;
			 if(e>=48&&e<96) fenshu[q]=4;
			 if(e>=96&&e<192) fenshu[q]=2;
			 if(e>=192) fenshu[q]=1;
			 if(record[q].problem_id!=record[q+1].problem_id) e=0;			 
			 if(record[q].problem_id==record[q+1].problem_id) e++;							
		}
			 	
		for(f=0;f<300;f++)
		{
				for(p=0;p<i;p++)
			{		
				if(record[p].id==f+1) grade[f]+=fenshu[p];
			}			
		}
		int a,ID[301],temp,TEMP;
		for(a=1,j=0;j<300;j++)
		{
			ID[j]=a;
			a++;
		}
		for(f=0;f<300-1;f++)
		{
			for(e=0;e<300-f-1;e++)
			{
				if(grade[e]<grade[e+1])
				{
					temp=grade[e];
					grade[e]=grade[e+1];
					grade[e+1]=temp;
					TEMP=ID[e];
					ID[e]=ID[e+1];
					ID[e+1]=TEMP;
				} 
			}
		}
	
		int score[301];		
		for(j=0;j<300;j++)
		{
			score[j]=round(100+(log(1+1.0*(grade[j]-grade[0])/grade[0]))*10);		
		}		
		fprintf(fp3,"排名 用户ID 积分 成绩\n");
		for(j=0;j<300;j++)		
		{
			fprintf(fp3,"%3d   %3d   %4d %3d\n",j+1,ID[j],grade[j],score[j]);
		}
		printf("老师，现在您可以按任意键关闭窗口了!\n");		
		getchar();		
		fclose(fp1);
		fclose(fp2);
		fclose(fp3); 
	return 0;
} 
