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
/*string *PMT_ID;
string  A, B,C;
PMT_ID = new string[137];
char  input_PMT[500]="./PMT_Input.txt";
ifstream inputfile2(input_PMT, ifstream::in);
if(inputfile2.fail()){ cout<<" This File Does not exit"<<endl; inputfile2.close();}
for (int i=101;i<137;i++)
    {
     inputfile2>>PMT_ID[i]>>A>>B>>C;
     cout<<"PMT_ID="<<PMT_ID[i]<<endl;
    }*/

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
/*
int lightIntensity=0;
if(strstr(tmpFileName,"_0.1pe_LED"))
{
    lightIntensity=0;
}
else if(strstr(tmpFileName,"_3000_LED"))
{
  lightIntensity=1;
}
else
{
  cout<<"find error"<<endl;
  return -1;
}
  
*/
sprintf(tmpFileName,"mass%d_intensity1_container1_results.txt",massNumber);
sprintf(tmpTagName,"mass%d_intensity1_container1_tag.txt",massNumber);
sprintf(tmpTagName_new,"mass%d_intensity1_container1_tag_new.txt",massNumber);
outFile_tag.open(tmpTagName);
outFile_tag_new.open(tmpTagName_new);
outFile.open(tmpFileName);
outFile<<"Channel"<<"  "<<"Mass_ID"<<"  "<<"PMT_ID"<<"  "<<"MCP_Hama"<<"  "<<"HV"<<"  "<<"Gain"<<"  "<<"Mu"<<"  "<<"CF"<<"  "<<"Mu_charge"<<"  "<<"CF_charge"<<"  "<<"Mean_charge"<<"  "<<"Amplitude"<<"  "<<"Resolution"<<"  "<<"P/V"<<"  "<<"S/N"<<"  "<<"Risetime"<<"  "<<"Falltime"<<"  "<<"FWHM"<<"  "<<"Prepulse_proportion"<<"  "<<"Dark_rate"<<"  "<<"Pedestal_chi2_ndf"<<"  "<<"Signal_chi2_ndf"<<"  "<<"PDE"<<"  "<<"Hittime"<<"  "<<"TTS"<<"  "<<"Prepulse_proportion_sub"<<endl;
for(int i=101;i<137;i++)
{
    if (i!=131)
    {
        outFile<<i<<"  "<<massNumber<<"  "<<PMT_ID[i]<<"  "<<Mcp_Hama[i]<<"  "<<HV[i]<<"  "<<Gain[i]<<"  "<<Mu[i]<<"  "<<CF[i]<<"  "<<Mu_charge[i]<<"  "<<CF_charge[i]<<"  "<<Mean_charge[i]<<"  "<<Amplitude[i]<<"  "<<Resolution[i]<<"  "<<P_V[i]<<"  "<<S_N[i]<<"  "<<Risetime[i]<<"  "<<Falltime[i]<<"  "<<FWHM_NEW[i]<<"  "<<Prepulse_proportion[i]<<"  "<<Dark_rate[i]<<"  "<<Pedestal_chi2_ndf[i]<<"  "<<Signal_chi2_ndf[i]<<"  "<<PDE[i]<<"  "<<Hittime[i]<<"  "<<TTS[i]<<"  "<<Prepulse_proportion_sub[i]<<endl;
		/*----------------------MYSQL MODULE----------------*/
		Connection conn(false);
    	if (conn.connect(DATEBASE_NAME, DATEBASE_IP, DATEBASE_USERNAME, DATEBASE_PWD))
		{
			time_t now = time(0);
			char Day[45];
			strftime(Day, sizeof(Date), "%Y-%m-%d", localtime(&now));
			string Date;
			Date = Day;
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
				string UpdateSQL="UPDATE ";
				SS << UpdateSQL << DATABASE_TABLE << " SET " << "Gain_at_setpoints3000='" << Gain[i] << "',Mu_at_setpoints3000='" << Mu[i] << "',CF_at_setpoints3000='" << CF[i] << "',Mu_Charge_at_setpoints3000='" << Mu_charge[i] << "',CF_charge_at_setpoints3000='" << CF_charge[i] << "',Mean_charge_at_setpoints3000='" << Mean_charge[i] << "',Amplitude_at_setpoints3000='" << Amplitude[i] << "',Resolution_at_setpoints3000='" << Resolution[i] << "',PvsV_at_setpoints3000='" << P_V[i] << "',SvsN_at_setpoints3000='" << S_N[i] << "',Risetime_at_setpoints3000='" << Risetime[i] << "',Falltime_at_setpoints3000='" << Falltime[i] << "',FWHM_at_setpoints3000='" << FWHM_NEW[i] << "',Prepulse_proportion_at_setpoints3000='" << Prepulse_proportion[i] << "',Dark_rate_at_setpoints3000='" << Dark_rate[i] << "',Pedestal_chi2_ndf_at_setpoints3000='" << Pedestal_chi2_ndf[i] << "',Signal_chi2_ndf_at_setpoints3000='" << Signal_chi2_ndf[i] << "',PDE_at_setpoints3000='" << PDE[i] << "',Hittime_at_setpoints3000='" << Hittime[i] << "',TTS_LED_at_setpoints3000='" << TTS[i] << "',Prepulse_proportion_sub_at_setpoints3000='" << Prepulse_proportion_sub[i] << "' WHERE Channel='" << i << "' AND Mass_ID='" << massNumber << "' AND PMT_ID ='" << PMT_ID[i] << "'";
				UpdateSQL = SS.str();
				cout << UpdateSQL << endl;
				Query query1 = conn.query(UpdateSQL);
				StoreQueryResult res1 = query1.store();
				cout << PMT_ID[i] << " Update Success!" << endl;
			}
			else 
			{ 
				cout << "This record is not existed!" << endl;
				SS.str("");
				string InsertSQL="INSERT INTO ";
				SS << InsertSQL << DATABASE_TABLE << "(Channel,Mass_ID,PMT_ID,MCP_Hama,HV,Gain_at_setpoints3000,Mu_at_setpoints3000,CF_at_setpoints3000,Mu_Charge_at_setpoints3000,CF_charge_at_setpoints3000,Mean_charge_at_setpoints3000,Amplitude_at_setpoints3000,Resolution_at_setpoints3000,PvsV_at_setpoints3000,SvsN_at_setpoints3000,Risetime_at_setpoints3000,Falltime_at_setpoints3000,FWHM_at_setpoints3000,Prepulse_proportion_at_setpoints3000,Dark_rate_at_setpoints3000,Pedestal_chi2_ndf_at_setpoints3000,Signal_chi2_ndf_at_setpoints3000,PDE_at_setpoints3000,Hittime_at_setpoints3000,TTS_LED_at_setpoints3000,Prepulse_proportion_sub_at_setpoints3000) VALUES ('" <<  i << "','" << massNumber << "','" << PMT_ID[i] << "','" << Mcp_Hama << "','" << HV << "','" << Gain[i] << "','" << Mu[i] << "','" << CF[i] << "','" << Mu_charge[i] << "','" << CF_charge[i] << "','" << Mean_charge[i] << "','" << Amplitude[i] << "','" << Resolution[i] << "','" << P_V[i] << "','" << S_N[i] << "','" << Risetime[i] << "','" << Falltime[i] << "','" << FWHM_NEW[i] << "','" << Prepulse_proportion[i] << "','" << Dark_rate[i] << "','" << Pedestal_chi2_ndf[i] << "','" << Signal_chi2_ndf[i] << "','" << PDE[i] << "','" << Hittime[i] << "','" << TTS[i] << "','" << Prepulse_proportion_sub[i] << "')";
				InsertSQL = SS.str();
				cout << InsertSQL << endl;
				Query query2 = conn.query(InsertSQL);
				StoreQueryResult res2 = query2.store();
				cout << PMT_ID[i] << " Insert Success!" << endl;
			}
		}
		else
		{
			cout << "DB connection fault!" << endl;
		};
		/*------------------------MYSQL MODULE END------------*/
	}
    if (i==131)
       {outFile<<i<<"  "<<massNumber<<"  "<<"NAN"<<"  "<<"NAN"<<"  "<<"NAN"<<"  "<<"NAN"<<"  "<<"NAN"<<"  "<<"NAN"<<"  "<<"NAN"<<"  "<<"NAN"<<"  "<<"NAN"<<"  "<<"NAN"<<"  "<<"NAN"<<"  "<<"NAN"<<"  "<<"NAN"<<"  "<<"NAN"<<"  "<<"NAN"<<"  "<<"NAN"<<"  "<<"NAN"<<"  "<<"NAN"<<"  "<<"NAN"<<"  "<<"NAN"<<"  "<<"NAN"<<"  "<<"NAN"<<"  "<<"NAN"<<"  "<<"NAN"<<endl;
    }
    if (i!=131)
       {
         if((Gain[i]<9.5E6)||(Gain[i]>1.3E7))
          {outFile_tag<<"channel:"<<i<<"---"<<"HV:"<<HV[i]<<"---"<<"PMT_ID:"<<PMT_ID[i]<<"----"<<"Gain="<<Gain[i]<<"  "<<"error of connection-->Container system"<<endl;
           outFile_tag_new<<massNumber<<"  "<<i<<"  "<<HV[i]<<"  "<<PMT_ID[i]<<"  "<<"Gain="<<Gain[i]<<"  "<<"Red_Bad_connection"<<"  "<<"Container"<<endl;}
        else
        {
        if(PDE[i]>23&&PDE[i]<25)
          {
           outFile_tag<<"channel:"<<i<<"---"<<"HV:"<<HV[i]<<"---"<<"PMT_ID:"<<PMT_ID[i]<<"----"<<"PDE="<<PDE[i]<<"      "<<"Yellow Mark for the edge of PDE requirement-->Scanning Station"<<endl;
           outFile_tag_new<<massNumber<<"  "<<i<<"  "<<HV[i]<<"  "<<PMT_ID[i]<<"  "<<"PDE="<<PDE[i]<<"  "<<"Yellow_Edge_PDE"<<"  "<<"Scanning"<<endl;
          }
        if(PDE[i]<23)
          {
           outFile_tag<<"channel:"<<i<<"---"<<"HV:"<<HV[i]<<"---"<<"PMT_ID:"<<PMT_ID[i]<<"----"<<"PDE="<<PDE[i]<<"      "<<"Red Mark for low PDE-->rejection"<<endl; 
           outFile_tag_new<<massNumber<<"  "<<i<<"  "<<HV[i]<<"  "<<PMT_ID[i]<<"  "<<"PDE="<<PDE[i]<<"  "<<"Red_PDE<23"<<"  "<<"Rejection"<<endl;
          }
        }      
    }
    
}
outFile.close();

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
