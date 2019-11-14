#include <iostream>
using namespace std;

int main() {

    Cliente* cliente = new Cliente();

    LoggerMenu* loggerMenu = new LoggerMenu(cliente);

    if (loggerMenu->open()){

        cout<<"Felicidades, estas jugando!"<<endl;
    }
    return 0;
}