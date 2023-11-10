    #include <iostream>
    #include <fstream>
    #include <windows.h>
    #include <cmath>
    #include <string>
    #include <queue>
    #include <vector>
    #include <algorithm>

    #define RESET "\033[97m"
    #define RED "\033[31m"
    #define GREEN "\033[32m"
    #define YELLOW "\033[33m"
    #define BLUE "\033[34m"

    using namespace std;

    // Struct node untuk menyimpan data playlist
    struct Node
    {
        string judul;
        string penyanyi;
        string genre;
        Node *next; // pointer ke node selanjutnya
    };

    // Class untuk menyimpan data user
    class User
    {
    public:
        string username;
        string password;
        string email;
        Node *head; // pointer ke node pertama playlist user
        User(string u, string p, string e)
        {
            username = u;
            password = p;
            email = e;
            head = NULL;
        }
    };

    // Fungsi untuk menambahkan node baru di akhir linked list
    void tambahNode(Node **head, string judul, string penyanyi, string genre)
    {
        Node *newNode = new Node(); // buat node baru
        newNode->judul = judul;
        newNode->penyanyi = penyanyi;
        newNode->genre = genre;
        newNode->next = NULL;
        if (*head == NULL)
        {
            *head = newNode;
        }
        else
        {
            Node *temp = *head; // buat pointer sementara
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    // Fungsi untuk menampilkan data semua node dari linked list
    void tampilNode(Node *head)
    {
        if (head == NULL)
        {
            system("cls");
            cout << RED << "Playlist kosong, tidak ada yang bisa ditampilkan.\n";
            Sleep(1000);
            return;
        }

        Node *temp = head;
        int i = 1; // variabel untuk menyimpan nomor urut
        while (temp != NULL)
        {
            cout << RED << i << ". " << temp->judul << " - " << temp->penyanyi << " (" << temp->genre << ")\n";
            temp = temp->next;
            i++;
        }
    }

    // Fungsi untuk menfyimpan data semua node dari linked list ke file txt
    void simpanNode(Node *head, string username)
    {
        ofstream file;
        file.open(username + ".txt"); // buka file dengan nama username.txt
        Node *temp = head;
        while (temp != NULL)
        {
            file << temp->judul << "\n";
            file << temp->penyanyi << "\n";
            file << temp->genre << "\n";
            temp = temp->next;
        }
        file.close(); // tutup file
    }

    // Fungsi untuk membaca data semua node dari file txt
    void bacaNode(Node **head, string username)
    {
        ifstream file;
        file.open(username + ".txt"); // buka file dengan nama username.txt
        if (file.is_open())
        {
            string judul, penyanyi, genre;
            while (getline(file, judul))
            {
                getline(file, penyanyi);
                getline(file, genre);
                tambahNode(head, judul, penyanyi, genre);
            }
            file.close(); // tutup file
        }
    }

    // Fungi untuk menukar node
    void tukarNode(Node **head, int pos1, int pos2)
    {
        if (pos1 == pos2)
        {
            return; // Tidak ada yang perlu diubah jika posisi sama
        }

        Node *node1 = *head;
        Node *node2 = *head;
        Node *prev1 = NULL, *prev2 = NULL;

        // Cari node ke-pos1 dan node ke-pos2 beserta node sebelumnya
        int currentPos = 1;
        while (node1 != NULL && currentPos != pos1)
        {
            prev1 = node1;
            node1 = node1->next;
            currentPos++;
        }

        currentPos = 1;
        while (node2 != NULL && currentPos != pos2)
        {
            prev2 = node2;
            node2 = node2->next;
            currentPos++;
        }

        // Jika pos1 atau pos2 melebihi panjang playlist, keluar dari fungsi
        if (node1 == NULL || node2 == NULL)
        {
            return;
        }

        // Perbarui node sebelumnya (prev1 dan prev2) untuk menunjuk ke node yang akan ditukar
        if (prev1 != NULL)
        {
            prev1->next = node2;
        }
        else
        {
            *head = node2;
        }

        if (prev2 != NULL)
        {
            prev2->next = node1;
        }
        else
        {
            *head = node1;
        }

        // Tukar node selanjutnya
        Node *temp = node1->next;
        node1->next = node2->next;
        node2->next = temp;
    }

    int hitungNode(Node *head)
    {
        int count = 0;
        Node *current = head;

        while (current != nullptr)
        {
            count++;
            current = current->next;
        }

        return count;
    }

    // Fungsi untuk merubah urutan playlist user
    void ubahUrutanPlaylist(Node **head)
    {
        system("cls");
        cout << BLUE   << "=====================================\n";
        cout << YELLOW << "          Playlist saat ini\n";
        cout << BLUE   << "=====================================\n";
 
        // Menambahkan error handling jika tidak ada playlist
        if (*head == nullptr)
        {
            cout << RED << "Playlist kosong. Tidak dapat mengubah urutan.\n";
            system("pause");
            return;
        }

        tampilNode(*head);
        cout << BLUE << "=====================================\n";

        int pos1, pos2;
        cout << YELLOW << "Masukkan posisi lagu pertama yang ingin ditukar: ";
        cin >> pos1;

        // Menambahkan error handling jika posisi lagu pertama tidak valid
        if (pos1 < 1 || pos1 > hitungNode(*head))
        {
            cout << RED << "Posisi lagu pertama tidak valid.\n";
            Sleep(1000);
            return;
        }

        cout << YELLOW << "Masukkan posisi lagu kedua yang ingin ditukar: ";
        cin >> pos2;

        // Menambahkan error handling jika posisi lagu kedua tidak valid
        if (pos2 < 1 || pos2 > hitungNode(*head))
        {
            cout << RED << "Posisi lagu kedua tidak valid.\n";
            Sleep(1000);
            return;
        }

        // Memanggil fungsi untuk menukar node
        tukarNode(head, pos1, pos2);

        system("cls");
        cout << GREEN << "Urutan playlist berhasil diubah.\n";
        Sleep(1000);
    }

    // Fungsi untuk mengecek apakah username sudah ada di file txt atau belum
    bool cekUsername(string username)
    {
        ifstream file;
        file.open("user.txt");
        if (file.is_open())
        {
            string u, p, e;
            while (getline(file, u))
            {
                getline(file, p);
                getline(file, e);
                if (u == username)
                {
                    file.close();
                    return true; // kembalikan nilai true
                }
            }
            file.close();
        }
        return false; // kembalikan nilai false
    }

    // Fungsi untuk mengecek apakah username dan password cocok dengan yang ada di file txt
    bool cekLogin(string username, string password)
    {
        ifstream file;
        file.open("user.txt");
        if (file.is_open())
        {
            string u, p, e;
            while (getline(file, u))
            {
                getline(file, p);
                getline(file, e);
                if (u == username && p == password)
                {
                    file.close();
                    return true;
                }
            }
            file.close();
        }
        return false;
    }

    // Fungsi untuk membuat user baru dan menyimpannya ke file txt
    void buatUser(string username, string password, string email)
    {
        ofstream file;
        file.open("user.txt", ios::app); // buka file user.txt dengan mode append
        file << username << "\n";
        file << password << "\n";
        file << email << "\n";
        file.close();
    }

    void lihatPlaylistUser(Node *head, string username)
    {
        system("cls");
        cout << GREEN << "=====================================\n";
        cout << BLUE  << "            Playlist milik " << username << ":\n";
        cout << GREEN << "=====================================\n";
        tampilNode(head);
        cout << GREEN << "=====================================\n";
    }

    // Fungsi untuk menghapus playlist
    void hapusLaguDariPlaylist(Node **head, int posisi)
    {
        if (*head == nullptr)
        {
            system("cls");
            cout << RED << "Playlist kosong, tidak ada yang bisa dihapus.\n";
            Sleep(1000);
            return;
        }

        Node *hapus = *head;
        Node *sebelumHapus = nullptr;
        int nomor = 1;

        // Mencari node yang akan dihapus berdasarkan posisi
        while (hapus != nullptr && nomor != posisi)
        {
            sebelumHapus = hapus;
            hapus = hapus->next;
            nomor++;
        }

        // Jika nomor melebihi panjang playlist, keluar dari fungsi
        if (hapus == nullptr)
        {
            return;
        }

        // Menghapus node dari playlist
        if (sebelumHapus != nullptr)
        {
            sebelumHapus->next = hapus->next;
        }
        else
        {
            *head = hapus->next;
        }

        delete hapus;

        system("cls");
        cout << GREEN << "Lagu berhasil dihapus dari playlist.\n";
        Sleep(1000);
    }

    // Fungsi untuk menampilkan menu utama
    void tampilMenu()
    {
        system("cls");
        cout << BLUE << "========================================\n";
        cout << RESET<< "Selamat datang di program playlist musik\n";
        cout << BLUE << "========================================\n";
        cout << RESET << "[1] Login\n";
        cout << "[2] Register\n";
        cout << "[3] Keluar\n";
        cout << BLUE << "========================================\n";
        cout << RESET<< "        Masukkan pilihan Anda: ";
    }

    // Fungsi untuk menampilkan menu login
    void tampilLogin()
    {
        system("cls");
        cout << BLUE << "=====================================\n";
        cout << RESET << "           Silahkan login\n";
        cout << BLUE << "=====================================\n";
        cout << RESET << "Masukkan username dan password Anda\n";
    }

    // Fungsi untuk menampilkan menu register
    void tampilRegister()
    {
        system("cls");
        cout << BLUE << "=====================================\n";
        cout << RESET << "           Silahkan register\n";
        cout << BLUE << "=====================================\n";
        cout << RESET << "Masukkan username, password, dan email Anda\n"; // tampilkan pesan
    }

    // Fungsi untuk menampilkan menu admin
    void tampilAdmin()
    {
        system("cls");
        cout << GREEN << "=====================================\n";
        cout << BLUE << "              Menu admin\n";
        cout << GREEN << "=====================================\n";
        cout << YELLOW << "[1] Tambah Lagu\n";
        cout << "[2] Melihat List Lagu\n";
        cout << "[3] Mengubah Lagu\n";
        cout << "[4] Menghapus Lagu\n";
        cout << "[5] Mencari User & Tampilkan Playlist\n";
        cout << "[6] Logout\n";
        cout << GREEN << "=====================================\n";
        cout << BLUE  << "        Masukkan pilihan Anda: ";
    }

    // Fungsi untuk menampilkan menu user
    void tampilUser()
    {
        system("cls");
        cout << BLUE   << "=====================================\n";
        cout << YELLOW <<"               Menu user\n";
        cout << BLUE   << "=====================================\n";
        cout << RED << "[1] Membuat playlist\n";
        cout << "[2] Melihat playlist\n";
        cout << "[3] Mengubah playlist\n";
        cout << "[4] Menghapus playlist\n";
        cout << "[5] Mainkan playlist\n";
        cout << "[6] Logout\n";
        cout << BLUE   << "=====================================\n";
        cout << YELLOW << "        Masukkan pilihan Anda: ";
    }

    // Fungsi untu menambah Lagu Admin
    void tambahLaguAdmin()
    {
        system("cls");
        string judul, penyanyi, genre;
        cout << "Masukkan judul lagu: ";
        getline(cin, judul);
        cout << "Masukkan penyanyi lagu: ";
        getline(cin, penyanyi);
        cout << "Masukkan genre lagu: ";
        getline(cin, genre);

        ofstream file("daftar_lagu.txt", ios::app);

        if (file.is_open())
        {
            file << judul << "\n";
            file << penyanyi << "\n";
            file << genre << "\n";
            file.close();
            system("cls");
            cout << GREEN << "Lagu berhasil ditambahkan ke daftar lagu.\n";
            Sleep(1000);
        }
        else
        {
            cout << "Gagal membuka file daftar lagu.\n";
            Sleep(1000);
        }
    }

    // Fungsi pertukaran untuk vektor berisi informasi lagu
    void swap(vector<string> &a, vector<string> &b)
    {
        vector<string> temp = a;
        a = b;
        b = temp;
    }

    // Fungsi quicksort untuk vektor berisi informasi lagu
    void quicksort(vector<vector<string>> &arr, int low, int high)
    {
        if (low < high)
        {
            // Pilih pivot (biasanya diambil dari tengah array)
            vector<string> pivot = arr[(low + high) / 2];

            // Inisialisasi indeks dari kedua sisi array
            int i = low;
            int j = high;

            // Partisi array
            while (i <= j)
            {
                // Temukan elemen yang lebih kecil dari pivot
                while (arr[i][0] < pivot[0])
                    i++;

                // Temukan elemen yang lebih besar dari pivot
                while (arr[j][0] > pivot[0])
                    j--;

                // Jika elemen yang lebih kecil dan lebih besar ditemukan, tukar
                if (i <= j)
                {
                    swap(arr[i], arr[j]);
                    i++;
                    j--;
                }
            }

            // Panggil rekursif untuk subarray sebelum dan setelah partisi
            quicksort(arr, low, j);
            quicksort(arr, i, high);
        }
    }

    // Fungsi untuk menyimpan vektor ke file teks
    void simpanKeFile(const vector<vector<string>> &arr, const string &filename)
    {
        ofstream file(filename);

        if (file.is_open())
        {
            for (const vector<string> &lagu : arr)
            {
                file << lagu[0] << "\n";
                file << lagu[1] << "\n";
                file << lagu[2] << "\n";
            }

            file.close();
        }
        else
        {
            cout << "Gagal membuka file " << filename << endl;
        }
    }

    // Fungsi untuk melihat daftar lagu
    void lihatLaguAdmin()
    {
        system("cls");
        cout << GREEN << "=====================================\n";
        cout << BLUE  << "         Daftar Lagu Admin\n";
        cout << GREEN << "=====================================\n";
        ifstream file("daftar_lagu.txt");

        if (file.is_open())
        {
            vector<vector<string>> laguList; // Vector untuk menyimpan informasi lagu

            string judul, penyanyi, genre;

            while (getline(file, judul) && getline(file, penyanyi) && getline(file, genre))
            {
                // Tambahkan baris lagu ke vector
                laguList.push_back({judul, penyanyi, genre});
            }

            // Panggil quicksort untuk mengurutkan vector
            quicksort(laguList, 0, laguList.size() - 1);

            int nomor = 1;

            // Tampilkan daftar lagu yang sudah diurutkan
            for (const vector<string> &lagu : laguList)
            {
                cout << YELLOW << nomor << ". " << lagu[0] << " - " << lagu[1] << " (" << lagu[2] << ")\n";
                nomor++;
            }

            file.close();

            // Simpan hasil sorting ke file teks yang sudah ada
            simpanKeFile(laguList, "daftar_lagu.txt");

            cout << GREEN << "=====================================\n";
            system("pause");
        }
        else
        {
            cout << "Gagal membuka file daftar lagu.\n";
            Sleep(1000);
        }
    }

    // Fungsi untuk mengubah lagu dalam daftar lagu admin
    void ubahLaguAdmin()
    {
        system("cls");
        cout << GREEN << "=====================================\n";
        cout << BLUE  << "          Daftar Lagu Admin\n";
        cout << GREEN << "=====================================\n";
        ifstream file("daftar_lagu.txt");
        ofstream temporaryFile("temporary_daftar_lagu.txt");

        if (file.is_open() && temporaryFile.is_open())
        {
            string judul, penyanyi, genre;
            int nomor = 1;

            // Tampilkan daftar lagu admin
            while (getline(file, judul) && getline(file, penyanyi) && getline(file, genre))
            {
                cout << YELLOW << nomor << ". " << judul << " - " << penyanyi << " (" << genre << ")\n";
                nomor++;
            }

            file.close();

            // Pilih lagu yang ingin diubah
            int nomorLagu;
            cout << GREEN << "=====================================\n";
            cout << BLUE << "Masukkan nomor lagu yang ingin diubah (0 untuk batal): ";
            cin >> nomorLagu;
            cin.ignore();

            if (nomorLagu > 0 && nomorLagu < nomor)
            {
                file.open("daftar_lagu.txt"); // Buka kembali file daftar lagu
                nomor = 1;

                while (getline(file, judul) && getline(file, penyanyi) && getline(file, genre))
                {
                    if (nomor == nomorLagu)
                    {
                        string judulBaru, penyanyiBaru, genreBaru;

                        // Masukkan data baru
                        cout << "Masukkan judul lagu baru: ";
                        getline(cin, judulBaru);
                        cout << "Masukkan penyanyi lagu baru: ";
                        getline(cin, penyanyiBaru);
                        cout << "Masukkan genre lagu baru: ";
                        getline(cin, genreBaru);

                        // Tulis data baru ke temporary file
                        temporaryFile << judulBaru << "\n";
                        temporaryFile << penyanyiBaru << "\n";
                        temporaryFile << genreBaru << "\n";

                        system("cls");
                        cout << GREEN << "Lagu berhasil diubah.\n";
                        Sleep(1000);
                    }
                    else
                    {
                        // Salin data lagu yang tidak diubah ke temporary file
                        temporaryFile << judul << "\n";
                        temporaryFile << penyanyi << "\n";
                        temporaryFile << genre << "\n";
                    }

                    nomor++;
                }

                file.close();
                temporaryFile.close();

                // Ganti nama temporary file menjadi file utama
                remove("daftar_lagu.txt");
                rename("temporary_daftar_lagu.txt", "daftar_lagu.txt");
            }
            else if (nomorLagu != 0)
            {
                cout << RED << "Nomor lagu tidak valid.\n";
            }
        }
        else
        {
            cout << "Gagal membuka file daftar lagu.\n";
        }
    }

    // Fungsi untuk menghapus lagu dari daftar lagu admin
    void hapusLaguAdmin()
    {
        system("cls");
        cout << GREEN << "=====================================\n";
        cout << BLUE  << "         Daftar Lagu Admin\n";
        cout << GREEN << "=====================================\n";
        ifstream file("daftar_lagu.txt");
        ofstream temporaryFile("temporary_daftar_lagu.txt");

        if (file.is_open() && temporaryFile.is_open())
        {
            string judul, penyanyi, genre;
            int nomor = 1;

            // Tampilkan daftar lagu admin
            while (getline(file, judul) && getline(file, penyanyi) && getline(file, genre))
            {
                cout << YELLOW << nomor << ". " << judul << " - " << penyanyi << " (" << genre << ")\n";
                nomor++;
            }

            file.close();

            // Pilih lagu yang ingin dihapus
            int nomorLagu;
            cout << GREEN << "=====================================\n";
            cout << BLUE << "Masukkan nomor lagu yang ingin dihapus (0 untuk batal): ";
            cin >> nomorLagu;
            cin.ignore();

            if (nomorLagu > 0 && nomorLagu < nomor)
            {
                file.open("daftar_lagu.txt"); // Buka kembali file daftar lagu
                nomor = 1;

                while (getline(file, judul) && getline(file, penyanyi) && getline(file, genre))
                {
                    if (nomor != nomorLagu)
                    {
                        // Salin data lagu yang tidak dihapus ke temporary file
                        temporaryFile << judul << "\n";
                        temporaryFile << penyanyi << "\n";
                        temporaryFile << genre << "\n";
                    }
                    else
                    {
                        system("cls");
                        cout << GREEN << "Lagu berhasil dihapus.\n";
                        Sleep(1000);
                    }

                    nomor++;
                }

                file.close();
                temporaryFile.close();

                // Ganti nama temporary file menjadi file utama
                remove("daftar_lagu.txt");
                rename("temporary_daftar_lagu.txt", "daftar_lagu.txt");
            }
            else if (nomorLagu != 0)
            {
                cout << RED << "Nomor lagu tidak valid.\n";
            }
        }
        else
        {
            cout << "Gagal membuka file daftar lagu.\n";
        }
    }

    // Fungsi untuk melakukan preprocessing karakter terhadap pola
    void preProcessPattern(const string &pattern, vector<int> &badChar)
    {
        int m = pattern.size();

        // Inisialisasi tabel bad character
        badChar.assign(256, -1);

        // Mengisi indeks karakter terakhir dari pola
        for (int i = 0; i < m; i++)
        {
            badChar[static_cast<int>(pattern[i])] = i;
        }
    }

    // Fungsi untuk mencari pola menggunakan algoritma Boyer-Moore
    vector<int> boyerMooreSearch(const string &text, const string &pattern)
    {
        vector<int> positions;
        int m = pattern.size();
        int n = text.size();
        vector<int> badChar;

        // Preprocessing pola
        preProcessPattern(pattern, badChar);

        int s = 0;
        while (s <= n - m)
        {
            int j = m - 1;
            while (j >= 0 && pattern[j] == text[s + j])
            {
                j--;
            }

            if (j < 0)
            {
                positions.push_back(s);
                s += (s + m < n) ? m - badChar[text[s + m]] : 1;
            }
            else
            {
                s += max(1, j - badChar[text[s + j]]);
            }
        }

        return positions;
    }

    // Fungsi untuk mencari user dan melihat playlistnya
    void cariUser()
    {
        system("cls");
        string username;
        cout << BLUE << "Masukkan username user yang ingin dicari (0 untuk batal): ";
        getline(cin, username);

        ifstream file("user.txt");
        if (file.is_open())
        {
            string u, p, e;
            vector<int> positions;

            // Mencari username menggunakan algoritma Boyer-Moore
            while (getline(file, u))
            {
                positions = boyerMooreSearch(u, username);
                if (!positions.empty())
                {
                    cout << "User " << u << " ditemukan.\n";
                    cout << "=====================================\n";

                    Node *head = NULL;
                    bacaNode(&head, u);
                    lihatPlaylistUser(head, u);

                    file.close();
                    system("pause");
                    return;
                }
                getline(file, p);
                getline(file, e);
            }

            file.close();
        }
        if (username == "0")
        {
            return;
        }
        system("cls");
        cout << RED << "User tidak ditemukan.\n";
        Sleep(1000);
    }

    // Fungsi untuk user menambahkaan lagu ke playlist yang dimiliki
    void pilihLaguDariDaftar(User *user)
    {
        cout << BLUE   << "=====================================\n";
        cout << YELLOW << "      Daftar Lagu yang Tersedia\n";
        cout << BLUE   << "=====================================\n";
        ifstream file("daftar_lagu.txt");

        if (file.is_open())
        {
            string judul, penyanyi, genre;
            int nomor = 1;
            int nomorLagu;

            while (getline(file, judul) && getline(file, penyanyi) && getline(file, genre))
            {
                cout << RED << nomor << ". " << judul << " - " << penyanyi << " (" << genre << ")\n";
                nomor++;
            }

            file.close();

            do
            {
                cout << BLUE << "=====================================\n";
                cout << YELLOW << "Masukkan nomor lagu yang ingin Anda tambahkan ke playlist (0 untuk kembali): ";
                cin >> nomorLagu;
                cin.ignore();

                if (nomorLagu > 0 && nomorLagu < nomor)
                {
                    ifstream file("daftar_lagu.txt");
                    bool laguSudahAdaDiPlaylist = false;
                    bool laguSudahAdaDiDaftarLagu = false;

                    for (int i = 1; i <= nomor; i++)
                    {
                        getline(file, judul);
                        getline(file, penyanyi);
                        getline(file, genre);

                        if (i == nomorLagu)
                        {
                            // Periksa apakah lagu sudah ada di playlist
                            Node *temp = user->head;
                            while (temp != nullptr)
                            {
                                if (temp->judul == judul)
                                {
                                    laguSudahAdaDiPlaylist = true;
                                    break;
                                }
                                temp = temp->next;
                            }

                            if (laguSudahAdaDiPlaylist)
                            {
                                cout << RED << "Lagu sudah ada di playlist Anda.\n";
                                Sleep(1000);
                            }
                            else
                            {
                                // Tambahkan lagu yang dipilih ke playlist user
                                ofstream userFile(user->username + ".txt", ios::app);
                                userFile << judul << "\n";
                                userFile << penyanyi << "\n";
                                userFile << genre << "\n";
                                cout << GREEN << "Lagu berhasil ditambahkan ke playlist.\n";
                                Sleep(1000);
                                tambahNode(&(user->head), judul, penyanyi, genre);
                                simpanNode(user->head, user->username);
                                userFile.close();
                            }
                        }
                    }

                    file.close();
                }
                else if (nomorLagu == 0)
                {
                    return; // Keluar dari loop jika nomor 0
                }
                else
                {
                    cout << RED << "Nomor lagu tidak valid.\n";
                    Sleep(1000);
                }
            } while (nomorLagu != 0);
        }
        else
        {
            cout << "Gagal membuka file daftar lagu.\n";
            Sleep(1000);
        }
    }

    queue<Node *> playlistQueue; // Membuat antrian (queue) untuk lagu

    // Fungsi untuk menampilkan teks lagu
    void playSong(Node *song)
    {
        system("cls");
        cout << BLUE   << "============================================\n";
        cout << YELLOW << "     Now Playing: " << song->judul << " - " << song->penyanyi << " (" << song->genre << ")\n";
        cout << BLUE   << "============================================\n";
        // Tunda program selama 5 detik
        Sleep(5000);
    }

    // Fungsi untuk memutar playlist menggunakan metode queue
    void playPlaylist(Node *head)
    {
        Node *currentSong = head;

        while (currentSong != nullptr)
        {
            playlistQueue.push(currentSong); // Menambahkan lagu ke dalam queue
            playSong(currentSong);           // Memutar lagu
            currentSong = currentSong->next; // Pindah ke lagu berikutnya
        }
    }

    // Fungsi untuk mengatur dan memainkan playlist user
    void playUserPlaylist(User *user)
    {
        playPlaylist(user->head);
    }

    // Fungsi utama
    int main()
    {
        int pilihan;                      // variabel untuk menyimpan pilihan menu
        string username, password, email; // variabel untuk menyimpan data user
        User *user = NULL;                // pointer untuk menyimpan user yang sedang login
        bool login = false;               // variabel untuk menyimpan status login
        bool admin = false;               // variabel untuk menyimpan status admin
        bool keluar = false;              // variabel untuk menyimpan status keluar
        int kesempatan = 3;               // variabel untuk menyimpan kesempatan login
        while (!keluar)
        {
            // Menampilkan menu utama
            tampilMenu();
            cin >> pilihan;
            cin.ignore();

            switch (pilihan)
            {
            case 1:
                do
                {
                    tampilLogin(); // menampilkan menu login
                    cout << "\n";
                    cout << "Username: ";
                    getline(cin, username);
                    cout << "Password: ";
                    getline(cin, password);

                    // Kondisi jika username dan password adalah admin
                    if (username == "admin" && password == "admin")
                    {
                        system("cls");
                        login = true;
                        admin = true;
                        cout << GREEN << "Anda berhasil login sebagai admin." << RESET << endl;
                        Sleep(1500);
                    }
                    // Kondisi jika username dan password adalah user
                    else if (cekLogin(username, password))
                    {
                        system("cls");
                        login = true;
                        admin = false;
                        user = new User(username, password, email);
                        bacaNode(&user->head, username);
                        cout << GREEN << "Anda berhasil login sebagai user." << RESET << endl;
                        Sleep(1500);
                    }
                    // Kondisi jika username dan password tidak cocok
                    else
                    {
                        system("cls");
                        kesempatan--;
                        cout << RED << "Username atau password salah.\n";
                        cout << YELLOW << "Anda memiliki " << kesempatan << " kesempatan lagi.\n";
                        Sleep(1500);
                        if (kesempatan == 0)
                        {
                            system("cls");
                            cout << "Anda gagal login.\n";
                            Sleep(1000);
                            keluar = true;
                            break;
                        }
                    }
                } while (!login); // Melakukan loop hingga login berhasil
                break;

            case 2:
                tampilRegister(); // menampilkan menu register
                cout << "\n";
                cout << "Username: ";
                getline(cin, username);
                // Kondiisi jika username sudah ada di file txt
                if (cekUsername(username))
                {
                    system("cls");
                    cout << RED << "Username sudah digunakan, silakan pilih username lain.\n";
                    Sleep(1000);
                    break;
                }
                cout << "Password: ";
                getline(cin, password);
                cout << "Email: ";
                getline(cin, email);
                buatUser(username, password, email); // buat user baru dan simpan ke file txt
                system("cls");
                cout << GREEN << "Anda berhasil register.\n";
                Sleep(1000);
                break;

            case 3:
                system("cls");
                cout << GREEN << "Terima kasih telah menggunakan program ini.\n";
                Sleep(1000);
                keluar = true;
                break;

            default:
                system("cls");
                cout << RED << "Pilihan tidak valid, silakan masukkan angka 1, 2, atau 3.\n";
                Sleep(1000);
                break;
            }

            // Kondisi setelah login
            while (login && !keluar)
            {
                if (admin) // jika user adalah admin
                {
                    tampilAdmin();
                }
                else
                {
                    tampilUser();
                }
                cin >> pilihan;
                cin.ignore();
                switch (pilihan)
                {
                case 1:
                    // pilihan 1 Admin (Menambah Lagu)
                    if (admin)
                    {
                        tambahLaguAdmin();
                        break;
                    }
                    // pilihan 1 User (Membuat playlist)
                    else
                    {
                        system("cls");
                        pilihLaguDariDaftar(user);
                        break;
                    }

                case 2:
                    // pilihan 2 Admin (Melihat list lagu)
                    if (admin)
                    {

                        lihatLaguAdmin();
                        break;
                    }
                    // pilihan 2 User (Melihat list lagu di playlist)
                    else
                    {
                        lihatPlaylistUser(user->head, user->username);
                        system("pause");
                        break;
                    }
                    break;

                case 3:
                    // pilihan 3 Admin (Mengubah Lagu)
                    if (admin)
                    {
                        ubahLaguAdmin();
                        break;
                    }
                    // pilihan 3 User (Mengubah urutan lagu di playlist)
                    else
                    {
                        lihatPlaylistUser(user->head, user->username);
                        ubahUrutanPlaylist(&(user->head));
                    }
                    break;

                case 4:
                    // pilihan 4 Admin (Menghapus Lagu)
                    if (admin)
                    {
                        hapusLaguAdmin();
                        break;
                    }
                    // pilhan 4 User (Menghapus Lagu yang ada di playlist)
                    else
                    {
                        lihatPlaylistUser(user->head, user->username);
                        int posisiHapus;
                        cout << YELLOW << "Masukkan nomor lagu yang ingin dihapus (0 untuk batal): ";
                        cin >> posisiHapus;

                        if (posisiHapus > 0)
                        {
                            hapusLaguDariPlaylist(&(user->head), posisiHapus);
                            simpanNode(user->head, user->username);
                        }
                    }
                    break;

                case 5:
                    // pilihan 5 Admin (Mencari user dan melihat playlist nya)
                    if (admin)
                    {
                        cariUser();
                    }
                    // pilihan 5 User (Putar musik)
                    else
                    {
                        playUserPlaylist(user);
                    }
                    break;

                case 6:
                    // pilihan 6 Admin & user (Logout)
                    if (admin)
                    {
                        system("cls");
                        cout << GREEN << "Anda berhasil logout sebagai admin.\n";
                        Sleep(1000);
                        login = false;
                    }
                    else
                    {
                        system("cls");
                        simpanNode(user->head, user->username);
                        delete user;
                        cout << GREEN << "Anda berhasil logout sebagai user.\n";
                        Sleep(1000);
                    }
                    login = false;
                    break;
                default:
                    system("cls");
                    cout << RED << "Pilihan tidak valid, silakan masukkan angka yang valid.\n";
                    Sleep(1000);
                    break;
                }
            }
        }
        return 0;
    }
