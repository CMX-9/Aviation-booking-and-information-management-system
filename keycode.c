#include "manage.h"
/*管理员主界面选择功能函数，对航班信息进行修改、添加、删除操作主函数*/
void gmainwork(MOUSE *mouse) 
{
   int flag;
  while(1)
  {
	   Pscr1();
	   mouse_reset(mouse);
	   flag=gmainch1(mouse);
	   switch(flag)
	   {
		 case ADD_XIU:
			 workch(mouse);    //添加或者修改航班信息
			 break;
		 case DELETPL:
			 del_work(mouse);  //删除航班信息
			 break;
		 case G_CHECK:
			 Pcheck(mouse);    //查看售票情况
		}
	   if(flag==BACK) break;   //返回
   }
}



/*管理员操作主界面鼠标选择*/
int gmainch1(MOUSE *mouse)  
{
		int a[4];
		while(1)
		{
			a[0]=chshow(mouse,170,160,420,210);
			a[1]=chshow(mouse,480,160,740,210);
			a[2]=chshow(mouse,850,170,920,200);
			a[3]=chshow(mouse,850,315,980,350);
			if(a[0]==ANXIA)   return ADD_XIU;   //点击添加或者修改航班信息
			if(a[1]==ANXIA)   return DELETPL;   //点击删除航班信息
			if(a[2]==ANXIA)   return BACK;      //点击返回
			if(a[3]==ANXIA)   return G_CHECK;   //点击查看售票情况
		}
}


/*添加、修改界面功能选择函数*/
int gmainch2(MOUSE *mouse,int *t,char pathname[20][35],char datetime[20][12])
{
	int m=0;
	while(1)
	{
		xianshi(mouse,(*t),ADDPL,pathname,datetime);     		  //显示航班信息
		datech(mouse,t,&m,ADDPL);       		                  //功能选择
		if(m==ADDPL)     return  ADDPL;
		if(m==XIUGAI)    return XIUGAI;
		if(m==BACK) 	 return BACK;
		if(m==ADD_PAGE)  return ADD_PAGE;
		if(m==DATE_XIU)  return DATE_XIU;
		if(m==UPDATE)    return UPDATE;
	}
}


/*删除界面功能选择函数*/
int gmainch3(MOUSE *mouse,int *t,char pathname[20][35],char datetime[20][12])
{
	int m=0;
	while(1)
	{
		xianshi(mouse,(*t),DELETPL,pathname,datetime);			//显示航班信息
		datech(mouse,t,&m,DELETPL);				//功能选择
		if(m==ADDPL)     return DELETPL;
		if(m==XIUGAI) 	 return UPDATE;
		if(m==DEL_PAGE)  return DEL_PAGE;
		if(m==BACK)  	 return BACK;
	}
}

/*添加或者修改航班信息功能函数*/
void workch(MOUSE *mouse)
{
	FILE *fp;
	PLAINFOR *plainfor;
	int r,c,m,ch,flag;
	int t=1;
	char pathname[20][35];
	char pathname2[20][35];
	char datetime[20][12];
     /*将存储不同日期的航班路径写入pathname，存储不同日期出发地及到达地的数字文件路径存入pathname2,所有航班日期写入datetime*/
	 update(pathname,pathname2,datetime);                          
	 bar_(70,95,210,125,-1);
	 while(1)
	 {
		 flag=gmainch2(mouse,&t,pathname,datetime);  	               				 		 //功能选择函数
		 if(flag==BACK) 			                                        		 		 //返回
		{
			break;
		}
		 plainfor=(PLAINFOR *)malloc(2*(sizeof(PLAINFOR)));         						 //存储添加、修改的航班信息
		 if(plainfor==NULL)
		 {
			printf("cann't creat memory");
			exit(1);
		 }
		 plainfor[1].name[0]='\0';
		 plainfor[1].startP[0]='\0';
		 plainfor[1].arriveP[0]='\0';
		 plainfor[1].startT[0]='\0';
		 plainfor[1].arriveT[0]='\0';
		 plainfor[1].num[0]='\0';
		 plainfor[1].price[0]='\0';
		 plainfor[1].datetime[0]='\0';
			switch(flag)
			{
			 case ADDPL:      //添加航班信息
				 r=rowch(mouse,t,pathname,flag);
				while(1)
				 {
					  c=colch(mouse,r);
					 switch(c)
					 {
						  case 1:
							  add1(mouse,&plainfor[0],r,flag);              				  //添加航班号
							  break;
						  case 2:
							  add2(mouse,&plainfor[0],r,0,155,310,flag);     				  //添加出发地点
							  break;
						  case 3:
							  add2(mouse,&plainfor[0],r,0,310,455,flag);    		 		  //添加到达地点
							  break;
						  case 4:
							  add4(mouse,&plainfor[0],r,0,455,595,flag);     		  		  //添加出发时间
							  break; 
						  case 5:
							  add4(mouse,&plainfor[0],r,0,595,715,flag);             		  //添加到达时间
							  break;
						  case 6:
							  add6(mouse,&plainfor[0],r,flag);              				   //添加最大载客数
							  break;
						  case 7:
							  add7(mouse,&plainfor[0],r,flag);           			 		   //添加价格
							  break;
						  case 8:
							  ch=changech(mouse);                                      		    //选择是否添加
							  c=add8(mouse,&plainfor[0],t,ch,pathname,pathname2,datetime);      //选择添加后的文件操作，返回11
							  break;
						 
						  
					 }
					 if(c==11)  break;                                      					 //添加完毕后返回添加、修改界面
				}
		   break;

		   case XIUGAI:    //修改航班信息
				 r=rowch(mouse,t,pathname,flag);
				 while(1)
				 {
					  c=colch(mouse,r);
					  switch(c)
					  {
						  case 1:
							  add1(mouse,&plainfor[1],r,flag);               					 //修改航班号
							  break;
						  case 2:
							  add2(mouse,&plainfor[1],r,c,155,310,flag);      					//修改出发地点
							  break;
						  case 3:
							  add2(mouse,&plainfor[1],r,c,310,455,flag);     					 //修改到达地点
							  break;
						  case 4:
							  add4(mouse,&plainfor[1],r,c,455,595,flag);     					 //修改出发时间
							  break;
						  case 5:
							  add4(mouse,&plainfor[1],r,c,595,715,flag);      					 //修改到达时间
							  break;
						  case 6:
							  add6(mouse,&plainfor[1],r,flag);              				     //修改最大载客量
							  break;
						  case 7:
							  add7(mouse,&plainfor[1],r,flag);               					  //修改价格
							  break;
						  case 8:
							  ch=changech(mouse);                             					  //选择是否修改
							  c=xiugai(&plainfor[1],t,r,ch,pathname,pathname2);  				  //选择修改后的文件操作，返回11
							  break;
							  
					   }
					  if(c==11)	  break;                                       					  //修改完毕后返回添加、修改界面
				 }
		  break;
		  case ADD_PAGE:      //加页
				  ch=changech(mouse);
				  if(ch==9)
				  {
					  add_page(mouse,&t,pathname,pathname2,datetime);
					  break;
				  }
				  if(ch==10)  break;
		  case DATE_XIU:	  //修改航班日期
				  date_ch(mouse,&plainfor[1],t,XIUGAI,datetime,pathname);
				  break;
		  case UPDATE:		  //更新
				  update(pathname,pathname2,datetime);
				  break;
			}
		free(plainfor);
	 }
}

/*更新航班信息函数*/
void update(char pathname[20][35],char pathname2[20][35],char datetime[20][12])
{
	FILE *fp;
	int i;
	int count0,count1;
	
	fp=fopen("plainfor\\datetime.txt","r");
	fscanf(fp,"%d",&count1);
	for(i=0;i<count1;i++)
	fscanf(fp,"%s",datetime[i]);
	fclose(fp);

	fp=fopen("plainfor\\pl_path.txt","r");
	if(fp==NULL)  
	{
		put_asc(0,0,1,1,"can't open",0); 
		delay(2000); 
		fclose(fp);
	}
	else if(fp!=NULL)
	{
		fscanf(fp,"%d",&count0);
		for(i=0;i<count0;i++)
		{
			fscanf(fp,"%s",pathname[i]);
		}
		fclose(fp);
	}
	
	fp=fopen("plainfor\\ck_path.txt","r");
	if(fp==NULL)  
	{ 
		put_asc(0,0,1,1,"can't open",0);
		delay(2000); 
		fclose(fp);
	}
	else if(fp!=NULL)
	{
		fscanf(fp,"%d",&count0);
		for(i=0;i<count0;i++)
		{
			fscanf(fp,"%s",pathname2[i]);
		}
		fclose(fp);
	}
}

/*添加或修改航班号*/	
int add1(MOUSE *mouse,PLAINFOR *plainfor,int r,int flag)  
{
	char str[2];
    char ac;
	int n1=0;
	int pos1=90;
	str[1]='\0';
	mouse_recover(mouse);  
	if(flag==XIUGAI) 
	bar_(77,(189+55*(r-1)),146,(223+55*(r-1)),-1); 
	while(bioskey(1))
    { 
        getch();
    }
   /*该循环用于输入航班号，当输入回车键时退出循环*/
    while((ac=getch())!=13)   
    {
        /*若输入的为0-9，a-z，则进行相关操作，且位数最多为3位*/
        if(((ac>='0'&&ac<='9')||(ac>='a'&&ac<='z'))&&n1<3)
        {
            plainfor->name[n1++]=ac;
            str[0]=ac;
            put_asc(pos1,(200+55*(r-1)),1,1,str,0);
            pos1+=10;        
        }
        /*按下backspace时后退一位*/
		else if(ac==8&&n1>=1&&pos1>77)
        {
             n1--;
             pos1-=10;
             bar_(pos1,(189+55*(r-1)),pos1+10,(223+55*(r-1)),-1);       
        }
    }
     plainfor->name[n1]='\0';    //将用户名的最后一个元素设置为\0，方便用fscanf函数	
	 mouse_reset(mouse); 
}  

/*添加或修改航班出发地点及到达地点*/	
int add2(MOUSE *mouse,PLAINFOR *plainfor,int r,int c,int x1,int x2,int flag) 
{
	int t1,t2,t3,t4,t5,t6,t7,t8,t9,ch;
	if(flag==XIUGAI&&(c==2))  
	{
		bar_(162,(189+55*(r-1)),302,(223+55*(r-1)),-1); 
	}
	if(flag==XIUGAI&&(c==3))  
	{
		bar_(317,(189+55*(r-1)),447,(223+55*(r-1)),-1); 
	}
	while(1)
	{
		ch=chshow(mouse,x1,(180+55*(r-1)),x2,(230+55*(r-1)));
		if(ch==ANXIA) break;
	}
	
    bar_(55,10,965,40,-1);  
	dishz(57,20,"请选择地点",0);
	dishz(167,20,"武汉",0);
	dishz(217,20,"上海",0);	
	dishz(267,20,"广州",0);	
	dishz(317,20,"杭州",0);	
	dishz(367,20,"云南",0);	
	dishz(417,20,"江苏",0);	
	dishz(467,20,"深圳",0);	
	dishz(517,20,"北京",0);	
	dishz(567,20,"厦门",0);	
	while(1)
	{
		t1=chshow(mouse,160,10,215,40);
		t2=chshow(mouse,210,10,265,40);
		t3=chshow(mouse,260,10,315,40);
		t4=chshow(mouse,310,10,365,40);
		t5=chshow(mouse,360,10,415,40);
		t6=chshow(mouse,410,10,465,40);
		t7=chshow(mouse,460,10,515,40);
		t8=chshow(mouse,510,10,565,40);
		t9=chshow(mouse,560,10,615,40);
		if(t1==ANXIA)
		{
			mouse_recover(mouse);
			dishz((x1+20),(195+55*(r-1)),"武汉",0);
			if(x1==155) strcpy(plainfor->startP,"武汉");
			if(x1==310) strcpy(plainfor->arriveP,"武汉");
			break;
		}
		if(t2==ANXIA)
		{
			mouse_recover(mouse);
			dishz((x1+20),(195+55*(r-1)),"上海",0);	
			if(x1==155) strcpy(plainfor->startP,"上海");
			if(x1==310) strcpy(plainfor->arriveP,"上海");	
			break;
		}
		if(t3==ANXIA)
		{
			mouse_recover(mouse);
			dishz((x1+20),(195+55*(r-1)),"广州",0);	
			if(x1==155) strcpy(plainfor->startP,"广州");
			if(x1==310) strcpy(plainfor->arriveP,"广州");	
			break;
		}
		if((t4==ANXIA)||(t5==ANXIA)||(t6==ANXIA)||(t7==ANXIA)||(t8==ANXIA)||(t9==ANXIA))
		{
			mouse_recover(mouse);
			dishz(20,45,"该地点暂时无航班站点",0);
			delay(1500);
			bar_(15,40,250,60,0x64bd);
		}
	}
	
	 bar_(55,10,965,40,0x64bd);  
	 mouse_reset(mouse);
}  

/*添加或修改航班的起飞时间及到达时间*/	    
int add4(MOUSE *mouse,PLAINFOR *plainfor,int r,int c,int x1,int x2,int flag)	 
{
	char str[2];
	char time[7];
	char ch,ac;
	int n1=0;
	int pos1=(x1+20);
	if(flag==XIUGAI&&(c==4))                                        //添加或者修改起飞时间
	{
		bar_(462,(189+55*(r-1)),548,(223+55*(r-1)),-1); 
	}
	if(flag==XIUGAI&&(c==5))									    //添加或者修改到达时间
	{
		bar_(602,(189+55*(r-1)),708,(223+55*(r-1)),-1); 
	}
	str[1]='\0';
	while(1)
	{
		ch=chshow(mouse,x1,(180+55*(r-1)),x2,(230+55*(r-1)));
		if(ch==ANXIA) break;
	}
	mouse_recover(mouse);   
	while(bioskey(1))
    {
        getch();
    }
     /*该循环用于输入起飞时间及到达时间，当输入回车键时退出循环*/
    while((ac=getch())!=13&&n1<5)    
    {
        if((ac>='0'&&ac<='2')&&n1<1)
        {
            time[n1++]=ac;
            str[0]=ac;
            put_asc(pos1,(200+55*(r-1)),1,1,str,0);
            pos1+=10;       
        }
		else if((ac>='0'&&ac<='9')&&n1==1&&(time[0]=='0'||time[0]=='1'))
        {
            time[n1++]=ac;
            str[0]=ac;
            put_asc(pos1,(200+55*(r-1)),1,1,str,0);
            pos1+=10;       
        }
		else if((ac>='0'&&ac<='4')&&n1==1&&(time[0]=='2'))
        {
            time[n1++]=ac;
            str[0]=ac;
            put_asc(pos1,(200+55*(r-1)),1,1,str,0);
            pos1+=10;        
        }
		else if((ac==':')&&n1==2)
        {
            time[n1++]=ac;
            str[0]=ac;
            put_asc(pos1,(200+55*(r-1)),1,1,str,0);
            pos1+=10;       
        }
		else if((ac>='0'&&ac<='6')&&n1==3)
        {
            time[n1++]=ac;
            str[0]=ac;
            put_asc(pos1,(200+55*(r-1)),1,1,str,0);
            pos1+=10;        
        }
		else if((ac=='0')&&n1==4&&(time[3]=='6'))
        {
            time[n1++]=ac;
            str[0]=ac;
            put_asc(pos1,(200+55*(r-1)),1,1,str,0);
            pos1+=10;        
        }
		else if((ac>='0'&&ac<='9')&&n1==4&&(time[3]>='0'&&time[3]<='5'))
        {
            time[n1++]=ac;
            str[0]=ac;
            put_asc(pos1,(200+55*(r-1)),1,1,str,0);
            pos1+=10;      
        }
        /*按下backspace时后退一位*/
		else if(ac==8&&n1<=5)
        {
             n1--;
             pos1-=10;
             bar_(pos1,(189+55*(r-1)),pos1+10,(223+55*(r-1)),-1);      
        }
    }
      time[n1]='\0';   													 //将用户名的最后一个元素设置为\0，方便用fscanf函数	
	  if(x1==455)   strcpy(plainfor->startT,time);
	  if(x1==595)   strcpy(plainfor->arriveT,time);
	  mouse_reset(mouse);
	  
}


 /*添加或修改航班的最大载客数*/
int add6(MOUSE *mouse,PLAINFOR *plainfor,int r,int flag)	  
{
	char str[2];
	char numm[5];
	char ch,ac;
	int n1=0;
	int pos1=742;
	str[1]='\0';
	if(flag==XIUGAI)  
	{
		bar_(722,(189+55*(r-1)),847,(223+55*(r-1)),-1); 
	}
	while(1)
	{
		ch=chshow(mouse,715,(180+55*(r-1)),855,(230+55*(r-1)));
		if(ch==ANXIA) break;
	}
	mouse_recover(mouse);  
	while(bioskey(1))
    {
        getch();
    }
     /*该循环用于输入最大载客数，当输入回车键时退出循环*/
    while((ac=getch())!=13)     
    {
        if((ac>='0'&&ac<='9')&&n1<3)
        {
            numm[n1++]=ac;
            str[0]=ac;
            put_asc(pos1,(200+55*(r-1)),1,1,str,0);
            pos1+=10;        
        }
        /*按下backspace时后退一位*/
		if(ac==8&&n1>=1)
        {
			 n1--;
			 pos1-=10;
		     bar_(pos1,(189+55*(r-1)),pos1+10,(223+55*(r-1)),-1);       
		}
	}
	numm[n1]='\0';
	strcpy(plainfor->num,numm);
	mouse_reset(mouse);
}


/*添加或修改航班的价格*/
int add7(MOUSE *mouse,PLAINFOR *plainfor,int r,int flag)	   
{
	
	char str[2];
	char pric[5];
	char ch,ac;
	int n1=0;
	int pos1=882;
	str[1]='\0';
	if(flag==XIUGAI)  
	{
		bar_(862,(189+55*(r-1)),948,(223+55*(r-1)),-1); 
	}
	while(1)
	{
		ch=chshow(mouse,855,(180+55*(r-1)),955,(230+55*(r-1)));
		if(ch==ANXIA) break;
	}
	mouse_recover(mouse);   
	while(bioskey(1))
    {
        getch();
    }
     /*该循环用于输入最大载客数，当输入回车键时退出循环*/
    while((ac=getch())!=13)    
    {
        /*输入*/
        if((ac>='0'&&ac<='9')&&n1<3)
        {
            pric[n1++]=ac;
            str[0]=ac;
            put_asc(pos1,(200+55*(r-1)),1,1,str,0);
            pos1+=10;        
        }
        /*按下backspace时后退一位*/
		if(ac==8&&n1>=1)
        {
             n1--;
			 pos1-=10;
             bar_(pos1,(189+55*(r-1)),pos1+10,(223+55*(r-1)),-1);      
        }
	}
	pric[n1]='\0';
	strcpy(plainfor->price,pric);
	mouse_reset(mouse);
}

void date_ch(MOUSE *mouse,PLAINFOR *plainfor,int t,int flag,char datetime[20][12],char pathname[20][35])
{
     FILE *fp;
    char str[2];
	char tim[12];
	char ch,ac;
	int n1=0,count,i=0,j;
	int pos1=77;
	char timee[35];
	char txtname[9][35];
	if(t>2)             
	{
		str[1]='\0';
		
		if(flag==XIUGAI)  
		{
			while(1)
	        {
				count=chshow(mouse,70,95,210,125);
				if(count==ANXIA) break;
	        }
			mouse_recover(mouse);
			bar_(70,95,210,125,-1); 
			Rectangular(70,95,210,125,0);
		}
		while(bioskey(1))
		{
			getch();
		}
	    /*该循环用于输入日期，当输入回车键时退出循环*/
		while((ac=getch())!=13)    
		{
			/*输入*/
			if((ac>='0'&&ac<='9')&&n1<10&&n1!=4&&(n1!=7))
			{
				tim[n1++]=ac;
				str[0]=ac;
				put_asc(pos1,105,1,1,str,0);
				pos1+=10;        
			}
			if(((n1==4)||(n1==7))&&(ac=='.'))
			{
				tim[n1++]=ac;
				str[0]=ac;
				put_asc(pos1,105,1,1,str,0);
				pos1+=10;        
			}
			/*按下backspace时后退一位*/
			if(ac==8&&n1>=1)
			{
				 n1--;
				 pos1-=10;
				 bar_(pos1,102,pos1+10,118,-1);      
			}
		}
		tim[n1]='\0';
		mouse_reset(mouse);
		strcpy(plainfor->datetime,tim);
		if(flag==XIUGAI)                                                            //修改日期                                                 
		{
			fp=fopen("plainfor\\datetime.txt","r+");
			if(fp!=NULL)
			{
				fscanf(fp,"%d",&count);
				for(i=0;i<count;i++)
				{
					if(i==t)   
					{
						strcpy(datetime[i],(plainfor->datetime));
						fscanf(fp,"%s",timee);
					}
					else       fscanf(fp,"%s",datetime[i]);
				}
				fclose(fp);
			}
			
			fp=fopen("plainfor\\datetime.txt","w");
			fprintf(fp,"%d\n",count);
			for(i=0;i<count;i++)
			{
				  fprintf(fp,"%s\n",datetime[i]);
			}
			fclose(fp);
			strcpy(datetime[t],tim);
			
			fp=fopen(pathname[t],"r+");                                                  //修改各个航班信息的日期
			if(fp!=NULL)
			{
				fscanf(fp,"%d",&count);
				if(count!=0)
				{
					for(i=0;i<count;i++)
					{
							fscanf(fp,"%s",txtname[i]);
					}
				}
			   fclose(fp);
			}
				
			for(i=0;i<count;i++)
			{
			   fp=fopen(txtname[i],"r+");
			   if(fp!=NULL)
			   {
				   fseek(fp,-15L,2);
				   fprintf(fp,"%c",'\n');
				   fseek(fp,0L,1);
				   fprintf(fp,"%s\n",datetime[t]);
				   fclose(fp);
			   }
			}
			
		}
		else if(flag==ADDPL)														 //添加日期
		{
			fp=fopen("plainfor\\datetime.txt","r+");
			if(fp!=NULL)
			{
				fscanf(fp,"%d",&count);
				count+=1;
				fseek(fp,0L,0);
				fprintf(fp,"%d\n",count);
				fseek(fp,0L,2);
				fprintf(fp,"\n%s",plainfor->datetime);
				fclose(fp);
				strcpy(datetime[t],tim);
	   
			}
		}
	}
	if(t<3)                                                 //方便模拟订票
	{
		dishz(10,25,"该日期暂不能修改",0);
		delay(1500);
		bar_(5,20,200,50,0x64bd);
	}
}


/*加页（添加不同日期的航班）函数*/
void add_page(MOUSE *mouse,int *t,char pathname[20][35],char pathname2[20][35],char datetime[20][12])		   
{
	char ch,count;
	int ch_count=0;
	FILE *fp;
	char txtname[35],name[4];
	PLAINFOR plainfor;
	Pscr2(ADDPL);
	mouse_reset(mouse);
	(*t)+=1;                                                     //加页后，对应不同日期的航班标志加一
	dishz(0,30,"请填写航班起飞日期",0);
	delay(1500);
	bar_(0,40,250,50,0x64bd);
	while(1)
	{
		ch=chshow(mouse,70,95,210,125);
		if(ch==ANXIA) break;
	}
	
	date_ch(mouse,&plainfor,(*t),ADDPL,datetime,pathname);			     //添加航班日期
	
	ch_count=(*t);
	itoa(ch_count,name,10); 							         //以动态变化的t作为以航班路径为内容的文件名
	strcpy(txtname,"plainfor\\pl_");                  
	strcat(txtname,name);
	strcat(txtname,".txt");
	fp=fopen("plainfor\\pl_path.txt","r+");                      //将新加页的航班路径写入总航班路径文件
	if(fp!=NULL)
	{
       fscanf(fp,"%d",&count);
	   count+=1;
	   fseek(fp,0,0);
	   fprintf(fp,"%d\n",count);
	   fseek(fp,0,2);
       fprintf(fp,"\n%s",txtname);
	   fclose(fp);
	   strcpy(pathname[(*t)],txtname);                             //将增添的航班路径存入路径数组，以便动态显示
	}
	
	fp=fopen(txtname,"w");                        				   //创建新加页的存储航班路径的文件
	fprintf(fp,"%d\n",0);
	fclose(fp);
	
	strcpy(txtname,"plainfor\\ck_");
	strcat(txtname,name);
	strcat(txtname,".txt");
	fp=fopen("plainfor\\ck_path.txt","r+");                        //将新加页的航班数字路径写入总航班数字路径文件
	if(fp!=NULL)
	{
       fscanf(fp,"%d",&count);
	   count+=1;
	   fseek(fp,0,0);
	   fprintf(fp,"%d\n",count);
	   fseek(fp,0,2);
       fprintf(fp,"\n%s",txtname);
	   fclose(fp);
	   strcpy( pathname2[(*t)],txtname);                           //将将增添的航班路径存入数字路径数组
	}
	
	fp=fopen(txtname,"w");                                         //创建新加页的存储航班出发地、到达地（对应数字）的文件
	fprintf(fp,"%d\n",0);
	fclose(fp);
}
	
	
/*用于将添加的航班信息及航班路径写入文件*/
int add8(MOUSE *mouse,PLAINFOR *plainfor,int t,int ach,char pathname[20][35],char pathname2[20][35],char datetime[20][12])
{
	FILE *fp;
    int t1,t2;
	int count=0;
	char b[3];
	char textname[35];
	b[2]='\0';
	if(ach==10) return 11;
	strcpy(textname,"plainfor\\");           //生成新添加的航班路径
	strcat(textname,plainfor->name);
	strcat(textname,".txt");
	if(strcmp(plainfor->startP,"武汉")==0)     b[0]='1';
	if(strcmp(plainfor->startP,"广州")==0)     b[0]='2';
	if(strcmp(plainfor->startP,"上海")==0)     b[0]='3';
	if(strcmp(plainfor->arriveP,"武汉")==0)    b[1]='1';
	if(strcmp(plainfor->arriveP,"广州")==0)    b[1]='2';
	if(strcmp(plainfor->arriveP,"上海")==0)    b[1]='3';
	fp=fopen(pathname2[t],"r+");            //打开存储出发地及到达地的数字文件并修改
	if(fp==NULL)                            //存储航班路径的文件为空，则重新创建文件
	{
		fclose(fp);
		fp=fopen(pathname2[t],"w+");
		fprintf(fp,"%d\n",count);
		fseek(fp,0,0);
	}
	fscanf(fp,"%d",&count);
	++count;
	fseek(fp,0,0);
	fprintf(fp,"%d\n",count);
	fseek(fp,0,2);
	fprintf(fp,"\n%s",b);
	fclose(fp);
	fp=fopen(pathname[t],"r+");
	if(fp==NULL)                           //存储航班路径的文件为空，则重新创建文件
	{
		fclose(fp);
		fp=fopen(pathname[t],"w+");
		fprintf(fp,"%d\n",count);
	}
	fscanf(fp,"%d",&count);
	++count;
	fseek(fp,0,0);
	fprintf(fp,"%d\n",count);
	fseek(fp,0,2);
	fprintf(fp,"\n%s",textname);             //将新加的航班加到航班路径文件的末尾
	fclose(fp);
	fp=fopen(textname,"w");
	if(fp==NULL)                            //生成新添加航班的文件
	{
		dishz(0,0,"生成文件失败",0);
		bar_(0,0,200,20,0x64bd);
		fclose(fp);
    }
	else if(fp!=NULL)
	{
		fprintf(fp,"%s\n",plainfor->name);   
		fprintf(fp,"%s\n",plainfor->startP); 
		fprintf(fp,"%s\n",plainfor->arriveP); 
		fprintf(fp,"%s\n",plainfor->startT); 
		fprintf(fp,"%s\n",plainfor->arriveT); 
		fprintf(fp,"%s\n",plainfor->num);
		fprintf(fp,"%s\n",plainfor->price);
	    fprintf(fp,"%s\n",datetime[t]);
		fprintf(fp,"%s\n","0");              //新添加的航班，售票数自动为0
		fclose(fp);
	}
	
	return 11;
}


/*用于将修改的航班信息及修改的航班路径写入文件*/ 
int xiugai(PLAINFOR *plainfor,int t,int r,int xch,char pathname[20][35],char pathname2[20][35]) 
{
	FILE *fp;
	int i,count;
	char textname1[35],textname[35];    			 //textname用于存储原有航班路径，textname1用于存储修改后的航班路径，textname2用于存储所有这一日期的航班路径
	char textname2[10][35];
	char a[10][3],b[3];                              //a[][]存储出发地、到达地对应的数字文件
	PLAINFOR plainfo;  							 	//用于取出文件原有航班
	b[2]='\0';
	if(xch==10)  return 11;             			 //选择不添加航班
	strcpy(textname1,"plainfor\\");      			 //修改的航班路径生成
	strcat(textname1,plainfor->name);
	strcat(textname1,".txt");
	fp=fopen(pathname[t],"r+");
	if(fp==NULL)                          			//打开存储航班信息路径的文件
	{
		  dishz(0,0,"不存在所修改的航班",0);
		  bar_(0,0,200,20,0x64bd);
		  fclose(fp);
	}
	else if(fp!=NULL)                   		 	//路径文件中存在所修改的航班路径
	{
		fscanf(fp,"%d",&count);
		for(i=0;i<count;i++)
		{
		   fscanf(fp,"%s",textname2[i]);
		}
		strcpy(textname,textname2[r-1]);
		if((strcmp(textname1,textname2[r-1])!=0)&&(plainfor->name[0]!='\0'))     //如果航班号修改，则相应的航班路径也要改
		{
		    strcpy(textname2[r-1],textname1);
		} 
		fclose(fp);
	}
	remove(pathname[t]);
	fp=fopen(pathname[t],"w");                      //打开存储航班信息路径的文件,不存在则重新建立
	fprintf(fp,"%d\n",count);
	for(i=0;i<count;i++)
	{
		fprintf(fp,"%s\n",textname2[i]);
	}
	fclose(fp);
	fp=fopen(textname,"r+");
	if(fp!=NULL) 									 //打开存储航班信息路径的文件
	{
		fscanf(fp,"%s",plainfo.name);
		fscanf(fp,"%s",plainfo.startP);
		fscanf(fp,"%s",plainfo.arriveP);
		fscanf(fp,"%s",plainfo.startT);
		fscanf(fp,"%s",plainfo.arriveT);
		fscanf(fp,"%s",plainfo.num);
		fscanf(fp,"%s",plainfo.price);
		fscanf(fp,"%s",plainfo.datetime);
		fscanf(fp,"%s",plainfo.solved);
		remove(textname);
		fclose(fp);
	}
	else if(fp==NULL)
	{
		dishz(0,0,"该航班不存在",0);
		delay(1500);
		bar_(0,0,200,20,0x64bd);
		remove(textname);
		fclose(fp);
	}
	if(plainfor->startP[0]!='\0'&&strcmp((plainfor->startP),"武汉")==0)   b[0]='1';
	if(plainfor->startP[0]!='\0'&&strcmp((plainfor->startP),"广州")==0)   b[0]='2';
	if(plainfor->startP[0]!='\0'&&strcmp((plainfor->startP),"上海")==0)   b[0]='3';
	if(plainfor->arriveP[0]!='\0'&&strcmp((plainfor->arriveP),"武汉")==0)   b[1]='1';
	if(plainfor->arriveP[0]!='\0'&&strcmp((plainfor->arriveP),"广州")==0)   b[1]='2';
	if(plainfor->arriveP[0]!='\0'&&strcmp((plainfor->arriveP),"上海")==0)   b[1]='3';
	if(plainfor->startP[0]=='\0'&&strcmp((plainfo.startP),"武汉")==0)   b[0]='1';
	if(plainfor->startP[0]=='\0'&&strcmp((plainfo.startP),"广州")==0)   b[0]='2';
	if(plainfor->startP[0]=='\0'&&strcmp((plainfo.startP),"上海")==0)   b[0]='3';
	if(plainfor->arriveP[0]=='\0'&&strcmp((plainfo.arriveP),"武汉")==0)   b[1]='1';
	if(plainfor->arriveP[0]=='\0'&&strcmp((plainfo.arriveP),"广州")==0)   b[1]='2';
	if(plainfor->arriveP[0]=='\0'&&strcmp((plainfo.arriveP),"上海")==0)   b[1]='3';
	/*查看那些航班被修改过,没有被修改的项便strcpy*/
	if(plainfor->name[0]=='\0')
	 strcpy(plainfor->name,plainfo.name);
	if(plainfor->startP[0]=='\0')
	 strcpy(plainfor->startP,plainfo.startP);
	if(plainfor->arriveP[0]=='\0')
	 strcpy(plainfor->arriveP,plainfo.arriveP);
	if(plainfor->startT[0]=='\0')
	 strcpy(plainfor->startT,plainfo.startT);
	if(plainfor->arriveT[0]=='\0')
	 strcpy(plainfor->arriveT,plainfo.arriveT);
	if(plainfor->num[0]=='\0')
	 strcpy(plainfor->num,plainfo.num);
	if(plainfor->price[0]=='\0')
	 strcpy(plainfor->price,plainfo.price);
	strcpy(plainfor->datetime,plainfo.datetime);
	strcpy(plainfor->solved,plainfo.solved);
	fp=fopen(textname2[r-1],"w");                              //打开存储航班信息路径的文件
	fprintf(fp,"%s\n",plainfor->name);                    //将修改后的航班信息添加到文件里
	fprintf(fp,"%s\n",plainfor->startP);
	fprintf(fp,"%s\n",plainfor->arriveP);
	fprintf(fp,"%s\n",plainfor->startT);
	fprintf(fp,"%s\n",plainfor->arriveT);
	fprintf(fp,"%s\n",plainfor->num);
	fprintf(fp,"%s\n",plainfor->price);
	fprintf(fp,"%s\n",plainfor->datetime);
	fprintf(fp,"%s\n",plainfor->solved);
	fclose(fp);
	fp=fopen(pathname2[t],"r+");
	if(fp==NULL)                          			//打开存储出发地及到达地的数字文件
	{
		  dishz(0,0,"不存在所修改的航班",0);
		  bar_(0,0,200,20,0x64bd);
		  fclose(fp);
	}
	else if(fp!=NULL)                   		 	//路径文件中存在所修改的航班路径
	{
			fscanf(fp,"%d",&count);
			for(i=0;i<count;i++)
			 fscanf(fp,"%s",a[i]);
			fclose(fp);
	}   
	remove(pathname2[t]);
	fp=fopen(pathname2[t],"w");
	fprintf(fp,"%d\n",count);
	if(strcmp(a[r-1],b)!=0)   strcpy(a[r-1],b);
	for(i=0;i<count;i++)
	{
	   fprintf(fp,"%s\n",a[i]);
	}
	 fclose(fp);
	return 11;
}



/*删除航班信息*/
void del_work(MOUSE *mouse)
{
	int r,dch,t=1,m;
	int flag;
	char pathname[20][35];
	char pathname2[20][35];
	char datetime[20][12];
	update(pathname,pathname2,datetime);

	while(1)
	{
		 flag=gmainch3(mouse,&t,pathname,datetime);                				//功能选择
		 switch(flag)
		 {
		 case DELETPL:     //删除
			 r=rowch(mouse,t,pathname,DELETPL);
			 dch=changech(mouse);
			 dele(t,r,dch,pathname,pathname2);
			 break;
		 case UPDATE:     //更新数据
			  break;
		 case DEL_PAGE:   //删除某页
			 m=changech(mouse);
			 if(m==9)
			 {
				 del_page(&t,pathname,pathname2,datetime);
				 break;
			 }
			 if(m==10)
				 break;
			 }
		 if(flag==BACK)    //返回
		   break;
     }
}


/*删除页函数*/
void del_page(int *t,char pathname[20][35],char pathname2[20][35],char datetime[20][12])
{
	FILE *fp;
	int i,j,count,count1;
	char platxt[9][35];
	char middle1[12],middle2[35],middle3[35];
	
	fp=fopen("plainfor\\datetime.txt","r+");
	if(fp!=NULL)
	{
		fscanf(fp,"%d",&count);
		for(i=0,j=0;i<count;i++)
		{
			if(i!=(*t)) 
			{
				fscanf(fp,"%s",datetime[j]);
				j++;
			}
		    if(i==(*t))   fscanf(fp,"%s",middle1);
		}
		remove(middle1);
		
	}
	count-=1;
	
    fp=fopen("plainfor\\datetime.txt","w");
	fprintf(fp,"%d\n",count);
	for(i=0;i<count;i++)
	{
		  fprintf(fp,"%s\n",datetime[i]);
	}
	fclose(fp);
	
	fp=fopen("plainfor\\pl_path.txt","r+");
	if(fp!=NULL)
	{
		fscanf(fp,"%d",&count);
		for(i=0,j=0;i<count;i++)
		{
			if(i!=(*t))
			{
				fscanf(fp,"%s",pathname[j]);
				j++;
			}
		    if(i==(*t))   fscanf(fp,"%s",middle2);
		}
		
	}
	
	fp=fopen(middle2,"r+");
	if(fp!=NULL)
	{
		fscanf(fp,"%d",&count1);
		if(count1==0) fclose(fp);
		if(count1!=0)
		{
			for(i=0;i<count1;i++)
			{
				fscanf(fp,"%s",platxt[i]);
			}
			for(i=0;i<count1;i++)
			{
				remove(platxt[i]);
			}
		}
		fclose(fp);
	}
	remove(middle2);
	
	count-=1;
	
    fp=fopen("plainfor\\pl_path.txt","w");
	fprintf(fp,"%d\n",count);
	for(i=0;i<count;i++)
	{
	    fprintf(fp,"%s\n",pathname[i]);
	}
	fclose(fp);
	
	
	
	fp=fopen("plainfor\\ck_path.txt","r+");
	if(fp!=NULL)
	{
		fscanf(fp,"%d",&count);
		for(i=0,j=0;i<count;i++)
		{
		    if(i!=(*t)) 
			{
				fscanf(fp,"%s",pathname2[j]);
				j++;
			}
		    if(i==(*t))   fscanf(fp,"%s",middle3);
		}
	}
	
	fp=fopen(middle3,"r+");
	if(fp!=NULL)
	{
		fscanf(fp,"%d",&count1);
		if(count==0) fclose(fp);
		if(count!=0)
		{
			for(i=0;i<count1;i++)
			{
				fscanf(fp,"%s",platxt[i]);
			}
			for(i=0;i<count1;i++)
			{
				remove(platxt[i]);
			}
		}
		fclose(fp);
	}
	remove(middle3);
	
	count-=1;
	
    fp=fopen("plainfor\\ck_path.txt","w");
	fprintf(fp,"%d\n",count);
	for(i=0,j=0;i<count;i++,j++)
	{
		 fprintf(fp,"%s\n",pathname2[j]);
	}
	fclose(fp);
	(*t)-=1;
}


/*用于删除航班信息及航班路径*/
int dele(int t,int r,int dch,char pathname[3][35],char pathname2[3][35])
{
	FILE *fp;
	int t1,t2,i;
	int count=0;
	char textname[10][35];
	char a[10][3];
	if(dch==10) return 10;
	fp=fopen(pathname2[t],"r+");									 //打开存储对应出发地、到达地的数字文件
	if(fp==NULL)
	{
		 dishz(0,0,"所需删除的航班信息不存在",0);
		 bar_(0,0,200,15,0x64bd);
		 fclose(fp);
	}
	else if(fp!=NULL)
	{
		 fscanf(fp,"%d",&count);
		 for(i=0;i<count;i++)
		 fscanf(fp,"%s",a[i]);
	     remove(pathname2[t]);
	}
	fp=fopen(pathname2[t],"w");
		 count-=1;
		 fprintf(fp,"%d\n",count);
		 for(i=0;i<count;i++)
		 {
			 if(i!=(r-1))
			 fprintf(fp,"%s\n",a[i]);
		 }
		 fclose(fp);
	fp=fopen(pathname[t],"r+");									  //打开存储航班信息路径的文件
	if(fp==NULL)
	{
		 dishz(0,0,"所需删除的航班信息不存在",0);
		 bar_(0,0,200,15,0x64bd);
		 fclose(fp);
	}
	else if(fp!=NULL)
	{
		fscanf(fp,"%d",&count);
		for(i=0;i<count;i++)
		{
			fscanf(fp,"%s",textname[i]);
		}
		fclose(fp);
	}
	remove(textname[r-1]);
	count-=1;
	fp=fopen(pathname[t],"w");  							  //重建存储航班信息路径的文件
	fprintf(fp,"%d\n",count);
	for(i=0;i<count;i++)
	{
		if(i!=(r-1))
		fprintf(fp,"%s\n",textname[i]);
	}
	fclose(fp);
	return 10;
}


int Pcheck(MOUSE *mouse)
{
	FILE *fp;
  int t1,t2,t3,t4,t5,n[10];
  int t=1,m=0,x,count,count0,count1,i,j;
  int a[10];                                                 //存储转换后的int型票数
  char num1[10][3];											 //航班号
  char num2[10][15];                                         //票数
  char path[10][35];
  char datetime[20][12];
  char pathname[20][35];
  
  fp=fopen("plainfor\\pl_path.txt","r");
  if(fp!=NULL)
  {
	  fscanf(fp,"%d",&count0);                                 //count0==count1代表不同日期数
	 if(count0!=0)
	 {
		for(i=0;i<count0;i++)
		{
			fscanf(fp,"%s",pathname[i]);
		}
     }		
	 fclose(fp);
  }
  
  fp=fopen("plainfor\\datetime.txt","r");
  if(fp!=NULL)
  {
	  fscanf(fp,"%d",&count1);
	 if(count1!=0)
	 {
		for(i=0;i<count1;i++)
		{
			fscanf(fp,"%s",datetime[i]);
		}
     }		
	 fclose(fp);
  }
  
  while(1)
   {
	  if(m==2) return BACK;                                      //返回
	  Pscr3();
	  mouse_reset(mouse);
	   dishz(300,87,"售票情况（日期：",0);
	   put_asc(460,87,1,1,datetime[t],0);
	   dishz(560,87,"）",0);
	  
	  fp=fopen(pathname[t],"r");
	  if(fp!=NULL) 
	  {
		   fscanf(fp,"%d",&count);                                 //count存储该日期航班数
		   if(count!=0)
		   {
			   for(i=0;i<count;i++)
			   {
				  fscanf(fp,"%s",path[i]);
			   }
		   }
		   else if(count==0)       
		   {
			   dishz(300,300,"该日期暂无航班",0);
			   delay(1500);
		   }
		   
		   fclose(fp);
	 }
	  if(fp==NULL)
	  {
		  dishz(0,0,"文件打开失败了",0);
		  delay(1500);
		  bar_(0,0,200,15,0x64bd);
		  fclose(fp);
	  }
	  if(count!=0)
	  {
		  for(i=0;i<count;i++)
		  {
				fp=fopen(path[i],"r+");
				if(fp!=NULL)
				{
					fscanf(fp,"%s",num1[i]);
					while(!feof(fp))
					fscanf(fp,"%s",num2[i]);
					fclose(fp);
				}
				if(fp==NULL)
				{
					dishz(0,0,"文件打开失败",0); 
					fclose(fp);
				}	
		  }
	  } 
	  if((m==0)&&(count!=0))  //矩形图
	  {
			for(i=0,x=120;i<count;i++,x+=70)
			{
			  n[i]=atoi(num2[i]);
			  if((n[i]<=500)&&(n[i]>0))                                  //已售票数必须小于最大载客数
			  bar_(x,(620-n[i]),(x+50),620,-1);
			  put_asc((x+23),(605-n[i]),1,1,num2[i],0);
			  put_asc((x+23),630,1,1,num1[i],0);
			 
			}
	  }
	  else if((m==1)&&(count!=0))  //折线图
	  {
		    for(i=0,x=120;i<count;i++,x+=70)
			 {
				 put_asc((x+23),630,1,1,num1[i],0);
				 n[i]=atoi(num2[i]);
				   if((n[i]<=500)&&(n[i]>=0))
				   {
				 	 yuan((x+23),(620-n[i]),10,0x8800);
					 put_asc((x+19),(598-n[i]),1,1,num2[i],0);
				   }
			 }
			 for(i=0,x=120;i<count;i++,x+=70)
			 {
				 if(i<(count-1)&&(n[i]<=500)&&(n[i+1]<=500))
				 Line((x+23),(620-n[i]),(x+93),(620-n[i+1]),0);     //画斜线
			 }
	  }
	  while(1)
	  {
		  t1=chshow(mouse,735,105,800,155);   					 
		  t2=chshow(mouse,860,105,930,155);   					 
		  t3=chshow(mouse,880,260,900,280); 					
		  t4=chshow(mouse,880,410,900,430); 					 
		  t5=chshow(mouse,20,19,85,48);         					
		  if(t1==ANXIA&&t>0)  { t-=1; break;}  						//选择上一页
		  if(t2==ANXIA&&(t<(count1-1)))  { t+=1; break;}			//选择下一页
		  if(t3==ANXIA)  { m=0; break;} 							//选择矩形图
		  if(t4==ANXIA)  { m=1; break;}								//选择折线图
		  if(t5==ANXIA)  { m=2; break;} 							//选择返回
	  }
   }
}
