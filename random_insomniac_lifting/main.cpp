//#include <iostream>
//#include <vector>
#include <stdlib.h>
#include <time.h>
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include "ships.cpp"

#define N 12
#define PIRATE_HP 1200
#define PORT_HEAL 30
#define PORT_DAMAGE 15
#define WEATHER_BASE_DMG 15
#define NUM_OF_SHIPS 40
#define GOLD_TARGET 2000

using namespace std;

void WorldInit(chart ***mapp);
bool WeathTreasCheck(chart ***mapp, vector<string> *info_msgs);
void WeatherChange(chart ***mapp);
bool PortOperate(chart ***mapp, vector<string> *info_msgs);
int RemoveDeadShips(chart ***mapp, vector<ship *> *vec, vector<ship *> *dvec);
void printMapp(chart ***mapp);
void vec_sorting(vector<ship *> *ship_vec);
bool PauseMenu(chart ***mapp, vector<ship *> *all_ships, vector<ship *> *ship_vec, vector<ship *> *rem_ships);
void FreeGoldAvgWeath(chart ***mapp);

int ship::dead_ships=0;                              //arxikopoihsh static metavliton
int ship::add_ships=0;
int ship::rem_ships=0;
int ship::shipcount=0;
int ship::total_gold_in_=0;
int ship::total_gold_out_=0;
int ship::total_dmg_in_=0;
int ship::total_heal_in_=0;
int ship::total_blocks_moved_=0;

int pirate::shipcount=0;
int pirate::dead_ships=0;
int pirate::p_shipcount=0;
int pirate::total_gold_in_=0;
int pirate::total_gold_out_=0;
int pirate::total_dmg_in_=0;
int pirate::total_heal_in_=0;
int pirate::total_blocks_moved_=0;
int pirate::total_dmg_out_=0;
int pirate::total_attacks_=0;
int pirate::total_kills_=0;

int mercantile::shipcount=0;
int mercantile::dead_ships=0;
int mercantile::total_gold_in_=0;
int mercantile::total_gold_out_=0;
int mercantile::total_dmg_in_=0;
int mercantile::total_heal_in_=0;
int mercantile::total_blocks_moved_=0;
int mercantile::total_dock_trades_=0;

int repairing::shipcount=0;
int repairing::dead_ships=0;
int repairing::total_gold_in_=0;
int repairing::total_gold_out_=0;
int repairing::total_dmg_in_=0;
int repairing::total_heal_in_=0;
int repairing::total_blocks_moved_=0;
int repairing::total_heal_out_=0;
int repairing::total_heals_=0;

int exploring::shipcount=0;
int exploring::dead_ships=0;
int exploring::e_shipcount=0;
int exploring::total_gold_in_=0;
int exploring::total_gold_out_=0;
int exploring::total_dmg_in_=0;
int exploring::total_heal_in_=0;
int exploring::total_blocks_moved_=0;
int exploring::total_evades_=0;

int prt_r::shipcount=0;
int prt_r::dead_ships=0;
int prt_r::total_gold_in_=0;
int prt_r::total_gold_out_=0;
int prt_r::total_dmg_in_=0;
int prt_r::total_heal_in_=0;
int prt_r::total_blocks_moved_=0;
int prt_r::total_heal_out_=0;
int prt_r::total_heals_=0;

int exp_s::shipcount=0;
int exp_s::dead_ships=0;
int exp_s::total_gold_in_=0;
int exp_s::total_gold_out_=0;
int exp_s::total_dmg_in_=0;
int exp_s::total_heal_in_=0;
int exp_s::total_blocks_moved_=0;
int exp_s::total_sups_=0;

int k, ports_count=0, dock_attacks=0, dock_kills=0, dock_heals=0, dock_heal_out=0,free_gold,gold_places, weath_attacks=0, weath_kills=0,top_gold;
float avg_weath;
string top_ship;

HANDLE hConsole;


int main()
{
    int i,j,m;
    
    
    bool move_flag, oper_flag, death_flag, endGame=false;
    //string *msg_delete;
    stringstream ss;
    
    vector<ship *> ship_vec;      //edo einai apothikeumena ola ta 'en zwh' ploia
    vector<ship *> dead_ship_vec;  //edo einai apothikeumena ola ta 'nekra' ploia
    vector<ship *> all_ships;    //edo apothikeuontai ola ta ploia xoris na afairethei kanena
    vector<ship *> rem_ships;    //edo epothikeuontai ola ta ploia pou afairountai apo ti prosomoiosi me paremvasi tou xristi
    vector<string> info_msgs;    //edo apothikeuontai ta minimata pou tha emfanizontai sto telos kathe gyrou
    info_msgs.clear();
    
    pirate *prt;
    mercantile *merc;
    repairing *rpr;
    exploring *exp;
    prt_r *prtr;
    exp_s *exps;
    
    
    
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);           //entoles allagis xromatos grammatoseiras
    SetConsoleTextAttribute(hConsole, 15 + 0*16);
    
    HWND console = GetConsoleWindow();                     //entoles allagis megethous parathyrou cmd
    RECT r;
    GetWindowRect(console, &r); 
    MoveWindow(console, r.left, r.top, 800, 600, TRUE);
        
    chart ***mapp;
    mapp=new chart **[N];
    for(i=0;i<N;i++){mapp[i]=new chart *[N];}
   
       
    cout<<"System is now creating the world."<<endl;
    Sleep(500);
    cout<<"Please wait... ";
    Sleep(1000);
    
    WorldInit(mapp);      // synartisi topothetisis limanion kai thisauron se tyxaia simeia pano sto xarti
                          //den mporo na ypologiso ta ports_count kai treas_count an den doso deiktes san orisma sti WorldInit
    
    cout<<"OK!"<<endl;
    Sleep(500);
    cout<<"The world is ready.";
    //Sleep(500);
    
    system("CLS");
    cout<<"\nWORLD:"<<endl;
    cout<<endl;
    SetConsoleTextAttribute(hConsole, 0 + 0*16);
    cout<<"_______________________________________________\n";
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            if(mapp[i][j]->getPort() == true){
                SetConsoleTextAttribute(hConsole, 15 + 3*16);   // 3 = gkrimple            
                cout<<" ";
                SetConsoleTextAttribute(hConsole, 0 + 3*16);   // 1 = mple
                cout<<"D";
                SetConsoleTextAttribute(hConsole, 7 + 3*16);
                if(j==N-1){    
                    cout<<" ";
                }
                else{
                    cout<<" |";
                }
                SetConsoleTextAttribute(hConsole, 15 + 0*16);   // 0 = mavro, 15 = aspro
            }
            else if(mapp[i][j]->getTreasure() != 0){
                SetConsoleTextAttribute(hConsole, 15 + 3*16);
                cout<<" ";
                SetConsoleTextAttribute(hConsole, 14 + 3*16);  //14 = kitrino
                cout<<"g";
                SetConsoleTextAttribute(hConsole, 7 + 3*16);
                if(j==N-1){
                    cout<<" ";
                }
                else{
                     cout<<" |";
                }
                SetConsoleTextAttribute(hConsole, 15 + 0*16);
            }
            else{
                SetConsoleTextAttribute(hConsole, 7 + 3*16); 
                if(j==N-1){
                    cout<<"   ";
                }
                else{
                    cout<<"   |";
                }
                SetConsoleTextAttribute(hConsole, 15 + 0*16);
            }
        }
          
        if(i==5){cout<<"    D = Dock\n";}
        else if(i==6){cout<<"    g = gold\n";}
        else{cout<<"\n";}
        SetConsoleTextAttribute(hConsole, 7 + 3*16);
        cout<<"   |   |   |   |   |   |   |   |   |   |   |   \n";
        
        if(i!=N-1){
            cout<<"---+---+---+---+---+---+---+---+---+---+---+---\n";
        }
        SetConsoleTextAttribute(hConsole, 15 + 0*16);
    }
    cout<<endl;
//==============================================================================    
    //edo ginetai dimiourgia kai topothetisi ton ploion pano sto xarti
    
    system("pause");
    cout<<"Now creating and placing some ships...";
    srand(time(0));
    for(k=0;k<NUM_OF_SHIPS;k++){
        i=rand()%N;
        j=rand()%N;
        while(mapp[i][j]->getPort() || (mapp[i][j]->getShip()!=0)){
            i=rand()%N;
            j=rand()%N;
        }
        if(k%6==0){
             mapp[i][j]->setShip(new pirate(i,j));      
        }
        else if(k%6==1){
             mapp[i][j]->setShip(new mercantile(i,j));
        }
        else if(k%6==2){
             mapp[i][j]->setShip(new repairing(i,j));
        }
        else if(k%6==3){
             mapp[i][j]->setShip(new exploring(i,j));
        }
        else if(k%6==4){
             
             mapp[i][j]->setShip(new prt_r(i,j));
        }
        else{
             mapp[i][j]->setShip(new exp_s(i,j));
        }
        ship_vec.push_back(mapp[i][j]->getShip());
        all_ships.push_back(mapp[i][j]->getShip());
    }
    
    
//==============================================================================    
    Sleep(1500);
    cout<<"OK!\nShips are ready.\n";
    Sleep(500);
    system("CLS");
    cout<<"\n               .:: DAY 0 ::.\n\n";
    printMapp(mapp);
    cout<<endl;
    cout<<"Press any key to begin simulation.\n\n";
    system("pause");
    Sleep(500);
    k=0;    
    
    while((top_gold < GOLD_TARGET) && (ship_vec.size()>0) && (!endGame)){     //epanalipseis prosompoiosis
        k++;
        ss.clear();
        ss.str("");
        ss << k;
        info_msgs.push_back("\nDAY "+ss.str()+" info:\n\n");
        system("CLS");
        cout<<"\n               .:: DAY "<<k<<" ::.\n";
        
        m=0;
        death_flag=false;
        
        death_flag = WeathTreasCheck(mapp,&info_msgs);                   //syllogi thisauron kai efarmogi zimias apo kairikes synthikes
        if(death_flag){
            m=RemoveDeadShips(mapp,&ship_vec,&dead_ship_vec);             //afairesi katestramenon ploion apo kairikes synthikes
        }
        WeatherChange(mapp);                                            //allagi kairikon synthikon 
        death_flag = PortOperate(mapp, &info_msgs);                        //leitourgia ton limanion
        if(death_flag){
            m=RemoveDeadShips(mapp,&ship_vec,&dead_ship_vec);               //afairesi ton peiratikon ploion pou katastrafikan apo epitheis limaniou
        }
        
        for(i=0;i<ship_vec.size();i++){                                         //epanalipseis klisis methodou metakinis gia kathe ploio
            move_flag=ship_vec[i]->Move(mapp);
            if(!move_flag){
                info_msgs.push_back("Ship "+ship_vec[i]->getName()+" was blocked!\n");
            }
            else{
                 info_msgs.push_back("Ship "+ship_vec[i]->getName()+" moved!\n");
            }
            if(ship_vec[i]->getSpeed()>1){
                move_flag=ship_vec[i]->Move(mapp);
            }
        }

        cout<<"\n";
        printMapp(mapp);                                                      //emfanisi tou xarti
        
        
        for(i=0;i<ship_vec.size();i++){                                         //epanaliseis klisis Operate gia kathe ploio
            oper_flag=false; 
            if( (prtr=dynamic_cast<prt_r *>(ship_vec[i])) !=0){
                
                oper_flag=prtr->Operate(mapp,&info_msgs);
                
            }                                                                  
            else if( (prt=dynamic_cast<pirate *>(ship_vec[i])) !=0){

                oper_flag = prt->Operate(mapp,&info_msgs);

                if(oper_flag){
                    m=RemoveDeadShips(mapp,&ship_vec,&dead_ship_vec);
                    if(m<i){
                        i--;
                    }
                    
                }
            }
            else if( (merc=dynamic_cast<mercantile *>(ship_vec[i])) !=0){
                oper_flag = merc->Operate(mapp,&info_msgs);
                
            }
            else if( (rpr=dynamic_cast<repairing *>(ship_vec[i])) !=0){
                
                oper_flag = rpr->Operate(mapp,&info_msgs);
                
            }
            else if( (exps=dynamic_cast<exp_s *>(ship_vec[i])) !=0){
                 oper_flag = exps->Operate(mapp,&info_msgs);
                 
            }
            else if( (exp=dynamic_cast<exploring *>(ship_vec[i])) !=0){
                
                oper_flag = exp->Operate(mapp,&info_msgs);
                
            }
            

        }
        Sleep(1000);
        system("CLS");

        cout<<"\n               .:: DAY "<<k<<" ::.\n";

        cout<<"\n";
        printMapp(mapp);                                                       //emfanisi tou xarti
        Sleep(1000);
        
        
        if(ship_vec.size()>0){                                                 //taksinomisi tou vector ton 'en zoi' kai symmetexonton sti
            vec_sorting(&ship_vec);                                           //sti prosomoiosi ploion me vasi ti posotita xrysou pou exoun
            top_gold=ship_vec.back()->getCurtreas(); 
            top_ship=ship_vec.back()->getName();
        }
        
        if(k%25==0){                                                            //kathe 25 gyrous prostithetai 10 tyxaies posotites xrysou
            srand(time(0));                                                      //se 10 tyxaia simeia tou xarti
            for(i=0;i<N;i++){
                m=rand()%N;
                j=rand()%N;
                while((mapp[m][j]->getPort()) || (mapp[m][j]->getTreasure()>0)){
                    m=rand()%N;
                    j=rand()%N;
                }
                mapp[m][j]->setTreasure((rand()%10) *10 +(rand()%10));
            }
                    
        }
        
        if(GetAsyncKeyState(0x49)){                                             //an patithike to 'i' emfanizontai plirofories tis imeras
                                   
            cout<<"\nPress any key to display last day's info.\n\n";
            system("pause");
        
            system("CLS");
            for(i=0;i<info_msgs.size();i++){
                cout<<info_msgs[i];
            }
            
            cout<<"\nPress any key to display alive ships joining simulation...\n\n";
            system("pause");
            system("CLS");
            cout<<"\n.:: ALIVE SHIPS ::.\n\n";
            if(ship_vec.size()<1){cout<<"No alive ships joining simulation.\n";}
            for(i=0;i<ship_vec.size();i++){
                ship_vec[i]->printInfo();
            }
            cout<<"\nPress any key to display destroyed ships...\n";
            cout<<endl;
            system("pause");
            system("cls");
            cout<<".:: DESTROYED SHIPS ::.\n\n";
            if(dead_ship_vec.size()<1){cout<<"No destroyed ships!\n";}
            for(i=0;i<dead_ship_vec.size();i++){
                dead_ship_vec[i]->printInfo();
            }
            cout<<"\nPress any key to display removed ships...\n";
            cout<<endl;
            system("pause");
            system("cls");
            cout<<".:: REMOVED SHIPS ::.\n\n";
            if(rem_ships.size()<1){cout<<"No removed ships!\n";}
            for(i=0;i<rem_ships.size();i++){
                rem_ships[i]->printInfo();
            }
            
            
            cout<<"\nPress any key to continue simulation.\n\n";
            system("pause");
            cout<<"\nReturning to simulation in 3 seconds. Please wait . ";
            Sleep(1000);
            cout<<". ";
            Sleep(1000);
            cout<<". ";
            Sleep(1000);
            cout<<". ";
            //Sleep(1000);
        }
        if(GetAsyncKeyState(0x50)){                                              //an patithike to 'p' mpainoume sto Pause Menu
             cout<<"\nPress any key to enter pause menu.\n\n";
             
             system("Pause");
             system("CLS");
             cout<<"PAUSE MENU\n";
             
             endGame = PauseMenu(mapp,&all_ships,&ship_vec,&rem_ships);
             
             if(!endGame){
                 
                 cout<<"\nReturning to simulation in 3 seconds. Please wait . ";
                 Sleep(1000);
                 cout<<". ";
                 Sleep(1000);
                 cout<<". ";
                 Sleep(1000);
                 cout<<". ";
             }
             else{
                  cout<<"\nTerminating simulation in 3 seconds. Please wait . ";
                  Sleep(1000);
                  cout<<". ";
                  Sleep(1000);
                  cout<<". ";
                  Sleep(1000);
                  cout<<". ";
             }
             
        }
        
        info_msgs.clear();
        //system("pause");
        
        
                        
    }                                                                         //i prosomoiosi termatizetai eite an to epileksei o xristis meso
                                                                             //tou pause menu eite an kapoio ploio kseperasei ta 2k gold eite
    if(!endGame){                                                             //an katastrafoun/afairethoun ola ta ploia pano sto xarti
        cout<<"\n\nSimulation COMPLETED!\n";                                   //kai sti synexeia emfanizontai ta katallila minimata
        if((ship_vec.size()==0) && (top_gold==GOLD_TARGET+1)){
            cout<<"\nNO SHIPS LEFT TO JOIN SIMULATION!\n";
        }
        else if(ship_vec.size()==0){
             cout<<"\nALL SHIPS WERE DESTROYED!\n";
        }
        else if(ship_vec.back()->getCurtreas() >= GOLD_TARGET){
            cout<<"\nSHIP "<<ship_vec.back()->getName()<<" REACHED THE GOLD TARGET OF "<<GOLD_TARGET<<" GOLD!\n";
        }
    }
    else{
         
         cout<<"\n\nSimulation TERMINATED!\n";                                     
    } 
    cout<<"\nPress any key to display simulation general info.\n\n";            //emfanizontai genikes plirofories sxetika me to prosomiosi
    system("pause");
    system("CLS");
    
    cout<<"\n\nSIMULATION GENERAL INFO:\n\n";
    
    cout<<"Total Days of Simulation: "<<k<<endl;
    cout<<"World Size: "<<N<<"x"<<N<<endl<<endl;
    
    cout<<"Total Weather Hits: "<<weath_attacks<<endl;
    cout<<"Total Weather Kills: "<<weath_kills<<endl<<endl;
    
    cout<<"Total Docks: "<<ports_count<<endl;
    cout<<"Total Dock Heal Out: "<<dock_heal_out<<endl;
    cout<<"Total Dock Heals: "<<dock_heals<<endl;
    cout<<"Total Dock Attacks: "<<dock_attacks<<endl;
    cout<<"Total Dock Kills: "<<dock_kills<<endl<<endl;
    
    cout<<"Total Alive Ships: "<<ship::shipcount-ship::dead_ships<<"/"<<ship::shipcount<<" ("<<ship::add_ships<<" added, "<<ship::rem_ships<<" removed)"<<endl;
    cout<<"Alive Pirate Ships: "<<pirate::p_shipcount - pirate::dead_ships<<"/"<<pirate::p_shipcount<<endl;
    cout<<"Alive Pirate Healer Ships: "<<prt_r::shipcount - prt_r::dead_ships<<"/"<<prt_r::shipcount<<endl;
    cout<<"Alive Mercantile Ships: "<<mercantile::shipcount - mercantile::dead_ships<<"/"<<mercantile::shipcount<<endl;
    cout<<"Alive Repairing Ships: "<<repairing::shipcount - repairing::dead_ships<<"/"<<repairing::shipcount<<endl;
    cout<<"Alive Exploring Ships: "<<exploring::e_shipcount - exploring::dead_ships<<"/"<<exploring::e_shipcount<<endl;
    cout<<"Alive Exploring Supplier Ships: "<<exp_s::shipcount - exp_s::dead_ships<<"/"<<exp_s::shipcount<<endl;
    if((ship_vec.size()>0) && (!endGame)){
        cout<<"\nShip Winner: "<<top_ship<<endl;
        cout<<"Ship Winner Gold: "<<top_gold<<endl;
    }
    cout<<"\nTotal Gold In: "<<ship::total_gold_in_<<"\nTotal Gold Out: "<<ship::total_gold_out_<<endl;
    cout<<"Total Damage In: "<<ship::total_dmg_in_<<"\nTotal Heal In: "<<ship::total_heal_in_<<endl;
    cout<<"Total Blocks Moved: "<<ship::total_blocks_moved_<<endl;
    cout<<"Total Pirate Damage Out: "<<pirate::total_dmg_out_<<"\nTotal Pirate Attacks: "<<pirate::total_attacks_<<endl;
    cout<<"Total Pirate Kills: "<<pirate::total_kills_<<endl;
    cout<<"Total Pirate Healer Heal Out: "<<prt_r::total_heal_out_<<"\nTotal Pirate Healer Heals: "<<prt_r::total_heals_<<endl;
    cout<<"Total Mercantile Dock Trades: "<<mercantile::total_dock_trades_<<endl;
    cout<<"Total Repairing Heal Out: "<<repairing::total_heal_out_<<"\nTotal Repairing Heals: "<<repairing::total_heals_<<endl;
    cout<<"Total Exploring Evades: "<<exploring::total_evades_<<endl;
    cout<<"Total Exploring Supplier Supplies: "<<exp_s::total_sups_<<endl<<endl;
    
    cout<<"Final World Image:\n\n";                                             //emfanizetai i teliki eikona tou xarti
          
    SetConsoleTextAttribute(hConsole, 0 + 0*16);
         cout<<"_______________________________________________\n";
         for(i=0;i<N;i++){
             for(j=0;j<N;j++){
                if(mapp[i][j]->getPort() == true){
                    SetConsoleTextAttribute(hConsole, 15 + 3*16);   // 3 = gkrimple            
                    cout<<" ";
                    SetConsoleTextAttribute(hConsole, 0 + 3*16);   // 1 = mple
                    cout<<"D";
                    SetConsoleTextAttribute(hConsole, 7 + 3*16);
                    if(j==N-1){    
                        cout<<" ";
                    }
                    else{
                        cout<<" |";
                    }
                    SetConsoleTextAttribute(hConsole, 15 + 0*16);   // 0 = mavro, 15 = aspro
                }
                else if(mapp[i][j]->getShip() != 0){
                    if(dynamic_cast<prt_r *>(mapp[i][j]->getShip())!=0){
                        SetConsoleTextAttribute(hConsole, 15 + 3*16);   // 3 = gkrimple            
                        cout<<" ";
                        SetConsoleTextAttribute(hConsole, 14 + 3*16);   // 1 = mple
                        cout<<"h";
                        SetConsoleTextAttribute(hConsole, 7 + 3*16);
                        if(j==N-1){    
                            cout<<" ";
                        }
                        else{
                            cout<<" |";
                        }
                        SetConsoleTextAttribute(hConsole, 15 + 0*16);
                    }
                    else if(dynamic_cast<pirate *>(mapp[i][j]->getShip())!=0){
                        SetConsoleTextAttribute(hConsole, 15 + 3*16);   // 3 = gkrimple            
                        cout<<" ";
                        SetConsoleTextAttribute(hConsole, 12 + 3*16);   // 1 = mple
                        cout<<"p";
                        SetConsoleTextAttribute(hConsole, 7 + 3*16);
                        if(j==N-1){    
                            cout<<" ";
                        }
                        else{
                            cout<<" |";
                         }
                         SetConsoleTextAttribute(hConsole, 15 + 0*16);
                    }
                    else if(dynamic_cast<mercantile *>(mapp[i][j]->getShip())!=0){
                        SetConsoleTextAttribute(hConsole, 15 + 3*16);   // 3 = gkrimple            
                        cout<<" ";
                        SetConsoleTextAttribute(hConsole, 10 + 3*16);   // 1 = mple
                        cout<<"m";
                        SetConsoleTextAttribute(hConsole, 7 + 3*16);
                        if(j==N-1){    
                            cout<<" ";
                        }
                        else{
                            cout<<" |";
                        }
                        SetConsoleTextAttribute(hConsole, 15 + 0*16);
                    }
                    else if(dynamic_cast<repairing *>(mapp[i][j]->getShip())!=0){
                        SetConsoleTextAttribute(hConsole, 15 + 3*16);   // 3 = gkrimple            
                        cout<<" ";
                        SetConsoleTextAttribute(hConsole, 13 + 3*16);   // 1 = mple
                        cout<<"r";
                        SetConsoleTextAttribute(hConsole, 7 + 3*16);
                        if(j==N-1){    
                            cout<<" ";
                        }
                        else{
                            cout<<" |";
                        }
                        SetConsoleTextAttribute(hConsole, 15 + 0*16);
                    }
                    else if(dynamic_cast<exp_s *>(mapp[i][j]->getShip())!=0){
                        SetConsoleTextAttribute(hConsole, 15 + 3*16);   // 3 = gkrimple            
                        cout<<" ";
                        SetConsoleTextAttribute(hConsole, 11 + 3*16);   // 1 = mple
                        cout<<"s";
                        SetConsoleTextAttribute(hConsole, 7 + 3*16);
                        if(j==N-1){    
                            cout<<" ";
                        }
                        else{
                            cout<<" |";
                        }
                        SetConsoleTextAttribute(hConsole, 15 + 0*16);
                    }
                    else if(dynamic_cast<exploring *>(mapp[i][j]->getShip())!=0){
                        SetConsoleTextAttribute(hConsole, 15 + 3*16);   // 3 = gkrimple            
                        cout<<" ";
                        SetConsoleTextAttribute(hConsole, 9 + 3*16);   // 1 = mple
                        cout<<"e";
                        SetConsoleTextAttribute(hConsole, 7 + 3*16);
                        if(j==N-1){    
                            cout<<" ";
                        }
                        else{
                            cout<<" |";
                        }
                        SetConsoleTextAttribute(hConsole, 15 + 0*16);
                    }
                     
                }
                else{
                    SetConsoleTextAttribute(hConsole, 7 + 3*16); 
                    if(j==N-1){
                        cout<<"   ";
                    }
                    else{
                        cout<<"   |";
                    }
                    SetConsoleTextAttribute(hConsole, 15 + 0*16);
                }
             }
          
             if(i==3){cout<<"    D = Dock\n";}
             else if(i==4){cout<<"    p = pirate\n";}
             else if(i==5){cout<<"    h = pirate healer\n";}
             else if(i==6){cout<<"    m = mercantile\n";}
             else if(i==7){cout<<"    r = repairing\n";}
             else if(i==8){cout<<"    e = exploring\n";}
             else if(i==9){cout<<"    s = exploring supplier\n";}
             else{cout<<"\n";}
        
             SetConsoleTextAttribute(hConsole, 7 + 3*16);
             cout<<"   |   |   |   |   |   |   |   |   |   |   |   \n";
        
             if(i!=N-1){
                 cout<<"---+---+---+---+---+---+---+---+---+---+---+---\n";
             }
             SetConsoleTextAttribute(hConsole, 15 + 0*16);
    }
    cout<<endl; 
    cout<<"Press any key to display alive ships joining simulation...\n\n";                  //emfanizontai listes me ta en_zoi ploia
    system("pause");                                                                        //ta katestramena ploia 
                                                                                            //kai ta ploia pou afairethikan apo to xristi
    
    system("CLS");
    cout<<"\n.:: ALIVE SHIPS ::.\n\n";
    if(ship_vec.size()<1){cout<<"No alive ships joining simulation.\n";}
    for(i=0;i<ship_vec.size();i++){
        ship_vec[i]->printInfo();
    }
    cout<<"\nPress any key to display destroyed ships...\n";
    cout<<endl;
    system("pause");
    system("cls");
    cout<<".:: DESTROYED SHIPS ::.\n\n";
    if(dead_ship_vec.size()<1){cout<<"No destroyed ships.\n";}
    for(i=0;i<dead_ship_vec.size();i++){
        dead_ship_vec[i]->printInfo();
    }
    cout<<"\nPress any key to display removed ships...\n";
    cout<<endl;
    system("pause");
    system("cls");
    cout<<".:: REMOVED SHIPS ::.\n\n";
    if(rem_ships.size()<1){cout<<"No removed ships.\n\n";}
    for(i=0;i<rem_ships.size();i++){
        rem_ships[i]->printInfo();
    }
    cout<<endl<<"Press any key to exit programm...\n\n";
    system("pause");
    return 0;                                                        //telos programmatos 
}

int SearchShip(ship *shp, vector<ship *> *vec){                       // voithitiki synartisi anazitisis ploion
    
    int i;
    string str1, str2;

    for(i=0;i<(*vec).size();i++){
        str1=(*vec)[i]->getName();
        str2=shp->getName();
        if(str1.compare(str2) == 0){
            return i;
        }
    }
    return (-1);
}
            

int RemoveDeadShips(chart ***mapp, vector<ship *> *vec, vector<ship *> *dvec){       //synartisi afairesis vythismenon ploion apo to xarti
     
     int i,j,gold,pos=-1;
     ship *shp;
     
     for(i=0;i<N;i++){
         for(j=0;j<N;j++){
             if((!mapp[i][j]->getPort()) && (mapp[i][j]->getShip()!=0)){
                 shp = mapp[i][j]->getShip();                        
                 if(shp->getDead()){
                     ship::dead_ships++;
                     gold=shp->getCurtreas();
                     shp->setCurtreas(0);
                     mapp[i][j]->setTreasure(mapp[i][j]->getTreasure()+gold);
                     pos = SearchShip(shp,vec);
                     if(pos!= -1){
                         (*vec).erase((*vec).begin()+pos);
                     }
                     else{
                          cout<<"NOT FOUND IN VECTOR!\n";
                     }
                     (*dvec).push_back(shp);
                     mapp[i][j]->setShip(NULL);
                 }
             }
         }
     }
     return pos;
     
}            

bool PortOperate(chart ***mapp, vector<string> *info_msgs){                   //synartisi leitourgias ton limanion
     
     int i,j, m,n,prev_health;
     pirate *prt;
     ship *shp;
     bool death_flag=false;
     
     for(i=0;i<N;i++){
         for(j=0;j<N;j++){
             
             if(mapp[i][j]->getPort()){
                 for(m=i-1;m<=i+1;m++){
                     if((m>-1) && (m<N)){
                         for(n=j-1;n<=j+1;n++){
                             if((n>-1) && (n<N)){
                                 
                                 shp = mapp[m][n]->getShip();
                                 if(shp!=NULL){
                                     
                                     prt = dynamic_cast<pirate *>(shp);
                                     if( prt==NULL ){
                                         if(shp->getCurhp() < shp->getMaxhp()){
                                               
                                             (*info_msgs).push_back("Ship "+shp->getName()+" was healed by a near port!\n");
                                              
                                              prev_health=shp->getCurhp();
                                             shp->setCurhp(shp->getCurhp()+PORT_HEAL);
                                             
                                             if(shp->getCurhp() > shp->getMaxhp()){
                                                 shp->setCurhp(shp->getMaxhp());
                                             }
                                             dock_heal_out+=(shp->getCurhp() - prev_health);
                                             dock_heals++;   
                                         }
                                         
                                     }
                                     else if(prt!=NULL){
                                          shp->setCurhp(shp->getCurhp() -PORT_DAMAGE);
                                          dock_attacks++;
                                          (*info_msgs).push_back("Ship "+shp->getName()+" was attacked by a near port!\n");
                                          if(shp->getCurhp()<=0){
                                              death_flag=true;
                                              shp->setDead(true);
                                              dock_kills++;
                                              (*info_msgs).push_back("Ship "+shp->getName()+" was destroyed by a near port attack!\n");
                                          }
                                     }
                                     
                                 }
                                 
                             }
                         }
                     }
                 }
             }
             
         }
     }
     return death_flag;
}

void WeatherChange(chart ***mapp){                                        //synartisi allagis kairikon synthikon toy xarti
     
     int i,j;
     
     for(i=0;i<N;i++){
         for(j=0;j<N;j++){
             if(!mapp[i][j]->getPort()){
                 mapp[i][j]->setWeather( mapp[i][j]->getWeather() +(rand()%3 -1) );
                 if(mapp[i][j]->getWeather() >10){
                     mapp[i][j]->setWeather(10);
                 }
                 else if(mapp[i][j]->getWeather() <1){
                      mapp[i][j]->setWeather(1);
                 }
             }
         }
     }
}

bool WeathTreasCheck(chart ***mapp, vector<string> *info_msgs){        //synartisi elegxou gia zimia apo kairikes synthikes kai perissylogi thysavron
     
     int i,j, weath, treas;
     ship * shp;
     bool death_flag=false;
     stringstream ss;
     
     for(i=0;i<N;i++){
         for(j=0;j<N;j++){
             if( (!mapp[i][j]->getPort()) && (mapp[i][j]->getShip()!=NULL) ){
                 weath=mapp[i][j]->getWeather();
                 treas=mapp[i][j]->getTreasure();
                 shp=mapp[i][j]->getShip();
                 if(weath>5){
                     shp->setCurhp(shp->getCurhp() -((weath-5)*WEATHER_BASE_DMG));
                     ss.clear();
                     ss.str("");
                     ss << ( (weath-5) *WEATHER_BASE_DMG);
                     weath_attacks++;
                     (*info_msgs).push_back("Ship "+shp->getName()+" got "+ss.str()+" damage by bad weather!\n");
                 }
                 if(shp->getCurhp() <= 0){
                     death_flag=true;
                     shp->setDead(true);
                     weath_kills++;
                     (*info_msgs).push_back("Ship "+shp->getName()+" was destroyed by bad weather!\n");
                 }
                 if((!shp->getDead()) && (treas>0)){
                     shp->setCurtreas(shp->getCurtreas() + treas);
                     mapp[i][j]->setTreasure(0);
                     ss.clear();
                     ss.str("");
                     ss << treas;
                     (*info_msgs).push_back("Ship "+shp->getName()+" collected "+ss.str()+" gold!\n");                   
                 }
             }
         }
         
     }
     
     return death_flag;
     
}

void WorldInit(chart ***mapp){                                           //synartisi arxikopoihshs tou xarti
     
     int i,j, flagi=-3, flagj=-3;
     int test;
     
     srand(time(0));
     for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            
            test=rand()%10+1;
            
            if(test==1 || test==3 || test==5 || test==7){

                mapp[i][j]=new chart();                                 //ta limania topothetountai me elaxisti apostasi metaksu 
                if((i-flagi)>=3){                                       //tous 2 blocks pros oles tis kateuthinseis
                    mapp[i][j]->setPort(true);
                    flagi=i;
                    flagj=j;
                    ports_count++;
                }
                else if((j-flagj)>=3){
                    mapp[i][j]->setPort(true);
                    flagi=i;
                    flagj=j;
                    ports_count++;
                }
                else{
                     
                     mapp[i][j]->setWeather(rand()%10+1);
                }
                
            }
            else if(test==6 || test==8 || test==9 || test==10){
                mapp[i][j]=new chart();
                
                mapp[i][j]->setTreasure((rand()%10)*10 +(rand()%10));

                mapp[i][j]->setWeather(rand()%10+1);
                //treas_count++;
                
            }
            else{
                mapp[i][j]=new chart();
                mapp[i][j]->setWeather(rand()%10+1);
                
            }
            
        }
    }
     
}

void printMapp(chart ***mapp){                                             //synartisi ektyposis tou xarti
     
     int i,j;
     
    SetConsoleTextAttribute(hConsole, 0 + 0*16);
    cout<<"_______________________________________________\n";
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            if(mapp[i][j]->getPort() == true){
                SetConsoleTextAttribute(hConsole, 15 + 3*16);   // 3 = gkrimple            
                cout<<" ";
                SetConsoleTextAttribute(hConsole, 0 + 3*16);   // 1 = mple
                cout<<"D";
                SetConsoleTextAttribute(hConsole, 7 + 3*16);
                if(j==N-1){    
                    cout<<" ";
                }
                else{
                    cout<<" |";
                }
                SetConsoleTextAttribute(hConsole, 15 + 0*16);   // 0 = mavro, 15 = aspro
            }
            else if(mapp[i][j]->getShip() != 0){
                 if(dynamic_cast<prt_r *>(mapp[i][j]->getShip())!=0){
                     SetConsoleTextAttribute(hConsole, 15 + 3*16);   // 3 = gkrimple            
                     cout<<" ";
                     SetConsoleTextAttribute(hConsole, 14 + 3*16);   // 1 = mple
                     cout<<"h";
                     SetConsoleTextAttribute(hConsole, 7 + 3*16);
                     if(j==N-1){    
                         cout<<" ";
                     }
                     else{
                         cout<<" |";
                     }
                     SetConsoleTextAttribute(hConsole, 15 + 0*16);
                 }
                 else if(dynamic_cast<pirate *>(mapp[i][j]->getShip())!=0){
                     SetConsoleTextAttribute(hConsole, 15 + 3*16);   // 3 = gkrimple            
                     cout<<" ";
                     SetConsoleTextAttribute(hConsole, 12 + 3*16);   // 1 = mple
                     cout<<"p";
                     SetConsoleTextAttribute(hConsole, 7 + 3*16);
                     if(j==N-1){    
                         cout<<" ";
                     }
                     else{
                         cout<<" |";
                     }
                     SetConsoleTextAttribute(hConsole, 15 + 0*16);
                 }
                 else if(dynamic_cast<mercantile *>(mapp[i][j]->getShip())!=0){
                     SetConsoleTextAttribute(hConsole, 15 + 3*16);   // 3 = gkrimple            
                     cout<<" ";
                     SetConsoleTextAttribute(hConsole, 10 + 3*16);   // 1 = mple
                     cout<<"m";
                     SetConsoleTextAttribute(hConsole, 7 + 3*16);
                     if(j==N-1){    
                         cout<<" ";
                     }
                     else{
                         cout<<" |";
                     }
                     SetConsoleTextAttribute(hConsole, 15 + 0*16);
                 }
                 else if(dynamic_cast<repairing *>(mapp[i][j]->getShip())!=0){
                     SetConsoleTextAttribute(hConsole, 15 + 3*16);   // 3 = gkrimple            
                     cout<<" ";
                     SetConsoleTextAttribute(hConsole, 13 + 3*16);   // 1 = mple
                     cout<<"r";
                     SetConsoleTextAttribute(hConsole, 7 + 3*16);
                     if(j==N-1){    
                         cout<<" ";
                     }
                     else{
                         cout<<" |";
                     }
                     SetConsoleTextAttribute(hConsole, 15 + 0*16);
                 }
                 else if(dynamic_cast<exp_s *>(mapp[i][j]->getShip())!=0){
                      SetConsoleTextAttribute(hConsole, 15 + 3*16);   // 3 = gkrimple            
                     cout<<" ";
                     SetConsoleTextAttribute(hConsole, 11 + 3*16);   // 1 = mple
                     cout<<"s";
                     SetConsoleTextAttribute(hConsole, 7 + 3*16);
                     if(j==N-1){    
                         cout<<" ";
                     }
                     else{
                         cout<<" |";
                     }
                     SetConsoleTextAttribute(hConsole, 15 + 0*16);
                 }
                 else if(dynamic_cast<exploring *>(mapp[i][j]->getShip())!=0){
                     SetConsoleTextAttribute(hConsole, 15 + 3*16);   // 3 = gkrimple            
                     cout<<" ";
                     SetConsoleTextAttribute(hConsole, 9 + 3*16);   // 1 = mple
                     cout<<"e";
                     SetConsoleTextAttribute(hConsole, 7 + 3*16);
                     if(j==N-1){    
                         cout<<" ";
                     }
                     else{
                         cout<<" |";
                     }
                     SetConsoleTextAttribute(hConsole, 15 + 0*16);
                 }
                     
             }
            else{
                SetConsoleTextAttribute(hConsole, 7 + 3*16); 
                if(j==N-1){
                    cout<<"   ";
                }
                else{
                    cout<<"   |";
                }
                SetConsoleTextAttribute(hConsole, 15 + 0*16);
            }
        }
          
        if(i==1){cout<<"    D = Dock\n";}
        else if(i==2){cout<<"    p = pirate\n";}
        else if(i==3){cout<<"    h = pirate healer\n";}
        else if(i==4){cout<<"    m = mercantile\n";}
        else if(i==5){cout<<"    r = repairing\n";}
        else if(i==6){cout<<"    e = exploring\n";}
        else if(i==7){cout<<"    s = exploring supplier\n";}
        else if(i==9){cout<<"    Press 'i' for Day info.\n";}
        else if(i==10){cout<<"    Press 'p' for Pause Menu.\n";}
        else{cout<<"\n";}
        
        SetConsoleTextAttribute(hConsole, 7 + 3*16);
        cout<<"   |   |   |   |   |   |   |   |   |   |   |   \n";
        
        if(i!=N-1){
            cout<<"---+---+---+---+---+---+---+---+---+---+---+---\n";
        }
        SetConsoleTextAttribute(hConsole, 15 + 0*16);
    }
     
     
     
        
}
void swap_el(vector<ship *> *ship_vec, int i, int j){                  // voithiki synartisi gia ti synartisi taksinomisis
     
     ship *temp;
     
     temp=(*ship_vec)[i];
     (*ship_vec)[i] = (*ship_vec)[j];
     (*ship_vec)[j] = temp;

}

void vec_sorting(vector<ship *> *ship_vec){                             //synartisi taksinomisis vector kata auksousa seira xrysou
     
    int i, up_s, down_s, max, max_p;
     
    up_s = -1;
    down_s = (*ship_vec).size();
    max = (*ship_vec)[down_s-1]->getCurtreas();
    max_p = down_s-1;
     
    while((down_s-up_s!=2) && (down_s-up_s!=1)){

        for(i=down_s-1;i>up_s+1;i--){

            if((*ship_vec)[i]->getCurtreas()<(*ship_vec)[i-1]->getCurtreas()){
                
                swap_el(ship_vec,i,i-1);    

                if((*ship_vec)[i]->getCurtreas()>max){
                    max=(*ship_vec)[i]->getCurtreas();
                    max_p=i;
                }
                else if((*ship_vec)[i]->getCurtreas()==max){
                     if((*ship_vec)[i]->getCurhp()>(*ship_vec)[max_p]->getCurhp()){
                         max=(*ship_vec)[i]->getCurtreas();
                         max_p=i;
                     }
                }
                
            }
            else if((*ship_vec)[i]->getCurtreas()==(*ship_vec)[i-1]->getCurtreas()){
                 if((*ship_vec)[i]->getCurhp()<(*ship_vec)[i-1]->getCurhp()){
                     
                     swap_el(ship_vec,i,i-1);
                     
                     if((*ship_vec)[i]->getCurtreas()>max){
                         max=(*ship_vec)[i]->getCurtreas();
                         max_p=i;
                     }
                     else if((*ship_vec)[i]->getCurtreas()==max){
                         if((*ship_vec)[i]->getCurhp()>(*ship_vec)[max_p]->getCurhp()){
                             max=(*ship_vec)[i]->getCurtreas();
                             max_p=i;
                         }
                     }
                 }
                 
            }
        }
        up_s++;
        swap_el(ship_vec,max_p,down_s-1);
        down_s--;
        max=(*ship_vec)[down_s-1]->getCurtreas();
        max_p=down_s-1;

     }
     
}

bool pirate::Operate(chart ***mapp, vector<string> *info_msgs){        // eksoterikos orismos methodou leitourgias tis pirate
                  
  int i,j, x_atk=-1, y_atk=-1, hp_atk=PIRATE_HP+1, gold, steal;
  ship *shp_atk;
  bool death_flag=false;
  stringstream ss;                 
  
  for(i=x_pos-1;i<=x_pos+1;i++){
    if((i>-1) && (i<N)){
        for(j=y_pos-1;j<=y_pos+1;j++){
            if((j>-1) && (j<N)){
                                     
                if((i!=x_pos) || (j!=y_pos)){
                                       
                    if((!mapp[i][j]->getPort()) && (mapp[i][j]->getShip()!=NULL)){
                                         
                        if(dynamic_cast<prt_r *>(mapp[i][j]->getShip()) == 0) {

                            if(mapp[i][j]->getShip()->getCurhp()<hp_atk){
                                x_atk=i;
                                y_atk=j;
                                hp_atk=mapp[i][j]->getShip()->getCurhp();
                            }
                        }
                                           
                    }
                }
                                     
            }
        }
    }
  }
                       
  if((x_atk!=-1) && (y_atk!=-1) && (hp_atk<PIRATE_HP+1)){
                           
    shp_atk=mapp[x_atk][y_atk]->getShip();
    if(dynamic_cast<pirate *>(shp_atk)!=0){           
        shp_atk->setCurhp(shp_atk->getCurhp() - (damage-defence));
        total_dmg_out+=(damage-defence);
        total_dmg_out_+=(damage-defence);
    }
    else{
         shp_atk->setCurhp(shp_atk->getCurhp() - damage);
         total_dmg_out+=damage;
         total_dmg_out_+=damage;
    }
    total_attacks++;
    total_attacks_++;
    gold=shp_atk->getCurtreas();
    if(gold<=200){
        steal=(int)(gold*0.42);
        gold-=steal;
    }
    else if(gold<=500){
        steal=(int)(gold*0.32);
        gold-=steal;
    }
    else if(gold<=1000){
        steal=(int)(gold*0.26);
        gold-=steal;
    }
    else if(gold<=1500){
        steal=(int)(gold*0.21);
        gold-=steal;
    }
    else{
        steal=330;
        gold-=steal;
    }
    shp_atk->setCurtreas(gold);
    this->setCurtreas(this->getCurtreas() +steal);
    ss.clear();
    ss.str("");
    ss << steal;
    if(shp_atk->getCurhp()<=0){
        death_flag=true;
        shp_atk->setDead(true);
        total_kills++;
        total_kills_++;
        (*info_msgs).push_back("Ship "+this->getName()+" attacked ship "+shp_atk->getName()+" stealing "+ss.str()+" gold and destroyed it!\n");
    }
    else{
        (*info_msgs).push_back("Ship "+this->getName()+" attacked ship "+shp_atk->getName()+" stealing "+ss.str()+" gold!\n");
    }
  }
  else{
    
    (*info_msgs).push_back("Ship "+this->getName()+" didn't attack any other ship!\n");
  }
  return death_flag;
                  
}

bool ship::Move(chart ***mapp){                                           //eksoterikos orismos methodou kinisis tis klassis ship
            
            
            int x, y, new_x, new_y, blocked=0;
                        
            for(x=x_pos-1;x<=x_pos+1;x++){
                if((x>-1) && (x<N)){
                         for(y=y_pos-1;y<=y_pos+1;y++){
                             if((y>-1) && (y<N)){
                                       if((!mapp[x][y]->getPort()) && (mapp[x][y]->getShip()==NULL)){
                                                                 blocked++;
                                       }
                             }
                         }
                }
            }
            if(blocked<1){
                return false;
            }
            
            if(x_pos==0){
                if(y_pos==0){
                    
                    do{
                       x=rand()%3 -1;
                       y=rand()%3 -1;
                       while((x==0 && y==0) || (x==-1) || (y==-1)){
                                  x=rand()%3 -1;
                                  y=rand()%3 -1;
                       }
                       
                    }while((mapp[x_pos+x][y_pos+y]->getPort()) || (mapp[x_pos+x][y_pos+y]->getShip()!=NULL));
                }
                else if(y_pos==N-1){
                     
                     do{
                       x=rand()%3 -1;
                       y=rand()%3 -1;
                       while((x==0 && y==0) || (x==-1) || (y==1)){
                                  x=rand()%3 -1;
                                  y=rand()%3 -1;
                       }

                    }while((mapp[x_pos+x][y_pos+y]->getPort()) || (mapp[x_pos+x][y_pos+y]->getShip()!=NULL));
                     
                }
                else{
                     
                     do{
                       x=rand()%3 -1;
                       y=rand()%3 -1;
                       while((x==0 && y==0) || (x==-1)){
                                  x=rand()%3 -1;
                                  y=rand()%3 -1;
                       }
                      
                    }while((mapp[x_pos+x][y_pos+y]->getPort()) || (mapp[x_pos+x][y_pos+y]->getShip()!=NULL));
                }
            }
            else if(x_pos==N-1){
                 if(y_pos==0){
                          
                          do{
                             x=rand()%3 -1;
                             y=rand()%3 -1;
                             while((x==0 && y==0) || (x==1) || (y==-1)){
                                  x=rand()%3 -1;
                                  y=rand()%3 -1;
                             }
                             
                          }while((mapp[x_pos+x][y_pos+y]->getPort()) || (mapp[x_pos+x][y_pos+y]->getShip()!=NULL));
                              
                 }
                 else if(y_pos==N-1){
                      
                      do{
                         x=rand()%3 -1;
                         y=rand()%3 -1;
                         while((x==0 && y==0) || (x==1) || (y==1)){
                                     x=rand()%3 -1;
                                     y=rand()%3 -1;
                         }
                         
                      }while((mapp[x_pos+x][y_pos+y]->getPort()) || (mapp[x_pos+x][y_pos+y]->getShip()!=NULL)); 
                      
                 }
                 else{
                      
                      do{
                         x=rand()%3 -1;
                         y=rand()%3 -1;
                         while((x==0 && y==0) || (x==1)){
                                     x=rand()%3 -1;
                                     y=rand()%3 -1;
                         }
                         
                      }while((mapp[x_pos+x][y_pos+y]->getPort()) || (mapp[x_pos+x][y_pos+y]->getShip()!=NULL));
                 }
                 
            }
            else{
                 if(y_pos==0){
                     
                     do{
                         x=rand()%3 -1;
                         y=rand()%3 -1;
                         while((x==0 && y==0) || (y==-1)){
                                     x=rand()%3 -1;
                                     y=rand()%3 -1;
                         }
                         
                      }while((mapp[x_pos+x][y_pos+y]->getPort()) || (mapp[x_pos+x][y_pos+y]->getShip()!=NULL));
                     
                 }
                 else if(y_pos==N-1){
                      
                      do{
                         x=rand()%3 -1;
                         y=rand()%3 -1;
                         while((x==0 && y==0) || (y==1)){
                                     x=rand()%3 -1;
                                     y=rand()%3 -1;
                         }
                        
                      }while((mapp[x_pos+x][y_pos+y]->getPort()) || (mapp[x_pos+x][y_pos+y]->getShip()!=NULL));
                      
                 }
                 else{
                      
                      do{
                         x=rand()%3 -1;
                         y=rand()%3 -1;
                         while(x==0 && y==0){
                                     x=rand()%3 -1;
                                     y=rand()%3 -1;
                         }
                         
                      }while((mapp[x_pos+x][y_pos+y]->getPort()) || (mapp[x_pos+x][y_pos+y]->getShip()!=NULL));
                 }
                 
            }
            new_x=x_pos+x;
            new_y=y_pos+y;
            
            mapp[new_x][new_y]->setShip(mapp[x_pos][y_pos]->getShip());
            mapp[x_pos][y_pos]->setShip(0);
            setX_pos(new_x);
            setY_pos(new_y);
            
            total_blocks_moved++;
            total_blocks_moved_++;
            if(dynamic_cast<prt_r *>(this)!=0){
                prt_r::total_blocks_moved_++;
            }
            else if(dynamic_cast<pirate *>(this)!=0){
                pirate::total_blocks_moved_++;
            }
            else if(dynamic_cast<exp_s *>(this)!=0){
                exp_s::total_blocks_moved_++;
            }
            else if(dynamic_cast<exploring *>(this)!=0){
                exploring::total_blocks_moved_++;
            }
            else if(dynamic_cast<mercantile *>(this)!=0){
                mercantile::total_blocks_moved_++;
            }
            else if(dynamic_cast<repairing *>(this)!=0){
                repairing::total_blocks_moved_++;
            }
            
            return true;
            
}        


void ship::setCurhp(int hp){                                               //eksoterikos orismos methodou setCurhp tis klassis ship
            if(hp>=curhp){
                total_heal_in+=(hp-curhp);
                total_heal_in_+=(hp-curhp);
                
                if(dynamic_cast<prt_r *>(this)!=0){
                    prt_r::total_heal_in_+=(hp-curhp);
                }
                else if(dynamic_cast<pirate *>(this)!=0){
                    pirate::total_heal_in_+=(hp-curhp);
                }
                else if(dynamic_cast<exp_s *>(this)!=0){
                    exp_s::total_heal_in_+=(hp-curhp);
                }
                else if(dynamic_cast<exploring *>(this)!=0){
                    exploring::total_heal_in_+=(hp-curhp);
                }
                else if(dynamic_cast<mercantile *>(this)!=0){
                    mercantile::total_heal_in_+=(hp-curhp);
                }
                else if(dynamic_cast<repairing *>(this)!=0){
                    repairing::total_heal_in_+=(hp-curhp);
                }
                
            }
            else{
                total_dmg_in+=(curhp-hp);
                total_dmg_in_+=(curhp-hp);
                
                if(dynamic_cast<prt_r *>(this)!=0){
                    prt_r::total_dmg_in_+=(curhp-hp);
                }
                else if(dynamic_cast<pirate *>(this)!=0){
                    pirate::total_dmg_in_+=(curhp-hp);
                }
                else if(dynamic_cast<exp_s *>(this)!=0){
                    exp_s::total_dmg_in_+=(curhp-hp);
                }
                else if(dynamic_cast<exploring *>(this)!=0){
                    exploring::total_dmg_in_+=(curhp-hp);
                }
                else if(dynamic_cast<mercantile *>(this)!=0){
                    mercantile::total_dmg_in_+=(curhp-hp);
                }
                else if(dynamic_cast<repairing *>(this)!=0){
                    repairing::total_dmg_in_+=(curhp-hp);
                }
                
            }
            curhp=hp;
}

void ship::setCurtreas(int treas){                                            //eksoterikos orismos methodou setCurtreas tis klassis ship
            if(treas>=curtreas){
                total_gold_in+=(treas-curtreas);
                total_gold_in_+=(treas-curtreas);
                
                if(dynamic_cast<prt_r *>(this)!=0){
                    prt_r::total_gold_in_+=(treas-curtreas);
                }
                else if(dynamic_cast<pirate *>(this)!=0){
                    pirate::total_gold_in_+=(treas-curtreas);
                }
                else if(dynamic_cast<exp_s *>(this)!=0){
                    exp_s::total_gold_in_+=(treas-curtreas);
                }
                else if(dynamic_cast<exploring *>(this)!=0){
                    exploring::total_gold_in_+=(treas-curtreas);
                }
                else if(dynamic_cast<mercantile *>(this)!=0){
                    mercantile::total_gold_in_+=(treas-curtreas);
                }
                else if(dynamic_cast<repairing *>(this)!=0){
                    repairing::total_gold_in_+=(treas-curtreas);
                }
                
            }
            else{
                total_gold_out+=(curtreas-treas);
                total_gold_out_+=(curtreas-treas);
                
                if(dynamic_cast<prt_r *>(this)!=0){
                    prt_r::total_gold_out_+=(curtreas-treas);
                }
                else if(dynamic_cast<pirate *>(this)!=0){
                    pirate::total_gold_out_+=(curtreas-treas);
                }
                else if(dynamic_cast<exp_s *>(this)!=0){
                    exp_s::total_gold_out_+=(curtreas-treas);
                }
                else if(dynamic_cast<exploring *>(this)!=0){
                    exploring::total_gold_out_+=(curtreas-treas);
                }
                else if(dynamic_cast<mercantile *>(this)!=0){
                    mercantile::total_gold_out_+=(curtreas-treas);
                }
                else if(dynamic_cast<repairing *>(this)!=0){
                    repairing::total_gold_out_+=(curtreas-treas);
                }
                
            }
            curtreas=treas;
}

void ship::setDead(bool dead){                                               //eksoterikos orismos methodou setDead tis klassis ship
    
    isDead=dead;
    if(dynamic_cast<prt_r *>(this)!=0){
        prt_r::dead_ships++;
    }
    else if(dynamic_cast<pirate *>(this)!=0){
        pirate::dead_ships++;
    }
    else if(dynamic_cast<exp_s *>(this)!=0){
        exp_s::dead_ships++;
    }
    else if(dynamic_cast<exploring *>(this)!=0){
        exploring::dead_ships++;
    }
    else if(dynamic_cast<mercantile *>(this)!=0){
        mercantile::dead_ships++;
    }
    else if(dynamic_cast<repairing *>(this)!=0){
        repairing::dead_ships++;
    }
            
            
}

void ship::printInfo(){                                                          //eksoterikos orismos methodou printInfo tis klassis ship
               
                  cout<<"Name: "<<name<<endl<<"HP: "<<curhp<<"/"<<maxhp<<endl<<"Speed: "<<speed<<endl;
                  if((dynamic_cast<pirate *>(this)!=0) && (dynamic_cast<prt_r *>(this)==0)){
                      cout<<"Damage: "<<dynamic_cast<pirate *>(this)->getDamage()<<endl;
                  }
                  cout<<"Gold: "<<curtreas<<endl<<"Position:\nX="<<x_pos<<", Y="<<y_pos<<endl;
                  if(isDead){cout<<"Status: Dead\n";}
                  else{cout<<"Status: Alive\n";}
                  if(isRemoved){cout<<"Removed: YES\n";}
                  else{cout<<"Removed: NO\n";}
                  cout<<"Total Gold In: "<<total_gold_in<<endl<<"Total Gold Out: "<<total_gold_out<<endl;
                  cout<<"Total Damage In: "<<total_dmg_in<<endl<<"Total Heal In: "<<total_heal_in<<endl;
                  cout<<"Total Blocks Moved: "<<total_blocks_moved<<endl;
                  if(dynamic_cast<prt_r *>(this)!=0){
                      cout<<"Total Heal Out: "<<dynamic_cast<prt_r *>(this)->getTotalHealOut()<<endl;
                      cout<<"Total Heals: "<<dynamic_cast<prt_r *>(this)->getTotalHeals()<<endl<<endl;
                  }
                  else if(dynamic_cast<pirate *>(this)!=0){
                      cout<<"Total Damage Out: "<<dynamic_cast<pirate *>(this)->getTotalDmgOut()<<endl;
                      cout<<"Total Attacks: "<<dynamic_cast<pirate *>(this)->getTotalAttacks()<<endl;
                      cout<<"Total Kills: "<<dynamic_cast<pirate *>(this)->getTotalKills()<<endl<<endl;
                  }
                  else if(dynamic_cast<exp_s *>(this)!=0){
                      cout<<"Total Supplies: "<<dynamic_cast<exp_s *>(this)->getTotalSups()<<endl<<endl;
                  }
                  else if(dynamic_cast<exploring *>(this)!=0){
                      cout<<"Total Evades: "<<dynamic_cast<exploring *>(this)->getTotalEvades()<<endl<<endl;
                  }
                  else if(dynamic_cast<mercantile *>(this)!=0){
                      cout<<"Total Dock Trades: "<<dynamic_cast<mercantile *>(this)->getTotalDockTrades()<<endl<<endl;
                  }
                  else if(dynamic_cast<repairing *>(this)!=0){
                      cout<<"Total Heal Out: "<<dynamic_cast<repairing *>(this)->getTotalHealOut()<<endl;
                      cout<<"Total Heals: "<<dynamic_cast<repairing *>(this)->getTotalHeals()<<endl<<endl;
                  }
}


bool PauseMenu(chart ***mapp, vector<ship *> *all_ships, vector<ship *> *ship_vec, vector<ship *> *rem_ships){     //synartisi Pause Menu
     
     
  int choice,i,j,m,ship_num,x,y;
  bool enterEdit, dockBlock;
  char c;
     
  while(true){
     
     do{
        system("cls");
        
        cout<<" .:: PAUSE MENU ::. \n\n";
        cout<<"1. Get specific ship info\n\n";
        cout<<"2. Get specific world location info\n\n";
        cout<<"3. Get specific ship type info\n\n";
        cout<<"4. Get simulation general info\n\n";
        cout<<"5. Edit Menu\n\n";
        cout<<"6. Terminate simulation\n\n";
        cout<<"0. Return to simulation\n\n";
        cout<<"Choose an available option: ";
        cin>>choice;
        if((choice!=1) && (choice!=2) && (choice!=3) && (choice!=4) && (choice!=5) && (choice!=6) && (choice!=0)){
            cout<<"\nInvalid choice!\n\n";
            system("pause");
        }
     }while((choice!=1) && (choice!=2) && (choice!=3) && (choice!=4) && (choice!=5) && (choice!=6) && (choice!=0));
     
     if(choice==1){
                   system("cls");
                   cout<<"\n-> Get specific ship info\n\n";
                   cout<<"SHIPS LIST:\n\n";
                   for(i=0;i<(*all_ships).size();i++){
                       cout<<i<<". "<<(*all_ships)[i]->getName()<<endl;
                   }
                   cout<<"\nChoose a ship to display info: ";
                   cin>>ship_num;
                   cout<<endl;
                   if((ship_num>=0) && (ship_num<(*all_ships).size())){
                       (*all_ships)[ship_num]->printInfo();
                   }
                   else{
                        cout<<"\nInvalid choice!\n\n";
                        
                   }
                   system("pause");
                   
     }
     else if(choice==2){
          system("cls");
          cout<<"\n-> Get specific world location info\n\n";
          cout<<"Enter location coordinates to display info:\n";
          cout<<"x = "; cin>>x;
          cout<<"y = "; cin>>y;
          if((x>=0) && (x<N) && (y>=0) && (y<N)){
              if(mapp[x][y]->getPort()){
                  cout<<"\nLocation ("<<x<<","<<y<<"):\n";
                  cout<<"  Dock = YES\n\n";
              }
              else if(mapp[x][y]->getShip()!=0){
                  cout<<"\nLocation ("<<x<<","<<y<<"):\n";
                  cout<<"  Dock = NO\n";
                  cout<<"  Weather = "<<mapp[x][y]->getWeather()<<endl;
                  cout<<"  Treasure = "<<mapp[x][y]->getTreasure()<<endl; 
                  cout<<"  Ship = YES\n\n";
                  mapp[x][y]->getShip()->printInfo();
                  
              }
              else{
                   cout<<"\nLocation ("<<x<<","<<y<<"):\n";
                   cout<<"  Dock = NO\n";
                   cout<<"  Weather = "<<mapp[x][y]->getWeather()<<endl;
                   cout<<"  Treasure = "<<mapp[x][y]->getTreasure()<<endl; 
                   cout<<"  Ship = NO\n\n";
              }              
          }
          else{
               cout<<"\nInvalid coordinates!\n\n";
               
          }
          system("pause");
          
     }
     else if(choice==3){
          system("cls");
          cout<<"\n-> Get specific ship type info\n\n";
          cout<<"SHIP TYPE LIST:\n\n";
          cout<<"1. Pirate Ships\n\n";
          cout<<"2. Pirate Healer Ships\n\n";
          cout<<"3. Mercantile Ships\n\n";
          cout<<"4. Repairing Ships\n\n";
          cout<<"5. Exploring Ships\n\n";
          cout<<"6. Exploring Supplier Ships\n\n";
          cout<<"Choose a ship type to display info: ";
          cin>>i;
          if(i==1){
              cout<<"\nPIRATE SHIPS:\n\n";
              cout<<"Alive Ships: "<<pirate::p_shipcount - pirate::dead_ships<<"/"<<pirate::p_shipcount<<endl;
              cout<<"Total Gold In: "<<pirate::total_gold_in_<<"\nTotal Gold Out: "<<pirate::total_gold_out_<<endl;
              cout<<"Total Damage In: "<<pirate::total_dmg_in_<<"\nTotal Heal In: "<<pirate::total_heal_in_<<endl;
              cout<<"Total Blocks Moved: "<<pirate::total_blocks_moved_<<endl;
              cout<<"Total Damage Out: "<<pirate::total_dmg_out_<<"\nTotal Attacks: "<<pirate::total_attacks_<<endl;
              cout<<"Total Kills: "<<pirate::total_kills_<<endl<<endl;
          }
          else if(i==2){
               cout<<"\nPIRATE HEALER SHIPS:\n\n";
               cout<<"Alive Ships: "<<prt_r::shipcount - prt_r::dead_ships<<"/"<<prt_r::shipcount<<endl;
               cout<<"Total Gold In: "<<prt_r::total_gold_in_<<"\nTotal Gold Out: "<<prt_r::total_gold_out_<<endl;
               cout<<"Total Damage In: "<<prt_r::total_dmg_in_<<"\nTotal Heal In: "<<prt_r::total_heal_in_<<endl;
               cout<<"Total Blocks Moved: "<<prt_r::total_blocks_moved_<<endl;
               cout<<"Total Heal Out: "<<prt_r::total_heal_out_<<"\nTotal Heals: "<<prt_r::total_heals_<<endl<<endl;
          }
          else if(i==3){
               cout<<"\nMERCANTILE SHIPS:\n\n";
               cout<<"Alive Ships: "<<mercantile::shipcount - mercantile::dead_ships<<"/"<<mercantile::shipcount<<endl;
               cout<<"Total Gold In: "<<mercantile::total_gold_in_<<"\nTotal Gold Out: "<<mercantile::total_gold_out_<<endl;
               cout<<"Total Damage In: "<<mercantile::total_dmg_in_<<"\nTotal Heal In: "<<mercantile::total_heal_in_<<endl;
               cout<<"Total Blocks Moved: "<<mercantile::total_blocks_moved_<<endl;
               cout<<"Total Dock Trades: "<<mercantile::total_dock_trades_<<endl<<endl;
          }
          else if(i==4){
               cout<<"\nREPAIRING SHIPS:\n\n";
               cout<<"Alive Ships: "<<repairing::shipcount - repairing::dead_ships<<"/"<<repairing::shipcount<<endl;
               cout<<"Total Gold In: "<<repairing::total_gold_in_<<"\nTotal Gold Out: "<<repairing::total_gold_out_<<endl;
               cout<<"Total Damage In: "<<repairing::total_dmg_in_<<"\nTotal Heal In: "<<repairing::total_heal_in_<<endl;
               cout<<"Total Blocks Moved: "<<repairing::total_blocks_moved_<<endl;
               cout<<"Total Heal Out: "<<repairing::total_heal_out_<<"\nTotal Heals: "<<repairing::total_heals_<<endl<<endl;
          }
          else if(i==5){
               cout<<"\nEXPLORING SHIPS:\n\n";
               cout<<"Alive Ships: "<<exploring::e_shipcount - exploring::dead_ships<<"/"<<exploring::e_shipcount<<endl;
               cout<<"Total Gold In: "<<exploring::total_gold_in_<<"\nTotal Gold Out: "<<exploring::total_gold_out_<<endl;
               cout<<"Total Damage In: "<<exploring::total_dmg_in_<<"\nTotal Heal In: "<<exploring::total_heal_in_<<endl;
               cout<<"Total Blocks Moved: "<<exploring::total_blocks_moved_<<endl;
               cout<<"Total Evades: "<<exploring::total_evades_<<endl<<endl;
          }
          else if(i==6){
               cout<<"\nEXPLORING SUPPLIER SHIPS:\n\n";
               cout<<"Alive Ships: "<<exp_s::shipcount - exp_s::dead_ships<<"/"<<exp_s::shipcount<<endl;
               cout<<"Total Gold In: "<<exp_s::total_gold_in_<<"\nTotal Gold Out: "<<exp_s::total_gold_out_<<endl;
               cout<<"Total Damage In: "<<exp_s::total_dmg_in_<<"\nTotal Heal In: "<<exp_s::total_heal_in_<<endl;
               cout<<"Total Blocks Moved: "<<exp_s::total_blocks_moved_<<endl;
               cout<<"Total Supplies: "<<exp_s::total_sups_<<endl<<endl;
          }
          else{
               cout<<"Invalid choice!\n";
          }
          system("pause");
     }
     else if(choice==4){
          
          system("cls");
          FreeGoldAvgWeath(mapp);
          cout<<"\n-> Get simulation general info\n";
          cout<<"\nSIMULATION GENERAL INFO\n\n";
          
          cout<<"Days of simulation: "<<k<<endl;
          cout<<"World Size: "<<N<<"x"<<N<<endl<<endl;
          cout<<"Current Average Weather: "<<avg_weath<<endl;
          cout<<"Total Weather Hits: "<<weath_attacks<<endl;
          cout<<"Total Weather Kills: "<<weath_kills<<endl;
          cout<<"Total Free Gold: "<<free_gold<<" at "<<gold_places<<" different locations\n\n";
          cout<<"Total Docks: "<<ports_count<<endl;
          cout<<"Total Dock Heal Out: "<<dock_heal_out<<endl;
          cout<<"Total Dock Heals: "<<dock_heals<<endl;
          cout<<"Total Dock Attacks: "<<dock_attacks<<endl;
          cout<<"Total Dock Kills: "<<dock_kills<<endl<<endl;
          cout<<"Alive Ships: "<<ship::shipcount-ship::dead_ships<<"/"<<ship::shipcount<<" ("<<ship::add_ships<<" added, "<<ship::rem_ships<<" removed)"<<endl;
          cout<<"Ships Joining Simulation: "<<(ship::shipcount-ship::dead_ships-ship::rem_ships)<<"/"<<ship::shipcount-ship::dead_ships<<endl;
          cout<<"Alive Pirate Ships: "<<pirate::p_shipcount - pirate::dead_ships<<"/"<<pirate::p_shipcount<<endl;
          cout<<"Alive Pirate Healer Ships: "<<prt_r::shipcount - prt_r::dead_ships<<"/"<<prt_r::shipcount<<endl;
          cout<<"Alive Mercantile Ships: "<<mercantile::shipcount - mercantile::dead_ships<<"/"<<mercantile::shipcount<<endl;
          cout<<"Alive Repairing Ships: "<<repairing::shipcount - repairing::dead_ships<<"/"<<repairing::shipcount<<endl;
          cout<<"Alive Exploring Ships: "<<exploring::e_shipcount - exploring::dead_ships<<"/"<<exploring::e_shipcount<<endl;
          cout<<"Alive Exploring Supplier Ships: "<<exp_s::shipcount - exp_s::dead_ships<<"/"<<exp_s::shipcount<<endl;
          
          cout<<"\nCurrently winning ship: "<<top_ship<<endl;
          if(top_ship.compare("UNKNOWN")!=0){
              cout<<"Currently winning ship gold: "<<top_gold<<endl;
          }
          else{
              cout<<"Currently winning ship gold: -1\n";
          }
          cout<<"\nTotal Gold In: "<<ship::total_gold_in_<<"\nTotal Gold Out: "<<ship::total_gold_out_<<endl;
          cout<<"Total Damage In: "<<ship::total_dmg_in_<<"\nTotal Heal In: "<<ship::total_heal_in_<<endl;
          cout<<"Total Blocks Moved: "<<ship::total_blocks_moved_<<endl;
          cout<<"Total Pirate Damage Out: "<<pirate::total_dmg_out_<<"\nTotal Pirate Attacks: "<<pirate::total_attacks_<<endl;
          cout<<"Total Pirate Kills: "<<pirate::total_kills_<<endl;
          cout<<"Total Pirate Healer Heal Out: "<<prt_r::total_heal_out_<<"\nTotal Pirate Healer Heals: "<<prt_r::total_heals_<<endl;
          cout<<"Total Mercantile Dock Trades: "<<mercantile::total_dock_trades_<<endl;
          cout<<"Total Repairing Heal Out: "<<repairing::total_heal_out_<<"\nTotal Repairing Heals: "<<repairing::total_heals_<<endl;
          cout<<"Total Exploring Evades: "<<exploring::total_evades_<<endl;
          cout<<"Total Exploring Supplier Supplies: "<<exp_s::total_sups_<<endl<<endl;
          cout<<"Current World Image:\n\n";
          
         SetConsoleTextAttribute(hConsole, 0 + 0*16);
         cout<<"_______________________________________________\n";
         for(i=0;i<N;i++){
             for(j=0;j<N;j++){
                if(mapp[i][j]->getPort() == true){
                    SetConsoleTextAttribute(hConsole, 15 + 3*16);   // 3 = gkrimple            
                    cout<<" ";
                    SetConsoleTextAttribute(hConsole, 0 + 3*16);   // 1 = mple
                    cout<<"D";
                    SetConsoleTextAttribute(hConsole, 7 + 3*16);
                    if(j==N-1){    
                        cout<<" ";
                    }
                    else{
                        cout<<" |";
                    }
                    SetConsoleTextAttribute(hConsole, 15 + 0*16);   // 0 = mavro, 15 = aspro
                }
                else if(mapp[i][j]->getShip() != 0){
                    if(dynamic_cast<prt_r *>(mapp[i][j]->getShip())!=0){
                        SetConsoleTextAttribute(hConsole, 15 + 3*16);   // 3 = gkrimple            
                        cout<<" ";
                        SetConsoleTextAttribute(hConsole, 14 + 3*16);   // 1 = mple
                        cout<<"h";
                        SetConsoleTextAttribute(hConsole, 7 + 3*16);
                        if(j==N-1){    
                            cout<<" ";
                        }
                        else{
                            cout<<" |";
                        }
                        SetConsoleTextAttribute(hConsole, 15 + 0*16);
                    }
                    else if(dynamic_cast<pirate *>(mapp[i][j]->getShip())!=0){
                        SetConsoleTextAttribute(hConsole, 15 + 3*16);   // 3 = gkrimple            
                        cout<<" ";
                        SetConsoleTextAttribute(hConsole, 12 + 3*16);   // 1 = mple
                        cout<<"p";
                        SetConsoleTextAttribute(hConsole, 7 + 3*16);
                        if(j==N-1){    
                            cout<<" ";
                        }
                        else{
                            cout<<" |";
                         }
                         SetConsoleTextAttribute(hConsole, 15 + 0*16);
                    }
                    else if(dynamic_cast<mercantile *>(mapp[i][j]->getShip())!=0){
                        SetConsoleTextAttribute(hConsole, 15 + 3*16);   // 3 = gkrimple            
                        cout<<" ";
                        SetConsoleTextAttribute(hConsole, 10 + 3*16);   // 1 = mple
                        cout<<"m";
                        SetConsoleTextAttribute(hConsole, 7 + 3*16);
                        if(j==N-1){    
                            cout<<" ";
                        }
                        else{
                            cout<<" |";
                        }
                        SetConsoleTextAttribute(hConsole, 15 + 0*16);
                    }
                    else if(dynamic_cast<repairing *>(mapp[i][j]->getShip())!=0){
                        SetConsoleTextAttribute(hConsole, 15 + 3*16);   // 3 = gkrimple            
                        cout<<" ";
                        SetConsoleTextAttribute(hConsole, 13 + 3*16);   // 1 = mple
                        cout<<"r";
                        SetConsoleTextAttribute(hConsole, 7 + 3*16);
                        if(j==N-1){    
                            cout<<" ";
                        }
                        else{
                            cout<<" |";
                        }
                        SetConsoleTextAttribute(hConsole, 15 + 0*16);
                    }
                    else if(dynamic_cast<exp_s *>(mapp[i][j]->getShip())!=0){
                        SetConsoleTextAttribute(hConsole, 15 + 3*16);   // 3 = gkrimple            
                        cout<<" ";
                        SetConsoleTextAttribute(hConsole, 11 + 3*16);   // 1 = mple
                        cout<<"s";
                        SetConsoleTextAttribute(hConsole, 7 + 3*16);
                        if(j==N-1){    
                            cout<<" ";
                        }
                        else{
                            cout<<" |";
                        }
                        SetConsoleTextAttribute(hConsole, 15 + 0*16);
                    }
                    else if(dynamic_cast<exploring *>(mapp[i][j]->getShip())!=0){
                        SetConsoleTextAttribute(hConsole, 15 + 3*16);   // 3 = gkrimple            
                        cout<<" ";
                        SetConsoleTextAttribute(hConsole, 9 + 3*16);   // 1 = mple
                        cout<<"e";
                        SetConsoleTextAttribute(hConsole, 7 + 3*16);
                        if(j==N-1){    
                            cout<<" ";
                        }
                        else{
                            cout<<" |";
                        }
                        SetConsoleTextAttribute(hConsole, 15 + 0*16);
                    }
                     
                }
                else{
                    SetConsoleTextAttribute(hConsole, 7 + 3*16); 
                    if(j==N-1){
                        cout<<"   ";
                    }
                    else{
                        cout<<"   |";
                    }
                    SetConsoleTextAttribute(hConsole, 15 + 0*16);
                }
             }
          
             if(i==3){cout<<"    D = Dock\n";}
             else if(i==4){cout<<"    p = pirate\n";}
             else if(i==5){cout<<"    h = pirate healer\n";}
             else if(i==6){cout<<"    m = mercantile\n";}
             else if(i==7){cout<<"    r = repairing\n";}
             else if(i==8){cout<<"    e = exploring\n";}
             else if(i==9){cout<<"    s = exploring supplier\n";}
             else{cout<<"\n";}
        
             SetConsoleTextAttribute(hConsole, 7 + 3*16);
             cout<<"   |   |   |   |   |   |   |   |   |   |   |   \n";
        
             if(i!=N-1){
                 cout<<"---+---+---+---+---+---+---+---+---+---+---+---\n";
             }
             SetConsoleTextAttribute(hConsole, 15 + 0*16);
        }
         
         
        cout<<endl; 
        cout<<"\nEnter (1) to view ships joining simulation sorted by gold.\n\n";
        cout<<"Enter any other key to return to Pause Menu.\n\n";
        cout<<"Enter: ";
        cin>>c;
        if(c=='1'){
            cout<<endl;
            if((*ship_vec).size()>0){
                for(i=(*ship_vec).size()-1;i>=0;i--){
                    cout<<(*ship_vec).size()-i<<". "<<(*ship_vec)[i]->getName()<<" ("<<(*ship_vec)[i]->getCurtreas()<<" gold)\n";
                }
            
            }
            else{
                cout<<"\nThere are no ships joining simulation to display!\n";
            }
            cout<<"\n";
            system("pause");
        }
        
          
     }
     else if(choice==5){
          enterEdit=true;
          while(enterEdit){
              do{
                 system("cls");
                 cout<<".:: Edit Menu ::.\n\n";
                 cout<<"1. Add Ship\n\n";
                 cout<<"2. Remove Ship\n\n";
                 cout<<"3. Replace Ship\n\n";
                 cout<<"4. Add Dock\n\n";
                 cout<<"5. Remove Dock\n\n";
                 cout<<"6. Add Treasure\n\n";
                 cout<<"7. Remove Treasure\n\n";
                 cout<<"0. Back\n\n";
                 cout<<"Choose an available option: ";
                 cin>>i;
                 if((i!=1) && (i!=2) && (i!=3) && (i!=4) && (i!=5) && (i!=6) && (i!=7) && (i!=0)){
                     cout<<"\nInvalid option!\n\n";
                     system("pause");
                 }
              }while((i!=1) && (i!=2) && (i!=3) && (i!=4) && (i!=5) && (i!=6) && (i!=7) && (i!=0));
              
              if(i==1){
                  system("cls");
                  cout<<"\n-> Add Ship\n\n";
                  
                  cout<<"Enter location coordinates to add ship:\n";
                  cout<<"x = "; cin>>x;
                  cout<<"y = "; cin>>y;
                  if((x>=0) && (x<N) && (y>=0) && (y<N)){
                      
                      if((!mapp[x][y]->getPort()) && (mapp[x][y]->getShip()==0)){
                          cout<<"\nShip Types:\n\n";
                          cout<<"1. Pirate\n\n";
                          cout<<"2. Mercantile\n\n";
                          cout<<"3. Repairing\n\n";
                          cout<<"4. Exploring\n\n";
                          cout<<"5. Pirate Healer\n\n";
                          cout<<"6. Exploring Supplier\n\n";
                          cout<<"Choose a type for the ship to add: ";
                          cin>>j;
                          if((j==1) || (j==2) || (j==3) || (j==4) || (j==5) || (j==6)){
                              if(j==1){
                                  mapp[x][y]->setShip(new pirate(x,y));
                              }
                              else if(j==2){
                                  mapp[x][y]->setShip(new mercantile(x,y));
                              }
                              else if(j==3){
                                  mapp[x][y]->setShip(new repairing(x,y));
                              }
                              else if(j==4){
                                  mapp[x][y]->setShip(new exploring(x,y));
                              }
                              else if(j==5){
                                  mapp[x][y]->setShip(new prt_r(x,y));
                              }
                              else if(j==6){
                                  mapp[x][y]->setShip(new exp_s(x,y));
                              }
                              (*ship_vec).push_back(mapp[x][y]->getShip());
                              (*all_ships).push_back(mapp[x][y]->getShip());
                              
                              if((*ship_vec).size()>0){
                                  vec_sorting(ship_vec);
                                  top_gold=(*ship_vec).back()->getCurtreas();
                                  top_ship=(*ship_vec).back()->getName();
                              }
                              else{
                                  top_gold=GOLD_TARGET+1;
                                  top_ship="UNKNOWN";
                                  
                              }
                              cout<<"\nShip "<<mapp[x][y]->getShip()->getName()<<" succesfully addes to location ("<<x<<","<<y<<") !\n\n";
                              ship::add_ships++;
                          }
                          else{
                               cout<<"\nInvalid choice!\n\n";
                               
                               
                          }
                          
                      }
                      else{
                           if(mapp[x][y]->getPort()){
                               cout<<"\nLocation ("<<x<<","<<y<<") is a Dock!\n\n";
                               
                           }
                           else if(mapp[x][y]->getShip()!=0){
                               cout<<"\nLocation ("<<x<<","<<y<<") has already a ship!\n\n";
                               
                           }
                      }
                  }
                  else{
                      cout<<"\nInvalid coordinates!\n\n";
                      
                  }
                  system("pause");
    
              }
              else if(i==2){
                  system("cls");
                  cout<<"\n-> Remove Ship\n\n";
                  
                  cout<<"Currently Alive Available Ships:\n\n";
                  for(j=0;j<(*ship_vec).size();j++){
                      cout<<j<<". "<<(*ship_vec)[j]->getName()<<endl;
                  }
                  if((*ship_vec).size()<1){
                      cout<<"No alive ships available to remove!\n\n";
                  }
                  else{
                    cout<<"\nChoose a ship to remove: ";
                    cin>>j;
                    if((j>=0) && (j<(*ship_vec).size())){
                      mapp[(*ship_vec)[j]->getX_pos()][(*ship_vec)[j]->getY_pos()]->setShip(0);
                      (*rem_ships).push_back((*ship_vec)[j]);
                      (*rem_ships).back()->setRemoved(true);
                      (*ship_vec).erase((*ship_vec).begin()+j);
                      
                      if((*ship_vec).size()>0){
                          vec_sorting(ship_vec);
                          top_gold=(*ship_vec).back()->getCurtreas();
                          top_ship=(*ship_vec).back()->getName();
                      }
                      else{
                          top_gold=GOLD_TARGET+1;
                          top_ship="UNKNOWN";
                                  
                      }
                      cout<<"\nShip "<<(*rem_ships).back()->getName()<<" has been succesfully removed from the world!\n\n";
                      ship::rem_ships++;
                    }
                    else{
                       cout<<"\nInvalid choice!\n\n";
                    }
                  }
                  system("pause");
              }
              else if(i==3){
                  system("cls");
                  cout<<"\n-> Replace Ship\n\n";
                  cout<<"Currently Alive Ships:\n\n";
                  for(j=0;j<(*ship_vec).size();j++){
                      cout<<j<<". "<<(*ship_vec)[j]->getName()<<endl;
                  }
                  if((*ship_vec).size()<1){
                      cout<<"No alive ships available to replace!\n\n";
                  }
                  else{
                    cout<<"\nChoose a ship to replace: ";
                    cin>>j;
                    if((j>=0) && (j<(*ship_vec).size())){
                      
                      cout<<"\nShip Types:\n\n";
                      cout<<"1. Pirate\n\n";
                      cout<<"2. Mercantile\n\n";
                      cout<<"3. Repairing\n\n";
                      cout<<"4. Exploring\n\n";
                      cout<<"5. Pirate Healer\n\n";
                      cout<<"6. Exploring Supplier\n\n";
                      cout<<"Choose a type for the new ship: ";
                      cin>>m;
                      if((m==1) || (m==2) || (m==3) || (m==4) || (m==5) || (m==6)){
                          x=(*ship_vec)[j]->getX_pos();
                          y=(*ship_vec)[j]->getY_pos();
                          (*rem_ships).push_back(mapp[x][y]->getShip());
                          (*rem_ships).back()->setRemoved(true);
                          (*ship_vec).erase((*ship_vec).begin()+j);
                          if(m==1){
                              mapp[x][y]->setShip(new pirate(x,y));
                          }
                          else if(m==2){
                              mapp[x][y]->setShip(new mercantile(x,y));
                          }
                          else if(m==3){
                              mapp[x][y]->setShip(new repairing(x,y));
                          }
                          else if(m==4){
                              mapp[x][y]->setShip(new exploring(x,y));
                          }
                          else if(m==5){
                              mapp[x][y]->setShip(new prt_r(x,y));
                          }
                          else if(m==6){
                              mapp[x][y]->setShip(new exp_s(x,y));
                          }
                          (*ship_vec).push_back(mapp[x][y]->getShip());
                          (*all_ships).push_back(mapp[x][y]->getShip());
                          vec_sorting(ship_vec);
                          if((*ship_vec).size()>0){
                              vec_sorting(ship_vec);
                              top_gold=(*ship_vec).back()->getCurtreas();
                              top_ship=(*ship_vec).back()->getName();
                          }
                          else{
                              top_gold=GOLD_TARGET+1;
                              top_ship="UNKNOWN";
                                  
                          }
                          ship::rem_ships++;
                          ship::add_ships++;
                          cout<<"\nShip "<<(*rem_ships).back()->getName()<<" in location ("<<x<<","<<y<<") has been succesfully replaced by ship "<<mapp[x][y]->getShip()->getName()<<".\n\n";
                          
                      }
                      else{
                           cout<<"\nInvalid choice!\n\n";
                      }
 
                    }
                    else{
                       cout<<"\nInvalid choice!\n\n";
                    }
                  }

                  system("pause");

              }
              else if(i==4){
                  
                  system("cls");
                  dockBlock=false;
                  m=0;
                  cout<<"\n-> Add Dock\n\n";
                  cout<<"DOCKS LIST:\n\n";
                  for(i=0;i<N;i++){
                      for(j=0;j<N;j++){
                          if(mapp[i][j]->getPort()){
                              cout<<m<<". Dock at ("<<i<<","<<j<<")\n";
                              m++;
                          }
                      }
                  }
                  if(m==0){
                      cout<<"\nNo docks in the world!\n\n";
                  }
                  cout<<"\nNote: \nA dock has to be at least 2 blocks (to each direction) away from any other dock!\n\n";
                  cout<<"Enter coordinates to add dock:\n";
                  cout<<"x = "; cin>>x;
                  cout<<"y = "; cin>>y;
                  if((x>=0) && (x<N) && (y>=0) && (y<N)){
                      
                      if((!mapp[x][y]->getPort()) && (mapp[x][y]->getShip()==0)){
                            
                          for(i=x-2;i<=x+2;i++){
                              if((i>=0) && (i<N)){
                                  for(j=y-2;j<=y+2;j++){
                                      if((j>=0) && (j<N)){
                                      
                                          if(mapp[i][j]->getPort()){
                                              dockBlock=true;
                                          }
   
                                      }
                                  }
                              }
                          }
                          if(!dockBlock){
                              mapp[x][y]->setPort(true);
                              mapp[x][y]->setWeather(0);
                              mapp[x][y]->setTreasure(0);
                              cout<<"A dock was succesfuly placed to location ("<<x<<","<<y<<") !\n\n";
                              ports_count++;
                         
                          }
                          else{
                               cout<<"Cannot add dock to location ("<<x<<","<<y<<").\nA dock has to be placed at least 2 blocks (to each direction) away from another dock!\n\n";
                          }
                      }
                      else{
                           if(mapp[x][y]->getPort()){
                               cout<<"\nLocation ("<<x<<","<<y<<") has already a dock!\n\n";
                           }
                           else if(mapp[x][y]->getShip()!=0){
                               cout<<"\nLocation ("<<x<<","<<y<<") has a ship!\n\n";
                           }    
                      }
                      
                  }
                  else{
                       cout<<"\nInvalid coordinates!\n\n";
                  }
                  system("pause");
              }
              else if(i==5){
                  system("cls");
                  cout<<"\n-> Remove Dock\n\n";
                  cout<<"DOCKS LIST:\n\n";
                  m=0;
                  for(i=0;i<N;i++){
                      for(j=0;j<N;j++){
                          if(mapp[i][j]->getPort()){
                              cout<<m<<". Dock at ("<<i<<","<<j<<")\n";
                              m++;
                          }
                      }
                  }
                  if(m==0){
                      cout<<"\nNo docks to remove!\n\n";
                  }
                  else{
                    cout<<"\nEnter coordinates of dock to remove:\n";
                    cout<<"x = "; cin>>x;
                    cout<<"y = "; cin>>y;
                    if((x>=0) && (x<N) && (y>=0) && (y<N)){
                      if(mapp[x][y]->getPort()){
                          mapp[x][y]->setPort(false);
                          mapp[x][y]->setWeather((rand()%10)+1);
                          mapp[x][y]->setTreasure(100);
                          ports_count--;
                          cout<<"\nDock at location ("<<x<<","<<y<<") was succesfully removed!\n\n";
                      }
                      else{
                           cout<<"\nLocation ("<<x<<","<<y<<") is not a dock!\n\n";
                      }
  
                    }
                    else{
                       cout<<"\nInvalid coordinates!\n\n";
                    }
                  }
                  system("pause");
              }
              else if(i==6){
                  system("cls");
                  cout<<"\n-> Add Treasure\n\n";
                  cout<<"Enter coordinates to add treasure: \n";
                  cout<<"x = "; cin>>x;
                  cout<<"y = "; cin>>y;
                  if((x>=0) && (x<N) && (y>=0) && (y<N)){
                      if(!mapp[x][y]->getPort()){
                          cout<<"\nLocation ("<<x<<","<<y<<") contains "<<mapp[x][y]->getTreasure()<<" gold.\n";
                          cout<<"Enter an amount of gold to be added (0 to 99): ";
                          cin>>m;
                          if((m>=0) && (m<100)){
                              mapp[x][y]->setTreasure(mapp[x][y]->getTreasure()+m);
                              cout<<"Trasure of location ("<<x<<","<<y<<") was succesfully increased by "<<m<<" gold! ("<<mapp[x][y]->getTreasure()-m<<" -> "<<mapp[x][y]->getTreasure()<<")\n\n";
                          
                          }
                          else{
                              cout<<"\nInvalid amount of gold!\n\n";
                          }
                      }
                      else{
                           cout<<"\nLocation ("<<x<<","<<y<<") is a dock!\n\n";
                      }
                  }
                  else{
                       cout<<"\nInvalid coordinates!\n\n";
                  }
                  system("pause");
              }
              else if(i==7){
                  system("cls");
                  m=0;
                  cout<<"\n-> Remove Treasure\n\n";
                  cout<<"TREASURE LOCATIONS:\n\n";
                  for(i=0;i<N;i++){
                      for(j=0;j<N;j++){
                          if((!mapp[i][j]->getPort()) && (mapp[i][j]->getTreasure()>0)){
                              cout<<m<<". Treasure Location ("<<i<<","<<j<<") -> "<<mapp[i][j]->getTreasure()<<" gold\n";
                              m++;
                          }
                      }
                  }
                  if(m==0){
                      cout<<"\nNo treasures to remove!\n\n";
                  }
                  else{
                      cout<<"Enter coordinates of location to remove trasure:\n";
                      cout<<"x = "; cin>>x;
                      cout<<"y = "; cin>>y;
                      if((x>=0) && (x<N) && (y>=0) && (y<N)){
                          if(!mapp[x][y]->getPort()){
                              cout<<"\nLocation ("<<x<<","<<y<<") contains "<<mapp[x][y]->getTreasure()<<" gold.\n";
                              cout<<"Enter amount of gold to remove (0 to "<<mapp[x][y]->getTreasure()<<"): ";
                              cin>>m;
                              if((m>=0) && (m<=mapp[x][y]->getTreasure())){
                                  mapp[x][y]->setTreasure(mapp[x][y]->getTreasure()-m);
                                  cout<<"\nTreasure of location ("<<x<<","<<y<<") was succesfully decreased by "<<m<<" gold! ("<<mapp[x][y]->getTreasure()+m<<" -> "<<mapp[x][y]->getTreasure()<<")\n\n";
                              }
                              else{
                                   cout<<"\nInvalid amount of gold!\n\n";
                              }
                          }
                          else{
                              cout<<"\nLocation ("<<x<<","<<y<<") is a dock!\n\n";
                          }
                      
                      }
                      else{
                           cout<<"\nInvalid coordinates!\n\n";
                      }
                  }
                  system("pause");
              }
              else if(i==0){
                  enterEdit=false;
              }
              
          }
          
          
     }
     else if(choice==6){
          
          return true;
     }
     else if(choice==0){
          cout<<"\nContinuing simulation...";
          
          return false;
     }
     
  }
  
}                                                                            // telos synartisis Pause Menu

void FreeGoldAvgWeath(chart ***mapp){                                      // synartisi ypologismou eleutherou xrysou ston xarti
                                                                           //kai MO kairikon sunthikon
     int i,j,total_weath=0, weath_locs=0;
     
     free_gold=0;
     gold_places=0;
     
     for(i=0;i<N;i++){
         for(j=0;j<N;j++){
             if(!mapp[i][j]->getPort()){
                 if(mapp[i][j]->getTreasure()>0){                       
                                        
                     free_gold+=mapp[i][j]->getTreasure();
                     gold_places++;
                 }
                 total_weath+=mapp[i][j]->getWeather();
                 weath_locs++;
             }
         }
     }
     avg_weath = total_weath / weath_locs;
     
}
