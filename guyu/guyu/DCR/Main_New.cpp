#include <iostream>
#include <TMath.h>
#include <TFile.h>
#include <TTree.h>
#include <iostream>
#include <fstream>
#include <TF1.h>
#include <string>
using std::cout;  
using std::endl;  
using std::string; 
#include <TFitResult.h>
#include <TFitResultPtr.h>
#include <TFormula.h>
#include <TChain.h>
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

char* str_remove_key( char* src,char* key);

void Main_New(char *inDirectory)
{
 //********call the function******************
 open_directory_new(inDirectory);


 //******create some parameters for cout*******
 string PMT_ID[137];
 double Dark_Rate[137];
 int massNumber;
 int Threshold;
 int Soft_channel;
 int Hard_channel;
 //**********open the total file with the txt file******
 string A;
 char a[50000];
 string channel_filename_new;
 string public_filename=inDirectory;
 char   public_filename_c[500];
 strcpy(public_filename_c,inDirectory);
 cout<<public_filename_c<<endl;
 char *pointer0=strstr(public_filename_c,"/mass");
 cout<<pointer0<<endl;
 sscanf(pointer0,"/mass%d",&massNumber); 

 //************for input file to get the PMT_ID and HV
 string PMTID_Input[137],HV_Input_131,MCP_HAMA_Input_131;
 double ChannelID_Input[137],HV_Input[137],MCP_HAMA_Input[137];
 string PMT_Input="PMT_Input.txt";
 string PMT_Input_new=public_filename+'/'+PMT_Input;
 char   PMT_Input_new_c[500];
 strcpy(PMT_Input_new_c,PMT_Input_new.c_str());
 ifstream PMT_Input_file(PMT_Input_new_c, ifstream::in);
 if(PMT_Input_file.fail()){ cout<<" This File Does not exit"<<endl; PMT_Input_file.close();}
 cout<<"successful about PMT_Input"<<endl;
 for(int i=101;i<137;i++)
    {
     if (i!=131)
        {PMT_Input_file>>PMTID_Input[i]>>ChannelID_Input[i]>>HV_Input[i]>>MCP_HAMA_Input[i];}
     else
        {PMT_Input_file>>PMTID_Input[i]>>ChannelID_Input[i]>>HV_Input_131>>MCP_HAMA_Input_131;}
    }


 //****for out-put file*********
 ofstream outFile;
 ofstream outFile_tag;
 ofstream outFile_tag_new;
 char tmpFileName[500];
 char tmpFileName_tag[500];
 char tmpFileName_tag_new[500];
 sprintf(tmpFileName,"mass%d_3mv_1E7HV_container1_darkrate_results.txt",massNumber);
 sprintf(tmpFileName_tag,"mass%d_3mv_1E7HV_container1_darkrate_tag.txt",massNumber);
 sprintf(tmpFileName_tag_new,"mass%d_3mv_1E7HV_container1_darkrate_tag_new.txt",massNumber);
 outFile.open(tmpFileName);
 outFile_tag.open(tmpFileName_tag);
 outFile_tag_new.open(tmpFileName_tag_new);
 outFile<<"channel_ID"<<"  "<<"massNumber"<<"  "<<"PMT_ID"<<"  "<<"HV"<<"  "<<"darkrate"<<endl;
 string channel_filename;
 char total_filename[500]="Filelist.txt";
 ifstream inputfile_new(total_filename, ifstream::in);
 if(inputfile_new.fail()){ cout<<" This File Does not exit"<<endl; inputfile_new.close();}
 cout<<"successful"<<endl;

  while(getline(inputfile_new,channel_filename))
    {

 if((channel_filename!=".")&&(channel_filename!=".."))
 {
 char channel_filename_c[500];
 strcpy(channel_filename_c,channel_filename.c_str());
 if(strstr(channel_filename_c,"End_DCR"))
   {
    if(strstr(channel_filename_c,"MCP"))
      {
       char *pointer1=strstr(channel_filename_c,"_");
       sscanf(pointer1,"_%d_MCP",&Soft_channel);
       cout<<Soft_channel<<endl;
      }
    if(strstr(channel_filename_c,"Ham"))
      {
       char *pointer1=strstr(channel_filename_c,"_");
       sscanf(pointer1,"_%d_Ham",&Soft_channel);
       cout<<Soft_channel<<endl;
      }
   int mark=0;
   string pmt_id="gfjjahsadjkjk";
   for (int i=0;i<20;i++)
       {
        if ((channel_filename_c[i]==' ')||(channel_filename_c[i]=='_'))
           {
            mark=i;
            break;    
           }     
       }
  pmt_id=channel_filename.substr(0,mark);
   cout<<pmt_id<<endl;
 PMT_ID[Soft_channel]=pmt_id;
 channel_filename_new=public_filename+'/'+channel_filename;
 cout<<channel_filename_new<<endl;
 char exp_filename[500];
 strcpy(exp_filename,channel_filename_new.c_str());
 ifstream inputfile(exp_filename, ifstream::in);
 if(inputfile.fail()){ cout<<" This File Does not exit"<<endl; inputfile.close();}
 else cout<<"open is OK!"<<endl;
 inputfile>>A>>A>>A>>A;
// cout<<A<<endl;
 strcpy(a,A.c_str());
 cout<<a<<endl; 
 /* for (int i=0;i<40;i++)
       {
        if (a[i]=='H')
           {
            mark=i;
            break;
           }
       }*/
  
 char* p =str_remove_key(a,"Hz");
 double dark_noise=0;
 double Dark_noise=0;
 sscanf(p,"%lf",&dark_noise);
 cout<<"dark_noise"<<dark_noise<<endl;
 Dark_noise=dark_noise/1000;
 Dark_Rate[Soft_channel]=Dark_noise;
 cout<<"Dark_noise="<<Dark_noise<<endl;
  //  free(p);
 //   free(p1);
 /*if(Soft_channel==135){Dark_Rate[101]=Dark_noise;}
 if(Soft_channel==136){Dark_Rate[102]=Dark_noise;}
 if(Soft_channel==134){Dark_Rate[103]=Dark_noise;}
 if(Soft_channel==133){Dark_Rate[104]=Dark_noise;}
 if(Soft_channel==132){Dark_Rate[105]=Dark_noise;}
 if(Soft_channel==131){Dark_Rate[106]=Dark_noise;}
 if(Soft_channel==130){Dark_Rate[107]=Dark_noise;}
 if(Soft_channel==129){Dark_Rate[108]=Dark_noise;}
 if(Soft_channel==128){Dark_Rate[109]=Dark_noise;}
 if(Soft_channel==127){Dark_Rate[110]=Dark_noise;}
 if(Soft_channel==126){Dark_Rate[111]=Dark_noise;}
 if(Soft_channel==125){Dark_Rate[112]=Dark_noise;}
 if(Soft_channel==123){Dark_Rate[113]=Dark_noise;}
 if(Soft_channel==124){Dark_Rate[114]=Dark_noise;}
 if(Soft_channel==122){Dark_Rate[115]=Dark_noise;}
 if(Soft_channel==121){Dark_Rate[116]=Dark_noise;}
 if(Soft_channel==120){Dark_Rate[117]=Dark_noise;}
 if(Soft_channel==119){Dark_Rate[118]=Dark_noise;}
 if(Soft_channel==118){Dark_Rate[119]=Dark_noise;}
 if(Soft_channel==117){Dark_Rate[120]=Dark_noise;}
 if(Soft_channel==116){Dark_Rate[121]=Dark_noise;}
 if(Soft_channel==115){Dark_Rate[122]=Dark_noise;}
 if(Soft_channel==114){Dark_Rate[123]=Dark_noise;}
 if(Soft_channel==113){Dark_Rate[124]=Dark_noise;}
 if(Soft_channel==111){Dark_Rate[125]=Dark_noise;}
 if(Soft_channel==112){Dark_Rate[126]=Dark_noise;}
 if(Soft_channel==110){Dark_Rate[127]=Dark_noise;}
 if(Soft_channel==109){Dark_Rate[128]=Dark_noise;}
 if(Soft_channel==108){Dark_Rate[129]=Dark_noise;}
 if(Soft_channel==107){Dark_Rate[130]=Dark_noise;}
 if(Soft_channel==106){Dark_Rate[131]=Dark_noise;}
 if(Soft_channel==105){Dark_Rate[132]=Dark_noise;}
 if(Soft_channel==104){Dark_Rate[133]=Dark_noise;}
 if(Soft_channel==103){Dark_Rate[134]=Dark_noise;}
 if(Soft_channel==102){Dark_Rate[135]=Dark_noise;}
 if(Soft_channel==101){Dark_Rate[136]=Dark_noise;}*/
} 
}
 }   

 for(int j=101;j<137;j++)
 {
	if(PMTID_Input[j]=="NAN")
    {outFile<<j<<"  "<<massNumber<<"  "<<"NAN"<<"  "<<"NAN"<<"  "<<"NAN"<<endl;}
    else
    {
		outFile<<j<<"  "<<massNumber<<"  "<<PMTID_Input[j]<<"  "<<HV_Input[j]<<"  "<<Dark_Rate[j]<<endl;
		//******insert the code here for GUYU*******************
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
			SS << "SELECT * FROM " << DATABASE_TABLE << " WHERE Channel='" << j << "' AND Mass_ID='" << massNumber << "' AND PMT_ID ='" << PMTID_Input[j] << "'";
			cout << SS.str() << endl;
			string QuerySQL = SS.str();
			Query query = conn.query(QuerySQL);
		    StoreQueryResult res = query.store();
			if ( res.num_rows() > 0)
			{ 
				cout << "This record is already existed!" << endl;
				SS.str("");
				string UpdateSQL="UPDATE ";
				SS << UpdateSQL << DATABASE_TABLE << " SET " << "Dark_count_rate='" << Dark_Rate[j] << "' WHERE Channel='" << j << "' AND Mass_ID='" << massNumber << "' AND PMT_ID ='" << PMTID_Input[j] << "'";
				UpdateSQL = SS.str();
				cout << UpdateSQL << endl;
				Query query1 = conn.query(UpdateSQL);
				StoreQueryResult res1 = query1.store();
				cout << PMTID_Input[j] << " Update Success!" << endl;
			}
			else 
			{ 
				cout << "This record is not existed!" << endl;
				SS.str("");
				string InsertSQL="INSERT INTO ";
				SS << InsertSQL << DATABASE_TABLE << "(Channel,Mass_ID,PMT_ID,Dark_count_rate) VALUES ('" <<  j << "','" << massNumber << "','" << PMTID_Input[j] << "','" << Dark_Rate[j] << "')";
				InsertSQL = SS.str();
				cout << InsertSQL << endl;
				Query query2 = conn.query(InsertSQL);
				StoreQueryResult res2 = query2.store();
				cout << PMTID_Input[j] << " Insert Success!" << endl;
			}
		}
		else
		{
			cout << "DB connection fault!" << endl;
		};
		/*------------------------MYSQL MODULE END------------*/
		if(Dark_Rate[j]<1)
		{
			outFile_tag<<"channel_ID:"<<j<<"---"<<"PMT_ID:"<<PMT_ID[j]<<"---"<<"HV:"<<HV_Input[j]<<"---"<<"Darkrate:"<<Dark_Rate[j]<<"==>container"<<endl;
			outFile_tag_new<<massNumber<<"  "<<j<<"  "<<HV_Input[j]<<"  "<<PMT_ID[j]<<"  "<<"DCR="<<Dark_Rate[j]<<"  "<<"Red_Bad_connection"<<"  "<<"Container"<<endl;
		}
		else
		{
			if(PMT_ID[j][0]=='E'&&(Dark_Rate[j]>50))
			{
				outFile_tag<<"channel_ID:"<<j<<"---"<<"PMT_ID:"<<PMT_ID[j]<<"---"<<"HV:"<<HV_Input[j]<<"---"<<"Darkrate:"<<Dark_Rate[j]<<"==>container"<<endl;
				outFile_tag_new<<massNumber<<"  "<<j<<"  "<<HV_Input[j]<<"  "<<PMT_ID[j]<<"  "<<"DCR="<<Dark_Rate[j]<<"  "<<"Red_DCR>50K"<<"  "<<"Container"<<endl;
			}
			if(PMT_ID[j][0]=='P'&&(Dark_Rate[j]>100))
			{
			outFile_tag<<"channel_ID:"<<j<<"---"<<"PMT_ID:"<<PMT_ID[j]<<"---"<<"HV:"<<HV_Input[j]<<"---"<<"Darkrate:"<<Dark_Rate[j]<<"==>container"<<endl;
			outFile_tag_new<<massNumber<<"  "<<j<<"  "<<HV_Input[j]<<"  "<<PMT_ID[j]<<"  "<<"DCR="<<Dark_Rate[j]<<"  "<<"Red_DCR>100K"<<"  "<<"Container"<<endl;
			}
		}
	} 
 }
  
}
//the function of moving some chars 
char* str_remove_key( char* src, char* key)
{
    int keyLen = strlen(key);
    char *xx = (char*)malloc(strlen(src)+1);
    char *dest = (char*)malloc(strlen(src)+1);
    char *xtemp = xx;
    int lastIndex = 0;
    int i=0;
     while((xx = strstr(src,key))!=NULL)
    {
        int len = xx - src;
        if(len){
            for(i=0;i<len;i++){

                dest[lastIndex+i] = *(src+i);
            }
            lastIndex += i;
       }else{}
        xx +=keyLen;
        src = xx;
    }
    dest[lastIndex] = '\0';
    strcat(dest,src);
    free(xtemp);
    return dest;
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

    Main_New(DIRECTORY);
    return 0;
 }
#endif
