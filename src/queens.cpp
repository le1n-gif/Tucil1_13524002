#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <cstdlib>
#include <limits>
#include <set>

using namespace std;

int N = 0;
const int maxN = 26;
char board[maxN][maxN];
int queens[maxN];
bool solution = false;

bool sizeValidation(){
    set<char> uniqueChars;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            uniqueChars.insert(board[i][j]);
        }
    }
    
    if ((int)uniqueChars.size() != N){
        cout << "Jumlah karakter/warna pada papan tidak sesuai dengan ukuran papan." << endl;   
        return false;
    }
    return true;
}

void printBoard(ostream& out){
    for (int i = 0; i <= N-1; i++){
        for (int j = 0; j <= N-1; j++){
            if (queens[i] == j){
                out << "# ";
            } else {
                out << board[i][j] << " ";
            }
        }
        out << endl;
    }   
}

void loadBoard(){
    N = 0;
    ifstream file;
    string filename;
    bool validFilename = false;
    
    while (!validFilename){
        cout << "Masukkan nama file input atau path (misal case.txt atau testcase/tc.txt): ";
        getline(cin, filename);

        if (!filename.empty() && filename.front() == '"') filename.erase(0, 1);
        if (!filename.empty() && filename.back() == '"') filename.pop_back();

        if (filename.empty()){
            cout << "Nama file tidak boleh kosong." << endl;
            continue;
        }

        string txtExt = ".txt";
        if (filename.size() < txtExt.size() || 
            filename.substr(filename.size() - txtExt.size()) != txtExt){
            cout << "Format file tidak valid. Hanya file .txt yang diterima." << endl;
            continue;
        }

        validFilename = true;
    }

    file.open(filename);
    while (!file.is_open()){
        cout << "File tidak ditemukan. Masukkan nama file yang benar: ";
        getline(cin, filename);
        if (!filename.empty() && filename.front() == '"') filename.erase(0, 1);
        if (!filename.empty() && filename.back() == '"') filename.pop_back();
        file.clear();
        file.open(filename);
    }
    cout << "File " << filename << " berhasil dibuka." << endl;

    string line;
    int row = 0;
    
    while (getline(file,line)){
        while (!line.empty() && isspace((unsigned char)line.back())){
            line.pop_back();
        }
        if (!line.empty() && line[line.length()-1] == '\r'){
            line.erase(line.length()-1);
        }
        if (line.empty()){
            continue;   
        }
        if (N == 0){
            N = line.length();
            if (N > maxN){
                cout << "Ukuran papan melebihi batas maksimal." << endl;
                exit(1);
            }  
        }
        if ((int)line.length()!=N){
            cout << "Format input tidak valid." << endl;
            exit(1);
        }
        for (int col = 0; col < N; col++){
            char currentChar = line[col];

            if (currentChar == ' ' || currentChar == '\t'){
                cout << "Error: Format papan cacat!" << endl;
                exit(1);
            }

            
            if (currentChar < 'A' || currentChar > 'Z'){
                cout << "Error: Karakter tidak valid ditemukan!" << endl;
                exit(1);
            }

            board[row][col] = currentChar;
        }
        row++;
    }
    file.close();

    if (row == 0){
        cout << "File kosong!" << endl;
        exit(1);
    }
    if (row != N){
        cout << "Board tidak berbentuk persegi (n x n)!" << endl;
        exit(1);
    }
    if (!sizeValidation()){
        exit(1);
    }
    cout << "Board " << N << "x" << N << " berhasil dimuat." << endl;
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

bool isValid(int row, int col){
    for (int otherRow = 0; otherRow < N; otherRow++){
        if (otherRow == row){
            continue;
        }
        int otherCol = queens[otherRow];
        if (otherCol == col){
            return false;
        }
        int rowDiff = row - otherRow;
        int colDiff = col - otherCol;

        if (rowDiff < 0){
            rowDiff = -1 * rowDiff;
        }
        if (colDiff < 0){
            colDiff = -1 *colDiff;
        }
        if (rowDiff<=1 && colDiff <=1){
            return false;
        }
        if (board[row][col] == board[otherRow][otherCol]){
            return false;
        }
    }
    return true;
}

void saveSolution(long long iteration,double duration){
    string response;
    cout << "Apakah Anda ingin menyimpan solusi? (y/n): ";
    cin >> response;
    if (response == "y" || response == "Y"){
        string filename;
        bool validFilename = false;
        
        while (!validFilename){
            cout << "Masukkan nama file/path untuk menyimpan file output (misal hasil.txt): ";
            cin >> filename;

            if (filename.empty()){
                cout << "Nama file tidak boleh kosong." << endl;
                continue;
            }

            string txtExt = ".txt";
            if (filename.size() < txtExt.size() || 
                filename.substr(filename.size() - txtExt.size()) != txtExt){
                cout << "Format file tidak valid. Hanya file .txt yang diterima." << endl;
                continue;
            }

            validFilename = true;
        }

        ofstream file(filename);

        if (!file.is_open()){
            cout << "Gagal membuka file untuk menyimpan solusi." << endl;
            return;
        }else{
            printBoard(file);
            file << "\nIterasi: " << iteration << endl;
            file << "Waktu eksekusi: " << duration << " ms" << endl;    
            file.close();
            cout << "Solusi berhasil disimpan ke " << filename << endl;
        }
    } 
}

int main() {
    loadBoard();
    for (int i = 0; i < N; i++){
        queens[i] = 0;
    }
    long long iterations = 0;
    bool found = false;

    cout << "Mencari solusi..." << endl;
    auto start = chrono::high_resolution_clock::now();

    while (true){
        iterations++;

        if (iterations % 1000000==0){
            clearScreen();
            cout << "Iterasi ke-" << iterations << endl;
            printBoard(cout);
        }
        bool valid = true;
        for (int i=0; i < N; i++){
            if(isValid(i, queens[i]) == false){
                valid = false;
                break;
            }
        }

        if (valid){
            found = true;
            break;
        }

        int row = N-1;
        while (row>=0){
            queens[row]++;
            if (queens[row] < N){
                break;
            }else{
                queens[row] = 0;
                  row--;
            }
        }
        if (row < 0){
            break;
        }
    }
    
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;
    
    cout << "\nIterasi: " << iterations << endl;
    cout << "Waktu eksekusi: " << duration.count() << " ms" << endl;
    
    cout << "HASIL AKHIR:" << endl;
    if (found){
        printBoard(cout);
        cout << "\nSolusi ditemukan!" << endl;
        saveSolution(iterations, duration.count());
    } else {
        cout << "\nTidak ada solusi yang ditemukan." << endl;
    }
}


