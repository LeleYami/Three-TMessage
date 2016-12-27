#include "TFile.h"
#include "TServerSocket.h"
#include "TSocket.h"
#include "TMessage.h"
#include "TMonitor.h"
#include "Sclass.h"
#include "TROOT.h"

void hserv() 
{
   gROOT->ProcessLine(".L libSclass.so");
   TServerSocket *ss = new TServerSocket(51400, kTRUE);

   // Accept a connection and return a full-duplex communication socket.
   TSocket *s = ss->Accept();
   
   //Close the server socket
   ss->Close();
   
   TMessage *mess;
   //TSocket *s;
 
   s->Recv(mess);
 
   if (mess->What() == kMESS_OBJECT){ 
      Sclass* m= (Sclass*)mess->ReadObject(mess->GetClass()); 
      m->Print();
   }else if(mess->What() == kMESS_STRING){
   //}else{
      //printf("have no object to output");
      char str[64];
      mess->ReadString(str,64);
      printf("%s\n", str);
   }

   delete mess;

   printf("Client: bytes recv = %d, bytes sent = %d\n", s->GetBytesRecv(),
          s->GetBytesSent());

   // Close the socket.
   s->Close();
}

int main(int argc, char **argv){
	hserv();
}
