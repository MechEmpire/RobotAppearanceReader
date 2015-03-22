#include <dlfcn.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <streambuf>
#include "sys/RobotAI_Interface.h"

using namespace std;


int main(int argc, char * argv[])
{
    //argv[1] the path and name for the libAI.so
    //argv[2] the path and name for the output json file
    if(argc > 3)
    {
        return -1;
    }

    void * ai_handle;
    typedef RobotAI_Interface* (*Export)();
    typedef void (*FreeRobotAIPointer)(RobotAI_Interface*);
    Export exportAIFunction;
    FreeRobotAIPointer freeAIFunction;
    RobotAI_Interface* pAI;

    ai_handle = dlopen(argv[1],RTLD_LAZY);
    exportAIFunction = (Export)dlsym(ai_handle,"Export");
    freeAIFunction = (FreeRobotAIPointer)dlsym(ai_handle,"FreeRobotAIPointer");
    pAI = (*exportAIFunction)();

    weapontypename weapon = WT_Cannon;
    enginetypename engine = ET_Spider;
    pAI -> ChooseArmor(weapon,engine,false);

    int wr=0,wg=0,wb=0;
    int er=0,eg=0,eb=0;
    wr = pAI -> GetWeaponRed();
    wg = pAI -> GetWeaponGreen();
    wb = pAI -> GetWeaponBlue();
    er = pAI -> GetEngineRed();
    eg = pAI -> GetEngineGreen();
    eb = pAI -> GetEngineBlue();


    //output json
    //

    bool tofile = true;
    if(strcmp(argv[2],"stdout") == 0)
    {
        tofile = false;
    }


    ofstream out;
    streambuf * x = NULL;
    if(tofile)
    {
        out.open(argv[2]);
        x = cout.rdbuf(out.rdbuf());
    }

    cout<<"{";
    cout<<"\"name\":\""<<pAI->GetName()<<"\",";
    cout<<"\"author\":\""<<pAI->GetAuthor()<<"\",";
    cout<<"\"weapon\":"<<weapon<<",";
    cout<<"\"engine\":"<<engine<<",";
    cout<<"\"wr\":"<<wr<<",";
    cout<<"\"wg\":"<<wg<<",";
    cout<<"\"wb\":"<<wb<<",";
    cout<<"\"er\":"<<er<<",";
    cout<<"\"eg\":"<<eg<<",";
    cout<<"\"eb\":"<<eb;
    cout<<"}";

    if(tofile)
    {
        cout.rdbuf(x);
        out.close();
    }







    (*freeAIFunction)(pAI);
    dlclose(ai_handle);

    return 0;
}
