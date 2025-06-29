/* 
 学生成绩管理 
 设计要求： 
 一、定义学生类(student)类，其中至少包括姓名、性别、学号、班级和三门功课的成绩 
 二、实现下面的功能 
     1.输入功能:输入学生信息，并保存到文件中 
     2.计算每个学生的总分与平均分并按升序排序 
     3.能根据学号修改学生信息 
     4.能根据学号删除学生信息 
     5.能够根据学号查询学生信息 
 */ 
//IDE：Visual Studio Code 1.100.2
//编译环境：g++
/*版本V1.2    csv数据存储管理优化(支持EXCEL第三方数据修改，支持批量导入)*/ 
#include <iostream> 
#include <string> 
#include <fstream>           //文件IO 将学生信息保存至student.csv中
using namespace std; 

class student{ 
private: 
    string name;             //姓名
    string gender;           //性别
    string ID_number;        //学号
    string Class_name;       //班级名称
    double score_1;          //科目1 
    double score_2;          //科目2 
    double score_3;          //科目3 
    double Total_score;      //总分 
    double Average_score;    //平均分 
public: 
    void input(){ 
        cout << "----------------------输入信息---------------------"<<endl; 
        cout << "请输入学生姓名:"    ;cin >> name; 
        cout << "请输入学生性别:"    ;cin >> gender; 
        cout << "请输入学生学号:"    ;cin >> ID_number; 
        cout << "请输入学生班级:"    ;cin >> Class_name; 
        cout << "请输入学生成绩科目1:";cin >> score_1; 
        cout << "请输入学生成绩科目2:";cin >> score_2; 
        cout << "请输入学生成绩科目3:";cin >> score_3; 
        calculate(); // 输入后自动计算总分和平均分 
    }; 
    void display(){          //显示信息 
        cout <<"----------------------学生信息---------------------"<<endl; 
        cout << "姓名:"     << name           << endl; 
        cout << "性别:"     << gender         << endl; 
        cout << "学号:"     << ID_number      << endl; 
        cout << "班级:"     << Class_name     << endl; 
        cout << "成绩科目1:" << score_1        << endl; 
        cout << "成绩科目2:" << score_2        << endl; 
        cout << "成绩科目3:" << score_3        << endl; 
        cout << "总分:"     << Total_score    << endl; 
        cout << "平均分:"   << Average_score   << endl; 
    } 
    void modify(){           //修改信息 
        cout <<"----------------------修改信息---------------------"<<endl; 
        cout << "请输入学生姓名:"    ;cin >> name; 
        cout << "请输入学生性别:"    ;cin >> gender; 
        cout << "请输入学生学号:"    ;cin >> ID_number; 
        cout << "请输入学生班级:"    ;cin >> Class_name; 
        cout << "请输入学生成绩科目1:";cin >> score_1; 
        cout << "请输入学生成绩科目2:";cin >> score_2; 
        cout << "请输入学生成绩科目3:";cin >> score_3; 
        calculate(); // 修改后自动计算总分和平均分 
    } 
    void calculate(){        //计算平均分&总分 
        Total_score = score_1 + score_2 + score_3; 
        Average_score = Total_score / 3; 
    } 
    void saveToFile(ofstream & fout) {                                //保存学生信息到文件 
        fout << name << "," 
             << gender << "," 
             << ID_number << "," 
             << Class_name << "," 
             << score_1 << "," 
             << score_2 << "," 
             << score_3 << endl; 
    } 
    void loadFromFile(ifstream & fin) {                           //从文件加载学生信息 
        fin >> name 
            >> gender 
            >> ID_number 
            >> Class_name 
            >> score_1 
            >> score_2 
            >> score_3; 
        calculate();           //执行calculate()函数，计算总分和平均分 、
    } 

    double getTotalScore() { return Total_score; }    //获取总分 
    double getAverageScore() { return Average_score; }    //获取平均分 
    string ID_get() {return ID_number;}    //获取学号 
}; 

//全局变量及其初始化 
student* students = nullptr; // 修改变量名，避免与类名冲突 
int current_Student_Size = 0;   //当前学生数量 
int initial_Student_Size = 4;   //初始学生数量 

//学生扩容函数
void expandCapacity() { 
    initial_Student_Size *= 2; 
    student* newStudent = new student[initial_Student_Size]; 
    for (int i = 0; i < current_Student_Size; i++) { 
        newStudent[i] = students[i]; 
    } 
    delete[] students; 
    students = newStudent; 
} 

//从文件加载学生信息 
void loadFromFile() { 
    ifstream fin("student.txt"); 
    if (!fin.is_open()) { 
        cout << "WARN:无法打开文件,将创建新文件" << endl; 
        return; 
    } 
    
    // 先读取学生数量 
    int size; 
    if (fin >> size && size > 0) { 
        //释放原有内存 
        if (students != nullptr) { 
            delete[] students; 
        } 
        students = new student[size]; 
        initial_Student_Size = size; 
        current_Student_Size = size; 
        
        //逐个读取学生信息 
        for (int i = 0; i < size; i++) { 
            students[i].loadFromFile(fin); 
        } 
    } 
    fin.close();    
} 

//保存所有学生信息到文件 
void saveToFile() { 
    ofstream fout("student.csv"); 
    if (!fout.is_open()) { 
        cout << "ERROR:无法打开文件进行写入" << endl; //检测文件状态
        return; 
    } 
     if (!fout.is_open()) { 
        cout << "ERROR:无法打开文件进行写入" << endl; 
        return; 
    } 
    // 先写入学生数量 
    fout << current_Student_Size << endl; 
    
    //逐个写入学生信息 
    for (int i = 0; i < current_Student_Size; i++) { 
        students[i].saveToFile(fout); 
    } 
    fout.close(); 
    cout << "INFO:学生信息已成功保存" << endl; 
} 

void Score_Ranking(){ 
    for (int i = 0; i < current_Student_Size - 1; i++) { 
        for (int j = 0; j < current_Student_Size - i - 1; j++) { 
            if (students[j].getTotalScore() > students[j + 1].getTotalScore()) { 
                student temp = students[j]; 
                students[j] = students[j + 1]; 
                students[j + 1] = temp;                    //交换次序排序法
            } 
        } 
    } 
} 

void Menu(){ 
    cout << "\n===== 学生成绩管理系统 =====" << endl; 
    cout << "1. 添加学生信息" << endl; 
    cout << "2. 显示所有学生(按总分升序)" << endl; 
    cout << "3. 修改学生信息" << endl; 
    cout << "4. 删除学生信息" << endl; 
    cout << "5. 查询学生信息" << endl; 
    cout << "0. 退出系统&保存" << endl; 
    cout << "============V1.2============" << endl; 
    cout << "请选择操作(0-5):"; 
} 

//添加学生信息
void addStudent() { 
    if (current_Student_Size >= initial_Student_Size) { 
        expandCapacity(); 
    } 
    
    students[current_Student_Size].input(); 
    current_Student_Size++; 
    cout << "INFO:学生信息添加成功!" << endl; 
} 

//显示所有学生信息(按总分升序)
void displayAllStudents() { 
    if (current_Student_Size == 0) { 
        cout << "WARN:暂无学生信息!" << endl; 
        return; 
    } 
    
    Score_Ranking(); // 先排序再显示 
    for (int i = 0; i < current_Student_Size; i++) { 
        students[i].display(); 
        cout << "" << endl; 
        cout << "第" << i + 1 << "名/共" << current_Student_Size << "名" << endl; 
    } 
} 


//修改学生信息
void modifyStudent() { 
    if (current_Student_Size == 0) { 
        cout << "WARN:暂无学生信息!" << endl; 
        return; 
    } 
    string id; 
    cout << "INFO:请输入要修改的学生学号:"; 
    cin >> id; 
    for (int i = 0; i < current_Student_Size; i++) { 
        if (students[i].ID_get() == id) { 
            students[i].modify(); 
            cout << "INFO:学生信息修改成功!" << endl; 
            return; 
        } 
    } 
    
    cout << "WARN:未找到学号为\"" << id << "\"的学生!" << endl; 
} 

//删除学生信息
void deleteStudent() { 
    if (current_Student_Size == 0) { 
        cout << "WARN:暂无学生信息!" << endl; 
        return; 
    } 
    
    string id; 
    cout << "INFO:请输入要删除的学生学号:"; 
    cin >> id; 
    
    for (int i = 0; i < current_Student_Size; i++) { 
        if (students[i].ID_get() == id) { 
            // 移动数组元素，覆盖要删除的学生 
            for (int j = i; j < current_Student_Size - 1; j++) { 
                students[j] = students[j + 1]; 
            } 
            current_Student_Size--; 
            cout << "INFO:学生信息删除成功!" << endl; 
            return; 
        } 
    } 
    
    cout << "WARN:未找到学号为\"" << id << "\"的学生!" << endl; 
} 

void queryStudent() { 
    if (current_Student_Size == 0) { 
        cout << "WARN:暂无学生信息!" << endl; 
        return; 
    } 
    
    string id; 
    cout << "INFO:请输入要查询的学生学号:"; 
    cin >> id; 
    
    for (int i = 0; i < current_Student_Size; i++) { 
        if (students[i].ID_get() == id) { 
            students[i].display(); 
            return; 
        } 
    } 
    cout << "WARN:未找到学号为\"" << id << "\"的学生!" << endl; 
} 

int main() { 
    // 初始化学生数组 
    students = new student[initial_Student_Size]; 
    // 从文件加载学生信息 
    loadFromFile(); 
    int choice; 
    while (true) { 
        Menu(); 
        cin >> choice; 
        
        switch (choice) { 
            case 1: 
                addStudent(); 
                break; 
            case 2: 
                displayAllStudents(); 
                break; 
            case 3: 
                modifyStudent(); 
                break; 
            case 4: 
                deleteStudent(); 
                break; 
            case 5: 
                queryStudent(); 
                break; 
            case 0: 
                saveToFile(); 
                delete[] students; // 释放内存 
                cout << "INFO:谢谢使用，再见!" << endl; 
                return 0; 
            default: 
                cout << "WARN:无效的选项，请重新输入!" << endl; 
        } 
    } 
    return 0; 
} 