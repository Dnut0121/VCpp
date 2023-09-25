#include <iostream> //입출력 헤더파일
#include <thread> //sleep_for사용을 위한 헤더파일
#include <conio.h> //_getch 사용을 위한 헤더파일

int main() {
    std::cout << "패턴을 입력하세요!! 종료하려면 'esc' 키를 누르세요." << std::endl;

    // 입력을 저장할 문자열
    std::string input_ch; //입력받은 문자 저장
    std::string adogen = "123"; //아래,오른,a
    std::string jangpoong = "112";//아래,아래,오른
    std::string kapkick = "241"; //오른,왼,아래
    int pattern = 0;

    while (1) {
        if (_kbhit()) {
            char ch = _getch();
            if (ch == 80) {         //아래쪽 방향키 = 80
                input_ch += '1';
            }
            else if (ch == 77) {    //오른쪽 방향키 = 77
                input_ch += '2';
            }
            else if (ch == 97) {    //a키 = 97
                input_ch += '3';
            }
            else if (ch == 75) {    //왼쪽 방향키 = 75
                input_ch += '4';
            }
            // 입력을 0.3초마다 쌓습니다.
            std::this_thread::sleep_for(std::chrono::milliseconds(300));

            // esc키를 확인하고 종료
            if (ch == 27) { // esc = 27입니다.
                break;
            }
            //size_t->8바이트
            size_t found_ado = input_ch.find(adogen);// find로 아도겐 패턴확인
            if (found_ado != std::string::npos) {
                pattern = 1;
                break;
            }
            size_t found_jang = input_ch.find(jangpoong);// 장풍 패턴확인
            if (found_jang != std::string::npos) {
                pattern = 2;
                break;
            }
            size_t found_kap = input_ch.find(kapkick);// 카프킥 패턴확인
            if (found_kap != std::string::npos) {
                pattern = 3;
                break;
            }                      
        }
    }
    if (pattern == 1) {
        std::cout << "아도겐! =o" << std::endl;
    }
    else if (pattern == 2) {
        std::cout << "장풍! =>" << std::endl;
    }
    else if (pattern == 3) {
        std::cout << "카프킥! o<=>o" << std::endl;
    }
    
    return 0;
}