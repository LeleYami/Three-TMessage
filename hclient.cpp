#include "Sclass.h"
#include "TFile.h"
#include "TSocket.h"
#include "TMessage.h"

void hclient()
{
   // Open connection to server
   TSocket *sock = new TSocket("localhost", 51400);

   //select which file to transfer
   std::cout<<"please input number:"<<std::endl;
   int a;
   std::cin>>a;
    
   //open the file and get the object
   if(a==1){
      TFile f1("test1.root");
      Sclass* obj1=dynamic_cast<Sclass*>(f1.Get("anObject1"));
      //create TMessage to save the object
      TMessage mess(kMESS_OBJECT);
      mess.WriteObject(obj1);
      obj1->Print();

      // send message
      sock->Send(mess);
   }else if(a==2){
      TFile f2("test2.root");
      Sclass* obj2=dynamic_cast<Sclass*>(f2.Get("anObject2"));
      //create TMessage to save the object 
      TMessage mess(kMESS_OBJECT);
      mess.WriteObject(obj2);
      obj2->Print();

      // send message
      sock->Send(mess);
   }else if(a==3){
      TFile f3("test3.root");
      Sclass* obj3=dynamic_cast<Sclass*>(f3.Get("anObject3"));
      //create TMessage to save the object 
      TMessage mess(kMESS_OBJECT);
      mess.WriteObject(obj3);
      obj3->Print();

      // send message
      sock->Send(mess);
   }else{
      sock->Send(" have no object to output\n");
      printf("the input is wrong\n");    
   }
   // Close the socket
   sock->Close();
}

int main(int argc, char **argv){
	hclient();
        return 0;
}
