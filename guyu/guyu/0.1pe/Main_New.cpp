#include <stdlib.h>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <fstream>
#include <TTree.h>
#include <TFile.h>
#include <TMath.h>
#include <TH1.h>
#include <TF1.h>
#include <TROOT.h>
#include <TBrowser.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TString.h>
#include <TGraph.h>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <fstream>
#include "globle_pars.h"
#include <mysql++.h>
#include <string>
#include <sstream>
using namespace std;
using namespace mysqlpp;
#define DATEBASE_NAME "junopmttest"
#define DATEBASE_IP "119.23.229.99"
#define DATEBASE_USERNAME "pmttest"
#define DATEBASE_PWD "juno20170516"
#define DATABASE_TABLE "container_test"

int Main_New(char *inDirectory)
{
//********open the folder and print it in the a txt file********
//********call the open_directory_new function*****************
 open_directory_new(inDirectory);

//***************call the functions**************************
 string *PMT_ID;
 double  HV[137]={0},channel[137]={0},Mcp_Hama[137]={0};
 PMT_ID = new string[137];
 double Prepulse_proportion[137]={0};
 double Dark_rate[137]={0};
 double Prepulse_proportion_sub[137]={0};
 LED_reconstructe(PMT_ID, channel, HV, Mcp_Hama,Prepulse_proportion,Dark_rate,inDirectory,Prepulse_proportion_sub);
 double Mu_charge[n_channels]={0};
 double CF_charge[n_channels]={0};
 double Mean_charge[n_channels]={0};
 double Mu[n_channels]={0};
 double CF[n_channels]={0};
 double Gain[n_channels]={0};
 double P_V[n_channels]={0};
 double S_N[n_channels]={0};
 double Resolution[n_channels]={0};
 double Risetime[n_channels]={0};
 double Falltime[n_channels]={0};
 double FWHM_NEW[n_channels]={0};
 double Hittime[n_channels]={0};
 double TTS[n_channels]={0};
 double Amplitude[n_channels]={0};
 double N_pedestal_tag[n_channels]={0}; 
 double Pedestal_chi2_ndf[n_channels]={0};
 double Signal_chi2_ndf[n_channels]={0};
 double CF_New[n_channels]={0};
 double PDE[n_channels]={0};
 LED_analysis(Mu, CF, Mu_charge, CF_charge, Mean_charge, Gain, P_V, S_N, Resolution, Risetime, Falltime, FWHM_NEW, Amplitude,N_pedestal_tag,Pedestal_chi2_ndf,Signal_chi2_ndf,PDE,inDirectory,Hittime,TTS);
//*********open the PMT_input file*******************************

//****************create a txt to cout all the results********
ofstream outFile;
ofstream outFile_tag_new;
ofstream outFile_tag;
char tmpFileName[500];
char tmpTagName[500];
char tmpTagName_new[500];
strcpy(tmpFileName,inDirectory);
char *pointer0=strstr(tmpFileName,"/mass");
if(!pointer0)
{
  cout<<"read error"<<endl;
  return -1;
}

int massNumber=0;
sscanf(pointer0,"/mass%d",&massNumber);
sprintf(tmpFileName,"mass%d_intensity0_container1_results.txt",massNumber);
sprintf(tmpTagName,"mass%d_intensity0_container1_tag.txt",massNumber);
sprintf(tmpTagName_new,"mass%d_intensity0_container1_tag_new.txt",massNumber);
outFile_tag.open(tmpTagName);
outFile_tag_new.open(tmpTagName_new);
outFile.open(tmpFileName);

outFile<<"Channel"<<"  "<<"Mass_ID"<<"  "<<"PMT_ID"<<"  "<<"MCP_Hama"<<"  "<<"HV"<<"  "<<"Gain"<<"  "<<"Mu"<<"  "<<"CF"<<"  "<<"Mu_charge"<<"  "<<"CF_charge"<<"  "<<"Mean_charge"<<"  "<<"Amplitude"<<"  "<<"Resolution"<<"  "<<"P/V"<<"  "<<"S/N"<<"  "<<"Risetime"<<"  "<<"Falltime"<<"  "<<"FWHM"<<"  "<<"Prepulse_proportion"<<"  "<<"Dark_rate"<<"  "<<"Pedestal_chi2_ndf"<<"  "<<"Signal_chi2_ndf"<<"  "<<"PDE"<<"  "<<"Hittime"<<"  "<<"TTS"<<"  "<<"Prepulse_proportion_sub"<<endl;
for(int i=101;i<137;i++)
    {
    Connection conn(false);
    if (PMT_ID[i]!="NAN")
       {
        outFile<<i<<"  "<<massNumber<<"  "<<PMT_ID[i]<<"  "<<Mcp_Hama[i]<<"  "<<HV[i]<<"  "<<Gain[i]<<"  "<<Mu[i]<<"  "<<CF[i]<<"  "<<Mu_charge[i]<<"  "<<CF_charge[i]<<"  "<<Mean_charge[i]<<"  "<<Amplitude[i]<<"  "<<Resolution[i]<<"  "<<P_V[i]<<"  "<<S_N[i]<<"  "<<Risetime[i]<<"  "<<Falltime[i]<<"  "<<FWHM_NEW[i]<<"  "<<Prepulse_proportion[i]<<"  "<<Dark_rate[i]<<"  "<<Pedestal_chi2_ndf[i]<<"  "<<Signal_chi2_ndf[i]<<"  "<<PDE[i]<<"  "<<Hittime[i]<<"  "<<TTS[i]<<"  "<<Prepulse_proportion_sub[i]<<endl;
        /*----------------------MYSQL MODULE----------------*/
    	if (conn.connect(DATEBASE_NAME, DATEBASE_IP, DATEBASE_USERNAME, DATEBASE_PWD))
	{
		time_t now = time(0);
		char Day[45];
		strftime(Day, sizeof(Date), "%Y-%m-%d", localtime(&now));
		string Date;
		Date = Day;
		cout << Date << endl;
		stringstream SS;
		SS.str("");
		SS << "SELECT * FROM " << DATABASE_TABLE << " WHERE Channel='" << i << "' AND Mass_ID='" << massNumber << "' AND PMT_ID ='" << PMT_ID[i] << "'";
		cout << SS.str() << endl;
		string QuerySQL = SS.str();
		Query query = conn.query(QuerySQL);
        	StoreQueryResult res = query.store();
		if ( res.num_rows() > 0)
		{ 
			cout << "This record is already existed!" << endl;
			SS.str("");
			string UpdateSQL="UPDATE container_test SET ";
			SS << UpdateSQL << "Mcp_Hama='" << Mcp_Hama[i] << "',HV='" << HV[i] << "',Gain_at_0_1pe='" << Gain[i] << "',Mu_at_0_1pe='" << Mu[i] << "',CF_at_0_1pe='" << CF[i] << "',Mu_Charge_at_0_1pe='" << Mu_charge[i] << "',CF_charge_at_0_1pe='" << CF_charge[i] << "',Mean_charge_at_0_1pe='" << Mean_charge[i] << "',Amplitude_at_0_1pe='" << Amplitude[i] << "',Resolution_at_0_1pe='" << Resolution[i] << "',PvsV_at_0_1pe='" << P_V[i] << "',SvsN_at_0_1pe='" << S_N[i] << "',Risetime_at_0_1pe='" << Risetime[i] << "',Falltime_at_0_1pe='" << Falltime[i] << "',FWHM_at_0_1pe='" << FWHM_NEW[i] << "',Prepulse_proportion_at_0_1pe='"<< Prepulse_proportion[i] << "',Dark_rate_at_0_1pe='" << Dark_rate[i] << "',Pedestal_chi2_ndf_at_0_1pe='" << Pedestal_chi2_ndf[i] << "',Signal_chi2_ndf_at_0_1pe='" << Signal_chi2_ndf[i] << "',PDE_at_0_1pe='" << PDE[i] << "',Hittime_at_0_1pe='" << Hittime[i] << "',TTS_LED_at_0_1pe='" << TTS[i] << "',Prepulse_proportion_sub_at_0_1pe='" << Prepulse_proportion_sub[i] << "' WHERE Channel='" << i << "' AND Mass_ID='" << massNumber << "' AND PMT_ID ='" << PMT_ID[i] << "'";
			UpdateSQL = SS.str();
			cout << UpdateSQL << endl;
			Query query1 = conn.query(UpdateSQL);
			StoreQueryResult res1 = query1.store();
			cout << "Update Success!" << endl;
		}
		else 
		{ 
			cout << "This record is not existed!" << endl;
			SS.str("");
			string InsertSQL="INSERT INTO container_test(Date,Channel,Mass_ID,PMT_ID,MCP_Hama,HV,Gain_at_0_1pe,Mu_at_0_1pe,CF_at_0_1pe,Mu_Charge_at_0_1pe,CF_charge_at_0_1pe,Mean_charge_at_0_1pe,Amplitude_at_0_1pe,Resolution_at_0_1pe,PvsV_at_0_1pe,SvsN_at_0_1pe,Risetime_at_0_1pe,Falltime_at_0_1pe,FWHM_at_0_1pe,Prepulse_proportion_at_0_1pe,Dark_rate_at_0_1pe,Pedestal_chi2_ndf_at_0_1pe,Signal_chi2_ndf_at_0_1pe,PDE_at_0_1pe,Hittime_at_0_1pe,TTS_LED_at_0_1pe,Prepulse_proportion_sub_at_0_1pe) VALUES ('";
			SS << InsertSQL << Date << "','" << i << "','" << massNumber << "','" << PMT_ID[i] << "','" << Mcp_Hama[i] << "','" << HV[i] << "','" << Gain[i] << "','" << Mu[i] << "','" << CF[i] << "','" << Mu_charge[i] << "','" << CF_charge[i] << "','" << Mean_charge[i] << "','" << Amplitude[i] << "','" << Resolution[i] << "','" << P_V[i] << "','" << S_N[i] << "','" << Risetime[i] << "','" << Falltime[i] << "','" << FWHM_NEW[i] << "','" << Prepulse_proportion[i] << "','" << Dark_rate[i] << "','" << Pedestal_chi2_ndf[i] << "','" << Signal_chi2_ndf[i] << "','" << PDE[i] << "','" << Hittime[i] << "','" << TTS[i] << "','" << Prepulse_proportion_sub[i] << "')";
			InsertSQL = SS.str();
			cout << InsertSQL << endl;
			Query query2 = conn.query(InsertSQL);
			StoreQueryResult res2 = query2.store();
			cout << "Insert Success!" << endl;
		}
	}
	else
	{
		cout << "DB connection fault!" << endl;
	}
	/*------------------------MYSQL MODULE END------------*/
    }
    if (PMT_ID[i]=="NAN")
       {outFile<<i<<"  "<<massNumber<<"  "<<"NAN"<<"  "<<"NAN"<<"  "<<"NAN"<<"  "<<"NAN"<<"  "<<"NAN"<<"  "<<"NAN"<<"  "<<"NAN"<<"  "<<"NAN"<<"  "<<"NAN"<<"  "<<"NAN"<<"  "<<"NAN"<<"  "<<"NAN"<<"  "<<"NAN"<<"  "<<"NAN"<<"  "<<"NAN"<<"  "<<"NAN"<<"  "<<"NAN"<<"  "<<"NAN"<<"  "<<"NAN"<<"  "<<"NAN"<<"  "<<"NAN"<<"  "<<"NAN"<<"  "<<"NAN"<<"  "<<"NAN"<<endl;
    } 
    if (PMT_ID[i]!="NAN")
       {
        if((Gain[i]<9.5E6)||(Gain[i]>1.3E7))
          {outFile_tag<<"channel:"<<i<<"---"<<"HV:"<<HV[i]<<"---"<<"PMT_ID:"<<PMT_ID[i]<<"----"<<"Gain="<<Gain[i]<<"  "<<"Bad_connection-->Container system"<<endl;
           outFile_tag_new<<massNumber<<"  "<<i<<"  "<<HV[i]<<"  "<<PMT_ID[i]<<"  "<<"Gain="<<Gain[i]<<"  "<<"RED_Bad_connection"<<"  "<<"Container"<<endl;}
        else
        {   
        if(PMT_ID[i][0]=='E')
          {
           if(HV[i]>2350)
             {
             outFile_tag<<"channel:"<<i<<"---"<<"HV:"<<HV[i]<<"---"<<"PMT_ID:"<<PMT_ID[i]<<"----"<<"HV="<<HV[i]<<"  "<<"HV >2350V-->Container system"<<endl;
              outFile_tag_new<<massNumber<<"  "<<i<<"  "<<HV[i]<<"  "<<PMT_ID[i]<<"  "<<"HV="<<HV[i]<<"  "<<"Red_HV>2350"<<"  "<<"Container"<<endl;
             } 
           if(P_V[i]<2.5)
             {
             outFile_tag<<"channel:"<<i<<"---"<<"HV:"<<HV[i]<<"---"<<"PMT_ID:"<<PMT_ID[i]<<"----"<<"P/V="<<P_V[i]<<"  "<<"P/V<2.5-->Container system"<<endl;
             outFile_tag_new<<massNumber<<"  "<<i<<"  "<<HV[i]<<"  "<<PMT_ID[i]<<"  "<<"P/V="<<P_V[i]<<"  "<<"Red_P/V<2.5"<<"  "<<"Container"<<endl;
             }
           if(Prepulse_proportion_sub[i]>0.015)
             {
             outFile_tag<<"channel:"<<i<<"---"<<"HV:"<<HV[i]<<"---"<<"PMT_ID:"<<PMT_ID[i]<<"----"<<"Prepulse="<<Prepulse_proportion_sub[i]<<"  "<<"Prepulse>1.5%-->Container system"<<endl;
             outFile_tag_new<<massNumber<<"  "<<i<<"  "<<HV[i]<<"  "<<PMT_ID[i]<<"  "<<"PP="<<Prepulse_proportion_sub[i]<<"  "<<"Red_Prepulse>1.5%"<<"  "<<"Container"<<endl;
             }
           if(Risetime[i]>8)
             {
              outFile_tag<<"channel:"<<i<<"---"<<"HV:"<<HV[i]<<"---"<<"PMT_ID:"<<PMT_ID[i]<<"----"<<"Risetime="<<Risetime[i]<<"  "<<"Risetime>8-->Container system"<<endl;
              outFile_tag_new<<massNumber<<"  "<<i<<"  "<<HV[i]<<"  "<<PMT_ID[i]<<"  "<<"RT="<<Risetime[i]<<"  "<<"Red_Risetime>8"<<"  "<<"Container"<<endl;
             }
           if(Falltime[i]>12)
             {
              outFile_tag<<"channel:"<<i<<"---"<<"HV:"<<HV[i]<<"---"<<"PMT_ID:"<<PMT_ID[i]<<"----"<<"Falltime="<<Falltime[i]<<"  "<<"Falltime>12-->Container system"<<endl;
              outFile_tag_new<<massNumber<<"  "<<i<<"  "<<HV[i]<<"  "<<PMT_ID[i]<<"  "<<"FT="<<Falltime[i]<<"  "<<"Red_Falltime>12"<<"  "<<"Container"<<endl;
             }
           if(Hittime[i]>450)
             {
              outFile_tag<<"channel:"<<i<<"---"<<"HV:"<<HV[i]<<"---"<<"PMT_ID:"<<PMT_ID[i]<<"----"<<"Hittime="<<Hittime[i]<<"  "<<"error of base connection-->Container system"<<endl;
             outFile_tag_new<<massNumber<<"  "<<i<<"  "<<HV[i]<<"  "<<PMT_ID[i]<<"  "<<"HT="<<Hittime[i]<<"  "<<"Red_Bad_connection"<<"  "<<"Container"<<endl;
             }
             
          }
          if(PMT_ID[i][0]=='P')
            {
             if(HV[i]>2800)
             {
            outFile_tag<<"channel:"<<i<<"---"<<"HV:"<<HV[i]<<"---"<<"PMT_ID:"<<PMT_ID[i]<<"----"<<"HV="<<HV[i]<<"  "<<"HV >2800V-->Container system"<<endl;
            outFile_tag_new<<massNumber<<"  "<<i<<"  "<<HV[i]<<"  "<<PMT_ID[i]<<"  "<<"HV="<<HV[i]<<"  "<<"Red_HV>2800"<<"  "<<"Container"<<endl;
             }
             if(P_V[i]<2.5)
             {
             outFile_tag<<"channel:"<<i<<"---"<<"HV:"<<HV[i]<<"---"<<"PMT_ID:"<<PMT_ID[i]<<"----"<<"P/V="<<P_V[i]<<"  "<<"P/V<2.5-->Container system"<<endl;
            outFile_tag_new<<massNumber<<"  "<<i<<"  "<<HV[i]<<"  "<<PMT_ID[i]<<"  "<<"P/V="<<P_V[i]<<"  "<<"Red_P/V<2.5"<<"  "<<"Container"<<endl;
             }
             if(Resolution[i]>0.4)
             {
             outFile_tag<<"channel:"<<i<<"---"<<"HV:"<<HV[i]<<"---"<<"PMT_ID:"<<PMT_ID[i]<<"----"<<"Resolution="<<Resolution[i]<<"  "<<"Resolution>40%-->Container system"<<endl;
             outFile_tag_new<<massNumber<<"  "<<i<<"  "<<HV[i]<<"  "<<PMT_ID[i]<<"  "<<"Resolution="<<Resolution[i]<<"  "<<"Red_Reso<2.5"<<"  "<<"Container"<<endl;
             } 
             if(Hittime[i]>450)
             {
              outFile_tag<<"channel:"<<i<<"---"<<"HV:"<<HV[i]<<"---"<<"PMT_ID:"<<PMT_ID[i]<<"----"<<"Hittime="<<Hittime[i]<<"  "<<"error of base connection-->Container system"<<endl;
              outFile_tag_new<<massNumber<<"  "<<i<<"  "<<HV[i]<<"  "<<PMT_ID[i]<<"  "<<"HT="<<Hittime[i]<<"  "<<"Red_Bad_connection"<<"  "<<"Container system"<<endl;
             }
             
            }
      }       
        }
    
}
outFile.close();
outFile_tag.close();
outFile_tag_new.close();

 return 0;
}
#ifndef __CINT__
int main(int argc, char **argv)
{
  char DIRECTORY[500];
 
  if(argc==1)
    strcpy(DIRECTORY,"/pmtfs/disk01/container_data/calibrationSetPointTesting/run38_09_22_2017_1E7HV_3000_LED_mass13/");
  else if(argc==2)
    strcpy(DIRECTORY,argv[1]);

    cout<<DIRECTORY<<endl;

// LED_reconstructe();
   Main_New(DIRECTORY);
   return 0;
}
#endif
