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
#include "mysql++.h"
#include <string>
#include <sstream>
using namespace std;
using namespace mysqlpp;
#define DATEBASE_NAME "junopmttest"
#define DATEBASE_IP "119.23.229.99"
#define DATEBASE_USERNAME "pmttest"
#define DATEBASE_PWD "juno20170516"


int  Main_New(char *inDirectory)
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
	Connection conn(false);
    	if (conn.connect(DATEBASE_NAME, DATEBASE_IP, DATEBASE_USERNAME, DATEBASE_PWD))
	{
		time_t now = time(0);
	    	/* ??now è?为å¬?¸²形å*/
		char Day[45];
		strftime(Day, sizeof(Date), "%Y-%m-%d", localtime(&now));
		string Date;
		Date = Day;
		//cout << Date << endl;
		stringstream SS;
		SS.str("");
		SS << "SELECT * FROM container_test WHERE Channel='" << i << "' AND Mass_ID='" << Mass_ID << "' AND PMT_ID ='" << PMT_ID << "'";
		//cout << SS.str() << endl;
		string QuerySQL = SS.str();
		Query query = conn.query(QuerySQL);
        StoreQueryResult res = query.store();
		if ( res.num_rows() > 0)	//?¤æ??????????		{ 
			cout << "This record is already existed!" << endl;
			SS.str("");
			string UpdateSQL="UPDATE container_test SET ";
			SS << UpdateSQL << "Mcp_Hama='" << Mcp_Hama << "',HV='" << HV << "',Gain_at_0_1pe='" << GAIN << "',Mu_at_0_1pe='" << Mu << "',CF_at_0_1pe='" << CF << "',Mu_Charge_at_0_1pe='" << Mu_charge << "',CF_charge_at_0_1pe='" << CF_charge << "',Mean_charge_at_0_1pe='" << Mean_charge << "',Amplitude_at_0_1pe='" << Amplitude << "',Resolution_at_0_1pe='" << Resolution << "',PvsV_at_0_1pe='" << P_V << "',SvsN_at_0_1pe='" << S_N<< "',Risetime_at_0_1pe='" << Risetime << "',Falltime_at_0_1pe='" << Falltime << "',FWHM_at_0_1pe='" << FWHM_NEW << "',Prepulse_proportion_at_0_1pe='"<< Prepulse_proportion << "',Dark_rate_at_0_1pe='" << Dark_rate << "',Pedestal_chi2_ndf_at_0_1pe='" << Pedestal_chi2_ndf << "',Signal_chi2_ndf_at_0_1pe='" << Signal_chi2_ndf << "',PDE_at_0_1pe='" << PDE << "',Hittime_at_0_1pe='" << Hittime << "',TTS_LED_at_0_1pe='" << TTS << "',Prepulse_proportion_sub_at_0_1pe='" << Prepulse_proportion_sub << "' WHERE Channel='" << i << "' AND Mass_ID='" << Mass_ID << "' AND PMT_ID ='" << PMT_ID << "'";
			UpdateSQL = SS.str();
			//cout << UpdateSQL << endl;
			Query query1 = conn.query(UpdateSQL);
			cout << "Update Success!" << endl;
		}
		else 
		{ 
			cout << "This record is not existed!" << endl;
			SS.str("");
			string InsertSQL="INSERT INTO container_test(Date,Channel,Mass_ID,PMT_ID,MCP_Hama,HV,Gain_at_0_1pe,Mu_at_0_1pe,CF_at_0_1pe,Mu_Charge_at_0_1pe,CF_charge_at_0_1pe,Mean_charge_at_0_1pe,Amplitude_at_0_1pe,Resolution_at_0_1pe,PvsV_at_0_1pe,SvsN_at_0_1pe,Risetime_at_0_1pe,Falltime_at_0_1pe,FWHM_at_0_1pe,Prepulse_proportion_at_0_1pe,Dark_rate_at_0_1pe,Pedestal_chi2_ndf_at_0_1pe,Signal_chi2_ndf_at_0_1pe,PDE_at_0_1pe,Hittime_at_0_1pe,TTS_LED_at_0_1pe,Prepulse_proportion_sub_at_0_1pe) VALUES ('";
			SS << InsertSQL << Date << "','" << i << "','" << Mass_ID << "','" << PMT_ID << "','" << Mcp_Hama << "','" << HV << "','" << GAIN << "','" << Mu << "','" << CF << "','" << Mu_charge << "','" << CF_charge << "','" << Mean_charge << "','" << Amplitude << "','" << Resolution << "','" << P_V << "','" << S_N << "','" << Risetime << "','" << Falltime << "','" << FWHM_NEW << "','" << Prepulse_proportion << "','" << Dark_rate << "','" << Pedestal_chi2_ndf << "','" << Signal_chi2_ndf << "','" << PDE << "','" << Hittime << "','" << TTS << "','" << Prepulse_proportion_sub << "')";
			InsertSQL = SS.str();
			//cout << InsertSQL << endl;
			Query query2 = conn.query(InsertSQL);
			cout << "Insert Success!" << endl;
		}
	}
	else
	{
		cout << "DB connection fault!" << endl;
	};	
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
