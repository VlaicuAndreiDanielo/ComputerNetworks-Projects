#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <set>

using namespace std;

string generateRandomIP(set<string>& usedIPs) {
    string ip;
    do {
        ostringstream oss;
        oss << rand() % 256 << "." << rand() % 256 << "." << rand() % 256 << "." << rand() % 256;
        ip = oss.str();
    } while (usedIPs.find(ip) != usedIPs.end());
    usedIPs.insert(ip);
    return ip;
}

class Computer {
public:
    string id;
    string ip;
    string buffer;
    Computer(string id, string ip) : id(id), ip(ip), buffer("") {}
};

struct Token {
    string srcIP;    
    string destIP;  
    string message;  
    bool isFree;     
    bool delivered;  
};

void printNetworkState(const vector<Computer>& computers) {
    for (const auto& comp : computers) {
        cout << comp.id << " (" << comp.ip << ") -> "
            << (comp.buffer.empty() ? "null" : comp.buffer) << "\n";
    }
    cout << "\n";
}

int main() {
    srand(time(0));

    const int n = 10;
    vector<Computer> computers;
    set<string> usedIPs;

    for (int i = 0; i < n; i++) {
        string id = "C" + to_string(i);
        string ip = generateRandomIP(usedIPs);
        computers.push_back(Computer(id, ip));
    }

    int opt;
    cout << "Alegeti sensul de circulatie:\n";
    cout << "1 - Sensul acelor de ceas (clockwise: C0, C1, ... C9, apoi C0)\n";
    cout << "2 - Sensul opus al acelor de ceas (counterclockwise: C0, C9, ... C1, apoi C0)\n";
    cout << "Optiune: ";
    cin >> opt;
    int direction = (opt == 2) ? -1 : 1;

    cout << "Introduceti mesajul de test:\n";
    string message;
    cin >> message;

    Token token;
    token.isFree = true;
    token.delivered = true;
    int current = -1; 

    for (int step = 1; step <= 10; step++) {

        for (int i = 0; i < n; i++) {
            computers[i].buffer = "";
        }
        cout << "\nPasul " << step << ":\n";
        printNetworkState(computers);


        int newSrc = rand() % n;
        int dest = rand() % n;
        while (dest == newSrc) {
            dest = rand() % n;
        }
        cout << "Noua sursa: " << computers[newSrc].id
            << " Destinatia: " << computers[dest].id << "\n\n";


        if (step == 1) {
            token.srcIP = computers[newSrc].ip;
            current = newSrc;
        }

        else if (computers[newSrc].ip != token.srcIP) {
            cout << "Token-ul se muta de la " << token.srcIP
                << " la " << computers[newSrc].ip << "\n\n";
            while (computers[current].ip != computers[newSrc].ip) {

                for (int i = 0; i < n; i++) {
                    computers[i].buffer = "";
                }
                computers[current].buffer = token.message.empty() ? "Token" : token.message;
                printNetworkState(computers);
                cout << computers[current].id << ": Muta token-ul catre noua sursa\n\n";
                current = (current + direction + n) % n;
            }

            token.srcIP = computers[newSrc].ip;
        }


        token.destIP = computers[dest].ip;
        token.message = message;
        token.isFree = false;
        token.delivered = false;

        int state = 0;
        while (!token.isFree || !token.delivered) {

            for (int i = 0; i < n; i++) {
                computers[i].buffer = "";
            }
            computers[current].buffer = token.message;
            printNetworkState(computers);

            if (state == 0) {
                if (current == dest) {
                    cout << computers[current].id
                        << ": Am ajuns la destinatie (delivered == true)\n\n";
                    token.delivered = true;
                    state = 1;
                }
                else {
                    cout << computers[current].id << ": Muta token-ul spre destinatie\n\n";
                }
            }
            else if (state == 1) {
                cout << computers[current].id << ": Muta token-ul din destinatie spre sursa\n\n";
                if (current == newSrc) {
                    token.isFree = true;
                    cout << computers[current].id
                        << ": Am ajuns inapoi la sursa (isFree == true)\n\n";
                    break;
                }
                state = 2;
            }
            else if (state == 2) {
                if (current == newSrc) {
                    token.isFree = true;
                    cout << computers[current].id
                        << ": Am ajuns inapoi la sursa (isFree == true)\n\n";
                    break;
                }
                else {
                    cout << computers[current].id << ": Muta token-ul spre sursa\n\n";
                }
            }
            current = (current + direction + n) % n;
        }

        cout << "------------------------------------\n";
    }

    return 0;
}
