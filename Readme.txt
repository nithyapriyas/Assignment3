Name   - Nithyapriya S
RollNo - CS21M510
mail   - nithyapriya1997@gmail.com

To generate binary - g++ -std=c++11 bignum.cpp RSA.cpp -o RSA

********************************************Usage****************************************
Command:           RSA.exe p=<p value> q=<q value> e=<e value> m=<message to be encrypted>

Sample - RSA.exe p=46134478684436156789454923032401055711 q=75164025890726496019173371238111072907 e=65537 m=243454654765675


******************************************************************Output******************************************************************

RSA.exe p=46134478684436156789454923032401055711 q=75164025890726496019173371238111072907 e=65537 m=2434546547656758767

p value considered : 46134478684436156789454923032401055711
q value considered : 75164025890726496019173371238111072907
e value considered : 65537
message provided   : 2434546547656758767


N Value                   : 3467653150292128944085570730651678681582886897717273344896793080665689721877
Phi Value                 : 3467653150292128944085570730651678681461588393142110692088164786395177593260
Public key e              : 65537
Private key d             : 3343575962788351804853065987325341093411671174137300438751168182582114873633
Value to be encrypted     : 2434546547656758767


******************RSA Encryption*******************

Cipher Text               : 3230810209957054296656549485459518033585083561812268225511189868164743539220

******************RSA Decryption*******************

Decrypted Text            : 2434546547656758767

******************RSA Decryption With CRT*******************

Decrypted value with CRT  :  2434546547656758767



Time taken for RSA encryption          - 0.109000 seconds
Time taken for RSA decryption          - 2.156000 seconds
Time taken for RSA decryption with CRT - 1.547000 seconds