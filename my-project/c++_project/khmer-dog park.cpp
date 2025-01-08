#include <iostream>
using namespace std;

class Khmer_dog_park {
public:
    int package, point, i, ans;
    float hight;
    
    void showMenu() {
        cout << "-----------\n   Menu\n-----------\n[1]Package details\n[2]Check height\n[3]Choose package\n[4]Pay\n[0]Exit" << endl;
    }
    
    // รับค่าความสูง
    float getHigh() {
        cout << "------------------------\n#Tell me your height#\n------------------------" << endl;
        cout << "Enter your height: ";
        cin >> hight;
        return hight;
    }

    // แสดง package และ ราคา
    void showPackage() {
        cout << "-------\nPackage\n-------\n#Extreme package# 300 baht\n-Roller Coaster\n-Raptor\n-Falcon\n-Viking\n" << endl;
        cout << "#Family package# 250 baht\n-Bouncing castle\n-Inflatable house\n-Swan boat\n" << endl;
        cout << "#Other package# 200 baht\n-Carousel and giant house\n\n#All you can play package# 400 baht\n-You can play anything you want in Khmerdogpark\n" << endl;
    }

    // คำนวณราคา package
    int setPackage(int a) {
        int pack = 0; // กำหนดค่าเริ่มต้นให้กับ pack
        while (true) {
            cout << "--------------\nChoose package\n--------------\n[1]Extreme package 300 baht\n[2]Family package 250 baht\n[3]Other package 200 baht\n[4]All you can play package 400 baht\n[0]Exit" << endl;
            cin >> ans;
            switch (ans) {
                case 1:
                    pack += 300; // เพิ่มค่า 300
                    break;
                case 2:
                    pack += 250; // เพิ่มค่า 250
                    break;
                case 3:
                    pack += 200; // เพิ่มค่า 200
                    break;
                case 4:
                    pack += 400; // เพิ่มค่า 400
                    break;
                case 0:
                    break; // ออกจากการเลือก package
            }
            a--;
            if (a == 0) {
                break; // ถ้าจำนวนคนครบแล้ว ให้หยุด
            }
        }
        return pack; // ส่งกลับราคาที่คำนวณได้
    }

    Khmer_dog_park() {
        cout << "\n------------------------\nWelcome to Khmerdogpark\n------------------------" << endl;
        i = 0;
    }
};

class Rule : public Khmer_dog_park {
public:
    // ตรวจสอบส่วนสูงของผู้ใช้งาน
    void checkRule() {
        if (hight >= 131) {
            cout << "\nYou can play in #Extreme-zone# and #carousel and giant house#" << endl;
        } else {
            cout << "\nYou can play in #Family-zone# and #carousel and giant house#" << endl;
        }
    }
};

class Customer : public Rule {
public:
    // เลือกเมนู
    int chooseMenu() {
        cout << "Choose: ";
        cin >> i;
        return i;
    }
};

int main() {
    Customer player;
    int i = 0;
    int price = 0; // เก็บราคาสุดท้าย
    int groupCount = 0; // เก็บจำนวนคนในกลุ่ม

    cout << "How many people in your group: ";
    cin >> groupCount;

    while (true) {
        player.showMenu();  // แสดงเมนู
        i = player.chooseMenu();  // รับคำสั่งจากผู้ใช้

        if (i == 1) {
            player.showPackage();  // แสดงรายละเอียดแพ็คเกจ
        }
        else if (i == 2) {
            player.getHigh();  // รับค่าความสูง
            player.checkRule();  // ตรวจสอบกฎตามความสูง
        }
        else if (i == 3) {
            int totalPackage = player.setPackage(groupCount);  // เพิ่มราคาของกลุ่ม
            price += totalPackage;  // รวมราคา
            cout << "Total Price: " << price << " baht" << endl;  // แสดงราคา
        }
        else if (i == 4) {
            cout << "Total Price: " << price << " baht" << endl;  // แสดงราคาเมื่อเลือกจ่าย
        }
        else if (i == 0) {
            break;  // ออกจากโปรแกรม
        }
    }

    return 0;
}
