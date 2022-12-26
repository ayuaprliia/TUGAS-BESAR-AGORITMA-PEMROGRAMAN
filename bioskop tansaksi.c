#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

//variabel global untuk fungsi pemesanan

void main();
void mainpage();
void admin_panel();
void login_adm();
void detailfilm();
void menu_aplikasi();
void menu_customer();
void regis_customer();
void login_customer();
int checkpassword();
int checkusername();
void close();
void header_data_pesanan();
void pemesanan();
void riwayat_transaksi();
void selesai();
FILE *fp,*fp1;

struct film
{
	char kode[5];
	char judul[30];
	char genre[20];
	char bahasa[30];
	char studio[3];
}M;

typedef struct{
	int kelas_tiket;
	int harga_tiket;
	int total_harga;
	int total_bayar;
	int kembalian;
	int no_hari;
    int no_konser;
    char nama_hari[255];
    char nama_konser[255];
}DataPembelian;

struct film tambahfilm();
struct film hapusfilm();
struct film tampilkan_film();
struct film booking();

void close(){
    fflush(stdin);
    printf("\n\tTekan Enter untuk Melanjutkan...");
    getchar();
    system("cls");
}

struct customer{
	char nama_cust[50];
	int pin_cust;
};

struct customer registrasi;
struct customer login;

void main(){
    mainpage();
}

//tampilan menu utama
void mainpage(){
    int pilih=0;
	while (pilih!=4)
	{
	system("cls");
	printf("\n\t==============================================================");
    printf("\n\t||                 M E T R O P O L E   X X I                ||");
    printf("\n\t||``````````````````````````````````````````````````````````||");
    printf("\n\t||             PROGRAM BOOKING TIKET BIOSKOP                ||");
    printf("\n\t||==========================================================||");
    printf("\n\t||  [1] Masuk sebagai admin                                 ||");
    printf("\n\t||  [2] Masuk sebagai pelanggan                             ||");
    printf("\n\t||  [3] Keluar                                              ||");
    printf("\n\t==============================================================");
    printf("\n\t Masukkan pilihan Anda [1][2][3] : ");
    scanf("%d", &pilih);
    system("cls");
    switch (pilih){
    	case 1:{
    		login_adm();
    		break;
	}
		case 2:{
			menu_customer();
			break;
		}
		case 3:{
			exit(0);
			break;
		}
	default:{
	printf("menu tidak tersedia");
	break;
	}
}
}
}

//tampilan log in admin
void login_adm(){
	char username [15];
	char password [15];
	printf("\n=======PROGRAM PEMESANAN TIKET BIOSKOP=======\n");
	printf("\n          M E T R O P O L E  X X I           \n");
	printf("\n`````````````````````````````````````````````\n");
	printf("\nMasukkan username: ");
	scanf("%s", &username);
	printf("\nMasukkan password: ");
	fflush(stdin);
	scanf("%s", &password);
    if ((strcmp(username, "admin") == 0) && (strcmp(password, "metropole") ==0)){ //untuk meng-set username dan password
        getchar();
        system ("cls");
        printf("\n\t==============================================================\n");
        printf("\t||                                                          ||");
        printf("\n\t||                M E T R O P O L E   X X I                 ||");
        printf("\n\t||                                                          ||");
        printf("\n\t`````````````````````````````````````````````````````````````");
        printf("\n\t||                      Selamat Datang                      ||");
        printf("\n\t==============================================================\n");
        printf("\n\n\tTekan Enter untuk melanjutkan...");
        getchar();
        system ("cls");
        admin_panel();
        //validasi
	}else {
        printf("\n--------------------------------");
		printf("\nPassword atau Username Salah!\n");
        getchar();
        printf("\nTEKAN ENTER UNTUK KEMBALI");
        printf("\n-------------------------------");
        getchar();
        system ("cls");
        main();
	}
}

//tampilan menu admin
void admin_panel(){
	int choice;
	while (choice!=5){
	system("cls");
	printf("\n\t==============================================================");
    printf("\n\t||                 M E T R O P O L E   X X I                ||");
    printf("\n\t||``````````````````````````````````````````````````````````||");
    printf("\n\t||                       ADMIN PANEL                        ||");
    printf("\n\t||==========================================================||");
    printf("\n\t||                    Pilihan Menu Pegawai                  ||");
    printf("\n\t||  [1] Menambahkan Film                                    ||");
    printf("\n\t||  [2] Menghapus Film                                      ||");
    printf("\n\t||  [3] Lihat Riwayat Transaksi                             ||");
    printf("\n\t||  [4] Hapus Riwayat Transaksi                             ||");
    printf("\n\t||  [5] Log Out                                             ||");
    printf("\n\t==============================================================");
    printf("\n\tMasukkan pilihan Anda [1][2][3][4][5] : ");
    scanf("%d", &choice);
    switch(choice){
    	case 1:
    		{
    			tambahfilm();
    			break;
			}
		case 2:
			{
				hapusfilm();
				break;
			}
			case 5:{
                printf("logging out......");
                close();
                mainpage();
                break;
			}
		default:
			{
				printf("Menu tidak tersedia!");
				break;
			}
	}


	}
}

struct film tambahfilm()
{
	char ch;
	int a;
	system("cls");
	detailfilm();
	MOVIE:
	printf("Ingin menambahkan film lagi? (y/n) : ");
	fflush(stdin);
	scanf("%c",&ch);
	if(ch=='y'||ch=='Y')
	{
		system("cls");
		detailfilm();
		goto MOVIE;
	}
	else if(ch=='n'||ch=='N')
	{

		printf("Film Berhasil ditambahkan...");
	}
	admin_panel();
}

void detailfilm(){
	system("cls");
	fp=fopen("daftarfilm.txt","a");
	printf("Masukkan kode film : ");
	scanf("%s",&M.kode);
	printf("\nMasukkan judul Film : ");
	fflush(stdin);
	gets(M.judul);
	printf("\nMasukkan genre film : ");
	gets(M.genre);
	printf("\nMasukkan bahasa film : ");
	gets(M.bahasa);
	printf("\nMasukkan studio penanyangan : ");
	gets(M.studio);

	fwrite(&M,sizeof(M),1,fp);
//	fprintf(fp,"\n");
	fclose(fp);
	fclose(fp1);
}

struct film hapusfilm()
{
	int i=0;
	system("cls");
	tampilkan_film();
	fp=fopen("daftarfilm.txt","r");
	fp1=fopen("daftarfilm2.txt","w");
	char id[5], c;//,found='f',ans;
	printf("Masukkan kode film yang akan dihapus : ");
	scanf("%s",&id);
	fflush(stdin);
	printf("apakah anda yakin? (y/n)");
	scanf("%c",&c);
	if(c=='y'||c=='Y')
	{
		while(fread(&M,sizeof(M),1,fp)>0)
		{
			if(strcmp(id,M.kode)!=0)
				fwrite(&M,sizeof(M),1,fp1);
			else
				i++;
		}
		if(i!=0)
		{
			printf("Film telah dihapus...");
		}
		else
		{
			printf("Kode film tidak ditemukan!!");
		}


		fclose(fp);
		fclose(fp1);

		remove("daftarfilm.txt");
		rename("daftarfilm2.txt","daftarfilm.txt");
		getch();
	}
	if (c=='n'||c=='N')
	{
		hapusfilm();
	}
//	main_page();
		admin_panel();
}

struct film tampilkan_film()
{
	system("cls");
	int i=0;
	fp1=fopen("daftarfilm.txt","r");
	printf("===============DAFTAR FILM====================\n");
	printf("-------------                -----------------\n");
	printf("------------:KODE:   :JUDUL:------------------\n");
	fflush(stdin);
	while(fread(&M,sizeof(M),1,fp1)>0)
	{

		printf("              %s        %s\n",M.kode,M.judul);
		i++;
	}
	fclose(fp1);

}


void menu_customer(){//Menampilkan pilihan menu awal yang dapat dipilih customer untuk masuk ke program
    //system("color 9");
    int menu;
    printf("\n\t==============================================================");
    printf("\n\t||                   M E T R O P O L E   X X I              ||");
    printf("\n\t||         Jl. Raya Kampus Unud No.530C Jimbaran Badung     ||");
    printf("\n\t||----------------------------------------------------------||");
    printf("\n\t||                        SELAMAT DATANG                    ||");
    printf("\n\t||==========================================================||");
    printf("\n\t||  [1] Registrasi                                          ||");
    printf("\n\t||----------------------------------------------------------||");
    printf("\n\t||  [2] Login                                               ||");
    printf("\n\t||----------------------------------------------------------||");
    printf("\n\t||  [3] Exit                                                ||");
    printf("\n\t==============================================================");
    printf("\n\tMasukkan Pilihan Anda : ");
	while(scanf("%d", &menu)==0 || menu < 1 || menu > 3){
        printf("\t--------------------------------------------------------------");
        printf("\n\tAngka yang Anda inputkan salah!");
        printf("\n\tMohon inputkan pilihan yang benar...");
        printf("\n\t--------------------------------------------------------------");
        printf("\n\tMasukkan pilihan Anda: ");
        while((getchar())!='\n');
    }
	close();
    if (menu==1){
        regis_customer(); // menuju bagian registrasi (apabila customer belum terdaftar)
    }else if(menu==2){
        login_customer(); // menuju bagian login customer (apabila customer sudah pernah mendaftarkan PIN dan usernamenya)
    }else{
        selesai(); // keluar dari menu customer(nanti klo uda digabungin bawa ke menu awal bgt)
    }
}

//registrasi customer baru
void regis_customer()
{
int i;
char d;
 do {
    char username[ ][10] = {"","","","","","","","","","",""};
    char password[ ][10] = {"","","","","","","","","","",""};

    FILE *fusername,*fpassword;
    fusername = fopen("username_pelanggan.txt", "a");
    fpassword = fopen("password_pelanggan.txt", "a");

    for(i=0; i<10; i++)
    {
        fgets(username[i], 255, (FILE*)fusername);

        fgets(password[i], 255, (FILE*)fpassword);

    }

    fclose(fusername);
    fclose(fpassword);
    printf("%s",username[1]);

    printf("\t\t=============================================\n");
    printf("\t\t         M E T R O P O L E  X X I            \n");
    printf("\t\t_____________________________________________\n");
    printf("\t\t----------REGISTRASI PELANGGAN BARU----------\n");
    printf("\t\t_____________________________________________\n");
    printf("\t\tMasukan Username (maksimal 9 karakter) : ");
    scanf("%s[^\n]",username[0]);
    printf("\t\tMasukan Password (maksimal 9 digit)  : ");
    scanf("%s[^\n]",password[0]);


    FILE *f = fopen("username_pelanggan.txt", "a");

    //input username ke file
    fputs(username[0], f);
    fputs("\n", f);
    fclose(f);
    //input password ke file
    f = fopen("password_pelanggan.txt", "a");
    fputs(password[0], f);
    fputs("\n", f);
    fclose(f);

    printf("\n\n\t\t=============================================\n");
    printf("\t\t         M E T R O P O L E  X X I            \n");
    printf("\t\t_____________________________________________\n");
    printf("\t\t------------AKUN BERHASIL DIBUAT-------------\n");
    printf("\t\t_____________________________________________\n");
    printf("\t\t=============================================\n");
    printf("\n");


 printf("\t\tApakah ingin membuat akun lagi? (y/t) : ");
 scanf(" %s", &d);
system("cls");

 }while (d=='Y' || d=='y');
}

//untuk mengecek kebenaran username yang diinputkan
int checkusername(){

    FILE* filePointer;
    int bufferLength = 255;
    char buffer[bufferLength];
    char checkus[255];
    filePointer = fopen("username_pelanggan.txt", "r");
    int index=0;
    int indexfound=0;
    printf("\t\tMasukan Username : ");
    scanf("%s",checkus);

    while(fgets(buffer, bufferLength, filePointer)) {

    buffer[strlen(buffer)-1] = '\0';
    int length = strlen(buffer);
    if(strcmp(buffer,checkus)==0)
    {
        indexfound=index;
        return indexfound;
        //printf("found on index:%u",index);
    }
        //printf("length username: %u,lengh check:", length,length2);
         index++;

        //printf("%s", buffer);
    }

    fclose(filePointer);
    //printf(" username  found index:%u",indexfound);
    return 999;
}

//untuk mengecek kebenaran password yang diinputkan
int checkpassword(){

    FILE* filePointer;
    int bufferLength = 255;
    char buffer[bufferLength];
    char checkus[255];
    filePointer = fopen("password_pelanggan.txt", "r");
    int index=0;
    int indexfound=0;
    printf("\t\tMasukan Passwrod : ");
    scanf("%s",checkus);

    while(fgets(buffer, bufferLength, filePointer)) {

    buffer[strlen(buffer)-1] = '\0';
    int length = strlen(buffer);
    if(strcmp(buffer,checkus)==0)
    {
        indexfound=index;
        return indexfound;

        //printf("found on index:%u",index);
    }
        //printf("length username: %u,lengh check:", length,length2);
         index++;

        //printf("%s", buffer);
    }

    fclose(filePointer);
 //   printf(" pw  found index:%u",indexfound);

return 193;
}

//tampilan log in untuk customer yang sudah melakukan registrasi akun
void login_customer()
{
    char d;
    do {

    printf("\t\t=============================================\n");
    printf("\t\t         M E T R O P O L E  X X I            \n");
    printf("\t\t_____________________________________________\n");
    printf("\t\t--------------LOG IN PELANGGAN---------------\n");
    printf("\t\t_____________________________________________\n");
    printf("\t\t=============================================\n");
    int username=999;
    int password=123;
    username=checkusername();
    password=checkpassword();

    if(username==password)
    {
        menu_aplikasi();
    }
    else
    {
        printf("\n\n\t\tAkun tidak ditemukan!! \n");
    }

     printf("\n\t\tApakah Anda ingin log in kembali? (y/t) : ");
	 scanf(" %s", &d);
     system("cls");

 }while (d=='Y' || d=='y');
}

void menu_aplikasi(){
    //system("color E");
    system("cls");
    int menu;
    printf("\n\t==============================================================\n");
    printf("\n\t  --------------- M E T R O P O L E   X X I ---------------- \n");
    printf("\n\t==============================================================");
    printf("\n\t||                     P I L I H A N  M E N U               ||");
    printf("\n\t==============================================================");
    printf("\n\t||  [1] PEMESANAN TIKET                                     ||");
    printf("\n\t||----------------------------------------------------------||");
    printf("\n\t||  [3] LOGOUT                                              ||");
    printf("\n\t==============================================================\n");
    printf("\n\tMasukkan Pilihan Anda : ");
	while(scanf("%d", &menu)==0 || menu < 1 || menu > 2){
        printf("\t--------------------------------------------------------------");
        printf("\n\tAngka yang Anda inputkan salah!");
        printf("\n\tMohon inputkan pilihan yang benar...");
        printf("\n\t--------------------------------------------------------------");
        printf("\n\tMasukkan pilihan Anda: ");
        while((getchar())!='\n');
    }
	close();
    if (menu==1){
    	tampilkan_film();
        booking();
    }
    else{
        mainpage(); // keluar dari menu customer(nanti klo uda digabungin bawa ke menu awal bgt)
    }
}

struct film booking()
{
	FILE *fp1;
	char id[5],c;
	int i=0;
	printf("\n\nMasukkan kode film pilihan Anda : ");
	fflush(stdin);
	gets(id);
	system("cls");
	fp1=fopen("daftarfilm.txt","r");
	fflush(stdin);
	while(fread(&M,sizeof(M),1,fp1)>0)
	{
		if(strcmp(id,M.kode)==0)
		{

			printf("Kode film:%s\n\t\t\t Judul film :%s\n\t\t\t Genre      :%s\n\t\t\t Bahasa     :%s\n\t\t\t\ Studio     :%s\n",M.kode,M.judul,M.genre,M.bahasa,M.studio);
	}
	}
	printf("Lanjut untuk memilih jam tayang? (y/n) ");
	scanf("%c",&c);
	if(c=='y'||c=='Y')
	{
		fclose(fp1);
		mainpage();
	}

	else
	{
		fclose(fp1);
		menu_customer();
	}
}





void selesai(){
    printf("\n\t==========================================================");
    printf("\n\t|                                                        |");
    printf("\n\t|                T E R I M A   K A S I H                 |");
    printf("\n\t|                                                        |");
    printf("\n\t|         ----------SELAMAT MENONTON----------           |");
    printf("\n\t|                                                        |");
    printf("\n\t==========================================================\n\n");
    exit(0);
}

