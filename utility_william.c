// #include<stdio.h>
// #include<stdlib.h>
// #include<math.h>
// #include"bangunan.h"
// #include"point.h"
// #include"stack.h"
// #include"state.h"
// #include"array.h"
// #include"matriks.h"
// #include "listbangunan.h"
// //#include "skill.h"
// #include"pemain.h"
// #include"boolean.h"
// #include"bangunan.c"
// #include"point.c"
// #include"stack.c"
// #include"state.c"
// #include"array.c"
// #include"matriks.c"
// #include "listbangunan.c"
// //#include "listlinier.c"
// #include "mesinkar.c"
// #include "mesinkata.c"
// #include "readkonfigurasi.c"
// //#include "skill.c"
// #include"pemain.c"
// #include<stdio.h>
// #include<stdlib.h>
// #include"mesinkata.h"
// #include"mesinkar.h"
#define printInt(x) printf("%d", x)
#define printlnInt(x) printf("%d\n", x)
#define println(x) printf("%c\n", x)
#define print(x) printf("%c", x)
#define bacaInt(x) scanf("%d", &x)
#define bacaChar(x) scanf("%c", &c)
#define endline printf("\n")
#define SIZE 100

boolean IsAbleMove(Bangunan bangunanAwal, Bangunan bangunanTujuan, int n, Pemain P){
	/* Mengecek apakah pasukan suatu bangunan dapat dipindahkan ke bangunan tujuan*/
	/*
		Validasi didasari oleh :
			1. Apakah bangunan 1 terhubung dengan bangunan 2
	*/

	// cek keterhubungan
	// cek apakah kedua bangunan berasal dari pemilik yang sama
	// cek apakah jumlah pasukan yang dimasukkan valid

	// tambahin cek keterhubungan 2 bangunan
	if (!(haveBuildingB(P,bangunanAwal)) || !(haveBuildingB(P,bangunanTujuan))){
		return false;
	} 
	if (Pasukan(bangunanAwal) < n){
		return false;
	}
	return true;
}

void Move(Bangunan * bangunanAwal, Bangunan * bangunanTujuan, int n, Pemain P){
	/*
	I.S. Bangunan Awal dan Bangunan Tujuan terdefinisi
		 Jumlah pasukan <= pasukan total di bangunanAwal
	F.S. Pasukan sebanyak n dipindahkan ke bangunanTujuan dari bangunan Awal
	Pemain d
	*/
	if (IsAbleMove((*bangunanAwal),(*bangunanTujuan), n, P)){
		Pasukan(*bangunanAwal) -= n;
		Pasukan(*bangunanTujuan) += n;
	}

}

boolean IsAbleSerang(Bangunan bangunanPe, Bangunan bangunanDe, int n){
	/*
		Mengecek apakah suatu bangunan dapat menyerang bangunan bertahan
		1. Cek apakah tersambung
		2. Cek apakah dia uda pernah nyerang
		3. Cek apakah jumlah penyerang tidak lebih dari jumlah total pasukan di bangunan tersebut
	*/

	// cek keterhubungan
	if (IsSudahSerang(bangunanPe)){
		// cek kondisi apakah sudah pernah menyerang atau belum
		return false;
	} 
	if (Pasukan(bangunanPe) < n){
		// cek apakah jumlah pasukan yang diinput valid atau tidak
		return false;
	}
	return true;
}


void NextTurnLBangunan(ListB * L){
	/*
	Melakukan traversal ke seluruh bangunan pada list bangunan
	dan melakukan penambahan 
	*/
	elb bangunan;
	if (!IsEmptyListB(*L)){
		bangunan = FirstB(*L);
		while (bangunan != Kosong){
			NextTurnBangunan(&Bangunan(bangunan));
			bangunan = NextB(bangunan);
		}
	}
}

void SerangB(Bangunan * bangunanPe, Bangunan * bangunanDe, int n, Pemain * P1, Pemain * P2){
	/*
	I.S. 2 Bangunan Terdefinisi
	F.S. bangunan 1 menyerang bangunan 2
	*/
	int x;
	if (IsAbleSerang((*bangunanPe), ((*bangunanDe)), n)){
		if (IsPindahPemilik((*bangunanDe),n)){
			if (Pertahanan(*bangunanDe)){
				x = ceil((4/3) * Pasukan(*bangunanDe));
				Pasukan(*bangunanDe) = n - x;
			} else {
				// tidak ada pertahanan
				Pasukan(*bangunanDe) = n - Pasukan(*bangunanDe);
			}
			Pasukan(*bangunanPe) -= n;
			ChangeOwner((P1), (*bangunanDe) , P2);

		} else {
			if (Pertahanan(*bangunanDe)){
				x = floor((3/4) * n);
				Pasukan(*bangunanDe) -= x;
			} else {
				Pasukan(*bangunanDe) = Pasukan(*bangunanDe) - n;
			}
			Pasukan(*bangunanPe) -= n;
		}
	Serang(*bangunanPe) = true;
	}
}

void NextTurnPemain(Pemain * P){
	/*
	I.S. Pemain terdefinisi,
		 Seluruh bangunan yang dimiliki pemain dalam keadaan turn sebelumnya
	F.S. Seluruh bangunan milik pemain memiliki kondisi yang terubah sesuai dengan 
		 ketentuan bangunan
	btw, buat perubahan yang terjadi taro disini aja
	*/
	ListB listB;

	listB = (*P).b;

	NextTurnLBangunan(&listB);

	// ketentuan perubahan status pada turn berikutnya
}


/*
	Checker netral, 
	simple, kalo ga ada di list 2 pemain, bangunan netral
*/
boolean IsBangunanNetral(Bangunan b, Pemain p1, Pemain p2){
	/* Melakukan pengecekan apakah suatu bangunan bersifat netral atau tidak */
	if ((SearchListB(p1.b,b) == Kosong) && (SearchListB(p2.b,b) == Kosong)) return true;
	else return false;
}

char * outputString() {
	char * s = malloc(sizeof (char) * CKata.Length);
	for (int i = 1; i <= CKata.Length; i++){
		s[i-1] = CKata.TabKata[i];
	}
	return s;
}


int pengubahAngka() {
	int sum = 0;
	for (int i = 1; i <= CKata.Length; i++){
		sum = sum * 10 + (CKata.TabKata[i] - '0');
	}
	return sum;
}

char * BacaInputUser(){
	STARTKATAIn();
	while(!EndKata){
		ADVKATAIn();
	}
	char * s = malloc(sizeof (char) * CKata.Length);
	for (int i = 1; i <= CKata.Length;i++){
		s[i-1] = CKata.TabKata[i];
	}
	return s;
}
boolean IsAttack (char s[]){
	char attack[6];
	attack[0] = 'A';
	attack[1] = 'T';
	attack[2] = 'T';
	attack[3] = 'A';
	attack[4] = 'C';
	attack[5] = 'K';

	int sizeof_attack = sizeof(attack) / sizeof(char);
	int sizeof_s;
	for(sizeof_s = 0; s[sizeof_s] != '\0'; ++sizeof_s);
	if (sizeof_s != sizeof_attack) return false;
	else {
		for (int i = 0; i < sizeof_attack; i++){
			if (s[i] != attack[i]){
				return false;
			}
		}
	}
	return true;
}

boolean IsLevelUp(char s[]){
	char levelUp[8];
	levelUp[0] = 'L';
	levelUp[1] = 'E';
	levelUp[2] = 'V';
	levelUp[3] = 'E';
	levelUp[4] = 'L';
	levelUp[5] = '_';
	levelUp[6] = 'U';
	levelUp[7] = 'P';

	int sizeof_levelUp = sizeof(levelUp) / sizeof(char);
int sizeof_s;
	for(sizeof_s = 0; s[sizeof_s] != '\0'; ++sizeof_s);
	if (sizeof_s != sizeof_levelUp) return false;
	else {
		for (int i = 0; i < sizeof_levelUp ;i++){
			if (s[i] != levelUp[i]){
				return false;
			}
		}
	}
	return true;
}

boolean IsMove(char s[]){
	char move[4];
	move[0] = 'M';
	move[1] = 'O';
	move[2] = 'V';
	move[3] = 'E';

	int sizeof_move = sizeof(move) / sizeof(char);
int sizeof_s;
	for(sizeof_s = 0; s[sizeof_s] != '\0'; ++sizeof_s);

	if (sizeof_s != sizeof_move) return false;
	else {
		for (int i = 0; i < sizeof_move; i++){
			if (s[i] != move[i]){
				return false;
			}
		}
	}
	return true;
}

boolean IsSkill(char s[]){
	char skill[5];
	skill[0] = 'S';
	skill[1] = 'K';
	skill[2] = 'I';
	skill[3] = 'L';
	skill[4] = 'L';

	int sizeof_skill = sizeof(skill) / sizeof(char);
	int sizeof_s;
	for(sizeof_s = 0; s[sizeof_s] != '\0'; ++sizeof_s);
	if (sizeof_s != sizeof_skill) return false;
	else {
		for (int i = 0; i < sizeof_skill; i++){
			if (s[i] != skill[i]){
				return false;
			}
		}
	}
	return true;
}

boolean IsUndo(char s[]){
	char undo[4];
	undo[0] = 'U';
	undo[1] = 'N';
	undo[2] = 'D';
	undo[3] = 'O';

	int sizeof_undo = sizeof(undo) / sizeof(char);
	int sizeof_s;
	for(sizeof_s = 0; s[sizeof_s] != '\0'; ++sizeof_s);
	if (sizeof_s != sizeof_undo) return false;
	else {
		for (int i = 0; i < sizeof_undo; i++){
			if (s[i] != undo[i]){
				return false;
			}
		}
	}
	return true;
}

boolean IsEndTurn (char s[]){
	char endTurn[8];
	endTurn[0] = 'E';
	endTurn[1] = 'N';
	endTurn[2] = 'D';
	endTurn[3] = '_';
	endTurn[4] = 'T';
	endTurn[5] = 'U';
	endTurn[6] = 'R';
	endTurn[7] = 'N';

	int sizeof_endTurn = sizeof(endTurn) / sizeof(char);
	int sizeof_s;
	for(sizeof_s = 0; s[sizeof_s] != '\0'; ++sizeof_s);	
		if (sizeof_s != sizeof_endTurn) return false;
	else {
		for (int i = 0; i < sizeof_endTurn; i++){
			if (s[i] != endTurn[i]){
				return false;
			}
		}
	}
	return true;
}

boolean IsSave (char s[]){
	char save[4];
	save[0] = 'S';
	save[1] = 'A';
	save[2] = 'V';
	save[3] = 'E';

	int sizeof_save = sizeof(save) / sizeof(char);
		int sizeof_s;
	for(sizeof_s = 0; s[sizeof_s] != '\0'; ++sizeof_s);
	if (sizeof_s != sizeof_save) return false;
	else {
		for (int i = 0; i < sizeof_save; i++){
			if (s[i] != save[i]){
				return false;
			}
		}
	}
	return true;
}