#include <iostream> //����� �������
#include <thread> //sleep_for����� ���� �������
#include <conio.h> //_getch ����� ���� �������

int main() {
    std::cout << "������ �Է��ϼ���!! �����Ϸ��� 'esc' Ű�� ��������." << std::endl;

    // �Է��� ������ ���ڿ�
    std::string input_ch; //�Է¹��� ���� ����
    std::string adogen = "123"; //�Ʒ�,����,a
    std::string jangpoong = "112";//�Ʒ�,�Ʒ�,����
    std::string kapkick = "241"; //����,��,�Ʒ�
    int pattern = 0;

    while (1) {
        if (_kbhit()) {
            char ch = _getch();
            if (ch == 80) {         //�Ʒ��� ����Ű = 80
                input_ch += '1';
            }
            else if (ch == 77) {    //������ ����Ű = 77
                input_ch += '2';
            }
            else if (ch == 97) {    //aŰ = 97
                input_ch += '3';
            }
            else if (ch == 75) {    //���� ����Ű = 75
                input_ch += '4';
            }
            // �Է��� 0.3�ʸ��� �׽��ϴ�.
            std::this_thread::sleep_for(std::chrono::milliseconds(300));

            // escŰ�� Ȯ���ϰ� ����
            if (ch == 27) { // esc = 27�Դϴ�.
                break;
            }
            //size_t->8����Ʈ
            size_t found_ado = input_ch.find(adogen);// find�� �Ƶ��� ����Ȯ��
            if (found_ado != std::string::npos) {
                pattern = 1;
                break;
            }
            size_t found_jang = input_ch.find(jangpoong);// ��ǳ ����Ȯ��
            if (found_jang != std::string::npos) {
                pattern = 2;
                break;
            }
            size_t found_kap = input_ch.find(kapkick);// ī��ű ����Ȯ��
            if (found_kap != std::string::npos) {
                pattern = 3;
                break;
            }                      
        }
    }
    if (pattern == 1) {
        std::cout << "�Ƶ���! =o" << std::endl;
    }
    else if (pattern == 2) {
        std::cout << "��ǳ! =>" << std::endl;
    }
    else if (pattern == 3) {
        std::cout << "ī��ű! o<=>o" << std::endl;
    }
    
    return 0;
}