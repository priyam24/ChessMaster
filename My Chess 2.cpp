#include<iostream>
#include<conio.h>
#include "board.txt"
#include "knight.txt"
#include "pawn.txt"
#include "king.txt"
#include "queen.txt"
#include "rook.txt"
#include "bishop.txt"

using namespace std;

static int qb_cnt=0,qw_cnt=0,rb_cnt=0,rw_cnt=0,bb_cnt=0,bw_cnt=0,kb_cnt=0,kw_cnt=0;


int main()
{
	cout<<"\nWELCOME TO THE WONDERFUL GAME OF CHESS !\n\n";
	cout<<"THE LOWERCASE LETTERS RESEMBLES THE WHITE PIECES AND \nTHE UPPERCASE LETTERS RESEMBLES THE BLACK.\n\n"
	<<"FOR SELECTING THE WHITE'S PIECES DO AS FOLLOWS :\n"
	<<"\nFOR KING   PRESS x\nFOR QUEEN  PRESS q\nFOR ROOK   PRESS r\nFOR BISHOP PRESS b\nFOR KNIGHT PRESS k\nFOR PAWN   PRESS p\n"
	<<"\nFOR SELECTING THE BLACK'S PIECES DO AS FOLLOWS :\n"
	<<"\nFOR KING   PRESS X\nFOR QUEEN  PRESS Q\nFOR ROOK   PRESS R\nFOR BISHOP PRESS B\nFOR KNIGHT PRESS K\nFOR PAWN   PRESS P\n\n";
	
	string name1,name2,name11,name22;
	char chp;
	cout<<"ENTER NAME OF PLAYER 1 : ";
	cin>>name11;
	cout<<"ENTER NAME OF PLAYER 2 : ";
	cin>>name22;
	cout<<"\nPRESS 'W' FOR WHITE AND 'B' FOR BLACK";
	cout<<"\n\n"<<name11<<" CHOOSE YOUR SIDE : ";
	cin>>chp;
	if(chp=='W'||chp=='w'){
		name1=name11;
		name2=name22;
	}
	else{
		name1=name22;
		name2=name11;
	}
	
	board B;

	king xb('b'),xw('w');
	
	queen qb[9],qw[9];
	qb[qb_cnt]=queen(0,3);
	qw[qw_cnt]=queen(7,3);
	for(int i=1;i<9;i++){
		qb[i]=queen(-1,-1);
		qw[i]=queen(-1,-1);
	}
	
	rook rb[10],rw[10];
	rb[rb_cnt]=rook(0,0);
	rb[++rb_cnt]=rook(0,7);
	rw[rw_cnt]=rook(7,0);
	rw[++rw_cnt]=rook(7,7);
	for(int i=2;i<10;i++){
		rb[i]=rook(-1,-1);
		rw[i]=rook(-1,-1);
	}
	
	knight kb[10],kw[10];
	kb[kb_cnt]=knight(0,1);
	kb[++kb_cnt]=knight(0,6);
	kw[kw_cnt]=knight(7,1);
	kw[++kw_cnt]=knight(7,6);
	for(int i=2;i<10;i++){
		kb[i]=knight(-1,-1);
		kw[i]=knight(-1,-1);
	}
	
	bishop bb[10],bw[10];
	bb[bb_cnt]=bishop(0,2);
	bb[++bb_cnt]=bishop(0,5);
	bw[bw_cnt]=bishop(7,2);
	bw[++bw_cnt]=bishop(7,5);
	for(int i=2;i<10;i++){
		bb[i]=bishop(-1,-1);
		bw[i]=bishop(-1,-1);
	}
	
	pawn pb[8],pw[8];
	for(int i=0;i<8;i++){
		pb[i]=pawn('b',i);
		pw[i]=pawn('w',i);
	}

	char ch;
	int m,n,mp,np,vm;
	int total_movesw=0,total_movesb=0;
	
	while(1){
		if(total_movesw==0)
		cout<<"\n\nPRESS ANY KEY TO DISPLAY THE CHESS BOARD\n";
		else cout<<"\n\nPRESS ANY KEY TO ROTATE BOARD FOR WHITE'S TURN\n";
		getch();
		system("cls");
		B.show('w');
		cout<<"\nIT'S "<<name1<<"'S TURN\n";
		cout<<"SELECT A PIECE\n";
		ch=getche();
		cout<<"\nENTER COORDINATES OF PREVIOUS POSITION\n";
		cin>>mp>>np;
		cout<<"\nENTER COORDINATES OF CURRENT POSITION OF YOUR CHOICE\n";
		cin>>m>>n;
		
		try{
			if(ch!='x'&&ch!='q'&&ch!='r'&&ch!='b'&&ch!='k'&&ch!='p'){
				throw ch;
			}
			else if(m>7||m<0||n>7||n<0){
				throw ch;
			}
			else if(B.getb(mp,np)=='-'){
				throw ch;
			}
		}
		catch(char c){
			cout<<"\nINVALID INPUT\n";
            continue;
		}
		switch(ch){
			case 'x':
				vm=xw.virtual_move(mp,np,m,n,'w',B);
				if(vm==1||vm==100){
					if(vm==100)
					{
						cout<<"\nWrong Selection\n";
						goto jump;
					}
				cout<<"\nINVALID INPUT OR WRONG SELECTION OR MAYBE THERE IS A CHECK\n";
				cout<<"GIVE ANOTHER INPUT\n";
				cout<<"vm="<<vm<<endl;
				goto jump;	
				}
				else{
					switch(vm){
						case 22:
							for(int i=0;i<9;i++){
								if(qb[i].istrue(m,n))
								qb[i].vanish(qb[i]);
							}
						break;
						case 33:
							for(int i=0;i<10;i++){
							if(kb[i].istrue(m,n))
							kb[i].vanish(kb[i]);
							}
						break;
						case 44:
							for(int i=0;i<10;i++){
							if(rb[i].istrue(m,n))
							rb[i].vanish(rb[i]);
							}
						break;
						case 55:
							for(int i=0;i<10;i++){
							if(bb[i].istrue(m,n))
							bb[i].vanish(bb[i]);
							}
						break;
						case 66:
							for(int i=0;i<8;i++){
							if(pb[i].istrue(m,n))
							pb[i].vanish(pb[i]);
							}
						break;
						default:
							break;
					}
					xw.final_move(mp,np,m,n,'w',B);
					goto jump1;
				}
			case 'q':
				for(int i=0;i<9;i++){
					vm=qw[i].virtual_move(mp,np,m,n,'w',B);
				if(vm==1||vm==100){
					if(vm==100)
					{
						if(i==8){
							cout<<"\nWrong Selection\n";
							goto jump;
						}
						else continue;
					}
					cout<<"\nINVALID INPUT OR WRONG SELECTION OR MAYBE THERE IS A CHECK\n";
				    cout<<"GIVE ANOTHER INPUT\n";
				    cout<<"vm="<<vm<<endl;
				    goto jump;
				}
				else{
					switch(vm){
						case 22:
							for(int i=0;i<9;i++){
								if(qb[i].istrue(m,n))
								qb[i].vanish(qb[i]);
							}
						break;
						case 33:
							for(int i=0;i<10;i++){
							if(kb[i].istrue(m,n))
							kb[i].vanish(kb[i]);
							}
						break;
						case 44:
							for(int i=0;i<10;i++){
							if(rb[i].istrue(m,n))
							rb[i].vanish(rb[i]);
							}
						break;
						case 55:
							for(int i=0;i<10;i++){
							if(bb[i].istrue(m,n))
							bb[i].vanish(bb[i]);
							}
						break;
						case 66:
							for(int i=0;i<8;i++){
							if(pb[i].istrue(m,n))
							pb[i].vanish(pb[i]);
							}
						break;
						default:
							break;
					}
					qw[i].final_move(mp,np,m,n,'w',B);
					goto jump1;
				}
				}
			case 'k':
				for(int i=0;i<10;i++){
					vm=kw[i].virtual_move(mp,np,m,n,'w',B);
					if(vm==1||vm==100){
					if(vm==100)
					{
						if(i==9){
							cout<<"\nWrong Selection\n";
							goto jump;
						}
						else continue;
					}
					cout<<"\nINVALID INPUT OR WRONG SELECTION OR MAYBE THERE IS A CHECK\n";
				    cout<<"GIVE ANOTHER INPUT\n";
					cout<<"vm="<<vm<<endl;
				    goto jump;	
				}
				else{
				    switch(vm){
						case 22:
							for(int i=0;i<9;i++){
								if(qb[i].istrue(m,n))
								qb[i].vanish(qb[i]);
							}
						break;
						case 33:
							for(int i=0;i<10;i++){
							if(kb[i].istrue(m,n))
							kb[i].vanish(kb[i]);
							}
						break;
						case 44:
							for(int i=0;i<10;i++){
							if(rb[i].istrue(m,n))
							rb[i].vanish(rb[i]);
							}
						break;
						case 55:
							for(int i=0;i<10;i++){
							if(bb[i].istrue(m,n))
							bb[i].vanish(bb[i]);
							}
						break;
						case 66:
							for(int i=0;i<8;i++){
							if(pb[i].istrue(m,n))
							pb[i].vanish(pb[i]);
							}
						break;
						default:
							break;
					}
					kw[i].final_move(mp,np,m,n,'w',B);
					goto jump1;
				}
				}
			case 'r':
				for(int i=0;i<10;i++){
					vm=rw[i].virtual_move(mp,np,m,n,'w',B);
					if(vm==1||vm==100){
					if(vm==100)
					{
						if(i==9){
							cout<<"\nWrong Selection\n";
							goto jump;
						}
						else continue;
					}
					cout<<"\nINVALID INPUT OR WRONG SELECTION OR MAYBE THERE IS A CHECK\n";
				    cout<<"GIVE ANOTHER INPUT\n";
				    cout<<"vm="<<vm<<endl;
				    goto jump;	
				}
				else{
					switch(vm){
						case 22:
							for(int i=0;i<9;i++){
								if(qb[i].istrue(m,n))
								qb[i].vanish(qb[i]);
							}
						break;
						case 33:
							for(int i=0;i<10;i++){
							if(kb[i].istrue(m,n))
							kb[i].vanish(kb[i]);
							}
						break;
						case 44:
							for(int i=0;i<10;i++){
							if(rb[i].istrue(m,n))
							rb[i].vanish(rb[i]);
							}
						break;
						case 55:
							for(int i=0;i<10;i++){
							if(bb[i].istrue(m,n))
							bb[i].vanish(bb[i]);
							}
						break;
						case 66:
							for(int i=0;i<8;i++){
							if(pb[i].istrue(m,n))
							pb[i].vanish(pb[i]);
							}
						break;
						default:
							break;
					}
					rw[i].final_move(mp,np,m,n,'w',B);
					goto jump1;
				}
				}
			case 'p':
				for(int i=0;i<8;i++){
					vm=pw[i].virtual_move(mp,np,m,n,'w',B);
					if(vm==1||vm==100){
					if(vm==100)
					{
						if(i==7){
							cout<<"\nWrong Selection\n";
							goto jump;
						}
						else continue;
					}
					cout<<"\nINVALID INPUT OR WRONG SELECTION OR MAYBE THERE IS A CHECK\n";
				    cout<<"GIVE ANOTHER INPUT\n";
				    cout<<"vm="<<vm<<endl;
				    goto jump;	
				}
				else{
					switch(vm){
						case 22:
							for(int i=0;i<9;i++){
								if(qb[i].istrue(m,n))
								qb[i].vanish(qb[i]);
							}
						break;
						case 33:
							for(int i=0;i<10;i++){
							if(kb[i].istrue(m,n))
							kb[i].vanish(kb[i]);
							}
						break;
						case 44:
							for(int i=0;i<10;i++){
							if(rb[i].istrue(m,n))
							rb[i].vanish(rb[i]);
							}
						break;
						case 55:
							for(int i=0;i<10;i++){
							if(bb[i].istrue(m,n))
							bb[i].vanish(bb[i]);
							}
						break;
						case 66:
							for(int i=0;i<8;i++){
							if(pb[i].istrue(m,n))
							pb[i].vanish(pb[i]);
							}
						break;
						default:
							break;
					}
					switch(pw[i].final_move(mp,np,m,n,'w',B)){
						case 'q':
							qw[++qw_cnt]=queen(m,n);
							break;
						case 'r':
							rw[++rw_cnt]=rook(m,n);
							break;
						case 'b':
							bw[++bw_cnt]=bishop(m,n);
							break;
						case 'k':
							kw[++kw_cnt]=knight(m,n);
							break;
						default:
							break;	
					}
					goto jump1;
				}
				}
			case 'b':
				for(int i=0;i<10;i++){
					vm=bw[i].virtual_move(mp,np,m,n,'w',B);
					if(vm==1||vm==100){
					if(vm==100)
					{
						if(i==9){
							cout<<"\nWrong Selection\n";
							goto jump;
						}
						else continue;
					}
					cout<<"\nINVALID INPUT OR WRONG SELECTION OR MAYBE THERE IS A CHECK\n";
				    cout<<"GIVE ANOTHER INPUT\n";
				    cout<<"vm="<<vm<<endl;
				    goto jump;	
				}
				else{
					switch(vm){
						case 22:
							for(int i=0;i<9;i++){
								if(qb[i].istrue(m,n))
								qb[i].vanish(qb[i]);
							}
						break;
						case 33:
							for(int i=0;i<10;i++){
							if(kb[i].istrue(m,n))
							kb[i].vanish(kb[i]);
							}
						break;
						case 44:
							for(int i=0;i<10;i++){
							if(rb[i].istrue(m,n))
							rb[i].vanish(rb[i]);
							}
						break;
						case 55:
							for(int i=0;i<10;i++){
							if(bb[i].istrue(m,n))
							bb[i].vanish(bb[i]);
							}
						break;
						case 66:
							for(int i=0;i<8;i++){
							if(pb[i].istrue(m,n))
							pb[i].vanish(pb[i]);
							}
						break;
						default:
							break;
					}
					bw[i].final_move(mp,np,m,n,'w',B);
					goto jump1;
				}
				}
			default:
				cout<<"\n*INVALID INPUT*\n";	
			    goto jump;
		}
		jump:
			continue;
		jump1:
			system("cls");
			B.show('w');
			cout<<"\nTotal Moves for White till now = "<<++total_movesw;
			int v_chk=B.alt_check(B,m,n,'w');
			int vir_chkmtw=B.check_without_king(B,m,n,'w');
			if(vir_chkmtw==0){
				vir_chkmtw=B.check_with_king(B,m,n,'w');
				if(vir_chkmtw==1){
					vir_chkmtw=B.check(B,m,n,'b');
					if(vir_chkmtw==1)
					vir_chkmtw=0;
				}
			}
			int chkmt_status=B.get_checkmate_status(B,'b',ch,m,n,vir_chkmtw,v_chk);
			if(chkmt_status==1){
				cout<<"\nCHECKMATE : "<<name1<<" WON\n";
				break;
			}
			/*if(B.get_stalemate_status(B,'b')==1){
				cout<<"\nSTALEMATE : DRAW GAME\n";
				break;
			}*/
			goto jump2;
		jump2:
		cout<<"\n\nPRESS ANY KEY TO ROTATE BOARD FOR BLACK'S TURN\n";
		getch();
		system("cls");
		B.show('b');		
		cout<<"\nIT'S "<<name2<<"'S TURN\n";
		cout<<"SELECT A PIECE\n";
		ch=getche();
		cout<<"\nENTER COORDINATES OF PREVIOUS POSITION\n";
		cin>>mp>>np;
		cout<<"ENTER COORDINATES OF CURRENT POSITION OF YOUR CHOICE\n";
		cin>>m>>n;
		
		try{
			if(ch!='X'&&ch!='Q'&&ch!='R'&&ch!='B'&&ch!='K'&&ch!='P'){
				throw ch;
			}
			else if(m>7||m<0||n>7||n<0){
				throw ch;
			}
			else if(B.getb(mp,np)=='-'){
				throw ch;
			}
		}
		catch(char c){
			cout<<"\nINVALID INPUT\n";
            goto jump2;
		}
		
		switch(ch){
			case 'X':
				vm=xb.virtual_move(mp,np,m,n,'b',B);
				if(vm==1||vm==100){
					if(vm==100)
					{
						cout<<"\nWrong Selection\n";
						goto jump2;
					}					
				cout<<"\nINVALID INPUT OR WRONG SELECTION OR MAYBE THERE IS A CHECK\n";
				cout<<"GIVE ANOTHER INPUT\n";
				cout<<"vm="<<vm<<endl;
				goto jump2;	
				}
				else{
					switch(vm){
						case 2:
							for(int i=0;i<9;i++){
								if(qw[i].istrue(m,n))
								qw[i].vanish(qw[i]);
							}
						break;
						case 3:
							for(int i=0;i<10;i++){
							if(kw[i].istrue(m,n))
							kw[i].vanish(kw[i]);
							}
						break;
						case 4:
							for(int i=0;i<10;i++){
							if(rw[i].istrue(m,n))
							rw[i].vanish(rw[i]);
							}
						break;
						case 5:
							for(int i=0;i<10;i++){
							if(bw[i].istrue(m,n))
							bw[i].vanish(bw[i]);
							}
						break;
						case 6:
							for(int i=0;i<8;i++){
							if(pw[i].istrue(m,n))
							pw[i].vanish(pw[i]);
							}
						break;
						default:
							break;
					}
					xb.final_move(mp,np,m,n,'b',B);
					break;
				}
				goto jump3;
			case 'Q':
				for(int i=0;i<9;i++){
					vm=qb[i].virtual_move(mp,np,m,n,'b',B);
					if(vm==1||vm==100){
					if(vm==100)
					{
						if(i==9){
							cout<<"\nWrong Selection\n";
							goto jump2;
						}
						else continue;
					}
					cout<<"\nINVALID INPUT OR WRONG SELECTION OR MAYBE THERE IS A CHECK\n";
				    cout<<"GIVE ANOTHER INPUT\n";
				    cout<<"vm="<<vm<<endl;
				    goto jump2;	
				}
				else{
					switch(vm){
						case 2:
							for(int i=0;i<9;i++){
								if(qw[i].istrue(m,n))
								qw[i].vanish(qw[i]);
							}
						break;
						case 3:
							for(int i=0;i<10;i++){
							if(kw[i].istrue(m,n))
							kw[i].vanish(kw[i]);
							}
						break;
						case 4:
							for(int i=0;i<10;i++){
							if(rw[i].istrue(m,n))
							rw[i].vanish(rw[i]);
							}
						break;
						case 5:
							for(int i=0;i<10;i++){
							if(bw[i].istrue(m,n))
							bw[i].vanish(bw[i]);
							}
						break;
						case 6:
							for(int i=0;i<8;i++){
							if(pw[i].istrue(m,n))
							pw[i].vanish(pw[i]);
							}
						break;
						default:
							break;
					}
					qb[i].final_move(mp,np,m,n,'b',B);
					break;
				}
				}
				goto jump3;
			case 'K':
				for(int i=0;i<10;i++){
					vm=kb[i].virtual_move(mp,np,m,n,'b',B);
					if(vm==1||vm==100){
					if(vm==100)
					{
						if(i==9){
							cout<<"\nWrong Selection\n";
							goto jump2;
						}
						else continue;
					}
					cout<<"\nINVALID INPUT OR WRONG SELECTION OR MAYBE THERE IS A CHECK\n";
				    cout<<"GIVE ANOTHER INPUT\n";
					cout<<"vm="<<vm<<endl;
				    goto jump2;	
				}
				else{
					switch(vm){
						case 2:
							for(int i=0;i<9;i++){
								if(qw[i].istrue(m,n))
								qw[i].vanish(qw[i]);
							}
						break;
						case 3:
							for(int i=0;i<10;i++){
							if(kw[i].istrue(m,n))
							kw[i].vanish(kw[i]);
							}
						break;
						case 4:
							for(int i=0;i<10;i++){
							if(rw[i].istrue(m,n))
							rw[i].vanish(rw[i]);
							}
						break;
						case 5:
							for(int i=0;i<10;i++){
							if(bw[i].istrue(m,n))
							bw[i].vanish(bw[i]);
							}
						break;
						case 6:
							for(int i=0;i<8;i++){
							if(pw[i].istrue(m,n))
							pw[i].vanish(pw[i]);
							}
						break;
						default:
							break;
					}
					kb[i].final_move(mp,np,m,n,'b',B);
					break;
				}
				}
				goto jump3;
			case 'R':          
				for(int i=0;i<10;i++){
					vm=rb[i].virtual_move(mp,np,m,n,'b',B);
					if(vm==1||vm==100){
					if(vm==100)
					{
						if(i==9){
							cout<<"\nWrong Selection\n";
							goto jump2;
						}
						else continue;
					}
					cout<<"\nINVALID INPUT OR WRONG SELECTION OR MAYBE THERE IS A CHECK\n";
				    cout<<"GIVE ANOTHER INPUT\n";
				    cout<<"vm="<<vm<<endl;
				    goto jump2;	
				}
				else{
					switch(vm){
						case 2:
							for(int i=0;i<9;i++){
								if(qw[i].istrue(m,n))
								qw[i].vanish(qw[i]);
							}
						break;
						case 3:
							for(int i=0;i<10;i++){
							if(kw[i].istrue(m,n))
							kw[i].vanish(kw[i]);
							}
						break;
						case 4:
							for(int i=0;i<10;i++){
							if(rw[i].istrue(m,n))
							rw[i].vanish(rw[i]);
							}
						break;
						case 5:
							for(int i=0;i<10;i++){
							if(bw[i].istrue(m,n))
							bw[i].vanish(bw[i]);
							}
						break;
						case 6:
							for(int i=0;i<8;i++){
							if(pw[i].istrue(m,n))
							pw[i].vanish(pw[i]);
							}
						break;
						default:
							break;
					}
					rb[i].final_move(mp,np,m,n,'b',B);
					break;
				}
				}
				goto jump3;
			case 'P':
				for(int i=0;i<8;i++){
					vm=pb[i].virtual_move(mp,np,m,n,'b',B);
					if(vm==1||vm==100){
					if(vm==100)
					{
						if(i==7){
							cout<<"\nWrong Selection\n";
							goto jump2;
						}
						else continue;
					}
					cout<<"\nINVALID INPUT OR WRONG SELECTION OR MAYBE THERE IS A CHECK\n";
				    cout<<"GIVE ANOTHER INPUT\n";
				    cout<<"vm="<<vm<<endl;
				    goto jump2;	
				}
				else {
					switch(vm){
						case 2:
							for(int i=0;i<9;i++){
								if(qw[i].istrue(m,n))
								qw[i].vanish(qw[i]);
							}
						break;
						case 3:
							for(int i=0;i<10;i++){
							if(kw[i].istrue(m,n))
							kw[i].vanish(kw[i]);
							}
						break;
						case 4:
							for(int i=0;i<10;i++){
							if(rw[i].istrue(m,n))
							rw[i].vanish(rw[i]);
							}
						break;
						case 5:
							for(int i=0;i<10;i++){
							if(bw[i].istrue(m,n))
							bw[i].vanish(bw[i]);
							}
						break;
						case 6:
							for(int i=0;i<8;i++){
							if(pw[i].istrue(m,n))
							pw[i].vanish(pw[i]);
							}
						break;
						default:
							break;
					}
					switch(pb[i].final_move(mp,np,m,n,'b',B)){
						case 'Q':
							qb[++qb_cnt]=queen(m,n);
							break;
						case 'R':
							rb[++rb_cnt]=rook(m,n);
							break;
						case 'B':
							bb[++bb_cnt]=bishop(m,n);
							break;
						case 'K':
							kb[++kb_cnt]=knight(m,n);
							break;
						default:
							break;	
					}
					break;
				}
				}
				goto jump3;
			case 'B':
				for(int i=0;i<10;i++){
					vm=bb[i].virtual_move(mp,np,m,n,'b',B);
					if(vm==1||vm==100){
					if(vm==100)
					{
						if(i==9){
							cout<<"\nWrong Selection\n";
							goto jump2;
						}
						else continue;
					}
					cout<<"\nINVALID INPUT OR WRONG SELECTION OR MAYBE THERE IS A CHECK\n";
				    cout<<"GIVE ANOTHER INPUT\n";
				    cout<<"vm="<<vm<<endl;
				    goto jump2;	
				}
				else{
					switch(vm){
						case 2:
							for(int i=0;i<9;i++){
								if(qw[i].istrue(m,n))
								qw[i].vanish(qw[i]);
							}
						break;
						case 3:
							for(int i=0;i<10;i++){
							if(kw[i].istrue(m,n))
							kw[i].vanish(kw[i]);
							}
						break;
						case 4:
							for(int i=0;i<10;i++){
							if(rw[i].istrue(m,n))
							rw[i].vanish(rw[i]);
							}
						break;
						case 5:
							for(int i=0;i<10;i++){
							if(bw[i].istrue(m,n))
							bw[i].vanish(bw[i]);
							}
						break;
						case 6:
							for(int i=0;i<8;i++){
							if(pw[i].istrue(m,n))
							pw[i].vanish(pw[i]);
							}
						break;
						default:
							break;
					}
					bb[i].final_move(mp,np,m,n,'b',B);
					break;
				}
				}
				goto jump3;
			default:
			cout<<"\n*INVALID INPUT*\n";
			goto jump2;
		}
		jump3:
	    system("cls");
		B.show('b');
		cout<<"\nTotal Moves for Black till now = "<<++total_movesb;
		v_chk=B.alt_check(B,m,n,'b');
			int vir_chkmtb=B.check_without_king(B,m,n,'b');
			if(vir_chkmtb==0){
				vir_chkmtb=B.check_with_king(B,m,n,'b');
				if(vir_chkmtb==1){
					vir_chkmtb=B.check(B,m,n,'w');
					if(vir_chkmtb==1)
					vir_chkmtb=0;
				}
			}
		chkmt_status=B.get_checkmate_status(B,'w',ch,m,n,vir_chkmtb,v_chk);
		if(chkmt_status==1){
				cout<<"\nCHECKMATE : "<<name2<<" WON\n";
				break;
		}
		/*if(B.get_stalemate_status(B,'w')==1){
			cout<<"STALEMATE : DRAW GAME\n";
			break;
		}*/	
	}
	
	cout<<"\n\n                ================== GAME OVER ==================";
	cout<<"\n================================== THANK YOU ===================================\n\n";
	getch();
	return 0;
}
