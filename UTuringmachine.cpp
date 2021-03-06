// UTuringmachine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <mutex>
#include <random>
#include <future>
#include <vector>
#include <iomanip>
#include <chrono>

using namespace std;


std::mutex cout_m;

void DoWork(string curr_state[], char curr_symb[], char new_symb[], char direction[], string new_state[], string tape, int head, int row)
{
	
	string next_state = "0";	
	while (head >= 0)
	{
		for (auto i = 0; i < row; i++)
		{
			if (curr_state[i] == next_state)
			{
				if (curr_symb[i] == tape[head])
				{
					tape[head] = new_symb[i];
					next_state = new_state[i];

					if (direction[i] == 'R')
					{
						head++;
					}
					else
					{
						head--;
					}
				}
			}
		}
		
		//system("cls");
		
	std::cout << tape << endl;
	
	}
	//return tape;
	
}

void process_file(const std::string& file_name)
{
	
	
		
	if (std::ifstream fin{ file_name })
	{
		//cout_m.lock();
		std::string tape;
		int head;
		if (fin >> head >> tape)
		{
			const int MAX_ROWS = 100;
			std::string curr_state[MAX_ROWS], new_state[MAX_ROWS];
			char direction[MAX_ROWS], curr_symbol[MAX_ROWS], new_symb[MAX_ROWS];

			int row = 0;
			while (row < MAX_ROWS &&
				fin >> curr_state[row] >> curr_symbol[row]
				>> new_symb[row] >> direction[row]
				>> new_state[row]) ++row;
			
			DoWork(curr_state, curr_symbol, new_symb, direction,
				new_state, tape, head, row);
			
		}
	}
	//cout_m.unlock();
	//std::lock_guard<std::mutex> unlock(cout_m);
	
	std::this_thread::sleep_for(std::chrono::seconds(1));
	
}

int main()
{
	//std::launch::async;
   /* std::thread A(process_file, "1.txt");
	std::thread B(process_file, "2.txt");
	std::thread C(process_file, "3.txt");
	std::thread D(process_file, "4.txt");
	

	A.join();
	B.join();
	C.join();
	D.join();*/

	std::vector< std::future<void> > futures;


	for (std::string file_name : { "1.txt", "2.txt", "3.txt", "4.txt" }) {
			futures.push_back(std::async(std::launch::async, process_file, file_name));
		}

		for ( auto& f : futures) f.wait();
}







































/*std::vector< std::future<void> > futures;*/


	/*for (std::string file_name : { "1.txt", "2.txt", "3.txt", "4.txt" }) {
		futures.push_back(std::async(std::launch::async, process_file, file_name));
	}

	for (const auto& f : futures) f.wait();*/






//
//struct Turing
//{
//	string curr_state;
//	char curr_symb;
//	char new_symb;
//	char direction;
//	string new_state;
//};

//
//void Universal_Turing_Machine( string curr_state[], char curr_symbol[], char new_symb[], char direction[], string new_state[], string tape, int head, int row)
//{
//	Turing T[3000];
//	//int head, row = 1;
//	//string tape, temp_state;
//	std::string temp_state;
//
//	while (head >= 0)
//		    {
//		        for (int i = 0; i < row; i++)
//		        {
//		            if (T[i].curr_state == temp_state)
//		            {
//		                if (T[i].curr_symb == tape[head])
//		                {
//							tape[head] = T[i].new_symb;
//							temp_state = T[i].new_state;
//							
//		                    if (T[i].direction == 'R')
//		                    {
//		                        head++;
//		                    }
//		                    if (T[i].direction == 'L') {
//		                        head--;
//		                    }
//							//system("cls");
//							cout << tape << endl;
//		                }				
//		            }			
//		        }		
//		    }	
//
//}
//
//void process_file(const std::string& file_name)
//{
//	static std::mutex cout_mutex; // static: shared across all threads
//
//	{
//		std::lock_guard<std::mutex> lock(cout_mutex);
//		std::cout << "function process_file, file name: " << std::quoted(file_name)
//			<< ", executed by thread " << std::this_thread::get_id() << '\n';
//	}
//
//	if (std::ifstream fin{ file_name })
//	{
//		std::string tape;
//		int head;
//		if (fin >> tape >> head)
//		{
//			const int MAX_ROWS = 100;
//			std::string curr_state[MAX_ROWS], new_state[MAX_ROWS];
//			char direction[MAX_ROWS], curr_symb[MAX_ROWS], new_symb[MAX_ROWS];
//
//			int row = 0;
//			while (row < MAX_ROWS &&
//				fin >> curr_state[row] >> curr_symb[row]
//				>> new_symb[row] >> direction[row]
//				>> new_state[row]) ++row;
//
//			Universal_Turing_Machine(curr_state, curr_symb, new_symb, direction,
//				new_state, tape, head, row);
//		}
//	}
//
//	// debug stub: mimic a time consuming operation by sleeping for a while
//	std::this_thread::sleep_for(std::chrono::milliseconds(100 + std::random_device{}() % 512));
//
//	{
//		std::lock_guard<std::mutex> lock(cout_mutex);
//		std::cout << "thread " << std::this_thread::get_id()
//			<< " has finished processing file " << std::quoted(file_name) << '\n';
//	}
//}
//
//
//
//
//
//
//int main()
//{
//
//	// https://en.cppreference.com/w/cpp/thread/future
//	std::vector< std::future<void> > futures;
//
//	// execute process_file asynchronously (in parallel) for each file
//	// https://en.cppreference.com/w/cpp/thread/async
//	for (std::string file_name : { "1.txt", "2.txt", "3.txt", "4.txt" })
//		futures.push_back(std::async(std::launch::async, process_file, file_name));
//
//	// wait for asynchronous execution to finish before ending the program
//	// https://en.cppreference.com/w/cpp/thread/future/wait
//	for (const auto& f : futures) f.wait();
//
//};
//
//





















//struct Turing
//{
//	string curr_state;
//	char curr_symb;
//	char new_symb;
//	char direction;
//	string new_state;
//};
//int main()
//{
//	Turing T[3000];
//	int head, row=1;      
//	string tape, temp_state;
//	temp_state = '0';
//	char fname[10];
//	ifstream ifile;
//
//
//	cout << "enter file name" << endl;
//	cin >> fname;
//	ifile.open(fname);
//
//	if (!ifile) {cout << "Error in opening file";}
//	ifile >> head;
//	//cout << head << endl;
//
//	ifile >> tape;
//	//cout << tape<<endl;
//	
//	while (!ifile.eof()) {
//		ifile >> T[row].curr_state; ifile >> T[row].curr_symb;  ifile >> T[row].new_symb; ifile >> T[row].direction;	ifile >> T[row].new_state;
//	   //  cout << T[row].curr_state;   cout << T[row].curr_symb;  cout << T[row].new_symb;  cout << T[row].direction;	 cout << T[row].new_state<<endl;
//		 row++;
//	}
//	
//	
//    
//	 while (head >= 0)
//    {
//        for (int i = 0; i < row; i++)
//        {
//            if (T[i].curr_state == temp_state)
//            {
//                if (T[i].curr_symb == tape[head])
//                {
//					tape[head] = T[i].new_symb;
//					temp_state = T[i].new_state;
//					
//                    if (T[i].direction == 'R')
//                    {
//                        head++;
//                    }
//                    if (T[i].direction == 'L') {
//                        head--;
//                    }
//					//system("cls");
//					cout << tape << endl;
//                }				
//            }			
//        }		
//    }	
//}
