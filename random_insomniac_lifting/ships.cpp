#include <iostream>
#include <sstream>
#include <vector>
#include "chart.h"

#define N 12
#define MAX_SUPPLY 25
#define MERC_GOLD_GAIN 55
#define PIRATE_DMG 100
#define PIRATE_DEF 60
#define PIRATE_HP 1200
#define MERC_HP 1000
#define REPAIR_HP 1000
#define EXPLORE_HP 1000
#define PRT_R_HP 900
#define EXP_S_HP 900

using namespace std;

class ship{                                                                     //basiki klassi ship
protected:
          string name;
          int maxhp, curhp, speed, curtreas, x_pos, y_pos;
          bool isDead, isRemoved;
          int total_gold_in, total_gold_out, total_dmg_in, total_heal_in, total_blocks_moved;

public:
       static int shipcount, dead_ships, rem_ships, add_ships, total_gold_in_, total_gold_out_, total_dmg_in_,total_heal_in_,total_blocks_moved_;
    
       ship(){
              shipcount++;
              isDead=false;
              isRemoved=false;
              curtreas=0;
              total_gold_in=0;
              total_gold_out=0;
              total_dmg_in=0;
              total_heal_in=0;
              total_blocks_moved=0;
       }
       
       virtual ~ship(){}
       
       void operator+ (int life){                        //h yperfortosi ton sygkekrimenon teleston exei ginei apla kai mono
            curhp+=life;                                 //epeidi to zitaei i ekfonisi tou project. den ginetai pouthena xrisi 
            if(curhp>maxhp){                             // ton sygkekrimenon yperfortomenon teleston gia aplopoihsh tou programmatos
                curhp=maxhp;                             // mesa ston ypoloipo kodika
            }
       }
       
       void operator- (int life){
            curhp-=life;
            if(curhp<0){
                curhp=0;
            }
       }
       
       void operator++ (int gold){
            curtreas+=gold;
       }
       
       void operator-- (int gold){
            curtreas-=gold;
            if(curtreas<0){
                curtreas=0;
            }
       }
       
       string getName(){return name;}
       int getMaxhp(){return maxhp;}
       int getCurhp(){return curhp;}
       
       void setCurhp(int hp);
       int getSpeed(){return speed;}
       int getCurtreas(){return curtreas;}
       void setCurtreas(int treas);
       int getX_pos(){return x_pos;}
       int getY_pos(){return y_pos;}
       void setX_pos(int x){x_pos=x;}
       void setY_pos(int y){y_pos=y;}
       bool getRemoved(){return isRemoved;}
       void setRemoved(bool rem){isRemoved=rem;}
       bool getDead(){return isDead;}
       void setDead(bool dead);
       int getTotalGoldIn(){return total_gold_in;}
       void printInfo();
       
       virtual bool Operate(chart ***mapp, vector<string> *info_msgs)=0;

       bool Move(chart ***mapp);

};


class pirate: public ship{                                                     //klasi peiratiko ploiou
      
      protected:
             int damage,defence;
             
             int total_dmg_out, total_attacks, total_kills;
      
      public:
             static int shipcount, dead_ships, total_gold_in_, total_gold_out_, total_dmg_in_,total_heal_in_,total_blocks_moved_;
             static int p_shipcount,total_dmg_out_,total_attacks_,total_kills_;
             
             pirate(){
                      shipcount++;
                      stringstream ss;
                      ss << p_shipcount;
                      name="Pirate_"+ss.str();
                      maxhp=PIRATE_HP;
                      curhp=PIRATE_HP;
                      speed=1;
                      curtreas=0;
                      damage=PIRATE_DMG;
                      defence=PIRATE_DEF;
                      isDead=false;
                      isRemoved=false;
                      total_gold_in=0;
                      total_gold_out=0;
                      total_dmg_in=0;
                      total_heal_in=0;
                      total_blocks_moved=0;
                      total_dmg_out=0;
                      total_attacks=0;
                      total_kills=0;
             }
             
             pirate(int x, int y){
                           p_shipcount++;
                           shipcount++;
                           stringstream ss;
                           ss << p_shipcount;
                           name="Pirate_"+ss.str();
                           maxhp=PIRATE_HP;
                           curhp=PIRATE_HP;
                           speed=1;
                           curtreas=0;
                           x_pos=x;
                           y_pos=y;
                           damage=PIRATE_DMG;
                           defence=PIRATE_DEF;
                           isDead=false;
                           isRemoved=false;
                           total_gold_in=0;
                           total_gold_out=0;
                           total_dmg_in=0;
                           total_heal_in=0;
                           total_blocks_moved=0;
                           total_dmg_out=0;
                           total_attacks=0;
                           total_kills=0;
                                                     
             }
             virtual ~pirate(){}
             
             int getDamage(){return damage;}
             int getDefence(){return defence;}
             int getTotalDmgOut(){return total_dmg_out;}
             int getTotalAttacks(){return total_attacks;}
             int getTotalKills(){return total_kills;}
             void printInfo(){
                  cout<<"Name: "<<name<<endl<<"HP: "<<curhp<<"/"<<maxhp<<endl<<"Speed: "<<speed<<endl;
                  cout<<"Damage: "<<damage<<endl;
                  cout<<"Gold: "<<curtreas<<endl<<"Position:\nX="<<x_pos<<", Y="<<y_pos<<endl<<"isDead: "<<isDead<<endl<<endl;
             }
             
             virtual bool Operate(chart ***mapp, vector<string> *info_msgs);
          
};

class prt_r: public pirate{                                                     //klasi peiratikou episkeuastikou ploiou- ypoklasi peiratikou
      protected:
                int total_heal_out, total_heals;
      
      public:
             static int shipcount, dead_ships, total_gold_in_, total_gold_out_, total_dmg_in_, total_heal_in_,total_blocks_moved_;
             static int total_heal_out_,total_heals_;
             
             prt_r(){
                      shipcount++;
                      stringstream ss;
                      ss << shipcount;
                      name="Pirate_R_"+ss.str();
                      maxhp=PRT_R_HP;
                      curhp=PRT_R_HP;
                      speed=1;
                      curtreas=0;
                      isDead=false;
                      isRemoved=false;
                      total_gold_in=0;
                      total_gold_out=0;
                      total_dmg_in=0;
                      total_heal_in=0;
                      total_blocks_moved=0;
                      total_heal_out=0;
                      total_heals=0;
             }
             
             prt_r(int x, int y){
                           shipcount++;
                           stringstream ss;
                           ss << shipcount;
                           name="Pirate_R_"+ss.str();
                           maxhp=PRT_R_HP;
                           curhp=PRT_R_HP;
                           speed=1;
                           curtreas=0;
                           x_pos=x;
                           y_pos=y;
                           isDead=false;
                           isRemoved=false;
                           total_gold_in=0;
                           total_gold_out=0;
                           total_dmg_in=0;
                           total_heal_in=0;
                           total_blocks_moved=0;
                           total_heal_out=0;
                           total_heals=0;
                                                     
             }
             virtual ~prt_r(){}
             int getTotalHealOut(){return total_heal_out;}
             int getTotalHeals(){return total_heals;}
             
             bool Operate(chart ***mapp, vector<string> *info_msgs){
                  
                  int i,j,hp_loss, avail_gold, gold_gain, top_gain_h=-1, top_gain_p=-1;
                  ship *shp, *shp_heal_h, *shp_heal_p;
                  stringstream ss;
                  
                  for(i=x_pos-1;i<=x_pos+1;i++){
                      if((i>-1) && (i<N)){
                          for(j=y_pos-1;j<=y_pos+1;j++){
                              if((j>-1) && (j<N)){
                                
                                if((i!=x_pos) || (j!=y_pos)){    
                                  
                                  if((!mapp[i][j]->getPort()) && (mapp[i][j]->getShip()!=0)){
                                      shp = mapp[i][j]->getShip();
                                      
                                      if(dynamic_cast<prt_r *>(shp)!=0){
                                          avail_gold = shp->getCurtreas();
                                          hp_loss = shp->getMaxhp() - shp->getCurhp();
                                          if((avail_gold>0) && (hp_loss>0)){
                                              
                                              if(hp_loss>=avail_gold){
                                                  gold_gain = avail_gold;
                                              }
                                              else{
                                                   gold_gain = hp_loss; 
                                              }
                                              if(gold_gain > top_gain_h){
                                                  top_gain_h = gold_gain;
                                                  shp_heal_h = shp;
                                              }
                                                             
                                          }
                                      }
                                      else if(dynamic_cast<pirate *>(shp)!=0){
                                          avail_gold = shp->getCurtreas();
                                          hp_loss = shp->getMaxhp() - shp->getCurhp();
                                          if((avail_gold>0) && (hp_loss>0)){
                                              
                                              if(hp_loss>=avail_gold){
                                                  gold_gain = avail_gold;
                                              }
                                              else{
                                                   gold_gain = hp_loss; 
                                              }
                                              if(gold_gain > top_gain_p){
                                                  top_gain_p = gold_gain;
                                                  shp_heal_p = shp;
                                              }
                                                             
                                          }
                                      }                                      
                                      
                                      
                                  }
                                  
                                }
                                  
                              }
                          }
                      }
                  }
                  
                  if(top_gain_p>0){
                                   
                      avail_gold=shp_heal_p->getCurtreas();
                      hp_loss=shp_heal_p->getMaxhp() - shp_heal_p->getCurhp();
                      if(hp_loss>=avail_gold){
                          shp_heal_p->setCurhp(shp_heal_p->getCurhp()+avail_gold);
                          total_heal_out+=avail_gold;
                          total_heals++;
                          total_heal_out_+=avail_gold;
                          total_heals_++;
                          shp_heal_p->setCurtreas(0);
                          this->setCurtreas(this->getCurtreas()+avail_gold);
                          ss.clear();
                          ss.str("");
                          ss << avail_gold;
                          (*info_msgs).push_back("Ship "+this->getName()+" healed ship "+shp_heal_p->getName()+" for "+ss.str()+" hp!\n");
                          return true;
                      }
                      else{
                           shp_heal_p->setCurhp(shp_heal_p->getMaxhp());
                           total_heal_out+=hp_loss;
                           total_heals++;
                           total_heal_out_+=hp_loss;
                           total_heals_++;
                           shp_heal_p->setCurtreas(shp_heal_p->getCurtreas() -hp_loss);
                           this->setCurtreas(this->getCurtreas()+hp_loss);
                           ss.clear();
                           ss.str("");
                           ss << hp_loss;
                           (*info_msgs).push_back("Ship "+this->getName()+" healed ship "+shp_heal_p->getName()+" for "+ss.str()+" hp!\n");
                           return true;
                      }   
                  }
                  else if(top_gain_h>0){
                                        
                       avail_gold=shp_heal_h->getCurtreas();
                       hp_loss=shp_heal_h->getMaxhp() - shp_heal_h->getCurhp();
                       
                       if(hp_loss>=avail_gold){
                          shp_heal_h->setCurhp(shp_heal_h->getCurhp()+avail_gold);
                          total_heal_out+=avail_gold;
                          total_heals++;
                          total_heal_out_+=avail_gold;
                          total_heals_++;
                          shp_heal_h->setCurtreas(0);
                          this->setCurtreas(this->getCurtreas()+avail_gold);
                          ss.clear();
                          ss.str("");
                          ss << avail_gold;
                          (*info_msgs).push_back("Ship "+this->getName()+" healed ship "+shp_heal_h->getName()+" for "+ss.str()+" hp!\n");
                          return true;
                       }
                       else{
                           shp_heal_h->setCurhp(shp_heal_h->getMaxhp());
                           total_heal_out+=hp_loss;
                           total_heals++;
                           total_heal_out_+=hp_loss;
                           total_heals_++;
                           shp_heal_h->setCurtreas(shp_heal_h->getCurtreas() -hp_loss);
                           this->setCurtreas(this->getCurtreas()+hp_loss);
                           ss.clear();
                           ss.str("");
                           ss << hp_loss;
                           (*info_msgs).push_back("Ship "+this->getName()+" healed ship "+shp_heal_h->getName()+" for "+ss.str()+" hp!\n");
                           return true;
                       }   
                       
                  }
                  else{
                       avail_gold=this->getCurtreas();
                       hp_loss=this->getMaxhp() - this->getCurhp();
                       if((hp_loss>0) && (avail_gold>0)){
                                      
                           if(hp_loss>=avail_gold){
                               this->setCurhp(this->getCurhp()+avail_gold);
                               total_heal_out+=avail_gold;
                               total_heals++;
                               total_heal_out_+=avail_gold;
                               total_heals_++;
                               this->setCurtreas(0);
                               ss.clear();
                               ss.str("");
                               ss << avail_gold;
                               (*info_msgs).push_back("Ship "+this->getName()+" healed itself for "+ss.str()+" hp!\n");
                               return true;
                           }
                           else{
                                this->setCurhp(this->getMaxhp());
                                total_heal_out+=hp_loss;
                                total_heals++;
                                total_heal_out_+=hp_loss;
                                total_heals_++;
                                this->setCurtreas(this->getCurtreas()-hp_loss);
                                ss.clear();
                                ss.str("");
                                ss << hp_loss;
                                (*info_msgs).push_back("Ship "+this->getName()+" healed itself for "+ss.str()+" hp!\n");
                                return true;
                           }
                       }
                       else{
                            
                            (*info_msgs).push_back("Ship "+this->getName()+" didn't heal any ship!\n");
                            return false;
                       }
                  }
                  
             }
 
};



class mercantile: public ship{                                                  //klassi emporikou ploiou
      protected:
                int total_dock_trades;
      
      public:
             static int shipcount, dead_ships, total_gold_in_, total_gold_out_, total_dmg_in_, total_heal_in_, total_blocks_moved_;
             static int total_dock_trades_;
             
             mercantile(){
                          shipcount++;
                          stringstream ss;
                          ss << shipcount;
                          name="Mercantile_"+ss.str();
                          maxhp=MERC_HP;
                          curhp=MERC_HP;
                          speed=2;
                          curtreas=0;
                          isDead=false;
                          isRemoved=false;
                          total_gold_in=0;
                          total_gold_out=0;
                          total_dmg_in=0;
                          total_heal_in=0;
                          total_blocks_moved=0;
                          total_dock_trades=0;
                          
             }
             
             mercantile(int x, int y){
                           shipcount++;
                           stringstream ss;
                           ss << shipcount;
                           name="Mercantile_"+ss.str();
                           maxhp=MERC_HP;
                           curhp=MERC_HP;
                           speed=2;
                           curtreas=0;
                           x_pos=x;
                           y_pos=y;
                           isDead=false;
                           isRemoved=false;
                           total_gold_in=0;
                           total_gold_out=0;
                           total_dmg_in=0;
                           total_heal_in=0;
                           total_blocks_moved=0;
                           total_dock_trades=0;
                           
             }
             virtual ~mercantile(){}
             int getTotalDockTrades(){return total_dock_trades;}
             
             bool Operate(chart ***mapp, vector<string> *info_msgs){
                  
                  bool getGold=false;
                  int i,j;
                  stringstream ss;
                  
                  for(i=x_pos-1;i<=x_pos+1;i++){
                      if((i>-1) && (i<N)){
                          for(j=y_pos-1;j<=y_pos+1;j++){
                              if((j>-1) && (j<N)){
                                
                                if(!getGold){
                                              
                                  if(mapp[i][j]->getPort() && (mapp[i][j]->getShip()==0)){
                                      
                                      getGold=true;
                                      total_dock_trades++;
                                      total_dock_trades_++;
                                      this->setCurtreas(this->getCurtreas() +MERC_GOLD_GAIN);
                                      ss.clear();
                                      ss.str("");
                                      ss << MERC_GOLD_GAIN;
                                      (*info_msgs).push_back("Ship "+this->getName()+" gained "+ss.str()+" gold from a near port!\n");
                                  }
                                } 
                                    
                              }
                          }
                      }
                  }
                  if(!getGold){
                      (*info_msgs).push_back("Ship "+this->getName()+" didn't gained gold from any port!\n");
                  }
                  return getGold;
                          
                  
             }
         
};

class repairing: public ship{                                                   //klassi episkeuastikou ploiou
      protected:
                int total_heal_out, total_heals;
      
      public:
             static int shipcount,dead_ships,total_gold_in_, total_gold_out_, total_dmg_in_, total_heal_in_, total_blocks_moved_;
             static int total_heal_out_, total_heals_;
             
             repairing(){
                         shipcount++;
                         stringstream ss;
                         ss << shipcount;
                         name="Repairing_"+ss.str();
                         maxhp=REPAIR_HP;
                         curhp=REPAIR_HP;
                         speed=2;
                         curtreas=0;
                         isDead=false;
                         isRemoved=false;
                         total_gold_in=0;
                         total_gold_out=0;
                         total_dmg_in=0;
                         total_heal_in=0;
                         total_blocks_moved=0;
                         total_heal_out=0;
                         total_heals=0;
                         
             }
             repairing(int x, int y){
                           shipcount++;
                           stringstream ss;
                           ss << shipcount;
                           name="Repairing_"+ss.str();
                           maxhp=REPAIR_HP;
                           curhp=REPAIR_HP;
                           speed=2;
                           curtreas=0;
                           x_pos=x;
                           y_pos=y;
                           isDead=false;
                           isRemoved=false;
                           total_gold_in=0;
                           total_gold_out=0;
                           total_dmg_in=0;
                           total_heal_in=0;
                           total_blocks_moved=0;
                           total_heal_out=0;
                           total_heals=0;
                           
             }
             virtual ~repairing(){}
             int getTotalHealOut(){return total_heal_out;}
             int getTotalHeals(){return total_heals;}
             
             bool Operate(chart ***mapp, vector<string> *info_msgs){
             
             int i,j, hp_loss, avail_gold, gold_gain, top_gain=-1;
             ship *shp, *shp_heal=NULL;
             stringstream ss;
             
             for(i=x_pos-1;i<=x_pos+1;i++){
                     if((i>-1) && (i<N)){
                         for(j=y_pos-1;j<=y_pos+1;j++){
                             if((j>-1) && (j<N)){
                               
                               if((i!=x_pos) || (j!=y_pos)){
                                     
                                 if((!mapp[i][j]->getPort()) && (mapp[i][j]->getShip()!=0)){
                                     shp=mapp[i][j]->getShip();
                                     
                                     if( dynamic_cast<pirate *>(shp)==NULL){
                                         avail_gold=shp->getCurtreas();
                                         hp_loss= (shp->getMaxhp() - shp->getCurhp() );
                                         
                                         if((hp_loss>0) && (avail_gold>0)){
                                             
                                             if(hp_loss>=avail_gold){
                                                 gold_gain=avail_gold;
                                                 
                                             }
                                             else{
                                                 gold_gain=hp_loss;
                                                 
                                             }
                                             if(gold_gain>top_gain){
                                                 top_gain=gold_gain;
                                                 shp_heal=shp;
                                             }
                                         }
                                     
                                     }
                                 }
                               }
                             
                             }
                         }
                     }
                                              
             }
             
             
             if(top_gain<0){
                 if((this->getCurhp() < this->getMaxhp()) && (this->getCurtreas()>0)){
                     hp_loss=this->getMaxhp()-this->getCurhp();
                     if(hp_loss >= this->getCurtreas()){
                         this->setCurhp(this->getCurhp()+this->getCurtreas());
                         total_heal_out+=this->getCurtreas();
                         total_heals++;
                         total_heal_out_+=this->getCurtreas();
                         total_heals_++;
                         ss.clear();
                         ss.str("");
                         ss << this->getCurtreas();
                         this->setCurtreas(0);
                         (*info_msgs).push_back("Ship "+this->getName()+" healed itself for "+ss.str()+" hp!\n");
                         
                         return true;
                     }
                     else{
                         this->setCurhp(this->getCurhp()+hp_loss);
                         total_heal_out+=hp_loss;
                         total_heals++;
                         total_heal_out_+=hp_loss;
                         total_heals_++;
                         this->setCurtreas(this->getCurtreas()-hp_loss);
                         ss.clear();
                         ss.str("");
                         ss << hp_loss;
                         (*info_msgs).push_back("Ship "+this->getName()+" healed itself for "+ss.str()+" hp!\n");
                         
                         return true;
                     }
                 }
                 else{
                      (*info_msgs).push_back("Ship "+this->getName()+" didn't heal any ship!\n");
                      
                      return false;
                 }
             }
             avail_gold=shp_heal->getCurtreas();
             hp_loss=(shp_heal->getMaxhp() - shp_heal->getCurhp());
             if(hp_loss>=avail_gold){
                 shp_heal->setCurhp(shp_heal->getCurhp()+avail_gold);
                 total_heal_out+=avail_gold;
                 total_heals++;
                 total_heal_out_+=avail_gold;
                 total_heals_++;
                 shp_heal->setCurtreas(0);
                 this->setCurtreas(this->getCurtreas()+avail_gold);
                 ss.clear();
                 ss.str("");
                 ss << avail_gold;
                 (*info_msgs).push_back("Ship "+this->getName()+" healed ship "+shp_heal->getName()+" for "+ss.str()+" hp!\n");
                 
                 return true;
             }
             else{
                 shp_heal->setCurhp(shp_heal->getCurhp()+hp_loss);
                 total_heal_out+=hp_loss;
                 total_heals++;
                 total_heal_out_+=hp_loss;
                 total_heals_++;
                 shp_heal->setCurtreas(shp_heal->getCurtreas()-hp_loss);
                 this->setCurtreas(this->getCurtreas()+hp_loss);
                 ss.clear();
                 ss.str("");
                 ss << hp_loss;
                 (*info_msgs).push_back("Ship "+this->getName()+" healed ship "+shp_heal->getName()+" for "+ss.str()+" hp!\n");
                 
                 return true;
             }
   
             }
    
};

class exploring: public ship{                                                   //klassi eksereuntikou ploiou
      protected:
                int total_evades;
                
      
      public:
             static int shipcount,dead_ships,total_gold_in_, total_gold_out_, total_dmg_in_, total_heal_in_, total_blocks_moved_;
             static int e_shipcount, total_evades_;
             
             exploring(){
                         shipcount++;
                         stringstream ss;
                         ss << shipcount;
                         name="Exploring_"+ss.str();
                         maxhp=EXPLORE_HP;
                         curhp=EXPLORE_HP;
                         speed=2;
                         curtreas=0;
                         isDead=false;
                         isRemoved=false;
                         total_gold_in=0;
                         total_gold_out=0;
                         total_dmg_in=0;
                         total_heal_in=0;
                         total_blocks_moved=0;
                         total_evades=0;
             }
             exploring(int x, int y){
                           shipcount++;
                           e_shipcount++;
                           stringstream ss;
                           ss << e_shipcount;
                           name="Exploring_"+ss.str();
                           maxhp=EXPLORE_HP;
                           curhp=EXPLORE_HP;
                           speed=2;
                           curtreas=0;
                           x_pos=x;
                           y_pos=y;
                           isDead=false;
                           isRemoved=false;
                           total_gold_in=0;
                           total_gold_out=0;
                           total_dmg_in=0;
                           total_heal_in=0;
                           total_blocks_moved=0;
                           total_evades=0;
                           
             }
             virtual ~exploring(){}
             int getTotalEvades(){return total_evades;}
             
             virtual bool Operate(chart ***mapp, vector<string> *info_msgs){
                  
             int i,j,m,n, weath_d, hits_d;
             int hits[3][3];
             
             for(i=0;i<3;i++){
                 for(j=0;j<3;j++){
                     hits[i][j]=0;
                 }
             }
             
             
             for(i=x_pos-1;i<=x_pos+1;i++){
                 if((i>-1) && (i<N)){
                     for(j=y_pos-1;j<=y_pos+1;j++){
                         if((j>-1) && (j<N)){ 
                             
                             if(mapp[i][j]->getPort()){
                                 hits[i-(x_pos-1)][j-(y_pos-1)]++;
                             }
                             else if(mapp[i][j]->getShip()!=0){
                                 
                                 hits[i-(x_pos-1)][j-(y_pos-1)]++;
                                 
                                 
                                 if((dynamic_cast<pirate *>(mapp[i][j]->getShip())!=0) && (dynamic_cast<prt_r *>(mapp[i][j]->getShip())==0)){
                                     
                                     
                                     for(m=i-1;m<=i+1;m++){
                                         if((m>-1) && (m<N)){
                                             for(n=j-1;n<=j+1;n++){
                                                 if((n>-1) && (n<N)){
                                                     
                                                     
                                                     if( ( (m-(x_pos-1)) >-1) && ( (m-(x_pos-1)) <3) && ( (n-(y_pos-1)) >-1) && ( (n-(y_pos-1)) <3)){
                                                        
                                                         hits[m-(x_pos-1)][n-(y_pos-1)]++;
                                                         
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
             }
             m=-1;
             n=-1;
             hits_d=5;
             weath_d=11;
             
             for(i=0;i<3;i++){
               if((x_pos-1+i>-1) && (x_pos-1+i<N)){
                 for(j=0;j<3;j++){
                   if((y_pos-1+j>-1) && (y_pos-1+j<N)){
                     if((!mapp[x_pos-1+i][y_pos-1+j]->getPort()) && (mapp[x_pos-1+i][y_pos-1+j]->getShip()==0)){
                         if(hits[i][j]<hits_d){
                             m=x_pos+i-1;
                             n=y_pos+j-1;
                             hits_d=hits[i][j];
                             weath_d=mapp[x_pos+i-1][y_pos+j-1]->getWeather();
                             
                         }
                         else if(hits[i][j]==hits_d){
                             if(mapp[x_pos+i-1][y_pos+j-1]->getWeather() < weath_d){
                                 m=x_pos+i-1;
                                 n=y_pos+j-1;
                                 hits_d=hits[i][j];
                                 weath_d=mapp[x_pos+i-1][y_pos+j-1]->getWeather();
                             }
                         }
                     }
                   }
                 }
               }
             }
             if((m==-1) || (n==-1) || (hits_d==5) || (weath_d==11)){
                 (*info_msgs).push_back("Ship "+this->getName()+" couldn't evade anything because it was blocked!\n");
                 
                 return false;
             }
             
             mapp[m][n]->setShip(mapp[x_pos][y_pos]->getShip());
             mapp[x_pos][y_pos]->setShip(0);
             setX_pos(m);
             setY_pos(n);
             (*info_msgs).push_back("Ship "+this->getName()+" moved one position to evade incoming damage!\n");
             total_evades++;
             total_evades_++;
             total_blocks_moved++;
             total_blocks_moved_++;
             ship::total_blocks_moved_++;
             return true;
             }
   
};

class exp_s: public exploring{                                   //klassi eksereunitikou promitheutikou ploiou- ypoklassi tou eksereunitikou
      protected:
                int total_sups;
                
      public:
             static int shipcount, dead_ships, total_gold_in_, total_gold_out_, total_dmg_in_, total_heal_in_, total_blocks_moved_;
             static int total_sups_;
             
             exp_s(){
                         shipcount++;
                         stringstream ss;
                         ss << shipcount;
                         name="Exploring_S_"+ss.str();
                         maxhp=EXP_S_HP;
                         curhp=EXP_S_HP;
                         speed=2;
                         curtreas=0;
                         isDead=false;
                         isRemoved=false;
                         total_gold_in=0;
                         total_gold_out=0;
                         total_dmg_in=0;
                         total_heal_in=0;
                         total_blocks_moved=0;
                         total_sups=0;
                         
             }
             exp_s(int x, int y){
                           shipcount++;
                           stringstream ss;
                           ss << shipcount;
                           name="Exploring_S_"+ss.str();
                           maxhp=EXP_S_HP;
                           curhp=EXP_S_HP;
                           speed=2;
                           curtreas=0;
                           x_pos=x;
                           y_pos=y;
                           isDead=false;
                           isRemoved=false;
                           total_gold_in=0;
                           total_gold_out=0;
                           total_dmg_in=0;
                           total_heal_in=0;
                           total_blocks_moved=0;
                           total_sups=0;
                           
             }
             virtual ~exp_s(){}
             int getTotalSups(){return total_sups;}
             
             bool Operate(chart ***mapp, vector<string> *info_msgs){
                  
             int i, j, count=0, gold_give;
             ship *shp;
             stringstream ss;
             bool gold_get=false;
             
             for(i=x_pos-1;i<=x_pos+1;i++){
                 if((i>-1) && (i<N)){
                     for(j=y_pos-1;j<=y_pos+1;j++){
                         if((j>-1) && (j<N)){
                             
                             if((i!=x_pos) || (j!=y_pos)){
                                 
                                 if(mapp[i][j]->getPort()){
                                     this->setCurtreas(this->getCurtreas()+MAX_SUPPLY);
                                     gold_get=true;   
                                 }
                                 else if(mapp[i][j]->getShip()!=0){
                                      shp=mapp[i][j]->getShip();
                                      if( (dynamic_cast<exp_s *>(shp)==0) && (dynamic_cast<exploring *>(shp)!=0) ){
                                          count++;
                                      
                                      }
                                 }          
                             }

                         }
                     }
                 }
             }
             if((this->getCurtreas()>0) && (count>0)){
                 if((this->getCurtreas()/count)<=MAX_SUPPLY){
                     gold_give=this->getCurtreas() / count;
                 }
                 else{
                      gold_give=MAX_SUPPLY;
                 
                 }
             }
             else{
                  if(gold_get){
                      ss.clear();
                      ss.str("");
                      ss << MAX_SUPPLY;
                      (*info_msgs).push_back("Ship "+this->getName()+" got "+ss.str()+" gold from a near port but didn't supply any ship.\n");
                  }
                  else{
                      (*info_msgs).push_back("Ship "+this->getName()+" didn't supply any ship.\n");
                  }
                  return false;
             }
             if(gold_get){
                 ss.clear();
                 ss.str("");
                 ss << MAX_SUPPLY;
                 (*info_msgs).push_back("Ship "+this->getName()+" got "+ss.str()+" gold from a near port and supplied:\n");
             }
             else{
                 (*info_msgs).push_back("Ship "+this->getName()+" supplied:\n");
             }
             for(i=x_pos-1;i<=x_pos+1;i++){
                 if((i>-1) && (i<N)){
                     for(j=y_pos-1;j<=y_pos+1;j++){
                         if((j>-1) && (j<N)){
                             
                             if((i!=x_pos) || (j!=y_pos)){
                                   
                                   if((!mapp[i][j]->getPort()) && (mapp[i][j]->getShip()!=0)){
                                       shp=mapp[i][j]->getShip();
                                       if( (dynamic_cast<exp_s *>(shp)==0) && (dynamic_cast<exploring *>(shp)!=0) ){
                                           shp->setCurtreas(shp->getCurtreas()+gold_give);
                                           total_sups++;
                                           total_sups_++;
                                           this->setCurtreas(this->getCurtreas()-gold_give);
                                           ss.clear();
                                           ss.str("");
                                           ss << gold_give;
                                           (*info_msgs).push_back("\tShip "+shp->getName()+" with "+ss.str()+" gold\n");
                                           
                                       }
                                   }
                             }
                                   
                         }
                     }
                 }
             }
             return true;
                  
             }
      
};


