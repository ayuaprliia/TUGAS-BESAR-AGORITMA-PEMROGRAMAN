#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void mainpage(); void login_adm(); void admin_panel();
void detailfilm(); void daftar(); void login_user();
int checkusername(); int checkpassword(); void user_panel();
FILE *fp,*fp1;

struct film
{
	char kode[5];
	char judul[30];
	char genre[20];
	char bahasa[30];
	char studio[3];
}M;
struct film tambahfilm();
struct film hapusfilm();
struct film tampilkan_film();
struct film booking();

int main(){
	mainpage();
	return 0;
}

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
    printf("\n\t||  [1] Log-in sebagai admin                                ||");
    printf("\n\t||  [2] Log-in pelanggan                                    ||");
    printf("\n\t||  [3] Registrasi pelanggan baru                           ||");
    printf("\n\t||  [4] Keluar                                              ||");
    printf("\n\t==============================================================");
    printf("\n\t Masukkan pilihan Anda [1][2][3][4] : ");
    scanf("%d", &pilih);
    system("cls");
    switch (pilih){
    	case 1:{
    		login_adm();
    		break;
	}
		case 2:{
			login_user();
			break;
		}
		case 3:{
			daftar();
			break;
		}case 4:{
            exit(0);
		}
	default:{
	printf("menu tidak tersedia");
	break;
	}
}
}
}

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
        case 5:
            mainpage();
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


void daftar()
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
    printf("\t\tMasukan Username (maksima5l 9 karakter) : ");
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

void login_user()
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
        user_panel();
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

void user_panel(){
	int input;
	while (input!=3){
	system("cls");
	printf("\n\t==============================================================");
    printf("\n\t||                 M E T R O P O L E   X X I                ||");
    printf("\n\t||``````````````````````````````````````````````````````````||");
    printf("\n\t||                      USER PANEL                          ||");
    printf("\n\t||==========================================================||");
    printf("\n\t||                  Pilihan Menu Pelanggan                  ||");
    printf("\n\t||  [1] Membeli tiket bioskop                               ||");
    printf("\n\t||  [2] Cari tiket berdasarkan kode                         ||");
    printf("\n\t||  [3] Log Out                                             ||");
    printf("\n\t==============================================================");
    printf("\n\tMasukkan pilihan Anda [1][2][3] : ");
    scanf("%d", &input);
    switch(input){
    	case 1:{
    		tampilkan_film();
    		booking();
			break;
		}
		case 3:
            mainpage();
		default:{
			printf("\nMenu tidak tersedia!!");
			break;
		}
	}
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

			printf("Kode film:%s\n\t\t\t Judul film:%s\n\t\t\t Genre:%s\n\t\t\t Bahasa:%s\n\t\t\t\ Studio:%s\n",M.kode,M.judul,M.genre,M.bahasa,M.studio);
	}
	printf("Lanjut untuk memilih kursi? (y/n) ");
	scanf("%c",&c);
	if(c=='y'||c=='Y')
	{
		fclose(fp1);
		mainpage();
	}

	else
	{
		fclose(fp1);
		user_panel();
	}
}

}





