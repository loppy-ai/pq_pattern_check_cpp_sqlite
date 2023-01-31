#include "../include/print.h"

// ���ʕ\��
void printResult(const Param_Info* pi, const Chain_Info* ci)
{
    cout << "---------------------�A�����---------------------" << endl;
    cout << "-----------------------------------" << endl;
    cout << "|   �F   |������|  �{��  |�y�A�{��|" << endl;
    cout << "-----------------------------------" << endl;
    cout << "|   ��   |" << right << setw(6) << ci->getElementCountPerColor(Red) << "|" << right << setw(8) << fixed << setprecision(2) << ci->getMagnificationPerColor(pi, Red) << "|" << right << setw(8) << fixed << setprecision(2) << ci->getMagnificationPerColor(pi, Red) * 6.0 << "|" << endl;
    cout << "|   ��   |" << right << setw(6) << ci->getElementCountPerColor(Blue) << "|" << right << setw(8) << fixed << setprecision(2) << ci->getMagnificationPerColor(pi, Blue) << "|" << right << setw(8) << fixed << setprecision(2) << ci->getMagnificationPerColor(pi, Blue) * 6.2 << "|" << endl;
    cout << "|   ��   |" << right << setw(6) << ci->getElementCountPerColor(Green) << "|" << right << setw(8) << fixed << setprecision(2) << ci->getMagnificationPerColor(pi, Green) << "|" << right << setw(8) << fixed << setprecision(2) << ci->getMagnificationPerColor(pi, Green) * 4.5 << "|" << endl;
    cout << "|   ��   |" << right << setw(6) << ci->getElementCountPerColor(Yellow) << "|" << right << setw(8) << fixed << setprecision(2) << ci->getMagnificationPerColor(pi, Yellow) << "|" << right << setw(8) << fixed << setprecision(2) << ci->getMagnificationPerColor(pi, Yellow) * 5.5 << "|" << endl;
    cout << "|   ��   |" << right << setw(6) << ci->getElementCountPerColor(Purple) << "|" << right << setw(8) << fixed << setprecision(2) << ci->getMagnificationPerColor(pi, Purple) << "|" << right << setw(8) << fixed << setprecision(2) << ci->getMagnificationPerColor(pi, Purple) * 5.5 << "|" << endl;
    cout << "|���C���h| ---- |"                                                            << right << setw(8) << fixed << setprecision(2) << ci->getMagnificationPerColor(pi, None) << "|" << right << setw(8) << fixed << setprecision(2) << ci->getMagnificationPerColor(pi, None) * 2.2 << "|" << endl;
    cout << "-----------------------------------" << endl;
}

// �^�C���X�^���v�\��
string getTimeStamp()
{
	time_t timer;
	struct tm local_time;
    stringstream ss;

	timer = time(NULL);
	localtime_s(&local_time, &timer);
	ss << setfill('0') << right << setw(2) << local_time.tm_mon + 1 << "/"
        << setfill('0') << right << setw(2) << local_time.tm_mday << " " 
        << setfill('0') << right << setw(2) << local_time.tm_hour << ":"
        << setfill('0') << right << setw(2) << local_time.tm_min << ":"
        << setfill('0') << right << setw(2) << local_time.tm_sec;

	return ss.str();
}