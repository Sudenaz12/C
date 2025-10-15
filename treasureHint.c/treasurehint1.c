#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 5
#define TREASURES 3
#define TRAPS 3
#define MAX_NAME 50
#define MAX_MOVES 100

// Oyun tahtası
char grid[SIZE][SIZE];
char visibleGrid[SIZE][SIZE];
int playerX = 0, playerY = 0;
int collectedTreasures = 0;
int moves = 0;
char playerName[MAX_NAME];

// Rastgele hazine ve tuzak yerleştirme fonksiyonu
void placeItems(char item, int count) {
    int placed = 0;
    while (placed < count) {
        int x = rand() % SIZE;
        int y = rand() % SIZE;
        if (grid[x][y] == ' ') { // Boş alana yerleştir
            grid[x][y] = item;
            placed++;
//placed, placeItems fonksiyonunun, belirlenen toplam sayıya (count) ulaşana kadar kaç tane öğeyi başarılı
//  bir şekilde oyun tahtasına yerleştirdiğini sayan bir değişkendir
        }
    }
}
fclose
// Tahtayı başlatma fonksiyonu (memset yerine döngü kullanıldı)
void initializeGame() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            grid[i][j] = ' ';
            visibleGrid[i][j] = '?';
        }
    }
    grid[playerX][playerY] = 'P';
    srand(time(NULL));
    placeItems('T', TREASURES);//treasures değeri 3 olduğu içn 3 tane T yerleşir
    placeItems('X', TRAPS);
}

// Tahtayı ekrana yazdıran fonksiyon
void printBoard() {
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", visibleGrid[i][j]);
        }
        printf("\n");
    }
    printf("\nCollected Treasures: %d\n", collectedTreasures);
}

int countNearby(char item) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {  // Y ekseni etrafındaki 3 hücreyi kontrol eder
        for (int j = -1; j <= 1; j++) {  // X ekseni etrafındaki 3 hücreyi kontrol eder
            int nx = playerX + i, ny = playerY + j;  // Yeni pozisyon
            // Hücrenin geçerli olduğundan emin ol (tahtanın dışına çıkmaması için)
            if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE && grid[nx][ny] == item) {
                count++;  // Eğer item (hazine veya tuzak) bulunursa sayacı arttır
            }
        }
    }
    return count;  // Sonuçları döndür
}

// Oyuncunun hareketi
void movePlayer(char direction) {
    int newX = playerX, newY = playerY;
    if (direction == 'u') newX--;  // Yukarı
    if (direction == 'd') newX++;  // Aşağı
    if (direction == 'l') newY--;  // Sola
    if (direction == 'r') newY++;  // Sağa

    if (newX < 0 || newX >= SIZE || newY < 0 || newY >= SIZE) {
        printf("Invalid move! Stay within the grid.\n");
        return;
    }

    // Eski pozisyonu temizle
    grid[playerX][playerY] = ' ';
    visibleGrid[playerX][playerY] = '=';

    playerX = newX;
    playerY = newY;

    // Yeni pozisyonu güncelle
    if (grid[playerX][playerY] == 'T') {
        collectedTreasures++;
        printf("You found a treasure! \n");
        grid[playerX][playerY] = '='; // Hazineyi alındı olarak işaretle
    }
    else if (grid[playerX][playerY] == 'X') {
        printf("You hit a trap! Game Over. \n");
        exit(0); // Oyunun bitmesi
    }

    grid[playerX][playerY] = 'P'; // Yeni pozisyonda oyuncuyu yerleştir
    visibleGrid[playerX][playerY] = 'P';
    moves++;

    // Yakındaki hazineleri ve tuzakları hesapla ve yazdır
    printf("Nearby Treasures: %d, Nearby Traps: %d\n", countNearby('T'), countNearby('X'));
}




void saveGame() {
    char filename[100];
    printf("Enter save file name: ");
    scanf("%s", filename);  // Kaydedilecek dosya adını al

    // Dosyayı yazma modunda açıyoruz
    FILE *file = fopen(filename, "w");  
    if (!file) {  // Eğer dosya açılamıyorsa hata ver
        printf("Error saving game! Could not open file for writing.\n");
        return;
    }

    // Oyuncu verilerini kaydediyoruz
    fprintf(file, "%s %d %d %d %d\n", playerName, playerX, playerY, collectedTreasures, moves);

    // Oyun tahtasını kaydediyoruz
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (grid[i][j] == ' ') {
                fprintf(file, "? ");  // Boş hücreleri ? olarak kaydediyoruz
            } else {
                fprintf(file, "%c ", grid[i][j]);  // Diğer hücreleri olduğu gibi kaydediyoruz
            }
        }
        fprintf(file, "\n");  // Satır sonu ekliyoruz
    }

    // Dosyayı kapatıyoruz
    fclose(file);
    printf("Game saved successfully to %s!\n", filename);
}




// Oyun yükleme fonksiyonu (visibleGrid düzeltildi)
// Oyun yükleme fonksiyonu
// Oyun yükleme fonksiyonu
void loadGame(char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error loading game! \n");
        return;
    }

    char savedPlayerName[MAX_NAME];
    fscanf(file, "%s %d %d %d", savedPlayerName, &playerX, &playerY, &collectedTreasures);

    // Check if the player loading the game matches the saved player's name
    if (strcmp(savedPlayerName, playerName) != 0) {
        printf("This game is not yours! Only the game owner can load this game.\n");
        fclose(file);
        exit(0);  // Exit the program immediately if it's not the owner's game
    }

    // Load the game if the player matches
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            fscanf(file, " %c", &grid[i][j]);
        }
    }

    fclose(file);
    printf("Game loaded successfully! \n");

    // **visibleGrid dizisini düzeltelim**
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i == playerX && j == playerY) {
                visibleGrid[i][j] = 'P';  // Oyuncunun olduğu yer
            } 
            else if (visibleGrid[i][j] == '-') {
                // Önceden ziyaret edilen alanlar '-' olarak kalsın
                visibleGrid[i][j] = '-';
            }
            else {
                visibleGrid[i][j] = '?';  // Bilinmeyen alanlar '?' olarak kalmalı
            }
        }
    }
}




// liderlik  tablosu güncelleme
void updaateLeaderboard() {
    FILE *file = fopen("leaderboard.txt", "a");
    if (!file) {
        printf("Error updating leaderboard! \n");
        return;
    }

    fprintf(file, "%s %d\n", playerName, moves);
    fclose(file);
}

// liderlik  tablosunu görüntüleme
void displayLeaderboard() {
    FILE *file = fopen("leaderboard.txt", "r");
    if (!file) {
        printf("No leaderboard found! \n");
        return;
    }

    char name[MAX_NAME];
    int score;
    printf("\n Leaderboard \n");
    while (fscanf(file, "%s %d", name, &score) != EOF) {
        printf("%s: %d moves\n", name, score);
    }

    fclose(file);
}

// Oyun döngüsü
void gameLoop() {
    char command;
    while (collectedTreasures < TREASURES) {
        printBoard();
        printf("Enter move (u/d/l/r) or 's' to save: ");
        scanf(" %c", &command);

        if (command == 's') {
            saveGame();
        } else {
            movePlayer(command);
        }
    }

    printf("Congratulations, you found all the treasures! \n");
    updateLeaderboard();
}
int main(int argc, char *argv[]) {
    if (argc < 3 || strcmp(argv[1], "p") != 0) {
        printf("Usage: ./treasureHunt.exe p <player_name> [load <filename>] [leaders]\n");
        return 1;
    }

    strcpy(playerName, argv[2]);

    // Check if the player is the game owner before allowing them to load their saved game
    if (argc == 5 && strcmp(argv[3], "load") == 0) {
        loadGame(argv[4]);  //  dosya adının adresini loadgame fonk. atıyor
    } else {
        initializeGame();  // Hiçbir yükleme komutu verilmezse oyunu başlatın

    }

    //  liderlik tablosunu görüntülemek için koşullara bakıyor
    if (argc == 4 && strcmp(argv[3], "leaders") == 0) {
        displayLeaderboard();
    } else {
        gameLoop();  //  komutları alıyor
    }

    return 0;
}