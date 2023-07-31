/* CONTACT KEEPER
 * ==============
 * 
 * So far, you've been learning the C programing language about two weeks.
 * Now is the right time to think about your assignment.
 * This semester, your task is to write a C program, namely Contact Keeper,
 * to manage your contacts easily and effectively.
 * 
 * One contact should have the following features:
 *		1. First Name
 *		2. Last Name
 *		3. Company
 *		3. Phone Number
 *		4. Email
 *		5. Working Address
 *		6. Home Address
 *		7. Birthday
 *
 * Data validation should be implemented, for example:
 *		1. Phone Number should be a integer number of 9 or 10 digits
 *		2. Bithday should be in the DD/MM/YYYY format 
 *
 * Your program should have at least six functions:
 *		1. Add new contact
 *		2. Edit contact
 *		3. Delete contact (by name or phone number)
 *		4. Search contact (by name or phone number)
 *		5. List all contacts with birthdays in a given month (sort by date)
 *		6. List all contacts in the table format (sort by name)
 *
 * The contact information should be permanently stored in a text file
 * so that when the program starts all contacts could be loaded automatically.
 *
 * Form a group of three members and enjoy this task!
 */


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>

// Tao kieu Contact luu tru cac thuoc tinh can thiet
typedef struct Contact {
	int stt;
	char fname[20];
	char lname[20];
	char company[20];
	char phone[20];
	char email[50];
	char workingAddress[20];
	char homeAddress[20];
	char birthday[20];
} CT;

void print_menu();
void add_contact(CT a[], int stt);
void edit_contact(CT a[], int sttChange, int stt);
void delete_contact(CT a[], char name[], int *stt);
void search_contact(CT a[], char name[], int stt);
void display_month(CT a[], char month[], int stt);
void sort_by_name(CT[], int stt);
int valid_phone(char phone[]);
int valid_birth(char birthday[]);
int read_file(CT a[], char file[]);
void write_file(CT a[], int stt, char file[]);

int main()
{
	int sttChange;
	char choice;
	char nameSearch[20];
	char nameRemove[20];
	char month[5];
	char file[] = "information.txt";
	CT a[100];
	int stt = read_file(a, file);	// Doc xem trong file da co du lieu hay chua, stt la so luong dong thong tin da co
	
	do
	{
		//system("clear"); // for unix
		system("cls"); // for windows
		print_menu();
		scanf("%c%*c", &choice);

		//system("clear"); // for unix
		system("cls"); // for windows

		printf("CONTACT KEEPER\n");
		printf("==============\n\n");

		switch(choice)
		{
			case '1':
				// Phuong thuc them contact nen phai tang so luong them 1
				stt++;
				add_contact(a, stt);
				break;
			case '2':
		
				// Phuong thuc sua thong tin contact, can nhap vao stt muon sua
				printf("Enter STT of the contact you want to edit: ");
				fflush(stdin); scanf("%d", &sttChange);		// Cac lenh fflush de xoa bo dem
				edit_contact(a, sttChange, stt);
				break;
			case '3':
				
				// Phuong thuc xoa contact dua theo ten nhap vao
				printf("Enter name of the contact you want to remove: ");
				fflush(stdin); gets(nameRemove);
				delete_contact(a, nameRemove, &stt);
				break;
			case '4':
				// Tim kiem contact dua theo ten nhap vao
				printf("Enter name of the contact you want to search: ");
				fflush(stdin); gets(nameSearch);
				search_contact(a, nameSearch, stt);
				break;
			case '5':

				// Phuong thuc hien thi ra cac contact dua tren thang (month) nhap vao va sap xep theo ngay sinh
				printf("Enter month of birthday of contact you want to display (sort by date): ");
				fflush(stdin); gets(month);
				display_month(a, month, stt);
				break;
			case '6':
				// Hien thi tat ca thong tin sap xep theo ten
				sort_by_name(a, stt);
				break;
		}
		
		if (choice != 'q')
		{
			printf("\n\n---\n");
			printf("Press any key to back to main menu.");
			getchar();
		}
	}
	while (choice != 'q');
	write_file(a, stt, file);	// Ket thuc chuong trinh, ghi lai toan bo du lieu moi vao tep

	return 0;
}


void print_menu()
{
	printf("CONTACT KEEPER\n");
	printf("==============\n\n");
	printf("1. Add Contact\n");
	printf("2. Edit Contact\n");
	printf("3. Delete Contact (by name)\n");
	printf("4. Search Contact (by name)\n");
	printf("5. List all contacts with birthdays in a given month (sort by date)\n");
	printf("6. List all contacts in the table format (sort by name)\n");
	printf("q. Quit\n\n");
	printf("Enter your choice (1/2/3/q): ");
}

// Nhap thong tin contact theo stt
void enter_contact(CT *ct, int stt) 
{
	printf("Enter first name: "); fflush(stdin); gets((*ct).fname);
	printf("Enter last name: "); fflush(stdin); gets((*ct).lname);
	printf("Enter company: "); fflush(stdin); gets((*ct).company);
	
	// Kiem tra sdt nhap vao, so dth hop le co 9 hoac 10 chu so, neu khong bat nhap lai
	while (1) {
		printf("Enter phone number: "); fflush(stdin); gets((*ct).phone);
		if (valid_phone((*ct).phone) == 1) break;
		printf("Try again, phone number should have 9 or 10 digits\n");
	}
	printf("Enter email: "); fflush(stdin); gets((*ct).email);
	printf("Enter working address: "); fflush(stdin); gets((*ct).workingAddress);
	printf("Enter home address: "); fflush(stdin); gets((*ct).homeAddress);
	
	// Kiem tra ngay thang nam sinh nhap vao, dung dinh dang la DD/MM/YYYY, neu khong bat nhap lai
	while (1) {
		printf("Enter birthday (DD/MM/YYYY): "); fflush(stdin); gets((*ct).birthday);
		if (valid_birth((*ct).birthday) == 1) break;
		printf("Try again, birthday should be in the DD/MM/YYYY format\n");
	}
	(*ct).stt = stt;
	printf("\n");
}

// Them contact vao mang
void add_contact(CT a[], int stt)
{	
	printf("Enter contact information:\n");
	enter_contact(&a[stt-1], stt);
}

// Giong phuong thuc enter_contact, tuy nhien phuong thuc nay khong can biet stt vi stt
// da biet khi nhap tu ban phim
void enter_edit_contact(CT *ct) {
	printf("Enter new first name: "); fflush(stdin); gets((*ct).fname);
	printf("Enter new last name: "); fflush(stdin); gets((*ct).lname);
	printf("Enter new company: "); fflush(stdin); gets((*ct).company);
	while (1) {
		printf("Enter phone number: "); fflush(stdin); gets((*ct).phone);
		if (valid_phone((*ct).phone) == 1) break;
		printf("Try again, phone number should have 9 or 10 digits\n");
	}
	printf("Enter new email: "); fflush(stdin); gets((*ct).email);
	printf("Enter new working address: "); fflush(stdin); gets((*ct).workingAddress);
	printf("Enter new home address: "); fflush(stdin); gets((*ct).homeAddress);
	while (1) {
		printf("Enter birthday (DD/MM/YYYY): "); fflush(stdin); gets((*ct).birthday);
		if (valid_birth((*ct).birthday) == 1) break;
		printf("Try again, birthday should be in the DD/MM/YYYY format\n");
	}
	printf("\n");
}

// Edit contact dua tren stt nhap vao
void edit_contact(CT a[], int sttChange, int stt) 
{
	int i, found = 0;	// bien found de biet stt nhap vao co ton tai khong, 0 la chua tim duoc, 1 la da tim duoc
	for (i = 0; i < stt; i++) {
		if (a[i].stt == sttChange) {
			// Vi tim duoc stt co trong mang -> found = 1
			found = 1;
			printf("Found STT = %d\n", sttChange);
			enter_edit_contact(&a[i]);	// edit contact phia tren
		}
	}
	if (found ==  0) {
		// Stt khong co trong mang, thong bao khong tim thay
		printf("Cannot find any contact with STT = %d", sttChange);
		getch();
	}
}

// Xoa di cac contact co ten trung ten truyen vao (first name hay last name cung tinh)
void delete_contact(CT a[], char name[], int *stt)
{
	int i, found = 0;	// nhu tren, bien found de xem ten truyen vao co ton tai khong
	for (i = 0; i < *stt; i++) {
		if (strcmp(a[i].fname, name) == 0 || strcmp(a[i].lname, name) == 0) {	// Lenh so sanh 2 string co bang nhau khong
			// Da tim thay
			found = 1;
			int j;
			// Remove phan tu tai chi so i
			for (j = i; j < *stt; j++) {
				a[j] = a[j+1];
			}
			(*stt)--;	
			i--;	// i-- de khong bi kiem tra sot phan tu
		}
	}
	if (found == 1) printf("All contact with name = %s has been deleted", name);
	else printf("Cannot find any contact with name = %s", name);
	getch();
}

// Hien thi cac contact trong mang
void display_contact(CT a[], int stt) {
	int i;
	printf(" %-5s%-20s%-20s%-20s%-20s%-30s%-20s%-20s%-20s\n", "STT", "First name", "Last name", "Company name", "Phone number", "Email", "Working address", "Home address", "Birthday");
	for (i = 0; i < stt; i++) {
		printf(" %-5d%-20s%-20s%-20s%-20s%-30s%-20s%-20s%-20s\n", i+1, a[i].fname, a[i].lname, a[i].company, a[i].phone, a[i].email, a[i].workingAddress, a[i].homeAddress, a[i].birthday);
	}
	printf("\n");
	getch();
}

// Tim kiem contact dua theo ten truyen vao
void search_contact(CT a[], char name[], int stt) 
{
	int i, found = 0, j = 0;
	CT search[100];	// Mang search luu tru cac contact tim duoc, de khong lam anh huong den mang goc
	for (i = 0; i < stt; i++) {
		if (strcmp(a[i].fname, name) == 0 || strcmp(a[i].lname, name) == 0) {
			found = 1;
			search[j] = a[i];	// Vi tim thay nen gan phan tu do vao mang search
			j++;				// j dong thoi tang len (so luong phan tu cua mang search)
		}
	}
	if (found == 0) printf("Cannot find any contact with name = %s", name);
	else display_contact(search, j);
}

// Lay thang (month) cua birthday dang DD/MM/YYYY
int get_month(char birthday[])
{
	char temp[5];	
	temp[0] = birthday[3];
	temp[1] = birthday[4];
	return atoi(temp);	// atoi de ep string ve int
}

// Lay ngay (date) cua birthday
int get_date(char birthday[]) 
{
	char temp[5];	
	temp[0] = birthday[0];
	temp[1] = birthday[1];
	return atoi(temp);
}

// Sap xep cac contact tang dan theo ngay sinh
void sort_by_date(CT a[], int stt) 
{
	int i, j;
	// Thuat toan interchange sort 
	for (i = 0; i < stt - 1; i++) {
		for (j = i + 1; j < stt; j++) {
			if (get_date(a[i].birthday) > get_date(a[j].birthday)) {
				CT temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
	}	
}

// Chi hien thi cac contact co thang sinh trung voi month duoc truyen vao
void display_month(CT a[], char month[], int stt) 
{
	sort_by_date(a, stt);	// Dau tien, chay lenh sap xep ben tren sau do moi loc ra cac thang can tim
	int i, found = 0, flag = 0;
	
	for (i = 0; i < stt; i++) {
		// Check xem thang cua contact co bang thang truyen vao khong
		if (get_month(a[i].birthday) == atoi(month)) {
			found = 1;
			// flag la bien de in ra dong dau menu 1 lan duy nhat
			if (flag == 0) {
				printf(" %-5s%-20s%-20s%-20s%-20s%-30s%-20s%-20s%-20s\n", "STT", "First name", "Last name", "Company name", "Phone number", "Email", "Working address", "Home address", "Birthday");
				flag = 1;
			}
			// In ra cac contact
			printf(" %-5d%-20s%-20s%-20s%-20s%-30s%-20s%-20s%-20s\n", i+1, a[i].fname, a[i].lname, a[i].company, a[i].phone, a[i].email, a[i].workingAddress, a[i].homeAddress, a[i].birthday);
		}
	}
	// Khong tim thay contact nao co month trung voi month can tim
	if (found == 0) printf("Cannot find any contact have month in birthday = %s", month);
	printf("\n");
	getch();
}

// Phuong thuc sap xep tang dan theo ten, thuat toan interchange sort
void sort_by_name(CT a[], int stt)
{
	int i, j;
	for (i = 0; i < stt - 1; i++) {
		for (j = i + 1; j < stt; j++) {
			if (strcmp(a[i].fname, a[j].fname) > 0) {
				CT temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
	}
	// Sap xep xong thi in ra mang contact
	display_contact(a, stt);
}

// Check sdt hop le (co 9 hoac 10 chu so)
int valid_phone(char phone[])
{
	return (strlen(phone) == 9 || strlen(phone) == 10);
}

// Check ngay sinh hop le, phai dung dang DD/MM/YYYY, DD MM YYYY la cac chu so
int valid_birth(char birthday[])
{
	return (isdigit(birthday[0]) && isdigit(birthday[1]) 
		&& isdigit(birthday[3]) && isdigit(birthday[4]) 
		&& isdigit(birthday[6]) && isdigit(birthday[7]) 
		&& isdigit(birthday[8]) && isdigit(birthday[9])
		&& birthday[2] == '/' && birthday[5] == '/');
}

// Phuong thuc doc tep, tra ve so luong ban ghi (stt) da co
int read_file(CT a[], char file[])
{
	FILE *fp;
	int i = 0;
	fp = fopen(file, "r");
	while (fscanf(fp, "%5d%20s%20s%20s%20s%30s%20s%20s%20s\n", 
				&a[i].stt, &a[i].fname, &a[i].lname, &a[i].company, &a[i].phone, 
				&a[i].email, &a[i].workingAddress, &a[i].homeAddress, &a[i].birthday) != EOF) {
		i++;
	}
	printf("Read file successfully!\n\n");
	getch();
	fclose(fp);
	return i;	// So luong ban ghi trong tep
}

// Ket thuc chuong trinh, ghi thong tin cua mang vao tep
void write_file(CT a[], int stt, char file[])
{
	FILE *fp;
	fp = fopen(file, "w");
	int i;
	for (i = 0; i < stt; i++) {
		fprintf(fp, "%5d%20s%20s%20s%20s%30s%20s%20s%20s\n",
				a[i].stt, a[i].fname, a[i].lname, a[i].company, a[i].phone, 
				a[i].email, a[i].workingAddress, a[i].homeAddress, a[i].birthday);
	}
	printf("Write file successfully!\n\n");
	fclose(fp);
}

