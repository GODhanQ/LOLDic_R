#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

class LOLDic
{
    string name, position;
    int hp{}, mp{}, speed{}, range{};
    bool is_used{ false };

public:
    void InsertDic(const string& n, int h, int m, int s, int r, const string& pos)
    {
        name = n;
        position = pos;
        hp = h;
        mp = m;
        speed = s;
        range = r;
    }

    void Show() const
    {
        cout << "이름: " << name << " | "
            << "HP: " << hp << " | "
            << "MP: " << mp << " | "
            << "속도: " << speed << " | "
            << "사거리: " << range << " | "
            << "포지션: " << position << endl;
    }

    void Disable() {
        is_used = false;
    }

    void Ensable() {
        is_used = true;
    }

    string ShowName() const {
        return name;
    }

    string ShowPos() const {
        return position;
    }

    int ShowHp() const {
        return hp;
    }

    bool Is_Used() const {
        return is_used;
    }
};

void InSertTestData();
void ShowMenu();
int ExcuteCommand(int CommandNum);

void Print(int index);
int Search_R(int start, int num, const string name);
void InSert_R(const string name, int hp, int mp, int speed, int range, const string position, int index = 0);
void Delete_R(const string name, int index = 0, bool deleted = false);
void DeleteAll_R(const string pos, int index = 0);
void PrintAll_R(int index = 0);
void FindMaxHp_R(int Current_MaxHP = numeric_limits<int>::min(), int index = 0);
void SortByHp_R(int start, int end);

constexpr int Capacity{ 200 };
LOLDic Dictionary[Capacity];
int CountDic{};

int main()
{
    cout << "이 코드는 사전 데이터를 ifstream으로 입력받습니다.\n";
    cout << "리소스 파일에 testdata.txt를 넣어주세요.\n";
    InSertTestData();

    while (true)
    {

        int CommandNum{};

        ShowMenu();
        if (!(cin >> CommandNum))
        {
            system("cls");
            cout << "\n잘못된 입력입니다. 숫자를 입력하세요." << endl;
            cin.clear();  // 입력 스트림 플래그 초기화
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // 입력 버퍼 비우기
            continue;
        }

        if (CommandNum == 0)
            break;

        if (ExcuteCommand(CommandNum) == 1) {
            system("cls");
            cout << "잘못된 입력입니다. 다시 입력해주세요. " << endl;
            continue;
        }
    }
}

void ShowMenu()
{
    cout << "--------" << "**Menu**" << "--------" << endl;
    cout << "\t" << "1. Search" << endl;
    cout << "\t" << "2. Insert" << endl;
    cout << "\t" << "3. Delete" << endl;
    cout << "\t" << "4. DeleteAll" << endl;
    cout << "\t" << "5. PrintAll" << endl;
    cout << "\t" << "6. FindMaxHp" << endl;
    cout << "\t" << "7. SortByHp" << endl;
    cout << "0을 누르면 종료됩니다." << endl;
    cout << "커멘드 번호를 입력해주세요. : ";
}

int ExcuteCommand(int CommandNum)
{
    if (CommandNum == 1) {
        system("cls");
        string Sname;
        int index;

        cout << "검색할 챔피언의 이름을 입력해주세요. : ";
        cin >> Sname;

        index = Search_R(0, CountDic, Sname);
        system("cls");
        Print(index);

        return 0;
    }
    else if (CommandNum == 2) {
        system("cls");
        int hp{}, mp{}, speed{}, range{};
        string name, position;

        while (true) {
            cout << "추가할 챔피언 정보를 입력해주세요. " << endl;
            cout << "주의 : 입력 순서는 이름, 체력, 마나, 속도, 사거리, 포지션 입니다. " << endl;
            cout << "입력이 부족하다면 계속 입력을 기다리기에 꼭 6개의 입력을 해주세요." << endl;

            if (Capacity == CountDic) {
                system("cls");
                cout << "디렉토리가 꽉 찼습니다. \n";
                break;
            }

            else if (!(cin >> name >> hp >> mp >> speed >> range >> position)) {
                system("cls");
                cout << "입력에 오류가 있습니다. 다시 입력해주세요." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            for (int i = 0; i < CountDic; i++) {
                if (Dictionary[i].ShowName() == name) {
                    system("cls");
                    cout << "중복되는 이름이 있습니다. 다시 입력해주세요." << endl;
                    continue;
                }
            }

            break;
        }

        InSert_R(name, hp, mp, speed, range, position);
        system("cls");
        return 0;
    }
    else if (CommandNum == 3) {
        system("cls");
        string Dname;
        cout << "삭제할 챔피언의 이름을 입력해주세요. : ";
        cin >> Dname;

        Delete_R(Dname);
        return 0;
    }
    else if (CommandNum == 4) {
        system("cls");
        string Pos;
        bool flag{ false };
        cout << "삭제할 포지션을 입력해주세요. : ";
        cin >> Pos;

        DeleteAll_R(Pos);
        return 0;
    }
    else if (CommandNum == 5) {
        system("cls");

        PrintAll_R();
        cout << "총 " << CountDic << "개의 항목이 있습니다.\n";
        cout << "\n\n";
        return 0;
    }
    else if (CommandNum == 6) {
        system("cls");

        FindMaxHp_R();
        cout << "\n\n";
        return 0;
    }
    else if (CommandNum == 7) {
        system("cls");

        SortByHp_R(0, Capacity - 1);
        cout << "내림차순 정렬되었습니다.\n\n";
        return 0;
    }
    else {
        return 1;
    }
}

void Print(int index)
{
    if (true == Dictionary[index].Is_Used())
        Dictionary[index].Show();
}

int Search_R(int start, int num, const string name)
{
    if (CountDic == 0) {
        system("cls");
        cout << "딕셔너리에 항목이 존재하지 않습니다. \n";
        return NULL;
    }
    else if (num == 0) {
        system("cls");
        cout << "딕셔너리에 " << name << " 항목이 존재하지 않습니다. \n";
        return NULL;
    }

    if (name == Dictionary[start].ShowName()) {
        return start;
    }

    Search_R(start + 1, num - 1, name);
}

void InSert_R(const string name, int hp, int mp, int speed, int range, const string position, int index)
{
    if (index >= Capacity) {
        cout << "디렉토리가 꽉 찼습니다.\n";
        return;
    }

    if (false == Dictionary[index].Is_Used()) {
        Dictionary[index].InsertDic(name, hp, mp, speed, range, position);
        Dictionary[index].Ensable();
        CountDic++;
        return;
    }
    else 
        InSert_R(name, hp, mp, speed, range, position, index + 1);
}

void Delete_R(const string name, int index, bool deleted)
{
    if (CountDic == 0) {
        system("cls");
        cout << "딕셔너리에 항목이 존재하지 않습니다. \n";
        return;
    }
    else if (index >= Capacity) {
        return;
    }

    if (true == Dictionary[index].Is_Used() && name == Dictionary[index].ShowName()) {
        Dictionary[index].Disable();
        CountDic--;
        return;
    }
    else
        Delete_R(name, index + 1, deleted);

    return;
}

void DeleteAll_R(const string pos, int index)
{
    if (CountDic == 0) {
        system("cls");
        cout << "딕셔너리에 항목이 존재하지 않습니다. \n";
        return;
    }
    else if (index >= Capacity) {
        return;
    }
    
    if (true == Dictionary[index].Is_Used() && pos == Dictionary[index].ShowPos()) {
        Dictionary[index].Disable();
        CountDic--;
    }

    DeleteAll_R(pos, index + 1);
}

void PrintAll_R(int index)
{
    if (CountDic == 0) {
        system("cls");
        cout << "딕셔너리에 항목이 존재하지 않습니다. \n";
        return;
    }
    else if (index >= Capacity) {
        return;
    }

    if (true == Dictionary[index].Is_Used()) {
        Dictionary[index].Show();
    }

    PrintAll_R(index + 1);
}

void FindMaxHp_R(int Current_MaxHP, int index)
{
    int MaxHp{ Current_MaxHP };

    if (CountDic == 0) {
        system("cls");
        cout << "딕셔너리에 항목이 존재하지 않습니다. \n";
        return;
    }
    else if (index >= Capacity) {
        for (int i = 0; i < Capacity; i++) {
            if (true == Dictionary[i].Is_Used() && MaxHp == Dictionary[i].ShowHp()) {
                cout << "Max HP Champion : ";
                Print(i);
            }
        }
        return;
    }

    if (MaxHp < Dictionary[index].ShowHp()) {
        MaxHp = Dictionary[index].ShowHp();
    }
    
    FindMaxHp_R(MaxHp, index + 1);
}

void SortByHp_R(int start, int end)
{
    if (CountDic == 0) {
        system("cls");
        cout << "딕셔너리에 항목이 존재하지 않습니다. \n";
        return;
    }

    if (start >= end) {
        return;
    }

    int pivot = start;	//피봇은 첫 번째 원소 
    int i{ pivot + 1 }, j{ end }; //i는 피봇 다음원소 j는 마지막 원소 
    LOLDic temp;

    while (i <= j) {
        while (i <= end && Dictionary[i].ShowHp() >= Dictionary[pivot].ShowHp()) {
            i++;
        }
        while (j > start && Dictionary[j].ShowHp() <= Dictionary[pivot].ShowHp()) {
            j--;
        }

        if (i >= j) break;

        temp = Dictionary[i];
        Dictionary[i] = Dictionary[j];
        Dictionary[j] = temp;
    }

    temp = Dictionary[j];
    Dictionary[j] = Dictionary[pivot];
    Dictionary[pivot] = temp;

    SortByHp_R(start, j - 1);
    SortByHp_R(j + 1, end);
}

constexpr int MAX_LINE_LENGTH{ 256 }; // 적절한 최대 라인 길이 정의
constexpr int MAX_FIELD_LENGTH{ 64 }; // 각 필드의 최대 길이 정의
constexpr int MAX_FIELDS{ 6 };

void InSertTestData() {
    ifstream in("testdata.txt");
    if (!in.is_open()) {
        cerr << "Error opening testdata.txt" << endl;
        return;
    }

    char line[MAX_LINE_LENGTH];
    while (in.getline(line, MAX_LINE_LENGTH)) { // getline은 istream의 멤버 함수
        char* token;
        char* context{ nullptr };
        char fields[MAX_FIELDS][MAX_FIELD_LENGTH]{};
        int index{};

        token = strtok_s(line, "\t\t", &context); // 첫 번째 토큰 분리
        while (token != nullptr && index < MAX_FIELDS - 1) {
            strncpy_s(fields[index++], MAX_FIELD_LENGTH, token, _TRUNCATE); // 토큰 복사
            token = strtok_s(nullptr, "\t\t", &context); // 다음 토큰 분리
        }

        if (index == MAX_FIELDS - 1 && token != nullptr) { // 마지막 데이터 처리
            strncpy_s(fields[index], MAX_FIELD_LENGTH, token, _TRUNCATE);
            index++;
        }

        if (index == MAX_FIELDS) { // 데이터가 올바르게 6개 저장되었는지 확인
            char name[MAX_FIELD_LENGTH], position[MAX_FIELD_LENGTH];
            int hp, mp, speed, range;

            strncpy_s(name, MAX_FIELD_LENGTH, fields[0], _TRUNCATE);
            strncpy_s(position, MAX_FIELD_LENGTH, fields[5], _TRUNCATE);
            hp = atoi(fields[1]); mp = atoi(fields[2]); speed = atoi(fields[3]); range = atoi(fields[4]);

            InSert_R(name, hp, mp, speed, range, position);
        }
    }

    in.close();
}