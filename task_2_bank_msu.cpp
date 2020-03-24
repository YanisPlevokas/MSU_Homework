#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <cstdlib> // для system
using namespace std;


string NotStated = "NOT STATED";

struct Payment
{
	string CurrencyPayment;
	int SumPayment;
	string ReceiverNamePayment;
	string ReceiverNumberPayment;
};


void quickSortString(Payment* arr, int left, int right) 
{
	int i = left, j = right;
	Payment tmp;
	string pivot = arr[(left + right) / 2].ReceiverNamePayment;
	/* partition */
	while (i <= j) {
		while (arr[i].ReceiverNamePayment < pivot) 
		  {
		      i++;
		  }

		while (arr[j].ReceiverNamePayment > pivot) 
		      j--;
		if (i <= j) { 
		      tmp = arr[i];
		      arr[i] = arr[j];
		      arr[j] = tmp;
		      i++;
		      j--;
		}
	};

	/* recursion */
	if (left < j)
	quickSortString(arr, left, j);
	if (i < right)
	quickSortString(arr, i, right);
}

class Account
	{  
	public:
		static int EuroCourse;
		static int UsdCourse;
		static int CompletedTransactions;
		int PaymentsAmount;
		Payment* PaymentsHistory;
		string AccountNumber;
		string Currency;
		int Sum;

	public:
		Account()
		{
			PaymentsAmount = 0;
			PaymentsHistory = 0;
			Currency = "RUB";
			AccountNumber = NotStated;
			Sum = 0;
		}
		Account (const Account& copyAcc)
		{
			PaymentsAmount = copyAcc.PaymentsAmount;
			AccountNumber = copyAcc.AccountNumber;
			Currency = copyAcc.CurrencyPayment;
			PaymentsHistory = (Payment*) realloc (PaymentsHistory, PaymentsAmount);
			for (int i = 0; i < PaymentsAmount; i++)
			{
				PaymentsHistory[PaymentsAmount - 1].SumPayment = copyAcc.PaymentsHistory[PaymentsAmount - 1].SumPayment;
				PaymentsHistory[PaymentsAmount - 1].CurrencyPayment = copyAcc.PaymentsHistory[PaymentsAmount - 1].CurrencyPayment;
				PaymentsHistory[PaymentsAmount - 1].ReceiverNamePayment = copyAcc.PaymentsHistory[PaymentsAmount - 1].ReceiverNamePayment;
				PaymentsHistory[PaymentsAmount - 1].ReceiverNumberPayment = copyAcc.PaymentsHistory[PaymentsAmount - 1].ReceiverNumberPayment;
			}
		}

		~Account()
		{
			free(PaymentsHistory);
		}

		virtual const Account& operator=(const Account& NewAcc)
		{
			PaymentsAmount = NewAcc.PaymentsAmount;
			AccountNumber = NewAcc.AccountNumber;
			Currency = NewAcc.CurrencyPayment;
			PaymentsHistory = NewAcc.PaymentsHistory;
			return *this;
		}





		void MakePayment(int SumOfPayment, string CurrencyOfPayment,  string ReceiverNameNew,  string ReceiverNumberNew)
		{
			if ((PaymentsAmount + 5) % 5 == 0)
			{
				PaymentsHistory = (Payment*) realloc (PaymentsHistory, PaymentsAmount);
			}
				CompletedTransactions++;
				PaymentsAmount++;
				PaymentsHistory[PaymentsAmount - 1].SumPayment = SumOfPayment;
				PaymentsHistory[PaymentsAmount - 1].CurrencyPayment = CurrencyOfPayment;
				PaymentsHistory[PaymentsAmount - 1].ReceiverNamePayment = ReceiverNameNew;
				PaymentsHistory[PaymentsAmount - 1].ReceiverNumberPayment = ReceiverNumberNew;
				Sum -= SumOfPayment;
		}

		void OutputLastPayment()
		{
			OutputPayment(PaymentsAmount);
		}
		void OutputPayment(int index) const
		{
			if (index > PaymentsAmount || index < 0)
				cout << "Out of Range" << endl;
			else
			{
				cout << PaymentsHistory[index].ReceiverNamePayment << " - Receiver Name" << endl;
				cout << PaymentsHistory[index].ReceiverNumberPayment << " - Receiver Number" << endl;
				cout << PaymentsHistory[index].CurrencyPayment << " - Currency" << endl;
				cout << PaymentsHistory[index].SumPayment << " - Sum of Payment" << endl;
				cout << "____________________" << endl;
			}
		}

		virtual void OutputInfo() = 0;

		int ComputeCosts() const
		{
			int localSum = 0;

			for (int i = 0; i < PaymentsAmount; i++)
			{
				if (PaymentsHistory[i].CurrencyPayment == "EUR")
					localSum += PaymentsHistory[i].SumPayment * EuroCourse;
				if (PaymentsHistory[i].CurrencyPayment == "USD")
					localSum += PaymentsHistory[i].SumPayment * UsdCourse;
				if (PaymentsHistory[i].CurrencyPayment == "RUB")
					localSum += PaymentsHistory[i].SumPayment;
			}
			return localSum;
		}
		void OutputHistoryWithPerson(const string& Person, const string& Number) const
		{
			for (int i = 0; i < PaymentsAmount; i++)
			{
				if (PaymentsHistory[i].ReceiverNamePayment == Person && PaymentsHistory[i].ReceiverNumberPayment == Number)
					OutputPayment(i);
			}	
		}
		void OutputHistory() const
		{
			for (int i = 0; i < PaymentsAmount; i++)
			{
				OutputPayment(i);
			}
		}
		void SortByReceiverNames()
		{
			quickSortString(PaymentsHistory, 0, PaymentsAmount - 1);
		}


	};
	int Account::EuroCourse = 77;
	int Account::UsdCourse = 68;
	int Account::CompletedTransactions = 0;


class LawAccount : public Account
	{	
		string NumberOfLawFirm;
		string NameOfLawFirm;
	public:
		LawAccount()
		{
			PaymentsAmount = 0;
			PaymentsHistory = 0;
			Currency = "RUB";
			AccountNumber = NotStated;
			Sum = 0;
			NumberOfLawFirm = NotStated;
			NameOfLawFirm = NotStated;
		}

		LawAccount (const LawAccount& copyAcc)
		{
			PaymentsAmount = copyAcc.PaymentsAmount;
			AccountNumber = copyAcc.AccountNumber;
			Currency = copyAcc.CurrencyPayment;
			NumberOfLawFirm = copyAcc.NumberOfLawFirm;
			NameOfLawFirm = copyAcc.NameOfLawFirm;
			PaymentsHistory = (Payment*) realloc (PaymentsHistory, PaymentsAmount);
			for (int i = 0; i < PaymentsAmount; i++)
			{
				PaymentsHistory[PaymentsAmount - 1].SumPayment = copyAcc.PaymentsHistory[PaymentsAmount - 1].SumPayment;
				PaymentsHistory[PaymentsAmount - 1].CurrencyPayment = copyAcc.PaymentsHistory[PaymentsAmount - 1].CurrencyPayment;
				PaymentsHistory[PaymentsAmount - 1].ReceiverNamePayment = copyAcc.PaymentsHistory[PaymentsAmount - 1].ReceiverNamePayment;
				PaymentsHistory[PaymentsAmount - 1].ReceiverNumberPayment = copyAcc.PaymentsHistory[PaymentsAmount - 1].ReceiverNumberPayment;
			}
		}

		virtual const LawAccount& operator=(const LawAccount& NewAcc)
		{
			PaymentsAmount = NewAcc.PaymentsAmount;
			AccountNumber = NewAcc.AccountNumber;
			Currency = NewAcc.CurrencyPayment;
			for (int i = 0; i < PaymentsAmount; i++)
			{
				PaymentsHistory[PaymentsAmount - 1].SumPayment = NewAcc.PaymentsHistory[PaymentsAmount - 1].SumPayment;
				PaymentsHistory[PaymentsAmount - 1].CurrencyPayment = NewAcc.PaymentsHistory[PaymentsAmount - 1].CurrencyPayment;
				PaymentsHistory[PaymentsAmount - 1].ReceiverNamePayment = NewAcc.PaymentsHistory[PaymentsAmount - 1].ReceiverNamePayment;
				PaymentsHistory[PaymentsAmount - 1].ReceiverNumberPayment = NewAcc.PaymentsHistory[PaymentsAmount - 1].ReceiverNumberPayment;
			}
			NumberOfLawFirm = NewAcc.NumberOfLawFirm;
			NameOfLawFirm = NewAcc.NameOfLawFirm;
			return *this;
		}
		void changeInfo(string CurrencyNew = "RUB" , string AccountNumberNew = NotStated, int SumNew = 0, string NumberOfLawFirmNew = NotStated, string NameOfLawFirmNew = NotStated)
		{
			Currency = CurrencyNew;
			AccountNumber = AccountNumberNew;
			Sum = SumNew;
			NumberOfLawFirm = NumberOfLawFirmNew;
			NameOfLawFirm = NameOfLawFirmNew;

		}
		virtual void OutputInfo()
		{
			cout << NumberOfLawFirm << " - number of law firm" << endl;
			cout << NameOfLawFirm  << " - name of law firm" << endl;
			cout << Sum << " - current sum" << endl;
			cout << AccountNumber << " - account number" << endl;
			cout << PaymentsAmount << " - payments amount" << endl;
		}
		const Payment& operator[](int index)
		{
			if (index < PaymentsAmount)
				return PaymentsHistory[index];
			else
			{
				cout << "Mistake" << endl;
				Payment a;
				return a;
			}

		}
		friend std::ostream& operator<< (std::ostream &out, const LawAccount &point)
		{
			out << point.NumberOfLawFirm << " - number of law firm" << endl;
			out << point.NameOfLawFirm  << " - name of law firm" << endl;
			out << point.SumPayment << " - current sum" << endl;
			out << point.AccountNumber << " - account number" << endl;
			out << point.PaymentsAmount << " - payments amount" << endl;
			return out;
		}
	};


class UserAccount : public Account
	{	
		string NumberOfUserIDN;
	public:
		UserAccount()
		{
			PaymentsAmount = 0;
			PaymentsHistory = 0;
			Currency = "RUB";
			AccountNumber = NotStated;
			Sum = 0;
			NumberOfUserIDN = NotStated;
		}
		UserAccount (const UserAccount& copyAcc) 
		{
			PaymentsAmount = copyAcc.PaymentsAmount;
			AccountNumber = copyAcc.AccountNumber;
			Currency = copyAcc.CurrencyPayment;
			NumberOfUserIDN = copyAcc.NumberOfUserIDN;
			PaymentsHistory = (Payment*) realloc (PaymentsHistory, PaymentsAmount);
			for (int i = 0; i < PaymentsAmount; i++)
			{
				PaymentsHistory[PaymentsAmount - 1].SumPayment = copyAcc.PaymentsHistory[PaymentsAmount - 1].SumPayment;
				PaymentsHistory[PaymentsAmount - 1].CurrencyPayment = copyAcc.PaymentsHistory[PaymentsAmount - 1].CurrencyPayment;
				PaymentsHistory[PaymentsAmount - 1].ReceiverNamePayment = copyAcc.PaymentsHistory[PaymentsAmount - 1].ReceiverNamePayment;
				PaymentsHistory[PaymentsAmount - 1].ReceiverNumberPayment = copyAcc.PaymentsHistory[PaymentsAmount - 1].ReceiverNumberPayment;
			}
		}
		void changeInfo(string CurrencyNew = "RUB" , string AccountNumberNew = NotStated, int SumNew = 0, string NumberOfUserIDNNew = NotStated)
		{
			Currency = CurrencyPaymentNew;
			AccountNumber = AccountNumberNew;
			Sum = SumNew;
			NumberOfUserIDN = NumberOfUserIDNNew;
		}
		virtual const UserAccount& operator=(const UserAccount& NewAcc) 
		{
			PaymentsAmount = NewAcc.PaymentsAmount;
			AccountNumber = NewAcc.AccountNumber;
			Currency = NewAcc.CurrencyPayment;
			PaymentsHistory = (Payment*) realloc (PaymentsHistory, PaymentsAmount);
			for (int i = 0; i < PaymentsAmount; i++)
			{
				PaymentsHistory[PaymentsAmount - 1].SumPayment = NewAcc.PaymentsHistory[PaymentsAmount - 1].SumPayment;
				PaymentsHistory[PaymentsAmount - 1].CurrencyPayment = NewAcc.PaymentsHistory[PaymentsAmount - 1].CurrencyPayment;
				PaymentsHistory[PaymentsAmount - 1].ReceiverNamePayment = NewAcc.PaymentsHistory[PaymentsAmount - 1].ReceiverNamePayment;
				PaymentsHistory[PaymentsAmount - 1].ReceiverNumberPayment = NewAcc.PaymentsHistory[PaymentsAmount - 1].ReceiverNumberPayment;
			}
			NumberOfUserIDN = NewAcc.NumberOfUserIDN;
			return *this;
		}

		virtual void OutputInfo()
		{
			cout << NumberOfUserIDN << " - number of user IDN" << endl;
			cout << Sum << " - current sum" << endl;
			cout << AccountNumber << " - account number" << endl;
			cout << PaymentsAmount << " - payments amount" << endl;
		}
		friend std::ostream& operator<< (std::ostream &out, const UserAccount &point)
		{
			out << point.NumberOfUserIDN << " - number of user IDN" << endl;
			out << point.SumPayment << " - current sum" << endl;
			out << point.AccountNumber << " - account number" << endl;
			out << point.PaymentsAmount << " - payments amount" << endl;
			return out;
		}
		const Payment& operator[](int index)
		{
			if (index < PaymentsAmount)
				return PaymentsHistory[index];
			else
			{
				cout << "Mistake" << endl;
				Payment a;
				return a;
			}

		}


	};



int main ()
{
	LawAccount Yanis;
	UserAccount Ivan, Andrey;
	Ivan.changeInfo("123", "asd", 1234, "FASF");
	Yanis.MakePayment(123, "RUB", "Dmitriy", "24331");
	Yanis.OutputHistory();
	cout << Yanis << endl;
	Payment rock = Yanis[0];
	
  return 0;
}
