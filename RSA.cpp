#include <iostream>
#include <regex>
#include "bignum.h"
using namespace std;

int ParseCommandLine(int argc, char** argv, string& p, string& q, string& e, string& msg )
{
    int result = 0;
    if (argc > 1)
    {
        for (int i = 1; i < argc; ++i)
        {
            string str = argv[i];
            if (str.find("p=") != string::npos)
            {
                std::regex rx("^p=(\\d+)$");
                std::cmatch match;
                regex_search(argv[i], match, rx);
                if (match.size() == 2)
                {
                    p = match[1];
                    BigNum bigNum =  StringToArray(p);
                    if(!IsPrime(bigNum))
                    {
                        printf("\n P value provided %s is not prime", p.c_str());
                        return -1;
                    }
                }
                else
                {
                    return -1;
                }
            }
            else if (str.find("q=") != string::npos)
            {
                std::regex rx("^q=(\\d+)$");
                std::cmatch match;
                regex_search(argv[i], match, rx);
                if (match.size() == 2)
                {
                    q = match[1];
                    BigNum bigNum =  StringToArray(q);
                    if(!IsPrime(bigNum))
                    {
                        printf("\n Q value provided %s is not prime", q.c_str());
                        return -1;
                    }
                }
                else
                {
                    return -1;
                }
            }
            else if (str.find("m=") != string::npos)
            {
                std::regex rx("^m=(\\d+)$");
                std::cmatch match;
                regex_search(argv[i], match, rx);
                if (match.size() == 2)
                {
                    msg = match[1];
                }
                else
                {
                    return -1;
                }
            }
            else if (str.find("e=") != string::npos)
            {
                std::regex rx("^e=(\\d+)$");
                std::cmatch match;
                regex_search(argv[i], match, rx);
                if (match.size() == 2)
                {
                    e = match[1];
                }
                else
                {
                    return -1;
                }
            }
        }
    }

    return 0;
}

void RSA(string p, string q, string e, string msg)
{
    printf("\np value considered : %s", p.c_str());
    printf("\nq value considered : %s", q.c_str());
    printf("\ne value considered : %s", e.c_str());
    printf("\nmessage provided   : %s\n\n", msg.c_str());

    BigNum pVal, qVal, eVal, dVal, nVal, phiVal, pMin1, qMin1, One;
    clock_t t;

    DivResult DR;
    One.Num[0] = 1;
    eVal.Num[0] = 2;

    pVal = StringToArray(p);
    qVal = StringToArray(q);
    nVal = Mul(pVal, qVal);
    pMin1 = Sub(pVal, One);
    qMin1 = Sub(qVal, One);
    phiVal = Mul(pMin1, qMin1);
    eVal = StringToArray(e);
    dVal = Inverse(eVal, phiVal);

    printf("\nN Value                   : %s", value_number(nVal).c_str());
    printf("\nPhi Value                 : %s", value_number(phiVal).c_str());
    printf("\nPublic key e              : %s", value_number(eVal).c_str());
    printf("\nPrivate key d             : %s", value_number(dVal).c_str());
    printf("\nValue to be encrypted     : %s", msg.c_str());

    printf("\n\n\n******************RSA Encryption*******************\n");
    BigNum msgVal = StringToArray(msg);
    t = clock();
    BigNum outVal = PwrMod(msgVal, eVal, nVal);
    t = clock() - t;
    string cipherText = value_number(outVal);
    double timeTakenRSAEncrypt = ((double)t) / CLOCKS_PER_SEC;
    printf("\nCipher Text               : %s", cipherText.c_str());


    printf("\n\n******************RSA Decryption*******************\n");
    BigNum cipherTextVal = StringToArray(cipherText);
    t = clock();
    outVal = PwrMod(cipherTextVal, dVal, nVal);
    t = clock() - t;
    string cipherTextStr= value_number(outVal);
    printf("\nDecrypted Text            : %s", cipherTextStr.c_str());
    double timeTakenRSADecrypt = ((double)t) / CLOCKS_PER_SEC; // in seconds


    printf("\n\n******************RSA Decryption With CRT*******************\n");
    BigNum dP,dQ,m1,m2,qInv, m, q1, val, crtMsgVal;
    t = clock();
    dP = PwrMod(dVal, One, pMin1);
    dQ= PwrMod(dVal, One, qMin1);
    m1 = PwrMod(cipherTextVal, dP, pVal);
    m2= PwrMod(cipherTextVal, dQ, qVal);
    qInv= Inverse(qVal, pVal);
    m = Sub(m1, m2);
    q1 = Mul(qInv, m);
    DR = DivLarge(q1, pVal);
    val = Mul(DR.Remainder, qVal);

    crtMsgVal = Add(m2, val);
    t = clock() - t;
    string decrpt = value_number(crtMsgVal);

    printf("\nDecrypted value with CRT  :  %s", decrpt.c_str());

    double timeTakenCRTDecrypt = ((double)t) / CLOCKS_PER_SEC; // in seconds


    printf("\n\n\n\nTime taken for RSA encryption          - %f seconds", timeTakenRSAEncrypt);
    printf("\nTime taken for RSA decryption          - %f seconds", timeTakenRSADecrypt);
    printf("\nTime taken for RSA decryption with CRT - %f seconds", timeTakenCRTDecrypt);
}

int main(int argc, char *argv[] )
{
    string p, q, e, pt;
    p = "75164025890726496019173371238111072907";
    q = "46134478684436156789454923032401055711";
    e = "65537";
    pt = "12345676564334";

        // Parse command line
    int result = ParseCommandLine(argc, argv, p,q,e,pt);
    if(result != 0)
    {
        printf("\nSomething wrong with the command line input... Exiting...");
        exit(1);
    }

    RSA(p,q,e,pt);
    return 0;
}