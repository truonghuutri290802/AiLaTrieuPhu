#include <stdio.h>
#include<conio.h>
#include <stdlib.h>
#include<time.h>
#include <string.h>
#include <stdio.h>
#include<windows.h>

int RED = 140;
int WHITE = 15;
int BLUE = 57;
int WIDTH = 700;
int HEIGHT = 500;
int WRONG = 12;
int WRIGHT = 10;
int YELLOW = 14;
int SoCauDatDuoc=0;

// Su dung thu vien Window.h de goi duoc toa do cua x , y tren console . Giup di chuyen chuyen den vi tri bat ki tren console

void textcolor(int x)
{
    HANDLE mau;
    mau = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(mau, x);
}

//---------------------------------------------------------------------------------//
void resizeConsole(int width, int height)
{
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, width, height, TRUE);
}

void gotoxy(int x, int y)
{
    static HANDLE h = NULL;
    if(!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };
    SetConsoleCursorPosition(h,c);
}

void XoaTaiToaDo(int x,int y)
{
    gotoxy(x,y);
    for(int i=0; i<80; i++)
        printf(" ");
}
struct DAPAN
{
    char A[100];
    char B[100];
    char C[100];
    char D[100];
};

struct CAUHOI
{
    char cauHoi[300];
    DAPAN dapAn;
    int ketQua;
};

struct Node
{
    CAUHOI data;
    Node *link;
};

struct List
{
    Node *first, *last;
};

void Init(List &l)
{
    l.first=l.last=NULL;
}
Node *getNode(CAUHOI x)
{
    Node *p= new Node;
    if(p==NULL)
        return NULL;
    p->data=x;
    p->link=NULL;
    return p;
}


void addLast(List &l, Node *new_question)
{
    if(l.first==NULL)
        l.first=l.last=new_question;
    else
    {
        l.last->link=new_question;
        l.last=new_question;
    }
}
//=================================DOC FILE================================//
void doc_File(CAUHOI &c,FILE *f)
{
    char *ch=new char[1000];
    char *str;
    fgets(ch,1000,f);
    str= strtok(ch,",");
    strcpy(c.cauHoi,str);
    str=strtok(NULL,",");
    strcpy(c.dapAn.A,str);
    str=strtok(NULL,",");
    strcpy(c.dapAn.B,str);
    str=strtok(NULL,",");
    strcpy(c.dapAn.C,str);
    str=strtok(NULL,",");
    strcpy(c.dapAn.D,str);
    str=strtok(NULL,",");
    c.ketQua=atoi(str);
}
void doc_DS_CauHoi(List &l){
	FILE *f;
	CAUHOI c;
	Init(l);
	int a;
	srand(time(NULL));
	a=rand()%2;
	if(a==1){
	f=fopen("boCauHoi1.txt","r");
	}else{
	f=fopen("boCauHoi2.txt","r");
	}
	if(f==NULL){
		printf("\nFile khong ton tai");
	}else{
		while(!feof(f))
		{
			doc_File(c,f);
			Node *p = getNode(c);
			addLast(l,p);
		}
	}
	fclose(f);
	printf("\n");
}
//=========================================================================//
void XuatA(char s[])
{

    gotoxy(0,10);
    printf("%s", s);
}

void XuatB(char s[])
{

    gotoxy(42,10);
    printf("%s", s);
}

void XuatC(char s[])
{

    gotoxy(0,15);
    printf("%s", s);
}

void XuatD(char s[])
{

    gotoxy(42,15);
    printf("%s", s);
}

void XuatCauHoi(CAUHOI x)
{

    printf("%s ", x.cauHoi);
    XuatA(x.dapAn.A);
    XuatB(x.dapAn.B);
    XuatC(x.dapAn.C);
    XuatD(x.dapAn.D);
}
void xuat1CauHoi(CAUHOI s)
{
    printf("\n%-s\n%-s\n%-s\n%-s\n%-s\n", s.cauHoi,s.dapAn.A,s.dapAn.B,s.dapAn.C,s.dapAn.D);
    printf("Chon ket qua bang cach nhan phim 1-4(lan luot la cac Dap An A, B, C, D): %d\n",s.ketQua);
}
void xuatDanhSach(List l)
{
	doc_DS_CauHoi(l);
    Node *p = l.first;
    while(p != NULL)
    {
        xuat1CauHoi(p->data);
        p = p->link;
    }
}

void nhapCauHoi(CAUHOI &c)
{
    printf("Nhap cau hoi: ");
    fflush(stdin);
    gets(c.cauHoi);
    printf("Nhap dap an A: ");
    fflush(stdin);
    gets(c.dapAn.A);
    printf("Nhap dap an B: ");
    fflush(stdin);
    gets(c.dapAn.B);
    printf("Nhap dap an C: ");
    fflush(stdin);
    gets(c.dapAn.C);
    printf("Nhap dap an D: ");
    fflush(stdin);
    gets(c.dapAn.D);
    printf("Dap an(1-4 tuong ung voi dap an A-B-C-D): ");
    scanf("%d", &c.ketQua);
}
//=============================QUYEN TRO GIUP================================//
void troGiup_50_50(CAUHOI &c,boolean &help)
{

    if(help==false)
    {
        printf("\n Quyen tro giup da cuoc su dung!");
        printf("\n Vui long su dung quyen tro giup khac!");
        return;
    }
    else
    {
        int a, b;
        gotoxy(0,25);
        printf("\n Hai dap an sai la: ");
        do
        {
            srand(time(NULL));
            a=rand()%4;
            b=rand()%4;
        }while(a==0||a==c.ketQua||b==0||b==c.ketQua||b==a);
        if(a==1&&b==2)
            printf("A va B");
        if(a==1&&b==3)
            printf("A va C");
        if(a==1&&b==4)
            printf("A va D");
        if(a==2&&b==1)
            printf("A va B");
        if(a==3&&b==1)
            printf("A va C");
        if(a==4&&b==1)
            printf("A va D");
        //=============================
        if(a==2&&b==3)
            printf("B va C");
        if(a==2&&b==4)
            printf("B va D");
        if(a==3&&b==2)
            printf("B va C");
        if(a==4&&b==2)
            printf("B va D");
        //=============================
        if(a==3&&b==4)
            printf("C va D");
        if(a==4&&b==3)
            printf("C va D");
        //=============================
        if(a==1||b==1)
            strcpy(c.dapAn.A, "");
        if(a==2||b==2)
            strcpy(c.dapAn.B, "");
        if(a==3||b==3)
            strcpy(c.dapAn.C, "");
        if(a==4||b==4)
            strcpy(c.dapAn.D, "");
        help=false;
    }
}

void goiDienNguoiThan(CAUHOI &q, boolean &help)
{
    if(help==false)
    {
        printf("\n Quyen tro giup nay da duoc su dung!");
        return;
    }
    else
    {
        gotoxy(0,25);
        srand(time(NULL));
        int a =rand()%4;
        if(a==1)
        {
            printf("\nTheo nhung gi toi duoc biet thi toi chac chan la dap an A :)) ");
        }
        else if(a==2)
        {
            printf("\nToi nghi dap an la B");
        }
        else if(a==3)
        {
            printf("\nHinh nhu la C day !");
        }
        else
            printf("\nDap an la D, tin toi di");
    }
}

void hoiYKienKhanGia(CAUHOI &q, boolean &tg3)
{
    if(tg3==false)
    {
        printf("\n Quyen tro giup nay da duoc su dung!");
        return;
    }
    else
    {
        int kq;
        if(q.ketQua == 1 )
            kq = 1;
        if(q.ketQua == 2)
            kq = 2;
        if(q.ketQua == 3)
            kq = 3;
        if(q.ketQua == 4)
            kq = 4;
        gotoxy(0,25);
        int rd,rd1, rd2, rd3;
        srand(time(NULL));
        do
        {
            rd = rand() % 80 + 1;
            rd1 = rand() % (100 - rd) + 1;
            int r = rd + rd1;
            rd2 = rand() % (100 - r) + 1;
            r = rd + rd1 + rd2;
            rd3 = 100 - r;
        }
        while (rd < 50 || rd + rd1 + rd2 + rd3 != 100);
        if (kq==1)
        {

            printf("%d phan tram khan gia lua chon A\n%d phan tram khan gia lua chon B\n%d phan tram khan gia lua chon C\n%d phan tram khan gia lua chon D "
                   ,rd,rd1,rd2,rd3 );
        }
        if (kq==2)
        {
            printf("%d phan tram khan gia lua chon A\n%d phan tram khan gia lua chon B\n%d phan tram khan gia lua chon C\n%d phan tram khan gia lua chon D "
                   ,rd1,rd,rd2,rd3 );
        }
        if (kq == 3)
        {
            printf("%d phan tram khan gia lua chon A\n%d phan tram khan gia lua chon B\n%d phan tram khan gia lua chon C\n%d phan tram khan gia lua chon D "
                   ,rd1,rd2,rd,rd3 );
        }
        if (kq == 4)
        {
            printf("%2d phan tram khan gia lua chon A\n%2d phan tram khan gia lua chon B\n%2d phan tram khan gia lua chon C\n%2d phan tram khan gia lua chon D "
                   ,rd1,rd2,rd3,rd );
        }
    }
}

//================================MUC TIEN======================================//
void tienthuong()
{
    Beep(3000,200);
    printf("\t--------------------SO TIEN THUONG QUA TUNG CAU HOI ---------------------\n");
    printf("\t\t\t --------------------------- \n");
    printf("\t\t\t|  Cau 15: 150,000,000 DONG |\n");
    printf("\t\t\t|---------------------------|\n");
    printf("\t\t\t|  Cau 14: 85,000,000 DONG  |\n");
    printf("\t\t\t|---------------------------|\n");
    printf("\t\t\t|  Cau 13: 60,000,000 DONG  |\n");
    printf("\t\t\t|---------------------------|\n");
    printf("\t\t\t|  Cau 12: 40,000,000 DONG  |\n");
    printf("\t\t\t|---------------------------|\n");
    printf("\t\t\t|  Cau 11: 30,000,000 DONG  |\n");
    printf("\t\t\t|---------------------------|\n");
    printf("\t\t\t|  Cau 10: 22,000,000 DONG  |\n");
    printf("\t\t\t|---------------------------|\n");
    printf("\t\t\t|  Cau 9:  14,000,000 DONG  |\n");
    printf("\t\t\t|===========================|\n");
    printf("\t\t\t|  Cau 8:  10,000,000 DONG  |\n");
    printf("\t\t\t|===========================|\n");
    printf("\t\t\t|  Cau 7:  6,000,000 DONG   |\n");
    printf("\t\t\t|---------------------------|\n");
    printf("\t\t\t|  Cau 6:  3,000,000 DONG   |\n");
    printf("\t\t\t|---------------------------|\n");
    printf("\t\t\t|  Cau 5:  2,000,000 DONG   |\n");
    printf("\t\t\t|===========================|\n");
    printf("\t\t\t|  Cau 4:  1,000,000 DONG   |\n");
    printf("\t\t\t|---------------------------|\n");
    printf("\t\t\t|  Cau 3:  600,000  DONG    |\n");
    printf("\t\t\t|---------------------------|\n");
    printf("\t\t\t|  Cau 2:  400,000  DONG    |\n");
    printf("\t\t\t|---------------------------|\n");
    printf("\t\t\t|  Cau 1:  200,000  DONG    |\n");
    printf("\t\t\t|---------------------------|\n");
}
//------------------------------ TINH TIEN --------------------------------//
void tinhdiem(int x, int &diem)
{
    switch(x)
    {
    case 1:
        diem+=200000;
        break;
    case 2:
        diem+=200000;
        break;
    case 3:
        diem+=200000;
        break;
    case 4:
        diem+=400000;
        break;
    case 5:
        diem+=1000000;
        break;
    case 6:
        diem+=1000000;
        break;
    case 7:
        diem+=3000000;
        break;
    case 8:
        diem+=4000000;
        break;
    case 9:
        diem+=4000000;
        break;
    case 10:
        diem+=8000000;
        break;
    case 11:
        diem+=8000000;
        break;
    case 12:
        diem+=10000000;
        break;
    case 13:
        diem+=20000000;
        break;
    case 14:
        diem+=25000000;
        break;
    case 15:
        diem+=65000000;
        break;
    }
}

void intienthuong(int diem)
{

    printf("\n\t\tTIEN THUONG CUA BAN LA: %d", diem);
    Sleep(5000);

}
void InSoTienDatDuoc(int m)
{
    gotoxy(70,0);
    textcolor(YELLOW);
    printf("%d VND",m);
    textcolor(WHITE);
}
//=======================KIEM TRA DAP AN=============================//
void DoiMauKetQua(CAUHOI qs,int mau, int tl)
{
    textcolor(mau);
    if(tl == 1 )
    {
        XuatA(qs.dapAn.A);
    }
    else if(tl == 2 )
    {
        XuatB(qs.dapAn.B);
    }
    else if(tl == 3)
    {
        XuatC(qs.dapAn.C);
    }
    else if(tl == 4)
    {
        XuatD(qs.dapAn.D);
    }
}

int KiemTraDungSai(CAUHOI qs, int tl)
{
    if(tl >= 'a')
        tl = tl - 32;
    if(qs.ketQua == tl)
    {
        //Right
        DoiMauKetQua(qs,WRIGHT,tl);
        Sleep(1000);
        return 1;
    }
    else
    {
        //Wrong
        //Doi mau cau dung
        DoiMauKetQua(qs,WRIGHT,qs.ketQua);
        Sleep(1000);
        //Doi mau cau sai
        DoiMauKetQua(qs,WRONG,tl);
        Sleep(1000);
        return 0;
    }
    textcolor(WHITE);
}


//========================= MENU TRO GIUP ============================//
void QuyenTroGiup(CAUHOI &q,boolean &tg1, boolean &tg2, boolean &tg3)
{
    Beep(3000,200);
    gotoxy(0,20);
    printf("\t\n---------QUYEN TRO GIUP---------\n");
    printf("1. 50:50                     \n");
    printf("2. Goi dien cho nguoi than   \n");
    printf("3. Y kien khan gia           \n");
    printf("Hay chon 1 quyen tro giup (neu khong muon hay nhan '0' de tra loi):\n");
    int chon;
    scanf("%d",&chon);
    while(chon<0||chon>4);
    switch(chon)
    {
    case 1:
    {
        XoaTaiToaDo(0,25);
        XoaTaiToaDo(0,24);
        troGiup_50_50(q,tg1);
        chon = 0;
    }
    break;
    case 2:
    {

        goiDienNguoiThan(q,tg2);
        chon = 0;


    }
    break;
    case 3:
    {
        hoiYKienKhanGia(q,tg3);
        chon = 0;


    }
    break;
    }
    while(chon=0);

}
//===============================CAU HOI=====================================//
int goicauhoi(List l, int x, boolean &tg1, boolean &tg2, boolean &tg3)
{
    int a;
    CAUHOI c=l.first->data;
    quaylai:
    if(x<15)
    {
        gotoxy(0,3);
        printf("\n\tCau hoi so %d: ", x);
    }
    else
    {
        printf("\n\tCau hoi so %d:", x);
    }
    XuatCauHoi(c);
    do
    {
        printf("\n -------------------------------------------------------------------------------");
        printf("\n| De xem quyen tro giup: Nhan 0                                                 |");
        printf("\n| Chon cau tra loi bang cach nhan phim 1-4 (tuong ung voi dap an A-B-C-D):      |\t");
        printf("\n -------------------------------------------------------------------------------");
        printf("\n Tra loi: ");
        scanf("%d", &a);
        if(tg1==false && tg2== false && tg3==false && a==0)
        {
            printf("\nBan da su dung het quyen tro giup cua minh!");
            goto quaylai;
        }
    }
    while(a<0||a>5);
    switch(a)
    {
    case 0:
        system("cls");
        QuyenTroGiup(c, tg1, tg2, tg3);

        goto quaylai;
        break;
    case 1:
    case 2:
    case 3:
    case 4:
    {
        if(KiemTraDungSai(c,a))
            return 1;
        else
            return 0;
    }
    break;
    }
    return 0;
}


void choiGame(List l,boolean &tg1, boolean &tg2, boolean &tg3)
{
	char tennguoichoi[100];
	int tuoi;
	char nghenghiep[100];
	char noio[50];
	printf("    GIOI THIEU BAN THAN   \n");
	printf(" Ten nguoi choi:");
	fflush(stdin);
	gets(tennguoichoi);
	printf(" Tuoi:");
	scanf("%d",&tuoi);
	fflush(stdin);
	printf(" Nghe nghiep: ");
	gets(nghenghiep);
	fflush(stdin);
	printf(" Noi o hien tai:");
	fflush(stdin);
	gets(noio);
    system("cls");
    doc_DS_CauHoi(l);
    tienthuong();
    Sleep(1000);
    system("cls");
    Node *q=l.first;
    int x=1;
    int diem=0;
    int luaChon,a ,b, c;
    while(l.first!=NULL)
    {
        srand(time(NULL));
        c=rand()%2;
        if(c==1)
        {
            l.first=l.first->link;
        }
        InSoTienDatDuoc(diem);
        int kq=goicauhoi(l, x, tg1, tg2, tg3);
        {
            if(kq==1)
            {
                system("cls");
                gotoxy(0,12);
                printf("\n\t\tChinh xac, xin chuc mung!\n");
                printf("                      %s",tennguoichoi);
                tinhdiem(x, diem);
                gotoxy(0,14);
                printf("\n\t SO TIEN HIEN TAI CUA %s LA: %d",tennguoichoi, diem);
                Sleep(1000);
                gotoxy(0,15);
                printf("\n\tNhan 1 de choi tiep hoac 0 de dung cuoc choi: ");
                scanf("%d", &a);
                while(a<0||a>1);
                if(a==0)
                {
                	system("cls");
                	gotoxy(0,12);
                	printf("\n\t\t Cam on %s da den voi chuong trinh!!",tennguoichoi);
                    gotoxy(0,13);
                    intienthuong(diem);
                    gotoxy(0,14);
                    printf("\n\t\t Nhan so bat ki de thoat!!");
                    scanf("%d", &b);
                    goto end;
                }

                if(x==15)
                {
                    system("cls");
                    gotoxy(36,12);
                    printf("\n\tTHANG CUOC                   ");
                    gotoxy(0,13);
                    intienthuong(diem);
                    gotoxy(0,14);
                    printf("\n Nhan so bat ki de thoat!!");
                    scanf("%d", &b);
                    goto end;
                }
                x++;
            }
            else if(kq==0)
            {
                system("cls");
                gotoxy(36,13);
                printf("END GAME!!");
                Beep(100,900);
                gotoxy(0,14);
                printf("\n\t\tRat tiec cau tra loi cua %s khong chinh xac",tennguoichoi);
                Sleep(1000);
                if(x<=5)
                {
                    diem = 0;
                    gotoxy(0,15);
                    intienthuong(diem);
                    gotoxy(0,16);
                    printf("\n\t\tNhan so bat ki de thoat!!");
                    scanf("%d", &b);
                    goto end;
                }
                else if(x<=10)
                    {
                    diem = 2000000;
                    gotoxy(0,15);
                    intienthuong(diem);
                    gotoxy(0,16);
                    printf("\n\t\tNhan so bat ki de thoat!!");
                    scanf("%d", &b);
                    goto end;
                }
                else
                {
                    diem = 22000000;
                    gotoxy(0,15);
                    intienthuong(diem);
                    gotoxy(0,16);
                    printf("\n\t\tNhan so bat ki de thoat!!");
                    scanf("%d", &b);
                    goto end;
                }
            }
            else
            {
                gotoxy(0,15);
                printf("%s",tennguoichoi);
                intienthuong(diem);
                gotoxy(0,16);
                printf("\n\t\tNhan so bat ki de thoat!!");
                scanf("%d", &b);
                goto end;
            }


            textcolor(WHITE);
            q = q->link;
            system("cls");
            l.first=l.first->link;
            }
        }
    end:
    ;
}
//=============================== CHUC NANG ===========================//
void timKiem(List l)
{
	doc_DS_CauHoi(l);
	char ch[300];
	printf("Nhap cau hoi: ");
    fflush(stdin);
    gets(ch);
	int check = 0;
	for (Node *p = l.first; p != NULL; p = p->link)
	{
        if(stricmp(p->data.cauHoi,ch) == 0)
        {
			printf("Cau Hoi :%s \n",  p->data.cauHoi);
			printf("A:%s\n", p->data.dapAn.A);
			printf("B:%s\n", p->data.dapAn.B);
			printf("C:%s\n", p->data.dapAn.C);
			printf("D:%s\n", p->data.dapAn.D);
			printf("Dap an la:%d\n", p->data.ketQua);
			check = 1;
		}
	}
	if (check == 0)
	{
		printf("Khong Tim Thay\n");
	}
}
void themCauHoi(List ds)
{
    system("cls");
    CAUHOI ch;
    int lc;
    FILE *fp;
    fp=fopen("boCauHoi1.txt","a");
    do
    {
        nhapCauHoi(ch);
        fprintf(fp,"\n");
        fprintf(fp, "%s,%s,%s,%s,%s,%d", ch.cauHoi, ch.dapAn.A, ch.dapAn.B, ch.dapAn.C, ch.dapAn.D, ch.ketQua);
        printf("\nTHEM THANH CONG! ");
            printf("\n Nhap tiep: nhan 1\n Thoat: nhan 0\nLua chon cua ban:");
            scanf("%d", &lc);
    }while(lc!=0);
    fclose(fp);
}

//========================== CHE DO DIEU KHIEN ==========================//
void Admin(List ds)
{
    printf("---Vui Long Chon---\n");
    printf("\t1.Them cau hoi moi\n");
    printf("\t2.Xuat danh sach cau hoi\n");
	printf("\t3.Tim kiem cau hoi\n");

    int chon;
    scanf("%d",&chon);
    switch(chon)
    {
    case 1:
   	     system("cls");
    	 themCauHoi(ds);
 		 break;
    case 2:
  		 system("cls");
   		 xuatDanhSach(ds);
		 Sleep(10000);
  		 break;
	case 3:
    	system("cls");
        timKiem(ds);
		Sleep(5000);
        break;
    }
    while(chon!=3);
}
//========================== Huong dan ===========================//
void huongDan()
{
	system("cls");

    printf("------------------------------HUONG DAN------------------------------------\n");
    printf("|=========================================================================|\n");
  	printf("|VUOT QUA DUOC 15 CAU HOI CUA CHUONG TRINH BAN SE NHAN DUOC 150 TRIEU DONG|\n");
  	printf("|                     BAN CO CAC QUYEN TRO GIUP                           |\n");
  	printf("|=========================================================================|\n");
  	printf("|1. GOI DIEN THOAI CHO NGUOI THAN                                         |\n");
	printf("|  BAN CO 30S DE GOI DIEN THOAI NHO SU GIUP SO CUA NGUOI THAN             |\n");
 	printf("|=========================================================================|\n");
  	printf("|2. TRO GIUP 50/50                                                        |\n");
  	printf("|  MAY TINH SE TU DONG LOAI BO HAI PHUONG AN SAI                          |\n");
  	printf("|=========================================================================|\n");
  	printf("|3. HOI Y KIEN KHAN GIA                                                   |\n");
  	printf("|  NHAN DUOC KET QUA: PHAN TRAM SO KHAN GIA LUA CHON PHUONG AN            |\n");
  	printf("|=========================================================================|\n");


  	printf("\n|=========================================================================|\n");
  	printf("|                       CACH TINH DIEM                                    |\n");
  	printf("|=========================================================================|\n");
  	printf("|1. NEU BAN QUYET DINH DUNG CUOC CHOI O CAU HOI NAO DO: SO TIEN CUA BAN   |\n");
  	printf("|SE DUOC TINH LA SO TIEN TUONG UNG VOI MOC TIEN CUA CAU HOI DO            |\n");
 	printf("|=========================================================================|\n");
  	printf("|2. NEU BAN TRA LOI SAI SE QUAY VE MOC GAN NHAT 0 - 5 - 10 - 15 MA BAN DA |\n");
  	printf("|TRA LOI DUOC TUONG UNG VOI SO TIEN 0-2 TRIEU-22 TRIEU-150 TRIEU          |\n");
  	printf("|=========================================================================|\n");


  	Sleep(12000);
}
//=========================== MAIN ==============================//
int main(int argc, char *argv[])
{

    List ds;
    Init(ds);
    boolean tg1=true;
    boolean tg2=true;
    boolean tg3=true;
    int chon;
    do
    {

        printf("\n\n\n\t\t\t\t|==============================================================================|\n");
        printf("\t\t\t\t|               CHAO MUNG BAN DEN VOI TRO CHOI AI LA TRIEU PHU                 |\n");
        printf("\t\t\t\t|==============================================================================|\n\n");
        printf("\n\n");
        printf("\t\t\t\t|==============================================================================|\n");
        printf("\t\t\t\t|                               1. Choi game                                   |\n");
        printf("\t\t\t\t|==============================================================================|\n");
        printf("\n\n");
        printf("\t\t\t\t|==============================================================================|\n");
        printf("\t\t\t\t|                               2. Huong dan                                   |\n");
        printf("\t\t\t\t|==============================================================================|\n");
        printf("\n\n");
        printf("\t\t\t\t|==============================================================================|\n");
        printf("\t\t\t\t|                               3. Quan ly                                     |\n");
        printf("\t\t\t\t|==============================================================================|\n");
        printf("\n\n");
        printf("\t\t\t\t|==============================================================================|\n");
        printf("\t\t\t\t|                               4. Thoat                                       |\n");
        printf("\t\t\t\t|==============================================================================|\n");
        do
        {
            printf("\n CHON MUC : ");
            scanf("%d", &chon);
            if(chon<1||chon>4)
                printf(" Lua chon khong phu hop vui long chon lai \n");
        }
        while(chon<1 && chon>4);
        switch(chon)
        {
        case 1:
            Beep(3000,200);
            tg1=true;
            tg2=true;
            tg3=true;
            choiGame(ds,tg1,tg2,tg3);
            break;
        case 2:
        	system("cls");
        	Beep(3000,200);
        	huongDan();
        	break;
        case 3:
            system("cls");
            Beep(3000,200);
            Admin(ds);
            break;

        }
        system("cls");
    }
    while(chon!=4);
    return 0;

}
